float yMin, yMax = 0;
float pMin, pMax = 0;
float rMin, rMax = 0;

float orX, ORx, ORX = 0;
float orY, ORy, ORY = 0;
float orZ, ORz, ORZ = 0;

float yaw, pitch, roll;
int yawS, pitchS, rollS;

int yawMIDI, pitchMIDI, rollMIDI; //cc1, cc2, cc3



void extractionOrientation(){
  
    orX = orientation.x; // orientation.y (roll) original value
    orY = orientation.y; // orientation.y (pitch) original value
    orZ = orientation.z; // orientation.z (yaw) original value
  
}

//this function CENTER the orientation Myo Data
void centerOrientation (){
    ORZ = ORz-(orZ-0.5); // centering YAW
    ORY = ORy-(orY-0.5); // centering PITCH
    ORX = ORx-(orX-0.5); // centering ROLL

    if(ORZ<0) {ORZ = 1+ORZ;}
    else if (ORZ>1) {ORZ = 1-ORZ;}
    else  {ORZ = ORZ;}
    
    if(ORY<0) {ORY = 1+ORY;}
    else if (ORY>1) {ORY = 1-ORY;}
    else  {ORY = ORY;}
    
    if(ORX<0) {ORX = 1+ORX;}
    else if (ORX>1) {ORX = 1-ORX;}
    else  {ORX = ORX;}  
}



//this function REVERSE the orientation Myo Data
void reverseOrientation(){
 roll = abs(ORX-reverseRoll); // reverse + scale
 pitch = abs(ORY-reversePitch); // reverse + scale
 yaw = abs(ORZ-reverseYaw); // reverse + scale 
}

//this function RESCALE the orientation Myo Data
void scaleOrientation(){
  
  yMin = rYaw.getLowValue();
  yMax = rYaw.getHighValue();

  pMin = rPitch.getLowValue();
  pMax = rPitch.getHighValue();
  
  rMin = rRoll.getLowValue();
  rMax = rRoll.getHighValue();

  emgMin = avgEMG.getLowValue();
  emgMax = avgEMG.getHighValue();
  
  roll = map(roll, 0, 1, rMin, rMax);
  pitch = map(pitch, 0, 1, pMin, pMax);
  yaw = map(yaw, 0, 1, yMin, yMax);
    
   roll = max(roll, 0);
   roll = min(roll, 1);     
   pitch = max(pitch, 0);
   pitch = min(pitch, 1);
   yaw = max(yaw, 0);
   yaw = min(yaw, 1);
}

void sendOrientation(){

if(MIDI){
     rollMIDI = int(roll*127);
     pitchMIDI = int(pitch*127);
     yawMIDI = int(yaw*127);
  
     myBus.sendControllerChange(chMIDI, 1, yawMIDI); // Send a Midi noteOn
     myBus.sendControllerChange(chMIDI, 2, pitchMIDI); // Send a Midi noteOn
     myBus.sendControllerChange(chMIDI, 3, rollMIDI); // Send a Midi noteOn
     

     }
     
 if(OpenSoundControl){ 
    rollS = int(roll*255);
    pitchS = int(pitch*255);
    yawS = int(yaw*255);
    
    OscMessage orient = new OscMessage("/orientation");
    OscMessage orientS = new OscMessage("/orientationS");
   
    orient.add(yaw);
    orient.add(pitch);
    orient.add(roll);
    
    orientS.add(yawS);
    orientS.add(pitchS);
    orientS.add(rollS);
 
    oscP5.send(orient, myRemoteLocation);   
    oscP5.send(orientS, myRemoteLocation);
 }

}


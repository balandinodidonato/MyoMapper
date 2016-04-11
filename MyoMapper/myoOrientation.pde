float yMin, yMax = 0;
float pMin, pMax = 0;
float rMin, rMax = 0;

float orX, ORx, ORX = 0;
float orY, ORy, ORY = 0;
float orZ, ORz, ORZ = 0;

float yaw, pitch, roll;
int yawS, pitchS, rollS;

int yawMIDI, pitchMIDI, rollMIDI; //cc1, cc2, cc3

boolean orientOnOff = true;

void Orientation(){
  
  orX = orientation.x; // orientation.y (roll) original value
  orY = orientation.y; // orientation.y (pitch) original value
  orZ = orientation.z; // orientation.z (yaw) original value
  
  centerOrientation();
  scaleOrientation();
  reverseOrientation();
  sendOrientation();
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

//this function RESCALE the orientation Myo Data
void scaleOrientation(){
  
  yMin = rYaw.getLowValue();
  yMax = rYaw.getHighValue();
  pMin = rPitch.getLowValue();
  pMax = rPitch.getHighValue();
  rMin = rRoll.getLowValue();
  rMax = rRoll.getHighValue();
  
  roll = map(ORX, 0, 1, rMin, rMax);
  pitch = map(ORY, 0, 1, pMin, pMax);
  yaw = map(ORZ, 0, 1, yMin, yMax);
    
   roll = max(roll, 0);
   roll = min(roll, 1);     
   pitch = max(pitch, 0);
   pitch = min(pitch, 1);
   yaw = max(yaw, 0);
   yaw = min(yaw, 1);
}

void reverseOrientation(){
  if(reverseYaw) yaw = abs(1-yaw);
  if(reversePitch) pitch = abs(1-pitch);
  if(reverseRoll) roll = abs(1-roll);
}

void sendOrientation(){

  if(MIDI){
    rollMIDI = int(roll*127);
    pitchMIDI = int(pitch*127);
    yawMIDI = int(yaw*127);
    
    myBus.sendControllerChange(chMIDI, 10, yawMIDI);
    myBus.sendControllerChange(chMIDI, 11, pitchMIDI);
    myBus.sendControllerChange(chMIDI, 12, rollMIDI);
    }
     
  if(OpenSoundControl){ 
    OscMessage orient = new OscMessage("/orientation");
     
    orient.add(yaw);
    orient.add(pitch);
    orient.add(roll);
  
    oscP5.send(orient, myRemoteLocation);   
    }
}


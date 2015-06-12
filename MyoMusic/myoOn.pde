float[] EMG = new float[8];

float yaw, pitch, roll;
int yawS, pitchS, rollS;
int intesity = 0;

float orX, ORx, ORX = 0;
float orY, ORy, ORY = 0;
float orZ, ORz, ORZ = 0;

float intensity  = 0;
int intensityS = 0;

int accSx, accSy, accSz = 0;
int gyroSx, gyroSy, gyroSz = 0;

int poseOSC, poseOSCs = 0;

float yMin, yMax = 0;
float pMin, pMax = 0;
float rMin, rMax = 0;
float emgMin  = 0;
float emgMax = 1;


int rollMIDI, pitchMIDI, yawMIDI; //cc1, cc2, cc3
int accXMIDI, accYMIDI, accZMIDI; //cc4, cc5, cc6
int gyroXMIDI, gyroYMIDI, gyroZMIDI; //cc7, cc8, cc9
int intensityMIDI; //cc10
int[] emgMIDI = new int[8]; //cc11, cc12, cc13, cc14, cc15, cc16, cc17, cc18

String connectionState, syncState;

void myoOn(Myo.Event event, Device myo, long timestamp) {
  
  switch(event) {
  case PAIR:
    println("myoOn PAIR");
    break;
  case UNPAIR:
    println("myoOn UNPAIR");
    break;
  case CONNECT:
    connectionState = "CONNECTED";
    break;
  case DISCONNECT:
    connectionState = "DISCONNECTED";
    break;
  case ARM_SYNC:
    syncState = "SYNC";
    println("myoOn ARM_SYNC");

    break;
  case ARM_UNSYNC:
    syncState = "UNSYNC";
    println("myoOn ARM_UNSYNC");
    break;
  case POSE:
    println("myoOn POSE");
   

    pose = myo.getPose();
   
    if ((pose=="REST")||(pose=="UNCKNOWN")) poseOSC = 0;
    else if (pose=="FIST") poseOSC = 1;
    else if (pose=="FINGERS_SPREAD") poseOSC = 2;
    else if (pose=="WAVE_IN") poseOSC = 3;
    else if (pose=="WAVE_OUT") poseOSC = 4;
    else if (pose=="DOUBLE_TAP") poseOSC = 5;
 
 if(OpenSoundControl){ 
    OscMessage Pose = new OscMessage("/pose");
    
    poseOSCs = poseOSC*51; // scale poseI values into serial values
    // 0 = rest and uncknown
    // 51 = FIST
    // 102 = FINGERS_SPREAD
    // 153 = WAVE_IN
    // 204 = WAVE_OUT
    // 255 = DOUBLE_TAP
    
    Pose.add(pose);
    Pose.add(poseOSC);
    Pose.add(poseOSCs);

    oscP5.send(Pose, myRemoteLocation);
 }
    break;
 
  case ORIENTATION:
  
     PVector orientation = myo.getOrientation();
     
    orX = orientation.x; // orientation.y (roll) original value
    orY = orientation.y; // orientation.y (pitch) original value
    orZ = orientation.z; // orientation.z (yaw) original value
   
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
    
    roll = abs(ORX-reverseRoll); // reverse + scale
    pitch = abs(ORY-reversePitch); // reverse + scale
    yaw = abs(ORZ-reverseYaw); // reverse + scale
    
    roll = map(roll, 0, 1, rMin, rMax);
    pitch = map(pitch, 0, 1, pMin, pMax);
    yaw = map(yaw, 0, 1, yMin, yMax);
    
   roll = max(roll, 0);
   roll = min(roll, 1);     
   pitch = max(pitch, 0);
   pitch = min(pitch, 1);
   yaw = max(yaw, 0);
   yaw = min(yaw, 1);
  
    
if(MIDI){
     rollMIDI = int(roll*127);
     pitchMIDI = int(pitch*127);
     yawMIDI = int(yaw*127);
  
     myBus.sendControllerChange(chMIDI, 1, rollMIDI); // Send a Midi noteOn
     myBus.sendControllerChange(chMIDI, 2, pitchMIDI); // Send a Midi noteOn
     myBus.sendControllerChange(chMIDI, 3, yawMIDI); // Send a Midi noteOn
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
 
    break;
 
  case ACCELEROMETER:
    // println("myoOn ACCELEROMETER");
      PVector acceleration = myo.getAccelerometer();

    accSx= int(acceleration.x*40.58451048843329); // scale acceleration.x (0-2PI) -> serial value (0-255)
    accSy= int(acceleration.y*40.58451048843329); // scale acceleration.x (0-2PI) -> serial value (0-255)
    accSz= int(acceleration.z*40.58451048843329); // scale acceleration.x (0-2PI) -> serial value (0-255)
 
if(MIDI){   
     accXMIDI = int(acceleration.x/(2*PI)*127);
     accYMIDI = int(acceleration.y/(2*PI)*127);
     accZMIDI = int(acceleration.z/(2*PI)*127);
     
     myBus.sendControllerChange(chMIDI, 4, rollMIDI); // Send a Midi noteOn
     myBus.sendControllerChange(chMIDI, 5, pitchMIDI); // Send a Midi noteOn
     myBus.sendControllerChange(chMIDI, 6, yawMIDI); // Send a Midi noteOn
    }
    
if(OpenSoundControl){  
    OscMessage acc = new OscMessage("/acc");
    OscMessage accS = new OscMessage("/accS");
   
    acc.add(acceleration.x); //  0-2PI
    acc.add(acceleration.y); //  0-2PI
    acc.add(acceleration.z); //  0-2PI
 
    accS.add(accSx); // 0-255
    accS.add(accSy); // 0-255
    accS.add(accSz); // 0-255
        
   oscP5.send(acc, myRemoteLocation); 
   oscP5.send(accS, myRemoteLocation); 
}

    break;
 
  case GYROSCOPE:
    // println("myoOn GYROSCOPE");
      PVector gyro = myo.getGyroscope();
  //  println("acceleration" + acceleration.x + " " + acceleration.y + " " + acceleration.z);

if(MIDI){   
     gyroXMIDI = int(gyro.x*0.127);
     gyroYMIDI = int(gyro.y*0.127);
     gyroYMIDI = int(gyro.z*0.127);
     
     myBus.sendControllerChange(chMIDI, 7, rollMIDI); // Send a Midi noteOn
     myBus.sendControllerChange(chMIDI, 8, pitchMIDI); // Send a Midi noteOn
     myBus.sendControllerChange(chMIDI, 9, yawMIDI); // Send a Midi noteOn
    }

if(OpenSoundControl){ 
    OscMessage Gyro = new OscMessage("/gyro");
    OscMessage gyroS = new OscMessage("/gyroS");
   
    gyroSx = int(gyro.x*0.255);
    gyroSy = int(gyro.y*0.255);
    gyroSz = int(gyro.z*0.255);

    Gyro.add(gyro.x);
    Gyro.add(gyro.y);
    Gyro.add(gyro.z);
    
    gyroS.add(gyroSx);
    gyroS.add(gyroSy);
    gyroS.add(gyroSz);
    
    oscP5.send(Gyro, myRemoteLocation); 
    oscP5.send(gyroS, myRemoteLocation); 
}
    break;
 
  case RSSI:
    println("myoOn RSSI");
    break;
 
  case EMG:  
      int emg[] = myo.getEmg(); // array of EMG data
      float emgSum = 0;

      for(int i=0; i<8; i++){

      emg[i] = abs(emg[i]);  // add emg value to /emg0 message
      EMG[i] = abs(reverseEmg-emg[i]);
      EMG[i] = map(EMG[i], 0, 128, emgMin, emgMax);
      emgSum = EMG[i]+emgSum; // EMG sum for avg calculation    
      if (MIDI){
        emgMIDI[i] = int(EMG[i]*127);
        myBus.sendControllerChange(chMIDI, 11+i, emgMIDI[i]);}
  }
     
      intensity = emgSum/8; // average calculation
      intensity = max(intensity, 0);
      intensity = min(intensity, 1);

     if (MIDI) {
      intensityMIDI = int(intensity*127);
      myBus.sendControllerChange(chMIDI, 10, intensityMIDI); // Send a 
      }
     
   if(OpenSoundControl){  
    
     OscMessage Emg = new OscMessage("/emg");
     OscMessage emgAvg = new OscMessage("/emgAvg");   
     OscMessage emgAvgS = new OscMessage("/emgAvgs");  
     
      intensityS = int(intensity*255);
     
      Emg.add(emg);
      emgAvg.add(intensity);
      emgAvgS.add(intensityS);
      
      oscP5.send(Emg, myRemoteLocation);
      oscP5.send(emgAvg, myRemoteLocation);
      oscP5.send(emgAvgS, myRemoteLocation);
   }
    break;
  }
}

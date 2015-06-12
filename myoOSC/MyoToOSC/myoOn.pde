float[] EMG = new float[8];

float yaw, pitch, roll;
int yawS, pitchS, rollS;
int intesity = 0;

float orX, ORx, ORX = 0;
float orY, ORy, ORY = 0;
float orZ, ORz, ORZ = 0;
float intensity = 0;

int accSx, accSy, accSz = 0;
int gyroSx, gyroSy, gyroSz = 0;

int poseOSC, poseOSCs = 0;

float yMin, yMax = 0;
float pMin, pMax = 0;
float rMin, rMax = 0;
float emgMin, emgMax = 0;

void myoOn(Myo.Event event, Device myo, long timestamp) {
  
  switch(event) {
  case PAIR:
    println("myoOn PAIR");
    break;
  case UNPAIR:
    println("myoOn UNPAIR");
    break;
  case CONNECT:
    println("myoOn CONNECT");
    break;
  case DISCONNECT:
    println("myoOn DISCONNECT");
    break;
  case ARM_SYNC:
    println("myoOn ARM_SYNC");
    OscMessage sync = new OscMessage("/sync");
    sync.add(myo.getArm());
    sync.add(myo.getFirmware());
    oscP5.send(sync, myRemoteLocation);
    break;
  case ARM_UNSYNC:
    println("myoOn ARM_UNSYNC");
    break;
  case POSE:
    println("myoOn POSE");
    OscMessage Pose = new OscMessage("/pose");

    pose = myo.getPose();
    
    if ((pose=="REST")||(pose=="UNCKNOWN")) poseOSC = 0;
    else if (pose=="FIST") poseOSC = 1;
    else if (pose=="FINGERS_SPREAD") poseOSC = 2;
    else if (pose=="WAVE_IN") poseOSC = 3;
    else if (pose=="WAVE_OUT") poseOSC = 4;
    else if (pose=="DOUBLE_TAP") poseOSC = 5;
    
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

    break;
 
  case ORIENTATION:
   OscMessage orient = new OscMessage("/orientation");
   OscMessage orientS = new OscMessage("/orientationS");

    // println("myoOn ORIENTATION");
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
     
    rollS = int(roll*255);
    pitchS = int(pitch*255);
    yawS = int(yaw*255);

    orient.add(yaw);
    orient.add(pitch);
    orient.add(roll);
    
    orientS.add(yawS);
    orientS.add(pitchS);
    orientS.add(rollS);
 
    oscP5.send(orient, myRemoteLocation);   
    oscP5.send(orientS, myRemoteLocation);

    break;
 
  case ACCELEROMETER:
    // println("myoOn ACCELEROMETER");
      PVector acceleration = myo.getAccelerometer();
//   println("acceleration" + acceleration.x + " " + acceleration.y + " " + acceleration.z);
      OscMessage acc = new OscMessage("/acc");
      OscMessage accS = new OscMessage("/accS");

    accSx= int(acceleration.x*40.58451048843329); // scale acceleration.x (0-2PI) -> serial value (0-255)
    accSy= int(acceleration.y*40.58451048843329); // scale acceleration.x (0-2PI) -> serial value (0-255)
    accSz= int(acceleration.z*40.58451048843329); // scale acceleration.x (0-2PI) -> serial value (0-255)
 
    acc.add(acceleration.x); //  0-2PI
    acc.add(acceleration.y); //  0-2PI
    acc.add(acceleration.z); //  0-2PI
 
    accS.add(accSx); // 0-255
    accS.add(accSy); // 0-255
    accS.add(accSz); // 0-255
        
   oscP5.send(acc, myRemoteLocation); 
   oscP5.send(accS, myRemoteLocation); 

    break;
 
  case GYROSCOPE:
    // println("myoOn GYROSCOPE");
      PVector gyro = myo.getGyroscope();
  //  println("acceleration" + acceleration.x + " " + acceleration.y + " " + acceleration.z);
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

    break;
 
  case RSSI:
    println("myoOn RSSI");
    break;
 
  case EMG:  
      float emgSum = 0;
      int emg[] = myo.getEmg(); // array of EMG data
     
 //     OscMessage Emg = new OscMessage("/emg0");
      OscMessage emgAvg = new OscMessage("/emgAvg");
      OscMessage Emg = new OscMessage("/emg");

      for(int i=0; i<8; i++){
      
        
      EMG[i]= map(abs(EMG[i]), 0., 128., emgMin, emgMax);
      
      emgSum = EMG[i] + emgSum; // EMG sum for avg calculation
      emg[i] = abs(emg[i]);  // add emg value to /emg0 message
      }
     
      intensity = abs(emgSum/8-reverseEmg); // average calculation
      emgAvg.add(intensity);
      Emg.add(emg);
    
 //     println("Intesity: "+intensity);

  //    oscP5.send(Emg, myRemoteLocation);
      oscP5.send(emgAvg, myRemoteLocation);
      oscP5.send(Emg, myRemoteLocation);

    break;
  }
}

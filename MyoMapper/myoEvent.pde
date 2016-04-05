
String connectionState, syncState;
PVector orientation, acceleration, gyro; 
int[] emg = new int[8];


void myoOn(Myo.Event event, Device myo, long timestamp) {
<<<<<<< HEAD

  switch(event) {
  case PAIR:
    println("Myo PAIR");
    break;
  case UNPAIR:
    println("Myo UNPAIR");
    break;
  case CONNECT:
    connectionState = "CONNECTED";
    break;
  case DISCONNECT:
    connectionState = "DISCONNECTED";
    break;
  case ARM_SYNC:
    syncState = "SYNC";
    println("Myo ARM_SYNC");
=======
>>>>>>> development

  switch(event) { 
    case PAIR:
      println("Myo PAIR");
    break;
      
    case UNPAIR:
      println("Myo UNPAIR");
      break;
      
    case CONNECT:
      connectionState = "CONNECTED";
      break;
      
    case DISCONNECT:
      connectionState = "DISCONNECTED";
      break;
      
    case ARM_SYNC:
      syncState = "SYNC";
      println("Myo ARM_SYNC");
      break;
      
    case ARM_UNSYNC:
      syncState = "UNSYNC";
      println("myoOn ARM_UNSYNC");
      break;
      
    case POSE:
     if(poseOnOff){
      pose = myo.getPose(); 
      convertPose();
     }
     break;
   
<<<<<<< HEAD
    pose = myo.getPose(); 
    convertPose();
    
    break;
 
  case ORIENTATION:
    orientation = myo.getOrientation();
    extractionOrientation();
    centerOrientation();
    reverseOrientation();
    scaleOrientation();
    break;
 
  case ACCELEROMETER:
    acceleration = myo.getAccelerometer();
    scaleAcceleration();
    break;
 
  case GYROSCOPE:
    gyro = myo.getGyroscope();
=======
    case ORIENTATION:
    if (orientOnOff){
      orientation = myo.getOrientation();
      }
    break;
   
    case ACCELEROMETER:
    if(accOnOff){
      acceleration = myo.getAccelerometer();
      }
    break;
   
    case GYROSCOPE:
      if(gyroOnOff)gyro = myo.getGyroscope();
>>>>>>> development
    break;
   
    case RSSI:
    break;
<<<<<<< HEAD
 
  case EMG: 
     emg = myo.getEmg(); 
 
=======
   
    case EMG:
     if(emgOnOff||mavOnOff) emg = myo.getEmg(); 
>>>>>>> development
    break;
    }
}

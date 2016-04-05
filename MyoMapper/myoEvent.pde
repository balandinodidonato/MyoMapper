
String connectionState, syncState;
PVector orientation, acceleration, gyro; 
int[] emg = new int[8];


void myoOn(Myo.Event event, Device myo, long timestamp) {

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
    break;
   
    case RSSI:
    break;
   
    case EMG:
     if(emgOnOff||mavOnOff) emg = myo.getEmg(); 
    break;
    }
}

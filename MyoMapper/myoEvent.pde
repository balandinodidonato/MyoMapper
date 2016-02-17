
String connectionState, syncState;
PVector orientation, acceleration, gyro; 

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
    break;
 
  case RSSI:
    break;
 
  case EMG: 
     emg = myo.getEmg(); 
 
    break;
  }
}

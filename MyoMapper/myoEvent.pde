
String connectionState, syncState;
PVector orientation, acceleration, gyro; 

void myoOn(Myo.Event event, Myo myo, long timestamp) {
  
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
    sendPose();
    break;
 
  case ORIENTATION:
    orientation = myo.getOrientation();
    extractionOrientation();
    centerOrientation();
    reverseOrientation();
    scaleOrientation();
    sendOrientation();
    break;
 
  case ACCELEROMETER:
    acceleration = myo.getAccelerometer();
    scaleAcceleration();
    sendAcceleration();
    break;
 
  case GYROSCOPE:
    gyro = myo.getGyroscope();
    sendGyro();
    break;
 
  case RSSI:
    break;
 
  case EMG: 
     emg = myo.getEmg(); 
     emgAvgSend();  
     emgSend();
     
    break;
  }
}

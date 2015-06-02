// ----------------------------------------------------------

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
    Pose.add(myo.getPose());
    oscP5.send(Pose, myRemoteLocation);
    break;
 
  case ORIENTATION:
    // println("myoOn ORIENTATION");
     PVector orientation = myo.getOrientation();
   //   println("orientation" + acceleration.x + " " + acceleration.y + " " + acceleration.z);
    OscMessage orient = new OscMessage("/orientation0");
   float orX=orientation.x;
    orient.add(orientation.x);
    orient.add(orientation.y);
    orient.add(orientation.z);
    oscP5.send(orient, myRemoteLocation);
    break;
 
  case ACCELEROMETER:
    // println("myoOn ACCELEROMETER");
      PVector acceleration = myo.getAccelerometer();
   //   println("acceleration" + acceleration.x + " " + acceleration.y + " " + acceleration.z);
       OscMessage accelerometer = new OscMessage("/acceleration0");
    accelerometer.add(acceleration.x);
    accelerometer.add(acceleration.y);
    accelerometer.add(acceleration.z);
    oscP5.send(accelerometer, myRemoteLocation);
    break;
 
  case GYROSCOPE:
    // println("myoOn GYROSCOPE");
      PVector gyro = myo.getGyroscope();
   //   println("acceleration" + acceleration.x + " " + acceleration.y + " " + acceleration.z);
       OscMessage gyroscope = new OscMessage("/gyro0");
    gyroscope.add(gyro.x);
    gyroscope.add(gyro.y);
    gyroscope.add(gyro.z);
    oscP5.send(gyroscope, myRemoteLocation);
    break;
 
  case RSSI:
    println("myoOn RSSI");
    break;
 
  case EMG:  
      OscMessage Emg = new OscMessage("/emg0");
      int emg[] = myo.getEmg();
      float emg1 = map(emg[0], -128, 127, 0, 1);
      float emg2 = map(emg[1], -128, 127, 0, 1);
      float emg3 = map(emg[2], -128, 127, 0, 1);
      float emg4 = map(emg[3], -128, 127, 0, 1);
      float emg5 = map(emg[4], -128, 127, 0, 1);
      float emg6 = map(emg[5], -128, 127, 0, 1);
      float emg7 = map(emg[6], -128, 127, 0, 1);
      float emg8 = map(emg[7], -128, 127, 0, 1);
      Emg.add(emg1);
      Emg.add(emg2);
      Emg.add(emg3);
      Emg.add(emg4);
      Emg.add(emg5);
      Emg.add(emg6);
      Emg.add(emg7);
      Emg.add(emg8);
      oscP5.send(Emg, myRemoteLocation);
    break;
  }
}

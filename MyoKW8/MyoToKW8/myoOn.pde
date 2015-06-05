int[] EMG = new int[8];

// ----------------------------------------------------------
int pan = 0;
int tilt = 0;
int intesity = 0;
float orY, ORy, ORY;
float orZ, ORz, ORZ;

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
//    OscMessage Pose = new OscMessage("/pose");
    pose = myo.getPose();
//    Pose.add(myo.getPose());
//    oscP5.send(Pose, myRemoteLocation);
    break;
 
  case ORIENTATION:
    // println("myoOn ORIENTATION");
     PVector orientation = myo.getOrientation();
 
   orY = orientation.y; // orientation.y (pitch) original value
   orZ = orientation.z; // orientation.z (yaw) original value
   
    ORY = orY-((ORy+0.5)-1);
    ORZ = orZ-((ORz+0.5)-1);
    
    OscMessage orient = new OscMessage("/orientation");
    pan = int(ORZ*255);
    pan = abs(pan-(pan*reversePan));
    
    tilt = int(ORY*255);
    tilt = abs(int(orientation.y*255)-reverseTilt);
    orient.add(pan);
    orient.add(tilt);
    oscP5.send(orient, myRemoteLocation);
//    println("PAN: "+pan);
//    println("TILT: "+tilt);
    break;
 
  case ACCELEROMETER:
    // println("myoOn ACCELEROMETER");
      PVector acceleration = myo.getAccelerometer();
//   println("acceleration" + acceleration.x + " " + acceleration.y + " " + acceleration.z);
/*      OscMessage accelerometer = new OscMessage("/acceleration0");
    accelerometer.add(acceleration.x);
    accelerometer.add(acceleration.y);
    accelerometer.add(acceleration.z);
   oscP5.send(accelerometer, myRemoteLocation); 
*/
    break;
 
  case GYROSCOPE:
    // println("myoOn GYROSCOPE");
      PVector gyro = myo.getGyroscope();
/*    println("acceleration" + acceleration.x + " " + acceleration.y + " " + acceleration.z);
    OscMessage gyroscope = new OscMessage("/gyro0");
    gyroscope.add(gyro.x);
    gyroscope.add(gyro.y);
    gyroscope.add(gyro.z);
    oscP5.send(gyroscope, myRemoteLocation); 
 */
    break;
 
  case RSSI:
    println("myoOn RSSI");
    break;
 
  case EMG:  
      int intensity = 0;
      int emgSum = 0;
      int emg[] = myo.getEmg(); // array of EMG data
     
 //     OscMessage Emg = new OscMessage("/emg0");
      OscMessage emgAvg = new OscMessage("/intesity");
      
      for(int i=0; i<8; i++){
      EMG[i]= abs(emg[i])+127; // rescale EMG data
      emgSum = EMG[i] + emgSum; // EMG sum for avg calculation
  //    Emg.add(EMG[i]);  // add emg value to /emg0 message
      }
     
      intensity = emgSum/8; // average calculation
      emgAvg.add(intensity);
    
 //     println("Intesity: "+intensity);

  //    oscP5.send(Emg, myRemoteLocation);
      oscP5.send(emgAvg, myRemoteLocation);

    break;
  }
}

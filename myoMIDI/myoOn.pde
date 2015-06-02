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
   
    break;
  case ARM_UNSYNC:
    println("myoOn ARM_UNSYNC");
    break;


  case POSE:
  //    println("myoOn POSE
  String pose= myo.getPose();

  if (pose == "FIST"){
        for(int i=21; i<28; i++){
         if (i ==21) myBus.sendControllerChange(1, i, 127);
         else myBus.sendControllerChange(1, i, 0);
      } }
    
  else if (pose == "WAVE_IN"){
        for(int i=21; i<28; i++){
         if (i ==22) myBus.sendControllerChange(1, i, 127);
         else myBus.sendControllerChange(1, i, 0);
      } }
   else if (pose == "WAVE_OUT"){
        for(int i=21; i<28; i++){
         if (i ==23) myBus.sendControllerChange(1, i, 127);
         else myBus.sendControllerChange(1, i, 0);
      } }
       else if (pose == "FINGERS_SPREAD"){
        for(int i=21; i<28; i++){
         if (i ==24) myBus.sendControllerChange(1, i, 127);
         else myBus.sendControllerChange(1, i, 0);
      } }
  else if (pose == "DOUBLE_TAP"){
       for(int i=21; i<28; i++){
        if (i ==25) myBus.sendControllerChange(1, i, 127);
        else myBus.sendControllerChange(1, i, 0);
      } }
  else if (pose == "REST"){
       for(int i=21; i<28; i++){
        if (i ==26) myBus.sendControllerChange(1, i, 127);
        else myBus.sendControllerChange(1, i, 0);
      } }

   else if (pose == "UNKNOWN"){
       for(int i=21; i<28; i++){
        if (i ==27) myBus.sendControllerChange(1, i, 127);
        else myBus.sendControllerChange(1, i, 0);
      } }
  break;

     
  case ORIENTATION:
    //myo.getPose()
  
    // println("myoOn ORIENTATION");
     PVector orientation = myo.getOrientation();
   //   println("orientation" + acceleration.x + " " + acceleration.y + " " + acceleration.z);
     

   int orX = (int) map(orientation.x, 0., 1., 0, 127);
   int orY = (int) map(orientation.y, 0., 1., 0, 127);
   int orZ = (int) map(orientation.z, 0., 1., 0, 127);



     myBus.sendControllerChange(1, 1, orX); // Send a controllerChange
     myBus.sendControllerChange(1, 2, orY); // Send a controllerChange
     myBus.sendControllerChange(1, 3, orZ); // Send a controllerChange

    break;
 
  case ACCELEROMETER:
    // println("myoOn ACCELEROMETER");
      PVector acceleration = myo.getAccelerometer();
   //   println("acceleration" + acceleration.x + " " + acceleration.y + " " + acceleration.z);
  

    int accX = (int) map(acceleration.x, 0., 6.28318, 0, 127);
    int accY = (int) map(acceleration.y, 0., 6.28318, 0, 127);
    int accZ = (int) map(acceleration.z, 0., 6.28318, 0, 127);

     myBus.sendControllerChange(1, 4, accX); // Send a controllerChange
     myBus.sendControllerChange(1, 5, accY); // Send a controllerChange
     myBus.sendControllerChange(1, 6, accZ); // Send a controllerChange
    break;
 
  case GYROSCOPE:
    // println("myoOn GYROSCOPE");
      PVector gyro = myo.getGyroscope();
   //   println("acceleration" + acceleration.x + " " + acceleration.y + " " + acceleration.z);
 
   int gyroX = (int) map(gyro.x, 0., 1000., 0, 127);
   int gyroY = (int) map(gyro.y, 0., 1000., 0, 127);
   int gyroZ = (int) map(gyro.z, 0., 1000., 0, 127);
     myBus.sendControllerChange(1, 7, gyroX); // Send a controllerChange
     myBus.sendControllerChange(1, 8, gyroY); // Send a controllerChange
     myBus.sendControllerChange(1, 9, gyroZ); // Send a controllerChange
    break;
 
  case RSSI:
//    println("myoOn RSSI");
    break;
 
  case EMG:
      int emg[] = myo.getEmg();
      int emg1 = abs(emg[0]);
      int emg2 = abs(emg[1]);
      int emg3 = abs(emg[2]);
      int emg4 = abs(emg[3]);
      int emg5 = abs(emg[4]);
      int emg6 = abs(emg[5]);
      int emg7 = abs(emg[6]);
      int emg8 = abs(emg[7]);
     myBus.sendControllerChange(1, 11, emg1); // Send a controllerChange
     myBus.sendControllerChange(1, 12, emg2); // Send a controllerChange
     myBus.sendControllerChange(1, 13, emg3); // Send a controllerChange
     myBus.sendControllerChange(1, 14, emg4); // Send a controllerChange
     myBus.sendControllerChange(1, 15, emg5); // Send a controllerChange
     myBus.sendControllerChange(1, 16, emg6); // Send a controllerChange
     myBus.sendControllerChange(1, 17, emg7); // Send a controllerChange
     myBus.sendControllerChange(1, 18, emg8); // Send a controllerChange

    break;
  }
}

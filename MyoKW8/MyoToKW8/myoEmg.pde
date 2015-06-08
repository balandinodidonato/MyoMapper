void myoOnEmg(Device myo, long timestamp, int[] data) {
  // println("Sketch: myoOnEmg");
  // int[] data <- 8 values from -128 to 1272
  

   
  synchronized (this){

   PVector orientation = myo.getOrientation();
   PVector acceleration = myo.getAccelerometer();
   PVector gyro = myo.getGyroscope();

   //   println("orientation" + acceleration.x + " " + acceleration.y + " " + acceleration.z);
   int[] imu = new int [9];
   imu[0] = (int) map(orientation.x, 0., 1., 0, 50);
   imu[1] = int(abs(ORY-reversePitch)*50);
   imu[2] = int(abs(ORZ-reverseYaw)*50);
   imu[3] = (int) map((acceleration.x/2)+3.141592653589793, 0., 6.28318, 0, 50);
   imu[4] = (int) map((acceleration.y/2)+3.141592653589793, 0., 6.28318, 0, 50);
   imu[5] = (int) map((acceleration.z/2)+3.141592653589793, 0., 6.28318, 0, 50);
   imu[6] = (int) map((gyro.x/2)+500, 0., 1000., 0, 50);
   imu[7] = (int) map((gyro.y/2)+500, 0., 1000., 0, 50);
   imu[8] = (int) map((gyro.z/2)+500, 0., 1000., 0, 50);
   
  for(int i=8; i<17; i++){
    sensors.get(i).add(imu[i-8]);}

    for(int i = 0; i<8; i++){
      sensors.get(i).add((int) map(data[i], -128, 127, 0, 50)); // [-128 - 127]
       
  }
   
    while(sensors.get(0).size() > width/2){

      for(ArrayList<Integer> sensor : sensors){

        sensor.remove(0);
      }
    }
  }
  
  
}

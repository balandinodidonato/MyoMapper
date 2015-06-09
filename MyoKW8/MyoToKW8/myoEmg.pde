void myoOnEmg(Device myo, long timestamp, int[] data) {
  // println("Sketch: myoOnEmg");
  // int[] data <- 8 values from -128 to 1272
  

   
  synchronized (this){

   PVector orientation = myo.getOrientation();
   PVector acceleration = myo.getAccelerometer();
   PVector gyro = myo.getGyroscope();

   //   println("orientation" + acceleration.x + " " + acceleration.y + " " + acceleration.z);
   int[] imu = new int [9];
   imu[0] = 50-int(yaw*0.19607843137255); // Original value 0-1
   imu[1] = 50-int(pitch*0.19607843137255); // Original value 0-1
   imu[2] = 50-int(roll*0.19607843137255); // Original value 0-1
   imu[3] = int(((acceleration.x/2)+PI)*7.9577471546); // Original value 0-2PI
   imu[4] = int(((acceleration.y/2)+PI)*7.9577471546); // Original value 0-2PI
   imu[5] = int(((acceleration.z/2)+PI)*7.9577471546); // Original value 0-2PI
   imu[6] = int(((gyro.x/2)+500)*0.05); // Original value 0-1000
   imu[7] = int(((gyro.y/2)+500)*0.05); // Original value 0-1000
   imu[8] = int(((gyro.z/2)+500)*0.05); // Original value 0-1000
   
  for(int i=8; i<17; i++){
    sensors.get(i).add(imu[i-8]);}

    for(int i = 0; i<8; i++){
      sensors.get(i).add(int((data[i]+128)*0.1960784314)); // [-128 - 127]
       
  }
   
    while(sensors.get(0).size() > width/2){

      for(ArrayList<Integer> sensor : sensors){

        sensor.remove(0);
      }
    }
  }
  
  
}

import de.voidplus.myo.*;

import oscP5.*;
import netP5.*;
  
OscP5 oscP5;
NetAddress myRemoteLocation;

Myo myo;
ArrayList<ArrayList<Integer>> sensors;

void setup() {
  size(1000, 900);
  background(255);
  noFill();
  stroke(0);
  // ...

  myo = new Myo(this);
  // myo.setVerbose(true);
  // myo.setVerboseLevel(4); // Default: 1 (1-4)
  
  myo.withEmg();
  // myo.withoutEmg();
  
  myo.setFrequency(15); // set frequency Data

  
  sensors = new ArrayList<ArrayList<Integer>>();
  for(int i=0; i<34; i++){
    sensors.add(new ArrayList<Integer>()); 
  }
  
  oscP5 = new OscP5(this,12000);
  myRemoteLocation = new NetAddress("127.0.0.1",5432);
}

void draw() {


  background(222,222,222);
   textSize(30);
   text("EMG 1", 10, 25);
   text("EMG 2", 10, 75);
   text("EMG 3", 10, 125);
   text("EMG 4", 10, 175);
   text("EMG 5", 10, 225);
   text("EMG 6", 10, 275);
   text("EMG 7", 10, 325);
   text("EMG 8", 10, 375);
   text("ROLL", 10, 425);
   text("PITCH", 10, 475);
   text("YAW", 10, 525);
   text("ACCELLERATION X", 10, 575);
   text("ACCELLERATION Y", 10, 625);
   text("ACCELLERATION Z", 10, 675);
   text("GYRO X", 10, 725);
   text("GYRO Y", 10, 775);
   text("GYRO Z", 10, 825);
   text("...", 10, 875);
   
 
  synchronized (this){
    for(int i=0; i<17; i++){
      if(!sensors.get(i).isEmpty()){
        beginShape();
        for(int j=0; j<sensors.get(i).size(); j++){
          vertex(j, sensors.get(i).get(j)+(i*50));
        }
        endShape();
      } 
    }
  } 
}

// ----------------------------------------------------------

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
   imu[1] = (int) map(orientation.y, 0., 1., 0, 50);
   imu[2] = (int) map(orientation.z, 0., 1., 0, 50);
   imu[3] = (int) map(acceleration.x, 0., 6.28318, 0, 50);
   imu[4] = (int) map(acceleration.y, 0., 6.28318, 0, 50);
   imu[5] = (int) map(acceleration.z, 0., 6.28318, 0, 50);
   imu[6] = (int) map(gyro.x, 0., 1000., 0, 50);
   imu[7] = (int) map(gyro.y, 0., 1000., 0, 50);
   imu[8] = (int) map(gyro.z, 0., 1000., 0, 50);
   
  for(int i=8; i<17; i++){
    sensors.get(i).add(imu[i-8]);}
    
    for(int i = 0; i<8; i++){
      sensors.get(i).add((int) map(data[i], -128, 127, 0, 50)); // [-128 - 127]
       
  }
   
    while(sensors.get(0).size() > width){
      for(ArrayList<Integer> sensor : sensors){
        sensor.remove(0);
      }
    }
  }
  
  
}

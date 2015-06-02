import themidibus.*;

import de.voidplus.myo.*;
import oscP5.*;
import netP5.*;

Myo myo;
MidiBus myBus; // The MidiBus

OscP5 oscP5;
NetAddress myRemoteLocation;



String p0 = " ";
String p1 = " ";
float pv0 = 0;
float pv1= 1;

int orX = 0;
int orY = 0;
int orZ = 0;

float yaw0 = 0;
float pitch0 = 0;
float roll0 = 0;

float yaw1 = 0;
float pitch1 = 0;
float roll1 = 0;

float accX0 = 0;
float accY0 = 0;
float accZ0 = 0;

int accX = 0;
int accY = 0;
int accZ = 0;

float accelerationX = 0;
float accelerationY = 0;
float accelerationZ = 0;


float accX1 = 0;
float accY1 = 0;
float accZ1 = 0;

float gyroX = 0;
float gyroY = 0;
float gyroZ = 0;

float gyroX0 = 0;
float gyroY0 = 0;
float gyroZ0 = 0;

int gyroXM = 0;
int gyroYM = 0;
int gyroZM = 0;


float gyroX1 = 0;
float gyroY1 = 0;
float gyroZ1 = 0;

void setup() {
  size(800, 500);
  background(255);
  // ...

  myo = new Myo(this);
  
   oscP5 = new OscP5(this,12000);
  myRemoteLocation = new NetAddress("127.0.0.1",5432);
  // myo.setVerbose(true);
  // myo.setVerboseLevel(4); // Default: 1 (1-4)
//   myo.withEmg();


   MidiBus.list(); // List all available Midi devices on STDOUT. This will show each device's index and name.

    //                 Parent  In        Out
  //                   |     |          |
  myBus = new MidiBus(this, 0, 1); // Create a new MidiBus with no input device and the default Java Sound Synthesizer as the output device.

}

void draw() {
 

  background(222, 222, 222);
  // ...
  textSize(35);
  fill(255,255,255);
  text("Myo Right", 400, 30);
  textSize(30);
  text("OSC (Open Sound Control)", 400, 90);

  textSize(25);
  text("Yaw: "+yaw0, 400, 120);
  text("Pith: "+pitch0, 400, 150);
  text("Roll: "+ roll0, 400, 180);
  
  text("Acceleration X: "+accX0, 400, 210);
  text("Acceleration Y: "+accY0, 400, 240);
  text("Acceleration Z: "+accZ0, 400, 270);

  text("Gyro X: "+gyroX0, 400, 300);
  text("Gyro Y: "+gyroY0, 400, 330);
  text("Gyro Z: "+gyroZ0, 400, 360);
  
  text("Pose: "+pv0+" "+p0, 400, 390);
  
  fill(0,0,0);
  textSize(35);
  text("Myo Left", 10, 30);
  textSize(30);
  text("OSC (Open Sound Control)", 10, 90);

  textSize(25);
  text("Yaw: "+yaw1, 10, 120);
  text("Pith: "+pitch1, 10, 150);
  text("Roll: "+ roll1, 10, 180);
  
  text("Acceleration X: "+accX1, 10, 210);
  text("Acceleration Y: "+accY1, 10, 240);
  text("Acceleration Z: "+accZ1, 10, 270);
  
  text("Gyro X: "+gyroX1, 10, 300);
  text("Gyro Y: "+gyroY1, 10, 330);
  text("Gyro Z: "+gyroZ1, 10, 360);
  
  text("Pose: "+pv1+" "+p1, 10, 390);

}

// ----------------------------------------------------------

// IMPORTANT: "Device" (not class "Myo") !!!        
void myoOnPair(Device myo, long timestamp, String firmware) {
  println("Sketch: myoOnPair & Device: "+myo.getId());
}

void myoOnUnpair(Device myo, long timestamp) {
  println("Sketch: myoOnUnpair & Device: "+myo.getId());
}

void myoOnConnect(Device myo, long timestamp, String firmware) {
  println("Sketch: myoOnConnect & Device: "+myo.getId());
}

void myoOnDisconnect(Device myo, long timestamp) {
  println("Sketch: myoOnDisconnect & Device: "+myo.getId());
}

void myoOnArmRecognized(Device myo, long timestamp, Arm arm) {
  println("Sketch: myoOnArmRecognized & Device: "+myo.getId());

  switch (arm.getType()) {
  case LEFT:
    println("Left arm.");
    break;
  case RIGHT:
    println("Right arm.");
    break;
  }

  if (myo.hasArm()) {
    if (myo.isArmLeft()) {
      println("Left arm.");
    } else {
      println("Right arm.");
    }
  }
}

void myoOnLock(Device myo, long timestamp){
  println("Sketch: myoOnLock & Device: "+myo.getId());
}
  
void myoOnUnLock(Device myo, long timestamp){
  println("Sketch: myoOnUnLock & Device: "+myo.getId());
}

void myoOnArmUnsync(Device myo, long timestamp) {
  println("Sketch: myoOnArmUnsync & Device: "+myo.getId());
}
  
void myoOnPose(Device myo, long timestamp, Pose pose) {
  
  OscMessage pos = new OscMessage("/pose"+myo.getId());
  
  switch (pose.getType()) {
  case REST:
    pos.add(0);
    if(myo.getId()==0){
      pv0=0;
      p0="(REST)";} 
    else 
      {pv1=0; 
       p1="(REST)";}    break;
  case FIST:
    pos.add(0.2);
    if(myo.getId()==0){
      pv0=0.2;
      p0="(FIST)";} 
    else 
      {pv1=0.2; 
       p1="(FIST)";}    break;
  case FINGERS_SPREAD:
    pos.add(0.4);
    if(myo.getId()==0){
      pv0=0.4;
      p0="(FINGERS_SPREAD)";} 
    else 
      {pv1=0.4; 
       p1="(FINGERS_SPREAD)";}
       break;
  case DOUBLE_TAP:
    pos.add(0.6);
    
    if(myo.getId()==0){
      pv0=0.6;
      p0="(DOUBLE_TAP)";}
    else 
      {pv1=0.6; 
       p1="(DOUBLE_TAP)";}
    break;
  case WAVE_IN:
    pos.add(0.8);
    if(myo.getId()==0){
      pv0=0.8;
      p0="(WAVE_IN)";} 
    else 
      {pv1=0.8; 
       p1="(WAVE_IN)";}
       break;
  case WAVE_OUT:
    pos.add(1);
    if(myo.getId()==0){
      pv0=1;
      p0="(WAVE_OUT)";} 
    else 
      {pv1=1; 
       p1="(WAVE_OUT)";}
    break;
  default:
    break;
  }
 oscP5.send(pos, myRemoteLocation);

} 


void myoOnOrientation(Device myo, long timestamp, PVector orientation) {
   //   println("orientation" + acceleration.x + " " + acceleration.y + " " + acceleration.z);
     
    OscMessage orient = new OscMessage("/orientation"+myo.getId());
    orient.add(orientation.x);
    orient.add(orientation.y);
    orient.add(orientation.z);
    oscP5.send(orient, myRemoteLocation);
    
   orX = (int) map(orientation.x, 0., 1, 0, 127);
   orY = (int) map(orientation.y, 0., 1, 0, 127);
   orZ = (int) map(orientation.z, 0., 1, 0, 127);
    
     myBus.sendControllerChange(myo.getId(), 1, orX); // Send a controllerChange
     myBus.sendControllerChange(myo.getId(), 2, orY); // Send a controllerChange
     myBus.sendControllerChange(myo.getId(), 3, orZ); // Send a controllerChange
    
     if(myo.getId()==0)
      {roll0 = orientation.x;
      pitch0 = orientation.y;
      yaw0 = orientation.z;}
    else 
      {roll1 = orientation.x;
      pitch1 = orientation.y;
      yaw1 = orientation.z;}
}

void myoOnAccelerometer(Device myo, long timestamp, PVector accelerometer) {
    OscMessage acc = new OscMessage("/acceleration"+myo.getId());
 
   accelerationX = map(accelerometer.x, -4, +4, 0, 1);
   accelerationY = map(accelerometer.y, -4, +4, 0, 1);
   accelerationZ = map(accelerometer.z, -4, +4, 0, 1);  
   
     accX = (int) map(accelerometer.x, 0., 1, 0, 127);
     accY = (int) map(accelerometer.y, 0., 1, 0, 127);
     accZ = (int) map(accelerometer.z, 0., 1, 0, 127);

     myBus.sendControllerChange(myo.getId(), 4, accX); // Send a controllerChange
     myBus.sendControllerChange(myo.getId(), 5, accY); // Send a controllerChange
     myBus.sendControllerChange(myo.getId(), 6, accZ); // Send a controllerChange
   
   
    acc.add(accelerationX);
    acc.add(accelerationY);
    acc.add(accelerationZ);
    oscP5.send(acc, myRemoteLocation);
    
     if(myo.getId()==0)
      {accX0 = accelerationX;
      accY0 = accelerationY;
      accZ0 = accelerationZ;}
    else 
      {accX1 = accelerationX;
      accY1 = accelerationY;
      accZ1 = accelerationZ;}
}

void myoOnGyroscope(Device myo, long timestamp, PVector gyroscope) {
    OscMessage gyro = new OscMessage("/gyro"+myo.getId());
   
   gyroX = map(gyroscope.x, -1000, +1000, 0, 1);
   gyroY = map(gyroscope.y, -1000, +1000, 0, 1);
   gyroZ = map(gyroscope.z, -1000, +1000, 0, 1);

   gyroXM = (int) map(gyroX, 0., 1, 0, 127);
   gyroYM = (int) map(gyroX, 0., 1, 0, 127);
   gyroZM = (int) map(gyroX, 0., 1, 0, 127);
   
     myBus.sendControllerChange(myo.getId(), 7, gyroXM); // Send a controllerChange
     myBus.sendControllerChange(myo.getId(), 8, gyroYM); // Send a controllerChange
     myBus.sendControllerChange(myo.getId(), 9, gyroZM); // Send a controllerChange
   
    gyro.add(gyroX);
    gyro.add(gyroY);
    gyro.add(gyroZ);
    oscP5.send(gyro, myRemoteLocation);
    
         if(myo.getId()==0)
      {gyroX0 = gyroX;
      gyroY0 = gyroY;
      gyroZ0 = gyroZ;}
    else 
      {gyroX1 = gyroX;
      gyroY1 = gyroY;
      gyroZ1 = gyroZ;}
}

void myoOnRssi(Device myo, long timestamp, int rssi) {
  // println("Sketch: myoOnRssi & Device: "+myo.getId());
}

// ----------------------------------------------------------

void myoOn(Myo.Event event, Myo myo, long timestamp) {
  // println("Sketch: myoOn & Device: "+myo.getId());
  
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
    println("myoOn POSE");  
    break;
  case ORIENTATION:
    // println("myoOn ORIENTATION");
    break;
  case ACCELEROMETER:
    // println("myoOn ACCELEROMETER");
    break;
  case GYROSCOPE:
    // println("myoOn GYROSCOPE");
    break;
  case RSSI:
    println("myoOn RSSI");
    break;
  
  } 

}


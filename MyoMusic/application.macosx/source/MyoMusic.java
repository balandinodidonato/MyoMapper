import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import controlP5.*; 
import themidibus.*; 
import de.voidplus.myo.*; 
import oscP5.*; 
import netP5.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class MyoMusic extends PApplet {


ControlP5 cp5;

public void setup() {
   cp5 = new ControlP5(this);

  size(1000, 850); //window size
  logoSetup();
  myoSetup(); 
  toggles();
  setUpMIDI();  
  bangs();
  oscSetup(); 
  rescale();
  setupSliders();  
} 

public void draw() {
  background(0); //background color
  logoRun();
  updateSliders();
  labels();
  emgGraphs();
}
 //Import the library

MidiBus myBus; // The MidiBus

boolean MIDI = false;

int portMIDI = 1;
int chMIDI = 1;

public void setUpMIDI(){
myBus.list();
myBus = new MidiBus(this, 2, portMIDI);
}
Slider yawSlider;
Slider pitchSlider;
Slider rollSlider;
Slider emgSlider;

public void setupSliders(){
 // cp5 = new ControlP5(this);

  yawSlider = cp5.addSlider("yawSlider")
              .setPosition(sYawX, sYawY)
              .setSize(sYawXsize,sYawYsize)
              .setRange(0,1)
              .setSliderMode(Slider.FLEXIBLE)
              ;

  pitchSlider = cp5.addSlider("pitchSlider")
     .setPosition(sPitchX, sPitchY)
     .setSize(sPitchXsize,sPitchYsize)
     .setRange(0,1)
     .setSliderMode(Slider.FLEXIBLE)

     ;
     
  rollSlider = cp5.addSlider("rollSlider")
     .setPosition(sRollX, sRollY)
     .setSize(sRollXsize,sRollYsize)
     .setRange(0,1)
     .setSliderMode(Slider.FLEXIBLE)

     ;     

  emgSlider = cp5.addSlider("emgSlider")
     .setPosition(sEmgX, sEmgY)
     .setSize(sEmgXsize,sEmgYsize)
     .setRange(0,1)
      .setSliderMode(Slider.FLEXIBLE)

     ; 
 
}

public void updateSliders(){

  yawSlider.setValue(yaw);
  pitchSlider.setValue(pitch);
  rollSlider.setValue(roll);
  emgSlider.setValue(intensity);
  
}

int bangSize;

int bngYawX, bngPitchX, bngRollX;
int bngYawY, bngPitchY, bngRollY;

public void bangs(){
      
    cp5 = new ControlP5(this);

    bangSize = tglXsize;
    
    bngYawY = bngPitchY = bngRollY = bngYawX = tglYawY+tglXsize;
    
    bngYawX = tglYawX;
    bngPitchX = tglPitchX;
    bngRollX = tglRollX;
    
    cp5.addBang("Cent. YAW")
       .setPosition(bngYawX, bngYawY)
       .setSize(bangSize, bangSize)
       .setId(0)
       ;
    cp5.addBang("Cent. PITCH")
       .setPosition(bngPitchX, bngPitchY)
       .setSize(bangSize, bangSize)
       .setId(1)
       ; 
    cp5.addBang("Cent. ROLL")
       .setPosition(bngRollX, bngRollY)
       .setSize(bangSize, bangSize)
       .setId(2)
       ;       
}

public void controlEvent(ControlEvent theEvent) {

  if (theEvent.controller().id() == 2) ORx=orX;
  else if (theEvent.controller().id() == 1) ORy=orY;
  else if (theEvent.controller().id() == 0) ORz=orZ;
}
public void labels(){
   noStroke();

   textSize(width/24.285714286f);
   fill(0xff1D4383);
  text("MyoMusic", width/2+width/8,height/18);

   fill(0xff1D4383);
   
   
   
      int pippo = 30;
      int labeX = width/150;
      int labelXFactor = PApplet.parseInt(height/17.6f);
      int marginY = PApplet.parseInt(height/17.2f);
      int[] labelY = new int[17];
      
      for(int i=0; i<17; i++){
      labelY[i]= marginY+(labelXFactor*i);
      }
      
      int labelTextSize = PApplet.parseInt(width/33);
   
   textSize(labelTextSize);
   text("EMG 1", labeX, labelY[0]);
   text("EMG 2", labeX, labelY[1]);
   text("EMG 3", labeX, labelY[2]);
   text("EMG 4", labeX, labelY[3]);
   text("EMG 5", labeX, labelY[4]);
   text("EMG 6", labeX, labelY[5]);
   text("EMG 7", labeX, labelY[6]);
   text("EMG 8", labeX, labelY[7]);
   text("YAW", labeX, labelY[8]);
   text("PITCH", labeX, labelY[9]);
   text("ROLL", labeX, labelY[10]);
   text("ACC X", labeX, labelY[11]);
   text("ACC Y", labeX, labelY[12]);
   text("ACC Z", labeX, labelY[13]);
   text("GYR X", labeX, labelY[14]);
   text("GYR Y", labeX, labelY[15]);
   text("GYR Z", labeX, labelY[16]);
   
   text("POSE: "+pose, rEmgX,rEmgY+rEmgYsize*2); 
   text("STATE: "+connectionState+" - "+syncState, rEmgX,rEmgY+rEmgYsize*3); 

   fill(0xff1D4383);
   textSize(width/56.666666667f);
   text("Balandino Di Donato - 2015", width-cons.width/1.3f,height-height/30); 
   text("www.balandinodidonato.com", width-cons.width/1.3f,height-height/100);
   
   noFill();  
}
PImage integralogo;
PImage cons;

public void logoSetup(){
   integralogo = loadImage("blue-integra.png"); //
  cons = loadImage("cons.png"); //
  int resizeConsFactor = PApplet.parseInt(width/154.54545455f);
  cons.resize(PApplet.parseInt(cons.width/resizeConsFactor),PApplet.parseInt(cons.height/resizeConsFactor));
  integralogo.resize(PApplet.parseInt(integralogo.width/3.5f),PApplet.parseInt(integralogo.height/3.5f));


  for (int i = 0;i<cons.width;i++) {// pour image d'origine allant de 0 \u00e0 la fin de la fenetre ( abscisse)
    for (int j = 0; j<cons.height;j++) {//......................................................(ordonn\u00e9e)
      //int r =(int) red(cons.get(i, j)); //definit les sous pixels rouges des pixels sur la longueur de l'image d'origine
      int r =(int)blue(cons.get(i, j)); //.......................bleu...................................................
      int b =(int)blue(cons.get(i, j)); //.......................bleu...................................................
      int g =(int)green(cons.get(i, j)); //......................vert..................................................
      cons.set(i, j, color(110-r, 110-g, 160-g));
    }
  }
  
}

public void logoRun(){
  
   image(integralogo, width/2+width/110, height-integralogo.height); // display integra logo
   image(cons, width-cons.width, height-integralogo.height); // display integra logo

}

Myo myo;

ArrayList<ArrayList<Integer>> sensors;

public void myoSetup(){

  myo = new Myo(this);
  myo.withEmg();
  myo.setFrequency(20); // set frequency Data
  
  sensors = new ArrayList<ArrayList<Integer>>();
  for(int i=0; i<34; i++){
    sensors.add(new ArrayList<Integer>()); 
  }
}
int accSx, accSy, accSz = 0;
int accXMIDI, accYMIDI, accZMIDI; //cc4, cc5, cc6

public void scaleAcceleration(){
    accSx= PApplet.parseInt(acceleration.x*40.58451048843329f); // scale acceleration.x (0-2PI) -> serial value (0-255)
    accSy= PApplet.parseInt(acceleration.y*40.58451048843329f); // scale acceleration.x (0-2PI) -> serial value (0-255)
    accSz= PApplet.parseInt(acceleration.z*40.58451048843329f); // scale acceleration.x (0-2PI) -> serial value (0-255)
}



public void sendAcceleration(){
  
if(MIDI){   
     accXMIDI = PApplet.parseInt(acceleration.x/(2*PI)*127);
     accYMIDI = PApplet.parseInt(acceleration.y/(2*PI)*127);
     accZMIDI = PApplet.parseInt(acceleration.z/(2*PI)*127);
     
     myBus.sendControllerChange(chMIDI, 4, rollMIDI); // Send a Midi noteOn
     myBus.sendControllerChange(chMIDI, 5, pitchMIDI); // Send a Midi noteOn
     myBus.sendControllerChange(chMIDI, 6, yawMIDI); // Send a Midi noteOn
    }
    
if(OpenSoundControl){  
    OscMessage acc = new OscMessage("/acc");
    OscMessage accS = new OscMessage("/accS");
   
    acc.add(acceleration.x); //  0-2PI
    acc.add(acceleration.y); //  0-2PI
    acc.add(acceleration.z); //  0-2PI
 
    accS.add(accSx); // 0-255
    accS.add(accSy); // 0-255
    accS.add(accSz); // 0-255
        
   oscP5.send(acc, myRemoteLocation); 
   oscP5.send(accS, myRemoteLocation); 
}
}

int emg[];

float[] EMG = new float[8];
float emgMin  = 0;
float emgMax = 1;


int intensityMIDI; //cc10
int[] emgMIDI = new int[8]; //cc11, cc12, cc13, cc14, cc15, cc16, cc17, cc18
float intensity = 0;
int intensityS = 0;


public void myoOnEmg(Device myo, long timestamp, int[] data) {
  // println("Sketch: myoOnEmg");
  // int[] data <- 8 values from -128 to 1272
   
  synchronized (this){

   PVector orientation = myo.getOrientation();
   PVector acceleration = myo.getAccelerometer();
   PVector gyro = myo.getGyroscope();

   //   println("orientation" + acceleration.x + " " + acceleration.y + " " + acceleration.z);
   int[] imu = new int [9];
   imu[0] = 50-PApplet.parseInt(yaw*49); // Original value 0-1
   imu[1] = 50-PApplet.parseInt(pitch*49); // Original value 0-1
   imu[2] = 50-PApplet.parseInt(roll*49); // Original value 0-1
   imu[3] = PApplet.parseInt(((acceleration.x/2)+PI)*7.79859221150287f); // Original value 0-2PI
   imu[4] = PApplet.parseInt(((acceleration.y/2)+PI)*7.79859221150287f); // Original value 0-2PI
   imu[5] = PApplet.parseInt(((acceleration.z/2)+PI)*7.79859221150287f); // Original value 0-2PI
   imu[6] = PApplet.parseInt(((gyro.x/2)+500)*0.049f); // Original value 0-1000
   imu[7] = PApplet.parseInt(((gyro.y/2)+500)*0.049f); // Original value 0-1000
   imu[8] = PApplet.parseInt(((gyro.z/2)+500)*0.049f); // Original value 0-1000
   
  for(int i=8; i<17; i++){
    sensors.get(i).add(imu[i-8]);}

  for(int i=0; i<8; i++){
    sensors.get(i).add(PApplet.parseInt(abs(emg[i])*(-0.3125f)+49));

   //for(int i = 0; i<8; i++){
     // sensors.get(i).add(int((data[i]+128)*0.1960784314)); // [-128 - 127]
  }
   
    while(sensors.get(0).size() > width/2){

      for(ArrayList<Integer> sensor : sensors){

        sensor.remove(0);
      }
    }
  } 
}
  
public void emgGraphs(){
  
   noFill();
   stroke(255);

   synchronized (this){
    for(int i=0; i<17; i++){
      if(!sensors.get(i).isEmpty()){
        beginShape();
        for(int j=100; j<sensors.get(i).size(); j++){
          vertex(j, sensors.get(i).get(j)+(i*49));
        }
        endShape();
      } 
    }
  }
  
}


public void emgAvgSend(){
      float emgSum = 0;

    for(int i=0; i<8; i++){
     emg[i] = abs(emg[i]);

        // add emg value to /emg0 message
      EMG[i] = abs(reverseEmg-emg[i]);
      EMG[i] = map(EMG[i], 0, 128, emgMin, emgMax);
      emgSum = EMG[i]+emgSum; // EMG sum for avg calculation    
   
      if (MIDI){
        emgMIDI[i] = PApplet.parseInt(EMG[i]*127);
        myBus.sendControllerChange(chMIDI, 11+i, emgMIDI[i]);}
  }
     
      intensity = emgSum/8; // average calculation
      intensity = max(intensity, 0);
      intensity = min(intensity, 1); 
}

public void emgSend(){
if (MIDI) {
      intensityMIDI = PApplet.parseInt(intensity*127);
      myBus.sendControllerChange(chMIDI, 10, intensityMIDI); // Send a 
      }
     
   if(OpenSoundControl){  
    
     OscMessage Emg = new OscMessage("/emg");
     OscMessage emgAvg = new OscMessage("/emgAvg");   
     OscMessage emgAvgS = new OscMessage("/emgAvgs");  
     
      intensityS = PApplet.parseInt(intensity*255);
     
      Emg.add(emg);
      emgAvg.add(intensity);
      emgAvgS.add(intensityS);
      
      oscP5.send(Emg, myRemoteLocation);
      oscP5.send(emgAvg, myRemoteLocation);
      oscP5.send(emgAvgS, myRemoteLocation);
   }
}

String connectionState, syncState;
PVector orientation, acceleration, gyro; 

public void myoOn(Myo.Event event, Device myo, long timestamp) {
  
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
int gyroXMIDI, gyroYMIDI, gyroZMIDI; //cc7, cc8, cc9
int gyroSx, gyroSy, gyroSz = 0;


public void sendGyro(){
  if(MIDI){   
     gyroXMIDI = PApplet.parseInt(gyro.x*0.127f);
     gyroYMIDI = PApplet.parseInt(gyro.y*0.127f);
     gyroYMIDI = PApplet.parseInt(gyro.z*0.127f);
     
     myBus.sendControllerChange(chMIDI, 7, rollMIDI); // Send a Midi noteOn
     myBus.sendControllerChange(chMIDI, 8, pitchMIDI); // Send a Midi noteOn
     myBus.sendControllerChange(chMIDI, 9, yawMIDI); // Send a Midi noteOn
    }

if(OpenSoundControl){
  // Scale Midi Myo Value in serial Value
    gyroSx = PApplet.parseInt(gyro.x*0.255f);
    gyroSy = PApplet.parseInt(gyro.y*0.255f);
    gyroSz = PApplet.parseInt(gyro.z*0.255f);

    OscMessage Gyro = new OscMessage("/gyro");
    OscMessage gyroS = new OscMessage("/gyroS");
   
    Gyro.add(gyro.x);
    Gyro.add(gyro.y);
    Gyro.add(gyro.z);
    
    gyroS.add(gyroSx);
    gyroS.add(gyroSy);
    gyroS.add(gyroSz);
    
    oscP5.send(Gyro, myRemoteLocation); 
    oscP5.send(gyroS, myRemoteLocation); 
 }
}
float yMin, yMax = 0;
float pMin, pMax = 0;
float rMin, rMax = 0;

float orX, ORx, ORX = 0;
float orY, ORy, ORY = 0;
float orZ, ORz, ORZ = 0;

float yaw, pitch, roll;
int yawS, pitchS, rollS;

int yawMIDI, pitchMIDI, rollMIDI; //cc1, cc2, cc3



public void extractionOrientation(){
  
    orX = orientation.x; // orientation.y (roll) original value
    orY = orientation.y; // orientation.y (pitch) original value
    orZ = orientation.z; // orientation.z (yaw) original value
  
}

//this function CENTER the orientation Myo Data
public void centerOrientation (){
    ORZ = ORz-(orZ-0.5f); // centering YAW
    ORY = ORy-(orY-0.5f); // centering PITCH
    ORX = ORx-(orX-0.5f); // centering ROLL

    if(ORZ<0) {ORZ = 1+ORZ;}
    else if (ORZ>1) {ORZ = 1-ORZ;}
    else  {ORZ = ORZ;}
    
    if(ORY<0) {ORY = 1+ORY;}
    else if (ORY>1) {ORY = 1-ORY;}
    else  {ORY = ORY;}
    
    if(ORX<0) {ORX = 1+ORX;}
    else if (ORX>1) {ORX = 1-ORX;}
    else  {ORX = ORX;}  
}



//this function REVERSE the orientation Myo Data
public void reverseOrientation(){
 roll = abs(ORX-reverseRoll); // reverse + scale
 pitch = abs(ORY-reversePitch); // reverse + scale
 yaw = abs(ORZ-reverseYaw); // reverse + scale 
}

//this function RESCALE the orientation Myo Data
public void scaleOrientation(){
  
  yMin = rYaw.getLowValue();
  yMax = rYaw.getHighValue();

  pMin = rPitch.getLowValue();
  pMax = rPitch.getHighValue();
  
  rMin = rRoll.getLowValue();
  rMax = rRoll.getHighValue();

  emgMin = avgEMG.getLowValue();
  emgMax = avgEMG.getHighValue();
  
  roll = map(roll, 0, 1, rMin, rMax);
  pitch = map(pitch, 0, 1, pMin, pMax);
  yaw = map(yaw, 0, 1, yMin, yMax);
    
   roll = max(roll, 0);
   roll = min(roll, 1);     
   pitch = max(pitch, 0);
   pitch = min(pitch, 1);
   yaw = max(yaw, 0);
   yaw = min(yaw, 1);
}

public void sendOrientation(){

if(MIDI){
     rollMIDI = PApplet.parseInt(roll*127);
     pitchMIDI = PApplet.parseInt(pitch*127);
     yawMIDI = PApplet.parseInt(yaw*127);
  
     myBus.sendControllerChange(chMIDI, 1, yawMIDI); // Send a Midi noteOn
     myBus.sendControllerChange(chMIDI, 2, pitchMIDI); // Send a Midi noteOn
     myBus.sendControllerChange(chMIDI, 3, rollMIDI); // Send a Midi noteOn
     }
     
 if(OpenSoundControl){ 
    rollS = PApplet.parseInt(roll*255);
    pitchS = PApplet.parseInt(pitch*255);
    yawS = PApplet.parseInt(yaw*255);
    
    OscMessage orient = new OscMessage("/orientation");
    OscMessage orientS = new OscMessage("/orientationS");
   
    orient.add(yaw);
    orient.add(pitch);
    orient.add(roll);
    
    orientS.add(yawS);
    orientS.add(pitchS);
    orientS.add(rollS);
 
    oscP5.send(orient, myRemoteLocation);   
    oscP5.send(orientS, myRemoteLocation);
 }

}

int poseInt, poseS, poseMIDI= 0;
String pose;

public void convertPose(){
   if ((pose=="REST")||(pose=="UNCKNOWN")) poseInt = 0;
    else if (pose=="FIST") poseInt = 1;
    else if (pose=="FINGERS_SPREAD") poseInt = 2;
    else if (pose=="WAVE_IN") poseInt = 3;
    else if (pose=="WAVE_OUT") poseInt = 4;
    else if (pose=="DOUBLE_TAP") poseInt = 5;
}

public void sendPose(){
  
   if(MIDI){
   poseMIDI = PApplet.parseInt(poseInt*25.4f); 
   myBus.sendControllerChange(chMIDI, 20, poseMIDI);
   /*cc20 send pose messages
     v0 = UNCKNOWN
     v25 = FIST
     v50 = FINGERS_SPREAD
     v76 = WAVE_IN
     v101 = WAVE_OUT
     127 = DOUBLE_TAP
   */
   }  
   
   if(OpenSoundControl){ 
    OscMessage Pose = new OscMessage("/pose");
    
    poseS = poseInt*51; // scale poseI values into serial values
    // 0 = rest and uncknown
    // 51 = FIST
    // 102 = FINGERS_SPREAD
    // 153 = WAVE_IN
    // 204 = WAVE_OUT
    // 255 = DOUBLE_TAP
    
    Pose.add(pose);
    Pose.add(poseInt);
    Pose.add(poseS);

    oscP5.send(Pose, myRemoteLocation);
 }
}

  // osc


OscP5 oscP5;
NetAddress myRemoteLocation;

boolean OpenSoundControl = true;

public void oscSetup(){
  
   // OSC settings
  oscP5 = new OscP5(this,12000);
  myRemoteLocation = new NetAddress("127.0.0.1",5432); // IP address and Port

}
Range rYaw;
Range rPitch;
Range rRoll;
Range avgEMG;

int sYawX, sPitchX, sRollX, sEmgX;
int sYawXsize, sPitchXsize, sRollXsize, sEmgXsize;
int sYawY, sPitchY, sRollY, sEmgY;
int sYawYsize, sPitchYsize, sRollYsize, sEmgYsize;

int rYawX, rPitchX, rRollX, rEmgX;
int rYawXsize, rPitchXsize, rRollXsize, rEmgXsize;
int rYawY, rPitchY, rRollY, rEmgY;
int rYawYsize, rPitchYsize, rRollYsize, rEmgYsize;

public void rescale() {
  
  rYawXsize = rPitchXsize = rRollXsize = rEmgXsize = sYawXsize = sPitchXsize = sRollXsize = sEmgXsize = width/3; // X size sliders
  rYawYsize = rPitchYsize = rRollYsize = rEmgYsize = sYawYsize = sPitchYsize = sRollYsize = sEmgYsize = height/25;  // Y Size
  sYawX = sPitchX = sRollX = sEmgX = rYawX = rPitchX = rRollX = rEmgX = width/2+20; // x margins
  
  sYawY = height/3;
  sPitchY = sYawY+(sYawYsize*3);
  sRollY = sYawY+(sYawYsize*6);
  sEmgY = sYawY+(sYawYsize*9);
  
  rYawY = sYawY+sYawYsize;
  rPitchY = sPitchY+rYawYsize;
  rRollY = sRollY+rYawYsize;
  rEmgY = sEmgY+rEmgYsize;


  // cp5 = new ControlP5(this);

  rYaw = cp5.addRange("Range Yaw")
             // disable broadcasting since setRange and setRangeValues will trigger an event
             .setBroadcast(false) 
             .setPosition(rYawX, rYawY)
             .setSize(rYawXsize, rYawYsize)
             .setHandleSize(20)
             .setRange(-2,2)
             .setRangeValues(0,2)
             // after the initialization we turn broadcast back on again
             .setBroadcast(true)
             .setColorForeground(color(255,40))
             .setColorBackground(color(255,40)) 
             .setHighValue(1)
             .setLowValue(0)
             ;
 
   rPitch = cp5.addRange("Range Pitch")
             // disable broadcasting since setRange and setRangeValues will trigger an event
             .setBroadcast(false) 
             .setPosition(rPitchX, rPitchY)
             .setSize(rPitchXsize,rPitchYsize)
             .setHandleSize(20)
             .setRange(-2,2)
             .setRangeValues(0,2)
             // after the initialization we turn broadcast back on again
             .setBroadcast(true)
             .setColorForeground(color(255,40))
             .setColorBackground(color(255,40))  
             .setHighValue(1)
             .setLowValue(0)
             ;
             
    rRoll = cp5.addRange("Range Roll")
             // disable broadcasting since setRange and setRangeValues will trigger an event
             .setBroadcast(false) 
             .setPosition(rRollX, rRollY)
             .setSize(rRollXsize,rRollYsize)
             .setHandleSize(20)
             .setRange(-2,2)
             .setRangeValues(-2,2)
             // after the initialization we turn broadcast back on again
             .setBroadcast(true)
             .setColorForeground(color(255,40))
             .setColorBackground(color(255,40))  
             .setHighValue(1)
             .setLowValue(0)
             ; 
    
        avgEMG = cp5.addRange("Range EMG")
             // disable broadcasting since setRange and setRangeValues will trigger an event
             .setBroadcast(false) 
             .setPosition(rEmgX, rEmgY)
             .setSize(rEmgXsize, rEmgYsize)
             .setHandleSize(20)
             .setRange(0,4)
             .setRangeValues(0,2)
             // after the initialization we turn broadcast back on again
             .setBroadcast(true)
             .setColorForeground(color(255,40))
             .setColorBackground(color(255,40))  
             .setHighValue(1)
             .setLowValue(0)
             ;  
                  
  noStroke();  
}
Toggle revYawTgl;
Toggle revPitchTgl;
Toggle revRollTgl;
Toggle revEmgTgl;
Toggle OSCTgl;
Toggle MIDITgl;
Numberbox MIDIPortNb;
Numberbox MIDIchannelNb;

int tglXsize = 60;
int tglYsize = 30;

int tglYawY, tglPitchY, tglRollY, tglEmgY;
int tglYawX, tglPitchX, tglRollX, tglEmgX;

int revYawTglX, revYawTglY, tglOSCY, tglMIDIY, nbMIDIportY = 0; // Reverse Yaw tgl
int revPitchTglX = 0; // Pitch tgl
int revRollTglX = 0; // Pitch tgl
int revEmgTglX = 0; // Pitch tgl
int tglMIDIX, tglOSCX, nbMIDIportX, nbMIDIchX, nbMIDIchY = 0;
float reverseYaw, reversePitch, reverseRoll, reverseEmg = 0;

public void toggles(){
  
    
 tglYawX = width/2+40;  
 
 tglOSCY = tglMIDIY = nbMIDIportY = nbMIDIchY = height/11;
 tglYawY = tglPitchY = tglRollY = tglEmgY = PApplet.parseInt(height/6.5f);

  tglPitchX = tglYawX + tglXsize*2;
  tglRollX = tglPitchX + tglXsize*2;
  tglEmgX = tglRollX + tglXsize*2;
  tglOSCX = tglYawX;
  tglMIDIX = tglPitchX;
  nbMIDIportX = tglRollX;
  nbMIDIchX = tglEmgX;
  
   // create a toggle and change the default look to a (on/off) switch look
 revYawTgl = cp5.addToggle("revYaw")
     .setPosition(tglYawX,tglYawY)
     .setSize(tglXsize,tglYsize)
     .setValue(true)
     .setMode(ControlP5.SWITCH)
     ;

 revPitchTgl = cp5.addToggle("revPitch")
     .setPosition(tglPitchX,tglPitchY)
     .setSize(tglXsize,tglYsize)
     .setValue(true)
     .setMode(ControlP5.SWITCH)
     ;
     
 revRollTgl = cp5.addToggle("revRoll")
     .setPosition(tglRollX,tglRollY)
     .setSize(tglXsize,tglYsize)
     .setValue(true)
     .setMode(ControlP5.SWITCH)
     ;
  
 revEmgTgl = cp5.addToggle("revEmg")
     .setPosition(tglEmgX,tglEmgY)
     .setSize(tglXsize,tglYsize)
     .setValue(true)
     .setMode(ControlP5.SWITCH)
     ;
     
 OSCTgl = cp5.addToggle("OSC")
     .setPosition(tglOSCX,tglOSCY)
     .setSize(tglXsize,tglYsize)
     .setValue(false)
     .setMode(ControlP5.SWITCH)
     ;
     
 MIDITgl = cp5.addToggle("MIDI")
     .setPosition(tglMIDIX,tglOSCY)
     .setSize(tglXsize,tglYsize)
     .setValue(true)
     .setMode(ControlP5.SWITCH)
     ;

  MIDIPortNb = cp5.addNumberbox("MIDI_PORT")
     .setPosition(nbMIDIportX,nbMIDIportY)
     .setSize(tglXsize,tglYsize)
     .setValue(1)
     .setScrollSensitivity(0.5f)
     .setMultiplier(1)
     .setMin(0)
     .setMax(10)
     ;
     
  MIDIchannelNb = cp5.addNumberbox("MIDI_CH")
     .setPosition(nbMIDIchX,nbMIDIchY)
     .setSize(tglXsize,tglYsize)
     .setValue(1)
     .setScrollSensitivity(0.5f)
     .setMultiplier(1)
     .setMin(0)
     .setMax(16)
     ;

}

//void revYaw() {
 // reverseYaw = 1-revYawTgl.getValue();
//}

public void revYaw(boolean theFlag) {
  if(!theFlag) reverseYaw = 1;
   else  reverseYaw = 0;
}

public void revPitch(boolean theFlag) {
  if(!theFlag) reversePitch = 1;
  else  reversePitch = 0;
}

public void revRoll(boolean theFlag) {
  if(!theFlag) reverseRoll = 1;
  else  reverseRoll = 0;
}

public void revEmg(boolean theFlag) {
  if(!theFlag) reverseEmg = 1;
  else  reverseEmg = 0;
}

public void OSC(boolean theFlag) {
  if(theFlag) {OpenSoundControl = false;}
  else {OpenSoundControl = true;}
}

public void MIDI(boolean theFlag) {
  if(theFlag) {MIDI = false;}
  else {MIDI = true;}
}

public void MIDI_PORT(int value) { 
  portMIDI = value;
  setUpMIDI();
  }

public void MIDI_CH(int value) { 
  chMIDI = value;
  }


  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "MyoMusic" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}


// integra Logo
PImage integralogo;

// osc
import oscP5.*;
import netP5.*;
OscP5 oscP5;
NetAddress myRemoteLocation;

// myo 
import de.voidplus.myo.*;
Myo myo;
ArrayList<ArrayList<Integer>> sensors;
String pose;

// buttons
Tgl revYawButton;
Tgl revPitchButton;
Tgl revRollButton;

Bng centYawButton;
Bng centPitchButton;
Bng centRollButton;


int revYawTglX, revYawTglSize, revYawTglY, reverseYaw = 0; // Reverse Yaw tgl
int revPitchTglX, revPitchTglY, revPitchTglSize, reversePitch = 0; // Pitch tgl
int revRollTglX, revRollTglY, revRollTglSize, reverseRoll = 0; // Pitch tgl

int centYawBngX, centYawBngY, centYawBngSize, centreYaw = 0; // Centre Yaw bng
int centPitchBngX, centPitchBngY, centPitchBngSize, centrePitch = 0; // Centre Pitch bng
int centRollBngX, centRollBngY, centRollBngSize, centreRoll = 0; // Centre Roll bng

void setup() {
  size(1000, 850); //window size

integralogo = loadImage("blue-integra.png"); // 

// Myo settingd
  myo = new Myo(this);
  myo.withEmg();
  myo.setFrequency(20); // set frequency Data
  
  sensors = new ArrayList<ArrayList<Integer>>();
  for(int i=0; i<34; i++){
    sensors.add(new ArrayList<Integer>()); 
  }
  
 // OSC settings
  oscP5 = new OscP5(this,12000);
  myRemoteLocation = new NetAddress("127.0.0.1",5432); // IP address
  
  int centering= 100;
 
 // Tgl settings
  revYawTglX = width/2-100;
  revYawTglSize = revPitchTglSize = revRollTglSize = 70;
  revPitchTglX = revYawTglX + revYawTglSize +30;
  revRollTglX = revPitchTglX + revPitchTglSize +30;
  revYawTglY = revPitchTglY = revRollTglY = 100;
 
  revYawButton = new Tgl(revYawTglX, revYawTglY, revYawTglSize);
  revPitchButton = new Tgl(revPitchTglX, revPitchTglY, revPitchTglSize);
  revRollButton = new Tgl(revRollTglX, revRollTglY, revRollTglSize);

 // Bng settings
  centYawBngX = revYawTglX;
  centYawBngSize = centPitchBngSize = centRollBngSize = 70;
  centPitchBngX = centYawBngX + centYawBngSize +30;
  centRollBngX = centPitchBngX + centPitchBngSize +30;
  centYawBngY = centPitchBngY = centRollBngY = revYawTglY+revYawTglSize+10;

  centYawButton = new Bng(centYawBngX, centYawBngY, centYawBngSize);
  centPitchButton = new Bng(centPitchBngX, centPitchBngY, centPitchBngSize);
  centRollButton = new Bng(centRollBngX, centRollBngY, centRollBngSize);
  
//Bang settings
   integralogo.resize(integralogo.width/2,integralogo.height/2);

  
} 




void draw() {
   background(0); //background color
   image(integralogo, width-integralogo.width, 0); // display integra logo

   noFill();
 
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
  
      //------- BUTTONS ------
      
// run buttons
revYawButton.run();
revPitchButton.run();
revRollButton.run();

centYawButton.run();
centPitchButton.run();
centRollButton.run();

// button state
if (revYawButton.status){reverseYaw=1;}
else if (!revYawButton.status){reverseYaw=0;}

if (revPitchButton.status){reversePitch=1;}
else if (!revPitchButton.status){reversePitch=0;}

if (revRollButton.status){reverseRoll=1;}
else if (!revRollButton.status){reverseRoll=0;}

if (centRollButton.status){ORx=orX;}
if (centPitchButton.status){ORy=orY;}
if (centYawButton.status){ORz=orZ;}
   
 // ---   LABELS -------
   textSize(30);
   fill(#ffb600);
   
   // title
      
   // graph
   text("EMG 1", 10, 35);
   text("EMG 2", 10, 85);
   text("EMG 3", 10, 135);
   text("EMG 4", 10, 185);
   text("EMG 5", 10, 235);
   text("EMG 6", 10, 285);
   text("EMG 7", 10, 335);
   text("EMG 8", 10, 385);
   text("ROLL", 10, 435);
   text("PITCH", 10, 485);
   text("YAW", 10, 535);
   text("ACCELLERATION X", 10, 585);
   text("ACCELLERATION Y", 10, 635);
   text("ACCELLERATION Z", 10, 685);
   text("GYRO X", 10, 735);
   text("GYRO Y", 10, 785);
   text("GYRO Z", 10, 835);
   text("POSE: "+pose, revYawTglX-revYawTglSize-20, 300); 
   
   // control pannel
   // data control
   text("------ DATA CONTROL ------", revYawTglX-110, revYawTglY-70);
   text("YAW", revYawTglX, revYawTglY-20);
   text("PITCH", revPitchTglX-7, revPitchTglY-20);
   text("ROLL", revRollTglX, revRollTglY-20);
   text("REV", revYawTglX-revYawTglSize-20, revYawTglY+(revYawTglSize/2));
   text("CENT", revYawTglX-revYawTglSize-20, centYawBngY+(centYawBngSize/1.5));
   noFill();


  
}

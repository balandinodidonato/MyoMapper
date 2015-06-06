import de.voidplus.myo.*;

import oscP5.*;
import netP5.*;
  
OscP5 oscP5;
NetAddress myRemoteLocation;

Myo myo;
ArrayList<ArrayList<Integer>> sensors;

String pose;

Tgl revYawButton;
Tgl revPitchButton;

int reverseYaw, reversePitch = 0;

void setup() {
  size(1000, 900);

  myo = new Myo(this);
  myo.withEmg();
  myo.setFrequency(20); // set frequency Data

  
  sensors = new ArrayList<ArrayList<Integer>>();
  for(int i=0; i<34; i++){
    sensors.add(new ArrayList<Integer>()); 
  
  }
  oscP5 = new OscP5(this,12000);
  myRemoteLocation = new NetAddress("127.0.0.1",5432);
  
  int centering= 100;
  
  revYawButton = new Tgl(300, 0, 50);
  revPitchButton = new Tgl(350, 0, 50);
  
 

  
} 

void draw() {

   background(222,222,222);
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
revYawButton.run();
revPitchButton.run();

if (revYawButton.status){reverseYaw=1;}
else if (!revYawButton.status){reverseYaw=0;}

if (revPitchButton.status){reversePitch=1;}
else if (!revPitchButton.status){reversePitch=0;}
   
 // ---   LABELS -------
   textSize(30);
   fill(255);
   
   // graph
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
   text("POSE: "+pose, 10, 875); 
   
   // buttons
   /*
   text("YAW", rectRevYawX, rectRevYawY-10);
   text("PITCH", rectRevPitchX, rectRevPitchY-10);
   text("REV", rectRevYawX-100, rectRevYawY+60);
   text("CENT", rectCentYawX-100, rectCentYawY+60);
   noFill();*/

  
}

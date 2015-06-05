import de.voidplus.myo.*;

import oscP5.*;
import netP5.*;
  
OscP5 oscP5;
NetAddress myRemoteLocation;

Myo myo;
ArrayList<ArrayList<Integer>> sensors;

String pose;

void setup() {
  size(1000, 900);
  background(0.5);

  myo = new Myo(this);
  myo.withEmg();
  myo.setFrequency(20); // set frequency Data

  
  sensors = new ArrayList<ArrayList<Integer>>();
  for(int i=0; i<34; i++){
    sensors.add(new ArrayList<Integer>()); 
  
  }
  oscP5 = new OscP5(this,12000);
  myRemoteLocation = new NetAddress("127.0.0.1",5432);
  
  
  circleColor1 = color(0,255,0);
  rectColor1 = color(0,255,0);
  circleX1 = width-(circleSize1/2+10);
  circleY1 = circleSize1-5;
  rectX1 = width-(rectSize1+circleSize1+20);
  rectY1 = rectSize1/2-5;

  circleColor2 = color(0);
  rectColor2 = color(0);
  circleX2 = width-(circleSize1/2+10);
  circleY2 = circleSize1*2+10;
  rectX2 = width-(rectSize1+circleSize1+20);
  rectY2 = rectSize1*2-28;
  ellipseMode(CENTER);  

  
} 

void draw() {


  background(222,222,222);
   textSize(30);
   fill(255);
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
  update(mouseX, mouseY);
  fill(rectColor1);
  stroke(0);
  rect(rectX1, rectY1, rectSize1, rectSize1);
  fill(circleColor1);
  ellipse(circleX1, circleY1, circleSize1, circleSize1);
  
  fill(rectColor2);
  stroke(0);
  rect(rectX2, rectY2, rectSize2, rectSize2);
  fill(circleColor2);
  ellipse(circleX2, circleY2, circleSize2, circleSize2);
}

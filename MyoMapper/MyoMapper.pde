import controlP5.*;
ControlP5 cp5;


int windowX, windowY = 0;
void setup() {
  
  frameRate(24);
  
  cp5 = new ControlP5(this);
  
  size(int(displayWidth*0.8), int(displayHeight*0.9)); //window size
  
  myoSetup(); 
  setUpMIDI();
  toggles();
  bangs();
  oscSetup(); 
  rescale();
  setupSliders(); 
<<<<<<< HEAD
 
} 

void draw() {
  background(0); //background color
  logoRun();
  updateSliders();
  labels();
  emgGraphs();
  
  //-------
  sendPose();
  sendOrientation();
  sendAcceleration();
  sendGyro();
  emgAvgSend();  
  emgSend();
     
=======
} 

void draw() {
  background(0);
  
  if(emgOnOff)EmgSend();
  if(mavOnOff)MAV();
  if(orientOnOff)Orientation();
  if(accOnOff)Acceleration();
  if(gyroOnOff)Gyro();
  if(poseOnOff)Pose();

  updateSliders();
  labels();
  if(waveformOnOff){
    labelsAnalysis();
    analysis();
    }
>>>>>>> development
}

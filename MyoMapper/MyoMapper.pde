import controlP5.*;
ControlP5 cp5;


int windowX, windowY = 0;
void setup() {
  
  frameRate(24);
  
  cp5 = new ControlP5(this);
  
  windowX = int(displayWidth/1.3);
  windowY = displayHeight-int(displayHeight/10);
  size(windowX, windowY); //window size
  
  myoSetup(); 
  toggles();
  setUpMIDI();  
  bangs();
  oscSetup(); 
  rescale();
  setupSliders(); 
 
} 

void draw() {
  background(0); //background color
  if(poseOnOff)sendPose();
  if(orientOnOff)sendOrientation();
  if(accOnOff)sendAcceleration();
  if(gyroOnOff)sendGyro();
  if(emgOnOff)emgSend();
  
  if(orientOnOff)updateSliders();
  labels();
  analysis();

   
}

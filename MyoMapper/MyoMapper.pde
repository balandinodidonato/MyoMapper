import controlP5.*;
ControlP5 cp5;

int windowX, windowY = 0;
void setup() {
  cp5 = new ControlP5(this);
  
  windowX = int(displayWidth/1.5);
  windowY = displayHeight-int(displayHeight/10);
  size(windowX, windowY); //window size
  
  logoSetup();
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
  logoRun();
  updateSliders();
  labels();
  emgGraphs();
}

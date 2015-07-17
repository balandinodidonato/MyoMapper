import controlP5.*;
ControlP5 cp5;

void setup() {
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

void draw() {
  background(0); //background color
  logoRun();
  updateSliders();
  labels();
  emgGraphs();
}

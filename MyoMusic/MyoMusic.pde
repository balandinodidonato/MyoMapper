PImage integralogo;
PImage cons;
import controlP5.*;


void setup() {
  size(1000, 850); //window size
  logoSetup(); 
  myoSetup();
  setUpMIDI();
  toggles();  
  bangs();
  oscSetup(); 
  rescale();
} 

void draw() {
  background(0); //background color
  logoRun();
  emgGraphs();
  sliders();
  labels();
}

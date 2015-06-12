PImage integralogo;
PImage cons;
import controlP5.*;

void setup() {
  size(1000, 850); //window size
  toggles();  
  BANGBANG();

  logoSetup(); 
  myoSetup();
  oscSetup(); 
  sliders();
} 


void draw() {
  background(0); //background color
  
  logoRun();
  emgGraphs();
  defineRange();
  labels();


}

PImage integralogo;
PImage cons;

void setup() {
  size(1000, 850); //window size

  logoSetup(); 
  myoSetup();
  oscSetup(); 
  setUpButtons();
  setUpSliders();
} 


void draw() {
  background(0); //background color
  
  logoRun();
  emgGraphs();
  buttons();
  labels();
  runSliders();
}

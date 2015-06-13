void setup() {
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
  emgGraphs();
  updateSliders();
  labels();
}

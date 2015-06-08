
// integra Logo
PImage integralogo;





void setup() {
  size(1000, 850); //window size

  integralogo = loadImage("blue-integra.png"); // 
  integralogo.resize(integralogo.width/2,integralogo.height/2);

  myoSetup();
  oscSetup(); 
  setUpButtons();
  setUpSliders();
 
} 


void draw() {

  background(0); //background color
  image(integralogo, width-integralogo.width-10, height-integralogo.height-10); // display integra logo

  emgGraphs();
  buttons();
  labels();
  runSliders();
}

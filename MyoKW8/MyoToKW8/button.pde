/**
 * Button. 
 * 
 * Click on one of the colored squares in the 
 * center of the image to change the color of 
 * the background. 
 */
 
int rectX1, rectY1;      // Position of square button
int circleX1, circleY1;  // Position of circle button
int rectSize1 = 90;     // Diameter of rect
int circleSize1 = 93;   // Diameter of circle
color rectColor1, circleColor1, baseColor1;
boolean rectOver1 = false;
boolean circleOver1 = false;
boolean reverseYaw = true;
boolean reversePitch = true;
int reversePan = 0;
int reverseTilt = 0;


void update(int x, int y) {
  if ( overCircle(circleX1, circleY1, circleSize1) ) {
    circleOver1 = true;
    rectOver1 = false;
  } else if ( overRect(rectX1, rectY1, rectSize1, rectSize1) ) {
    rectOver1 = true;
    circleOver1 = false;
  } else {
    circleOver1 = rectOver1 = false;
  }
}

void mousePressed() {
  if ((rectOver1)&&(reverseYaw)) {
     rectColor1 = color(255, 0, 0);
     reverseYaw = false;  
     reversePan=255;}
 else if ((rectOver1)&&(!reverseYaw)) {
     rectColor1 = color(0, 255, 0);
     reverseYaw = true;
     reversePan=0;}
  else if((circleOver1)&&(reversePitch)) {
     circleColor1 = color(255, 0, 0);  
     reversePitch = false;
     reverseTilt=255;}
  else if((circleOver1)&&(!reversePitch)){
      circleColor1 = color(0, 255, 0); 
      reversePitch = true;
      reverseTilt=0;}
}

boolean overRect(int x, int y, int width, int height)  {
  if (mouseX >= x && mouseX <= x+width && 
      mouseY >= y && mouseY <= y+height) {
    return true;
  } else {
    return false;
  }
}

boolean overCircle(int x, int y, int diameter) {
  float disX = x - mouseX;
  float disY = y - mouseY;
  if (sqrt(sq(disX) + sq(disY)) < diameter/2 ) {
    return true;
  } else {
    return false;
  }
}

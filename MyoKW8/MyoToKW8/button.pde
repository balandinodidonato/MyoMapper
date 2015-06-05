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

int rectX2, rectY2;      // Position of square button
int circleX2, circleY2;  // Position of circle button
int rectSize2 = 90;     // Diameter of rect
int circleSize2 = 93;   // Diameter of circle
color rectColor2, circleColor2, baseColor2;
boolean rectOver1 = false;
boolean circleOver1 = false;
boolean reverseYaw = true;
boolean reversePitch = true;
int reversePan = 0;
int reverseTilt = 0;

boolean circleOver2 = false;
boolean rectOver2 = false;


void update(int x, int y) {
  if ( overCircle1(circleX1, circleY1, circleSize1) ) {
    circleOver2 = false;
    rectOver2 = false;
    rectOver1 = false;
    circleOver1 = true;
  } else if ( overRect1(rectX1, rectY1, rectSize1, rectSize1) ) {
    circleOver2 = false;
    rectOver2 = false;
    rectOver1 = true;
    circleOver1 = false;
  }  
 else if ( overCircle2(circleX2, circleY2, circleSize2) ) {
    circleOver2 = true;
    rectOver2 = false;
    rectOver1 = false;
    circleOver1 = false;
  } else if ( overRect2(rectX2, rectY2, rectSize2, rectSize2) ) {
    circleOver2 = false;
    rectOver2 = true;
    rectOver1 = false;
    circleOver1 = false;
  } else {
    circleOver1 = rectOver1 = circleOver2 = rectOver2 = false;
  }
  
}

void mousePressed() {
  if ((rectOver1)&&(reverseYaw)) {
     rectColor1 = color(255, 0, 0);
     reverseYaw = false;  
     reversePan=1;} //reverse pan/yaw
 else if ((rectOver1)&&(!reverseYaw)) {
     rectColor1 = color(0, 255, 0);
     reverseYaw = true;
     reversePan=0;} //reverse tilt/pitch
  else if((circleOver1)&&(reversePitch)) {
     circleColor1 = color(255, 0, 0);  
     reversePitch = false;
     reverseTilt=1;}
  else if((circleOver1)&&(!reversePitch)){
      circleColor1 = color(0, 255, 0); 
      reversePitch = true;
      reverseTilt=0;}
 
 
  else if (rectOver2) {
   ORz = orZ;
  }
 else if (circleOver2) {
      ORy = orY;
 }
}

boolean overRect1(int x, int y, int width, int height)  {
  if (mouseX >= x && mouseX <= x+width && 
      mouseY >= y && mouseY <= y+height) {
    return true;
  } else {
    return false;
  }
}

boolean overCircle1(int x, int y, int diameter) {
  float disX = x - mouseX;
  float disY = y - mouseY;
  if (sqrt(sq(disX) + sq(disY)) < diameter/2 ) {
    return true;
  } else {
    return false;
  }}
  
  
  boolean overRect2(int x, int y, int width, int height)  {
  if (mouseX >= x && mouseX <= x+width && 
      mouseY >= y && mouseY <= y+height) {
    return true;
  } else {
    return false;
  }
}

boolean overCircle2(int x, int y, int diameter) {
  float disX = x - mouseX;
  float disY = y - mouseY;
  if (sqrt(sq(disX) + sq(disY)) < diameter/2 ) {
    return true;
  } else {
    return false;
  }
  
}

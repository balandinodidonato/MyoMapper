/**
 * Button. 
 * 
 * Click on one of the colored squares in the 
 * center of the image to change the color of 
 * the background. 
 */
 
int rectX, rectY;      // Position of square button
int circleX, circleY;  // Position of circle button
int rectSize = 90;     // Diameter of rect
int circleSize = 93;   // Diameter of circle
color rectColor, circleColor, baseColor;
color rectHighlight, circleHighlight;
color currentColor;
boolean rectOver = false;
boolean circleOver = false;
boolean centerYaw = true;
boolean centerPitch = true;



void update(int x, int y) {
  if ( overCircle(circleX, circleY, circleSize) ) {
    circleOver = true;
    rectOver = false;
  } else if ( overRect(rectX, rectY, rectSize, rectSize) ) {
    rectOver = true;
    circleOver = false;
  } else {
    circleOver = rectOver = false;
  }
}

void mousePressed() {
  if ((rectOver)&&(centerYaw)) {
     rectColor = color(255, 0, 0);
     centerYaw = false;  }
 else if ((rectOver)&&(!centerYaw)) {
     rectColor = color(0, 255, 0);
     centerYaw = true;  }
  else if((circleOver)&&(centerPitch)) {
     circleColor = color(255, 0, 0);  
     centerPitch = false;}
  else if((circleOver)&&(!centerPitch)){
      circleColor = color(0, 255, 0); 
      centerPitch = true;      }
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

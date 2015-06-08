class Bng{

  int x = 0;
  int y = 0;
  int circleSize = 10;
  int Cbutton = color(100);
  float size = 1;
  boolean circleOver = false;  
  boolean status = false;  // init button status
  int mouse = 0;
  
  Bng(int posX, int posY, int size) {
    
    x = posX+size/2;
    y = posY+size/2;
    circleSize = size;
    
  }
  
  
  
void display(){
  noStroke();
  fill(Cbutton);
  ellipse(x, y, circleSize, circleSize);
}
  
  
  
void run(){
  
   display(); // run display function
   update(); // run update function

  if ((mousePressed)&&(circleOver)) {
    if (mouse<1){  // mousePressed data filter
      if (status == false) // test the button status
         {status = true; // set button status on
          Cbutton = color(200);
           } 
         mouse++;  
     }
     else {status = false;
           Cbutton = color(100);}
     
   }
   else if((!mousePressed)&&(circleOver))
    mouse = 0;
}  



void update() {  // test the position of the mouse over the button
  if ( overCircle(x, y, circleSize) ) 
    { circleOver = true; 
     // println("overCircle = "+circleOver);
      }
  else 
    {circleOver = false;
     // println("overCircle = "+circleOver);
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


}

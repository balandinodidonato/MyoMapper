class Tgl{

  int x = 0;
  int y = 0;
  int rectSize = 10;
  int Cbutton = color(255,0,0);
  float size = 1;
  boolean rectOver = false;  
  boolean status = false;  // init button status
  int mouse = 0;
  
  Tgl(int posX, int posY, int size) {
    
    x = posX;
    y = posY;
    rectSize = size;
    
  }
  
void display(){
  fill(Cbutton);
  rect(x, y, rectSize, rectSize);
}
  
void run(){
  
   display(); // run display function
   update(); // run update function

  if ((mousePressed)&&(rectOver)) {
    if (mouse<1){  // mousePressed data filter
      if (status == false) // test the button status
         {status = true; // set button status on
          Cbutton = color(0, 255, 0); // change the button color to green
      //  println("status = "+status);
          }
      else if (status == true) // test the button status
              {status = false; // set button status off
               Cbutton = color(255, 0, 0);  // change the button color to red
           //  println("status = "+status);
              }
           
     }
     
     mouse++;
   }
   else if((!mousePressed)&&(rectOver))
    mouse = 0;
}  

void update() {  // test the position of the mouse over the button
  if ( overRect(x, y, rectSize, rectSize) ) 
    { rectOver = true; 
     // println("overRect = "+rectOver);
      }
  else 
    {rectOver = false;
     // println("overRect = "+rectOver);
     }
} 

boolean overRect(int X, int Y, int width, int height)  {  // mouse tracking
  if (mouseX >= X && mouseX <= X+width && 
      mouseY >= Y && mouseY <= Y+height) {
    return true;
  } else {
    return false;
  }
}


//----- end class
}

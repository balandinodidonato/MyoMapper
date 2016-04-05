int[][] numbers = new int[18][200];
boolean waveformOnOff = true;
int z; // variable to establish line colors
int lineY;

void analysis(){
  
  int constantY = int(labelY[0]-(graphLabelsTextSize));

  stroke(255);
  
  for(int y = 0; y<18;y++){
    
    beginShape();

    for(int i = 0; i<200;i++){
      if(y<8){
        stroke(155);
        lineY = int(height*0.0556);
        z = 1;}
     else if(y==8){ 
        stroke(255); 
        lineY = int(height*0.0569); }
      else if(y==9){ 
        stroke(255, 0, 0);
        lineY = int(height*0.0692);
        z = 1; }
      else if(y==10||y==13||y==16){ 
        stroke(0, 255, 0);
        z = 0; }
      else if(y==11||y==14||y==17){
        stroke(0, 0, 255);
        z = -1; }
      if(y==12){ 
        stroke(255, 0, 0);
        lineY = int(height*0.06019);
        z = 1; }
      else if(y==15){ 
        stroke(255, 0, 0);
        z = 1;
      }
      vertex((i*(width*0.00215))+width*0.085, (lineY*(y+z)-constantY)-numbers[y][i]);
    }
    
    endShape();
  } 
  
  for(int y = 0; y<18;y++){
    for(int i = 1; i<200;i++){
     numbers[y][i-1] = numbers[y][i];
   }
  }
  
  float constantEmg0 = height*0.00015;
  float constantEmg1 = labelTextSize*0.5;
  float constantMav =  height*0.038;
  float constantOrient = height*0.15;
  float constantAcc = height*0.0085;
  float constantGyro = height*0.000055;
  
  for(int y = 0; y<18;y++){
    if (emgOnOff){
       if(y<8)numbers[y][200-1]= int(emg[y]*constantEmg0+constantEmg1);
       }
    if(mavOnOff){
      if(y==8)numbers[y][200-1]= int(mav * constantMav);
      }
    if(orientOnOff){
      if(y==9)numbers[y][200-1]= int(yaw*constantOrient);
      else if(y==10)numbers[y][200-1]= int(pitch*constantOrient);
      else if(y==11)numbers[y][200-1]= int(roll*constantOrient);
      }
   if(accOnOff){
      if(y==12)numbers[y][200-1]= int(acceleration.x*constantAcc);
      else if(y==13)numbers[y][200-1]= int(acceleration.y*constantAcc);
      else if(y==14)numbers[y][200-1]= int(acceleration.z*constantAcc);
      }
    if(gyroOnOff){
      if(y==15)numbers[y][200-1]= int(gyro.x*constantGyro);
      else if(y==16)numbers[y][200-1]= int(gyro.y*constantGyro);
      else if(y==17)numbers[y][200-1]= int(gyro.z*constantGyro);
      }
  }
}

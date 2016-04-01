int[][] numbers = new int[17][200];

void analysis(){
  stroke(255);
  for(int y = 0; y<17;y++){
    beginShape();
    for(int i = 0; i<200;i++){
      vertex((i*2.3)+width/10, (height/17)*(y+1)-numbers[y][i]);
    }
    endShape();
  } 
  for(int y = 0; y<17;y++){
    for(int i = 1; i<200;i++){
     numbers[y][i-1] = numbers[y][i];
   }
  }
  for(int y = 0; y<17;y++){
    if (emgOnOff)
        {if(y<8)numbers[y][200-1]= int(abs(emg[y]/(height/200)));}
    if(orientOnOff){
      if(y==8)numbers[y][200-1]= int(yaw*(height/20));
      else if(y==9)numbers[y][200-1]= int(pitch*(height/20));
      else if(y==10)numbers[y][200-1]= int(roll*(height/20));
      }
   if(accOnOff){
      if(y==11)numbers[y][200-1]= int(acceleration.x*(height/220)+(height/70));
      else if(y==12)numbers[y][200-1]= int(acceleration.y*(height/220)+(height/70));
      else if(y==13)numbers[y][200-1]= int(acceleration.z*(height/220)+(height/70));
   }
    if(gyroOnOff){
      if(y==14)numbers[y][200-1]= int(gyro.x*(height*0.00002)+(height/70));
      else if(y==15)numbers[y][200-1]= int(gyro.y*(height*0.00002)+(height/70));
      else if(y==16)numbers[y][200-1]= int(gyro.z*(height*0.00002)+(height/70));
      }
  }
}

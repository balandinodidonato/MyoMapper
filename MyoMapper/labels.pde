void labels(){
   noStroke();

   textSize(width/24.285714286);
   fill(#1D4383);
  text("MyoMapper", width/2+width/8,height/18);

   fill(#1D4383);
   
      int labeX = width/150;
      int labelXFactor = int(height/17.6);
      int marginY = int(height/17.2);
      int[] labelY = new int[17];
      
      for(int i=0; i<17; i++){
      labelY[i]= (windowY/17)*(i+1);
      }
      
      int labelTextSize = int(width/33);
   
   textSize(labelTextSize);
   text("EMG 1", labeX, labelY[0]);
   text("EMG 2", labeX, labelY[1]);
   text("EMG 3", labeX, labelY[2]);
   text("EMG 4", labeX, labelY[3]);
   text("EMG 5", labeX, labelY[4]);
   text("EMG 6", labeX, labelY[5]);
   text("EMG 7", labeX, labelY[6]);
   text("EMG 8", labeX, labelY[7]);
   text("YAW", labeX, labelY[8]);
   text("PITCH", labeX, labelY[9]);
   text("ROLL", labeX, labelY[10]);
   text("ACC X", labeX, labelY[11]);
   text("ACC Y", labeX, labelY[12]);
   text("ACC Z", labeX, labelY[13]);
   text("GYR X", labeX, labelY[14]);
   text("GYR Y", labeX, labelY[15]);
   text("GYR Z", labeX, labelY[16]);
   
   text("POSE: "+pose, rEmgX,rEmgY+rEmgYsize*2); 
   text("STATE: "+connectionState+" - "+syncState, rEmgX,rEmgY+rEmgYsize*3); 

   fill(#1D4383);
   textSize(width/56.666666667);
   text("Balandino Di Donato - 2016", width/1.6, height-height/40); 
   text("www.balandinodidonato.com",  width/1.61, height-height/300);
   
   noFill();  
}

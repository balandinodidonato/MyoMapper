int labelTextSize = int(width*0.0303030303);
int labeX = int(width*0.006666666667);
int labelXFactor = int(height*0.05681818182);
int marginY = int(height*0.05681818182);
int[] labelY = new int[18];

void labels(){
  noStroke();

  textSize(width*0.04117647059);
  fill(#1D4383);
  text("MyoMapper", width*0.5+width*0.125,height*0.06);
  
  textSize(width*0.01764705882);
  text("Balandino Di Donato - 2016", width*0.625, height*0.97); 
  text("www.balandinodidonato.com",  width*0.625, height*0.99);
  
  noFill(); 

}

void labelsAnalysis(){
  
 labelTextSize = int(height*0.033);

  
  int X0 = 0;
  int X1 = int(width*0.52);
  int Y1 = int(height*0.516);
  int factor = int(height*0.168);

  stroke(#1D4383);

  for(int i=0; i<3; i++){
    int Y12 = int(Y1+(i*factor));
    line(X0, Y12, X1, Y12);
  }
  noStroke();


  for(int i=0; i<18; i++){
    labelY[i]= int(height*0.0555555555)*(i+1)-int(height*0.0055);
    
    stroke(#1D4383);
    if(i<8) line(X0, labelY[i]+int(height*0.01), X1, labelY[i]+int(height*0.01));   
    noStroke();

  textSize(labelTextSize);
  fill(155);
  text("EMG 1", labeX, labelY[0]);
  text("EMG 2", labeX, labelY[1]);
  text("EMG 3", labeX, labelY[2]);
  text("EMG 4", labeX, labelY[3]);
  text("EMG 5", labeX, labelY[4]);
  text("EMG 6", labeX, labelY[5]);
  text("EMG 7", labeX, labelY[6]);
  text("EMG 8", labeX, labelY[7]);
  fill(255);
  text(" MAV", labeX, labelY[8]);
  fill(255, 0, 0);
  text(" YAW", labeX, labelY[9]);
  fill(0, 255, 0);
  text("PITCH", labeX, labelY[10]);
  fill(0, 0, 255);
  text(" ROLL", labeX, labelY[11]);
  fill(255, 0, 0);
  text("ACC X", labeX, labelY[12]);
  fill(0, 255, 0);
  text("ACC Y", labeX, labelY[13]);
  fill(0, 0, 255);
  text("ACC Z", labeX, labelY[14]);
  fill(255, 0, 0);
  text("GYR X", labeX, labelY[15]);
  fill(0, 255, 0);
  text("GYR Y", labeX, labelY[16]);
  fill(0, 0, 255);
  text("GYR Z", labeX, labelY[17]);

  fill(#1D4383);   
  text("POSE: "+pose, rEmgX,rEmgY+rEmgYsize*2); 
  text("STATE: "+connectionState+" - "+syncState, rEmgX,rEmgY+rEmgYsize*3);
  
  noFill(); 
  }
}

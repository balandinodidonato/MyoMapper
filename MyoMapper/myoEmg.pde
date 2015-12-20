int emg[];

float[] EMG = new float[8];
float emgMin  = 0;
float emgMax = 1;


int intensityMIDI; //cc10
int[] emgMIDI = new int[8]; //cc11, cc12, cc13, cc14, cc15, cc16, cc17, cc18
float intensity = 0;
int intensityS = 0;


void myoOnEmg(Device myo, long timestamp, int[] data) {
  // println("Sketch: myoOnEmg");
  // int[] data <- 8 values from -128 to 1272
   
  synchronized (this){

   PVector orientation = myo.getOrientation();
   PVector acceleration = myo.getAccelerometer();
   PVector gyro = myo.getGyroscope();

   //   println("orientation" + acceleration.x + " " + acceleration.y + " " + acceleration.z);
   int[] imu = new int [9];
   imu[0] = 50-int(yaw*49); // Original value 0-1
   imu[1] = 50-int(pitch*49); // Original value 0-1
   imu[2] = 50-int(roll*49); // Original value 0-1
   imu[3] = int(((acceleration.x/2)+PI)*7.79859221150287); // Original value 0-2PI
   imu[4] = int(((acceleration.y/2)+PI)*7.79859221150287); // Original value 0-2PI
   imu[5] = int(((acceleration.z/2)+PI)*7.79859221150287); // Original value 0-2PI
   imu[6] = int(((gyro.x/2)+500)*0.049); // Original value 0-1000
   imu[7] = int(((gyro.y/2)+500)*0.049); // Original value 0-1000
   imu[8] = int(((gyro.z/2)+500)*0.049); // Original value 0-1000
   
  for(int i=8; i<17; i++){
    sensors.get(i).add(imu[i-8]);}

  for(int i=0; i<8; i++){
    sensors.get(i).add(int(abs(emg[i])*(-0.3125)+int(windowX/17)));

   //for(int i = 0; i<8; i++){
     // sensors.get(i).add(int((data[i]+128)*0.1960784314)); // [-128 - 127]
  }
   
    while(sensors.get(0).size() > width/2){

      for(ArrayList<Integer> sensor : sensors){

        sensor.remove(0);
      }
    }
  } 
}
  
void emgGraphs(){
  
   noFill();
   stroke(255);

   synchronized (this){
    for(int i=0; i<17; i++){
      if(!sensors.get(i).isEmpty()){
        beginShape();
        for(int j=100; j<sensors.get(i).size(); j++){
          vertex(j, sensors.get(i).get(j)+(i*(int(windowY/17))));
        }
        endShape();
      } 
    }
  }
  
}


void emgAvgSend(){
      float emgSum = 0;

    for(int i=0; i<8; i++){
     emg[i] = abs(emg[i]);

        // add emg value to /emg0 message
      EMG[i] = abs(reverseEmg-emg[i]);
      EMG[i] = map(EMG[i], 0, 128, emgMin, emgMax);
      emgSum = EMG[i]+emgSum; // EMG sum for avg calculation    
   
      if (MIDI){
        emgMIDI[i] = int(EMG[i]*127);
        myBus.sendControllerChange(chMIDI, 11+i, emgMIDI[i]);}
  }
     
      intensity = emgSum/8; // average calculation
      intensity = max(intensity, 0);
      intensity = min(intensity, 1); 
}

void emgSend(){
if (MIDI) {
      intensityMIDI = int(intensity*127);
      myBus.sendControllerChange(chMIDI, 10, intensityMIDI); // Send a 
      
      }
     
   if(OpenSoundControl){  
    
     OscMessage Emg = new OscMessage("/emg");
     OscMessage emgAvg = new OscMessage("/emgAvg");   
     OscMessage emgAvgS = new OscMessage("/emgAvgs");  
     
      intensityS = int(intensity*255);
     
      Emg.add(emg);
      emgAvg.add(intensity);
      emgAvgS.add(intensityS);
      
      oscP5.send(Emg, myRemoteLocation);
      oscP5.send(emgAvg, myRemoteLocation);
      oscP5.send(emgAvgS, myRemoteLocation);
   }
}

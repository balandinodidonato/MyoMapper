float[] EMG = new float[8];
float emgMin  = 0;
float emgMax = 1;
int mavMIDI; //cc10
int[] emgMIDI = new int[8]; //cc11, cc12, cc13, cc14, cc15, cc16, cc17, cc18
float mav = 0;  
float emgSum;

boolean emgOnOff = true;
boolean mavOnOff = true;
  
void MAV(){
  
  emgMin = avgEMG.getLowValue();
  emgMax = avgEMG.getHighValue();
  
  emgSum = 0;

  for(int i=0; i<8; i++){
    emg[i] = abs(emg[i]);

    EMG[i] = abs(reverseMAV-emg[i]);
    EMG[i] = map(EMG[i], 0, 128, emgMin, emgMax);
    emgSum = EMG[i]+emgSum; // EMG sum for avg calculation    
    }
    
  mav = emgSum*0.125;
  mav = max(mav, 0);
  mav = min(mav, 1);
 
  if (MIDI) { 
    mavMIDI = int(mav*127);
    myBus.sendControllerChange(chMIDI, 10, mavMIDI);
    } 
    
  if(OpenSoundControl){
    OscMessage emgMAV = new OscMessage("/emgMav");   
    emgMAV.add(mav);
    oscP5.send(emgMAV, myRemoteLocation);
    }
} 

void EmgSend(){
  
  if(MIDI) {
    for (int i=0; 1<8; i++){
      myBus.sendControllerChange(chMIDI, 11+i, emgMIDI[i]); 
      }  
    }

  if(OpenSoundControl){  
    if(emgOnOff){
      OscMessage Emg = new OscMessage("/emg");     
      Emg.add(emg);
      oscP5.send(Emg, myRemoteLocation);
      } 
    }
}


<<<<<<< HEAD
void emgAvgSend(){
      float emgSum = 0;

    for(int i=0; i<8; i++){
   //  emg[i] = abs(emg[i]);

        // add emg value to /emg0 message
      EMG[i] = abs(reverseEmg-emg[i]);
      EMG[i] = map(EMG[i], -128, 128, emgMin, emgMax);
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
=======
>>>>>>> development

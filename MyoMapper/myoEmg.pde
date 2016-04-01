float[] EMG = new float[8];
float emgMin  = 0;
float emgMax = 1;

int intensityMIDI; //cc10
int[] emgMIDI = new int[8]; //cc11, cc12, cc13, cc14, cc15, cc16, cc17, cc18
float intensity = 0;  
float emgSum;

boolean emgOnOff = true;
  
void emgSend(){
    
   emgMin = avgEMG.getLowValue();
   emgMax = avgEMG.getHighValue();
      
      float emgSum = 0;

    for(int i=0; i<8; i++){
     emg[i] = abs(emg[i]);

     // add emg value to /emg0 message
      EMG[i] = abs(reverseEmg-emg[i]);
      EMG[i] = map(EMG[i], 0, 128, emgMin, emgMax);
      emgSum = EMG[i]+emgSum; // EMG sum for avg calculation    
     
      intensity = emgSum/8; // average calculation
      intensity = max(intensity, 0);
      intensity = min(intensity, 1); 
    }    

if (MIDI) {
      intensityMIDI = int(intensity*127);
      myBus.sendControllerChange(chMIDI, 10, intensityMIDI); // Send a 
      
      for (int i=0; 1<8; i++){
         myBus.sendControllerChange(chMIDI, 11+i, emgMIDI[i]);
        }
      }
     
   if(OpenSoundControl){  
    
     OscMessage Emg = new OscMessage("/emg");
     OscMessage emgAvg = new OscMessage("/emgAvg");   
          
     Emg.add(emg);
     emgAvg.add(intensity);
     oscP5.send(Emg, myRemoteLocation);
     oscP5.send(emgAvg, myRemoteLocation);
   }
}



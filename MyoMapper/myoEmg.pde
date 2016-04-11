float[] EMG = new float[8];
float emgMin  = 0;
float emgMax = 1;
int mavMIDI; //cc10
int[] emgMIDI = new int[8]; //cc1, cc2, cc3, cc4, cc5, cc6, cc7, cc8
float mav = 0;  
float emgSum;

boolean emgOnOff = true;
boolean mavOnOff = true;
  
void MAV(){
  emgSum = 0;
  emgMin = avgEMG.getLowValue();
  emgMax = avgEMG.getHighValue();

  for(int i=0; i<8; i++){
    emgSum = abs(emg[i])+emgSum;  
    }
  mav = emgSum*0.125;
  mav = map(mav, 0, 128, emgMin, emgMax);
  
  if(!reverseMAV) mav = abs(1-mav);
 
  mav = min(mav, 1);
  mav = max(mav, 0);
 
  if (MIDI) { 
    mavMIDI = int(mav*127);
    myBus.sendControllerChange(chMIDI, 9, mavMIDI);
    } 
    
  if(OpenSoundControl){
    OscMessage emgMAV = new OscMessage("/emgMav");   
    emgMAV.add(mav);
    oscP5.send(emgMAV, myRemoteLocation);
    }
} 

void EMG(){
  
  if(MIDI) {
    for (int i=0; i<8; i++){
      emgMIDI[i]= abs(emg[i]);
      myBus.sendControllerChange(chMIDI, i+1, emgMIDI[i]); 
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



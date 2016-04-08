int accSx, accSy, accSz = 0;
int[] accMIDI = new int[3];

boolean accOnOff=true;

void Acceleration(){
  
  if(MIDI){   
    accMIDI[0] = int(acceleration.x*0.00125318852828); // /(2*PI)*127
    accMIDI[1] = int(acceleration.y*0.00125318852828); // /(2*PI)*127
    accMIDI[2] = int(acceleration.z*0.00125318852828); // /(2*PI)*127
       
    for(int i=0; i<3; i++) myBus.sendControllerChange(chMIDI, 13+i, accMIDI[i]);
    }
      
  if(OpenSoundControl){  
    OscMessage acc = new OscMessage("/acc");
     
    acc.add(acceleration.x);
    acc.add(acceleration.y);
    acc.add(acceleration.z);
    
    oscP5.send(acc, myRemoteLocation); 
    }
}


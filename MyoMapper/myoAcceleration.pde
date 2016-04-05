int accSx, accSy, accSz = 0;
int accXMIDI, accYMIDI, accZMIDI; //cc4, cc5, cc6
boolean accOnOff=true;

void Acceleration(){
  
  if(MIDI){   
    accXMIDI = int(acceleration.x*0.00125318852828); // /(2*PI)*127
    accYMIDI = int(acceleration.y*0.00125318852828); // /(2*PI)*127
    accZMIDI = int(acceleration.z*0.00125318852828); // /(2*PI)*127
       
    myBus.sendControllerChange(chMIDI, 4, accXMIDI);
    myBus.sendControllerChange(chMIDI, 5, accYMIDI);
    myBus.sendControllerChange(chMIDI, 6, accZMIDI);
    }
      
  if(OpenSoundControl){  
    OscMessage acc = new OscMessage("/acc");
     
    acc.add(acceleration.x);
    acc.add(acceleration.y);
    acc.add(acceleration.z);
    
    oscP5.send(acc, myRemoteLocation); 
    }
}


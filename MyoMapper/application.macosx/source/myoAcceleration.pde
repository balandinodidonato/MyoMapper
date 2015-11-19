int accSx, accSy, accSz = 0;
int accXMIDI, accYMIDI, accZMIDI; //cc4, cc5, cc6

void scaleAcceleration(){
    accSx= int(acceleration.x*40.58451048843329); // scale acceleration.x (0-2PI) -> serial value (0-255)
    accSy= int(acceleration.y*40.58451048843329); // scale acceleration.x (0-2PI) -> serial value (0-255)
    accSz= int(acceleration.z*40.58451048843329); // scale acceleration.x (0-2PI) -> serial value (0-255)
}



void sendAcceleration(){
  
if(MIDI){   
     accXMIDI = int(acceleration.x/(2*PI)*127);
     accYMIDI = int(acceleration.y/(2*PI)*127);
     accZMIDI = int(acceleration.z/(2*PI)*127);
     
     myBus.sendControllerChange(chMIDI, 4, rollMIDI); // Send a Midi noteOn
     myBus.sendControllerChange(chMIDI, 5, pitchMIDI); // Send a Midi noteOn
     myBus.sendControllerChange(chMIDI, 6, yawMIDI); // Send a Midi noteOn
    }
    
if(OpenSoundControl){  
    OscMessage acc = new OscMessage("/acc");
    OscMessage accS = new OscMessage("/accS");
   
    acc.add(acceleration.x); //  0-2PI
    acc.add(acceleration.y); //  0-2PI
    acc.add(acceleration.z); //  0-2PI
 
    accS.add(accSx); // 0-255
    accS.add(accSy); // 0-255
    accS.add(accSz); // 0-255
        
   oscP5.send(acc, myRemoteLocation); 
   oscP5.send(accS, myRemoteLocation); 
}
}


boolean accOnOff=true;
float[] acc = new float[3];
int[] accMIDI = new int[3];


void Acceleration(){
  
  acc[0]=acceleration.x;
  acc[1]=acceleration.y;
  acc[2]=acceleration.z;

  if(MIDI){   
    for(int i=0; i<3; i++){
      accMIDI[i] = int(acc[i]*0.00125318852828); // /(2*PI)*127
      myBus.sendControllerChange(chMIDI, 13+i, accMIDI[i]);
      }
    }
      
  if(OpenSoundControl){  
    OscMessage acc = new OscMessage("/acc");
     
    acc.add(acceleration.x);
    acc.add(acceleration.y);
    acc.add(acceleration.z);
    
    oscP5.send(acc, myRemoteLocation); 
    }
}


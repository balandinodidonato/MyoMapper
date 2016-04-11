boolean gyroOnOff = true;
int[] gyroMIDI = new int[3];
float[] giro = new float[3];

void Gyro(){
  
  giro[0]=gyro.x;
  giro[1]=gyro.y;
  giro[2]=gyro.z;
  
  if(MIDI){ 
    for(int i=0; i<3; i++){  
      gyroMIDI[i] = int(giro[i]*0.127);
      myBus.sendControllerChange(chMIDI, 16+i, gyroMIDI[i]);
      }
    }

  if(OpenSoundControl){
    OscMessage Gyro = new OscMessage("/gyro");
     
    Gyro.add(gyro.x);
    Gyro.add(gyro.y);
    Gyro.add(gyro.z);
    oscP5.send(Gyro, myRemoteLocation);
    }
}

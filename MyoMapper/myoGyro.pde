int[] gyroMIDI = new int[3];
boolean gyroOnOff = true;

void Gyro(){
  if(MIDI){   
    gyroMIDI[0] = int(gyro.x*0.127);
    gyroMIDI[1] = int(gyro.y*0.127);
    gyroMIDI[2] = int(gyro.z*0.127);
       
    for(int i=0; i<3; i++) myBus.sendControllerChange(chMIDI, 16+i, gyroMIDI[i]);// Send a Midi noteOn
    }

  if(OpenSoundControl){
    OscMessage Gyro = new OscMessage("/gyro");
    Gyro.add(gyro.x);
    Gyro.add(gyro.y);
    Gyro.add(gyro.z);
    oscP5.send(Gyro, myRemoteLocation);
    }
}

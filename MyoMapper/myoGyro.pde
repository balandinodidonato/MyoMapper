int gyroXMIDI, gyroYMIDI, gyroZMIDI; //cc7, cc8, cc9
boolean gyroOnOff = true;

void sendGyro(){
  if(MIDI){   
     gyroXMIDI = int(gyro.x*0.127);
     gyroYMIDI = int(gyro.y*0.127);
     gyroYMIDI = int(gyro.z*0.127);
     
     myBus.sendControllerChange(chMIDI, 7, rollMIDI); // Send a Midi noteOn
     myBus.sendControllerChange(chMIDI, 8, pitchMIDI); // Send a Midi noteOn
     myBus.sendControllerChange(chMIDI, 9, yawMIDI); // Send a Midi noteOn
    }

if(OpenSoundControl){

    OscMessage Gyro = new OscMessage("/gyro");
   
    Gyro.add(gyro.x);
    Gyro.add(gyro.y);
    Gyro.add(gyro.z);
    oscP5.send(Gyro, myRemoteLocation);
 }
}

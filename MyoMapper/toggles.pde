Toggle revYawTgl;
Toggle revPitchTgl;
Toggle revRollTgl;
Toggle revEmgTgl;
Toggle OSCTgl;
Toggle MIDITgl;
Toggle emg01Tgl;
Toggle gyro01Tgl;
Toggle orientation01Tgl;
Toggle acc01Tgl;
Toggle pose01Tgl;


Numberbox MIDIPortNb;
Numberbox MIDIchannelNb;

int tglXsize = 60;
int tglYsize = 30;

int tglYawY, tglPitchY, tglRollY, tglEmgY, tglemgY, tglorientationOnOffY, tglgyroOnOffY, tglaccOnOffY, tglposeOnOffY;
int tglYawX, tglPitchX, tglRollX, tglEmgX, tglemgX, tglorientationOnOffX, tglgyroOnOffX, tglaccOnOffX, tglposeOnOffX;

int revYawTglX, revYawTglY, tglOSCY, tglMIDIY, nbMIDIportY = 0; // Reverse Yaw tgl
int revPitchTglX = 0; // Pitch tgl
int revRollTglX = 0; // Pitch tgl
int revEmgTglX = 0; // Pitch tgl
int tglMIDIX, tglOSCX, nbMIDIportX, nbMIDIchX, nbMIDIchY = 0;
float reverseYaw, reversePitch, reverseRoll, reverseEmg = 0;

void toggles(){
  
 tglYawX = (width/2)+40;  
 
 tglOSCY = tglMIDIY = nbMIDIportY = nbMIDIchY = tglemgY = height/12;
 tglYawY = tglPitchY = tglRollY = tglEmgY = int(height/7);
 tglemgY = height/3;
 tglorientationOnOffY = tglemgY + int(tglYsize*1.5);
 tglaccOnOffY = tglorientationOnOffY + int(tglYsize*1.5);
 tglgyroOnOffY = tglaccOnOffY + int(tglYsize*1.5);
 tglposeOnOffY = tglgyroOnOffY + int(tglYsize*1.5);

  tglPitchX = tglYawX + int(tglXsize*1.5);
  tglRollX = tglPitchX + int(tglXsize*1.5);
  tglemgX = tglRollX + int(tglXsize*1.5);
  tglEmgX = tglRollX + int(tglXsize*1.5);
  tglOSCX = tglYawX;
  tglMIDIX = tglPitchX;
  nbMIDIportX = tglRollX;
  nbMIDIchX = tglEmgX;
  tglemgX = tglorientationOnOffX = tglgyroOnOffX = tglaccOnOffX = tglposeOnOffX = nbMIDIchX + int(tglXsize*2);
  
   // create a toggle and change the default look to a (on/off) switch look
 pose01Tgl = cp5.addToggle("POSE")
     .setPosition(tglposeOnOffX,tglposeOnOffY)
     .setSize(tglXsize,tglYsize)
     .setValue(false)
     .setMode(ControlP5.SWITCH)
     ;
 
 acc01Tgl = cp5.addToggle("ACC")
     .setPosition(tglaccOnOffX,tglaccOnOffY)
     .setSize(tglXsize,tglYsize)
     .setValue(false)
     .setMode(ControlP5.SWITCH)
     ;

 gyro01Tgl = cp5.addToggle("GYRO")
     .setPosition(tglgyroOnOffX,tglgyroOnOffY)
     .setSize(tglXsize,tglYsize)
     .setValue(false)
     .setMode(ControlP5.SWITCH)
     ;
 
 orientation01Tgl = cp5.addToggle("ORIENT")
     .setPosition(tglorientationOnOffX,tglorientationOnOffY)
     .setSize(tglXsize,tglYsize)
     .setValue(false)
     .setMode(ControlP5.SWITCH)
     ;

 emg01Tgl = cp5.addToggle("EMG")
     .setPosition(tglemgX,tglemgY)
     .setSize(tglXsize,tglYsize)
     .setValue(false)
     .setMode(ControlP5.SWITCH)
     ;


 revYawTgl = cp5.addToggle("revYaw")
     .setPosition(tglYawX,tglYawY)
     .setSize(tglXsize,tglYsize)
     .setValue(true)
     .setMode(ControlP5.SWITCH)
     ;

 revPitchTgl = cp5.addToggle("revPitch")
     .setPosition(tglPitchX,tglPitchY)
     .setSize(tglXsize,tglYsize)
     .setValue(true)
     .setMode(ControlP5.SWITCH)
     ;
     
 revRollTgl = cp5.addToggle("revRoll")
     .setPosition(tglRollX,tglRollY)
     .setSize(tglXsize,tglYsize)
     .setValue(true)
     .setMode(ControlP5.SWITCH)
     ;
  
 revEmgTgl = cp5.addToggle("revEmg")
     .setPosition(tglEmgX,tglEmgY)
     .setSize(tglXsize,tglYsize)
     .setValue(true)
     .setMode(ControlP5.SWITCH)
     ;
     
 OSCTgl = cp5.addToggle("OSC")
     .setPosition(tglOSCX,tglOSCY)
     .setSize(tglXsize,tglYsize)
     .setValue(false)
     .setMode(ControlP5.SWITCH)
     ;
     
 MIDITgl = cp5.addToggle("MIDI")
     .setPosition(tglMIDIX,tglOSCY)
     .setSize(tglXsize,tglYsize)
     .setValue(true)
     .setMode(ControlP5.SWITCH)
     ;
     

  MIDIPortNb = cp5.addNumberbox("MIDI_PORT")
     .setPosition(nbMIDIportX,nbMIDIportY)
     .setSize(tglXsize,tglYsize)
     .setValue(1)
     .setScrollSensitivity(0.5)
     .setMultiplier(1)
     .setMin(0)
     .setMax(10)
     ;
     
  MIDIchannelNb = cp5.addNumberbox("MIDI_CH")
     .setPosition(nbMIDIchX,nbMIDIchY)
     .setSize(tglXsize,tglYsize)
     .setValue(1)
     .setScrollSensitivity(0.5)
     .setMultiplier(1)
     .setMin(0)
     .setMax(16)
     ;

}

void revYaw(boolean theFlag) {
  if(!theFlag) reverseYaw = 1;
   else  reverseYaw = 0;
}

void revPitch(boolean theFlag) {
  if(!theFlag) reversePitch = 1;
  else  reversePitch = 0;
}

void revRoll(boolean theFlag) {
  if(!theFlag) reverseRoll = 1;
  else  reverseRoll = 0;
}

void revEmg(boolean theFlag) {
  if(!theFlag) reverseEmg = 1;
  else  reverseEmg = 0;
}

void POSE(boolean theFlag) {
  if(theFlag) {poseOnOff = false;}
  else {poseOnOff = true;}
}

void ACC(boolean theFlag) {
  if(theFlag) {accOnOff = false;}
  else {accOnOff = true;}
}

void ORIENT(boolean theFlag) {
  if(theFlag) {orientOnOff = false;}
  else {orientOnOff = true;}
}

void GYRO(boolean theFlag) {
  if(theFlag) {gyroOnOff = false;}
  else {gyroOnOff = true;}
}

void EMG(boolean theFlag) {
  if(theFlag) {emgOnOff = false;}
  else {emgOnOff = true;}
}

void OSC(boolean theFlag) {
  if(theFlag) {OpenSoundControl = false;}
  else {OpenSoundControl = true;}
}

void MIDI(boolean theFlag) {
  if(theFlag) {MIDI = false;}
  else {MIDI = true;}
}

void MIDI_PORT(int value) { 
  portMIDI = value;
  setUpMIDI();
  }

void MIDI_CH(int value) { 
  chMIDI = value;
  }



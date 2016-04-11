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
Toggle mav01Tgl;
Toggle waveform01Tgl;

Numberbox MIDIPortNb;
Numberbox MIDIchannelNb;

int tglXsize = int(width*4);
int tglYsize = int(width*2);

int tglYawY, tglPitchY, tglRollY, tglEmgY, tglemgY, tglorientationOnOffY, tglgyroOnOffY, tglaccOnOffY, tglposeOnOffY, tglmavOnOffY, tglwaveformOnOffY;
int tglYawX, tglPitchX, tglRollX, tglEmgX, tglemgX, tglorientationOnOffX, tglgyroOnOffX, tglaccOnOffX, tglposeOnOffX, tglmavOnOffX, tglwaveformOnOffX;

int revYawTglX, revYawTglY, tglOSCY, tglMIDIY, nbMIDIportY = 0; // Reverse Yaw tgl
int revPitchTglX = 0; // Pitch tgl
int revRollTglX = 0; // Pitch tgl
int revEmgTglX = 0; // Pitch tgl
int tglMIDIX, tglOSCX, nbMIDIportX, nbMIDIchX, nbMIDIchY = 0;
boolean reverseMAV, reverseYaw, reversePitch, reverseRoll = false;

int distanceXtoggles, distanceYtoggles;

void toggles(){

   cp5 = new ControlP5(this);

  tglXsize = int(width*0.06);
  tglYsize = int(height*0.035);
  distanceXtoggles = int(tglXsize*1.5);
  distanceYtoggles = int(tglYsize*2.25);
 
  tglOSCY = tglMIDIY = nbMIDIportY = nbMIDIchY = tglemgY = tglwaveformOnOffY = int(height*0.09);
  tglYawY = tglPitchY = tglRollY = tglEmgY = tglOSCY + distanceYtoggles;
 
  tglYawX = int(width*0.5)+int(width*0.03);
  tglPitchX = tglYawX + distanceXtoggles;
  tglRollX = tglPitchX + distanceXtoggles;
  tglemgX = tglRollX + distanceXtoggles;
  tglEmgX = tglRollX + distanceXtoggles;
  tglOSCX = tglYawX;
  tglMIDIX = tglPitchX;
  nbMIDIportX = tglRollX;
  nbMIDIchX = tglEmgX;
   
  tglemgX = tglorientationOnOffX = tglgyroOnOffX = tglaccOnOffX = tglposeOnOffX = tglmavOnOffX = tglwaveformOnOffX = int(width*0.91);

  tglemgY = int(height*0.42);
  tglmavOnOffY =  tglemgY + distanceYtoggles;
  tglorientationOnOffY = tglmavOnOffY + distanceYtoggles;
  tglaccOnOffY = tglorientationOnOffY + distanceYtoggles;
  tglgyroOnOffY = tglaccOnOffY + distanceYtoggles;
  tglposeOnOffY = tglgyroOnOffY + distanceYtoggles;
  
   // create a toggle and change the default look to a (on/off) switch look
  waveform01Tgl = cp5.addToggle("WAVEFORM")
    .setPosition(tglwaveformOnOffX,tglwaveformOnOffY)
    .setSize(tglXsize,tglYsize)
    .setValue(false)
    .setMode(ControlP5.SWITCH)
    ;

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

  mav01Tgl = cp5.addToggle("MAV_")
    .setPosition(tglmavOnOffX,tglmavOnOffY)
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
  
  revEmgTgl = cp5.addToggle("revMAV")
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
  reverseYaw = theFlag;
}

void revPitch(boolean theFlag) {
  reversePitch = theFlag;
}

void revRoll(boolean theFlag) {
  reverseRoll = theFlag;
}

void revMAV(boolean theFlag) {
  reverseMAV = theFlag;
}

void WAVEFORM(boolean theFlag) {
  if(theFlag) {waveformOnOff = false;}
  else {waveformOnOff = true;}
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

void MAV(boolean theFlag) {
  if(theFlag) {mavOnOff = false;}
  else {mavOnOff = true;}
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

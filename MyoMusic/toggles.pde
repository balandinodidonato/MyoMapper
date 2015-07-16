Toggle revYawTgl;
Toggle revPitchTgl;
Toggle revRollTgl;
Toggle revEmgTgl;
Toggle OSCTgl;
Toggle MIDITgl;
Numberbox MIDIPortNb;
Numberbox MIDIchannelNb;

int tglXsize = 60;
int tglYsize = 30;

int tglYawY, tglPitchY, tglRollY, tglEmgY;
int tglYawX, tglPitchX, tglRollX, tglEmgX;

int revYawTglX, revYawTglY, tglOSCY, tglMIDIY, nbMIDIportY = 0; // Reverse Yaw tgl
int revPitchTglX = 0; // Pitch tgl
int revRollTglX = 0; // Pitch tgl
int revEmgTglX = 0; // Pitch tgl
int tglMIDIX, tglOSCX, nbMIDIportX, nbMIDIchX, nbMIDIchY = 0;
float reverseYaw, reversePitch, reverseRoll, reverseEmg = 0;

void toggles(){
  
    
 tglYawX = width/2+40;  
 
 tglOSCY = tglMIDIY = nbMIDIportY = nbMIDIchY = height/11;
 tglYawY = tglPitchY = tglRollY = tglEmgY = int(height/6.5);

  tglPitchX = tglYawX + tglXsize*2;
  tglRollX = tglPitchX + tglXsize*2;
  tglEmgX = tglRollX + tglXsize*2;
  tglOSCX = tglYawX;
  tglMIDIX = tglPitchX;
  nbMIDIportX = tglRollX;
  nbMIDIchX = tglEmgX;
  
   // create a toggle and change the default look to a (on/off) switch look
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

//void revYaw() {
 // reverseYaw = 1-revYawTgl.getValue();
//}

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



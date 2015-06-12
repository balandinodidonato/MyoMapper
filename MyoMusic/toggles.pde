int tglXsize = 60;
int tglYsize = 30;

int tglYawY, tglPitchY, tglRollY, tglEmgY;
int tglYawX, tglPitchX, tglRollX, tglEmgX;

int revYawTglX, revYawTglY, reverseYaw, tglOSCY, tglMIDIY, nbMIDIportY = 0; // Reverse Yaw tgl
int revPitchTglX, reversePitch = 0; // Pitch tgl
int revRollTglX, reverseRoll = 0; // Pitch tgl
int revEmgTglX, reverseEmg = 0; // Pitch tgl
int tglMIDIX, tglOSCX, nbMIDIportX, nbMIDIchX, nbMIDIchY = 0;

void toggles(){
  
 cp5 = new ControlP5(this);
    
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
  cp5.addToggle("revYaw")
     .setPosition(tglYawX,tglYawY)
     .setSize(tglXsize,tglYsize)
     .setValue(true)
     .setMode(ControlP5.SWITCH)
     ;

  cp5.addToggle("revPitch")
     .setPosition(tglPitchX,tglPitchY)
     .setSize(tglXsize,tglYsize)
     .setValue(true)
     .setMode(ControlP5.SWITCH)
     ;
     
  cp5.addToggle("revRoll")
     .setPosition(tglRollX,tglRollY)
     .setSize(tglXsize,tglYsize)
     .setValue(true)
     .setMode(ControlP5.SWITCH)
     ;
  
    cp5.addToggle("revEmg")
     .setPosition(tglEmgX,tglEmgY)
     .setSize(tglXsize,tglYsize)
     .setValue(true)
     .setMode(ControlP5.SWITCH)
     ;
     
   cp5.addToggle("OSC")
     .setPosition(tglOSCX,tglOSCY)
     .setSize(tglXsize,tglYsize)
     .setValue(false)
     .setMode(ControlP5.SWITCH)
     ;
     
  cp5.addToggle("MIDI")
     .setPosition(tglMIDIX,tglOSCY)
     .setSize(tglXsize,tglYsize)
     .setValue(true)
     .setMode(ControlP5.SWITCH)
     ;

  cp5.addNumberbox("midiPort")
     .setPosition(nbMIDIportX,nbMIDIportY)
     .setSize(tglXsize,tglYsize)
     .setValue(3)
     .setScrollSensitivity(2)
     .setMin(0)
     .setMax(16)
     ;
     
  cp5.addNumberbox("midiChannel")
     .setPosition(nbMIDIchX,nbMIDIchY)
     .setSize(tglXsize,tglYsize)
     .setValue(1)
     .setScrollSensitivity(2)
     .setMin(0)
     .setMax(16)
     ;

}

void revYaw(boolean theFlag) {
  if(theFlag==false) {reverseYaw =1;}
  else {reverseYaw=0;}
}

void revPitch(boolean theFlag) {
  if(theFlag==false) {reversePitch =1;}
  else {reversePitch=0;}
}

void revRoll(boolean theFlag) {
  if(theFlag==false) {reverseRoll =1;}
  else {reverseRoll=0;}
}

void revEmg(boolean theFlag) {
  if(theFlag==false) {reverseEmg = 128;}
  else {reverseEmg = 0;}
}


void OSC(boolean theFlag) {
  if(theFlag==true) {OpenSoundControl = false;}
  else {OpenSoundControl = true;}
}

void MIDI(boolean theFlag) {
  if(theFlag==true) {MIDI = false;}
  else {MIDI = true;}
}

void midiPort(int value) { 
  portMIDI = value;
  setUpMIDI();
  }

void midiChannel(int Mch) { 
  chMIDI = Mch;
  }



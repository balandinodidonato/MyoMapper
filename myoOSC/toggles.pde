
int tglXsize = 60;
int tglYsize = 30;

int tglYawY, tglPitchY, tglRollY, tglEmgY;
int tglYawX, tglPitchX, tglRollX, tglEmgX;


int revYawTglX, revYawTglY, reverseYaw = 0; // Reverse Yaw tgl
int revPitchTglX, reversePitch = 0; // Pitch tgl
int revRollTglX, reverseRoll = 0; // Pitch tgl
int revEmgTglX, reverseEmg = 0; // Pitch tgl



void toggles(){
  
 cp5 = new ControlP5(this);
    
 tglYawX = width/2+40;  
 
 tglYawY = tglPitchY = tglRollY = tglEmgY = height/6;

  tglPitchX = tglYawX + tglXsize*2;
  tglRollX = tglPitchX + tglXsize*2;
  tglEmgX = tglRollX + tglXsize*2;
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

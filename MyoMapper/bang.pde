
int bangSize;

int bngYawX, bngPitchX, bngRollX;
int bngYawY, bngPitchY, bngRollY;

void bangs(){
      
  cp5 = new ControlP5(this);

  bangSize = tglXsize;
  bngYawY = bngPitchY = bngRollY = bngYawX = tglYawY+tglXsize;
    
  bngYawX = tglYawX;
  bngPitchX = tglPitchX;
  bngRollX = tglRollX;
    
  cp5.addBang("Cent. YAW")
    .setPosition(bngYawX, bngYawY)
    .setSize(bangSize, bangSize)
    .setId(0)
    ;
  
  cp5.addBang("Cent. PITCH")
    .setPosition(bngPitchX, bngPitchY)
    .setSize(bangSize, bangSize)
    .setId(1)
    ; 
  
  cp5.addBang("Cent. ROLL")
    .setPosition(bngRollX, bngRollY)
    .setSize(bangSize, bangSize)
    .setId(2)
    ;       
}

public void controlEvent(ControlEvent theEvent) {
  if (theEvent.controller().id() == 2) ORx=orX;
  else if (theEvent.controller().id() == 1) ORy=orY;
  else if (theEvent.controller().id() == 0) ORz=orZ;
}

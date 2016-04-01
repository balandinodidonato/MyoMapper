Range rYaw;
Range rPitch;
Range rRoll;
Range avgEMG;

int sYawX, sPitchX, sRollX, sEmgX;
int sYawXsize, sPitchXsize, sRollXsize, sEmgXsize;
int sYawY, sPitchY, sRollY, sEmgY;
int sYawYsize, sPitchYsize, sRollYsize, sEmgYsize;

int rYawX, rPitchX, rRollX, rEmgX;
int rYawXsize, rPitchXsize, rRollXsize, rEmgXsize;
int rYawY, rPitchY, rRollY, rEmgY;
int rYawYsize, rPitchYsize, rRollYsize, rEmgYsize;

void rescale() {
  
  rYawXsize = rPitchXsize = rRollXsize = rEmgXsize = sYawXsize = sPitchXsize = sRollXsize = sEmgXsize = width/4; // X size sliders
  rYawYsize = rPitchYsize = rRollYsize = rEmgYsize = sYawYsize = sPitchYsize = sRollYsize = sEmgYsize = height/25;  // Y Size
  sYawX = sPitchX = sRollX = sEmgX = rYawX = rPitchX = rRollX = rEmgX = tglYawX; // x margins
  
  sYawY = height/3;
  sPitchY = sYawY+(sYawYsize*3);
  sRollY = sYawY+(sYawYsize*6);
  sEmgY = sYawY+(sYawYsize*9);
  
  rYawY = sYawY+sYawYsize;
  rPitchY = sPitchY+rYawYsize;
  rRollY = sRollY+rYawYsize;
  rEmgY = sEmgY+rEmgYsize;


  // cp5 = new ControlP5(this);

  rYaw = cp5.addRange("Range Yaw")
             // disable broadcasting since setRange and setRangeValues will trigger an event
             .setBroadcast(false) 
             .setPosition(rYawX, rYawY)
             .setSize(rYawXsize, rYawYsize)
             .setHandleSize(20)
             .setRange(-2,2)
             .setRangeValues(0,2)
             // after the initialization we turn broadcast back on again
             .setBroadcast(true)
             .setColorForeground(color(255,40))
             .setColorBackground(color(255,40)) 
             .setHighValue(1)
             .setLowValue(0)
             ;
 
   rPitch = cp5.addRange("Range Pitch")
             // disable broadcasting since setRange and setRangeValues will trigger an event
             .setBroadcast(false) 
             .setPosition(rPitchX, rPitchY)
             .setSize(rPitchXsize,rPitchYsize)
             .setHandleSize(20)
             .setRange(-2,2)
             .setRangeValues(0,2)
             // after the initialization we turn broadcast back on again
             .setBroadcast(true)
             .setColorForeground(color(255,40))
             .setColorBackground(color(255,40))  
             .setHighValue(1)
             .setLowValue(0)
             ;
             
    rRoll = cp5.addRange("Range Roll")
             // disable broadcasting since setRange and setRangeValues will trigger an event
             .setBroadcast(false) 
             .setPosition(rRollX, rRollY)
             .setSize(rRollXsize,rRollYsize)
             .setHandleSize(20)
             .setRange(-2,2)
             .setRangeValues(-2,2)
             // after the initialization we turn broadcast back on again
             .setBroadcast(true)
             .setColorForeground(color(255,40))
             .setColorBackground(color(255,40))  
             .setHighValue(1)
             .setLowValue(0)
             ; 
    
        avgEMG = cp5.addRange("Range EMG")
             // disable broadcasting since setRange and setRangeValues will trigger an event
             .setBroadcast(false) 
             .setPosition(rEmgX, rEmgY)
             .setSize(rEmgXsize, rEmgYsize)
             .setHandleSize(20)
             .setRange(0,4)
             .setRangeValues(0,2)
             // after the initialization we turn broadcast back on again
             .setBroadcast(true)
             .setColorForeground(color(255,40))
             .setColorBackground(color(255,40))  
             .setHighValue(1)
             .setLowValue(0)
             ;  
                  
  noStroke();  
}

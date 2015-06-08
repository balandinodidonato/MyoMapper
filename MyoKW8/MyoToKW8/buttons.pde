Tgl revYawButton;
Tgl revPitchButton;
Tgl revRollButton;
Tgl revEmgButton;

Bng centYawButton;
Bng centPitchButton;
Bng centRollButton;

int revYawTglX, revYawTglSize, revYawTglY, reverseYaw = 0; // Reverse Yaw tgl
int revPitchTglX, revPitchTglY, revPitchTglSize, reversePitch = 0; // Pitch tgl
int revRollTglX, revRollTglY, revRollTglSize, reverseRoll = 0; // Pitch tgl
int revEmgTglX, revEmgTglY, revEmgTglSize, reverseEmg = 0; // Pitch tgl

int centYawBngX, centYawBngY, centYawBngSize, centreYaw = 0; // Centre Yaw bng
int centPitchBngX, centPitchBngY, centPitchBngSize, centrePitch = 0; // Centre Pitch bng
int centRollBngX, centRollBngY, centRollBngSize, centreRoll = 0; // Centre Roll bng


void setUpButtons(){
  // Tgl settings
  revYawTglX = width/2+width/7;
  revYawTglSize = revPitchTglSize = revRollTglSize = revEmgTglSize = 50;
  revYawTglY = revPitchTglY = revRollTglY = revEmgTglY = 200;
  revPitchTglX = revYawTglX + revYawTglSize +30;
  revRollTglX = revPitchTglX + revPitchTglSize +30;
  revEmgTglX = revRollTglX + revPitchTglSize +30;


  revYawButton = new Tgl(revYawTglX, revYawTglY, revYawTglSize);
  revPitchButton = new Tgl(revPitchTglX, revPitchTglY, revPitchTglSize);
  revRollButton = new Tgl(revRollTglX, revRollTglY, revRollTglSize);
  revEmgButton = new Tgl(revEmgTglX, revEmgTglY, revEmgTglSize);


 // Bng settings
  centYawBngX = revYawTglX;
  centYawBngSize = centPitchBngSize = centRollBngSize = revYawTglSize = revEmgTglSize;
  centPitchBngX = centYawBngX + centYawBngSize +30;
  centRollBngX = centPitchBngX + centPitchBngSize +30;
  centYawBngY = centPitchBngY = centRollBngY = revYawTglY+revYawTglSize+10;

  centYawButton = new Bng(centYawBngX, centYawBngY, centYawBngSize);
  centPitchButton = new Bng(centPitchBngX, centPitchBngY, centPitchBngSize);
  centRollButton = new Bng(centRollBngX, centRollBngY, centRollBngSize);
}


void buttons(){
  
  // run buttons
revYawButton.run();
revPitchButton.run();
revRollButton.run();
revEmgButton.run();

centYawButton.run();
centPitchButton.run();
centRollButton.run();

// button state pic
if (revYawButton.status){reverseYaw=1;}
else if (!revYawButton.status){reverseYaw=0;}

if (revPitchButton.status){reversePitch=1;}
else if (!revPitchButton.status){reversePitch=0;}

if (revRollButton.status){reverseRoll=1;}
else if (!revRollButton.status){reverseRoll=0;}

if (revEmgButton.status){reverseEmg=255;}
else if (!revEmgButton.status){reverseEmg=0;}

if (centRollButton.status){ORx=orX;}
if (centPitchButton.status){ORy=orY;}
if (centYawButton.status){ORz=orZ;}

}

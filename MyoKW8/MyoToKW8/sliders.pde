Slider sliderYaw;
Slider sliderPitch;
Slider sliderRoll;
Slider sliderEmg;

void setUpSliders(){
   sliderYaw = new Slider(centYawBngX, centYawBngY+centYawBngSize+20, revYawTglSize, 255);
   sliderPitch = new Slider(centPitchBngX, centPitchBngY+centPitchBngSize+20, revYawTglSize, 255);
   sliderRoll = new Slider(centRollBngX, centRollBngY+centRollBngSize+20, revYawTglSize, 255);
   sliderEmg = new Slider(revEmgTglX, centRollBngY+centRollBngSize+20, revYawTglSize, 255);

}



void runSliders(){
    

sliderRoll.bar = roll;
sliderPitch.bar = pitch;
sliderYaw.bar = yaw;
sliderEmg.bar = intensity; 

sliderRoll.run();
sliderPitch.run();
sliderYaw.run();
sliderEmg.run();

}

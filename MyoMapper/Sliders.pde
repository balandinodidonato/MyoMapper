Slider yawSlider;
Slider pitchSlider;
Slider rollSlider;
Slider emgSlider;

void setupSliders(){
 // cp5 = new ControlP5(this);

  yawSlider = cp5.addSlider("yawSlider")
              .setPosition(sYawX, sYawY)
              .setSize(sYawXsize,sYawYsize)
              .setRange(0,1)
              .setSliderMode(Slider.FLEXIBLE)
              ;

  pitchSlider = cp5.addSlider("pitchSlider")
     .setPosition(sPitchX, sPitchY)
     .setSize(sPitchXsize,sPitchYsize)
     .setRange(0,1)
     .setSliderMode(Slider.FLEXIBLE)

     ;
     
  rollSlider = cp5.addSlider("rollSlider")
     .setPosition(sRollX, sRollY)
     .setSize(sRollXsize,sRollYsize)
     .setRange(0,1)
     .setSliderMode(Slider.FLEXIBLE)

     ;     

  emgSlider = cp5.addSlider("emgSlider")
     .setPosition(sEmgX, sEmgY)
     .setSize(sEmgXsize,sEmgYsize)
     .setRange(0,1)
      .setSliderMode(Slider.FLEXIBLE)

     ; 
 
}

void updateSliders(){
    yawSlider.setValue(yaw);
    pitchSlider.setValue(pitch);
    rollSlider.setValue(roll);
    emgSlider.setValue(intensity);
}

Slider yawSlider;
Slider pitchSlider;
Slider rollSlider;
Slider mavSlider;

void setupSliders(){
 // cp5 = new ControlP5(this);

  yawSlider = cp5.addSlider("Yaw")
              .setPosition(sYawX, sYawY)
              .setSize(sYawXsize,sYawYsize)
              .setRange(0,1)
              .setSliderMode(Slider.FLEXIBLE)
              ;

  pitchSlider = cp5.addSlider("Pitch")
     .setPosition(sPitchX, sPitchY)
     .setSize(sPitchXsize,sPitchYsize)
     .setRange(0,1)
     .setSliderMode(Slider.FLEXIBLE)

     ;
     
  rollSlider = cp5.addSlider("Roll")
     .setPosition(sRollX, sRollY)
     .setSize(sRollXsize,sRollYsize)
     .setRange(0,1)
     .setSliderMode(Slider.FLEXIBLE)

     ;     

  mavSlider = cp5.addSlider("MAV")
     .setPosition(sEmgX, sEmgY)
     .setSize(sEmgXsize,sEmgYsize)
     .setRange(0,1)
      .setSliderMode(Slider.FLEXIBLE)

     ; 
 
}

void updateSliders(){
    if(orientOnOff){
      yawSlider.setValue(yaw);
      pitchSlider.setValue(pitch);
      rollSlider.setValue(roll);
      }
    if(mavOnOff)mavSlider.setValue(mav);
  }

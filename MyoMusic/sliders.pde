void sliders(){
  cp5 = new ControlP5(this);

  yMin = rYaw.getLowValue();
  yMax = rYaw.getHighValue();

  pMin = rPitch.getLowValue();
  pMax = rPitch.getHighValue();
  
  rMin = rRoll.getLowValue();
  rMax = rRoll.getHighValue();

  emgMin = avgEMG.getLowValue();
  emgMax = avgEMG.getHighValue();


  cp5.addSlider("yawSlider")
              .setPosition(sYawX, sYawY)
              .setSize(sYawXsize,sYawYsize)
              .setRange(0,1)
              .setValue(yaw)
            //  .setNumberOfTickMarks(100)
              .setSliderMode(Slider.FLEXIBLE)
              ;

  cp5.addSlider("pitchSlider")
     .setPosition(sPitchX, sPitchY)
     .setSize(sPitchXsize,sPitchYsize)
     .setRange(0,1)
     .setValue(pitch)
     .setSliderMode(Slider.FLEXIBLE)

     ;
     
  cp5.addSlider("rollSlider")
     .setPosition(sRollX, sRollY)
     .setSize(sRollXsize,sRollYsize)
     .setRange(0,1)
     .setValue(roll)
     .setSliderMode(Slider.FLEXIBLE)

     ;     

  cp5.addSlider("emgSlider")
     .setPosition(sEmgX, sEmgY)
     .setSize(sEmgXsize,sEmgYsize)
     .setRange(0,1)
     .setValue(intensity)
      .setSliderMode(Slider.FLEXIBLE)

     ; 
 
}

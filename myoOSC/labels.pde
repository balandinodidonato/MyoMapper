void labels(){
   noStroke();
   fill(#ffb600);   

   textSize(35);
  text("MyoToOSC", width/2+width/8,height/20);

   textSize(15);
   text("MyoToOSC send Myo Data at the port 5432.", sYawX, height/20+height/30);


   noFill();
   textSize(28);
   
   
   // title
      
   // graph
   text("EMG 1", 10, 35);
   text("EMG 2", 10, 85);
   text("EMG 3", 10, 135);
   text("EMG 4", 10, 185);
   text("EMG 5", 10, 235);
   text("EMG 6", 10, 285);
   text("EMG 7", 10, 335);
   text("EMG 8", 10, 385);
   text("YAW", 10, 435);
   text("PITCH", 10, 485);
   text("ROLL", 10, 535);
   text("ACC X", 10, 585);
   text("ACC Y", 10, 635);
   text("ACC Z", 10, 685);
   text("GYR X", 10, 735);
   text("GYR Y", 10, 785);
   text("GYR Z", 10, 835);
   
   // control pannel
   // data control
   
   textSize(25);

   textSize(20);
   textSize(28);
   text("POSE: "+pose, width-cons.width,height-cons.height-height/22); 
   
   fill(#1D4383);
   textSize(15);
   text("Balandino Di Donato 2015", width-cons.width/1.55,height-height/100); 

   

   noFill();
   
   
}

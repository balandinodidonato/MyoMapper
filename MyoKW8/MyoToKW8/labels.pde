void labels(){
   noStroke();
   fill(#ffb600);   

   textSize(35);
  text("MyoToKW8", width/2+cons.width/3,40);

   textSize(15);
   text("MyoToKW8 is an appliation which allows the user to drive a K-Array KW8", width-cons.width, 65);
   text("speakers, using the Myo Armband and the K-Array KW8 manager.", width-cons.width, 85);
   text("This application Myo Data trough OSC at the port 5432.", width-cons.width, 105);


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

   text("- -  DATA CONTROL  - - ", revYawTglX-revYawTglSize+20, revYawTglY-50);
   textSize(20);
   text("YAW", revYawTglX, revYawTglY-20);
   text("PITCH", revPitchTglX-7, revPitchTglY-20);
   text("ROLL", revRollTglX, revRollTglY-20);
   text("EMG", revEmgTglX, revRollTglY-20);
   text("REV", revYawTglX-revYawTglSize-20, revYawTglY+(revYawTglSize/2));
   text("CENT", revYawTglX-revYawTglSize-20, centYawBngY+(centYawBngSize/1.5));
   textSize(28);
   text("POSE: "+pose, revYawTglX-revYawTglSize-60, centRollBngY+centRollBngSize+350); 

   textSize(15);
   
   

   noFill();
   
   
}

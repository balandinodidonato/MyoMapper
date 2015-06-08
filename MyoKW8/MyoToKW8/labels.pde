void labels(){

   textSize(30);
   fill(#ffb600);
   
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
   text("ROLL", 10, 435);
   text("PITCH", 10, 485);
   text("YAW", 10, 535);
   text("ACC X", 10, 585);
   text("ACC Y", 10, 635);
   text("ACC Z", 10, 685);
   text("GYRO X", 10, 735);
   text("GYRO Y", 10, 785);
   text("GYRO Z", 10, 835);
   
   // control pannel
   // data control
   
   text("- DATA CONTROL -", revYawTglX-revYawTglSize+20, revYawTglY-70);
   textSize(20);
   text("YAW", revYawTglX, revYawTglY-20);
   text("PITCH", revPitchTglX-7, revPitchTglY-20);
   text("ROLL", revRollTglX, revRollTglY-20);
   text("EMG", revEmgTglX, revRollTglY-20);
   text("REV", revYawTglX-revYawTglSize-20, revYawTglY+(revYawTglSize/2));
   text("CENT", revYawTglX-revYawTglSize-20, centYawBngY+(centYawBngSize/1.5));
   text("POSE: "+pose, revYawTglX-revYawTglSize-20, centRollBngY+centRollBngSize+350); 

   noFill();
}

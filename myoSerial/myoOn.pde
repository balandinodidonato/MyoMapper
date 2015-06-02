// ----------------------------------------------------------
int orX = 0;
int orY = 0;
int orZ = 0;

int posX = 0;
int posY = 0;
int posZ = 0;


void myoOn(Myo.Event event, Device myo, long timestamp) {
    
  switch(event) {
  case PAIR:
    println("myoOn PAIR");
    break;
  case UNPAIR:
    println("myoOn UNPAIR");
    break;
  case CONNECT:
    println("myoOn CONNECT");
    break;
  case DISCONNECT:
    println("myoOn DISCONNECT");
    break;
  case ARM_SYNC:
    println("myoOn ARM_SYNC");
   
    break;
  case ARM_UNSYNC:
    println("myoOn ARM_UNSYNC");
    break;

  case POSE:
  //    println("myoOn POSE
  String pose= myo.getPose();

  if (pose == "FIST"){
        posX = orX;
        posY = orZ;
        posZ = orZ; 
       }
    
  else if (pose == "WAVE_IN"){
        posX = 64;
        posY = 64;
        posZ = 64;
        }
   else if (pose == "WAVE_OUT"){
        posX = 191;
        posY = 191;
        posZ = 191;
        }
   else if (pose == "FINGERS_SPREAD"){
        posX = orX;
        posY = orZ;
        posZ = orZ;      
       }
  else if (pose == "DOUBLE_TAP"){
        posX = orX;
        posY = orZ;
        posZ = orZ;
        }
  else if (pose == "REST"){
        posX = orX;
        posY = orZ;
        posZ = orZ;  
        }

  else if (pose == "UNKNOWN"){
       posX = orX;
       posY = orZ;
       posZ = orZ;
        }
  println("posX: "+posX+"    orY: "+posY+"    posZ: "+posZ);
  break;

     
  case ORIENTATION: //orientation OWL
    //myo.getPose()
  
    // println("myoOn ORIENTATION");
     PVector orientation = myo.getOrientation();
   //   println("orientation" + acceleration.x + " " + acceleration.y + " " + acceleration.z);
   orX = int(orientation.x * 255);
   orY = int(orientation.y * 255);
   orZ = int(orientation.z * 255);
    break;
 
  case ACCELEROMETER:
    // println("myoOn ACCELEROMETER");
      PVector acceleration = myo.getAccelerometer();
   //   println("acceleration" + acceleration.x + " " + acceleration.y + " " + acceleration.z); 
    int accX = int(acceleration.x * 40.58451048843329);
    int accY = int(acceleration.y * 40.58451048843329);
    int accZ = int(acceleration.z * 40.58451048843329);
   
    break;
 
  case GYROSCOPE:
    // println("myoOn GYROSCOPE");
    // PVector gyro = myo.getGyroscope();
    //  println("acceleration" + acceleration.x + " " + acceleration.y + " " + acceleration.z);
   
    break;
 
  case RSSI:
//    println("myoOn RSSI");
    break;
 
  case EMG:
      int emg[] = myo.getEmg();
      EMG[0] = emg[0]+128;
      EMG[1] = emg[1]+128;
      EMG[2] = emg[2]+128;
      EMG[3] = emg[3]+128;
      EMG[4] = emg[4]+128;
      EMG[5] = emg[5]+128;
      EMG[6] = emg[6]+128;
      EMG[7] = emg[7]+128;
        
      int avg = 0;
      int emgSum = 0;

      for (int i=0; i<8; i++) {emgSum = EMG[i] + emgSum;}
      avg = int(emgSum/8);
      println("Intesity: "+avg);
      // the value sum will gives the intensity value
      
    break;
  }
}

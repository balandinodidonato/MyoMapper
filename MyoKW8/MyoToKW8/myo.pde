import de.voidplus.myo.*;
Myo myo;
ArrayList<ArrayList<Integer>> sensors;
String pose;


void myoSetup(){

  myo = new Myo(this);
  myo.withEmg();
  myo.setFrequency(20); // set frequency Data
  
  sensors = new ArrayList<ArrayList<Integer>>();
  for(int i=0; i<34; i++){
    sensors.add(new ArrayList<Integer>()); 
  }
}



void emgGraphs(){
  
   noFill();
   stroke(255);

   synchronized (this){
    for(int i=0; i<17; i++){
      if(!sensors.get(i).isEmpty()){
        beginShape();
        for(int j=0; j<sensors.get(i).size(); j++){
          vertex(j, sensors.get(i).get(j)+(i*50));
        }
        endShape();
      } 
    }
  }
  
}

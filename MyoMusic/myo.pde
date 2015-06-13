import de.voidplus.myo.*;
Myo myo;

ArrayList<ArrayList<Integer>> sensors;

void myoSetup(){

  myo = new Myo(this);
  myo.withEmg();
  myo.setFrequency(20); // set frequency Data
  
  sensors = new ArrayList<ArrayList<Integer>>();
  for(int i=0; i<34; i++){
    sensors.add(new ArrayList<Integer>()); 
  }
}


  // osc
import oscP5.*;
import netP5.*;
OscP5 oscP5;
NetAddress myRemoteLocation;

boolean OpenSoundControl = true;

void oscSetup(){
  
   // OSC settings
  oscP5 = new OscP5(this,12000);
  myRemoteLocation = new NetAddress("127.0.0.1",5432); // IP address and Port

}

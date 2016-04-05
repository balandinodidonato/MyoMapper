import oscP5.*;
import netP5.*;
OscP5 oscP5;
NetAddress myRemoteLocation;

boolean OpenSoundControl = true;

void oscSetup(){
  oscP5 = new OscP5(this,12000); // OSC Port
  myRemoteLocation = new NetAddress("127.0.0.1",5432); // IP address and Port
}

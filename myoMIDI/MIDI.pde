import themidibus.*; //Import the library

MidiBus myBus; // The MidiBus

boolean MIDI = false;

int portMIDI = 3 ;

void setUpMIDI(){
myBus = new MidiBus(this, 2, portMIDI);
}




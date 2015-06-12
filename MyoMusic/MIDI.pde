import themidibus.*; //Import the library

MidiBus myBus; // The MidiBus

boolean MIDI = false;

int portMIDI;
int chMIDI;

void setUpMIDI(){
myBus = new MidiBus(this, 2, portMIDI);
}




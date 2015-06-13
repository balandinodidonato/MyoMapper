import themidibus.*; //Import the library

MidiBus myBus; // The MidiBus

boolean MIDI = false;

int portMIDI = 1;
int chMIDI = 1;

void setUpMIDI(){
myBus = new MidiBus(this, 2, portMIDI);
}




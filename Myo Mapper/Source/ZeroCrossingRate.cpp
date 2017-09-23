#include "ZeroCrossingRate.h"

void ZeroCrossing::setEmgValue(int Value){
    
    emgBuffer[emgCounter] = Value;
    zeroCrossEmg = 0;
    
    for (unsigned int i=0; i<200; i++) {
        if(emgBuffer[i]>0 && emgBuffer[(i+1)%200]<0){
            zeroCrossEmg++;
        }
        else if(emgBuffer[i]<0 && emgBuffer[(i+1)%200]>0){
            zeroCrossEmg++;
        }
        else continue;
    }
    
    emgCounter++;
    emgCounter = emgCounter % 200;
}

int ZeroCrossing::getValue(){
    return zeroCrossEmg;
}

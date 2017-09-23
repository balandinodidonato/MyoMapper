#include "ZeroCrossingRate.h"

void ZeroCrossing::setValue(float Value, int BufferSize){
    
    buffer[counter] = Value;
    zeroCrossingRate = 0;
    
    for (unsigned int i=0; i<BufferSize; i++) {
        if(buffer[i]>0 && buffer[(i+1)%BufferSize]<0){
            zeroCrossingRate++;
        }
        else if(buffer[i]<0 && buffer[(i+1)%200]>0){
            zeroCrossingRate++;
        }
        else continue;
    }
    
    counter++;
    counter = counter % 200;
}

int ZeroCrossing::getValue(){
    return zeroCrossingRate;
}

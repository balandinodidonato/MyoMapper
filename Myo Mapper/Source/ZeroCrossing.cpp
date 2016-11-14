// Zero Crossing feature extractor

#include "../JuceLibraryCode/JuceHeader.h"
#include "ZeroCrossing.h"

ZeroCrossing::ZeroCrossing()
{

}

ZeroCrossing::~ZeroCrossing()
{
}

void ZeroCrossing::setValue(float Value){
    input = Value;
    
    if(index<window.size()){
        window[index] = input;
        index++;
    }
    else{
        for(int i=1; i<window.size(); i++){
            if((window[i]<=0 && window[i-1]>0) || (window[i]>0 && window[i-1]<=0)){
                counter++;
            }
        }
        zeroCrossingRate = counter/window.size();
        index = 0;
    }
}

float ZeroCrossing::getValue(){
    return zeroCrossingRate;
}

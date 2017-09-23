#pragma once

class ZeroCrossing
{
public:
    void setValue(float Value, int BufferSize);
    int getValue();
    
private :
    int buffer[50];
    int counter = 0;
    int zeroCrossingRate = 0;
};

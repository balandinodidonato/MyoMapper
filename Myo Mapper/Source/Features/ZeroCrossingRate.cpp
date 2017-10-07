#include "ZeroCrossingRate.h"

<<<<<<< HEAD:Myo Mapper/Source/ZeroCrossingRate.cpp
void ZeroCrossing::setValue (float Value, int BufferSize)
{
    bufferSize = BufferSize;
    buffer[counter] = Value;
    zeroCrossingRate = 0;
    
    for (unsigned int i = 0; i < bufferSize; ++i)
    {
        if (buffer[i] > 0 && buffer[(i + 1) % bufferSize] < 0)
        {
            zeroCrossingRate++;
        }
        else if (buffer[i] < 0 && buffer[(i + 1) % bufferSize] > 0)
        {
            zeroCrossingRate++;
=======
void ZeroCrossing::setValue(float Value, int BufferSize){
    
    bufferSizeF = BufferSize;
    bufferF[counterF] = Value;
    zeroCrossingRateF = 0;
    
    for (unsigned int i=0; i<bufferSizeF; i++) {
        if(bufferF[i]>0 && bufferF[(i+1)%bufferSizeF]<0){
            zeroCrossingRateF++;
        }
        else if(bufferF[i]<0 && bufferF[(i+1)%bufferSizeF]>0){
            zeroCrossingRateF++;
>>>>>>> c3da6ca5dcc8775e4431be268d1481db9fb2b52d:Myo Mapper/Source/Features/ZeroCrossingRate.cpp
        }
        else continue;
    }
    
<<<<<<< HEAD:Myo Mapper/Source/ZeroCrossingRate.cpp
    ++counter;
    counter = counter % bufferSize;
=======
    counterF++;
    counterF = counterF % bufferSizeF;
}

void ZeroCrossing::setValue(int Value, int BufferSize){
    
    bufferSizeI = BufferSize;
    bufferI[counterI] = Value;
    zeroCrossingRateI = 0;
    
    for (unsigned int i=0; i<bufferSizeI; i++) {
        if(bufferI[i]>0 && bufferI[(i+1)%bufferSizeI]<0){
            zeroCrossingRateI++;
        }
        else if(bufferI[i]<0 && bufferI[(i+1)%bufferSizeI]>0){
            zeroCrossingRateI++;
        }
        else continue;
    }
    
    counterI++;
    counterI = counterI % bufferSizeI;
>>>>>>> c3da6ca5dcc8775e4431be268d1481db9fb2b52d:Myo Mapper/Source/Features/ZeroCrossingRate.cpp
}

void ZeroCrossing::setValue (Vector3D<float> Value, int BufferSize)
{
    Buffer3DSize = BufferSize;
    buffer3D[counter3D] = Value;
    zeroCrossingRate3D = {0, 0, 0};
    
    for (unsigned int i = 0; i < Buffer3DSize; ++i)
    {
        if (buffer3D[i].x > 0 && buffer3D[(i + 1) % Buffer3DSize].x < 0)
            ++zeroCrossingRate3D.x;
        else if (buffer3D[i].x < 0 && buffer3D[(i + 1) % Buffer3DSize].x > 0)
            ++zeroCrossingRate3D.x;
        
        if (buffer3D[i].y > 0 && buffer3D[(i + 1) % Buffer3DSize].y < 0)
            ++zeroCrossingRate3D.y;
        else if (buffer3D[i].y < 0 && buffer3D[(i + 1) % Buffer3DSize].y > 0)
            ++zeroCrossingRate3D.y;
        
        if (buffer3D[i].z > 0 && buffer3D[(i + 1) % Buffer3DSize].z < 0)
            ++zeroCrossingRate3D.z;
        else if (buffer3D[i].z < 0 && buffer3D[(i + 1) % Buffer3DSize].z > 0)
            ++zeroCrossingRate3D.z;
        else continue;
    }
    
    ++counter3D;
    counter3D = counter3D % Buffer3DSize;
}

<<<<<<< HEAD:Myo Mapper/Source/ZeroCrossingRate.cpp
int ZeroCrossing::getInt()
{
    return zeroCrossingRate;
=======
int ZeroCrossing::getInt(){
    return zeroCrossingRateI;
}

int ZeroCrossing::getFloat(){
    return zeroCrossingRateF;
>>>>>>> c3da6ca5dcc8775e4431be268d1481db9fb2b52d:Myo Mapper/Source/Features/ZeroCrossingRate.cpp
}

Vector3D<int> ZeroCrossing::getVector()
{
    return zeroCrossingRate3D;
}

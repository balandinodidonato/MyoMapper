#include "ZeroCrossingRate.h"

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
        }
        else continue;
    }
    
    ++counter;
    counter = counter % bufferSize;
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

int ZeroCrossing::getInt()
{
    return zeroCrossingRate;
}

Vector3D<int> ZeroCrossing::getVector()
{
    return zeroCrossingRate3D;
}

#include "ZeroCrossingRate.h"

float ZeroCrossing::extract(float Value, int BufferSize)
{
    int zcr = 0;
    bufferF.resize(BufferSize);
    bufferF[indexF] = Value;
    
    for (unsigned int i = 0; i < bufferF.size(); ++i)
    {
        if (bufferF[i] > 0 && bufferF[(i + 1) % BufferSize] < 0)
        {
            ++zcr;
        }
        else if (bufferF[i] < 0 && bufferF[(i + 1) % BufferSize] > 0)
        {
            ++zcr;
        }
        else continue;
    }
    
    ++indexF;
    indexF = indexF % bufferF.size();
    
    return zcr;
}

int ZeroCrossing::extract(int Value, int BufferSize)
{
    int zcr = 0;
    bufferI.resize(BufferSize);
    bufferI[indexF] = Value;
    
    for (unsigned int i = 0; i < bufferI.size(); ++i)
    {
        if (bufferI[i] > 0 && bufferI[(i + 1) % BufferSize] < 0)
        {
            ++zcr;
        }
        else if (bufferI[i] < 0 && bufferI[(i + 1) % BufferSize] > 0)
        {
            ++zcr;
        }
        else continue;
    }
    
    ++indexI;
    indexI = indexI % bufferI.size();
    
    return zcr;
}

void ZeroCrossing::setValue (Vector3D<float> Value, int BufferSize)
{
    buffer3D.resize(BufferSize);
    buffer3D[index3D] = Value;
    Vector3D<int> zcr = {0,0,0};
    
    for (unsigned int i = 0; i < buffer3D.size(); ++i)
    {
        if (buffer3D[i].x > 0 && buffer3D[(i + 1) % buffer3D.size()].x < 0)
        {
            ++zcr.x;
        }
        else if (buffer3D[i].x < 0 && buffer3D[(i + 1) % buffer3D.size()].x > 0)
        {
            ++zcr.x;
        }
        
        if (buffer3D[i].y > 0 && buffer3D[(i + 1) % buffer3D.size()].y < 0)
        {
            ++zcr.y;
        }
        else if (buffer3D[i].y < 0 && buffer3D[(i + 1) % buffer3D.size()].y > 0)
        {
            ++zcr.y;
        }
        
        if (buffer3D[i].z > 0 && buffer3D[(i + 1) % buffer3D.size()].z < 0)
        {
            ++zcr.z;
        }
        else if (buffer3D[i].z < 0 && buffer3D[(i + 1) % buffer3D.size()].z > 0)
        {
            ++zcr.z;
        }
        else continue;
    }
    
    ++index3D;
    index3D = index3D % buffer3D.size();
}

#include "ZeroCrossingRate.h"

float ZeroCrossing::extract(float Value, int BufferSize)
{
    int zcr = 0;
    buffer.resize(BufferSize);
    buffer[index] = Value;
    
    for (unsigned int i = 0; i < buffer.size(); ++i)
    {
        if (buffer[i] > 0.1 && buffer[(i + 1) % BufferSize] < 0.1)
        {
            ++zcr;
        }
        else if (buffer[i] < -0.1 && buffer[(i + 1) % BufferSize] > 0.1)
        {
            ++zcr;
        }
        else continue;
    }
    
    ++index;
    index = index % buffer.size();
    return zcr;
}

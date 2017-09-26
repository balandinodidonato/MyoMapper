#include "MinMax.h"

void MinMax::setValues (float Values, int bufferSize)
{
    buffer[counter] = Values;
    
    for (unsigned int i = 0; i < bufferSize; ++i)
    {
        if (buffer[i] < min)
        {
            min = buffer[i];
        }
        if (buffer[i] > max)
        {
            max = buffer[i];
        }
    }
    
    ++counter;
    counter = counter % bufferSize;
}

void MinMax::setValues (Vector3D<float> Values, int bufferSize)
{
    buffer3D[counter3D] = Values;
    
    for (unsigned int i = 0; i < bufferSize; ++i)
    {
        if (buffer3D[i].x < min3D.x)        min3D.x = buffer3D[i].x;
        if (buffer3D[i].y < min3D.y)        min3D.y = buffer3D[i].y;
        if (buffer3D[i].z < min3D.z)        min3D.z = buffer3D[i].z;
        if (buffer3D[i].x > max3D.x)        max3D.x = buffer3D[i].x;
        if (buffer3D[i].y > max3D.y)        max3D.y = buffer3D[i].y;
        if (buffer3D[i].z > max3D.z)        max3D.z = buffer3D[i].z;
    }
}


float MinMax::getMin()
{
    return min;
}

float MinMax::getMax()
{
    return max;
}

Vector3D<float> MinMax::getMin3D()
{
    return min3D;
}

Vector3D<float> MinMax::getMax3D()
{
    return max3D;
}

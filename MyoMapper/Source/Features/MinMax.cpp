#include "MinMax.h"

void MinMax::setValues (float Values, int BufferSize)
{
    buffer.resize(BufferSize);
    buffer[index] = Values;
    
    min = 100000;
    max = -100000;
    
    for (int i = 0; i < buffer.size(); ++i)
    {
        if (buffer[i] < min)
        {
            min = buffer[i];
        }
        else if (buffer[i] > max)
        {
            max = buffer[i];
        }
    }
    
    ++index;
    index = index % buffer.size();
}

void MinMax::setValues (Vector3D<float> Values, int BufferSize)
{
    buffer3D.resize(BufferSize);
    buffer3D[index3D] = Values;
    
    min3D = {100000, 100000, 100000};
    max3D = {-100000, -100000, -100000};

    for (int i = 0; i < buffer3D.size(); ++i)
    {
        if (buffer3D[i].x < min3D.x)
        {
            min3D.x = buffer3D[i].x;
        }
        else if (buffer3D[i].y < min3D.y)
        {
            min3D.y = buffer3D[i].y;
        }
        else if (buffer3D[i].z < min3D.z)
        {
            min3D.z = buffer3D[i].z;
        }
        else if (buffer3D[i].x > max3D.x)
        {
            max3D.x = buffer3D[i].x;
        }
        else if (buffer3D[i].y > max3D.y)
        {
            max3D.y = buffer3D[i].y;
        }
        else if (buffer3D[i].z > max3D.z)
        {
            max3D.z = buffer3D[i].z;
        }
    }
    
    index3D ++;
    index3D = index3D % buffer3D.size();
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

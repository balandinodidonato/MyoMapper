#include "MovingAverage.h"

float MovingAverage::extract (float Value, int BufferSize)
{
    inputF.resize(BufferSize);
    inputF[indexF] = Value;
    
    for (int i = 0; i < inputF.size(); ++i)
        sumF += inputF[i];
    
    float mavg = sumF / inputF.size();
    
    sumF = 0;
    ++indexF;
    indexF = indexF % inputF.size();
    
    return mavg;
}


int MovingAverage::extract (int Value, int BufferSize)
{
    inputI.resize(BufferSize);
    inputI[indexI] = Value;
    
    for (int i = 0; i < inputI.size(); ++i)
        sumI += inputI[i];
    
    float mavg = sumI / inputI.size();
    
    sumI = 0;
    ++indexI;
    indexI = indexI % inputI.size();
    
    return mavg;
}

Vector3D<float> MovingAverage::extract (Vector3D<float> Value, int BufferSize)
{
    input3D.resize(BufferSize);
    input3D[index3D] = Value;
    
    for (int i = 0; i < input3D.size(); ++i)
        sum3D += input3D[i];
    
    Vector3D<float> mavg = sum3D / input3D.size();
    
    sum3D = {0, 0 ,0};
    ++index3D;
    index3D = index3D % input3D.size();
    
    return mavg;
}

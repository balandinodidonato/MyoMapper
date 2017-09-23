#pragma once
#include <iostream>

class ZeroCrossing
{
public:
    void setEmgValue(int Value);
    int getValue();
    
private :
    int emgBuffer[200]; // the array is of 200 because EMG data are sent at a rate of 200Hz
    int emgCounter = 0;
    int zeroCrossEmg = 0;
    
    int imuBuffer[50]; // the array is of 200 because IMU data are sent at a rate of 50Hz
    int imuCounter = 0;
    int zeroCrossImu = 0;
};

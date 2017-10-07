#include "Mav.h"
#include <iostream>
#include <array>

void Mav::setValue (std::array<float, 8> Values)
{
    sum = 0;
    
    for (int i = 0; i < 8; ++i)
    {
        sum = sum + Values[i];
    }
    
    mav = sum * 0.125;
}

float Mav::getValue()
{
    return mav;
}

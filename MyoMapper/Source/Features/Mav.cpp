#include "Mav.h"
#include <iostream>
#include <array>

float Mav::extract (std::array<float, 8> Values)
{
    sum = 0;
    for (int i = 0; i < 8; ++i)
        sum += Values[i];
    
    mav = sum * 0.125;
    
    return mav;
}

#pragma once
#include <iostream>

class Mav
{
public:
    
    float extract (std::array<float, 8> Values);
    
private:
    
    float input[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    float sum = 0;
    float mav = 0;
};

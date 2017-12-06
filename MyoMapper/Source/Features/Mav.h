#pragma once
#include <iostream>

class Mav
{
public:
    
    void setValue (std::array<float, 8> Values);
    float getValue();
    
private:
    
    float input[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    float sum = 0;
    float mav = 0;
};

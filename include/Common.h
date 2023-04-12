#pragma once
#include <iostream>
#include <stdexcept>
#define DIE_ON_ERROR(VALUE,MSG) if(VALUE == 0) {std::cout << "\n";throw std::runtime_error(MSG);}
#define DIE_ON_NULL(VALUE,MSG) if(VALUE == NULL) {std::cout << "\n";throw std::runtime_error(MSG);}
#define DIE(MSG)  {std::cout << "\n";throw std::runtime_error(MSG);}
struct Color
{
    float r,g,b,a;
};

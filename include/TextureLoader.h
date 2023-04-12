#pragma once
#include "Common.h" 
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
#include <glad\glad.h>
class TextureLoader
{
    public:
    static GLuint CreateTexture(const std::string& InImagePath); 

};


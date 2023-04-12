#pragma once
#include "Common.h"
#include "OGLProgram.h"

class Ex04QuadColorDraw

{
    public:
    void Start();
    void Update(float deltatime);
    void Destroy();
private:
    OGLProgram* Program;

    
    GLuint VBO,VAO,EBO;
};
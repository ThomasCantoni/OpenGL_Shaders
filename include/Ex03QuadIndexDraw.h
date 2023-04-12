#pragma once
#include "Common.h"
#include "OGLProgram.h"

class Ex03QuadIndexDraw

{
    public:
    void Start();
    void Update(float deltatime);
    void Destroy();
private:
    OGLProgram* Program;

    
    GLuint VBO,VAO,EBO;
};
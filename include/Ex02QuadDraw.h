#pragma once
#include "Common.h"
#include "OGLProgram.h"

class Ex02QuadDraw

{
    public:
    void Start();
    void Update(float deltatime);
    void Destroy();
private:
    OGLProgram* Program;

    GLuint ProgramID;
    GLuint VBO,VAO;
};
#pragma once
#include "Common.h"
#include "OGLProgram.h"
class Ex01TriangleDraw

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

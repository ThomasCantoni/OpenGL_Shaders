#pragma once
#include <glad/glad.h>
#include "OGLProgram.h"
#include "stb_image.h"

class Ex07SeparateUVs
{
public:
    void Start();
    void Update(float InDeltaTime);
    void Destroy();
    GLuint CreateTexture(const std::string& InImagePath) ;


private:
    OGLProgram* Program;
    GLuint Vao;
    GLuint Vbo;
    GLuint Ebo;
    GLuint UVint;
};

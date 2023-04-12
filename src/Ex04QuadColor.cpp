#include "Ex04QuadColorDraw.h"
#include "Common.h"

#include <string>
#include <fstream>
#include <vector>



void Ex04QuadColorDraw::Start()
{
    
    Program = new OGLProgram("resources/shaders/QuadColor.vert","resources/shaders/QuadColor.frag");
    
    std::vector<float> Vertices=
    {  
     -0.5f,   0.5f,  0.f,    //top left
     -0.5f,  -0.5f,  0.f,    //bottom left
      0.5f,   0.5f,  0.f,    //top right
      0.5f,  -0.5f,  0.f,    //bottom right
    };
    std::vector<int32_t> Indexes = {
        0,1,2, //left triangle
        2,3,1   // right triangle
    };
    
    
    glGenVertexArrays(1,&VAO);  //generate vao
    glBindVertexArray(VAO);     //tell openGL to use this VAO as current VAO
    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO); // there's various types of buffer, we need a GL_ARRAY_BUFFER

    
    unsigned int DataSize = Vertices.size() * sizeof(float);
    glBufferData(GL_ARRAY_BUFFER,DataSize,Vertices.data(),GL_STATIC_DRAW);
    
    GLuint Location=0;
    glVertexAttribPointer(Location,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(Location);


    //4 element buffer object, still a buffer but takes 
    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    int EBO_Size = Indexes.size() * sizeof(uint32_t);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,EBO_Size,Indexes.data(),GL_STATIC_DRAW);

    //4. Set Viewport
    glViewport(0,0,600,400);
    glClearColor(0.5f,0.5f,0.5f,1.0f);
    Program->Bind();
    GLint BaseColorLoc = glGetUniformLocation(Program->ID(),"base_color");
    Color blue = {0,0,255,255};
    GLfloat* bluePointer =(float*)&blue.r;
    glUniform4fv(BaseColorLoc,1,bluePointer);

    glUseProgram(Program->ID());
    
}
void Ex04QuadColorDraw::Update(float d)
{
    glClear(GL_COLOR_BUFFER_BIT);
    //glDrawArrays(GL_TRIANGLES,0,6);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,(void*)0);
}
void Ex04QuadColorDraw::Destroy()
{
    delete(Program);
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
   
}
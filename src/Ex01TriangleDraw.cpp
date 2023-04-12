#include "Ex01TriangleDraw.h"
#include "Common.h"
#include <string>
#include <vector>




void Ex01TriangleDraw::Start()
{
    //REMEMBER!!! Shaders in openGL are not precompiled! They need to be compiled whenever the 3D application starts.
    // this however doesn't happen with later APIs like Vulkan, thanks to the SPIR-V system which
    // saves the compilation data in file form, so it needs less time to load them in the GPU

    //that being said we need to create our shaders...
    Program = new OGLProgram("resources/shaders/triangle.vert","resources/shaders/triangle.frag");
    // GLuint VertexShaderID = CreateShader("resources/shaders/triangle.vert",GL_VERTEX_SHADER);
    // GLuint FragmentShaderID = CreateShader(,GL_FRAGMENT_SHADER);
    
    // // and then compile them
    // GLuint ProgramID = CreateProgram(VertexShaderID,FragmentShaderID);


    // these are the vertices of the Triangle we want to draw
    std::vector<float> Vertices=
    {
         0.5f,  -0.5f,  0.f,    //bottom right
        -0.5f,  -0.5f,  0.f,    //bottom left
        -0.0f,   0.5f,  0.f    //top

    };
    // MORE INFO ABOUT VAO AND VBO ==>https://www.khronos.org/opengl/wiki/Vertex_Specification#Vertex_Array_Object 
    //  AND HERE https://www.khronos.org/opengl/wiki/Tutorial2:_VAOs,_VBOs,_Vertex_and_Fragment_Shaders_(C_/_SDL)

    //1. Create VAO (vertex array object)
    // This is an array that defines the format of the vertices of an object.
    // This is needed for the GPU to interpret and use vertices correctly,
    // otherwise these are just going to be random bytes for the GPU
    
    glGenVertexArrays(1,&VAO);  //generate vao
    glBindVertexArray(VAO);     //tell openGL to use this VAO as current VAO


    //2. Create VBO to load data 
    // VBO is vertex buffer object, this is object is supposed to be stored 
    // (and therefore accessed) by the GPU.
    // When the VAO defines the 'bones' of an object, VBO defines the 'flesh'
    // this defines the  is to be used 
    
    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO); // there's various types of buffer, we need a GL_ARRAY_BUFFER

    // we gotta fill this buffer
    unsigned int DataSize = Vertices.size() * sizeof(float);
    glBufferData(GL_ARRAY_BUFFER,DataSize,Vertices.data(),GL_STATIC_DRAW);
    // the line above essentially tells the GPU to load the VBO in a specific region of it's memory
    // the region depends whether the object to be drawn is STATIC_DRAW or DYNAMIC_DRAW
    //static means this data never changes

    //3. Link this data to the shader
    GLuint Location=0;
    glVertexAttribPointer(Location,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    //the line above associates the VAO and VBO to the shaders we loaded before

    glEnableVertexAttribArray(Location);

    //4. Set Viewport
    glViewport(0,0,600,400);
    glClearColor(0.5f,0.5f,0.5f,1.0f);

    glUseProgram(ProgramID);
}
void Ex01TriangleDraw::Update(float d)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES,0,3);

}
void Ex01TriangleDraw::Destroy()
{
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    delete(Program);
}
#include "Ex07SeparateUVs.h"
#include "Common.h" 
#include <string>
#include <fstream>
#include <vector>
#include <chrono>

//#define STB_IMAGE_IMPLEMENTATION

GLuint Ex07SeparateUVs::CreateTexture(const std::string& InImagePath) 
{
    stbi_set_flip_vertically_on_load(true);

    int Width, Height, Channels;
    unsigned char* Data = stbi_load(InImagePath.c_str(), &Width, &Height, &Channels, 0);
    DIE_ON_NULL(Data, "Failed Loading Texture!");

    GLenum Format = Channels == 3 ? GL_RGB : GL_RGBA;

    GLuint TextureId;
    glGenTextures(1, &TextureId);
    glBindTexture(GL_TEXTURE_2D, TextureId);

    //Load Data to GPU
    glTexImage2D(GL_TEXTURE_2D, 0, Format, Width, Height, 0, Format, GL_UNSIGNED_BYTE, Data);
    //Wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //Filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // Mimapping
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(Data);
    return TextureId;
}


void Ex07SeparateUVs::Start()
{
    
    Program = new OGLProgram("resources/shaders/quadTexture.vert", "resources/shaders/quadTexture.frag");
    
    std::vector<float> Vertices = {
        // Positions        
        -0.5f,  0.5f, 0.f,  //top left
        -0.5f, -0.5f, 0.f,  //bottom left
         0.5f,  0.5f, 0.f,  //top right    
         0.5f, -0.5f, 0.f //bottom right
    };

    std::vector<uint32_t> Indexes = {
        0, 1, 2, //Left Triangle
        2, 3, 1, //Right Triangle
    };
    std::vector<float> UVs = {
        0.0f,   1.0f,   //top left
        0.0f,   0.0f,   //bottom left
        1.0f,  1.0f,   //top right
        1.0f,   0.0f    //bottom right
    };

    //1. Create VAO
    int DataSize = 0;
    GLuint Location_1 = 1;
    glGenVertexArrays(1, &Vao);
    glBindVertexArray(Vao);

    //2. Create VBO to load data
    glGenBuffers(1, &Vbo);
    glBindBuffer(GL_ARRAY_BUFFER, Vbo);

    DataSize = Vertices.size() * sizeof(float);
    glBufferData(GL_ARRAY_BUFFER, DataSize, Vertices.data(), GL_STATIC_DRAW);

    
  

    //3. Link to Vertex Shader
    GLuint Location_0 = 0;
    glVertexAttribPointer(Location_0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(Location_0);
    //glVertexAttribPointer(Location_1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(3 * sizeof(float)));

    glGenBuffers( 1, &UVint );
	glBindBuffer( GL_ARRAY_BUFFER, UVint );


    DataSize = UVs.size() * sizeof(float);
	glBufferData( GL_ARRAY_BUFFER, DataSize , UVs.data(), GL_STATIC_DRAW );
	
    glVertexAttribPointer(Location_1, 2 , GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(Location_1);
    // set uv data

    //4. Crea EBO
    glGenBuffers(1, &Ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Ebo);
    int EboSize = Indexes.size() * sizeof(uint32_t);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, EboSize, Indexes.data(), GL_STATIC_DRAW);

    //4. Set Viewport
    glViewport(0, 0, 600, 400);
    glClearColor(0.5f, 0.5f, 0.5f, 1.f);
    Program->Bind();

    GLint BaseColorLoc = glGetUniformLocation(Program->ID(), "base_color");

    Color Blue{0, 0, 1, 1};
    GLfloat* BluePtr = (GLfloat*)&Blue;
    glUniform4fv(BaseColorLoc, 1, BluePtr);

    GLuint SmileTextureId = CreateTexture("resources/textures/smile.png");
    

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, SmileTextureId);

    


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Ex07SeparateUVs::Update(float InDeltaTime)
{

    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

}

void Ex07SeparateUVs::Destroy()
{
    glDeleteVertexArrays(1, &Vao);
    glDeleteBuffers(1, &Vbo);
    delete Program;
}
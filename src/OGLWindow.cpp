#include "OGLWindow.h"
#include "Common.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

OGLWindow::OGLWindow(int w,int h, const std::string& wintitle)
: width(w),height(h),Title(wintitle) //this assignment method is called "initializer list", 
//this is to avoid a extra cpu cycles to complete the default initialization of the variables width, height,title
{
   LastTime = DeltaTime = 0;
   DIE_ON_ERROR(glfwInit(),"GLFW init failed!");
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
   glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
   glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT,GL_TRUE);

    bool fullscreen = false;
    GLFWmonitor* monitor = fullscreen ? glfwGetPrimaryMonitor() : NULL;
    RawWindow = glfwCreateWindow(width,height,Title.c_str(),NULL,NULL); 

    DIE_ON_NULL(RawWindow,"Window is NULL!");
    glfwMakeContextCurrent(RawWindow);
    if(gladLoadGL()==0)
    {
        std::cout<< "Glad Load failed!"<<std::endl;
    }
}
void OGLWindow::PrintInfo() 
{
	std::cout << "GL VERSION: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GL RENDERER: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "GL VENDOR: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "GLSL VERSION: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}
bool OGLWindow::IsOpened()
{
    return !glfwWindowShouldClose(RawWindow);
}
float OGLWindow::GetDeltaTime()
{
    return DeltaTime;
}
void OGLWindow::Update()
{

    float currTime = glfwGetTime();
    
    DeltaTime =(currTime- LastTime);
    LastTime = currTime;
    glfwSwapBuffers(RawWindow);
    glfwPollEvents();
}
void OGLWindow::SetTitle(const std::string& inTitle)
{
    Title = inTitle;
    glfwSetWindowTitle(RawWindow,Title.c_str());
}
OGLWindow::~OGLWindow()
{
    glfwDestroyWindow(RawWindow);
}
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <format>
#include "OGLWindow.h"
#include "Ex01TriangleDraw.h"
#include "Ex02QuadDraw.h"
#include "Ex03QuadIndexDraw.h"
#include "Ex04QuadColorDraw.h"
#include "Ex05QuadTextureDraw.h"
#include "Ex06TextureMix.h"
#include "Ex07SeparateUVs.h"






//#include "Ex01TriangleDraw.h"
//#include "Ex02QuadDraw.h"


//these lines below are a trick to force the operative system to use the integrated GPU in the case of laptops
#ifdef _WIN32
extern "C" {
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001; //this forces Nvidia
	__declspec(dllexport) unsigned long AmdPowerXpressRequestHighPerformance = 0x00000001; //this forces AMD
}
#endif

int main() {
	std::cout << "It's Working" << std::endl;
    

	OGLWindow Win{600, 400, "OpenGL Window"};
	Win.PrintInfo();

	float TimeElapsed = 0.f;
	
	//Ex01TriangleDraw Scene;
	//Ex02QuadDraw Scene;
	//Ex04QuadColorDraw Scene;
	Ex05QuadTextureDraw Scene;
	//Ex07SeparateUVs Scene;

	Scene.Start();
   

	while(Win.IsOpened()) 
	{
		float DeltaTime = Win.GetDeltaTime();
		TimeElapsed += DeltaTime;
		if (TimeElapsed >= 1.f)
		{
			TimeElapsed -= 1.f;
			float Fps = 1.f / DeltaTime;
			std::string Title = std::format("OpenGL App | DeltaTime: {} - FPS: {}", DeltaTime, Fps);
			Win.SetTitle(Title);
		}

		Scene.Update(DeltaTime);

		Win.Update();
	}
	Scene.Destroy();
	return 0;	
}
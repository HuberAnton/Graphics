#include "Application.h"

#include <iostream>


Application::Application() : camera(CAMERA_TYPE::PERSPECTIVE)
{
   
    // Window init 
    if (glfwInit() == false)
    {
        glfwTerminate();
       
    }

	window = glfwCreateWindow(1280, 720, "GGraphics", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        std::cout << "OPEN GL WINDOW NOT CREATED. CHECK APP" << std::endl;
    }

    // Makes the window passed in the current context for graphics shenannigans.
    glfwMakeContextCurrent(window);

    // Terminate opengl if failed.
    if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
    {
        glfwDestroyWindow(window);
        glfwTerminate();
        std::cout << "OPEN GL FUNCTION NOT INITIALIZED. CHECK APP" << std::endl;
    }

    auto major = ogl_GetMajorVersion();
    auto minor = ogl_GetMinorVersion();

    printf("GL: %i.%i\n", major, minor);

	m_lastFrame = (float)glfwGetTime();
	m_deltaTime = 0;
}


// Does all the shenanigans needed for the update
void Application::UpdateApplication()
{
	float thisFrame = (float)glfwGetTime();
	m_deltaTime = thisFrame - m_lastFrame;
	m_lastFrame = thisFrame;
    
    // Needs to take place before or in the draw loop
    // when objmanager is moved into here.
	camera.Update(m_deltaTime);
}


float Application::GetDeltaTime()
{
	return m_deltaTime;
}



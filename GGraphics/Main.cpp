#include "glm.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"
#include <iostream>
#include "ext.hpp"
#include "..\glm\gtc\quaternion.hpp"
#include "..\glm\gtx\quaternion.hpp"
#include <fstream>
#include <sstream>
#include "Shader.h"
#include "Application.h"
#include "OBJMesh.h"
#define STB_IMAGE_IMPLEMENTATION
#include "DemoCamera.h"
#include "Object.h"
#include "ObjManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "MeshManager.h"
#include "PhysicsScene.h"
// Textures.  
#include "..\stbimage\stb_image.h"







int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //********************
    // Has window init deltaTime and camera.
    //********************
    // CAMERA IS CREATED IN APP CONSTRUCTOR WITH HARDCODED VAL
    Application app;

   
    ObjManager objManager(app.GetCamera().GetProjectionViewMatrix());

    ShaderManager shaderManager;
    TextureManager texureManager;
    MeshManager meshManager;

    PhysicsScene physicsScene;

    // Resorce Creation.
    //************************************************************
    //************************************************************

    // Shaders
    //************************************************************

    shaderManager.CreateShader("BasicShader", "..\\Dependencies\\Shaders\\vert_with_normals.glsl", "..\\Dependencies\\Shaders\\simple_color_frag.glsl");

    shaderManager.CreateShader("2DShader", "..\\Dependencies\\Shaders\\vert_with_normals.glsl", "..\\Dependencies\\Shaders\\2D_Frag.glsl");




    // Creating Lights

    objManager.CreateLight(glm::vec3(10, 0, 10), glm::vec3(0.3, 0.3, 0.3), glm::vec3(0.8, 0.2, 0.0), glm::vec3(1, 0, 0), 512, 1, (float)0.014, (float)0.007);
    objManager.CreateLight(glm::vec3(-10, 0, -10), glm::vec3(0.3, 0.3, 0.3), glm::vec3(0.0, 0.5, 0.5), glm::vec3(0, 0, 1), 1024, 1, (float)0.014, (float)0.007);


    //************************************************************
    // PHYSICS OBJECT CREATION
    //************************************************************

    
    objManager.CreateObject("Square1");
    meshManager.CreateMesh("Square1", PRIMITIVE::SQUARE, 1);
    objManager.SetMesh("Square1", meshManager.GetMesh("Square1"));
    objManager.SetShader("Square1", shaderManager.GetShader("2DShader")); 
    objManager.FindObject("Square1")->SetPosition(glm::vec3(0, 0.0, 0));
    AabbCollider2D* square1 = new AabbCollider2D(glm::vec2(objManager.FindObject("Square1")->GetPosition()), glm::vec2(2,2), glm::vec2(2,0));
    objManager.SetRigidBody("Square1", square1);
    physicsScene.AddActor(objManager.FindObject("Square1"));


    objManager.CreateObject("Square2");
    meshManager.CreateMesh("Square2", PRIMITIVE::SQUARE, 0.5f);
    objManager.SetMesh("Square2", meshManager.GetMesh("Square2"));
    objManager.SetShader("Square2", shaderManager.GetShader("2DShader"));
    objManager.FindObject("Square2")->SetPosition(glm::vec3(0, 1, 0));
    AabbCollider2D* square2 = new AabbCollider2D(glm::vec2(objManager.FindObject("Square2")->GetPosition()), glm::vec2(1, 1), glm::vec2(2, 0), 0.2f);
    objManager.SetRigidBody("Square2", square2);
    physicsScene.AddActor(objManager.FindObject("Square2"));


    objManager.CreateObject("Circle1");
    meshManager.CreateMesh("Circle1", PRIMITIVE::CIRCLE, 0.5f);
    objManager.SetMesh("Circle1", meshManager.GetMesh("Circle1"));
    objManager.SetShader("Circle1", shaderManager.GetShader("2DShader"));
    objManager.FindObject("Circle1")->SetPosition(glm::vec3(0.0, 0, 0));
    CircleColider* circle1 = new CircleColider(glm::vec2(objManager.FindObject("Circle1")->GetPosition()), glm::vec2(0,3), 1.0f, 0.5f);
    objManager.SetRigidBody("Circle1", circle1);
    physicsScene.AddActor(objManager.FindObject("Circle1"));


    objManager.CreateObject("Circle2");
    meshManager.CreateMesh("Circle2", PRIMITIVE::CIRCLE, 0.2f);
    objManager.SetMesh("Circle2", meshManager.GetMesh("Circle2"));
    objManager.SetShader("Circle2", shaderManager.GetShader("2DShader"));
    objManager.FindObject("Circle2")->SetPosition(glm::vec3(0.0, 0, 0));
    CircleColider* circle2 = new CircleColider(glm::vec2(objManager.FindObject("Circle2")->GetPosition()), glm::vec2(1, 3), 0.2f, 0.2f);
    objManager.SetRigidBody("Circle2", circle2);
    physicsScene.AddActor(objManager.FindObject("Circle2"));



    //************************************************************
    // PHYSICS OBJECT BOUNDS
    //************************************************************


    objManager.CreateObject("TopBorder");
    meshManager.CreateMesh("TopBorder", PRIMITIVE::PLANE);
    objManager.SetMesh("TopBorder", meshManager.GetMesh("TopBorder"));
    objManager.SetShader("TopBorder", shaderManager.GetShader("2DShader"));
    objManager.FindObject("TopBorder")->SetPosition(glm::vec3(0.0, 3, 0));
    Plane* topBorder = new Plane(glm::vec2(glm::vec2(0, -1)), -2.9f);
    objManager.SetRigidBody("TopBorder", topBorder);
    physicsScene.AddActor(objManager.FindObject("TopBorder"));


    objManager.CreateObject("BottomBorder");
    meshManager.CreateMesh("BottomBorder", PRIMITIVE::PLANE);
    objManager.SetMesh("BottomBorder", meshManager.GetMesh("BottomBorder"));
    objManager.SetShader("BottomBorder", shaderManager.GetShader("2DShader"));
    objManager.FindObject("BottomBorder")->SetPosition(glm::vec3(0.0, -3, 0));
    Plane* bottomBorder = new Plane(glm::vec2(glm::vec2(0, 1)), -2.9f);
    objManager.SetRigidBody("BottomBorder", bottomBorder);
    physicsScene.AddActor(objManager.FindObject("BottomBorder"));


    objManager.CreateObject("LeftBorder");
    meshManager.CreateMesh("LeftBorder", PRIMITIVE::PLANE);
    objManager.SetMesh("LeftBorder", meshManager.GetMesh("LeftBorder"));
    objManager.SetShader("LeftBorder", shaderManager.GetShader("2DShader"));
    objManager.FindObject("LeftBorder")->SetPosition(glm::vec3(5.3f, 0, 0));
    objManager.FindObject("LeftBorder")->SetModel(glm::rotate(objManager.FindObject("LeftBorder")->GetModel(), glm::radians(90.0f), glm::vec3(0, 0, 1)));
    Plane* leftBorder = new Plane(glm::vec2(glm::vec2(-1, 0)), -5.2);
    objManager.SetRigidBody("LeftBorder", leftBorder);
    physicsScene.AddActor(objManager.FindObject("LeftBorder"));


    objManager.CreateObject("RightBorder");
    meshManager.CreateMesh("RightBorder", PRIMITIVE::PLANE);
    objManager.SetMesh("RightBorder", meshManager.GetMesh("RightBorder"));
    objManager.SetShader("RightBorder", shaderManager.GetShader("2DShader"));
    objManager.FindObject("RightBorder")->SetPosition(glm::vec3(-5.3f, 0, 0));
    objManager.FindObject("RightBorder")->SetModel(glm::rotate(objManager.FindObject("RightBorder")->GetModel(), glm::radians(90.0f), glm::vec3(0, 0, 1)));
    Plane* rightBorder = new Plane(glm::vec2(glm::vec2(1, 0)), -5.2);
    objManager.SetRigidBody("RightBorder", rightBorder);
    physicsScene.AddActor(objManager.FindObject("RightBorder"));

    
    





    // Debug shenanigans and unchanged variables for below loop.
    //************************************************************
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    
    // The loop for the window.
    // Game stuff goes in there.
    while (!glfwWindowShouldClose(glfwGetCurrentContext()) && glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        app.UpdateApplication();

        // Physics.
        physicsScene.Update(app.GetDeltaTime());
        //********************************
        // Object manager
        //********************************

        glm::mat4 pv = *app.GetCamera().GetProjectionViewMatrix();

        // Obj manager should be in applicaiton and draw takes place
        // after the updates.
        objManager.Draw(pv, app.GetCamera().GetWorldTransform()[3]);
        
        // Swaps the front buffer and back buffer
        glfwSwapBuffers(glfwGetCurrentContext());
        
        glfwPollEvents();
    }
    glfwTerminate();
	return 0;
}

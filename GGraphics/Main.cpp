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
// Textures.  
#include "..\stbimage\stb_image.h"




// Things to do.
// Break up object creation into seperate loads.:
// Create a shader manager and place it in app.:
// Conatin all your texture binding to 1 place.
// Need a draw for textures that exist.:
// Rewrite your shaders. Or just rename variables
// so that they are the standard type of names.:
// Revist lights a little and make sure they
// contain all the neccisary parts(minus attenuation):
// Make a primitives class.
// Add a mesh manager/asset manger.
// Oh wait no... I just need an asset manager
// with templated lists of things.
// 2 dimensional array should work.



// Look into:
// structered uniforms. For passing whole structs. Look into fixing up uniforms.
// send sam or murry a question about the end of year project.
// Consider making mulitple shaders that are for;
// 1. Just model color.
// 2. Just light color using normals from model
// 3. Model and light color using normals from model.
// 4. Normals from map.
// 5. Model textures.
// 6. Model textures and lighting.
// And the ability to swap between them at runtime.

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //********************
    // Has window init deltaTime and camera.
    //********************
    Application app;

    // Mesh demo
    //************************************************************

    // It's honestly better to create a data type that then stores this data
    // rather than having a bunch of floats.
    // 3 Pos 2 Uv
    //float vertices[] = {
    //    // Front 
    //      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    //       0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    //       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    //       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    //      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    //      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    //      // Back
    //      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    //       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    //       0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    //       0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    //      -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    //      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    //      // Left
    //      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    //      -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    //      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    //      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    //      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    //      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    //      // Right
    //       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    //       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    //       0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    //       0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    //       0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    //       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    //       // Bottom
    //      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    //       0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
    //       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    //       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    //      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    //      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    //      // Top
    //      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    //       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    //       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    //       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    //      -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    //      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    //};
    //// This is used when using a IBO.
    //// It draws the order of objects. I feel there should be a pattern that is easily dealt with
    ////int index_buffer[]{ 0,1,3,1,2,3 };
    //// Unsigned int designator for the array of data.
    //unsigned int VAO;
    //// The Vao is assaigned a number here by the function call.
    //glGenVertexArrays(1, &VAO);
    //// Unsigned int designator for the buffer.
    //unsigned int VBO;
    //// Buffer is now assaigned a number here by the function call.
    //glGenBuffers(1, &VBO);
    ////unsigned int IBO;
    ////glGenBuffers(1, &IBO);
    //// We are now bound(selected the state) to the vao and can make changes.
    //glBindVertexArray(VAO);
    //// Bind the VBO to the current array buffer.
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //// The current array buffer data is now defined. 
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
    //// IBO shenanigans
    ////glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    ////// Define what d
    ////glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertices), index_buffer, GL_STATIC_DRAW);
    //// Defining what is happening
    //glEnableVertexAttribArray(0);
    //// The vertex attributes are these.
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
    //glEnableVertexAttribArray(1);
    //// Uv data.
    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(sizeof(float) * 3));
    //glBindVertexArray(0);
    //glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Textures
    //************************************************************

    // Now has own class. Look at Texture::Texture(const char* a_textureLocation) for info.

    // Mesh Loading - obj loading
    //************************************************************


    // Shader - Handled in class. Very basic
    //************************************************************

    // Now has own class. Loot at Shader::Shader

    // Managers - These shoud hold all the assets and are created at
    // start.
     //************************************************************

   
    ObjManager objManager(&app.GetCamera().GetProjectionViewMatrix());

    ShaderManager shaderManager;
    TextureManager texureManager;
    MeshManager meshManager;

    
    // Resorce Creation.
    //************************************************************
    //************************************************************

    // Shaders
    //************************************************************

    shaderManager.CreateShader("BasicShader", "..\\Dependencies\\Shaders\\vert_with_normals.glsl", "..\\Dependencies\\Shaders\\simple_color_frag.glsl");
    //texureManager.CreateTexture("woodenBox", "..\\Dependencies\\Textures\\woodenbox.jpg");
    //texureManager.CreateTexture("scribble", "..\\Dependencies\\Textures\\Scrabble.jpg");

    // Sword and shield textures.
    //************************************************************

    texureManager.SetTexture("Sword", "..\\Dependencies\\OBJ\\SwordandShield\\UVAlbedoMap_Sword.png", true);
    texureManager.SetTexture("Sword", "..\\Dependencies\\OBJ\\SwordandShield\\UVNormalMap_Sword.png", true, MAP_TYPE::NORMAL);
    texureManager.SetTexture("Shield", "..\\Dependencies\\OBJ\\SwordandShield\\UVAlbedoMap_Shield.png", true);
    texureManager.SetTexture("Shield", "..\\Dependencies\\OBJ\\SwordandShield\\UVNormalMap_Shield.png", true, MAP_TYPE::NORMAL);

    // Soul spear textures.
    //************************************************************

    //texureManager.SetTexture("SoulSpear", "..\\Dependencies\\OBJ\\soulspear\\soulspear_diffuse.tga", false);

    // Mesh Creation
    //************************************************************

    //meshManager.CreateMesh("Dragon", "..\\Dependencies\\OBJ\\Dragon.obj");
    //meshManager.CreateMesh("Bunny", "..\\Dependencies\\OBJ\\Bunny.obj");

   // meshManager.CreateMesh("Spear", "..\\Dependencies\\OBJ\\soulspear\\soulspear.obj");

    // Note this mesh has 2 mesh chunks so you need to load each texture seperatly.
    meshManager.CreateMesh("SwordandShield", "..\\Dependencies\\OBJ\\SwordandShield\\meshSwordShield.obj");

    // Object creation and asset assaginemnt.
    // Note that this is not 100% correctly implemented.
    // It does not create a copy of the resource so that
    // it can then modify it seperatly.
     //************************************************************
    //objManager.CreateObject("Bunny1");
    //objManager.SetMesh("Bunny1", meshManager.GetMesh("Bunny"));
    //objManager.SetShader("Bunny1", shaderManager.GetShader("BasicShader"));
    //objManager.SetTexture("Bunny1", texureManager.GetTexture("woodenBox"));


    //objManager.CreateObject("Dragon1");
    //objManager.SetMesh("Dragon1", meshManager.GetMesh("Dragon"));
    //objManager.SetShader("Dragon1", shaderManager.GetShader("BasicShader"));
    //objManager.SetTexture("Dragon1", texureManager.GetTexture("scribble"));

    objManager.CreateObject("SwordandShield");
    objManager.SetMesh("SwordandShield", meshManager.GetMesh("SwordandShield"));
    objManager.SetShader("SwordandShield", shaderManager.GetShader("BasicShader"));
    objManager.SetTexture("SwordandShield", texureManager.GetTexture("Shield"), 0);
    objManager.SetTexture("SwordandShield", texureManager.GetTexture("Sword"), 1);
    
   /* objManager.CreateObject("spear");
    objManager.SetMesh("spear", meshManager.GetMesh("Spear"));
    objManager.SetShader("spear", shaderManager.GetShader("BasicShader"));
    objManager.SetTexture("spear", texureManager.GetTexture("SoulSpear"), 0);*/
   



    // Loading models
    //objManager.Load("..\\Dependencies\\OBJ\\Bunny.obj", "Bunny1");
    //objManager.Load("..\\Dependencies\\OBJ\\Bunny.obj", "Bunny2");

    
    //objManager.SetShader("Bunny1", shaderManager.GetShader(0));
    
    //objManager.SetMesh("Bunny1", "..\\Dependencies\\OBJ\\Bunny.obj");

    //objManager.SetTexture("Bunny1", texureManager.GetTexture(0));
 

    // Setting textures
    //objManager.SetTexture("Bunny1", "..\\Dependencies\\Textures\\Scrabble.jpg", TEXTURE_TYPE::DIFFUSE);
    //objManager.SetTexture("Bunny2", "..\\Dependencies\\Textures\\woodenbox.jpg");


    // Creating Lights
    objManager.CreateLight(glm::vec3(-10, 0, 0), glm::vec3(0.3, 0, 0), 0.4f);
    objManager.CreateLight(glm::vec3(10, 0, 0), glm::vec3(0, 0, 0.3), 0.2f);
    //objManager.CreateLight(glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), 0.5f);

    
    // Debug shenanigans and unchanged variables for below loop.
    //************************************************************
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    
    // The loop for the window.
    // Game stuff goes in there.
    while (!glfwWindowShouldClose(glfwGetCurrentContext()) && glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        app.UpdateApplication();

        // Passed to the shader to adjust the color on the fly.
        //glm::vec4 color = glm::vec4(sinf((float)glfwGetTime() * 0.2f),sinf((float)glfwGetTime()* 0.5f),cosf((float)glfwGetTime() * 0.1f),1);
        //glUseProgram(shader_program_ID);
        // All the data being passed to the shaders goes here. 
        // This is for the mesh square.
        //auto uniform_location = glGetUniformLocation(shader_program_ID, "projection_view_matrix");
        //glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(pv));
        //uniform_location = glGetUniformLocation(shader_program_ID, "model_matrix");
        //glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(model));
        //glActiveTexture(GL_TEXTURE0);
        //glBindTexture(GL_TEXTURE_2D, textureDemo);
        // Part of the demo mesh.
        //glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 

        //********************************
        // Object manager
        //********************************

       
        // This is passed to the shader below to scale the models on screen.
        // Fix this. Should be a stored reference in the manager.
        glm::mat4 pv = app.GetCamera().GetProjectionViewMatrix();


        objManager.Draw(pv, app.GetCamera().GetWorldTransform()[3]);
        
        // Swaps the front buffer and back buffer
        glfwSwapBuffers(glfwGetCurrentContext());
        
        glfwPollEvents();
    }


    // Part of the demo mesh.
    //glDeleteBuffers(1, &VAO);
    //glDeleteBuffers(1, &VBO);


    glfwTerminate();
	return 0;
}

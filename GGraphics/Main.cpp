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

#include "..\stbimage\stb_image.h"

int main()
{
    // Initial  
    // Allows for gl function calls.
    if (glfwInit() == false)
    {
        glfwTerminate();
        return -1;
    }
    // Creates a window for open gl to run in with dimensions (x,y), name of window, which screen. (not 100% sure on last).
    GLFWwindow* window = glfwCreateWindow(1280, 720, "GGraphics", nullptr, nullptr);

    // Initiate open gl and check if a valid window has been created by windows
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Makes the window passed in the current context for graphics shenannigans.
    glfwMakeContextCurrent(window);


    // Terminate opengl if failed.
    if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
    {
        glfwDestroyWindow(window);
        glfwTerminate();
        return -3;
    }

    auto major = ogl_GetMajorVersion();
    auto minor = ogl_GetMinorVersion();

    printf("GL: %i.%i\n", major, minor);



 
    // We are using points we make in data.
    // With loading this should be commented out upon load.
    // These are 'local co-ordinates' I beleive


    // Mesh
    //************************************************************



    // It's honestly better to create a data type that then stores this data
    // rather than having a bunch of floats.
    // 3 Pos 2 Uv
    float vertices[] = {
        // Front 
          -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
           0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
           0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
           0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
          -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
          -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
          // Back
          -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
           0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
           0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
           0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
          -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
          -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
          // Left
          -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
          -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
          -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
          -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
          -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
          -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
          // Right
           0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
           0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
           0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
           0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
           0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
           0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
           // Bottom
          -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
           0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
           0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
           0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
          -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
          -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
          // Top
          -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
           0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
           0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
           0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
          -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
          -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
  




    // This is used when using a IBO.
    // It draws the order of objects. I feel there should be a pattern that is easily dealt with

    //int index_buffer[]{ 0,1,3,1,2,3 };



    // Unsigned int designator for the array of data.
    unsigned int VAO;
    // The Vao is assaigned a number here by the function call.
    glGenVertexArrays(1, &VAO);
    // Unsigned int designator for the buffer.
    unsigned int VBO;
    // Buffer is now assaigned a number here by the function call.
    glGenBuffers(1, &VBO);



    //unsigned int IBO;
    //glGenBuffers(1, &IBO);



    // We are now bound(selected the state) to the vao and can make changes.
    glBindVertexArray(VAO);
    // Bind the VBO to the current array buffer.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // The current array buffer data is now defined. 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);


    // IBO shenanigans
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    //// Define what d
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertices), index_buffer, GL_STATIC_DRAW);





    // Defining what is happening
    glEnableVertexAttribArray(0);

    // The vertex attributes are these.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);

    glEnableVertexAttribArray(1);

    // Uv data.
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(sizeof(float) * 3));

    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);


    // Textures
    //************************************************************

    // Make an unsigned int to pass to open gl.
    unsigned int textureDemo;

    // Used by stbi load and passed into the glTexImage.
    int x, y, n;


    // Need the texture locaiton
    unsigned char* data = stbi_load("..\\Dependencies\\Textures\\scrabble.jpg", &x, &y, &n, 0);

    // Open gl assaigns a number to this int and knows the number is 
    // a reference to a texture.

    glGenTextures(1, &textureDemo);
    glBindTexture(GL_TEXTURE_2D, textureDemo);
    // Notea that it might be rgba instead depending on what
    // type of file the texture is.
    if (data)
    {
        //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "No texture bud" << std::endl;
    }

    // Deallocates the memory.
    stbi_image_free(data);

    // Camera
    //************************************************************

    // For projection matrix.
    glm::mat4 projection = glm::perspective(1.507f, 16.0f/9.0f, 0.1f, 50.0f);
    // For view of camera.
    // Note that this is all arbitrary informaion.
    //glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 2), glm::vec3(0,0,0), glm::vec3(0, 1, 0));
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    // Model?
    glm::mat4 model = glm::mat4(1);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));


    // Mesh Loading - obj loading
    //************************************************************

    // Load fucntion is now called in constructor... for better or worse.
    //OBJMesh Bunny("..\\Dependencies\\OBJ\\Bunny.obj");

    
    //Bunny.load("..\\Dependencies\\OBJ\\Bunny.obj");




    // Shader - Handled in class. Very basic
    //************************************************************
   
    std::string vertLocaiton = "..\\Dependencies\\Shaders\\simple_vert.glsl";
    std::string fragLocation = "..\\Dependencies\\Shaders\\simple_color_frag.glsl";


    Shader basicShader(vertLocaiton, fragLocation);



    unsigned int shader_program_ID = basicShader.GetShaderId();
    
 


    //********************
    // Only in charge of delta time atm and ultimatly
    // needs to contain all the above.
    //********************
    Application app;




    // Debug shenanigans and unchanged variables for below loop.
    //************************************************************
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glm::vec4 color = glm::vec4(1, 0, 0, 1);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    
    // The loop for the window.
    // Game stuff goes in there.
    while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        app.UpdateApplication();

        // This is passed to the shader below to scale the models on screen.
        glm::mat4 pv = projection * view;
        //model = glm::rotate(model, glm::radians(10.0f) * app.GetDeltaTime(), glm::vec3(1,1, 0));
        // Passed to the shader to adjust the color on the fly.
        //glm::vec4 color = glm::vec4(sinf((float)glfwGetTime() * 0.2f),sinf((float)glfwGetTime()* 0.5f),cosf((float)glfwGetTime() * 0.1f),1);
        glUseProgram(shader_program_ID);
        // All the data being passed to the shaders goes here. 
        // This is for the mesh square.
        auto uniform_location = glGetUniformLocation(shader_program_ID, "projection_view_matrix");
        glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(pv));
        uniform_location = glGetUniformLocation(shader_program_ID, "model_matrix");
        glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(model));
        //uniform_location = glGetUniformLocation(shader_program_ID, "color");
        //glUniform4fv(uniform_location, 1, glm::value_ptr(color));
        /*uniform_location = glGetUniformLocation(shader_program_ID, "diffuse_texture");
        glUniform1i(uniform_location, 0);*/
   

        // Has something to do with using multiple textures.
        glActiveTexture(GL_TEXTURE0);


        glBindTexture(GL_TEXTURE_2D, textureDemo);
        glBindVertexArray(VAO);



        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 

        //********************************
        // Bunny model
        //********************************
        //Bunny.draw();

        
        // Swaps the front buffer and back buffer
        glfwSwapBuffers(window);
        
        glfwPollEvents();
        
    }

    glDeleteBuffers(1, &VAO);
    glDeleteBuffers(1, &VBO);


    glfwTerminate();
	return 0;
}

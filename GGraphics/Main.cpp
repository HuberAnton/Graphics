#include "glm.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"
#include <iostream>
#include "ext.hpp"
#include "..\glm\gtc\quaternion.hpp"
#include "..\glm\gtx\quaternion.hpp"
#include <fstream>
#include <sstream>






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
    if(!window)
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
    




    // Mesh data. 
    // We are using points we make in data.
    // With loading this should be commented out upon load.
    glm::vec3 vertices[] =
    {
       glm::vec3(-0.5f, -0.5f, 0),
       glm::vec3(-0.5f, -0.5f, 1),
       glm::vec3(0.5f, -0.5f, 1),
       glm::vec3(-0.5f, 0.5f, 1),
       glm::vec3(0.5f, 0.5f, 1),
       glm::vec3(-0.5f, 0.5f, 0),
       glm::vec3(0.5f, 0.5f, 0)
    };
    // This is dumb. 
    // Everytime I change the model I need to adjust this number.
    int verts = 12;

    // This is used when using a IBO.
    // It draws the order of objects. I feel there should be a pattern that is easily dealt with


    // Note this is refeerenced later.
    int index_buffer[]{ 0,1,2,1,2,3 };
    

    //*********
    // Note that this is like a state machine.
    //*********

    // Unsigned int designator for the array of data.
    unsigned int VAO;
    // The Vao is assaigned a number here by the function call.
    glGenVertexArrays(1, &VAO);
    // Unsigned int designator for the buffer.
    unsigned int VBO;
    // Buffer is now assaigned a number here by the function call.
    glGenBuffers(1, &VBO);


    
    unsigned int IBO;
    glGenBuffers(1, &IBO);
    


    // We are now bound(selected the state) to the vao and can make changes.
    glBindVertexArray(VAO);
    // Bind the VBO to the current array buffer.
    glBindBuffer(GL_ARRAY_BUFFER ,VBO);
    // The current array buffer data is now defined. 
    glBufferData(GL_ARRAY_BUFFER, verts * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);


    // IBO shenanigans
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    // Define what d
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(int), index_buffer, GL_STATIC_DRAW);
    




    // Defining what is happening
    glEnableVertexAttribArray(0);

    // The vertex attributes are these.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

    glBindVertexArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    

    // Camera
    //************************************************************

    // For projection matrix.
    glm::mat4 projection = glm::perspective(1.507f, 16.0f/9.0f, 0.1f, 50.0f);
    // For view of camera
    glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 2), glm::vec3(0,0,0), glm::vec3(0, 1, 0));
   
    glm::mat4 model = glm::mat4(1);



    unsigned int vertex_shader_ID = 0;
    unsigned int fragment_shader_ID = 0;
    unsigned int shader_program_ID = 0;


    // Shader
    //************************************************************

    // Vert Shader
    //************************************************************
    std::string shader_data;
    std::ifstream in_file_stream("..\\Shaders\\simple_vert.glsl", std::ifstream::in);
    std::stringstream string_stream;
    if (in_file_stream.is_open())
    {
        string_stream << in_file_stream.rdbuf();
        shader_data = string_stream.str();
        in_file_stream.close();
    }
    vertex_shader_ID = glCreateShader(GL_VERTEX_SHADER);
    const char* data = shader_data.c_str();
    glShaderSource(vertex_shader_ID, 1, (const GLchar**)&data, 0);


    glCompileShader(vertex_shader_ID);



    // Error Checking
    //***********************
    GLint success = GL_FALSE;
    glGetShaderiv(vertex_shader_ID, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        printf("Vertex shader failed.");
    }

    string_stream.clear();

    //Fragment shader
    //************************************************************

    std::string shader_data_frag;
    std::ifstream in_file_stream_frag("..\\Shaders\\simple_color_frag.glsl", std::ifstream::in);
    std::stringstream string_stream_frag;
    

    if (in_file_stream_frag.is_open())
    {
        string_stream_frag << in_file_stream_frag.rdbuf();
        shader_data_frag = string_stream_frag.str();
        in_file_stream_frag.close();
    }

    fragment_shader_ID = glCreateShader(GL_FRAGMENT_SHADER);
    const char* data_frag = shader_data_frag.c_str();
    glShaderSource(fragment_shader_ID, 1, (const GLchar**)&data_frag, 0);


    glCompileShader(fragment_shader_ID);


    // Error Checking
    //***********************
    success = GL_FALSE;
    glGetShaderiv(fragment_shader_ID, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        printf("Fragment shader failed.");
    }


    // Linker
    //***********************
    shader_program_ID = glCreateProgram();

    glAttachShader(shader_program_ID, vertex_shader_ID);
    glAttachShader(shader_program_ID, fragment_shader_ID);

    glLinkProgram(shader_program_ID);

    success = GL_FALSE;
    glGetProgramiv(shader_program_ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        printf("Link failed.");

        GLint log_length = 0;
        glGetProgramiv(shader_program_ID, GL_INFO_LOG_LENGTH, &log_length);

        char* log = new char[log_length];

        glGetProgramInfoLog(shader_program_ID, log_length, 0, log);

        std::string error_message(log);
        error_message += "Shader_failed_to_compile";
        printf(error_message.c_str());
        
        delete[] log;

    }



    //for (int i = 0; i < 6; i++)
    //{
    //    vertices[i] = (glm::vec3)(pvm * glm::vec4(vertices[i], 1));
    //}


    // Color shenanigans for model

    float r = 0.0f;
    float g = 0.0f;
    float b = 0.2f;

    float m_delta;

    

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // The loop for the window.
    // Game stuff goes in there.
    // Note as well the escape key should only work when in context with the window.
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {

        glClear(GL_COLOR_BUFFER_BIT);
        // Rgb and alpha
        // Swaps the front buffer and back buffer
        // Should do all shader shenanigans. 
       

        glm::mat4 pv = projection * view;
        glm::vec4 color = glm::vec4(r,g,b,1);

        glUseProgram(shader_program_ID);

        auto uniform_location = glGetUniformLocation(shader_program_ID, "projection_view_matrix");
        glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(pv));
        uniform_location = glGetUniformLocation(shader_program_ID, "model_matrix");
        glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(model));
        uniform_location = glGetUniformLocation(shader_program_ID, "color");
        glUniform4fv(uniform_location, 1, glm::value_ptr(color));

        // Shenanigans for rotate.
        model = glm::rotate(model, 0.01f, glm::vec3(0,1,0));

        // This is used with the vao to draw shapes in an order.
        // It uses the 
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, verts);
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 

        //projection = glm::perspective(fov, 16.0f / 9.0f, 0.1f, 50.0f);
        

        
        glfwSwapBuffers(window);
        
        glfwPollEvents();
        
    }

    glDeleteBuffers(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
	return 0;
}

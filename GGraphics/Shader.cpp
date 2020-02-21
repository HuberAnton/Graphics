#include "Shader.h"


// Takes in 2 strings with the locations of the files conftaining
// the code for the shaders, compiles them then links them.
// Might be lacking a delete command after shaders have been 
// attached to the program.
Shader::Shader(const char* a_vectorLocation, const char* a_fragmentShader)
{
    std::string shader_data_vert;
    std::ifstream in_file_stream_vert(a_vectorLocation, std::ifstream::in);
    std::stringstream string_stream_vert;
    if (in_file_stream_vert.is_open())
    {
        string_stream_vert << in_file_stream_vert.rdbuf();
        shader_data_vert = string_stream_vert.str();
        in_file_stream_vert.close();
    }
    unsigned int vertex_shader_ID = glCreateShader(GL_VERTEX_SHADER);
    const char* data_vert = shader_data_vert.c_str();
    glShaderSource(vertex_shader_ID, 1, (const GLchar**)&data_vert, 0);


    glCompileShader(vertex_shader_ID);



    // Error Checking
    //***********************
    GLint success = GL_FALSE;
    glGetShaderiv(vertex_shader_ID, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        printf("Vertex shader failed.");
    }


    //Fragment shader
    //************************************************************

    std::string shader_data_frag;
    std::ifstream in_file_stream_frag(a_fragmentShader, std::ifstream::in);
    std::stringstream string_stream_frag;


    if (in_file_stream_frag.is_open())
    {
        string_stream_frag << in_file_stream_frag.rdbuf();
        shader_data_frag = string_stream_frag.str();
        in_file_stream_frag.close();
    }

    unsigned int fragment_shader_ID = glCreateShader(GL_FRAGMENT_SHADER);
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
    m_shaderProgramId = glCreateProgram();

    glAttachShader(m_shaderProgramId, vertex_shader_ID);
    glAttachShader(m_shaderProgramId, fragment_shader_ID);

    glLinkProgram(m_shaderProgramId);

    success = GL_FALSE;
    glGetProgramiv(m_shaderProgramId, GL_LINK_STATUS, &success);
    if (!success)
    {
        printf("Link failed.");

        GLint log_length = 0;
        glGetProgramiv(m_shaderProgramId, GL_INFO_LOG_LENGTH, &log_length);

        char* log = new char[log_length];

        glGetProgramInfoLog(m_shaderProgramId, log_length, 0, log);

        std::string error_message(log);
        error_message += "Shader_failed_to_compile";
        printf(error_message.c_str());

        delete[] log;
    }
}
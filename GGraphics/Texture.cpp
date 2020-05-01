#include "Texture.h"
#include "glm.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"
#include <iostream>
#include "ext.hpp"
#include "..\stbimage\stb_image.h"

// Not idea. Will be removed.
Texture::Texture()
{
    m_name = "NoName";
    // Just set to a value that SHOULDN'T be bound.
    m_diffuse = 999;
    m_specular = 999;
    m_normals = 999;
}

Texture::Texture(const char* a_name)
{
    m_name = a_name;
    // Just set to a value that SHOULDN'T be bound.
    m_diffuse = 999;
    m_specular = 999;
    m_normals = 999;
}


// Note that this might be redundant as a wrong load may cause crash.
// Also it shouldn't be hard to tell something is missing.
void Texture::SetDiffuse(const char* a_location, bool a_flip /*= false*/)        // Slot 1
{
    stbi_set_flip_vertically_on_load(a_flip);
    // Used by stbi load and passed into the glTexImage.
    int x, y, n;

    // Need the texture locaiton
    unsigned char* data = stbi_load(a_location, &x, &y, &n, 0);

    // Open gl assaigns a number to this int and knows the number is 
    // a reference to a texture.

    glGenTextures(1, &m_diffuse);
    glBindTexture(GL_TEXTURE_2D, m_diffuse);
   
    /*if(a_flip)
    {
        stbi_set_flip_vertically_on_load(a_flip);
    }*/
    // Notea that it might be rgba instead depending on what
    // type of file the texture is.
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "No diffuse bud." << std::endl;
        return;
    }
   
    // Deallocates the memory.
    stbi_image_free(data);
    stbi_set_flip_vertically_on_load(0);
}

void Texture::SetSpecular(const char* a_location, bool a_flip/*= false*/)   // Slot 2
{
    stbi_set_flip_vertically_on_load(a_flip);
    // Used by stbi load and passed into the glTexImage.
    int x, y, n;

    // Need the texture locaiton
    unsigned char* data = stbi_load(a_location, &x, &y, &n, 0);

    // Open gl assaigns a number to this int and knows the number is 
    // a reference to a texture.

    glGenTextures(1, &m_specular);
    glBindTexture(GL_TEXTURE_2D, m_specular);
    
    //if (a_flip)
    //{
    //    stbi_set_flip_vertically_on_load(a_flip);
    //}
    // Notea that it might be rgba instead depending on what
    // type of file the texture is.
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "No specular bud" << std::endl;
        return;
    }
    //stbi_set_flip_vertically_on_load(1);
    // Deallocates the memory.
    stbi_image_free(data);
    stbi_set_flip_vertically_on_load(0);
}


void Texture::SetNormal(const char* a_location, bool a_flip /*= false*/)     // Slot 3
{
    stbi_set_flip_vertically_on_load(a_flip);
    // Used by stbi load and passed into the glTexImage.
    int x, y, n;

    // Need the texture locaiton
    unsigned char* data = stbi_load(a_location, &x, &y, &n, 0);

    // Open gl assaigns a number to this int and knows the number is 
    // a reference to a texture.

    glGenTextures(1, &m_normals);
    glBindTexture(GL_TEXTURE_2D, m_normals);
    
    //if (a_flip)
    //{
    //    stbi_set_flip_vertically_on_load(a_flip);
    //}
    // Notea that it might be rgba instead depending on what
    // type of file the texture is.
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "No normal bud" << std::endl;
        return;
    }
    //stbi_set_flip_vertically_on_load(1);
    // Deallocates the memory.
    stbi_image_free(data);
    stbi_set_flip_vertically_on_load(0);
}
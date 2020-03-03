#include "Texture.h"
#include "glm.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"
#include <iostream>
#include "ext.hpp"
#include "..\stbimage\stb_image.h"


Texture::Texture()
{
    // Just set to a value that SHOULDN'T be bound.
    m_diffuse = 999;
    m_specular = 999;
    m_normals = 999;
}

// 'Default' for testing a map. It really is only useful for a diffuse.
// Consider removing after object is refactored
Texture::Texture(const char* a_textureLocation)
{
    if (a_textureLocation != nullptr)
    {
        // Used by stbi load and passed into the glTexImage.
        int x, y, n;

        // Need the texture locaiton
        unsigned char* data = stbi_load(a_textureLocation, &x, &y, &n, 0);

        // Open gl assaigns a number to this int and knows the number is 
        // a reference to a texture.

        glGenTextures(1, &m_diffuse);
        glBindTexture(GL_TEXTURE_2D, m_diffuse);
        // Notea that it might be rgba instead depending on what
        // type of file the texture is.
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "No diffuse bud" << std::endl;
        }

        // Deallocates the memory.
        stbi_image_free(data);
    }
}


// If success return true;
// Note that this might be redundant as a wrong load may cause crash.
// Also it shouldn't be hard to tell something is missing.
bool Texture::SetDiffuse(const char* a_location)        // Slot 1
{
    // Used by stbi load and passed into the glTexImage.
    int x, y, n;

    // Need the texture locaiton
    unsigned char* data = stbi_load(a_location, &x, &y, &n, 0);

    // Open gl assaigns a number to this int and knows the number is 
    // a reference to a texture.

    glGenTextures(1, &m_diffuse);
    glBindTexture(GL_TEXTURE_2D, m_diffuse);
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
        return false;
    }

    // Deallocates the memory.
    stbi_image_free(data);
}

bool Texture::SetSpecular(const char* a_location)
{
    // Used by stbi load and passed into the glTexImage.
    int x, y, n;

    // Need the texture locaiton
    unsigned char* data = stbi_load(a_location, &x, &y, &n, 0);

    // Open gl assaigns a number to this int and knows the number is 
    // a reference to a texture.

    glGenTextures(1, &m_specular);
    glBindTexture(GL_TEXTURE_2D, m_specular);
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
        return false;
    }

    // Deallocates the memory.
    stbi_image_free(data);
}


bool Texture::SetNormal(const char* a_location)
{
    // Used by stbi load and passed into the glTexImage.
    int x, y, n;

    // Need the texture locaiton
    unsigned char* data = stbi_load(a_location, &x, &y, &n, 0);

    // Open gl assaigns a number to this int and knows the number is 
    // a reference to a texture.

    glGenTextures(1, &m_normals);
    glBindTexture(GL_TEXTURE_2D, m_normals);
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
        return false;
    }

    // Deallocates the memory.
    stbi_image_free(data);
}
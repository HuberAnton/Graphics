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
    m_normals = 999;
}


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
//
// Created by daniel on 11/25/22.
//

#include "../include/Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb_image.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

Texture::Texture(bool skybox, std::string fileName) {
    this->skybox = skybox;
    this->fileName = fileName;
    if (skybox){
        std::vector<std::string> faces {
                "right.jpg",
                "left.jpg",
                "top.jpg",
                "bottom.jpg",
                "front.jpg",
                "back.jpg"
        };

        unsigned int textureID;
        glGenTextures(1, &ourTexture);
        glBindTexture(GL_TEXTURE_2D, ourTexture);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        int width, height, nrChannels;
        for (unsigned int i = 0; i < 6; ++i)
        {
            std::string loc = "../textures/nicer_skybox/" + faces[i];
            std::cout << loc << std::endl;
            unsigned char *data = stbi_load(loc.c_str(), &width, &height, &nrChannels, 0);
            if (data)
            {
                glTexImage2D(
                        GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                        0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else
            {
                std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            }
            stbi_image_free(data);
        }
    } else {
        if (fileName == ""){
            return;
        }
        glGenTextures(1, &ourTexture);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, ourTexture);

        // set the ourTexture wrapping/filtering options (on the currently bound ourTexture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // load and generate the ourTexture
        int width, height, nrChannels;
        std::string file = "../" + fileName;
        unsigned char *data = stbi_load(file.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load ourTexture" << std::endl;
        }
        stbi_image_free(data);
    }

    std::cout << "Our texture is: " << ourTexture << std::endl;
}

void Texture::bind() {
    if (this->skybox){
        glDepthMask(GL_FALSE);
        glBindTexture(GL_TEXTURE_CUBE_MAP, ourTexture);
    } else{
        glDepthMask(GL_TRUE);
        glBindTexture(GL_TEXTURE_2D, ourTexture);
    }
}

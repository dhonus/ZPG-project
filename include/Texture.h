//
// Created by daniel on 11/25/22.
//

#ifndef ZPG_TEXTURE_H
#define ZPG_TEXTURE_H
#include "string"
#include <vector>

class Texture {
public:
    Texture(bool skybox, std::string fileName);
    void bind();
private:
    std::string fileName;
    unsigned int ourTexture;
    bool skybox;
};


#endif //ZPG_TEXTURE_H

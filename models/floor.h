//
// Created by daniel on 10/14/22.
//

#ifndef ZPG_FLOOR_H
#define ZPG_FLOOR_H

#include <vector>

std::vector<float> floor_model{
        -200.0f, -5.0f, 200.0f, 1, 0.5f, 0.5f, 0.5f, 0.5f,
        -200.0f, -5.0f, -200.0f, 1, 0.5f, 0.5f, 0.5f, 0.5f,
        200.0f, -5.0f, -200.0f, 1, 0.5f, 0.5f, 0.5f, 0.5f,
        200.0f, -5.0f, 200.0f, 1, 0.5f, 0.5f, 0.5f, 0.5f,
};

std::vector<float> plain {
        //vrchol, normála, uv souřadnice
        1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
        1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
        -1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,

        -1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
        -1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f
};

#endif //ZPG_FLOOR_H

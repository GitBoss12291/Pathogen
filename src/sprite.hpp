#pragma once

#include <string>

namespace pathogen
{
    struct Sprite
    {
        float x, y;
        float rotation = 0.0f;
        float scale = 1.0f;
        unsigned int textureID = -1;
    };
}
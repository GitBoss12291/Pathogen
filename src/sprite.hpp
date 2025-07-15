#pragma once

#include <string>

namespace pathogen
{
    struct Sprite
    {
        unsigned int instanceID = -1;

        float rotation = 0.0f;
        float scale = 1.0f;
        float width = 100, height = 100;

        unsigned int textureID = 0;
        const char* texPath;
    };
}
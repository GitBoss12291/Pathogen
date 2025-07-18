#pragma once

#include <string>
#include <glm/vec4.hpp>

namespace pathogen
{
    struct Sprite
    {
        unsigned int instanceID = -1;

        glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

        float rotation = 0.0f;
        float scale = 1.0f;
        float width = 100, height = 100;
        int step = 0;
        int maxSteps = 1;
        int cols = 0;
        int rows = 0;

        unsigned int textureID = 0;
        const char* texPath;
    };
}
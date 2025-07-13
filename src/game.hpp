#pragma once

#include <vector>

namespace pathogen
{
    struct Sprite;

    struct Camera
    {
        float x, y;
        float zoom = 1.0f;
    };

    struct Game
    {
        std::vector<Sprite> sprites;
        Camera camera;
        float time;

        void tick();
        void draw();
    };
}
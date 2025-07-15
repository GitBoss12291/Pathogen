#pragma once

#include <unordered_map>

namespace pathogen
{
    struct Sprite;
    class Shader;

    class SpriteRenderer
    {
    public:
        void init();
        void drawSprite(Sprite& sprite, float camX, float camY);
        void shutdown();

        void setScreenDim(int width, int height);
        void setWorldOrigin(float x, float y);

    private:
        unsigned int quadVAO = 0;
        unsigned int quadVBO = 0;
        float screenWidth;
        float screenHeight;
        float originX;
        float originY;
        
        Shader* shader = nullptr;
    };
}
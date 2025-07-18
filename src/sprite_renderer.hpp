#pragma once

#include <unordered_map>
#include <glm/vec4.hpp>

namespace pathogen
{
    struct Sprite;
    class Shader;

    class SpriteRenderer
    {
    public:
        void init();
        void drawSprite(Sprite& sprite, float x, float y, float camX, float camY, 
            glm::vec4 color = glm::vec4(1.0f), int stepCount = 1, 
            int cols = 0, int rows = 0);
        void drawRect(float x, float y, float width, float height, glm::vec4 color);
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

        unsigned int whiteTextureID;
        
        Shader* shader = nullptr;
        Shader* uiShader = nullptr;
    };
}
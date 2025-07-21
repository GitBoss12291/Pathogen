#pragma once

#include <unordered_map>
#include <string>
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
            int cols = 0, int rows = 0, bool calculateUVOffset = true);
        void drawRect(float x, float y, float width, float height, glm::vec4 color, 
            const std::string& text = "", glm::vec4 textColor = {1.0f, 1.0f, 1.0f, 1.0f});
        void drawText(const std::string& text, float x, float y, float width, float height, glm::vec4 color, float fontSize = 32, float minFontSize = 4);
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

        unsigned int fontTex;
        float fontBaseline;
    };
}
#pragma once

namespace pathogen
{
    struct Sprite;

    class SpriteRenderer
    {
    public:
        void init();
        void drawSprite(Sprite& sprite);
        void shutdown();

    private:
        unsigned int quadVAO = 0;
        unsigned int quadVBO = 0;
        unsigned int shaderProgram = 0;
    };
}
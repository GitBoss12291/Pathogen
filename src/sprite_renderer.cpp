#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype/stb_truetype.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write/stb_image_write.h>

#include "shader.hpp"
#include "sprite_renderer.hpp"
#include "sprite.hpp"


namespace pathogen
{
    stbtt_bakedchar cdata[96];

    void SpriteRenderer::init()
    {
        shader = new Shader("assets/shaders/basic.vert", "assets/shaders/basic.frag");
        uiShader = new Shader("assets/shaders/ui.vert", "assets/shaders/ui.frag");

        unsigned char* ttf_buffer = new unsigned char[1 << 20];
        unsigned char* temp_bitmap = new unsigned char[512 * 512];

        FILE* fontFile = fopen("assets/fonts/Tiny5-Regular.ttf", "rb");
        if (!fontFile)
        {
            std::cerr << "Failed to load font file!" << std::endl;
            return;
        }

        fread(ttf_buffer, 1, 1 << 20, fontFile);
        fclose(fontFile);

        stbtt_fontinfo font;

        stbtt_InitFont(&font, ttf_buffer, stbtt_GetFontOffsetForIndex(ttf_buffer, 0));

        int ascent, descent, lineGap;
        stbtt_GetFontVMetrics(&font, &ascent, &descent, &lineGap);

        float scale = stbtt_ScaleForPixelHeight(&font, 32.0f);
        fontBaseline = ascent * scale;

        stbtt_BakeFontBitmap(ttf_buffer, 0, 32.0, temp_bitmap, 512, 512, 32, 96, cdata);
        stbi_write_png("assets/fonts/font_debug.png", 512, 512, 1, temp_bitmap, 512);

        glGenTextures(1, &fontTex);
        glBindTexture(GL_TEXTURE_2D, fontTex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 512, 512, 0, GL_RED, GL_UNSIGNED_BYTE, temp_bitmap);

        GLint swizzleMask[] = { GL_RED, GL_RED, GL_RED, GL_RED };
        glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzleMask);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        delete[] ttf_buffer;
        delete[] temp_bitmap;

        float vertices[] = {
            // pos         // tex
            -0.5f,  0.5f,  0.0f, 1.0f,
             0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f,  0.0f, 0.0f,

             0.5f, -0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f,  0.0f, 0.0f
        };

        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);

        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }


    // Draw a Sprite on Screen
    // Optionally use the sprite's texture as an atlas by specifying stepcount cols and rows
    void SpriteRenderer::drawSprite(Sprite& sprite, float x, float y, float camX, float camY, glm::vec4 color, int stepCount, int cols, int rows, bool calculateUVOffset)
    {
        if (!shader)
        {
            std::cerr << "SpriteRenderer not initialized, Shader is still nullptr" << std::endl;
            return;
        }
        if (sprite.textureID == 0)
        {
            shader->genTexture(sprite.textureID, sprite.texPath.c_str());
        }

        glm::mat4 modelMat = glm::mat4(1.0f);
        modelMat = glm::translate(modelMat, glm::vec3(x + originX, y + originY, 0.0f));
        modelMat = glm::rotate(modelMat, glm::radians(sprite.rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        modelMat = glm::scale(modelMat, glm::vec3(sprite.width * sprite.scale, sprite.height * sprite.scale, 1.0f));

        glm::mat4 projMat = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight, -1.0f, 1.0f);

        glm::vec2 camPos = glm::vec2(camX, camY);
        glm::mat4 viewMat = glm::translate(glm::mat4(1.0f), glm::vec3(-camPos, 0.0f));

        shader->use();
        shader->setMat4("uModel", glm::value_ptr(modelMat));
        shader->setMat4("uProjection", glm::value_ptr(projMat));
        shader->setMat4("uView", glm::value_ptr(viewMat));
        shader->setVec4("uColor", glm::value_ptr(color));

        if (stepCount > 1 && cols > 0 && rows > 0 && calculateUVOffset)
        {
            int step = sprite.step;
            
            float uStep = 1.0f / cols;
            float vStep = 1.0f / rows;

            int col = step % cols;
            int row = step / cols;

            float uOffset = col * uStep;
            float vOffset = 1.0f - (row + 1) * vStep;

            shader->setVec2("uUVOffset", uOffset, vOffset);
            shader->setVec2("uUVScale", uStep, vStep);
        }
        else if (calculateUVOffset)
        {
            shader->setVec2("uUVOffset", 0.0f, 0.0f);
            shader->setVec2("uUVScale", 1.0f, 1.0f);
        }

        glBindTexture(GL_TEXTURE_2D, sprite.textureID);
        glBindVertexArray(quadVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    void SpriteRenderer::drawRect(float x, float y, float width, float height, glm::vec4 color, const std::string& text, glm::vec4 textColor)
    {
        if (!uiShader)
        {
            std::cerr << "SpriteRenderer not initialized, Shader is still nullptr" << std::endl;
            return;
        }

        float xy[2] = { x, y };
        float size[2] = { width, height}; // multiply by two because the size was in half-pixels before.
        float res[2] = { screenWidth, screenHeight };

        uiShader->use();
        uiShader->setVec2("uPos", xy);
        uiShader->setVec2("uSize", size);
        uiShader->setVec4("uColor", glm::value_ptr(color));
        uiShader->setVec2("uResolution", res);
        
        glBindVertexArray(quadVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        if (text != "" && fontTex != 0)
        {
            drawText(text, x, y, width, height, textColor);
        }
    }

    void SpriteRenderer::drawText(const std::string& text, float x, float y, float width, float height, glm::vec4 color, float fontSize, float minFontSize)
    {
        float startX = x;
        float startY = y + fontBaseline;
        Sprite glyphSprite;
        glyphSprite.textureID = fontTex;
        glyphSprite.scale = 1.0f;
        glyphSprite.rotation = 0.0f;
        for (char c : text)
        {
            if (c < 32 || c >= 128) continue;

            stbtt_aligned_quad q;
            stbtt_GetBakedQuad(cdata, 512, 512, c - 32, &x, &startY, &q, 1);
            float glyphX = q.x0;
            float glyphY = q.y1;
            float glyphW = q.x1 - q.x0;
            float glyphH = q.y1 - q.y0;
            float glyphYOffset = q.y1 - startY;

            glm::vec4 posColor = color;

            shader->use();
            shader->setVec2("uUVOffset", q.s0, q.t1);
            shader->setVec2("uUVScale", q.s1 - q.s0, q.t0 - q.t1);

            glyphSprite.width = glyphW;
            glyphSprite.height = glyphH;

            float drawX = glyphX - originX;
            float drawY = glyphY - glyphYOffset - originY;

            drawSprite(glyphSprite, drawX, -drawY, 0.0f, 0.0f, posColor, 1, 0, 0, false);
        }
    }

    // Releases resources properly
    void SpriteRenderer::shutdown()
    {
        if (shader)
        {
            delete shader;
            shader = nullptr;
        }

        if (uiShader)
        {
            delete uiShader;
            uiShader = nullptr;
        }

        glDeleteVertexArrays(1, &quadVAO);
        glDeleteBuffers(1, &quadVBO);
    }

    void SpriteRenderer::setScreenDim(int width, int height)
    {
        screenWidth = (float)width;
        screenHeight = (float)height;
    }

    void SpriteRenderer::setWorldOrigin(float x, float y)
    {
        originX = x;
        originY = y;
    }
}
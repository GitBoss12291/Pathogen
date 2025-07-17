#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "shader.hpp"
#include "sprite_renderer.hpp"
#include "sprite.hpp"


namespace pathogen
{
    void SpriteRenderer::init()
    {
        shader = new Shader("assets/shaders/basic.vert", "assets/shaders/basic.frag");
        uiShader = new Shader("assets/shaders/ui.vert", "assets/shaders/ui.frag");
    
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
    void SpriteRenderer::drawSprite(Sprite& sprite, float x, float y, float camX, float camY)
    {
        if (!shader)
        {
            std::cerr << "SpriteRenderer not initialized, Shader is still nullptr" << std::endl;
            return;
        }
        if (sprite.textureID == 0)
        {
            shader->genTexture(sprite.textureID, sprite.texPath);
        }

        glm::mat4 modelMat = glm::mat4(1.0f);
        modelMat = glm::translate(modelMat, glm::vec3(x + originX, y + originY, 0.0f));
        modelMat = glm::scale(modelMat, glm::vec3(sprite.width * sprite.scale, sprite.height * sprite.scale, 1.0f));

        glm::mat4 projMat = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight, -1.0f, 1.0f);

        glm::vec2 camPos = glm::vec2(camX, camY);
        glm::mat4 viewMat = glm::translate(glm::mat4(1.0f), glm::vec3(-camPos, 0.0f));

        shader->use();
        shader->setMat4("uModel", glm::value_ptr(modelMat));
        shader->setMat4("uProjection", glm::value_ptr(projMat));
        shader->setMat4("uView", glm::value_ptr(viewMat));

        glBindTexture(GL_TEXTURE_2D, sprite.textureID);
        glBindVertexArray(quadVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    void SpriteRenderer::drawRect(float x, float y, float width, float height, glm::vec4 color)
    {
        if (!uiShader)
        {
            std::cerr << "SpriteRenderer not initialized, Shader is still nullptr" << std::endl;
            return;
        }

        float xy[2] = { x, y };
        float size[2] = { width, height };
        float res[2] = { screenWidth, screenHeight };

        uiShader->use();
        uiShader->setVec2("uPos", xy);
        uiShader->setVec2("uSize", size);
        uiShader->setVec4("uColor", glm::value_ptr(color));
        uiShader->setVec2("uResolution", res);
        
        glBindVertexArray(quadVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    // Releases resources properly
    void SpriteRenderer::shutdown()
    {
        if (shader)
        {
            delete shader;
            shader = nullptr;
        }

        glDeleteVertexArrays(1, &quadVAO);
        glDeleteBuffers(1, &quadVBO);
    }

    void SpriteRenderer::setScreenDim(int width, int height)
    {
        screenWidth = width;
        screenHeight = height;
    }

    void SpriteRenderer::setWorldOrigin(float x, float y)
    {
        originX = x;
        originY = y;
    }
}
#pragma once

#include <vector>

namespace pathogen
{
    class GameObject;
    class SpriteRenderer;

    struct Camera
    {
        float x = 0.0f, y = 0.0f;
        float zoom = 1.0f;
    };

    struct Game
    {
        ~Game();

        void init();

        void setScreenDim(int width, int height);

        void addGameObject(GameObject* gameObject);

        void tick(float dt);
        void draw();
    
        std::vector<GameObject*> gameObjects;
        Camera camera;
        SpriteRenderer* spriteRenderer = nullptr;
        float time = 0.0f;
        float deltaTime = 0.0f;

    private:
        inline static int nextID = 0;
        inline int getNextID() { return ++nextID; }

    };
}
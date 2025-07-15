#pragma once

#include <vector>

namespace pathogen
{
    class GameObject;
    class SpriteRenderer;
    class Editor;

    struct Camera
    {
        float x = 0.0f, y = 0.0f;
        float zoom = 1.0f;
    };

    enum class GameState
    {
        Menu = 0,
        Play,
        Edit
    };

    struct Game
    {
        ~Game();

        void init();

        void setScreenDim(int width, int height);

        void addGameObject(GameObject* gameObject);

        void tick(float dt);
        void draw();
    
        GameState state = GameState::Menu;
        std::vector<GameObject*> gameObjects;
        Camera camera;
        Editor* editor = nullptr;
        SpriteRenderer* spriteRenderer = nullptr;
        float time = 0.0f;
        float deltaTime = 0.0f;

    private:
        inline static int nextID = 0;
        inline int getNextID() { return ++nextID; }
        void menu(float dt);
        void play(float dt);
        void edit(float dt);

    };
}
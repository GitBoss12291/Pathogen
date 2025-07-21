#pragma once

#include <unordered_map>

namespace pathogen
{
    class GameObject;
    class SpriteRenderer;
    class Editor;
    class Player;
    class Enemy;

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

        void init(int width, int height);

        void setScreenDim(int width, int height);

        void addGameObject(GameObject* gameObject);

        GameObject* getGameObjectByID(int instanceID);

        void tick(float dt);
        void draw() const;
    
        GameState state = GameState::Menu;
        GameState lastState = GameState::Menu;
        std::unordered_map<int, GameObject*> gameObjects;
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

        Player* setupPlayer();
        Enemy* spawnEnemy(Player* player);

        float screenWidth;
        float screenHeight;

        int playerID = -1;

    };
}
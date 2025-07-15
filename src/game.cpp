#include <iostream>
#include <GLFW/glfw3.h>

#include "game.hpp"
#include "game_object.hpp"
#include "sprite_renderer.hpp"
#include "sprite.hpp"
#include "input_handler.hpp"
#include "player.hpp"
#include "enemy.hpp"

namespace pathogen
{
	Game::~Game()
	{
		for (GameObject* obj : gameObjects)
			delete obj;
		gameObjects.clear();

		if (spriteRenderer)
		{
			spriteRenderer->shutdown();
			delete spriteRenderer;
			spriteRenderer = nullptr;
		}
	}

	Player* setupPlayer()
	{
		auto* player = new Player();
		player->sprite.texPath = "Pathogen.png";
		
		return player;
	}

	Enemy* spawnEnemy(Player* player)
	{
		auto* enemy = new Enemy();
		enemy->sprite.texPath = "Pathogen.png";
		enemy->setPlayer(player);
		return enemy;
	}

	void Game::init()
	{
		spriteRenderer = new SpriteRenderer();
		spriteRenderer->init();
		auto* player = setupPlayer();

		addGameObject(player);

		auto* testEnemy = spawnEnemy(player);

		addGameObject(testEnemy);
	}

	void Game::setScreenDim(int width, int height)
	{
		if (!spriteRenderer)
		{
			std::cerr << "ERROR: Sprite Renderer used before initialization, Initialize Game prior to use." << std::endl;
			return;
		}

		spriteRenderer->setWorldOrigin(width / 2.0f, height / 2.0f);
		spriteRenderer->setScreenDim(width, height);
	}

	// Adds a Game Object and generates a new id if it doesn't have one.
	void Game::addGameObject(GameObject* gameObject)
	{
		if (gameObject->instanceID == 0)
		{
			gameObject->instanceID = getNextID();
		}
		for (size_t i = 0; i < gameObjects.size(); ++i)
		{
			if (gameObjects[i]->instanceID == gameObject->instanceID)
			{
				return;
			}
		}

		gameObjects.push_back(gameObject);
	}

	void Game::tick(float dt)
	{
		time += dt;
		
		switch (state)
		{
		case GameState::Menu:
			menu(dt);
			break;
		case GameState::Play:
			play(dt);
			break;
		case GameState::Edit:
			edit(dt);
			break;
		}
	}

	void Game::draw()
	{
		for (auto& obj : gameObjects)
		{
			obj->draw(spriteRenderer, camera.x, camera.y);
		}
	}

	void Game::menu(float dt)
	{

	}

	void Game::play(float dt)
	{
		for (auto& obj : gameObjects)
		{
			obj->update(dt);

			if (obj->getType() == ObjectType::Player)
			{
				camera.x = obj->sprite.x;
				camera.y = obj->sprite.y;
			}
		}
	}

	void Game::edit(float dt)
	{

	}

}
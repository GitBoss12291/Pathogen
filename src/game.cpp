#include <iostream>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <ctime>
#include <cstdlib>

#include "game.hpp"
#include "game_object.hpp"
#include "sprite_renderer.hpp"
#include "sprite.hpp"
#include "input_handler.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "cell.hpp"
#include "part.hpp"
#include "editor.hpp"

namespace pathogen
{
	Game::~Game()
	{
		for (auto& pair : gameObjects)
			delete pair.second;
		gameObjects.clear();

		if (spriteRenderer)
		{
			spriteRenderer->shutdown();
			delete spriteRenderer;
			spriteRenderer = nullptr;
		}
	}

	Player* Game::setupPlayer()
	{
		auto* player = new Player();
		player->sprite.texPath = "cell.png";
		player->sprite.color = { 0.5f, 0.5, 0.8f, 1.0f };
		player->sprite.width = 150;
		player->sprite.height = 150;
		player->sprite.maxSteps = 14;
		player->sprite.cols = 7;
		player->sprite.rows = 4;


		Cell playerCell;
		playerCell.sprite = &player->sprite;
		playerCell.stats = { playerCell.baseSpeed, playerCell.baseAttack, playerCell.baseDefense };
		player->cell = playerCell;

		return player;
	}

	Enemy* Game::spawnEnemy(Player* player)
	{
		auto* enemy = new Enemy();
		enemy->x = 300.0f;
		enemy->y = -200.0f;
		enemy->sprite.texPath = "Pathogen.png";
		enemy->setPlayer(player);
		return enemy;
	}

	void Game::init()
	{
		editor = new Editor();

		state = GameState::Edit;
		std::srand(std::time(0));

		spriteRenderer = new SpriteRenderer();
		spriteRenderer->init();
		auto* player = setupPlayer();

		addGameObject(player);

		playerID = player->instanceID;

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

		if (!editor)
		{
			std::cerr << "ERROR: Editor used before initialization, Initialize Game prior to use." << std::endl;
			return;
		}

		spriteRenderer->setWorldOrigin(width / 2.0f, height / 2.0f);
		spriteRenderer->setScreenDim(width, height);
		editor->setScreenDim(width, height);
	}

	// Adds a Game Object and generates a new id if it doesn't have one.
	void Game::addGameObject(GameObject* gameObject)
	{
		if (gameObject->instanceID == -1)
		{
			gameObject->instanceID = getNextID();
		}
		if (gameObjects.find(gameObject->instanceID) != gameObjects.end())
		{
			return;
		}

		gameObjects[gameObject->instanceID] = gameObject;
	}

	GameObject* Game::getGameObjectByID(int instanceID)
	{
		auto it = gameObjects.find(instanceID);
		if (it != gameObjects.end())
		{
			return it->second;
		}

		std::cerr << "Object with id: " << instanceID << " nonexistant" << std::endl;
		return nullptr;
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

	void Game::draw() const
	{
		switch (state)
		{
		case GameState::Menu:
			break;
		case GameState::Play:
			for (const auto& pair : gameObjects)
			{
				pair.second->draw(spriteRenderer, camera.x, camera.y);
			}
			break;
		case GameState::Edit:
			editor->draw(spriteRenderer, camera.x, camera.y);
			break;
		}
	}

	void Game::menu(float dt)
	{
		
	}

	void Game::play(float dt)
	{
		for (auto& pair : gameObjects)
		{
			GameObject* obj = pair.second;
			obj->update(dt);

			if (obj->getType() == ObjectType::Player)
			{
				camera.x = obj->x;
				camera.y = obj->y;
			}
		}
	}

	void Game::edit(float dt)
	{
		if (!editor)
		{
			std::cerr << "Game not initialized, Editor is nullptr."
				"Always make sure to initialize Game before calling any methods" << std::endl;
			return;
		}

		Player* player = dynamic_cast<Player*>(getGameObjectByID(playerID));

		if (!player)
		{
			std::cerr << "Player not found for editor." << std::endl;
			return;
		}

		editor->setTargetCell(&player->cell);

		editor->tick(dt);
	}

}
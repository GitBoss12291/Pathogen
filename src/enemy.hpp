#pragma once

#include "game_object.hpp"

namespace pathogen
{
	class Player;

	class Enemy : public GameObject
	{
	public:
		void update(float dt) override;
		ObjectType getType() const override { return ObjectType::Enemy; }
		inline void setPlayer(Player* plyr) { player = plyr;  }

	private:
		Player* player;
	};
}
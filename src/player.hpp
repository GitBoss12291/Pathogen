#pragma once

#include "game_object.hpp"
#include "cell.hpp"

namespace pathogen
{
	class Player : public GameObject
	{
	public:
		Cell cell;
		void update(float dt) override;
		void draw(SpriteRenderer* renderer, float camX, float camY) override;
		ObjectType getType() const override { return ObjectType::Player; }
	};
}
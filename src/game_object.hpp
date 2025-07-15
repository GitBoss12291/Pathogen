#pragma once

#include "sprite.hpp"

namespace pathogen
{
	class SpriteRenderer;

	enum class ObjectType
	{
		Unknown = 0,
		Player, 
		Enemy
	};

	class GameObject
	{
	public:
		unsigned int instanceID = 0;

		Sprite sprite;
		virtual void update(float dt) = 0;
		virtual void draw(SpriteRenderer* renderer, float camX, float camY);
		virtual ObjectType getType() const { return ObjectType::Unknown; }
		virtual ~GameObject() = default;
	};
}
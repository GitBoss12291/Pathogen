#include "flagella.hpp"
#include "cell.hpp"

namespace pathogen
{
	Flagella::Flagella()
	{
		type = PartType::Flagella;
		sprite = Sprite();
		sprite.texPath = "flagella.png";
		sprite.maxSteps = 7;
		sprite.step = 1;
		sprite.cols = 4;
		sprite.rows = 2;
		sprite.scale = 0.5f;
		sprite.width = 100.0f;
		sprite.height = 100.0f;
	
		animateSpeed = 1.0f;
	}

	void Flagella::modifyStats()
	{
		host->stats.speed += 200.0f;
	}

	void Flagella::update(float dt)
	{
		sprite.step += animateSpeed * 1 * dt;
	}
}
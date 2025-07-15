#include "ui_panel.hpp"
#include "sprite_renderer.hpp"

namespace pathogen
{
	void UIPanel::draw(SpriteRenderer* renderer)
	{
		renderer->drawRect(x, y, width, height, fillColor);
	}
}
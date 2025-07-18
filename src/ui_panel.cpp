#include "ui_panel.hpp"
#include "sprite_renderer.hpp"

namespace pathogen
{
	void UIPanel::draw(SpriteRenderer* renderer) const
	{
		if (borderSize > 1e-6)
		{
			float halfBorder = borderSize * 0.49f;

			renderer->drawRect(x - halfBorder, y - halfBorder, width + borderSize, height + borderSize, borderColor);
		}

		renderer->drawRect(x, y, width, height, fillColor);
	}
}
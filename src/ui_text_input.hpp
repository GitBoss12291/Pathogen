#include "ui_panel.hpp"

#include <glm/vec4.hpp>
#include <string>

namespace pathogen
{
	class SpriteRenderer;

	struct UITextInput : UIPanel
	{
	public:
		void update(float dt, float screenWidth, float screenHeight); // must be called to process input
		void draw(SpriteRenderer* renderer) const override;

		std::string placeholder = "Enter Text... ";
		std::string value;
		glm::vec4 textColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	
		bool isActive;
		float blinkTimer = 0.5f; // 0 means static
		bool showCursor = true;
	
	private:
		bool backspaceHeld = false;
		float backspaceHoldTime = 0.0f;
		float backspaceRepeatTime = 0.0f;
	};
}
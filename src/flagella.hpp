#pragma once

#include "part.hpp"

namespace pathogen
{
	class Flagella : public Part
	{
	public:
		Flagella();
		void modifyStats() override;
		void update(float dt) override;
	};
}
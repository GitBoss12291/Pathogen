#pragma once

namespace pathogen
{
	class Cell;

	class Serializer
	{
	public:
		static void save(Cell* toSave, const char* path);
		static Cell load(const char* path);
	};
}
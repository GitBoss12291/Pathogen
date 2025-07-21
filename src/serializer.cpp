#include <json.hpp>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <iostream>
#include <vector>

#include "serializer.hpp"
#include "cell.hpp"
#include "part.hpp"
#include "flagella.hpp"
#include "sprite.hpp"

using json = nlohmann::json;

NLOHMANN_JSON_SERIALIZE_ENUM(pathogen::PartType, 
	{
		{pathogen::PartType::Flagella, "Flagella"},
		{pathogen::PartType::Spike, "Spike"}
	})

namespace pathogen
{
	void saveSprite(json& data, const char* name, Sprite* sprite)
	{
		data[name] =
		{
			{"color",
				{
					{"r", sprite->color.r},
					{"g", sprite->color.g},
					{"b", sprite->color.b},
					{"a", sprite->color.a}
				}
			},
			{"scale", sprite->scale},
			{"width", sprite->width},
			{"height", sprite->height},
			{"step", sprite->step},
			{"maxSteps", sprite->maxSteps},
			{"columns", sprite->cols},
			{"rows", sprite->rows},
			{"textureID", sprite->textureID},
			{"texturePath", sprite->texPath}
		};
	}

	Sprite* loadSprite(json& data, const char* name)
	{
		Sprite* sprite = new Sprite();
		auto s = data["sprite"];
		auto c = s["color"];
		c["r"].get_to(sprite->color.r);
		c["g"].get_to(sprite->color.g);
		c["b"].get_to(sprite->color.b);
		c["a"].get_to(sprite->color.a);
		s["scale"].get_to(sprite->scale);
		s["width"].get_to(sprite->width);
		s["height"].get_to(sprite->height);
		s["step"].get_to(sprite->step);
		s["maxSteps"].get_to(sprite->maxSteps);
		s["columns"].get_to(sprite->cols);
		s["rows"].get_to(sprite->rows);
		s["textureID"].get_to(sprite->textureID);
		s["texturePath"].get_to(sprite->texPath);

		return sprite;
	}

	void Serializer::save(Cell* toSave, const char* path)
	{
		std::filesystem::path filePath = std::filesystem::path("save") / path;
		std::filesystem::create_directories(filePath.parent_path());

		if (!toSave) return;

		json data;

		if (toSave->sprite)
		{
			saveSprite(data, "sprite", toSave->sprite);
		}
		data["partColor"] =
		{
			{"r", toSave->partColor.r},
			{"g", toSave->partColor.g},
			{"b", toSave->partColor.b},
			{"a", toSave->partColor.a}
		};

		data["parts"] = json::array();
		for (const auto& part : toSave->parts)
		{
			if (!part) continue;
			json p;
			p["type"] = part->type;
			p["id"] = part->instanceID;
			p["x"] = part->offsetX;
			p["y"] = part->offsetY;
			p["step"] = part->sprite.step;
			p["animateSpeed"] = part->animateSpeed;
			data["parts"].push_back(p);
		}

		data["stats"] =
		{
			{"speed", toSave->stats.speed},
			{"attack", toSave->stats.attack},
			{"defense", toSave->stats.defense}
		};

		std::ofstream out(filePath);
		if (!out.is_open())
		{
			std::cerr << "Failed to open file: " << filePath << std::endl;
			return;
		}
		
		out << data.dump(4);
		out.close();
	}

	Cell Serializer::load(const char* path)
	{
		std::ostringstream oss;
		oss << "save/" << path;

		std::ifstream f(oss.str());

		if (!f)
			throw std::runtime_error("ERROR: Failed to open file: " + oss.str());

		json data;

		try
		{
			data = json::parse(f);
		}
		catch (const std::exception& e)
		{
			throw std::runtime_error(std::string("ERROR: JSON parse error") + e.what());
		}

		Cell result = Cell();

		if (data.contains("sprite"))
		{
			result.sprite = loadSprite(data, "sprite");
		}

		if (data.contains("partColor"))
		{
			auto pc = data["partColor"];
			pc["r"].get_to(result.partColor.r);
			pc["g"].get_to(result.partColor.g);
			pc["b"].get_to(result.partColor.b);
			pc["a"].get_to(result.partColor.a);
		}

		if (data.contains("parts"))
		{
			for (auto& p : data["parts"])
			{
				Part* part;
				switch (p["type"].get<PartType>())
				{
				case PartType::Flagella:
					part = new Flagella();
					break;
				default:
					continue;
				}
				p["type"].get_to(part->type);
				p["id"].get_to(part->instanceID);
				p["x"].get_to(part->offsetX);
				p["y"].get_to(part->offsetY);
				p["step"].get_to(part->sprite.step);
				p["animateSpeed"].get_to(part->animateSpeed);
				result.parts.push_back(part);
			}
		}

		if (data.contains("stats"))
		{
			auto s = data["stats"];
			s["speed"].get_to(result.stats.speed);
			s["attack"].get_to(result.stats.attack);
			s["defense"].get_to(result.stats.defense);
		}

		return result;
	}
}
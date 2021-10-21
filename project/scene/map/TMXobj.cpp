#include "TMXobj.h"
#include <sstream>
#include <DxLib.h>

TMXobj::TMXobj()
{
	version_["1.7.2"] = 1;
}

TMXobj::~TMXobj()
{
}

bool TMXobj::LoadTMX(std::string FName)
{
	rapidxml::file<> tmxFName = FName.c_str();
	tmxDoc_.parse<0>(tmxFName.data());
	rapidxml::xml_node<>* mapnode =
		tmxDoc_.first_node("map");

	if (!CheckVersion(mapnode)) return false;

	auto tileSet = mapnode->first_node("tileset");

	std::string source =
		FName.substr(0, FName.find_last_of("/") + 1) +
		tileSet->first_attribute("source")->value();

	if (!LoadTSX(source))
	{
		return false;
	}

	firstGID_ = atrInt(tileSet, "firstgid");
	layerSize_ = atrInt(mapnode, "nextlayerid") - 1;
	worldArea_ = { atrInt(mapnode, "width") ,
					atrInt(mapnode, "height") };
	tileSize_ = { atrInt(mapnode, "tilewidth") ,
					atrInt(mapnode, "tileheight") };

	return SetMap();
}

bool TMXobj::LoadTSX(std::string FName)
{
	rapidxml::file<> tsxFName = FName.c_str();
	tsxDoc_.parse<0>(tsxFName.data());
	rapidxml::xml_node<>* tileSet =
		tsxDoc_.first_node("tileset");

	if (!CheckVersion(tileSet)) return false;

	auto node = tsxDoc_.first_node();

	auto image = tileSet->first_node("image");
	std::string source =
		FName.substr(0, FName.find_last_of("/") + 1) +
		image->first_attribute("source")->value();

	auto sizeX = atrInt(tileSet, "tilewidth" );
	auto sizeY = atrInt(tileSet, "tileheight");
	auto cntX  = atrInt(tileSet, "columns"	 );
	auto cntY  = atrInt(tileSet, "tilecount" ) / cntX;

	mapImage_.resize(cntX * cntY);
	LoadDivGraph(source.c_str(), cntX * cntY,
		cntX , cntY, sizeX, sizeY,
		&mapImage_[0], true);

	return true;
}

bool TMXobj::SetMap(void)
{
	rapidxml::xml_node<>* mapnode =
		tmxDoc_.first_node("map");
	if (!mapnode)
	{
		return false;
	}

	auto layernode = mapnode->first_node("layer");
	if (!layernode)
	{
		return false;
	}

	do
	{
		auto layer = mapData_.try_emplace
		(layernode->first_attribute("name")->value());

		if (layer.second)
		{
			layer.first->second.resize
			(worldArea_.x_ * worldArea_.y_);
		}

		std::stringstream dataStream;
		dataStream << layernode->first_node("data")->
						first_node()->value();

		for (auto& data : layer.first->second)
		{
			std::string numStr;
			getline(dataStream, numStr, ',');
			data = atoi(numStr.c_str());
		}

		layernode = layernode->next_sibling("layer");

	} while (layernode);

	return true;
}

const int TMXobj::GetMapData(std::string layer, Vector2 pos)
{
	if (!mapData_.count(layer))
	{
		return 0;
	}

	Vector2 mas = pos / tileSize_;
	int num = mas.y_ * worldArea_.x_ + mas.x_;

	if (num < 0 || num >= mapData_[layer].size())
	{
		return 0;
	}

	return mapData_[layer][num];
}

const int TMXobj::GetMapData(std::string layer, int x, int y)
{
	if (!mapData_.count(layer))
	{
		return 0;
	}

	int num = y * worldArea_.x_ + x;

	if (num < 0 || num > mapData_[layer].size())
	{
		return 0;
	}

	return mapData_[layer][num];
}

void TMXobj::ChangeChip(std::string layer, Vector2 pos, int after)
{
	if (!mapData_.count(layer))
	{
		return;
	}

	int num = pos.y_ * worldArea_.x_ + pos.x_;

	if (num < 0 || num >= mapData_[layer].size())
	{
		return;
	}

	mapData_[layer][num] = after;
}

bool TMXobj::CheckVersion(rapidxml::xml_node<>* node)
{
	if (!node)
	{
		return false;
	}

	rapidxml::xml_attribute<>* tiledversion =
		node->first_attribute("tiledversion");

	char* tVer = tiledversion->value();
	if (!version_.count(tVer))
	{
		return false;
	}
	if (!version_[tVer])
	{
		return false;
	}
	return true;
}

int TMXobj::atrInt(rapidxml::xml_node<>* node, std::string name)
{
	return atoi(node->first_attribute(name.c_str())->value());
}

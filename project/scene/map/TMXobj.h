#pragma once

#include <string>
#include <map>
#include <vector>
#include <list>
#include "../../Vector2.h"
#include "../../rapidxml/rapidxml.hpp"
#include "../../rapidxml/rapidxml_utils.hpp"

using MapData = std::map<std::string, std::vector<int>>;

class TMXobj
{
public:
	TMXobj();
	~TMXobj();

	bool LoadTMX(std::string FName);
	bool LoadTSX(std::string FName);
	bool SetMap(void);

	const Vector2& GetWorldArea(void) { return worldArea_; };
	const Vector2& GetTileSize(void) { return tileSize_; };
	const unsigned int GetFirstGID(void) { return firstGID_; };
	const unsigned int GetlayerSize(void) { return layerSize_; };

	const MapData& GetMapData(void) { return mapData_; };
	const int GetMapData(std::string layer, Vector2 pos);
	const int GetMapData(std::string layer, int x, int y);
	const std::vector<int>& GetImage(void) { return mapImage_; };

	void ChangeChip(std::string layer, Vector2 pos, int after);
private:
	bool CheckVersion(rapidxml::xml_node<>* node);
	int atrInt(rapidxml::xml_node<>* node, std::string name);

	std::map<std::string, int> version_;
	std::vector<int> mapImage_;

	// TMX
	rapidxml::xml_document<> tmxDoc_;
	unsigned int firstGID_;
	unsigned int layerSize_;
	Vector2 worldArea_;
	Vector2 tileSize_;
	MapData mapData_;

	// TSX
	rapidxml::xml_document<> tsxDoc_;
};


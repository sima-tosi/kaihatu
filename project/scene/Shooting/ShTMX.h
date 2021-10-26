#pragma once
#include "Shooting.h"
#include <string>
#include <vector>
#include "../../rapidxml/rapidxml.hpp"
#include "../../rapidxml/rapidxml_utils.hpp"

class ShTMX
{
public:
	ShTMX();
	~ShTMX();

	bool LoadTMX(std::string FName);
	std::vector<EnemyVecData> GetEnemyData(void);

private:
	int atrInt(rapidxml::xml_node<>* node, std::string name);
	double atrDouble(rapidxml::xml_node<>* node, std::string name);

	std::vector<EnemyVecData> enemyDataVec;

	// TMX
	rapidxml::xml_document<> tmxDoc_;
};


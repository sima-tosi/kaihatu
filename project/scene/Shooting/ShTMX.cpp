#include "ShTMX.h"
#include <sstream>

ShTMX::ShTMX()
{
	LoadTMX("image/Shooting/EnemyData.txt");
}

ShTMX::~ShTMX()
{
}

bool ShTMX::LoadTMX(std::string FName)
{
	rapidxml::file<> tmxFName = FName.c_str();
	tmxDoc_.parse<0>(tmxFName.data());
	rapidxml::xml_node<>* listNode =
		tmxDoc_.first_node("list");

	EnemyVecData enemyData;

	auto data = listNode->first_node();

	while (data)
	{
		enemyData.pos.x_ = atrInt(data, "x");
		enemyData.pos.y_ = atrInt(data, "y");
		enemyData.type   = (EnemyType)(atrInt(data, "type"));
		enemyData.time   = atrDouble(data, "time");

		enemyDataVec.push_back(enemyData);

		data = data->next_sibling();
	}

	return true;
}

std::vector<EnemyVecData> ShTMX::GetEnemyData(void)
{
	return enemyDataVec;
}

int ShTMX::atrInt(rapidxml::xml_node<>* node, std::string name)
{
	return atoi(node->first_attribute(name.c_str())->value());
}

double ShTMX::atrDouble(rapidxml::xml_node<>* node, std::string name)
{
	return atof(node->first_attribute(name.c_str())->value());
}

#include <map>
#include <vector>
#include <tuple>

#include "Player.h"
#include "Units.h"
#include "Shop.h"

using namespace std;

#ifndef GAME_H
#define GAME_H

class Game{
public:
	Game(){  // constructor
		shop = Shop();
		Player enemy;

		Peasant playerUnitPeasant;
		Footman playerUnitFootman;
		Archer playerUnitArcher;
		Griffon playerUnitGriffon;

		Creature* creature1 = &playerUnitPeasant;
		Creature* creature2 = &playerUnitFootman;
		Creature* creature3 = &playerUnitArcher;
		Creature* creature4 = &playerUnitGriffon;

		std::pair<Creature*, int> p1(creature1, 4);
		std::pair<Creature*, int> p2(creature2, 3);
		std::pair<Creature*, int> p3(creature3, 2);
		std::pair<Creature*, int> p4(creature4, 1);

		std::vector<pair<Creature*, int> > units;
		units.push_back(p1);
		units.push_back(p2);
		units.push_back(p3);
		units.push_back(p4);
		enemy.SetUnits(units);
		m_enemy = &enemy;
	}
	void MainMenu();
	void MainMenuTakeAction(string& action, bool& exit);
	void ShopMenu();
	void ShopMenuTakeAction(string& action, bool& exit);

	Shop* ReturnShop(){
		return &(this->shop);
	}
	Player* ReturnPlayer(){
		return this->m_player;
	}

protected:
	Player* m_player;
	Player* m_enemy;
	Shop shop;
};
#endif

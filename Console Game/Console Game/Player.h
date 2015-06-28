#include <tuple>
#include <vector>

#include "Units.h"

using namespace std;

#ifndef PLAYER_H
#define PLAYER_H

class Player{
public:
	Player(){  // (empty units, gold always 300)
		gold = 300;

		Creature* playerUnitPeasant = new Peasant;
		Creature* playerUnitFootman = new Footman;
		Creature* playerUnitArcher = new Archer;
		Creature* playerUnitGriffon = new Griffon;

		std::pair<Creature*, int>* p1 = new std::pair<Creature*, int>(playerUnitPeasant, 0);
		std::pair<Creature*, int>* p2 = new std::pair<Creature*, int>(playerUnitFootman, 0);
		std::pair<Creature*, int>* p3 = new std::pair<Creature*, int>(playerUnitArcher, 0);
		std::pair<Creature*, int>* p4 = new std::pair<Creature*, int>(playerUnitGriffon, 0);

		units.push_back(p1);
		units.push_back(p2);
		units.push_back(p3);
		units.push_back(p4);
	}
	Player(std::vector<pair<Creature*, int>* > units, int gold=300) : units(units), gold(gold){};  // (units, gold=300 default)
	int GetGold() const{
		return gold;
	}
	void SetGold(int g){
		gold = g;
	}
	vector<pair<Creature*, int>* >* ReturnUnits(){  // not a const; the units will be changed after being returned
		return &(this->units);
	}
	void SetUnits(vector<pair<Creature*, int>* > units){
		this->units = units;
	}
	virtual ~Player(){
		for (unsigned short i = 0; i < this->ReturnUnits()->size(); i++)  // deleting units
			delete this->ReturnUnits()->at(i)->first;
		for (unsigned short i = 0; i < this->ReturnUnits()->size(); i++)  // deleting pairs
			delete this->ReturnUnits()->at(i);
	}
protected:
	int gold;
	std::vector<pair<Creature*, int>* > units;
};
#endif

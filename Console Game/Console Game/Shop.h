#include <map>
#include <vector>
#include <tuple>

#include "Player.h"
#include "Units.h"

using namespace std;

#ifndef SHOP_H
#define SHOP_H

class Shop{
public:
	Shop(){
		units[peasant] = 30;
		units[footman] = 90;
		units[archer] = 50;
		units[griffon] = 150;
	}
	bool BuyUnit(Creatures cr, int count, Player* pl){
		if (pl->GetGold() >= count*units[cr]){
			switch (cr){
				case peasant : pl->ReturnUnits()->at(0).second + count; break;
				case footman:  pl->ReturnUnits()->at(1).second + count; break;
				case archer:   pl->ReturnUnits()->at(2).second + count; break;
				case griffon:  pl->ReturnUnits()->at(3).second + count; break;
			}
			return 1;
		}
		return 0;
	}

protected:
	std::map<Creatures, int> units;
};
#endif

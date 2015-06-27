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
	void BuyUnit(Creatures cr, int& count, Player* pl){
		if (pl->GetGold() >= count*units[cr]){
			switch (cr){
				case peasant : pl->ReturnUnits()->at(0)->second += count; break;
				case footman:  pl->ReturnUnits()->at(1)->second += count; break;
				case archer:   pl->ReturnUnits()->at(2)->second += count; break;
				case griffon:  pl->ReturnUnits()->at(3)->second += count; break;
			}
			pl->SetGold(pl->GetGold() - count*units[cr]);
			return;
		}
		cout << "Insufficient amount of gold." << endl << 
			"Gold required: " << count*units[cr] << endl <<
			"Current gold possessed: " << pl->GetGold() << endl <<
			count*units[cr] - pl->GetGold() << "more gold is necessary." << endl;
	}
	void PrintUnitsCost() const{
		cout << "Peasant - 30g" << endl <<
			"Footman - 90g" << endl <<
			"Archer - 50g" << endl <<
			"Griffon - 150g" << endl;
	}

protected:
	std::map<Creatures, int> units;
};
#endif

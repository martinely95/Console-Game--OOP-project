#include <map>
#include <vector>
#include <tuple>

#include "Battlefield.h"
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
	void BuyUnit(Creatures cr, int& count, Player* pl, Battlefield* bf){
		if (pl->GetGold() >= count*units[cr]){
			std::vector<std::pair<int, int> >* unitsCoords = pl->GetUnitsCoords();
			switch (cr){
				case peasant : 
					for (int i = 0; i < count; i++){
						Creature* playerUnitPeasant = new Peasant;
						std::vector<Creature*>* currPos = (*bf)[unitsCoords->at(0).first][unitsCoords->at(0).second];
						currPos->push_back(playerUnitPeasant);
					}					
					pl->ReturnUnits()->at(0)->second += count;
					cout << count << " peasant(s) purchased." << endl << endl;
					break;
				case footman:  
					for (int i = 0; i < count; i++){
						Creature* playerUnitFootman = new Footman;
						std::vector<Creature*>* currPos = (*bf)[unitsCoords->at(1).first][unitsCoords->at(1).second];
						currPos->push_back(playerUnitFootman);
					}
					pl->ReturnUnits()->at(1)->second += count; 
					cout << count << " footman(s) purchased." << endl << endl;
					break;
				case archer:   
					for (int i = 0; i < count; i++){
						Creature* playerUnitArcher = new Archer;
						std::vector<Creature*>* currPos = (*bf)[unitsCoords->at(2).first][unitsCoords->at(2).second];
						currPos->push_back(playerUnitArcher);
					}
					pl->ReturnUnits()->at(2)->second += count; 
					cout << count << " archer(s) purchased." << endl << endl;
					break;
				case griffon:  
					for (int i = 0; i < count; i++){
						Creature* playerUnitGriffon = new Griffon;
						std::vector<Creature*>* currPos = (*bf)[unitsCoords->at(3).first][unitsCoords->at(3).second];
						currPos->push_back(playerUnitGriffon);
					}
					pl->ReturnUnits()->at(3)->second += count; 
					cout << count << " griffon(s) purchased." << endl << endl;
					break;
			}
			pl->SetGold(pl->GetGold() - count*units[cr]);
			return;
		}
		cout << "Insufficient amount of gold." << endl << 
			"Gold required: " << count*units[cr] << endl <<
			"Current gold possessed: " << pl->GetGold() << endl <<
			count*units[cr] - pl->GetGold() << " more gold is necessary." << endl << endl;
	}
	void PrintUnitsCost() const{
		cout << "Peasant - 30g" << endl <<
			"Footman - 90g" << endl <<
			"Archer - 50g" << endl <<
			"Griffon - 150g" << endl << endl;
	}

protected:
	std::map<Creatures, int> units;
};
#endif

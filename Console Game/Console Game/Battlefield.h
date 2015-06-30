#include <vector>
#include <iostream>
#include <tuple>
#include <fstream>
#include <map>
#include <string>

#include "Units.h"

using namespace std;

#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

class Battlefield{
public:
	Battlefield(){
		for (int i = 0; i < SIZE_X; i++){
			std::vector<std::vector<Creature*>* > row(SIZE_Y);
			this->field.push_back(row);
		}
		for (int i = 0; i < 10; i += 3){
			std::pair<int, int> coords(0, i);
			this->initCoords.push_back(coords);
		}
		for (int i = 0; i < 10; i += 3){
			std::pair<int, int> coords(9, i);
			this->initCoords.push_back(coords);
		}
	}
	Battlefield(Player* me, Player* enemy) : Battlefield() {
		//initially the player has empty units
		for (int i = 0; i < 4; i++){
			std::vector<Creature*>* units = new std::vector<Creature*>();
			int x = initCoords[i].first;
			int y = initCoords[i].second;
			this->field[x][y] = units;
			int count = me->ReturnUnits()->at(i)->second;
			Creatures type = me->ReturnUnits()->at(i)->first->GetType();
			if (count){
				for (int i = 0; i < count; i++){
					switch (type){
						case Creatures::peasant:{
							Creature* playerUnitPeasant = new Peasant;
							this->field[x][y]->push_back(playerUnitPeasant);
							break;
						}
						case Creatures::footman:{
							Creature* playerUnitFootman = new Footman;
							this->field[x][y]->push_back(playerUnitFootman);
							break;
						}
						case Creatures::archer:{
							Creature* playerUnitArcher = new Archer;
							this->field[x][y]->push_back(playerUnitArcher);
							break;
						}
						case Creatures::griffon:{
							Creature* playerUnitGriffon = new Griffon;
							this->field[x][y]->push_back(playerUnitGriffon);
							break;
						}
					}
				}
			}
		}
		//initializing enemy units:
		for (int i = 4; i < 8; i++){
			std::vector<Creature*>* units = new std::vector<Creature*>();
			int x = initCoords[i].first;
			int y = initCoords[i].second;
			this->field[x][y] = units;
			int count = enemy->ReturnUnits()->at(i - 4)->second;
			Creatures type = enemy->ReturnUnits()->at(i - 4)->first->GetType();
			if (count){
				for (int i = 0; i < count; i++){
					switch (type){
						case Creatures::peasant:{
							Creature* playerUnitPeasant = new Peasant;
							playerUnitPeasant->SetOwnership("E");
							this->field[x][y]->push_back(playerUnitPeasant);
							break;
						}
						case Creatures::footman:{
							Creature* playerUnitFootman = new Footman;
							playerUnitFootman->SetOwnership("E");
							this->field[x][y]->push_back(playerUnitFootman);
							break;
						}
						case Creatures::archer:{
							Creature* playerUnitArcher = new Archer;
							playerUnitArcher->SetOwnership("E");
							this->field[x][y]->push_back(playerUnitArcher);
							break;
						}
						case Creatures::griffon:{
							Creature* playerUnitGriffon = new Griffon;
							playerUnitGriffon->SetOwnership("E");
							this->field[x][y]->push_back(playerUnitGriffon);
							break;
						}
					}
				}				 
			}
		}
	}
	void PrintBattlefield(std::string targetPath = "states\\", std::string targetFile = "state.txt", bool inFile = true){
		targetFile = targetPath + targetFile;
		std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
		std::fstream file;
		if (inFile){
			file.open(targetFile.c_str(), std::fstream::out | std::fstream::trunc);
			std::cout.rdbuf(file.rdbuf()); //redirect std::cout to state.txt!
		}	
		if (file.is_open() || !inFile) {
			std::map<std::string, int> units;
			for (int y = 9; y >= 0; y--){
				for (int x = 0; x < 10; x++){
					cout << "|";
					if ((field[x][y] != nullptr && field[x][y]->size() > 0)){
						std::string ownership = field[x][y]->at(0)->GetOwnership();
						int count = field[x][y]->size();
						switch (field[x][y]->at(0)->GetType()){
						case Creatures::archer: 
							cout << ownership << "A";
							units[ownership + "A"] += count; break;
						case Creatures::footman: 
							cout << ownership << "F"; 
							units[ownership + "F"] += count; break;
						case Creatures::griffon: 
							cout << ownership << "G"; 
							units[ownership + "G"] += count; break;
						case Creatures::hero: 
							cout << ownership << "errorHero"; 
							units[ownership + "H"] += count; break;
						case Creatures::nothing: 
							cout << ownership << "errorNothing"; 
							units[ownership + "Nothing"] += count; break;
						case Creatures::peasant: 
							cout << ownership << "P"; 
							units[ownership + "P"] += count; break;
						default: 
							cout << ownership << "error"; 
							units[ownership + "Error"] += count;
						}
					}
					else
						cout << "  ";
				}
				cout << "|" << endl;
			}

			typedef std::map<std::string, int>::iterator it_type;
			for (it_type iterator = units.begin(); iterator != units.end(); iterator++) {
				cout << iterator->first << " " << iterator->second << " ";
				// iterator->first = key
				// iterator->second = value
			}
			cout << " H 1 EH 1";
			cout << endl << endl;
			file.close();
		}
		else{
			cout << "Unable to open file!" << endl << endl;
			std::cout.rdbuf(coutbuf);
		}
		std::cout.rdbuf(coutbuf); //reset to standard output again

	}

	std::vector<std::vector<Creature*>* >& operator[](int id){
		try {
			return field[id];
		}
		catch (std::exception & ex) {
			cout << ex.what() << endl;
		}
	}
	std::vector<std::pair<int, int> >* ReturnInitCoords(){
		return &initCoords;
	}
protected:
	int SIZE_X = 10;
	int SIZE_Y = 10;
	//std::vector<std::vector<std::pair<Creature*, int>* > > field; // на 1 квадратче се разползагат всички единици от 1 тип за съответен играч
	std::vector<std::vector<std::vector<Creature*>* > > field; // на 1 квадратче се разползагат всички единици от 1 тип за съответен играч
	std::vector<std::pair<int, int> > initCoords;
};

#endif

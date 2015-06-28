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
			vector<std::pair<Creature*, int>* > row(SIZE_Y);
			this->field.push_back(row);
		}
	}
	Battlefield(Player* me, Player* enemy){
		for (int i = 0; i < SIZE_X; i++){
			vector<std::pair<Creature*, int>* > row(SIZE_Y);
			this->field.push_back(row);
		}

		this->field[0][0] = me->ReturnUnits()->at(0);
		this->field[0][3] = me->ReturnUnits()->at(1);
		this->field[0][6] = me->ReturnUnits()->at(2);
		this->field[0][9] = me->ReturnUnits()->at(3);

		this->field[9][0] = enemy->ReturnUnits()->at(0);
		this->field[9][3] = enemy->ReturnUnits()->at(1);
		this->field[9][6] = enemy->ReturnUnits()->at(2);
		this->field[9][9] = enemy->ReturnUnits()->at(3);
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
					if ((field[x][y] != nullptr)){
						std::string ownership = field[x][y]->first->GetOwnership();
						int count = field[x][y]->second;
						switch (field[x][y]->first->GetType()){
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
			cout << endl << endl;
			file.close();
		}
		else{
			cout << "Unable to open file!" << endl << endl;
			std::cout.rdbuf(coutbuf);
		}
		std::cout.rdbuf(coutbuf); //reset to standard output again

	}

	std::vector<std::pair<Creature*, int>* >& operator[](int id){
		try {
			return field[id];
		}
		catch (std::exception & ex) {
			cout << ex.what() << endl;
		}
	}

protected:
	int SIZE_X = 10;
	int SIZE_Y = 10;
	std::vector<std::vector<std::pair<Creature*, int>* > > field; // на 1 квадратче се разползагат всички единици от 1 тип за съответен играч
};

#endif

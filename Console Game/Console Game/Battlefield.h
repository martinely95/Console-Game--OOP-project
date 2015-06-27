#include <vector>
#include <iostream>
#include <tuple>

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

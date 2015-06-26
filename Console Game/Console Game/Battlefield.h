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
			vector<std::pair<Creature*, int> > row(SIZE_Y);
			this->field.push_back(row);
		}
	}
	std::vector<std::pair<Creature*, int> >& operator[](int id){
		try {
			return field[id];
		}
		catch (std::exception & ex) {
			cout << ex.what() << endl;
		}
	}

protected:
	const int SIZE_X = 10;
	const int SIZE_Y = 10;
	std::vector<std::vector<std::pair<Creature*, int> > > field; // на 1 квадратче се разползагат всички единици от 1 тип за съответен играч
};

#endif

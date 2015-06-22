#include <vector>
#include <iostream>

#include "Units.h"

using namespace std;

#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

class Battlefield{
public:
	Battlefield(){
		for (int i = 0; i < SIZE_X; i++){
			vector<Creature*> row(SIZE_Y);
			this->field.push_back(row);
		}
	}
	vector<Creature*>& operator[](int id){
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
	std::vector<std::vector<Creature*> > field;
};

#endif

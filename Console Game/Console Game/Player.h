#include <tuple>
#include <vector>

#include "Units.h"

using namespace std;

#ifndef PLAYER_H
#define PLAYER_H

class Player{
public:
	Player() : gold(300), units(std::vector<pair<Creature*, int> >()){};  // (empty units, gold always 300)
	Player(std::vector<pair<Creature*, int> > units, int gold=300) : units(units), gold(gold){};  // (units, gold=300 default)

protected:
	int gold;
	std::vector<pair<Creature*, int> > units;
};
#endif

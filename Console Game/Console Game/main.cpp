#include <iostream>
#include <conio.h>

#include "Game.h"
#include "Battlefield.h"

using namespace std;

int main(){
	Game game;
	game.Run();	

	cout << "Press enter to exit..." << endl;
	_getch();

	return 0;
}

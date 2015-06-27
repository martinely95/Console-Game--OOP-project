#include <iostream>
#include <cmath>
#include <fstream>
// create a folder if not exist
#include <windows.h>
#include <stdio.h>

#include "Split_StringToInt.h"
#include "Game.h"

using namespace std;

void Game::MainMenuTakeAction(string& action, bool& exit)
{
	std::vector<std::string> commands = split(action, ' ');
	if (commands.size() < 1)
		return;
	if (action == "start game")  // -започване на игра
	{
		if (this->endGame == true)	// ako zapo4vame nova igra
		{
			this->endGame = false;
			RestartGame();
		}
		GameMenu();
	}
	else if (action == "shop")  // - посещаване на магазина
	{
		ShopMenu();
	}
	else if (action == "exit")  // - излизане от играта
		exit = 1;
	else
	{
		cout << "Wrong input!" << endl;
		cout << endl;
	}
}

void Game::MainMenu()
{
	
	string action;
	bool exit = false;
	while (!exit)
	{
		cout << "Main menu." << endl;
		cout << "Available commands: " << endl;
		cout << "start game" << endl;
		cout << "shop" << endl;
		cout << "exit" << endl;
		cout << endl;
		getline(cin, action);
		cout << endl;
		MainMenuTakeAction(action, exit);
	}
}

void Game::ShopMenuTakeAction(string& action, bool& exit)
{
	std::vector<std::string> commands = split(action, ' ');
	if (commands.size() < 1)
		return;
	if (action == "show units and prices")  // изкарване на всички единици, които могат да бъдат закупени, както и техни цени
	{
		ReturnShop()->PrintUnitsCost();
	}
	else if (commands[0] == "buy")  // - закупуване на определен брой единици
	{
		if (ReturnPlayer() == nullptr || this->endGame == true){
			cout << "No game in progress. " << endl << endl;
			return;
		}
		if (commands.size() > 2) {
			int count = StringToInt(commands[2]);
			if (commands[1] == "peasant"){
				ReturnShop()->BuyUnit(Creatures::peasant, count, ReturnPlayer());
				cout << count << " peasant(s) purchased." << endl << endl;
			}
			else if (commands[1] == "archer"){
				ReturnShop()->BuyUnit(Creatures::archer, count, ReturnPlayer());
				cout << count << " archer(s) purchased." << endl << endl;
			}
			else if (commands[1] == "footman"){
				ReturnShop()->BuyUnit(Creatures::footman, count, ReturnPlayer());
				cout << count << " footman(s) purchased." << endl << endl;
			}
			else if (commands[1] == "griffon"){
				ReturnShop()->BuyUnit(Creatures::griffon, count, ReturnPlayer());
				cout << count << " griffon(s) purchased." << endl << endl;
			}
			else
				cout << "Invalid input. Please try again." << endl << endl;
		}
		else {
			cout << "Invalid input. Please try again." << endl << endl;
		}
	}
	else if (action == "current gold")  // - изкарване на наличното състояние злато, което има играчът
	{
		if (ReturnPlayer() == nullptr || this->endGame == true){
			cout << "No game in progress. " << endl << endl;
			return;
		}
		cout << "Current gold in possession: " << ReturnPlayer()->GetGold() << endl;
		cout << endl;
	}
	else if (action == "exit")
		exit = 1;
	else
	{
		cout << "Wrong input!" << endl;
		cout << endl;
	}
}

void Game::ShopMenu()
{

	string action;
	bool exit = false;
	while (!exit)
	{
		cout << "Shop menu." << endl;
		cout << "Available commands: " << endl;
		cout << "show units and prices" << endl;
		cout << "buy" << endl;
		cout << "current gold" << endl;
		cout << "exit" << endl;
		cout << endl;
		getline(cin, action);
		cout << endl;
		ShopMenuTakeAction(action, exit);
	}
}

void Game::GameMenuTakeAction(string& action, bool& exit)
{
	std::vector<std::string> commands = split(action, ' ');
	if (commands.size() < 1)
		return;
	if (commands[0] == "move")
	{
		/*
		- преместване на дадена единици на позиция на полето
		- да бъде реализирана чрез командата move <source coords> <destination coords>.
		Например ако на позиция (2,2) имаме грифон и искаме да го преместим на позиция (5,5), то командата ще е move (2,2) (5,5).
		Тук трябва да се правят проверки дали destination coordinates не е заето от друга единица и дали единицата може да ходи толкова далеч
		*/
		int a[2], b[2];
		a[0] = StringToInt(CharToString(commands[1][1]));
		a[1] = StringToInt(CharToString(commands[1][3]));
		b[0] = StringToInt(CharToString(commands[2][1]));
		b[1] = StringToInt(CharToString(commands[2][3]));
		Battlefield* bf = ReturnBattlefield();
		double distance = sqrt(pow(a[0] - b[0], 2) + pow(a[1] - b[1], 2));
		if (a[0] < 0 || a[0] > 9 || a[1] < 0 || a[1] > 9 || b[0] < 0 || b[0] > 9 || b[1] < 0 || b[1] > 9){
			cout << "Invalid coordinates." << endl << endl;
			return;
		}
		if ((*bf)[a[0]][a[1]] == nullptr){
			cout << "There is nothing to move." << endl << endl;
			return;
		}
		if ((*bf)[a[0]][a[1]]->second == 0){
			cout << "There is nothing to move. (0 units)" << endl << endl;
			return;
		}
		int allowedDistance = (*bf)[a[0]][a[1]]->first->GetStamina();
		if (distance > allowedDistance){
			cout << "Target coordinates are too far." << endl << endl;
			return;
		}
		if ((*bf)[b[0]][b[1]] == nullptr){
			(*bf)[b[0]][b[1]] = (*bf)[a[0]][a[1]];
			(*bf)[a[0]][a[1]] = nullptr;
			cout << "Successfully moved something from " << commands[1] << " to " << commands[2] << "." << endl << endl;
		}
		else
			cout << "There is already something at the target coordinates!" << endl << endl;
	}
	else if (commands[0] == "attack")  // - нападане на противникова единица
	{
		// not implemented yet
		/*
		-командата да е attack <source coords> <destination coords>.
		Например ако на(4, 4) имаме противников Footman, а на(2, 2) имаме наш Peasant, 
		с attack(2, 2) (4, 4) ще преместим Peasant - a на квадратче, 
		което е на 1 единица разстояние(например(3, 3)) и ще нападнем протовниковия Footman.
		*/
	}
	else if (action == "print current state")  // - принтиране във файл текущото състояние на полето
	{
		std::string targetPath = "states\\";
		std::string targetFile = targetPath + "state.txt";
		
		CreateDirectory(targetPath.c_str(), NULL);
		std::fstream file;
		file.open(targetFile.c_str(), std::fstream::out | std::fstream::trunc);
		if (file.is_open()) {
			file << " more lorem ipsum";

			file.close();
		}
		else
			cout << "Unable to open file!" << endl << endl;

		// not implemented yet
		/*
		- как са разположени единиците:
		- нашите единици да бъдат отбелязани така: P за Peasant, A за Archer, F за Footman, G за Griffon, H за Hero.
		- противниковите единици да бъдат отбелязани така: ЕP за Peasant, ЕA за Archer, ЕF за Footman, ЕG за Griffon, ЕH за Hero.
		- под таблицата да бъде изкарано колко единици има от всеки тип в момента на полето
		Например: P 10, A 14, F 20, G 3, H 1, EP 20, EA 40, EF 30, EG 8, EH 1
		*/
	}
	else if (action == "end move")  // -приключване на текущия ход.
	{
		// not implemented yet
		/*
		Когато приключим хода, противниковият играч трябва да изиграе хода си и да разположи своите единици, след което отново ние сме наред.
		*/
	}
	else if (action == "exit")
		exit = 1;
	else
	{
		cout << "Wrong input!" << endl;
		cout << endl;
	}
}

void Game::GameMenu()
{

	string action;
	bool exit = false;
	while (!exit)
	{
		cout << "Game menu." << endl; 	// също така трябва да изписва кой е на ход в момента: играч/ противник
		if (this->playerTurn) 
			cout << "Your turn." << endl;
		else
			cout << "Enemy's turn." << endl;
		cout << "Enter your desired actions." << endl;
		cout << "Available commands: " << endl;
		cout << "move" << endl;
		cout << "attack" << endl;
		cout << "print current state" << endl;
		cout << "end move" << endl;
		cout << "exit" << endl;
		cout << endl;
		getline(cin, action);
		cout << endl;
		GameMenuTakeAction(action, exit);
	}
}
#include <iostream>

#include "Split_StringToInt.h"
#include "Game.h"

using namespace std;

void Game::MainMenuTakeAction(string& action, bool& exit)
{
	std::vector<std::string> commands = split(action, ' ');
	if (action == "start game")  // -започване на игра
	{
		// not implemented yet
	}
	else if (action == "shop")  // - посещаване на магазина
	{
		// not implemented yet
	}
	else if (action == "exit")  // - излизане от играта
		exit = 1;
	else
		cout << "Wrong input!" << endl;
}

void Game::MainMenu()
{
	
	string action;
	bool exit = false;
	while (!exit)
	{
		cout << "Main menu." << endl;
		getline(cin, action);
		MainMenuTakeAction(action, exit);
	}
}

void Game::ShopMenuTakeAction(string& action, bool& exit)
{
	std::vector<std::string> commands = split(action, ' ');
	if (action == "show units and prices")  // изкарване на всички единици, които могат да бъдат закупени, както и техни цени
	{
		ReturnShop()->PrintUnitsCost();
	}
	else if (commands[0] == "buy")  // - закупуване на определен брой единици
	{
		int count = StringToInt(commands[2]);
		if (commands[1] == "peasant")
			ReturnShop()->BuyUnit(Creatures::peasant, count, ReturnPlayer());
		else if (commands[1] == "archer")
			ReturnShop()->BuyUnit(Creatures::archer, count, ReturnPlayer());
		else if (commands[1] == "footman")
			ReturnShop()->BuyUnit(Creatures::footman, count, ReturnPlayer());
		else if (commands[1] == "griffon")
			ReturnShop()->BuyUnit(Creatures::griffon, count, ReturnPlayer());
	}
	else if (action == "current gold")  // - изкарване на наличното състояние злато, което има играчът
	{
		cout << "Current gold in possession: " << ReturnPlayer()->GetGold() << endl;
	}
	else if (action == "exit")
		exit = 1;
	else
		cout << "Wrong input!" << endl;
}

void Game::ShopMenu()
{

	string action;
	bool exit = false;
	while (!exit)
	{
		cout << "Shop menu." << endl;
		getline(cin, action);
		ShopMenuTakeAction(action, exit);
	}
}

void Game::GameMenuTakeAction(string& action, bool& exit)
{
	std::vector<std::string> commands = split(action, ' ');
	if (commands[0] == "move")  // - преместване на дадена единици на позиция на полето
	{
		// not implemented yet
		/*
		- преместване на дадена единици на позиция на полето 
		- да бъде реализирана чрез командата move <source coords> <destination coords>. 
		Например ако на позиция (2,2) имаме грифон и искаме да го преместим на позиция (5,5), то командата ще е move (2,2) (5,5). 
		Тук трябва да се правят проверки дали destination coordinates не е заето от друга единица и дали единицата може да ходи толкова далеч
		*/
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
		cout << "Wrong input!" << endl;
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
		cout << "Enter your desired actions: " << endl;
		getline(cin, action);
		GameMenuTakeAction(action, exit);
	}
}
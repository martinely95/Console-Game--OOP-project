#include <iostream>

#include "Split_StringToInt.h"
#include "Game.h"

using namespace std;

void Game::MainMenuTakeAction(string& action, bool& exit)
{
	std::vector<std::string> commands = split(action, ' ');
	if (action == "start game")  // -��������� �� ����
	{
		// not implemented yet
	}
	else if (action == "shop")  // - ���������� �� ��������
	{
		// not implemented yet
	}
	else if (action == "exit")  // - �������� �� ������
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
	if (action == "show units and prices")  // ��������� �� ������ �������, ����� ����� �� ����� ��������, ����� � ����� ����
	{
		ReturnShop()->PrintUnitsCost();
	}
	else if (commands[0] == "buy")  // - ���������� �� ��������� ���� �������
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
	else if (action == "current gold")  // - ��������� �� ��������� ��������� �����, ����� ��� �������
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
		MainMenuTakeAction(action, exit);
	}
}
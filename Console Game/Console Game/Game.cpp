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
		ShopMenuTakeAction(action, exit);
	}
}

void Game::GameMenuTakeAction(string& action, bool& exit)
{
	std::vector<std::string> commands = split(action, ' ');
	if (commands[0] == "move")  // - ����������� �� ������ ������� �� ������� �� ������
	{
		// not implemented yet
		/*
		- ����������� �� ������ ������� �� ������� �� ������ 
		- �� ���� ����������� ���� ��������� move <source coords> <destination coords>. 
		�������� ��� �� ������� (2,2) ����� ������ � ������ �� �� ��������� �� ������� (5,5), �� ��������� �� � move (2,2) (5,5). 
		��� ������ �� �� ������ �������� ���� destination coordinates �� � ����� �� ����� ������� � ���� ��������� ���� �� ���� ������� �����
		*/
	}
	else if (commands[0] == "attack")  // - �������� �� ������������ �������
	{
		// not implemented yet
		/*
		-��������� �� � attack <source coords> <destination coords>.
		�������� ��� ��(4, 4) ����� ����������� Footman, � ��(2, 2) ����� ��� Peasant, 
		� attack(2, 2) (4, 4) �� ��������� Peasant - a �� ���������, 
		����� � �� 1 ������� ����������(��������(3, 3)) � �� �������� ������������� Footman.
		*/
	}
	else if (action == "print current state")  // - ���������� ��� ���� �������� ��������� �� ������
	{
		// not implemented yet
		/*
		- ��� �� ����������� ���������:
		- ������ ������� �� ����� ���������� ����: P �� Peasant, A �� Archer, F �� Footman, G �� Griffon, H �� Hero.
		- �������������� ������� �� ����� ���������� ����: �P �� Peasant, �A �� Archer, �F �� Footman, �G �� Griffon, �H �� Hero.
		- ��� ��������� �� ���� �������� ����� ������� ��� �� ����� ��� � ������� �� ������
		��������: P 10, A 14, F 20, G 3, H 1, EP 20, EA 40, EF 30, EG 8, EH 1
		*/
	}
	else if (action == "end move")  // -����������� �� ������� ���.
	{
		// not implemented yet
		/*
		������ ��������� ����, �������������� ����� ������ �� ������� ���� �� � �� ��������� ������ �������, ���� ����� ������ ��� ��� �����.
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
		cout << "Game menu." << endl; 	// ���� ���� ������ �� ������� ��� � �� ��� � �������: �����/ ���������
		if (this->playerTurn) 
			cout << "Your turn." << endl;
		else
			cout << "Enemy's turn." << endl;
		cout << "Enter your desired actions: " << endl;
		getline(cin, action);
		GameMenuTakeAction(action, exit);
	}
}
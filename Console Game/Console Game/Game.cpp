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
	if (action == "start game")  // -��������� �� ����
	{
		if (this->endGame == true)	// ako zapo4vame nova igra
		{
			this->endGame = false;
			RestartGame();
		}
		GameMenu();
	}
	else if (action == "shop")  // - ���������� �� ��������
	{
		ShopMenu();
	}
	else if (action == "exit")  // - �������� �� ������
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
	if (action == "show units and prices")  // ��������� �� ������ �������, ����� ����� �� ����� ��������, ����� � ����� ����
	{
		ReturnShop()->PrintUnitsCost();
	}
	else if (commands[0] == "buy")  // - ���������� �� ��������� ���� �������
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
	else if (action == "current gold")  // - ��������� �� ��������� ��������� �����, ����� ��� �������
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
		- ����������� �� ������ ������� �� ������� �� ������
		- �� ���� ����������� ���� ��������� move <source coords> <destination coords>.
		�������� ��� �� ������� (2,2) ����� ������ � ������ �� �� ��������� �� ������� (5,5), �� ��������� �� � move (2,2) (5,5).
		��� ������ �� �� ������ �������� ���� destination coordinates �� � ����� �� ����� ������� � ���� ��������� ���� �� ���� ������� �����
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
		cout << "Game menu." << endl; 	// ���� ���� ������ �� ������� ��� � �� ��� � �������: �����/ ���������
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
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
				ReturnShop()->BuyUnit(Creatures::peasant, count, ReturnPlayer(), ReturnBattlefield());
			}
			else if (commands[1] == "archer"){
				ReturnShop()->BuyUnit(Creatures::archer, count, ReturnPlayer(), ReturnBattlefield());
			}
			else if (commands[1] == "footman"){
				ReturnShop()->BuyUnit(Creatures::footman, count, ReturnPlayer(), ReturnBattlefield());
			}
			else if (commands[1] == "griffon"){
				ReturnShop()->BuyUnit(Creatures::griffon, count, ReturnPlayer(), ReturnBattlefield());
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
		std::vector<Creature*> **targetCoords = &(*bf)[b[0]][b[1]], **sourceCoords = &(*bf)[a[0]][a[1]];
		double distance = sqrt(pow(a[0] - b[0], 2) + pow(a[1] - b[1], 2));
		if (a[0] < 0 || a[0] > 9 || a[1] < 0 || a[1] > 9 || b[0] < 0 || b[0] > 9 || b[1] < 0 || b[1] > 9){
			cout << "Invalid coordinates." << endl << endl;
			return;
		}
		if (*sourceCoords == nullptr){
			cout << "There is nothing to move." << endl << endl;
			return;
		}
		if ((*sourceCoords)->size() == 0){
			cout << "There is nothing to move. (0 units)" << endl << endl;
			return;
		}
		int allowedDistance = (*sourceCoords)->at(0)->GetStamina();
		if (distance > allowedDistance){
			cout << "Target coordinates are too far." << endl << endl;
			return;
		}

		if (*targetCoords == nullptr){
			if ((*sourceCoords)->at(0)->GetUsed()){
				cout << "Units already used." << endl << endl;
				return;
			}
			*targetCoords = *sourceCoords;
			*sourceCoords = nullptr;
			for (int i = 0; i < (*sourceCoords)->size(); i++)
			{
				(*sourceCoords)->at(i)->SetUsed();
			}
			cout << "Successfully moved something from " << commands[1] << " to " << commands[2] << "." << endl << endl;
			//changing the coordinates in the player:
			ReturnPlayer()->ReturnUnitsCoords()->at((*targetCoords)->at(0)->GetType()).first = b[0];
			ReturnPlayer()->ReturnUnitsCoords()->at((*targetCoords)->at(0)->GetType()).second = b[1];
		}
		else
			cout << "There is already something at the target coordinates!" << endl << endl;
	}
	else if (commands[0] == "attack")  // - �������� �� ������������ �������
	{
		//attack with hero not implemented
		int a[2], b[2];
		a[0] = StringToInt(CharToString(commands[1][1]));
		a[1] = StringToInt(CharToString(commands[1][3]));
		b[0] = StringToInt(CharToString(commands[2][1]));
		b[1] = StringToInt(CharToString(commands[2][3]));
		Battlefield* bf = ReturnBattlefield();
		std::vector<Creature*> **targetCoords = &(*bf)[b[0]][b[1]], **sourceCoords = &(*bf)[a[0]][a[1]];
		double distance = sqrt(pow(a[0] - b[0], 2) + pow(a[1] - b[1], 2));
		if (a[0] < 0 || a[0] > 9 || a[1] < 0 || a[1] > 9 || b[0] < 0 || b[0] > 9 || b[1] < 0 || b[1] > 9){
			cout << "Invalid coordinates." << endl << endl;
			return;
		}
		if (*sourceCoords == nullptr){
			cout << "There is nothing to attack with." << endl << endl;
			return;
		}
		if ((*sourceCoords)->size() == 0){
			cout << "There is nothing to attack with. (0 units)" << endl << endl;
			return;
		}
		int allowedDistance = (*sourceCoords)->at(0)->GetAttackRange();
		if (distance > allowedDistance && allowedDistance != -1){
			cout << "Target coordinates are too far." << endl << endl;
			return;
		}
		if (*targetCoords != nullptr && (*targetCoords)->size() > 0){
			if ((*sourceCoords)->at(0)->GetUsed()){
				cout << "Units already used." << endl << endl;
				return;
			}
			std::string isEnemyLetter = (*targetCoords)->at(0)->GetOwnership();
			//ednovremenno 6te badat atakuvani vsi4ki i vsi4ki 6te imat = health
			double attackPower = (*sourceCoords)->at(0)->GetDamage() * (*sourceCoords)->size();
			double defensePower = (*targetCoords)->at(0)->GetDefense() * (*targetCoords)->size();
			double damagePerUnit = (attackPower - defensePower) / (*targetCoords)->size();
			unsigned short i = 0;
			while (i < (*targetCoords)->size()){
				double newHealth = (*targetCoords)->at(i)->GetHealth() - damagePerUnit;
				if (newHealth > 0)
					(*targetCoords)->at(i)->SetHealth(newHealth);
				else{
					// go home if dead
					std::vector<Creature*>  **homeCoordinates;
					if (isEnemyLetter == "E"){
						if (!(--ReturnEnemy()->ReturnUnits()->at((*targetCoords)->at(0)->GetType())->second)){
							int homeX = bf->ReturnInitCoords()->at((*targetCoords)->at(0)->GetType() + 4).first;
							int homeY = bf->ReturnInitCoords()->at((*targetCoords)->at(0)->GetType() + 4).second;
							homeCoordinates = &(*bf)[homeX][homeY];
						}
					}
					else{
						if (!(--ReturnPlayer()->ReturnUnits()->at((*targetCoords)->at(0)->GetType())->second)){
							int homeX = bf->ReturnInitCoords()->at((*targetCoords)->at(0)->GetType()).first;
							int homeY = bf->ReturnInitCoords()->at((*targetCoords)->at(0)->GetType()).second;
							homeCoordinates = &(*bf)[homeX][homeY];
						}
					}
					delete (*targetCoords)->at(i);	
					(*targetCoords)->erase((*targetCoords)->begin() + i);
					if ((*targetCoords)->size() < 1){
						//restart position on field and in player
						*homeCoordinates = *targetCoords;
						*targetCoords = nullptr;
						break;
					}
					i--;
				}
				i++;
			}
			for (int i = 0; i < (*sourceCoords)->size(); i++)
			{
				(*sourceCoords)->at(i)->SetUsed();
			}
			cout << "Successfully attacked something from " << commands[1] << " at " << commands[2] << "." << endl << endl;
		}
		else{
			cout << "There is nothing to aim at." << endl << endl;
			return;
		}
		/*
		-��������� �� � attack <source coords> <destination coords>.
		�������� ��� ��(4, 4) ����� ����������� Footman, � ��(2, 2) ����� ��� Peasant, 
		� attack(2, 2) (4, 4) �� ��������� Peasant - a �� ���������, 
		����� � �� 1 ������� ����������(��������(3, 3)) � �� �������� ������������� Footman.
		*/
	}
	else if (action.substr(0, 19) == "print current state")  // - ���������� ��� ���� �������� ��������� �� ������
	{
		std::string targetPath = "states\\";
		std::string targetFile = "state.txt";  // "states\\state.txt"
		
		CreateDirectory(targetPath.c_str(), NULL);
		Battlefield* bf = ReturnBattlefield();
		bool inFile = true;
		if (action.size() == 21){
			inFile = bool(StringToInt(action.substr(20)));
		}
		bf->PrintBattlefield(targetPath, targetFile, inFile);
		if (inFile)
			cout << "Current state is printed in folder\\file: states\\state.txt" << endl << endl;
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
		EnemyTurn();
		EndGame();
		for (int y = 9; y >= 0; y--){
			for (int x = 0; x < 10; x++){
				if ((field[x][y] != nullptr && field[x][y]->size() > 0)){
					for (int i = 0; i < field[x][y]->size(); i++)
					{
						field[x][y]->at(i)->SetUsed(false);
					}
				}
			}
		}
		
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
	while (!exit && !endGame)
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

void Game::EnemyTurn(){
	// not implemented yet; artificial intelligence
}
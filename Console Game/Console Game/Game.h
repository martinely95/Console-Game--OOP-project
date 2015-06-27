#include <map>
#include <vector>
#include <tuple>

#include "Player.h"
#include "Units.h"
#include "Shop.h"
#include "Battlefield.h"

using namespace std;

#ifndef GAME_H
#define GAME_H

class Game{
public:
	Game(){  // constructor
		shop = Shop();
		m_enemy = new Player;
		//Player enemy = Player();
		//m_enemy = &enemy;
		/*Creature* playerUnitPeasant = new Peasant;
		Creature* playerUnitFootman = new Footman;
		Creature* playerUnitArcher = new Archer;
		Creature* playerUnitGriffon = new Griffon;*/

		/*Creature* creature1 = playerUnitPeasant;
		Creature* creature2 = playerUnitFootman;
		Creature* creature3 = playerUnitArcher;
		Creature* creature4 = playerUnitGriffon;*/

		/*std::pair<Creature*, int> p1(playerUnitPeasant, 1);
		std::pair<Creature*, int> p2(playerUnitFootman, 0);
		std::pair<Creature*, int> p3(playerUnitArcher, 1);
		std::pair<Creature*, int> p4(playerUnitGriffon, 1);*/

		m_enemy->SetGold(10);

		std::vector<pair<Creature*, int>* >* units1 = m_enemy->ReturnUnits();
		units1->at(0)->second = 1;
		units1->at(2)->second = 1;
		units1->at(3)->second = 1;
		/*units1.push_back(p1);
		units1.push_back(p2);
		units1.push_back(p3);
		units1.push_back(p4);
		m_enemy->SetUnits(units1);
		m_enemy = &enemy;*/

		m_player = new Player;
		//m_player = &player;
		field = Battlefield(m_player, m_enemy);
	}
	void MainMenu();
	void MainMenuTakeAction(string& action, bool& exit);
	void ShopMenu();
	void ShopMenuTakeAction(string& action, bool& exit);
	void GameMenu();
	void GameMenuTakeAction(string& action, bool& exit);

	void EnemyTurn(){

		//implement artificial intelligence
	}

	void EndGame(){
		// // tuk nai veroqtno 6te se proverqva dali nqkoi ima ostanali edinici i 
		// ako nqma 6te se promenq endGame = true i playerWins = true
		
		
		//izpisvame koi e spe4elil i kolko zlato ala bala



	}

	void Run(){
		MainMenu();
	}

	Shop* ReturnShop(){
		return &(this->shop);
	}
	Player* ReturnPlayer(){
		return this->m_player;
	}

protected:
	Player* m_player;
	Player* m_enemy;
	Shop shop;
	Battlefield field;
	bool playerTurn = true;
	bool endGame = false;
	bool playerWins = false;
};
#endif
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

		m_enemy = new Player(true);
		std::vector<pair<Creature*, int>* >* units1 = m_enemy->ReturnUnits();
		units1->at(0)->second = 1;
		units1->at(2)->second = 1;
		units1->at(3)->second = 1;
		units1->at(0)->first->SetOwnership("E");
		units1->at(1)->first->SetOwnership("E");
		units1->at(2)->first->SetOwnership("E");
		units1->at(3)->first->SetOwnership("E");
		m_enemy->SetGold(10);

		m_player = new Player;

		field = Battlefield(m_player, m_enemy);
	}
	void MainMenu();
	void MainMenuTakeAction(string& action, bool& exit);
	void ShopMenu();
	void ShopMenuTakeAction(string& action, bool& exit);
	void GameMenu();
	void GameMenuTakeAction(string& action, bool& exit);

	virtual ~Game(){
		delete m_enemy;
		delete m_player;
		// деструктор на player
		//деструктор на pair - те във units na player
		//	голямата 3ка - samo toi ostana
			//деструктурите да са виртуални

	}

	void RestartGame(){
		delete m_enemy;
		delete m_player;
		shop = Shop();

		m_enemy = new Player(true);
		std::vector<pair<Creature*, int>* >* units1 = m_enemy->ReturnUnits();
		units1->at(0)->second = 1;
		units1->at(2)->second = 1;
		units1->at(3)->second = 1;
		units1->at(0)->first->SetOwnership("E");
		units1->at(1)->first->SetOwnership("E");
		units1->at(2)->first->SetOwnership("E");
		units1->at(3)->first->SetOwnership("E");
		units1->at(4)->first->SetOwnership("E");
		m_enemy->SetGold(10);

		m_player = new Player;

		field = Battlefield(m_player, m_enemy);
	}

	void EnemyTurn();

	void EndGame(){
		// // tuk nai veroqtno 6te se proverqva dali nqkoi ima ostanali edinici i 
		// ako nqma 6te se promenq endGame = true i playerWins = true
		
		
		//izpisvame koi e spe4elil i kolko zlato ala bala



	}

	void Run(){
		MainMenu();
	}

	Battlefield* ReturnBattlefield(){
		return &(this->field);
	}
	Shop* ReturnShop(){
		return &(this->shop);
	}
	Player* ReturnPlayer(){
		return this->m_player;
	}
	Player* ReturnEnemy(){
		return this->m_enemy;
	}

protected:
	Player* m_player;
	Player* m_enemy;
	Shop shop;
	Battlefield field;
	bool playerTurn = true;
	bool endGame = true;
	bool playerWins = false;
};
#endif
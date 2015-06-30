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
		int count = 0, enCount = 0;
		for (int y = 9; y >= 0; y--){
			for (int x = 0; x < 10; x++){
				if ((field[x][y] != nullptr && field[x][y]->size() > 0)){
					std::string ownership = field[x][y]->at(0)->GetOwnership();
					if (ownership == " "){
						count++;
					}
					else{
						enCount++;
					}
				}
			}
		}
		if (!count){
			endGame = true;
			playerWins = false;
			cout << "End of game. You lose." << endl << endl;
			int newGold = ReturnPlayer()->GetGold() - 100;
			if (newGold > 0)
				ReturnPlayer()->SetGold(ReturnPlayer()->GetGold() - 100);
			else
				ReturnPlayer()->SetGold(0);
		}
		if (!enCount){
			endGame = true;
			playerWins = true;
			cout << "End of game. You win." << endl << endl;
			ReturnPlayer()->SetGold(ReturnPlayer()->GetGold() + 200);
		}
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
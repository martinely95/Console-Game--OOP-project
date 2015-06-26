#ifndef UNITS_H
#define UNITS_H

enum Creatures {
	peasant,
	footman,
	archer,
	griffon
};

class Creature{
public:
	Creature() : damage(1), defense(1), health(5), mana(3), stamina(3), critChance(1), attackRange(1){};
	Creature(int damage, int defense, int health, int mana, int stamina, int critChance, int attackRange) : 
		damage(damage), defense(defense), health(health), mana(mana), stamina(stamina), critChance(critChance), attackRange(attackRange){};
	
	int GetDamage() const{
		return damage;
	}
	int GetDefense() const{
		return defense;
	}
	int GetHealth() const{
		return health;
	}
	int GetMana() const{
		return mana;
	}
	int GetStamina() const{
		return stamina;
	}
	int GetCritChance() const{
		return critChance;
	}
	int GetAttackRange() const{
		return attackRange;
	}
	void SetDamage(int a){
		damage = a;
	}
	void SetDefense(int a){
		defense = a;
	}
	void SetHealth(int a){
		health = a;
	}
	void SetMana(int a){
		mana = a;
	}
	void SetStamina(int a){
		stamina = a;
	}
	void SetCritChance(int a){
		critChance = a;
	}
	void SetAttackRange(int a){
		attackRange = a;
	}
	// ����� ��������� �� �� �� �������; ������� �� �������?
	virtual void Attack() = 0;  // ����� �� ���������� damage �� ������ ������� �� ����������� ���������
	virtual void Move() = 0;  // ��� �������� ������ ������� �� 1 ��������� ������ �� ����� ���������

protected:
	int damage;
	int defense;  // defense �������� � ����� �� ���� �������� ������������ �����
	int	health;
	int mana;
	int stamina;  // stamina �������� ����� ����������� ������ ���� �� �� �������� ������ ��������
	int critChance;  // critChance �������� ������������ ���������� �� ������ ����� damage ��� �����
	int attackRange;  // �������� ����� � ������� �� �������
};

class Peasant : public Creature {
public:
	virtual void Attack(){
		// ��� �� ��� �� �������������
		// tuk nai veroqtno 6te se proverqva dali nqkoi ima ostanali edinici i 
		// ako nqma 6te se promenq endGame = true i playerWins = true
	}
	virtual void Move(){
		//��� �� ��� �� �������������
	}
};

class Footman : public Creature {
public:
	Footman() : Creature() {
		this->stamina = 4;
		this->damage = 3;
	}
	virtual void Attack(){
		// ��� �� ��� �� �������������
	}
	virtual void Move(){
		// ��� �� ��� �� �������������
	}
};

class Archer : public Creature {
public:
	Archer() : Creature() {
		this->attackRange = -1;  // atakuva navsqkade
		this->damage = 2;
	}
	virtual void Attack(){
		// ��� �� ��� �� �������������
	}
	virtual void Move(){
		// ��� �� ��� �� �������������
	}
};

class Griffon : public Creature {
public:
	Griffon() : Creature() {
		this->stamina = 5;
		this->attackRange = 2;
		this->damage = 4;
	}
	virtual void Attack(){
		// ��� �� ��� �� �������������
	}
	virtual void Move(){
		// ��� �� ��� �� �������������
	}
};

class Hero : public Creature {
public:
	Hero() : Creature() {
		this->stamina = 0; // ne moje da se mesti po poleto
		this->attackRange = -1; // atakuva navsqkade
		this->damage = 2;
	}
	virtual void Attack(){
		// ��� �� ��� �� �������������
	}
	virtual void Move(){
		// ��� �� ��� �� �������������
	}
};

#endif

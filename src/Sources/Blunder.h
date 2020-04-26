#pragma once
#include "Equipment.h"
class Blunder :
	public Equipment
{
private:
	equipType type_;
	int ad_ = 0;
	double crit_ = 0;
	double bulletSpeed_ = 0;
	double distRate_ = 0;
	double disRange_ = 0;

public:
	Blunder(Texture* texture, string name, string desc, double price, int ad, double distRate, double crit, double disRange, equipType type, double bulletSpeed) :
		Equipment(texture, name, desc, price, type), ad_(ad), crit_(crit), distRate_(distRate), disRange_(disRange), type_(type), bulletSpeed_(bulletSpeed) {
		initStats();
	};
	virtual ~Blunder() {};

	//Equipar dicho equipamiento
	virtual void equip(Player* player);

	//Desequiparlo y perder sus stats
	virtual void remove(Player* player);

	virtual void writeStats() {
		std::cout << type_ << "\n";
		std::cout << "ad: " << ad_ << "\n";
		std::cout << "distRate: " << distRate_ << "\n";
	};
	//Devuelve el tipo del arma
	inline virtual equipType getType() const { return type_; };
	//Devuelve la velocidad de las balas
	inline double getBulletSpeed() { return bulletSpeed_; }
	//Inicializa los stats de la pistola
	void initStats();
};


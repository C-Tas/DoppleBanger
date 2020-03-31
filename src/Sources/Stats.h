#pragma once

struct Stats
{
	int health_ = 0;
	int mana_ = 0;
	double manaReg_ = 0;
	int armor_ = 0;
	int ad_ = 0; //Attack damage
	int ap_ = 0; //Ability power (da�o de habilidades y armas a distancia?)
	int crit_ = 0;
	int range_ = 0;
	int moveSpeed_ = 0;
	double meleeRate_ = 0;
	double distRate_ = 0;

	Stats(int health, int mana, int manaReg, int armor, int ad, int ap, int crit, int range, int moveSpeed, double meleeRate, double distRate) :
		health_(health), mana_(mana), manaReg_(manaReg), armor_(armor), ad_(ad), ap_(ap), crit_(crit), range_(range), moveSpeed_(moveSpeed), meleeRate_(meleeRate), distRate_(distRate) {};

	Stats() {
		health_, mana_, manaReg_, armor_, ad_, ap_, crit_, range_, moveSpeed_, meleeRate_, distRate_ = 0;
	}
};
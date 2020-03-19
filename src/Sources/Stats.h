#pragma once

struct Stats
{
	int health_ = 0;
	int mana_ = 0;
	double manaReg_ = 0;
	int armor_ = 0;
	int ad_ = 0; //Attack damage
	int ap_ = 0; //Ability power (daño de habilidades y armas a distancia?)
	int crit_ = 0;
	int moveSpeed_ = 0;
	double meleeRate_ = 0;
	double distRate_ = 0;

	Stats(int health, int mana, double manaReg, int armor, int ad, int ap, int crit, int moveSpeed, double meleeRate, double distRate) :
		health_(health), mana_(mana), manaReg_(manaReg), armor_(armor), ad_(ad), ap_(ap), crit_(crit), moveSpeed_(moveSpeed), meleeRate_(meleeRate), distRate_(distRate) {};

	Stats() {
		health_, mana_, manaReg_, armor_, ad_, ap_, crit_, moveSpeed_, meleeRate_, distRate_ = 0;
	}
	Stats operator=(const Stats& v)const { Stats r; r.health_ = v.health_; r.mana_ = v.mana_; r.manaReg_ = v.manaReg_; r.armor_ = v.armor_; r.ad_ = v.ad_; r.ap_ = v.ap_; r.crit_ = v.crit_; r.moveSpeed_ = v.moveSpeed_; r.meleeRate_ = v.meleeRate_; r.distRate_ = v.distRate_; return r; };
};
#pragma once

struct Stats
{
	double health_ = 0;		//Vida de la entidad
	double mana_ = 0;		//Maná de la entidad
	double manaReg_ = 0;	//Regeneración del maná de la entidad
	double armor_ = 0;		//Armadura de la entidad
	double meleeDmg_ = 0;	//Ataque físico de la entidad
	double distDmg_ = 0;	//Danyo de habilidades y armas a distancia
	double crit_ = 0;		//Crítico de la entidad
	double meleeRange_ = 0;	//Rango del ataque a melee
	double moveSpeed_ = 0;	//Velocidad de movimiento de la entidad
	double meleeRate_ = 0;	//Cadencia de ataque melee
	double distRate_ = 0;	//Cadencia de ataque a distancia

	Stats(double health, double mana, double manaReg, double armor, double ad, double ap, double crit, double range, double moveSpeed, double meleeRate, double distRate) :
		health_(health), mana_(mana), manaReg_(manaReg), armor_(armor), meleeDmg_(ad), distDmg_(ap), crit_(crit), meleeRange_(range), moveSpeed_(moveSpeed), meleeRate_(meleeRate), distRate_(distRate) {};

	Stats() { health_, mana_, manaReg_, armor_, meleeDmg_, distDmg_, crit_, meleeRange_, moveSpeed_, meleeRate_, distRate_ = 0; }
};
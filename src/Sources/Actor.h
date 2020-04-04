#pragma once

#include "Dynamic.h"
#include "Stats.h"
#include <vector>
class Actor : public Dynamic
{
protected:
	///<summary>vector de todas las texturas del actor</summary>
	vector<Texture*> textures_;
	///<summary>vector de la cantidad de frames de la textura correspondiente del actor</summary>
	vector<int> framesVector_;
	///<summary>Cambia la textura mientras se cumpla la condicion sino la devuelve a la que esta por defecto</summary>
	void changeTexture(bool condition, int animation);
///<summary>Constructor de la clase Actor</summary>
	Actor(Application* app, vector<Texture*> textures, Vector2D pos, Vector2D scale, SDL_Rect collisionArea, SDL_Rect frame = { 0,0,0,0 }, vector<int> numberFrames = { 0 })
		: Dynamic(app, textures[0], pos, scale, collisionArea,frame,numberFrames[0]),textures_(textures), framesVector_(numberFrames) {};
	Stats currStats_;
	///<summary>Destructor de la clase Actor</summary>
	virtual ~Actor(){};

	//<summary>Inicializa todas las stats</summary>
	void initStats(int health, int mana, int manaReg, int armor, int ad, int ap, int crit, int range, double moveSpeed, double meleeRate, double distRate);

public:
	///<summary>Detiene el movimiento, por ejemplo, al colisionar con un obst�culo</summary>
	void stop() { dir_ = Vector2D(0, 0); }
#pragma region setters
	void setHealth(int stat) { currStats_.health_ = stat; };
	void setMana(int stat) { currStats_.mana_ = stat; };
	void setManaReg(double stat) { currStats_.manaReg_ = stat; };
	void setArmor(int stat) { currStats_.armor_ = stat; };
	void setAd(int stat) { currStats_.ad_ = stat; };
	void setAp(int stat) { currStats_.ap_ = stat; };
	void setCrit(int stat) { currStats_.crit_ = stat; };
	void setMoveSpeed(int stat) { currStats_.moveSpeed_ = stat; };
	void setMeleeRate(double stat) { currStats_.meleeRate_ = stat; };
	void setDistRate(double stat) { currStats_.distRate_ = stat; };
#pragma endregion

#pragma region getters
	int getHealth() { return currStats_.health_; };
	int getMana() { return currStats_.mana_; };
	double getManaReg() { return currStats_.manaReg_; };
	int getArmor() { return currStats_.armor_; };
	int getAd() { return currStats_.ad_; };
	int getAp() { return currStats_.ap_; };
	int getCrit() { return currStats_.crit_; };
	int getMoveSpeed() { return currStats_.moveSpeed_; };
	double getMeleeRate() { return currStats_.meleeRate_; };
	double getDistRate() { return currStats_.distRate_; };
#pragma endregion

#pragma region addition
	void addHealth(int stat) { currStats_.health_ += stat; };
	void addMana(int stat) { currStats_.mana_ += stat; };
	void addManaReg(double stat) { currStats_.manaReg_ += stat; };
	void addArmor(int stat) { currStats_.armor_ += stat; };
	void addAd(int stat) { currStats_.ad_ += stat; };
	void addAp(int stat) { currStats_.ap_ += stat; };
	void addCrit(int stat) { currStats_.crit_ += stat; };
	void addMoveSpeed(int stat) { currStats_.moveSpeed_ += stat; };
	void addMeleeRate(double stat) { currStats_.meleeRate_ += stat; };
	void addDistRate(double stat) { currStats_.distRate_ += stat; };
#pragma endregion

#pragma region substraction
	void removeHealth(int stat) { currStats_.health_ -= stat; };
	void removeMana(int stat) { currStats_.mana_ -= stat; };
	void removeManaReg(double stat) { currStats_.manaReg_ -= stat; };
	void removeArmor(int stat) { currStats_.armor_ -= stat; };
	void removeAd(int stat) { currStats_.ad_ -= stat; };
	void removeAp(int stat) { currStats_.ap_ -= stat; };
	void removeCrit(int stat) { currStats_.crit_ -= stat; };
	void removeMoveSpeed(int stat) { currStats_.moveSpeed_ -= stat; };
	void removeMeleeRate(double stat) { currStats_.meleeRate_ -= stat; };
	void removeDistRate(double stat) { currStats_.distRate_ -= stat; };
#pragma endregion
};

#pragma once

class Equipment;
class GameManager;
class Application;
class SRandBasedGenerator;

class RandEquipGen
{
private:
	Application* app_ = nullptr;
	GameManager* gameManager_ = nullptr;
	SRandBasedGenerator* rn_;
	//variables para las diferentes velocidades de las balas
	const double PISTOL_BULLET_SPEED = 1000;	
	const double SHOTGUN_BULLET_SPEED = 750;
	const double BLUNDERBUSS_BULLET_SPEED = 500;

public:
	RandEquipGen(Application* app);
	Equipment* genEquip();
	Equipment* genEquip(int type);
};
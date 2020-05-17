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
	SRandBasedGenerator* rn_ = nullptr;

public:
	RandEquipGen(Application* app);
	RandEquipGen() {};
	Equipment* genEquip();
	Equipment* genEquip(int type);
};
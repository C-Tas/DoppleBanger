#pragma once

class Equipment;
class GameManager;
class Application;
class SRandBasedGenerator;
class Item;

class RandEquipGen
{
private:
	Application* app_ = nullptr;
	GameManager* gameManager_ = nullptr;
	SRandBasedGenerator* rn_ = nullptr;

public:
	RandEquipGen(Application* app);
	Item* genEquip();
	Item* genEquip(int type);
};
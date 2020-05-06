#pragma once
#include "GameObject.h"

class Player;

enum class equipType {
	ArmorI, ArmorII,
	GlovesI, GlovesII,
	BootsI, BootsII,
	SwordI, SwordII,
	SaberI, SaberII,
	PistolI, PistolII,
	ShotgunI, ShotgunII,
	//Tamaño del enum
	Size
};
enum class potionType { Health, Mana, Speed, Armor, Damage, Crit };
enum class ObjectType { Equipment, Usable };
class Item : public GameObject
{
protected:
	double price_ = 0;
	double quantity_ = 0;
	ObjectType objectType_;
	Item(Application* app, ObjectType objectType, double quantity = 1) : GameObject(app, Vector2D(0, 0), Vector2D(0, 0)), quantity_(quantity), objectType_(objectType) {};
	virtual void initObject() = 0;
public:
	~Item() {};
	virtual bool update() = 0;
	virtual void equip(Player* player) = 0;
	virtual void remove(Player* player) = 0;

	#pragma region Getters
		double getQuantity() { return quantity_; };
		double getPrice() { return price_; };
		ObjectType getObjectType() { return objectType_; };
	#pragma endregion
	#pragma region Setters
		void setQuantity(double quantity) { quantity_ = quantity; };
		void setPrice(double price) { price_ = price; };
	#pragma endregion

};
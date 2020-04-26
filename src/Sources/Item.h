#pragma once

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
enum class potionType { Health, Mana, Speed, Damage, Armor, Crit };

class Item
{
protected:
	double price_ = 0;
	double quantity_ = 0;
	
	Item(double quantity = 1) : quantity_(quantity) {};
	virtual void initObject() = 0;
public:
	~Item() {};
	virtual bool update() = 0;
	virtual void equip(Player* player) = 0;
	virtual void remove(Player* player) = 0;

	#pragma region Getters
		double getQuantity() { return quantity_; };
		double getPrice() { return price_; };
	#pragma endregion
	#pragma region Setters
		void setQuantity(double quantity) { quantity_ = quantity; };
		void setPrice(double price) { price_ = price; };
	#pragma endregion

};
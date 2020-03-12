#pragma once
#include "Texture.h"




class Item
{
private:
	string itemName_, itemDescription_;
	Texture* itemTexture_;
	double itemQuantity_, itemPrice_;
	
public:
	Item(Texture* tex, string name, string desc, double quantity, double price) { itemTexture_ = tex; itemName_ = name; itemDescription_ = desc; itemQuantity_ = quantity; itemPrice_ = price; };
	Item() { itemTexture_ = nullptr; itemName_ = ""; itemDescription_ = ""; itemQuantity_ = 1; itemPrice_ = 0; };
	~Item() { itemTexture_ = nullptr; };
	void setItemDescription(string desc) { itemDescription_ = desc; };
	void setItemName(string name) { itemName_ = name; };
	void setItemTexture(Texture* tex) { itemTexture_ = tex; };
	void setItemQuantity(double d) { itemQuantity_ = d; };
	void setItemPrice(double name) { itemPrice_ = name; };

	string getItemDescription() { return itemDescription_; };
	string getItemName() { return itemName_; };
	Texture* getItemTexture() { return itemTexture_; };
	double getItemQuantity() { return itemQuantity_; };
	double getItemPrice() { return itemPrice_; };
};
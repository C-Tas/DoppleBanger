#pragma once
#include "Texture.h"


class Item
{
private:
	string itemName_, itemDescription_;
	Texture* itemTexture_;
	double itemQuantity_, itemPrice_;

public:

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
#pragma once
#include "Button.h"
#include "Item.h"
#include "Vector2D.h"

class Container : public Button
{
private:
	Item* item_;
	Texture* background_;
	Vector2D pos_, scale_;
public:
	void render() override;
	Container(Texture* texture, Texture* background, Vector2D pos, Vector2D scale, CallBackOnClick* callBack, Item* item);

	void setPos(Vector2D pos) { pos_ = pos; };
	void setScale(Vector2D scale) { scale_ = scale; };
	void setItem(Item* item) { item_ = item; };

	Vector2D getPos() { return pos_; };
	Vector2D getScale() { return scale_; };
	Item* getItem() { return item_; };
};


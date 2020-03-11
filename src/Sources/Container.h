#pragma once
#include "Button.h"
#include "Item.h"
#include "Vector2D.h"
///<summary>
//Clase creada para los inventarios que ayuda a mostrar la informacion de un objeto dado
///</summary>
class Container : public Button
{
private:
	Item* item_; //Item a mostrar
	Texture* background_; //Textura de fondo
	Vector2D pos_, scale_; //Posicion y escala del contenedor
public:
	const void draw() override;
	Container(Texture* texture, Texture* background, Vector2D pos, Vector2D scale, CallBackOnClick* callBack, Item* item);

	void setPos(Vector2D pos) { pos_ = pos; };
	void setScale(Vector2D scale) { scale_ = scale; };
	void setItem(Item* item) { item_ = item; };

	Vector2D getPos() { return pos_; };
	Vector2D getScale() { return scale_; };
	Item* getItem() { return item_; };
};


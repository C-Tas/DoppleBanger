#pragma once
#include "Collider.h"
#include "TextBox.h"

class NPC : public Collider {
protected:
	TextBox txtBox;
public:
	NPC(Application* app, SDL_Rect collisionArea, Texture* texture, Point2D pos, Vector2D scale) :
		Collider(app, collisionArea, texture, pos, scale), txtBox(TextBox(app)) {};
	virtual ~NPC() {};

	///<summary>Devuelve la caja de texto, hay que llamar al diálogo que se quiera</summary>
	TextBox getTextBox() { return txtBox; };

	///<summary>Lleva la animación del NPC</summary>
	virtual bool update() { /**/ return false; };
	virtual void onCollider() {};
};
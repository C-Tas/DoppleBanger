#pragma once
#include "Collider.h"
#include "TextBox.h"

class NPC : public Collider {
private:
	TextBox txtBox;
public:
	NPC(Application* app, SDL_Rect collisionArea, Texture* texture, Point2D pos, Vector2D scale) :
		Collider(app, collisionArea, texture, pos, scale), txtBox(TextBox(app)) {};
	virtual ~NPC() {};

	///<summary>Devuelve la caja de texto, hay que llamar al diálogo que se quiera</summary>
	TextBox getTextBox() { return txtBox; };

	///<summary>Lleva la animación del NPC</summary>
	virtual bool update() { /**/ return false; };
	///<summary>Renderiza la animación idle del NPC</summary>
	virtual void draw() const { texture_->render(destiny_, frame_); };
	virtual void onCollider() {};
};
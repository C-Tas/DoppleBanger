#pragma once
#include "Collider.h"
#include "TextBox.h"


class NPC : public Collider {
private:
	TextBox* txtBox_ = nullptr;
	Anim npcIdle = { 0, 0, 0, 0, ""};
	int npcType_;
	Uint32 lasFrame_ = 0;

#pragma region Animaciones
	const string NAME = "npcIdle";

	//Viejo
	const int NUM_FRAMES_ELDERMAN = 0;
	const uint W_FRAME_ELDERMAN = 0;
	const uint H_FRAME_ELDERMAN = 0;
	const int FRAME_RATE_ELDERMAN = 0;

	//Mercader
	const int NUM_FRAMES_MERCHANT = 0;
	const uint W_FRAME_MERCHANT = 0;
	const uint H_FRAME_MERCHANT = 0;
	const int FRAME_RATE_MERCHANT= 0;

	//Cocinera
	const int NUM_FRAMES_CHEF = 2;
	const uint W_FRAME_CHEF = 29;
	const uint H_FRAME_CHEF = 63;
	const int FRAME_RATE_CHEF= 500;

	//Morty
	const int NUM_FRAMES_MORTY = 0;
	const uint W_FRAME_MORTY = 0;
	const uint H_FRAME_MORTY = 0;
	const int FRAME_RATE_MORTY= 0;

	//Loro
	const int NUM_FRAMES_PARROT = 0;
	const uint W_FRAME_PARROT = 0;
	const uint H_FRAME_PARROT = 0;
	const int FRAME_RATE_PARROT = 0;

	//Esqueleto
	const int NUM_FRAMES_SKELETON = 9;
	const uint W_FRAME_SKELETON = 75;
	const uint H_FRAME_SKELETON = 80;
	const int FRAME_RATE_SKELETON = 200;
#pragma endregion

protected:
	virtual void initObject();
	virtual void initAnim();

public:
	NPC(Application* app, Texture* texture, Point2D pos, Vector2D scale, int npcType) :
		Collider(app, pos, scale) {
		texture_ = texture;
		npcType_ = npcType;
		txtBox_ = new TextBox(app);
		initObject();
	};
	virtual ~NPC() { delete txtBox_; };

	///<summary>Devuelve la caja de texto, hay que llamar al diálogo que se quiera</summary>
	TextBox* getTextBox() { return txtBox_; };

	///<summary>Lleva la animación del NPC</summary>
	virtual bool update() { updateFrame(); return false; };
	virtual void onCollider() {};
};
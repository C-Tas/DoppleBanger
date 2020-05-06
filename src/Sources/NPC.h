#pragma once
#include "Collider.h"
#include "TextBox.h"

class NPC : public Collider {
private:
	TextBox* txtBox_ = nullptr;
	Anim npcIdle = { 0, 0, 0, 0, true };
	Uint32 lasFrame_ = 0;
	int npcType_;

#pragma region Animaciones
	//Viejo
	const int NUM_FRAMES_ELDERMAN = 9;
	const int W_FRAME_ELDERMAN = 75;
	const int H_FRAME_ELDERMAN = 80;
	const int FRAME_RATE_ELDERMAN = 200;

	//Mercader
	const int NUM_FRAMES_MERCHANT =2;
	const int W_FRAME_MERCHANT = 300;
	const int H_FRAME_MERCHANT = 267;
	const int FRAME_RATE_MERCHANT= 500;

	//Cocinera
	const int NUM_FRAMES_CHEF = 2;
	const int W_FRAME_CHEF = 29;
	const int H_FRAME_CHEF = 63;
	const int FRAME_RATE_CHEF= 500;

	//Morty
	const int NUM_FRAMES_MORTY = 0;
	const int W_FRAME_MORTY = 0;
	const int H_FRAME_MORTY = 0;
	const int FRAME_RATE_MORTY= 0;

	//Loro
	const int NUM_FRAMES_PARROT = 0;
	const int W_FRAME_PARROT = 0;
	const int H_FRAME_PARROT = 0;
	const int FRAME_RATE_PARROT = 0;

	//Esqueleto
	const int NUM_FRAMES_SKELETON = 9;
	const int W_FRAME_SKELETON = 75;
	const int H_FRAME_SKELETON = 80;
	const int FRAME_RATE_SKELETON = 200;

	//Cartógrafa
	const int NUM_FRAMES_CARTOGRAPHER = 1;
	const int W_FRAME_CARTOGRAPHER = 50;
	const int H_FRAME_CARTOGRAPHER = 70;
	const int FRAME_RATE_CARTOGRAPHER = 200;
#pragma endregion

protected:
	virtual void initObject();
	virtual void initAnims();

public:
	//Constructor para crear un NPC, npcType = 0:viejo, 1:mercader, 2:chef, 3:Morty, 4:loro, 5:esqueleto
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
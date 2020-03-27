#pragma once

#include "Dynamic.h"
#include "Stats.h"
#include <vector>
class Actor : public Dynamic
{
protected:
	///<summary>vector de todas las texturas del actor</summary>
	vector<Texture*> textures_;
	///<summary>vector de la cantidad de frames de la textura correspondiente del actor</summary>
	vector<int> framesVector_;
	///<summary>Cambia la textura mientras se cumpla la condicion sino la devuelve a la que esta por defecto</summary>
	void changeTexture(bool condition, int animation);
///<summary>Constructor de la clase Actor</summary>
	Actor(Application* app, vector<Texture*> textures, Vector2D pos, Vector2D scale, SDL_Rect collisionArea, SDL_Rect frame = { 0,0,0,0 }, vector<int> numberFrames = { 0 })
		: Dynamic(app, textures[0], pos, scale, collisionArea,frame,numberFrames[0]),textures_(textures), framesVector_(numberFrames) {};
	Stats currStats_;
///<summary>Destructor de la clase Actor</summary>
	virtual ~Actor(){};
	//<summary>Inicializa todas las stats</summary>
	void initStats(int health, int mana, int manaReg, int armor, int ad, int ap, int crit, int range, double moveSpeed, double meleeRate, double distRate);

public:
	///<summary>Detiene el movimiento, por ejemplo, al colisionar con un obst�culo</summary>
	void stop() { dir_ = Vector2D(0, 0); }
};


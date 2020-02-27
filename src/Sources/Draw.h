#pragma once
#include "GameObject.h"
//#include "Texture.h" 

class Texture;//TODO´s:

class Draw : public GameObject
{
private:
	Texture* texture_;
protected:
	//Draw(Texture* texture = nullptr) : texture_(texture) {};
	Draw(Texture* texture=nullptr, Vector2D pos = { 0,0 }, Vector2D scale = {0,0}) :GameObject(pos, scale), texture_(texture) {};
public:
	virtual void draw() {};
};


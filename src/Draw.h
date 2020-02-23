#pragma once
#include "GameObject.h"
//#include "Texture.h" 

class Texture;//TODO´s:

class Draw : public GameObject
{
private:
	Texture* texture_;
protected:
	Draw(Texture* texture) : texture_(texture) {};
	virtual void render() {};
};


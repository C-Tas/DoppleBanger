#pragma once
#include "Application.h"
#include "Texture.h"
//#include "Draw.h"

class TextBoxManager {
protected:
	Application* app_ = nullptr;
public:
	TextBoxManager(Application* app) : app_(app) {};
	~TextBoxManager() {};

	void DialogChef(bool unlock);
	void DialogMorty(bool unlock);
};
#pragma once
#include "Draw.h"

//Clase pensada para elementos est�ticos que no dependen de la c�mara, como fondos de men�s, etc.
class VisualElement : public Draw
{
public:
	//Background
	VisualElement(Application* app, Texture* texture) : Draw(app, texture) {};
	//Otros elementos estaticos
	VisualElement(Application* app, Texture* texture, SDL_Rect dest) : Draw(app, texture, dest) {};
	~VisualElement() {};
	const virtual void draw() {
		if (currAnim_.numberFrames_ <= 0) texture_->render(getDestiny(), SDL_FLIP_NONE);
		else texture_->render(getDestiny(), frame_);
	};
};


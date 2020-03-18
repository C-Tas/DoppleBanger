#include "SkillState.h"
#include "Button.h"
#include "Texture.h"

void SkillState::initSkillState() {
	cout << "SKILLTATE" << endl;
	cout << "TIENES " << puntos << " PUNTOS" << endl;
	createButtons();
}

void SkillState::createButtons() {
	//RAMA 1
	Button* b1 = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), { 200,50 }, { 50,50 }, increaseBranch1);
	gameObjects_.push_back(b1);
	objectsToRender_.push_back(b1);

	//RAMA 2
	Button* b2 = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), { 300,50 }, { 50,50 }, increaseBranch2);
	gameObjects_.push_back(b2);
	objectsToRender_.push_back(b2);

	//RAMA 3
	Button* b3 = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), { 400,50 }, { 50,50 }, increaseBranch3);
	gameObjects_.push_back(b3);
	objectsToRender_.push_back(b3);

	//VOLVER
	Button* b4 = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), { 500,150 }, { 50,50 }, backToPreviousState);
	gameObjects_.push_back(b4);
	objectsToRender_.push_back(b4);

#ifdef _DEBUG
	cout << "creados los botones correctamente" << endl;
#endif
}

void SkillState::backToPreviousState(Application* app) {
	app->getStateMachine()->popState();
}

void SkillState::increaseBranch1(Application* app) {
	cout << "BOTON 1" << endl;
	/*rama1++;
	puntos--;
	cout << "TIENES " << puntos << " PUNTOS" << endl;
	cout << "PUNTOS RAMA 1: " << rama1 << endl;*/
};

void SkillState::increaseBranch2(Application* app) {
	cout << "BOTON 2" << endl;
	/*rama2++;
	puntos--;
	cout << "TIENES " << puntos << " PUNTOS" << endl;
	cout << "PUNTOS RAMA 2: " << rama2 << endl;*/
};

void SkillState::increaseBranch3(Application* app) {
	cout << "BOTON 3" << endl;
	/*rama3++;
	puntos--;
	cout << "TIENES " << puntos << " PUNTOS" << endl;
	cout << "PUNTOS RAMA 3: " << rama3 << endl;*/
};
#include "SkillState.h"
#include "Button.h"
#include "Texture.h"
#include "GameManager.h"

void SkillState::initSkillState() {
	#ifdef _DEBUG
	cout << "SKILLTATE" << endl;
	cout << "TIENES " << GameManager::instance()->getAchievementPoints() << " PUNTOS" << endl;
	cout << "PRECISION " << (int)GameManager::instance()->getPresicionPoints() << " PUNTOS" << endl;
	cout << "MELEE " << (int)GameManager::instance()->getMeleePoints() << " PUNTOS" << endl;
	cout << "GHOST " << (int)GameManager::instance()->getGhostPoints() << " PUNTOS" << endl;
	#endif
	createButtons();
}

void SkillState::createButtons() {
	//RAMA 1
	Button* b1 = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), { 200,50 }, { 50,50 }, increasePrecisionBranch);
	gameObjects_.push_back(b1);
	objectsToRender_.push_back(b1);

	//RAMA 2
	Button* b2 = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), { 300,50 }, { 50,50 }, increaseMeleeBranch);
	gameObjects_.push_back(b2);
	objectsToRender_.push_back(b2);

	//RAMA 3
	Button* b3 = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::Timon), { 400,50 }, { 50,50 }, increaseGhostBranch);
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

//
void SkillState::increasePrecisionBranch(Application* app) {
	if (GameManager::instance()->getAchievementPoints() > 0 && (int)GameManager::instance()->getPresicionPoints() < 100) {
		GameManager::instance()->setPrecisionPoints((int)GameManager::instance()->getPresicionPoints() + 1);
		GameManager::instance()->setArchievementPoints(GameManager::instance()->getAchievementPoints() - 1);
		cout << "PRECISION " << (int)GameManager::instance()->getPresicionPoints() << " PUNTOS" << endl;
	}
	cout << "TE QUEDAN " << (int)GameManager::instance()->getAchievementPoints() << " PUNTOS" << endl;
};

void SkillState::increaseMeleeBranch(Application* app) {
	if (GameManager::instance()->getAchievementPoints() > 0 && (int)GameManager::instance()->getMeleePoints() < 100) {
		GameManager::instance()->setMeleePoints((int)GameManager::instance()->getMeleePoints() + 1);
		GameManager::instance()->setArchievementPoints(GameManager::instance()->getAchievementPoints() - 1);
		cout << "MELEE " << (int)GameManager::instance()->getMeleePoints() << " PUNTOS" << endl;
	}
	cout << "TE QUEDAN " << (int)GameManager::instance()->getAchievementPoints() << " PUNTOS" << endl;
};

void SkillState::increaseGhostBranch(Application* app) {
	if (GameManager::instance()->getAchievementPoints() > 0 && (int)GameManager::instance()->getGhostPoints() < 100) {
		GameManager::instance()->setGhostPoints((int)GameManager::instance()->getGhostPoints() + 1);
		GameManager::instance()->setArchievementPoints(GameManager::instance()->getAchievementPoints() - 1);
		cout << "GHOST " << (int)GameManager::instance()->getGhostPoints() << " PUNTOS" << endl;
	}
	cout << "TE QUEDAN " << (int)GameManager::instance()->getAchievementPoints() << " PUNTOS" << endl;
};
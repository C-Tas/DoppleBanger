#include "SkillState.h"
#include "Button.h"
#include "Texture.h"
#include "GameManager.h"
#include "InventoryState.h"

void SkillState::initSkillState() {
	#ifdef _DEBUG
	cout << "SKILLTATE" << endl;
	cout << "TIENES " << GameManager::instance()->getAchievementPoints() << " PUNTOS" << endl;
	cout << "PRECISION " << (int)GameManager::instance()->getPresicionPoints() << " PUNTOS" << endl;
	cout << "MELEE " << (int)GameManager::instance()->getMeleePoints() << " PUNTOS" << endl;
	cout << "GHOST " << (int)GameManager::instance()->getGhostPoints() << " PUNTOS" << endl;
	#endif
	bg_ = new Draw(app_, app_->getTextureManager()->getTexture(Resources::TextureId::SkillMenu));
	objectsToRender_.push_back(bg_);
	gameObjects_.push_back(bg_);
	createButtons();
}

void SkillState::createButtons() {
	//Precision Button
	Button* precisionButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::ButtonUpgradeGreen), { 770,375 }, { 50,50 }, increasePrecisionBranch);
	gameObjects_.push_back(precisionButton);
	objectsToRender_.push_back(precisionButton);

	//Melee Button
	Button* meleeButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::ButtonUpgradeYellow), { 770,525 }, { 50,50 }, increaseMeleeBranch);
	gameObjects_.push_back(meleeButton);
	objectsToRender_.push_back(meleeButton);

	//Ghost Button
	Button* ghostButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::ButtonUpgradeBlue), { 770,675 }, { 50,50 }, increaseGhostBranch);
	gameObjects_.push_back(ghostButton);
	objectsToRender_.push_back(ghostButton);

	//Back Button
	Button* backButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::ButtonX), { 1439,214 }, { 60,53 }, backToPreviousState);
	gameObjects_.push_back(backButton);
	objectsToRender_.push_back(backButton);

	//Inventary Button
	Button* inventaryButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::ButtonX), { 175,80 }, { 50,50 }, goToInventaryState);
	gameObjects_.push_back(inventaryButton);
	objectsToRender_.push_back(inventaryButton);

#ifdef _DEBUG
	cout << "creados los botones correctamente" << endl;
#endif
}

void SkillState::backToPreviousState(Application* app) {
	app->getStateMachine()->popState();
}

void SkillState::goToInventaryState(Application* app) {
	cout << "Cambia a inventoryState" << endl;
	//app->getStateMachine()->changeState(new InventoryState(app));
}

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
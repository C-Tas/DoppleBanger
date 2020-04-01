#include "SkillState.h"
#include "Button.h"
#include "Texture.h"
#include "GameManager.h"
#include "InventoryState.h"


void SkillState::update()
{
	GameState::update();
	updateBars();
	//updateSkillS();
}

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
	createBars();
}

void SkillState::createBars() {
	//PrecisionBar
	bars_[0] = new Draw(app_, app_->getTextureManager()->getTexture(Resources::TextureId::GreenBar), { 190, 390, 530, 20 });		// 150 es la distancia entre las barras
	//bars_[0]->setDestiny(*SDL_Rect({ 190, 390, 430, 90 }));
	objectsToRender_.push_back(bars_[0]);
	gameObjects_.push_back(bars_[0]);

	//MeleeBar
	bars_[1] = new Draw(app_, app_->getTextureManager()->getTexture(Resources::TextureId::YellowBar), { 190, 540, 530, 20 });		// 150 es la distancia entre las barras
	objectsToRender_.push_back(bars_[1]);
	gameObjects_.push_back(bars_[1]);

	//GhostBar
	bars_[2] = new Draw(app_, app_->getTextureManager()->getTexture(Resources::TextureId::BlueBar), { 190, 690, 530, 20 });		// 150 es la distancia entre las barras
	objectsToRender_.push_back(bars_[2]);
	gameObjects_.push_back(bars_[2]);

	updateBars();

	//Marcos de las barras
	//No me deja usar emptyBars_.size(), por eso está el 3 a pelo
	for (int i = 0; i < 3; i++) {
		emptyBars_[i] = new Draw(app_, app_->getTextureManager()->getTexture(Resources::TextureId::EmptyBar), { 190, 390 + i * 150, 530, 20 });		// 150 es la distancia entre las barras
		objectsToRender_.push_back(emptyBars_[i]);
		gameObjects_.push_back(emptyBars_[i]);
	}
}

void SkillState::updateBars() { 
	for (int i = 0; i < 3; i++) {
		SDL_Rect aux = bars_[i]->getDestiny();
		switch (i)
		{
		case 0:
			aux.w = (530 * (int)GameManager::instance()->getPresicionPoints() / 100);
			break;
		case 1:
			aux.w = (530 * (int)GameManager::instance()->getMeleePoints() / 100);
			break;
		case 2:
			aux.w = (530 * (int)GameManager::instance()->getGhostPoints() / 100);
			break;
		default:
			break;
		}
		bars_[i]->setDestiny(aux);
	}
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
}

void SkillState::backToPreviousState(Application* app) {
	app->getStateMachine()->popState();
}

void SkillState::goToInventaryState(Application* app) {
	cout << "Cambia a inventoryState" << endl;
	//app->getStateMachine()->changeState(new InventoryState(app));
}

void SkillState::increasePrecisionBranch(Application* app) {
	if (GameManager::instance()->getAchievementPoints() > 0 && (int)GameManager::instance()->getPresicionPoints() < 100) {	//Comprueba que tenga puntos de hazaña que invertir y que la rama no tenga ya 100 puntos (máximo)
		GameManager::instance()->setPrecisionPoints((int)GameManager::instance()->getPresicionPoints() + 1);				//Aumenta en uno los puntos de esta rama
		GameManager::instance()->setArchievementPoints(GameManager::instance()->getAchievementPoints() - 1);				//Reduce en uno los puntos de hazaña
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



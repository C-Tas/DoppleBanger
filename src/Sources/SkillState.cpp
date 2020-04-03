#include "SkillState.h"
#include "Button.h"
#include "Texture.h"
#include "GameManager.h"
#include "InventoryState.h"

void SkillState::initSkillState() {
	////QUITA EL COMENTARIO PARA DEBUGUEAR | LAS SKILLS SE DESBLOQUEAN EN 33,66 Y 100 PUNTOS EN LA RAMA
	//GameManager::instance()->setPrecisionPoints(65);
	//GameManager::instance()->setMeleePoints(32);
	//GameManager::instance()->setGhostPoints(99);

	#ifdef _DEBUG	//PARA DEBUG
	cout << "SKILLTATE" << endl;
	cout << "TIENES " << GameManager::instance()->getAchievementPoints() << " PUNTOS" << endl;
	cout << "PRECISION " << (int)GameManager::instance()->getPresicionPoints() << " PUNTOS" << endl;
	cout << "MELEE " << (int)GameManager::instance()->getMeleePoints() << " PUNTOS" << endl;
	cout << "GHOST " << (int)GameManager::instance()->getGhostPoints() << " PUNTOS" << endl;
	#endif

	bg_ = new Draw(app_, app_->getTextureManager()->getTexture(Resources::TextureId::SkillMenu));
	addRenderList(bg_);

	createButtons();
	createTexts();
	createBars();
	createSkillsIcons();
}

void SkillState::update()
{
	updateBars();
	updateSkillsIcons();
	updateTexts();
	GameState::update();
}

void SkillState::createBars() {
	//PrecisionBar
	bars_[0] = new Draw(app_, app_->getTextureManager()->getTexture(Resources::TextureId::GreenBar), { 190, 390, 530, 20 });		
	addRenderList(bars_[0]);

	//MeleeBar
	bars_[1] = new Draw(app_, app_->getTextureManager()->getTexture(Resources::TextureId::YellowBar), { 190, 540, 530, 20 });		
	addRenderList(bars_[1]);

	//GhostBar
	bars_[2] = new Draw(app_, app_->getTextureManager()->getTexture(Resources::TextureId::BlueBar), { 190, 690, 530, 20 });			
	addRenderList(bars_[2]);

	updateBars();

	//Marcos de las barras
	//No me deja usar emptyBars_.size(), por eso est� el 3 a pelo
	for (int i = 0; i < 3; i++) {
		emptyBars_[i] = new Draw(app_, app_->getTextureManager()->getTexture(Resources::TextureId::EmptyBar), { 190, 390 + i * 150, 530, 20 });		// 150 es la distancia entre las barras
		addRenderList(emptyBars_[i]);
	}
}

void SkillState::updateBars() { 
	for (int i = 0; i < 3; i++) {
		SDL_Rect aux = bars_[i]->getDestiny();
		switch (i)
		{
		case 0:	//Barra verde
			aux.w = (530 * (int)GameManager::instance()->getPresicionPoints() / 100);
			break;
		case 1:	//Barra amarilla
			aux.w = (530 * (int)GameManager::instance()->getMeleePoints() / 100);
			break;
		case 2:	//Barra azul
			aux.w = (530 * (int)GameManager::instance()->getGhostPoints() / 100);
			break;
		default:
			break;
		}
		bars_[i]->setDestiny(aux);
	}
}

void SkillState::createSkillsIcons()
{
	//Precision Skills
	skillsIcons_[0][0] = new Draw(app_, app_->getTextureManager()->getTexture(Resources::TextureId::SkillPerforanteBN), { 330, 352, 70, 40 });
	skillsIcons_[0][1] = new Draw(app_, app_->getTextureManager()->getTexture(Resources::TextureId::SkillRaudoBN), { 502, 352, 70, 40 });
	skillsIcons_[0][2] = new Draw(app_, app_->getTextureManager()->getTexture(Resources::TextureId::SkillReboteBN), { 684, 352, 70, 40 });
	//Melee Skills
	skillsIcons_[1][0] = new Draw(app_, app_->getTextureManager()->getTexture(Resources::TextureId::SkillGolpeFuerteBN), { 330, 502, 70, 40 });
	skillsIcons_[1][1] = new Draw(app_, app_->getTextureManager()->getTexture(Resources::TextureId::SkillInvencibleBN), { 502, 502, 70, 40 });
	skillsIcons_[1][2] = new Draw(app_, app_->getTextureManager()->getTexture(Resources::TextureId::SkillTorbellinoBN), { 684, 502, 70, 40 });
	//Ghost Skills
	skillsIcons_[2][0] = new Draw(app_, app_->getTextureManager()->getTexture(Resources::TextureId::SkillLiberationBN), { 330, 652, 70, 40 });
	skillsIcons_[2][1] = new Draw(app_, app_->getTextureManager()->getTexture(Resources::TextureId::SkillExplosionBN), { 502, 652, 70, 40 });
	skillsIcons_[2][2] = new Draw(app_, app_->getTextureManager()->getTexture(Resources::TextureId::SkillLiberationBN), { 684, 652, 70, 40 });

	//Los metemos en la lista de objetos a renderizar y actualizar
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			addRenderList(skillsIcons_[i][j]);
		}
	}

}

void SkillState::updateSkillsIcons()
{
	//Precision Skills
	if ((int)GameManager::instance()->getPresicionPoints() >= 33) {
		skillsIcons_[0][0]->setTexture(app_->getTextureManager()->getTexture(Resources::TextureId::SkillPerforanteC));
		if ((int)GameManager::instance()->getPresicionPoints() >= 66) {
			skillsIcons_[0][1]->setTexture(app_->getTextureManager()->getTexture(Resources::TextureId::SkillRaudoC));
			if ((int)GameManager::instance()->getPresicionPoints() >= 100) {
				skillsIcons_[0][2]->setTexture(app_->getTextureManager()->getTexture(Resources::TextureId::SkillReboteC));
			}
		}
	}

	//Melee Skills
	if ((int)GameManager::instance()->getMeleePoints() >= 33) {
		skillsIcons_[1][0]->setTexture(app_->getTextureManager()->getTexture(Resources::TextureId::SkillGolpeFuerteC));
		if ((int)GameManager::instance()->getMeleePoints() >= 66) {
			skillsIcons_[1][1]->setTexture(app_->getTextureManager()->getTexture(Resources::TextureId::SkillInvencibleC));
			if ((int)GameManager::instance()->getMeleePoints() >= 100) {
				skillsIcons_[1][2]->setTexture(app_->getTextureManager()->getTexture(Resources::TextureId::SkillTorbellinoC));
			}
		}
	}

	//Ghost Skills
	if ((int)GameManager::instance()->getGhostPoints() >= 33) {
		skillsIcons_[2][0]->setTexture(app_->getTextureManager()->getTexture(Resources::TextureId::SkillLiberationC));
		if ((int)GameManager::instance()->getGhostPoints() >= 66) {
			skillsIcons_[2][1]->setTexture(app_->getTextureManager()->getTexture(Resources::TextureId::SkillExplosionC));
			if ((int)GameManager::instance()->getGhostPoints() >= 100) {
				skillsIcons_[2][2]->setTexture(app_->getTextureManager()->getTexture(Resources::TextureId::SkillLiberationC));
			}
		}
	}
}

void SkillState::createTexts() {
	totalPoints_ = new Draw(app_, app_->getTextureManager()->getTexture(Resources::RedBar), { 1270, 250, 100, 40 });
	addRenderUpdateLists(totalPoints_);
}

void SkillState::updateTexts()
{

}

void SkillState::createButtons() {
	//Precision Button
	Button* precisionButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::ButtonUpgradeGreen), { 770,375 }, { 50,50 }, increasePrecisionBranch);
	addRenderUpdateLists(precisionButton);

	//Melee Button
	Button* meleeButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::ButtonUpgradeYellow), { 770,525 }, { 50,50 }, increaseMeleeBranch);
	addRenderUpdateLists(meleeButton);

	//Ghost Button
	Button* ghostButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::ButtonUpgradeBlue), { 770,675 }, { 50,50 }, increaseGhostBranch);
	addRenderUpdateLists(ghostButton);

	//Back Button
	Button* backButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::ButtonX), { 1439,214 }, { 60,53 }, backToPreviousState);
	addRenderUpdateLists(backButton);

	//Inventary Button
	Button* inventaryButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::ButtonX), { 175,80 }, { 50,50 }, goToInventaryState);
	addRenderUpdateLists(inventaryButton);
}

void SkillState::backToPreviousState(Application* app) {
	app->getStateMachine()->popState();
}

void SkillState::goToInventaryState(Application* app) {
	cout << "Cambia a inventoryState" << endl;
	//app->getStateMachine()->changeState(new InventoryState(app));
}

void SkillState::increasePrecisionBranch(Application* app) {
	if (GameManager::instance()->getAchievementPoints() > 0 && (int)GameManager::instance()->getPresicionPoints() < 100) {	//Comprueba que tenga puntos de haza�a que invertir y que la rama no tenga ya 100 puntos (m�ximo)
		GameManager::instance()->setPrecisionPoints((int)GameManager::instance()->getPresicionPoints() + 1);				//Aumenta en uno los puntos de esta rama
		GameManager::instance()->setArchievementPoints(GameManager::instance()->getAchievementPoints() - 1);				//Reduce en uno los puntos de haza�a
		cout << "PRECISION " << (int)GameManager::instance()->getPresicionPoints() << " PUNTOS" << endl; //PARA DEBUG
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



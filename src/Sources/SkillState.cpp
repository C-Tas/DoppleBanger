#include "SkillState.h"
#include "Button.h"
#include "Texture.h"
#include "GameManager.h"
#include "InventoryState.h"
#include "Player.h"

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
	//updateSkillsIcons();
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
	//No me deja usar emptyBars_.size(), por eso está el 3 a pelo
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
	auto it1 = skillsIcons_.insert(skillsIcons_.end(),new SkillButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::SkillPerforanteBN), { 330, 352},{ 70, 40 }, selectSkill, SkillNames::DisparoPerforante));
	skillsIcons_.insert(skillsIcons_.end(),new SkillButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::SkillRaudoBN), { 502, 352 }, { 70, 40 }, selectSkill, SkillNames::Pasiva));
	skillsIcons_.insert(skillsIcons_.end(),new SkillButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::SkillReboteBN), { 684, 352 }, { 70, 40 }, selectSkill, SkillNames::Rebote));
	//Melee Skills
	auto it2 = skillsIcons_.insert(skillsIcons_.end(), new SkillButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::SkillGolpeFuerteBN), { 330, 502 }, { 70, 40 }, selectSkill, SkillNames::GolpeFuerte));
	skillsIcons_.insert(skillsIcons_.end(),new SkillButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::SkillInvencibleBN), { 502, 502 }, { 70, 40 }, selectSkill, SkillNames::Pasiva));
	skillsIcons_.insert(skillsIcons_.end(),new SkillButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::SkillTorbellinoBN), { 684, 502 }, { 70, 40 }, selectSkill, SkillNames::Torbellino));
	//Ghost Skills
	auto it3 = skillsIcons_.insert(skillsIcons_.end(),new SkillButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::SkillLiberationBN), { 330, 652 }, { 70, 40 }, selectSkill, SkillNames::Pasiva));
	skillsIcons_.insert(skillsIcons_.end(),new SkillButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::SkillExplosionBN), { 502, 652 }, { 70, 40 }, selectSkill, SkillNames::Explosion));
	skillsIcons_.insert(skillsIcons_.end(),new SkillButton(app_, app_->getTextureManager()->getTexture(Resources::TextureId::SkillLiberationBN), { 684, 652 }, { 70, 40 }, selectSkill, SkillNames::Pasiva));

	skillsTypeIterator[0] = it1;
	skillsTypeIterator[1] = it2;
	skillsTypeIterator[2] = it3;


	//Los metemos en la lista de objetos a renderizar y actualizar
	for(SkillButton * ob : skillsIcons_) {
		addRenderUpdateLists(ob);
	}

}

void SkillState::updateSkillsIcons()const
{
	vector<SkillNames> aux = GameManager::instance()->getAllSkillsEquipped();
	int i = 0;
	for (SkillNames name : aux) {
		Texture* auxTex = getTextureFromSkill(name);
		if (auxTex != nullptr){
			auxTex->render(assignButtons[i]);//Provisional
		}
		i++;
	}

}

void SkillState::createTexts() {
	totalPoints_ = new Draw(app_, app_->getTextureManager()->getTexture(Resources::RedBar), { 1270, 250, 100, 40 });
	addRenderUpdateLists(totalPoints_);
}

void SkillState::updateTexts()
{

}

void SkillState::setSelectedSkillButton(SkillButton* button)
{
	selected_ = button;
#ifdef _DEBUG
	cout << "Cambio de seleccion en el skill state" << endl;
#endif // _DEBUG
}

void SkillState::equipSelectedSkill(SkillEquiped key)
{
	GameManager* gm = GameManager::instance();
	//Si no está asignada, no hay ninguna en esa tecla y no es una pasiva
	if (!selected_->isAsigned()&& gm->getSkillEquiped(key) == SkillNames::Unequipped && selected_->getSkillId() != SkillNames::Pasiva) {
		selected_->setAsigned(true);
		gm->setSkillEquiped(selected_->getSkillId(), key);
	}
	//Si está equipada pero la tecla en la que queremos equipar está libre
	else if (selected_->isAsigned() && selected_->getSkillId() != SkillNames::Pasiva && gm->getSkillEquiped(key) == SkillNames::Unequipped) {

		SkillEquiped aux = gm->getEquippedSkillKey(selected_->getSkillId());
		gm->setSkillEquiped(SkillNames::Unequipped, aux);
		gm->setSkillEquiped(selected_->getSkillId(), key);
	}
	//La tecla en la que queremos asignar no está libre
	else if (selected_->getSkillId() != SkillNames::Pasiva && gm->getSkillEquiped(key) != SkillNames::Unequipped){
		SkillNames aux = gm->getSkillEquiped(key);
		//Buscamos el botón que asigna dicha skill
		auto it = skillsIcons_.begin();
		while (it != skillsIcons_.end() && aux != (*it)->getSkillId())++it;

		///Si la skill que queremos introducir está ya asignada a una tecla
		if (selected_->isAsigned()) {
			//Buscamos en cual estaba asignada
			SkillEquiped changingKey = gm->getEquippedSkillKey((selected_)->getSkillId());
			//Equipamos la skill seleccionada en la tecla correspondiente
			gm->setSkillEquiped(selected_->getSkillId(), key);
			//Reasignamos la skill que estaba en la tecla q a la tecla en la que se encontraba 
			gm->setSkillEquiped((*it)->getSkillId(), changingKey);

		}
		///Si la skill que queremos introducir no está asignada
		else {
			//Cuando lo encontramos, marcamos esa skill como no equipada
			(*it)->setAsigned(false);
			//Actualizamos vector de skills equipadas
			gm->setSkillEquiped(selected_->getSkillId(), key);
		}
		
	}
}

void SkillState::meelePointsActualized()
{
	GameManager* gm = GameManager::instance();
	auxPointsActualized(skillsTypeIterator[1], app_->getTextureManager()->getTexture(Resources::TextureId::SkillGolpeFuerteC),
		app_->getTextureManager()->getTexture(Resources::TextureId::SkillInvencibleC), app_->getTextureManager()->getTexture(Resources::TextureId::SkillTorbellinoC),(int)gm->getMeleePoints());

}

void SkillState::distancePointsActualized()
{
	GameManager* gm = GameManager::instance();
	auxPointsActualized(skillsTypeIterator[0], app_->getTextureManager()->getTexture(Resources::TextureId::SkillPerforanteC),
		app_->getTextureManager()->getTexture(Resources::TextureId::SkillRaudoC), app_->getTextureManager()->getTexture(Resources::TextureId::SkillReboteC), (int)gm->getPresicionPoints());
}

void SkillState::ghostPointsActualized()
{
	GameManager* gm = GameManager::instance();
	auxPointsActualized(skillsTypeIterator[2], app_->getTextureManager()->getTexture(Resources::TextureId::SkillLiberationC),
		app_->getTextureManager()->getTexture(Resources::TextureId::SkillExplosionC), app_->getTextureManager()->getTexture(Resources::TextureId::SkillLiberationC), (int)gm->getGhostPoints());
}

void SkillState::auxPointsActualized(list<SkillButton*>::iterator aux, Texture* t1, Texture* t2, Texture* t3, int points)
{
	GameManager* gm = GameManager::instance();

	if (points >= 33 && !(*aux)->isUnlocked()) {
		(*aux)->setTexture(t1);
		(*aux)->setUnlocked(true);
	}
	++aux;
	if (points >= 66 && !(*aux)->isUnlocked()) {
		(*aux)->setTexture(t2);
		(*aux)->setUnlocked(true);
	}
	++aux;
	if (points >= 100 && !(*aux)->isUnlocked()) {
		(*aux)->setTexture(t3);
		(*aux)->setUnlocked(true);
	}
}

Texture* SkillState::getTextureFromSkill(SkillNames name)const
{
	Texture* tex;
	switch (name)
	{
	case SkillNames::Unequipped:
		tex = nullptr;
		break;
	case SkillNames::Pasiva:
		tex = nullptr;
		break;
	case SkillNames::GolpeFuerte:
		tex = app_->getTextureManager()->getTexture(Resources::TextureId::SkillGolpeFuerteC);
		break;
	case SkillNames::Torbellino:
		tex = app_->getTextureManager()->getTexture(Resources::TextureId::SkillTorbellinoC);
		break;
	case SkillNames::DisparoPerforante:
		tex = app_->getTextureManager()->getTexture(Resources::TextureId::SkillPerforanteC);
		break;
	case SkillNames::Rebote:
		tex = app_->getTextureManager()->getTexture(Resources::TextureId::SkillReboteC);
		break;
	case SkillNames::Clon:
		tex = app_->getTextureManager()->getTexture(Resources::TextureId::SkillLiberationC);
		break;
	case SkillNames::Explosion:
		tex = app_->getTextureManager()->getTexture(Resources::TextureId::SkillExplosionC);
		break;
	default:
		tex = nullptr;
		break;
	}

	return tex;
}

void SkillState::draw() const
{
	GameState::draw();
	updateSkillsIcons();
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

	///Botones en los que aparecerá la skillEquipada
	addRenderUpdateLists(new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::EquippedSkill), { 940,690 }, { 113,113 }, assingToQKey));
	addRenderUpdateLists(new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::EquippedSkill), { 1067,690 }, { 113,113 }, assingToWKey));
	addRenderUpdateLists(new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::EquippedSkill), { 1194,690 }, { 113,113 }, assingToEKey));

}

SkillState::~SkillState()
{
	for (int i = 0; i < 3; i++)delete emptyBars_[i];
	for (int i = 0; i < 3; i++)delete bars_[i];
	delete bg_;
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
		dynamic_cast<SkillState*>(app->getCurrState())->distancePointsActualized();
		cout << "PRECISION " << (int)GameManager::instance()->getPresicionPoints() << " PUNTOS" << endl; //PARA DEBUG
	}
	cout << "TE QUEDAN " << (int)GameManager::instance()->getAchievementPoints() << " PUNTOS" << endl;
};

void SkillState::increaseMeleeBranch(Application* app) {
	if (GameManager::instance()->getAchievementPoints() > 0 && (int)GameManager::instance()->getMeleePoints() < 100) {
		GameManager::instance()->setMeleePoints((int)GameManager::instance()->getMeleePoints() + 1);
		GameManager::instance()->setArchievementPoints(GameManager::instance()->getAchievementPoints() - 1);
		dynamic_cast<SkillState*>(app->getCurrState())->meelePointsActualized();
		cout << "MELEE " << (int)GameManager::instance()->getMeleePoints() << " PUNTOS" << endl;
	}
	cout << "TE QUEDAN " << (int)GameManager::instance()->getAchievementPoints() << " PUNTOS" << endl;
};

void SkillState::increaseGhostBranch(Application* app) {
	if (GameManager::instance()->getAchievementPoints() > 0 && (int)GameManager::instance()->getGhostPoints() < 100) {
		GameManager::instance()->setGhostPoints((int)GameManager::instance()->getGhostPoints() + 1);
		GameManager::instance()->setArchievementPoints(GameManager::instance()->getAchievementPoints() - 1);
		dynamic_cast<SkillState*>(app->getCurrState())->ghostPointsActualized();
		cout << "GHOST " << (int)GameManager::instance()->getGhostPoints() << " PUNTOS" << endl;
	}
	cout << "TE QUEDAN " << (int)GameManager::instance()->getAchievementPoints() << " PUNTOS" << endl;
}

void SkillState::selectSkill(Application* app, SkillButton* button)
{
	dynamic_cast<SkillState*>(app->getCurrState())->setSelectedSkillButton(button);
}

void SkillState::assingToQKey(Application* app)
{
#ifdef _DEBUG
	cout << "Asignado a la tecla Q" << endl;
#endif // _DEBUG
	dynamic_cast<SkillState*>(app->getCurrState())->equipSelectedSkill(SkillEquiped::Q);
}

void SkillState::assingToWKey(Application* app)
{
#ifdef _DEBUG
	cout << "Asignado a la tecla W" << endl;
#endif // _DEBUG
	dynamic_cast<SkillState*>(app->getCurrState())->equipSelectedSkill(SkillEquiped::W);
}

void SkillState::assingToEKey(Application* app)
{
#ifdef _DEBUG
	cout << "Asignado a la tecla E" << endl;
#endif // _DEBUG

	dynamic_cast<SkillState*>(app->getCurrState())->equipSelectedSkill(SkillEquiped::E);
}



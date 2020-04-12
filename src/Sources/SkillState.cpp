#include "SkillState.h"
#include "Button.h"
#include "Texture.h"
#include "GameManager.h"
#include "Inventory.h"
#include "Player.h"
#include "TextBox.h"
#include "Skill.h"
#include "VisualElement.h"

void SkillState::initState() {
	////QUITA EL COMENTARIO PARA DEBUGUEAR | LAS SKILLS SE DESBLOQUEAN EN 33,66 Y 100 PUNTOS EN LA RAMA
	//GameManager::instance()->setPrecisionPoints(65);
	//GameManager::instance()->setMeleePoints(32);
	//GameManager::instance()->setGhostPoints(99);

	#ifdef _DEBUG	//PARA DEBUG
	cout << "SKILLTATE" << endl;
	cout << "TIENES " << gm_->getAchievementPoints() << " PUNTOS" << endl;
	cout << "PRECISION " << (int)gm_->getPresicionPoints() << " PUNTOS" << endl;
	cout << "MELEE " << (int)gm_->getMeleePoints() << " PUNTOS" << endl;
	cout << "GHOST " << (int)gm_->getGhostPoints() << " PUNTOS" << endl;
	#endif

	bg_ = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::TextureId::SkillMenu));
	createButtons();
	createTexts();
	createBars();
	createSkillsIcons();
}

void SkillState::update()
{	
	//Comprobamos si el rat�n est� sobre alguna de las skills equipadas
	int i = 0;
	SDL_Point point;
	point.x = eventHandler_->getRealMousePos().getX();
	point.y = eventHandler_->getRealMousePos().getY();
	while (i < assignButtons.size() && !SDL_PointInRect(&point, &assignButtons[i]))i++;
	//Si lo est�, actualizamos cual descripcion debe mostrarse
	if (i < assignButtons.size()) lastPointed = gm_->getSkillEquiped((SkillEquiped)i);
	
	if (SDL_PointInRect(&point, &goToInventary_->getDestiny())) {
		goToInventary_->setTexture(app_->getTextureManager()->getTexture(Resources::TextureId::GoToInventoryBButton));
	}
	else {
		goToInventary_->setTexture(app_->getTextureManager()->getTexture(Resources::TextureId::GoToInventoryAButton));
	}

	//update de las barras
	updateBars();
	//update de todos los objetos
	GameState::update();
}

void SkillState::createBars() {
	//PrecisionBar
	bars_[0] = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::TextureId::GreenBar), { 190, 390, 530, 20 });
	addRenderList(bars_[0]);

	//MeleeBar
	bars_[1] = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::TextureId::YellowBar), { 190, 540, 530, 20 });
	addRenderList(bars_[1]);

	//GhostBar
	bars_[2] = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::TextureId::BlueBar), { 190, 690, 530, 20 });
	addRenderList(bars_[2]);

	updateBars();

	//Marcos de las barras
	//No me deja usar emptyBars_.size(), por eso est� el 3 a pelo
	for (int i = 0; i < 3; i++) {
		emptyBars_[i] = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::TextureId::EmptyBar), { 190, 390 + i * 150, 530, 20 });		// 150 es la distancia entre las barras
		addRenderList(emptyBars_[i]);
	}
}

void SkillState::updateBars() { 
	for (int i = 0; i < 3; i++) {
		SDL_Rect aux = bars_[i]->getDestiny();
		switch (i)
		{
		case 0:	//Barra verde
			aux.w = (530 * (int)gm_->getPresicionPoints() / 100);
			break;
		case 1:	//Barra amarilla
			aux.w = (530 * (int)gm_->getMeleePoints() / 100);
			break;
		case 2:	//Barra azul
			aux.w = (530 * (int)gm_->getGhostPoints() / 100);
			break;
		default:
			break;
		}
		bars_[i]->setDestiny(aux);
	}
}

void SkillState::createSkillsIcons()
{	
	Texture* auxTexture;

	//Precision Skills
	///Comprobamos si la habilidad esta desbloqueda, seg�n si est� o no, usamos una textura u otra
	auxTexture = (!gm_->isSkillUnlocked(SkillNames::DisparoPerforante)) ? app_->getTextureManager()->getTexture(Resources::TextureId::SkillPerforanteBN) : app_->getTextureManager()->getTexture(Resources::TextureId::SkillPerforanteC);
	auto it1 = skillsIcons_.insert(skillsIcons_.end(),new SkillButton(app_, auxTexture, { 330, 352},{ 70, 40 }, selectSkill, SkillNames::DisparoPerforante, SkillType::Active, changeDescription));

	auxTexture = (!gm_->isSkillUnlocked(SkillNames::Raudo)) ? app_->getTextureManager()->getTexture(Resources::TextureId::SkillRaudoBN) : app_->getTextureManager()->getTexture(Resources::TextureId::SkillRaudoC);
	skillsIcons_.insert(skillsIcons_.end(),new SkillButton(app_, auxTexture, { 502, 352 }, { 70, 40 }, selectSkill, SkillNames::Raudo, SkillType::Pasive, changeDescription));
	
	auxTexture = (!gm_->isSkillUnlocked(SkillNames::Rebote)) ? app_->getTextureManager()->getTexture(Resources::TextureId::SkillReboteBN) : app_->getTextureManager()->getTexture(Resources::TextureId::SkillReboteC);
	skillsIcons_.insert(skillsIcons_.end(),new SkillButton(app_, auxTexture, { 684, 352 }, { 70, 40 }, selectSkill, SkillNames::Rebote, SkillType::Active, changeDescription));
	
	//Melee Skills
	auxTexture = (!gm_->isSkillUnlocked(SkillNames::GolpeFuerte)) ? app_->getTextureManager()->getTexture(Resources::TextureId::SkillGolpeFuerteBN) : app_->getTextureManager()->getTexture(Resources::TextureId::SkillGolpeFuerteC);
	auto it2 = skillsIcons_.insert(skillsIcons_.end(), new SkillButton(app_, auxTexture, { 330, 502 }, { 70, 40 }, selectSkill, SkillNames::GolpeFuerte, SkillType::Active, changeDescription));
	
	auxTexture = (!gm_->isSkillUnlocked(SkillNames::Invencible)) ? app_->getTextureManager()->getTexture(Resources::TextureId::SkillInvencibleBN) : app_->getTextureManager()->getTexture(Resources::TextureId::SkillInvencibleC);
	skillsIcons_.insert(skillsIcons_.end(),new SkillButton(app_, auxTexture, { 502, 502 }, { 70, 40 }, selectSkill, SkillNames::Invencible, SkillType::Pasive, changeDescription));
	
	auxTexture = (!gm_->isSkillUnlocked(SkillNames::Torbellino)) ? app_->getTextureManager()->getTexture(Resources::TextureId::SkillTorbellinoBN) : app_->getTextureManager()->getTexture(Resources::TextureId::SkillTorbellinoC);
	skillsIcons_.insert(skillsIcons_.end(),new SkillButton(app_, auxTexture, { 684, 502 }, { 70, 40 }, selectSkill, SkillNames::Torbellino, SkillType::Active, changeDescription));
	
	//Ghost Skills
	auxTexture = (!gm_->isSkillUnlocked(SkillNames::LiberacionI)) ? app_->getTextureManager()->getTexture(Resources::TextureId::SkillLiberationBN) : app_->getTextureManager()->getTexture(Resources::TextureId::SkillLiberationC);
	auto it3 = skillsIcons_.insert(skillsIcons_.end(),new SkillButton(app_, auxTexture, { 330, 652 }, { 70, 40 }, selectSkill, SkillNames::LiberacionI, SkillType::Pasive, changeDescription));

	auxTexture = (!gm_->isSkillUnlocked(SkillNames::Explosion)) ? app_->getTextureManager()->getTexture(Resources::TextureId::SkillExplosionBN) : app_->getTextureManager()->getTexture(Resources::TextureId::SkillExplosionC);
	skillsIcons_.insert(skillsIcons_.end(),new SkillButton(app_, auxTexture, { 502, 652 }, { 70, 40 }, selectSkill, SkillNames::Explosion, SkillType::Active, changeDescription));
	
	auxTexture = (!gm_->isSkillUnlocked(SkillNames::LiberacionII)) ? app_->getTextureManager()->getTexture(Resources::TextureId::SkillLiberationBN) : app_->getTextureManager()->getTexture(Resources::TextureId::SkillLiberationC);
	skillsIcons_.insert(skillsIcons_.end(),new SkillButton(app_, auxTexture, { 684, 652 }, { 70, 40 }, selectSkill, SkillNames::LiberacionII, SkillType::Pasive, changeDescription));

	skillsTypeIterator[0] = it1;
	skillsTypeIterator[1] = it2;
	skillsTypeIterator[2] = it3;


	//Los metemos en la lista de objetos a renderizar y actualizar
	for(SkillButton * ob : skillsIcons_) {
		addRenderUpdateLists(ob);
	}

}

void SkillState::renderSkillsEquipped()const
{
	vector<SkillNames> aux = GameManager::instance()->getAllSkillsEquipped();
	int i = 0;
	for (SkillNames name : aux) {
		Texture* auxTex = getTextureFromSkill(name);
		if (auxTex != nullptr){
			auxTex->render(assignButtons[i]);
		}
		i++;
	}

}

void SkillState::createTexts() {
	totalPoints_ = new Texture(app_->getRenderer(), to_string(gm_->getAchievementPoints()),
		app_->getFontManager()->getFont(Resources::RETRO), SDL_Color{ (0,0,0,1) });
}


void SkillState::setSelectedSkillButton(SkillButton* button)
{
	selected_ = button;
	if (selectedRectangle == nullptr)selectedRectangle = new Draw(app_, app_->getTextureManager()->getTexture(Resources::RedBar), SDL_Rect{ (int)button->getPosX() - 10, (int)button->getPosY() - 10, (int)button->getScaleX() + 20, (int)button->getScaleY() + 10 });
	else {
		selectedRectangle->setPos(Vector2D(button->getPosX() - 10, button->getPosY() - 10));
	}
#ifdef _DEBUG
	cout << "Cambio de seleccion en el skill state" << endl;
#endif // _DEBUG
}

void SkillState::equipSelectedSkill(SkillEquiped key)
{
	if (selected_ != nullptr && selected_->isUnlocked()) {
		//Si no est� asignada, no hay ninguna en esa tecla y no es una pasiva
		if (!selected_->isAsigned() && gm_->getSkillEquiped(key) == SkillNames::Unequipped && selected_->getSkillType() != SkillType::Pasive) {
			selected_->setAsigned(true);
			gm_->setSkillEquiped(selected_->getSkillId(), key);
		}
		//Si est� equipada pero la tecla en la que queremos equipar est� libre
		else if (selected_->isAsigned() && selected_->getSkillType() != SkillType::Pasive && gm_->getSkillEquiped(key) == SkillNames::Unequipped) {

			SkillEquiped aux = gm_->getEquippedSkillKey(selected_->getSkillId());
			gm_->setSkillEquiped(SkillNames::Unequipped, aux);
			gm_->setSkillEquiped(selected_->getSkillId(), key);
		}
		//La tecla en la que queremos asignar no est� libre
		else if (selected_->getSkillType() != SkillType::Pasive && gm_->getSkillEquiped(key) != SkillNames::Unequipped) {
			SkillNames aux = gm_->getSkillEquiped(key);
			//Buscamos el bot�n que asigna dicha skill
			auto it = skillsIcons_.begin();
			while (it != skillsIcons_.end() && aux != (*it)->getSkillId())++it;

			///Si la skill que queremos introducir est� ya asignada a una tecla
			if (selected_->isAsigned()) {
				//Buscamos en cual estaba asignada
				SkillEquiped changingKey = gm_->getEquippedSkillKey((selected_)->getSkillId());
				//Equipamos la skill seleccionada en la tecla correspondiente
				gm_->setSkillEquiped(selected_->getSkillId(), key);
				//Reasignamos la skill que estaba en la tecla q a la tecla en la que se encontraba 
				gm_->setSkillEquiped((*it)->getSkillId(), changingKey);

			}
			///Si la skill que queremos introducir no est� asignada
			else {
				//Cuando lo encontramos, marcamos esa skill como no equipada
				(*it)->setAsigned(false);
				//Actualizamos vector de skills equipadas
				gm_->setSkillEquiped(selected_->getSkillId(), key);
				selected_->setAsigned(true);
			}

		}
	}
}

void SkillState::meleePointsActualized()
{
	auxPointsActualized(skillsTypeIterator[1], app_->getTextureManager()->getTexture(Resources::TextureId::SkillGolpeFuerteC),
		app_->getTextureManager()->getTexture(Resources::TextureId::SkillInvencibleC), app_->getTextureManager()->getTexture(Resources::TextureId::SkillTorbellinoC),(int)gm_->getMeleePoints());

}

void SkillState::distancePointsActualized()
{
	int points = (int)gm_->getPresicionPoints();
	auto aux = skillsTypeIterator[0];
	delete totalPoints_;
	createTexts();
	if (points >= 33 && !(*aux)->isUnlocked()) {
		(*aux)->setTexture(app_->getTextureManager()->getTexture(Resources::TextureId::SkillPerforanteC));
		(*aux)->setUnlocked(true);
		gm_->setSkillUnlocked((*aux)->getSkillId());
	}
	++aux;
	if (points >= 66 && !(*aux)->isUnlocked()) {
		(*aux)->setTexture(app_->getTextureManager()->getTexture(Resources::TextureId::SkillRaudoC));
		(*aux)->setUnlocked(true);
		gm_->setSkillUnlocked((*aux)->getSkillId());
		player_->activateSwiftGunslinger();
	}
	++aux;
	if (points >= 100 && !(*aux)->isUnlocked()) {
		(*aux)->setTexture(app_->getTextureManager()->getTexture(Resources::TextureId::SkillReboteC));
		(*aux)->setUnlocked(true);
		gm_->setSkillUnlocked((*aux)->getSkillId());
	}
}

void SkillState::ghostPointsActualized()
{
	auxPointsActualized(skillsTypeIterator[2], app_->getTextureManager()->getTexture(Resources::TextureId::SkillLiberationC),
		app_->getTextureManager()->getTexture(Resources::TextureId::SkillExplosionC), app_->getTextureManager()->getTexture(Resources::TextureId::SkillLiberationC), (int)gm_->getGhostPoints());
}

void SkillState::auxPointsActualized(list<SkillButton*>::iterator aux, Texture* t1, Texture* t2, Texture* t3, int points)
{
	delete totalPoints_;
	createTexts();
	if (points >= 33 && !(*aux)->isUnlocked()) {
		(*aux)->setTexture(t1);
		(*aux)->setUnlocked(true);
		gm_->setSkillUnlocked((*aux)->getSkillId());
	}
	++aux;
	if (points >= 66 && !(*aux)->isUnlocked()) {
		(*aux)->setTexture(t2);
		(*aux)->setUnlocked(true);
		gm_->setSkillUnlocked((*aux)->getSkillId());
	}
	++aux;
	if (points >= 100 && !(*aux)->isUnlocked()) {
		(*aux)->setTexture(t3);
		(*aux)->setUnlocked(true);
		gm_->setSkillUnlocked((*aux)->getSkillId());
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
	case SkillNames::Invencible:
		tex = app_->getTextureManager()->getTexture(Resources::TextureId::SkillInvencibleC);
		break;
	case SkillNames::Raudo:
		tex = app_->getTextureManager()->getTexture(Resources::TextureId::SkillRaudoC);
		break;
	case SkillNames::LiberacionI:
		tex = app_->getTextureManager()->getTexture(Resources::TextureId::SkillLiberationC);
		break;
	case SkillNames::LiberacionII:
		tex = app_->getTextureManager()->getTexture(Resources::TextureId::SkillLiberationC);
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
	//Estos dos objetos van fuera porque quiero que siempre se pinten los primeros
	bg_->draw();
	if (selectedRectangle != nullptr) selectedRectangle->draw();

	changeDescriptionTexture(lastPointed);
	totalPoints_->render({ 1270, 250, 100, 40 });
	GameState::draw();
	renderSkillsEquipped();
}

void SkillState::changeDescriptionTexture(SkillNames name)const
{

	TextBox descriptionBox(app_, Point2D(descriptionRect.x, descriptionRect.y));
	switch (name)
	{
	case SkillNames::Unequipped:
		break;
	case SkillNames::GolpeFuerte:
		descriptionBox.GolpeFuerte();
		break;
	case SkillNames::Invencible:
		descriptionBox.Invencible();
		break;
	case SkillNames::Torbellino:
		descriptionBox.Torbellino();
		break;
	case SkillNames::DisparoPerforante:
		descriptionBox.Perforador();
		break;
	case SkillNames::Raudo:
		descriptionBox.Raudo();
		break;
	case SkillNames::Rebote:
		descriptionBox.Rebote();
		break;
	case SkillNames::Clon:
		descriptionBox.Clon();
		break;
	case SkillNames::LiberacionI:
		descriptionBox.LiberationI();
		break;
	case SkillNames::Explosion:
		descriptionBox.Explosion();
		break;
	case SkillNames::LiberacionII:
		descriptionBox.LiberationII();
		break;
	default:
		break;
	}
}

void SkillState::changeDescription(SkillNames name)
{
	lastPointed = name;
}

void SkillState::setPlayerSkills()
{
	if (player_ != nullptr) {
		for (int i = 0; i < gm_->getAllSkillsEquipped().size() - 1; i++) {//-i pq la del clon siempre est� equipada por defecto
			player_->setSkillAt(i, createSkill(gm_->getSkillEquiped((SkillEquiped)i)));
		}
	}
}

Skill* SkillState::createSkill(SkillNames name)
{
	Skill* skill;
	switch (name)
	{
	case SkillNames::Unequipped:
		skill = nullptr;
		break;
	case SkillNames::GolpeFuerte:
		skill = new Skill(player_, SkillType::Active, SkillBranch::Distance);
		break;
	case SkillNames::Invencible:
		skill = new Skill(player_, SkillType::Active, SkillBranch::Distance);
		break;
	case SkillNames::Torbellino:
		skill = new Skill(player_, SkillType::Active, SkillBranch::Distance);
		break;
	case SkillNames::DisparoPerforante:
		skill = new Skill(player_, SkillType::Active, SkillBranch::Distance);
		break;
	case SkillNames::Raudo:
		skill = new Skill(player_, SkillType::Active, SkillBranch::Distance);
		break;
	case SkillNames::Rebote:
		skill = new Skill(player_, SkillType::Active, SkillBranch::Distance);
		break;
	case SkillNames::Clon:
		skill = new Skill(player_, SkillType::Active, SkillBranch::Distance);
		break;
	case SkillNames::LiberacionI:
		skill = new Skill(player_, SkillType::Active, SkillBranch::Distance);
		break;
	case SkillNames::Explosion:
		skill = new Skill(player_, SkillType::Active, SkillBranch::Distance);
		break;
	case SkillNames::LiberacionII:
		skill = new Skill(player_, SkillType::Active, SkillBranch::Distance);
		break;
	default:
		skill = nullptr;
		break;
	}
	return skill;
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
	Button* inventaryButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::GoToInventoryAButton), { 137,22 }, { 560, 121 }, goToInventaryState);
	goToInventary_ = inventaryButton;
	addRenderUpdateLists(inventaryButton);

	///Botones en los que aparecer� la skillEquipada
	addRenderUpdateLists(new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::EquippedSkill), { 940,693 }, { 110,110 }, assingToQKey));
	addRenderUpdateLists(new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::EquippedSkill), { 1067,693 }, { 110,110 }, assingToWKey));
	addRenderUpdateLists(new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::EquippedSkill), { 1194,693 }, { 110,110 }, assingToEKey));

}

SkillState::~SkillState()
{
	for (int i = 0; i < 3; i++)delete emptyBars_[i];
	for (int i = 0; i < 3; i++)delete bars_[i];
	delete bg_; delete selectedRectangle;
	delete totalPoints_;
	//Cuando se borran todos los objetos del estado, asignamos las nuevas skills
	//al player
	setPlayerSkills();
}

void SkillState::backToPreviousState(Application* app) {
	app->getGameStateMachine()->popState();
}

void SkillState::goToInventaryState(Application* app) {
	app->getGameStateMachine()->changeState(new Inventory(app));
}

void SkillState::increasePrecisionBranch(Application* app) {
	if (GameManager::instance()->getAchievementPoints() > 0 && (int)GameManager::instance()->getPresicionPoints() < 100) {	//Comprueba que tenga puntos de haza�a que invertir y que la rama no tenga ya 100 puntos (m�ximo)
		GameManager::instance()->setPrecisionPoints((int)GameManager::instance()->getPresicionPoints() + 1);				//Aumenta en uno los puntos de esta rama
		GameManager::instance()->setArchievementPoints(GameManager::instance()->getAchievementPoints() - 1);				//Reduce en uno los puntos de haza�a
		dynamic_cast<SkillState*>(app->getCurrState())->distancePointsActualized();
		cout << "PRECISION " << (int)GameManager::instance()->getPresicionPoints() << " PUNTOS" << endl; //PARA DEBUG
	}
	cout << "TE QUEDAN " << (int)GameManager::instance()->getAchievementPoints() << " PUNTOS" << endl;
};

void SkillState::increaseMeleeBranch(Application* app) {
	if (GameManager::instance()->getAchievementPoints() > 0 && (int)GameManager::instance()->getMeleePoints() < 100) {
		GameManager::instance()->setMeleePoints((int)GameManager::instance()->getMeleePoints() + 1);
		GameManager::instance()->setArchievementPoints(GameManager::instance()->getAchievementPoints() - 1);
		dynamic_cast<SkillState*>(app->getCurrState())->meleePointsActualized();
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

void SkillState::changeDescription(Application* app, SkillNames name)
{
	dynamic_cast<SkillState*>(app->getCurrState())->changeDescription(name);
}



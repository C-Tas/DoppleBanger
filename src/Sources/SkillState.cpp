#include "SkillState.h"
#include "GameManager.h"
#include "Inventory.h"
#include "Player.h"
#include "TextBox.h"
#include "SkillButton.h"
#include "Skill.h"
#include "VisualElement.h"
#include "RicochetSkill.h"
#include "WhirlwindSkill.h"
#include "PerforateSkill.h"
#include "EmpoweredSkill.h"
#include "ClonSelfDestructSkill.h"
#include "ClonSkill.h"


void SkillState::initState() {
	SDL_ShowCursor(SDL_ENABLE);
	player_ = gm_->getPlayer();

	//Se cambia la canción
	app_->resetSoundsChannels();
	app_->getAudioManager()->pauseChannel(Resources::MainMusicChannel);
	app_->getAudioManager()->playChannel(Resources::SkillState, -1, Resources::InventoryMusicChannel);

	bg_ = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::TextureId::SkillMenu));
	createButtons();
	createTexts();
	createBars();
	createSkillsIcons();
	//USABILIDAD
	int timest = std::chrono::duration_cast<std::chrono::seconds>(
		std::chrono::system_clock::now().time_since_epoch()).count();
	openSkills = (OpenSkills*)Tracker::CreateNewEvent(timest, "hola", "20012", (int)EventInfo::EventType::OpenSkills);
	pointsInOpen= GameManager::instance()->getAchievementPoints();
	//
}

void SkillState::update()
{	
	//Comprobamos si el rat�n est� sobre alguna de las skills equipadas
	int i = 0;
	SDL_Point point;
	point.x = (int)round(eventHandler_->getRealMousePos().getX());
	point.y = (int)round(eventHandler_->getRealMousePos().getY());
	while (i < assignButtons.size() && !SDL_PointInRect(&point, &assignButtons[i]))i++;
	//Si lo est�, actualizamos cual descripcion debe mostrarse
	if (i < assignButtons.size()) lastPointed = gm_->getEquippedSkill((Key)i);
	
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
	bars_[0] = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::TextureId::GreenBar), { (int)(0.1188 * app_->getWindowWidth()), (int)(0.4333 * app_->getWindowHeight()), (int)(0.3313 * app_->getWindowWidth()), (int)(0.0222 * app_->getWindowHeight()) });// , { 190, 390, 530, 20 });
	addRenderList(bars_[0]);

	//MeleeBar
	bars_[1] = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::TextureId::YellowBar), { (int)(0.1188 * app_->getWindowWidth()), (int)(0.6 * app_->getWindowHeight()), (int)(0.3313 * app_->getWindowWidth()), (int)(0.0222 * app_->getWindowHeight()) });//{ 190, 540, 530, 20 });
	addRenderList(bars_[1]);

	//GhostBar
	bars_[2] = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::TextureId::BlueBar), { (int)(0.1188 * app_->getWindowWidth()), (int)(0.7667 * app_->getWindowHeight()), (int)(0.3313 * app_->getWindowWidth()), (int)(0.0222 * app_->getWindowHeight()) });//{ 190, 690, 530, 20 });
	addRenderList(bars_[2]);

	updateBars();

	//Marcos de las barras
	//No me deja usar emptyBars_.size(), por eso est� el 3 a pelo
	for (int i = 0; i < 3; i++) {
		emptyBars_[i] = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::TextureId::EmptyBar), { (int)(0.1188 * app_->getWindowWidth()), (int)(0.4333 * app_->getWindowHeight()) + i * (int)(0.1667 * app_->getWindowHeight()), (int)(0.3313 * app_->getWindowWidth()), (int)(0.0222 * app_->getWindowHeight()) });// { 190, 390 + i * 150, 530, 20 });		// 150 es la distancia entre las barras
		addRenderList(emptyBars_[i]);
	}
}

void SkillState::updateBars() { 
	for (int i = 0; i < 3; i++) {
		SDL_Rect aux = bars_[i]->getDestiny();
		switch (i)
		{
		case 0:	//Barra verde
			aux.w = (int)(0.3313 * app_->getWindowWidth() * gm_->getPresicionPoints() / maxPoints);
			break;
		case 1:	//Barra amarilla
			aux.w = (int)(0.3313 * app_->getWindowWidth() * gm_->getMeleePoints() / maxPoints);
			break;
		case 2:	//Barra azul
			aux.w = (int)(0.3313 * app_->getWindowWidth() * gm_->getGhostPoints() / maxPoints);
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
	auxTexture = (!gm_->isSkillUnlocked(SkillName::DisparoPerforante)) ? app_->getTextureManager()->getTexture(Resources::TextureId::SkillPerforanteBN) : app_->getTextureManager()->getTexture(Resources::TextureId::SkillPerforanteC);
	auto it1 = skillsIcons_.insert(skillsIcons_.end(),new SkillButton(app_, auxTexture, { 0.2063 * app_->getWindowWidth(), 0.3911 * app_->getWindowHeight() }, { 0.0438 * app_->getWindowWidth(), 0.0444 * app_->getWindowHeight() }, selectSkill, SkillName::DisparoPerforante, SkillType::Active, changeDescription));

	auxTexture = (!gm_->isSkillUnlocked(SkillName::Raudo)) ? app_->getTextureManager()->getTexture(Resources::TextureId::SkillRaudoBN) : app_->getTextureManager()->getTexture(Resources::TextureId::SkillRaudoC);
	skillsIcons_.insert(skillsIcons_.end(),new SkillButton(app_, auxTexture, { 0.3138 * app_->getWindowWidth(), 0.3911 * app_->getWindowHeight() }, { 0.0438 * app_->getWindowWidth(), 0.0444 * app_->getWindowHeight() }, selectSkill, SkillName::Raudo, SkillType::Pasive, changeDescription));
	
	auxTexture = (!gm_->isSkillUnlocked(SkillName::Rebote)) ? app_->getTextureManager()->getTexture(Resources::TextureId::SkillReboteBN) : app_->getTextureManager()->getTexture(Resources::TextureId::SkillReboteC);
	skillsIcons_.insert(skillsIcons_.end(),new SkillButton(app_, auxTexture, { 0.4275 * app_->getWindowWidth(), 0.3911 * app_->getWindowHeight() }, { 0.0438 * app_->getWindowWidth(), 0.0444 * app_->getWindowHeight() }, selectSkill, SkillName::Rebote, SkillType::Active, changeDescription));
	
	//Melee Skills
	auxTexture = (!gm_->isSkillUnlocked(SkillName::GolpeFuerte)) ? app_->getTextureManager()->getTexture(Resources::TextureId::SkillGolpeFuerteBN) : app_->getTextureManager()->getTexture(Resources::TextureId::SkillGolpeFuerteC);
	auto it2 = skillsIcons_.insert(skillsIcons_.end(), new SkillButton(app_, auxTexture, { 0.2063 * app_->getWindowWidth(), 0.5578 * app_->getWindowHeight() }, { 0.0438 * app_->getWindowWidth(), 0.0444 * app_->getWindowHeight() }, selectSkill, SkillName::GolpeFuerte, SkillType::Active, changeDescription));
	
	auxTexture = (!gm_->isSkillUnlocked(SkillName::Invencible)) ? app_->getTextureManager()->getTexture(Resources::TextureId::SkillInvencibleBN) : app_->getTextureManager()->getTexture(Resources::TextureId::SkillInvencibleC);
	skillsIcons_.insert(skillsIcons_.end(),new SkillButton(app_, auxTexture, { 0.3138 * app_->getWindowWidth(), 0.5578 * app_->getWindowHeight() }, { 0.0438 * app_->getWindowWidth(), 0.0444 * app_->getWindowHeight() }, selectSkill, SkillName::Invencible, SkillType::Pasive, changeDescription));
	
	auxTexture = (!gm_->isSkillUnlocked(SkillName::Torbellino)) ? app_->getTextureManager()->getTexture(Resources::TextureId::SkillTorbellinoBN) : app_->getTextureManager()->getTexture(Resources::TextureId::SkillTorbellinoC);
	skillsIcons_.insert(skillsIcons_.end(),new SkillButton(app_, auxTexture, { 0.4275 * app_->getWindowWidth(), 0.5578 * app_->getWindowHeight() }, { 0.0438 * app_->getWindowWidth(), 0.0444 * app_->getWindowHeight() }, selectSkill, SkillName::Torbellino, SkillType::Active, changeDescription));
	
	//Ghost Skills
	auxTexture = (!gm_->isSkillUnlocked(SkillName::LiberacionI)) ? app_->getTextureManager()->getTexture(Resources::TextureId::SkillLiberationBN) : app_->getTextureManager()->getTexture(Resources::TextureId::SkillLiberationC);
	auto it3 = skillsIcons_.insert(skillsIcons_.end(),new SkillButton(app_, auxTexture, { 0.2063 * app_->getWindowWidth(), 0.7244 * app_->getWindowHeight() }, { 0.0438 * app_->getWindowWidth(), 0.0444 * app_->getWindowHeight() }, selectSkill, SkillName::LiberacionI, SkillType::Pasive, changeDescription));

	auxTexture = (!gm_->isSkillUnlocked(SkillName::Explosion)) ? app_->getTextureManager()->getTexture(Resources::TextureId::SkillExplosionBN) : app_->getTextureManager()->getTexture(Resources::TextureId::SkillExplosionC);
	skillsIcons_.insert(skillsIcons_.end(),new SkillButton(app_, auxTexture, { 0.3138 * app_->getWindowWidth(), 0.7244 * app_->getWindowHeight() }, { 0.0438 * app_->getWindowWidth(), 0.0444 * app_->getWindowHeight() }, selectSkill, SkillName::Explosion, SkillType::Active, changeDescription));
	
	auxTexture = (!gm_->isSkillUnlocked(SkillName::LiberacionII)) ? app_->getTextureManager()->getTexture(Resources::TextureId::SkillLiberationBN) : app_->getTextureManager()->getTexture(Resources::TextureId::SkillLiberationC);
	skillsIcons_.insert(skillsIcons_.end(),new SkillButton(app_, auxTexture, { 0.4275 * app_->getWindowWidth(), 0.7244 * app_->getWindowHeight() }, { 0.0438 * app_->getWindowWidth(), 0.0444 * app_->getWindowHeight() }, selectSkill, SkillName::LiberacionII, SkillType::Pasive, changeDescription));

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
	vector<SkillName> aux = gm_->getAllSkillsEquipped();
	int i = 0;
	for (SkillName name : aux) {
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
	if (selectedRectangle == nullptr)selectedRectangle = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::RedBar), SDL_Rect{ (int)button->getPosX() - 10, (int)button->getPosY() - 10, (int)button->getScaleX() + 20, (int)button->getScaleY() + 10 });
	else {
		selectedRectangle->setPos(Vector2D(button->getPosX() - 10, button->getPosY() - 10));
	}
}

void SkillState::equipSelectedSkill(Key key)
{
	if (selected_ != nullptr && selected_->isUnlocked()) {
		//Si no est� asignada, no hay ninguna en esa tecla y no es una pasiva
		if (!selected_->isAsigned() && gm_->getEquippedSkill(key) == SkillName::Unequipped && selected_->getSkillType() != SkillType::Pasive) {
			selected_->setAsigned(true);
			gm_->setSkillEquiped(selected_->getSkillId(), key);
		}
		//Si est� equipada pero la tecla en la que queremos equipar est� libre
		else if (selected_->isAsigned() && selected_->getSkillType() != SkillType::Pasive && gm_->getEquippedSkill(key) == SkillName::Unequipped) {

			Key aux = gm_->getEquippedSkillKey(selected_->getSkillId());
			gm_->setSkillEquiped(SkillName::Unequipped, aux);
			gm_->setSkillEquiped(selected_->getSkillId(), key);
		}
		//La tecla en la que queremos asignar no est� libre
		else if (selected_->getSkillType() != SkillType::Pasive && gm_->getEquippedSkill(key) != SkillName::Unequipped) {
			SkillName aux = gm_->getEquippedSkill(key);
			//Buscamos el bot�n que asigna dicha skill
			auto it = skillsIcons_.begin();
			while (it != skillsIcons_.end() && aux != (*it)->getSkillId())++it;

			///Si la skill que queremos introducir est� ya asignada a una tecla
			if (selected_->isAsigned()) {
				//Buscamos en cual estaba asignada
				Key changingKey = gm_->getEquippedSkillKey((selected_)->getSkillId());
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
	//std::function<int (int)> func = [](int i) { return i+4; };

	function<void (Player*)> func = [](Player* player) { player->activeInvincible(); };

	auxPointsActualized(skillsTypeIterator[1], app_->getTextureManager()->getTexture(Resources::TextureId::SkillGolpeFuerteC),
		app_->getTextureManager()->getTexture(Resources::TextureId::SkillInvencibleC),
		app_->getTextureManager()->getTexture(Resources::TextureId::SkillTorbellinoC), gm_->getMeleePoints(),
		nullptr, func, nullptr);
}

void SkillState::distancePointsActualized()
{
	function<void(Player*)> func = [](Player* player) { player->activateSwiftGunslinger(); };

	auxPointsActualized(skillsTypeIterator[0], app_->getTextureManager()->getTexture(Resources::TextureId::SkillPerforanteC),
		app_->getTextureManager()->getTexture(Resources::TextureId::SkillRaudoC), app_->getTextureManager()->getTexture(Resources::TextureId::SkillReboteC),
		gm_->getPresicionPoints(), nullptr, func, nullptr);
}

void SkillState::ghostPointsActualized()
{
	function<void(Player*)> func1 = [](Player* player) { player->setLiberation(1); };
	function<void(Player*)> func2 = [](Player* player) { player->setLiberation(2); };

	auxPointsActualized(skillsTypeIterator[2], app_->getTextureManager()->getTexture(Resources::TextureId::SkillLiberationC),
		app_->getTextureManager()->getTexture(Resources::TextureId::SkillExplosionC), app_->getTextureManager()->getTexture(Resources::TextureId::SkillLiberationC)
		, gm_->getGhostPoints(), func1, nullptr, func2);
}

void SkillState::auxPointsActualized(list<SkillButton*>::iterator aux, Texture* t1, Texture* t2, Texture* t3, int points, std::function<void(Player*)> p1, std::function<void(Player*)> p2, std::function<void(Player*)> p3)
{
	delete totalPoints_;
	createTexts();
	if (points >= UNLOCK_FIRST_SKILL && !(*aux)->isUnlocked()) {
		(*aux)->setTexture(t1);
		(*aux)->setUnlocked(true);
		gm_->setSkillUnlocked((*aux)->getSkillId());
		
		if (p1 != nullptr) {
			p1(player_);
		}
	}
	++aux;
	if (points >= UNLOCK_SECOND_SKILL && !(*aux)->isUnlocked()) {
		(*aux)->setTexture(t2);
		(*aux)->setUnlocked(true);
		gm_->setSkillUnlocked((*aux)->getSkillId());
		if (p2 != nullptr) {
			p2(player_);
		}
	}
	++aux;
	if (points >= UNLOCK_THRID_SKILL && !(*aux)->isUnlocked()) {
		(*aux)->setTexture(t3);
		(*aux)->setUnlocked(true);
		gm_->setSkillUnlocked((*aux)->getSkillId());
		if (p3 != nullptr) {
			p3(player_);
		}
	}
}

Texture* SkillState::getTextureFromSkill(SkillName name)const
{
	Texture* tex;
	switch (name)
	{
	case SkillName::Unequipped:
		tex = nullptr;
		break;
	case SkillName::Invencible:
		tex = app_->getTextureManager()->getTexture(Resources::TextureId::SkillInvencibleC);
		break;
	case SkillName::Raudo:
		tex = app_->getTextureManager()->getTexture(Resources::TextureId::SkillRaudoC);
		break;
	case SkillName::LiberacionI:
		tex = app_->getTextureManager()->getTexture(Resources::TextureId::SkillLiberationC);
		break;
	case SkillName::LiberacionII:
		tex = app_->getTextureManager()->getTexture(Resources::TextureId::SkillLiberationC);
		break;
	case SkillName::GolpeFuerte:
		tex = app_->getTextureManager()->getTexture(Resources::TextureId::SkillGolpeFuerteC);
		break;
	case SkillName::Torbellino:
		tex = app_->getTextureManager()->getTexture(Resources::TextureId::SkillTorbellinoC);
		break;
	case SkillName::DisparoPerforante:
		tex = app_->getTextureManager()->getTexture(Resources::TextureId::SkillPerforanteC);
		break;
	case SkillName::Rebote:
		tex = app_->getTextureManager()->getTexture(Resources::TextureId::SkillReboteC);
		break;
	case SkillName::Clon:
		tex = app_->getTextureManager()->getTexture(Resources::TextureId::ClonIconRect);
		break;
	case SkillName::Explosion:
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
	totalPoints_->render({ (int)(0.7938 * app_->getWindowWidth()), (int)(0.2778 * app_->getWindowHeight()), (int)(0.0625 * app_->getWindowWidth()), (int)(0.0444 * app_->getWindowHeight()) });//{ 1270, 250, 100, 40 });
	GameState::draw();
	renderSkillsEquipped();
}

void SkillState::changeDescriptionTexture(SkillName name)const
{

	TextBox descriptionBox(app_, Point2D(descriptionRect.x, descriptionRect.y));
	switch (name)
	{
	case SkillName::Unequipped:
		break;
	case SkillName::GolpeFuerte:
		descriptionBox.GolpeFuerte();
		break;
	case SkillName::Invencible:
		descriptionBox.Invencible();
		break;
	case SkillName::Torbellino:
		descriptionBox.Torbellino();
		break;
	case SkillName::DisparoPerforante:
		descriptionBox.Perforador();
		break;
	case SkillName::Raudo:
		descriptionBox.Raudo();
		break;
	case SkillName::Rebote:
		descriptionBox.Rebote();
		break;
	case SkillName::Clon:
		descriptionBox.Clon();
		break;
	case SkillName::LiberacionI:
		descriptionBox.LiberationI();
		break;
	case SkillName::Explosion:
		descriptionBox.Explosion();
		break;
	case SkillName::LiberacionII:
		descriptionBox.LiberationII();
		break;
	default:
		break;
	}
}

void SkillState::changeDescription(SkillName name)
{
	lastPointed = name;
}

void SkillState::setPlayerSkills()
{

	if (player_ != nullptr) {
		auto aux = player_->getSkillsArray();
		for (int i = 0; i < gm_->getAllSkillsEquipped().size() - 1; i++) {//-i pq la del clon siempre est� equipada por defecto
			player_->setSkillAt(i, player_->createSkill(gm_->getEquippedSkill((Key)i)));
		}
	}
}

void SkillState::createButtons() {
	//Precision Button
	Button* precisionButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::ButtonUpgradeGreen), { 0.4813 * app_->getWindowWidth(), 0.4167 * app_->getWindowHeight() }, { 0.0313 * app_->getWindowWidth(), 0.0556 * app_->getWindowHeight() }, increasePrecisionBranch);
	addRenderUpdateLists(precisionButton);

	//Melee Button
	Button* meleeButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::ButtonUpgradeYellow), { 0.4813 * app_->getWindowWidth(), 0.5833 * app_->getWindowHeight() }, { 0.0313 * app_->getWindowWidth(), 0.0556 * app_->getWindowHeight() }, increaseMeleeBranch);
	addRenderUpdateLists(meleeButton);

	//Ghost Button
	Button* ghostButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::ButtonUpgradeBlue), { 0.4813 * app_->getWindowWidth(), 0.75 * app_->getWindowHeight() }, { 0.0313 * app_->getWindowWidth(), 0.0556 * app_->getWindowHeight() }, increaseGhostBranch);
	addRenderUpdateLists(ghostButton);

	//Back Button
	Button* backButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::ButtonX), { 0.8994 * app_->getWindowWidth(), 0.2378 * app_->getWindowHeight() }, { 0.0313 * app_->getWindowWidth(), 0.0491 * app_->getWindowHeight() }, backToPreviousState);
	addRenderUpdateLists(backButton);

	//Inventary Button
	Button* inventaryButton = new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::GoToInventoryAButton), { 0.0856 * app_->getWindowWidth(), 0.0244 * app_->getWindowHeight() }, { 0.35 * app_->getWindowWidth(), 0.1345 * app_->getWindowHeight() }, goToInventaryState);
	goToInventary_ = inventaryButton;
	addRenderUpdateLists(inventaryButton);

	///Botones en los que aparecer� la skillEquipada
	addRenderUpdateLists(new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::EquippedSkill), { 0.5875 * app_->getWindowWidth(), 0.77 * app_->getWindowHeight() }, { 0.0688 * app_->getWindowWidth(), 0.1222 * app_->getWindowHeight() }, assingToQKey));
	addRenderUpdateLists(new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::EquippedSkill), { 0.6669 * app_->getWindowWidth(), 0.77 * app_->getWindowHeight() }, { 0.0688 * app_->getWindowWidth(), 0.1222 * app_->getWindowHeight() }, assingToWKey));
	addRenderUpdateLists(new Button(app_, app_->getTextureManager()->getTexture(Resources::TextureId::EquippedSkill), { 0.7463 * app_->getWindowWidth(), 0.77 * app_->getWindowHeight() }, { 0.0688 * app_->getWindowWidth(), 0.1222 * app_->getWindowHeight() }, assingToEKey));

}

SkillState::~SkillState()
{
	for (int i = 0; i < 3; i++)delete emptyBars_[i];
	for (int i = 0; i < 3; i++)delete bars_[i];
	delete bg_; delete selectedRectangle;
	delete totalPoints_;
	//USABILIDAD
	if(GameManager::instance()->getAchievementPoints()!=pointsInOpen)openSkills->setPoints(true);
	Tracker::TrackEvent(openSkills);
	//
}

void SkillState::backToPreviousState(Application* app) {
	static_cast<SkillState*>(app->getCurrState())->setPlayerSkills();
	SDL_ShowCursor(SDL_DISABLE);
	app->getAudioManager()->resumeChannel(Resources::MainMusicChannel);
	app->getAudioManager()->pauseChannel(Resources::InventoryMusicChannel);
	app->getGameStateMachine()->popState();
}

void SkillState::goToInventaryState(Application* app) {
	static_cast<SkillState*>(app->getCurrState())->setPlayerSkills();
	app->getGameStateMachine()->changeState(new Inventory(app));
}

void SkillState::increasePrecisionBranch(Application* app) {
	GameManager* gm = GameManager::instance();
	int earnedPoints = gm->getAchievementPoints();
	int spendingPoints = 1;
	if (earnedPoints > 0 && gm->getPresicionPoints() < gm->getMaxPoints() && !gm->onTutorial()) {	//Comprueba que tenga puntos de haza�a que invertir y que la rama no tenga ya el maximo
		if (earnedPoints >= 10 && (gm->getMaxPoints() - gm->getPresicionPoints()) >= 10) spendingPoints = 10;
		gm->setPrecisionPoints(gm->getPresicionPoints() + spendingPoints);				//Aumenta en uno los puntos de esta rama
		gm->setArchievementPoints(gm->getAchievementPoints() - spendingPoints);				//Reduce en uno los puntos de haza�a
		dynamic_cast<SkillState*>(app->getCurrState())->distancePointsActualized();
	}
};

void SkillState::increaseMeleeBranch(Application* app) {
	GameManager* gm = GameManager::instance();
	int earnedPoints = gm->getAchievementPoints();
	int spendingPoints = 1;
	if (earnedPoints > 0 && gm->getMeleePoints() < gm->getMaxPoints()) {
		if (earnedPoints >= 10 && (gm->getMaxPoints() - gm->getMeleePoints()) >= 10) spendingPoints = 10;
		gm->setMeleePoints(gm->getMeleePoints() + spendingPoints);
		gm->setArchievementPoints(gm->getAchievementPoints() - spendingPoints);
		dynamic_cast<SkillState*>(app->getCurrState())->meleePointsActualized();
	}
};

void SkillState::increaseGhostBranch(Application* app) {
	GameManager* gm = GameManager::instance();
	int earnedPoints = gm->getAchievementPoints();
	int spendingPoints = 1;
	if (earnedPoints > 0 && gm->getGhostPoints() < gm->getMaxPoints() && !gm->onTutorial()) {
		if (earnedPoints >= 10 && (gm->getMaxPoints() - gm->getGhostPoints()) >= 10) spendingPoints = 10;
		gm->setGhostPoints(gm->getGhostPoints() + spendingPoints);
		gm->setArchievementPoints(gm->getAchievementPoints() - spendingPoints);
		dynamic_cast<SkillState*>(app->getCurrState())->ghostPointsActualized();
	}
}

void SkillState::selectSkill(Application* app, SkillButton* button)
{
	dynamic_cast<SkillState*>(app->getCurrState())->setSelectedSkillButton(button);
}

void SkillState::assingToQKey(Application* app)
{
	dynamic_cast<SkillState*>(app->getCurrState())->equipSelectedSkill(Key::Q);
}

void SkillState::assingToWKey(Application* app)
{
	dynamic_cast<SkillState*>(app->getCurrState())->equipSelectedSkill(Key::W);
}

void SkillState::assingToEKey(Application* app)
{
	dynamic_cast<SkillState*>(app->getCurrState())->equipSelectedSkill(Key::E);
}

void SkillState::changeDescription(Application* app, SkillName name)
{
	dynamic_cast<SkillState*>(app->getCurrState())->changeDescription(name);
}
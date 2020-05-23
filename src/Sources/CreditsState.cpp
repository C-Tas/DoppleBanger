#include "CreditsState.h"
#include "Button.h"
#include "MainMenuState.h"

CreditsState::~CreditsState()
{
	app_->getAudioManager()->playChannel(Resources::AudioId::MainTheme, -1, Resources::MainMusicChannel);
	delete fileRect_;
}

void CreditsState::update()
{
	if (buttonAmpl_.isCooldownActive()) { buttonAmpl_.updateCooldown(); }
	if (!buttonAmpl_.isCooldownActive()) {
		buttonAmpl_.initCooldown(BUTTON_AMP);
		if(twitterButton_->getScaleX() < 55 && growing_)
		{
			twitterButton_->setScale(Vector2D(twitterButton_->getScaleX() + 1, twitterButton_->getScaleY() + 1));
			gitButton_->setScale(Vector2D(twitterButton_->getScaleX() + 1, twitterButton_->getScaleY() + 1));
			if (twitterButton_->getScaleX() >= 55) {
				growing_ = false;
			}
		}
		else{
			twitterButton_->setScale(Vector2D(twitterButton_->getScaleX() - 1, twitterButton_->getScaleY() - 1));
			gitButton_->setScale(Vector2D(twitterButton_->getScaleX() - 1, twitterButton_->getScaleY() - 1));
			if (twitterButton_->getScaleX() <= 50) {
				growing_ = true;
			}
		}
	}
	GameState::update();
}

void CreditsState::initState() {
	background_ = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::CreditBackground));
	addRenderUpdateLists(background_);

	Vector2D scaleButton(app_->getWindowWidth() / 6, app_->getWindowHeight() / 15);
	Vector2D posButton(scaleButton.getX() / 2, scaleButton.getY() / 4);
	createBeerButton(app_, app_->getTextureManager()->getTexture(Resources::BackButton), posButton, scaleButton, backToPreviousState, this); //Boton "Volver"
	createAvatars();
	createFiles();
	createGratitudePanel();
	createBonusButton();
	app_->getAudioManager()->playChannel(Resources::AudioId::CreditTheme, -1, Resources::MainMusicChannel);
}

void CreditsState::createAvatars()
{
	int avatarTexture = Resources::Agus;
	Vector2D initPos = { (double)app_->getWindowWidth() / 10, (double)app_->getWindowHeight() / 10 };
	for (int i = 0; i < 7; i++) {
		InventoryButton* avatar = new InventoryButton(app_, initPos, Vector2D(AVATAR_W, AVATAR_H), nullptr, selectAvatar);
		avatar->setTexture(app_->getTextureManager()->getTexture(avatarTexture));
		avatar->setDeclarator(avatarTexture +1);
		SDL_SetTextureAlphaMod(avatar->getTexture()->getSDLTex(), 175);
		addRenderUpdateLists(avatar);
		initPos.setX(initPos.getX() + AVATAR_W);
		avatarTexture++;
		if (i == 4) {
			initPos = { (double)app_->getWindowWidth() / 10, (double)app_->getWindowWidth() / 10 + (AVATAR_H / 2) };
		}
	}
}

void CreditsState::createFiles()
{
	fileRect_ = new SDL_Rect{ (app_->getWindowWidth() / 2) + (int)(FILE_W / 5),app_->getWindowHeight() / 4, (int)FILE_W,(int)FILE_H };
	currFile_ = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::fichaPrimera), *fileRect_);
	addRenderUpdateLists(currFile_);

	twitterX = ((fileRect_->x + fileRect_->w) - (TWITTER_W * 1.5));
	twitterY = ((fileRect_->y + fileRect_->h) - (TWITTER_H * 1.5));
	twitterButton_ = new InventoryButton(app_, Vector2D(twitterX, twitterY), Vector2D(TWITTER_W, TWITTER_H), nullptr, openTwitter);
	twitterButton_->setTexture(app_->getTextureManager()->getTexture(Resources::TwitterButton));
	addRenderUpdateLists(twitterButton_);

	gitButton_ = new InventoryButton(app_, Vector2D(fileRect_->x + TWITTER_W, twitterY) ,
		Vector2D(TWITTER_W, TWITTER_H), nullptr, openGit);
	gitButton_->setTexture(app_->getTextureManager()->getTexture(Resources::GitButton));
	addRenderUpdateLists(gitButton_);
}

void CreditsState::showAvatarInfo(InventoryButton* avatar)
{
	if (avatarSelected_ != nullptr) {
		SDL_SetTextureAlphaMod(avatarSelected_->getTexture()->getSDLTex(),175);
	}
	avatarSelected_ = avatar;
	SDL_Texture* tex = avatarSelected_->getTexture()->getSDLTex();
	SDL_SetTextureAlphaMod(avatarSelected_->getTexture()->getSDLTex(), 255);
	cout << avatar->getDeclarator() << endl;
	currFile_->setTexture(app_->getTextureManager()->getTexture(avatar->getDeclarator() + 6));
	twitterButton_->setDeclarator(avatar->getDeclarator());
	gitButton_->setDeclarator(avatar->getDeclarator());
}

void CreditsState::openTwitterWeb(int option)
{	//Cuando se agregen todos los twitters se cuadraran
	/*	Agus,
		//Aida,
		Amaro,
		//Aurora,
		Dani,
		Georgi,
		Leyre,
		//Paula
		Oscar,
		Stiven,*/
	switch (option)
	{
		//Agus
	case 294:
		break;
		//Amaro
	case 295:
		system("start https://twitter.com/AmaroBlestPolo");
		break;
		//
	case 296:

		break;
	default:
		system("start https://twitter.com/DoppleBangerVG");
		break;
	}
	
}

void CreditsState::openGitWeb(int option)
{	//Cuando se agregen todos los twitters se cuadraran
	/*	Agus,
		//Aida,
		Amaro,
		//Aurora,
		Dani,
		Georgi,
		Leyre,
		//Paula
		Oscar,
		Stiven,*/
	switch (option)
	{
		//Agus
	case 294:
		break;
		//Amaro
	case 295:
		system("start https://github.com/Sounagix");
		break;
		//
	case 296:

		break;
		//
	default:
		system("start https://github.com/C-Tas/DoppleBanger");
		break;
	}

}

void CreditsState::createGratitudePanel()
{
	gratitudePanel_ = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::PanelCollaborators),
		{ app_->getWindowWidth() / 4 - (GRATITUDE_W / 8) ,app_->getWindowHeight() / 2 + (GRATITUDE_H /8),GRATITUDE_W,GRATITUDE_H });
	addRenderUpdateLists(gratitudePanel_);
}

void CreditsState::createBonusButton()
{
	bonusButton_ = new InventoryButton(app_, Vector2D((app_->getWindowWidth() / 2) + (BONUS_W * 1.6), (app_->getWindowHeight() - (BONUS_H * 2))) ,
		Vector2D(BONUS_W, BONUS_H), nullptr, openBonus);
	bonusButton_->setTexture(app_->getTextureManager()->getTexture(Resources::BotonBonus));
	addRenderUpdateLists(bonusButton_);
}

void CreditsState::openBonus()
{
	VisualElement* bonus = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::Bonus)
		, { 100,100,app_->getWindowWidth() - 200,app_->getWindowHeight() - 200 });
	addRenderUpdateLists(bonus);
	//desactiveButtons();
}

void CreditsState::desactiveButtons()
{
	avatarSelected_->setNewCallBack(nullptr);
	twitterButton_->setNewCallBack(nullptr);
	gitButton_->setNewCallBack(nullptr);
	bonusButton_->setNewCallBack(nullptr);
}

void CreditsState::backToPreviousState(Application* app) {
	app->getGameStateMachine()->popState();
}

void CreditsState::selectAvatar(Application* app, InventoryButton* avatar) {
	dynamic_cast<CreditsState*>(app->getCurrState())->showAvatarInfo(avatar);
}

void CreditsState::openTwitter(Application* app, InventoryButton* avatar)
{
	dynamic_cast<CreditsState*>(app->getCurrState())->openTwitterWeb(avatar->getDeclarator());
}

void CreditsState::openGit(Application* app, InventoryButton* avatar)
{
	dynamic_cast<CreditsState*>(app->getCurrState())->openGitWeb(avatar->getDeclarator());
}

void CreditsState::openBonus(Application* app, InventoryButton* avatar)
{
	dynamic_cast<CreditsState*>(app->getCurrState())->openBonus();
}

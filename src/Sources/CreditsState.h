#pragma once
#include "GameState.h"
#include "InventoryButton.h"
#include "VisualElement.h"

using CallBackOnClickInventory = void(Application * app, InventoryButton * button);


class CreditsState : public GameState
{
public:
	///<summary>Constructora de CreditsState</summary>
	CreditsState(Application* app = nullptr) :GameState(app) { initState(); };
	///<summary>Destructora</summary>
	virtual ~CreditsState();
	///<summary>Metodo para pasar a los botones de este estado, vuelve al anterior</summary>
	virtual void update();
	static void backToPreviousState(Application* app);
	static void selectAvatar(Application* app, InventoryButton* avatar);
	static void openTwitter(Application* app, InventoryButton* avatar);
	static void openGit(Application* app, InventoryButton* avatar);
	static void openBonus(Application* app, InventoryButton* avatar);
private:
	InventoryButton* avatarSelected_ = nullptr;
	InventoryButton* twitterButton_ = nullptr;
	InventoryButton* gitButton_ = nullptr;
	InventoryButton* bonusButton_ = nullptr;

	VisualElement* currFile_ = nullptr;
	VisualElement* gratitudePanel_ = nullptr;
	Cooldown buttonAmpl_;
	bool growing_ = true;
	const int BUTTON_AMP = 250;
	const int numAvatars = 10;
	vector<Button*> avatars_;
	SDL_Rect* fileRect_ = nullptr;
	const double AVATAR_W = 150;
	const double AVATAR_H = 175;
	const double FILE_W = 600;
	const double FILE_H = 400;
	const int TWITTER_W = 50;
	const int TWITTER_H = 50;
	const int GRATITUDE_W = 400;
	const int GRATITUDE_H = 300;
	const int BONUS_W = 200;
	const int BONUS_H = 100;
	double twitterX = 0;
	double twitterY = 0;
	void createAvatars();
	void createFiles();
	void showAvatarInfo(InventoryButton* avatar);
	void openTwitterWeb(int option);
	void openGitWeb(int option);
	void createGratitudePanel();
	void createBonusButton();
	void openBonus();
	void desactiveButtons();
	virtual void initState();
};


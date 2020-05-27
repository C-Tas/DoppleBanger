#include "WinState.h"
#include "CreditsState.h"

void resetGame(Application* app) {
	app->getGameStateMachine()->clearAllStateExceptFirst();
	app->getGameStateMachine()->pushState(new CreditsState(app));
}

void WinState::initState()
{
	SDL_ShowCursor(SDL_ENABLE);
	//Inicializamos la musica
	app_->resetMusicChannels();
	app_->resetSoundsChannels();
	app_->getAudioManager()->playChannel(Resources::MainTheme, -1, Resources::MainMusicChannel);

	background_ = new VisualElement(app_, app_->getTextureManager()->getTexture(Resources::Win));
	addRenderUpdateLists(background_);

	double winWidth = app_->getWindowWidth();
	double winHeight = app_->getWindowHeight();

	Vector2D sizeButton = Vector2D(winWidth / 6, winHeight / 10);
	Vector2D posButton = Vector2D((winWidth / 2) - sizeButton.getX() / 2, (winHeight * 5 / 6));
	createBeerButton(app_, app_->getTextureManager()->getTexture(Resources::CreditsButton), posButton, sizeButton, resetGame, this);
}


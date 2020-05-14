#include "WinState.h"
#include "EndState.h"

void resetGame(Application* app) {
	app->getGameStateMachine()->clearAllStateExceptFirst();
}

void WinState::initState()
{
	SDL_ShowCursor(SDL_ENABLE);
	//Inicializamos la musica
	app_->resetMusicChannels();
	app_->resetSoundsChannels();
	app_->getAudioManager()->playChannel(Resources::MainTheme, -1, Resources::MainMusicChannel);

	createButton(app_, app_->getTextureManager()->getTexture(Resources::Win), Vector2D(0, 0),
		Vector2D(app_->getWindowWidth(), app_->getWindowHeight()), resetGame);
}


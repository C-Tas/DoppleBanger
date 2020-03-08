#include "MainMenuState.h"
#include "ControlsState.h"
#include "CreditsState.h"
#include "StoryState.h"
#include "SaveLoadState.h"
#include "Button.h"
#include "Texture.h"
using namespace std;
MainMenuState::MainMenuState(Application* app):GameState(app) {
#ifndef NDEBUG
	cout << "MainMenuState";
#endif // !NDEBUG


	 initMenuState(); 

}
void MainMenuState::initMenuState()
{
	Button* b = new Button(new Texture(app_->getRenderer(), "../Sources/assets/timon.png"), { 50,50 }, { 50,50 }, goControlState);
	gameObjects_.push_back(b);
	objectsToRender_.push_back(b);
	//meter botones etc..
	//gameObjects_.push_back();
    // player_ = new Player(Vector2D(0.5, -0.5), new Texture(app_->getRenderer(), "../Sources/assets/timon.png"),
	// 	&SDL_Rect({ 50,50,100,100 }), Vector2D(50, 50), Vector2D(50, 50), SDL_Rect({ 0,0,0,0 }));
	// addUpdateList(player_);
	// addRenderList(player_);
}

void MainMenuState::goControlState(Application* app) {
	app->getStateMachine()->pushState( new ControlsState(app));
};
void MainMenuState::goCreditsState(Application* app) {
	app->getStateMachine()->pushState( new CreditsState(app));
};
void MainMenuState::goLoadState(Application* app) {
	app->getStateMachine()->pushState(new SaveLoadState(app, true)); //TRUE => LOAD //FALSE => SAVE
};
void MainMenuState::goStoryState(Application* app) {
	app->getStateMachine()->pushState( new StoryState(app));
};
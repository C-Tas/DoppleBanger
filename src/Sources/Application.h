#pragma once

#include "SDL.h"
#include "GameStateMachine.h"
#include "RandEquipGen.h"
#include "TextureManager.h"
#include "checkML.h"
using namespace std;

class Application
{
private:

	///<summary>Variables basicas de SDL</summary>
	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;

	///<summary>Máquina de estados</summary>
	GameStateMachine* machine_ = nullptr;
	///<summary>Manager que gestiona las texturas </summary>
	TextureManager* textureManager_ = nullptr;
	///<summary>Generador de randoms</summary>
	RandEquipGen* equipGen_ = nullptr;
	
	///<summary>Variables que controla el fin del bucle principal de app</summary>
	bool appClosed_ = false;

	///<summary>Constantes con las dimensiones de la ventana </summary>
	static const int winWidth_ = 1600;
	static const int winHeight_ = 900;

	///<summary>Metodo que inicializa SDL</summary>
	void initSDL();
	///<summary>Metodo que inicializa los recursos de la app</summary>
	void initResources();

	///<summary>Método que borra la memoria generada añ crear los recursos</summary>
	void closeResources();

	///<summary>Frame actual </summary>
	Uint64 currTicks_ = SDL_GetPerformanceCounter();
	///<summary>Frame anterior </summary>
	Uint64 lastTicks_ = 0;
	///<summary>Tiempo que ha pasado entre el frame actual y el anterior </summary>
	double deltaTime_;
	void updateDelta();

	///<summary>Area en la que se encuentra el jugador (1 - 3 -> primera isla, 4 - 6 -> segunda isla)</summary>
	///<summary>Esto deberia ir en el GameManager</summary>
	int currArea_ = 1;

public:
	///<summary>Construtora de la app</summary>
	Application(GameStateMachine* state=nullptr);
	virtual ~Application(); 

	///<summary>Bucle principal de la aplicacion</summary>
	void runApp();
#pragma region Setters
	///<summary>Metodo que termina el bucle principal de la app</summary>
	void endGame() { appClosed_ = true; };
#pragma endregion

#pragma region Getters
	///<summary>Devuelve maquina de estados</summary>
	GameStateMachine* getStateMachine() { return machine_; };
	///<summary>Devuelve el estado actual</summary>
	GameState* getCurrState() { return machine_->getState(); };
	///<summary>Devuelve si se esta procesando el bucle principal de la  </summary>
	bool isRunning() { return !appClosed_; };
	///<summary>Devuelve ancho de la ventana</summary>
	int getWindowWidth() { return winWidth_; };
	///<summary>Devuelve alto de la ventana </summary>
	int getWindowHeight() { return winHeight_; };
	///<summary>Devuelve ventana </summary>
	SDL_Window* getWindow() { return window_; };
	///<summary>Devuelve renderer </summary>
	SDL_Renderer* getRenderer() { return renderer_; };
	///<summary>Devuelve el tiempo que ha pasado entre el frame actual y el anterior </summary>
	double getDeltaTime() { return deltaTime_; }
	///<summary>Frame actual </summary>
	int getCurrArea() { return currArea_; }; //Mover a GameManager cuando tengamos
	///<summary>Devuelve el texture manager</summary>
	TextureManager* getTextureManager() { return textureManager_; };

	///<summary>Devuelve el generador de equipamiento aleatorio </summary>
	Equipment* genEquip() { return equipGen_->genEquip(); };
	///<summary>Devuelve un objeto del tipo type generado aleatoriamente</summary>
	Equipment* genEquip(equipType type) { return equipGen_->genEquip(type); };
#pragma endregion

	
};

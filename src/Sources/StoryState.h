#pragma once
#include <array>
#include "GameState.h"

using uint = unsigned int;

struct Scene {
	Uint32 duration;
	Texture* sceneTexture;
};

class StoryState :
	public GameState
{
public:
	///<summary>Constructora de la clase StoryState</summary>
	StoryState(Application* app = nullptr) :GameState(app) { initState(); timeSinceUpdate = SDL_GetTicks(); };
	///<summary>Destructora</summary>
	virtual ~StoryState() {};

	///<summary>Metodos redefinifos de la clase padre</summary>
	virtual void draw() const;
	virtual void update();

	///<summary>Método para pasar al juego </summary>
	void goToGame();
private:
	///<summary>Numero de escenas que cuentan la historia del juego</summary>
	static const uint nScenes = 3;
	///<summary>Array que contiene las información (Textura y duración) de las distintas escenas</summary>
	array<Scene, nScenes> scenes;
	///<summary>Contador de la escena en la que nos encontramos</summary>
	int currentScene = 0;
	///<summary>Tiempo desde el ultimo cambio de escena</summary>
	Uint32 timeSinceUpdate;

	///<summary>Método auxiliar para inicializar el estado</summary>
	void initState();
};


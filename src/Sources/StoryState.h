#pragma once
#include <stack>
#include "GameState.h"

//<summary>Struct que define cada una de las escenas (imagen a mostrar y duraci�n de la misma)</summary>
struct Scene {
	Uint32 duration;
	Texture* sceneTexture;
};

class StoryState : public GameState
{
public:
	///<summary>Constructora de la clase StoryState</summary>
	StoryState(Application* app = nullptr) :GameState(app) { initState(); };
	///<summary>Destructora</summary>
	virtual ~StoryState() {};

	///<summary>Metodos redefinidos de la clase padre</summary>
	virtual void draw() const;
	virtual void update();

	///<summary>M�todo para pasar al juego </summary>
	static void goToGame(Application* app);
private:

	///<summary>Pila que contiene la informaci�n (Textura y duraci�n) de las distintas escenas</summary>
	stack<Scene> scenes;
	///<summary>Tiempo desde el ultimo cambio de escena</summary>
	Uint32 timeSinceUpdate;

	///<summary>M�todo auxiliar para inicializar el estado, asigna las texturas de las escenas, el tiempo que dura cada una y
	/// un bot�n para saltar directamente al juego</summary>
	void initState();
};


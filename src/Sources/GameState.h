#pragma once
#include "GameObject.h"
#include "Draw.h"
#include "Application.h"
#include "SDL.h"
#include "Texture.h"
#include "Resources.h"
#include <list>
//#include "//clase EventHandler"
using namespace std;
using uint = unsigned int;

class GameState
{
protected:
	///<summary>Lista con todos los objetos</summary>
	list<GameObject*> gameObjects_;
	///<summary>Lista con todos los objetos con metodo Draw()</summary>
	list<Draw*> objectsToRender_;
	//list<EventHandlerClass*> objectEvents_;
	///<summary>Puntero a la aplicacion</summary>
	Application* app_;
public:
	GameState(Application* app = nullptr) : app_(app) {};
	virtual ~GameState();
	///<summary>Renderiza todos los objetos en la lista de objectToRender_</summary>
	virtual void draw() const;//Renderiza todos los objetos en la lista de objectToRender_
	///<summary>Actualiza todos los objetos en la lista de gameObjects_</summary>
	virtual void update();
	///<summary>Maneja los eventos de todos los objetos en la lista de objectEvents_</summary>
	virtual void handleEvents(SDL_Event& event);//Ejecuta los eventos de los objetos objectEvents_
	///<summary>Añade un objeto a la lista de gameObjects</summary>
	virtual void addUpdateList(GameObject* obj);
	///<summary>Añade un objeto a la lista de objectsToRender_</summary>
	virtual void addRenderList(Draw* obj);
};


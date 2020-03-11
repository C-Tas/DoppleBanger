#pragma once

#include "GameObject.h"
#include "Draw.h"
#include "Application.h"
#include "SDL.h"
#include "Texture.h"
#include "Resources.h"
#include "HandleEvents.h"
#include "Button.h"
#include <list>
#include "checkML.h"

using namespace std;
using uint = unsigned int;

using CallBackOnClick = void(Application * App);
class GameState
{
protected:
	///<summary>Lista con todos los objetos</summary>
	list<GameObject*> gameObjects_;
	///<summary>Lista con todos los objetos con metodo Draw()</summary>
	list<Draw*> objectsToRender_;
	///<summary>Lista con todos los objetos a eliminar</summary>
	list<GameObject*> objectsToErase_;
	///<summary>Puntero a la aplicacion</summary>
	Application* app_;
	///<summary>Referencia al HandleEvents</summary>
	HandleEvents* eventHandler_;

public:
	GameState(Application* app = nullptr) : app_(app) { eventHandler_ = HandleEvents::instance(); };
	virtual ~GameState();
	///<summary>Renderiza todos los objetos en la lista de objectToRender_</summary>
	virtual void draw() const;//Renderiza todos los objetos en la lista de objectToRender_
	///<summary>Actualiza todos los objetos en la lista de gameObjects_</summary>
	virtual void update();
	///<summary>Maneja los eventos de todos los objetos en la lista de objectEvents_</summary>
	///<summary>A�ade un objeto a la lista de gameObjects</summary>
	virtual void handleEvents();//Ejecuta los eventos de los objetos objectEvents_
	virtual void createButton(Texture* texture, Vector2D pos, Vector2D scale, CallBackOnClick* callBack,Application* app);
	///<summary>A�ade un objeto a la lista de gameObjects</summary>
	void addUpdateList(GameObject* obj);
	///<summary>A�ade un objeto a la lista de objectsToRender_</summary>
	void addRenderList(Draw* obj);
	///<summary>A�ade un objeto a las listas de objectsToRender_ y gameObjects_</summary>
	void addRenderUpdateLists(Draw* obj);
	///<summary>Añade un elemento a la lista objectsToErase</summary>
	void addObjectsToErase(GameObject* obj);
};


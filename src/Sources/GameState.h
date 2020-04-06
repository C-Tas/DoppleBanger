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
#include "GameManager.h"

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
	list<GameObject*> objectsToRemove_;
	///<summary>Lista con todos los objetos con metodo Draw() a eliminar</summary>
	list<Draw*> rendersToRemove_;
	///<summary>Lista con todos los objetos con método Update() y metodo Draw() a eliminar</summary>
	list<Draw*> objRendToRemove_;
	///<summary>Puntero a la aplicacion</summary>
	Application* app_;
	///<summary>Referencia al HandleEvents</summary>
	HandleEvents* eventHandler_;
	///<summary>Referencia al gameManager</summary>
	GameManager* gameManager_;

public:
	GameState(Application* app = nullptr) : app_(app) { eventHandler_ = HandleEvents::instance(); gameManager_ = GameManager::instance(); };
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
	///<summary>A�ade un objeto a la lista objectsToRemove_</summary>
	void removeUpdateList(GameObject* obj);
	///<summary>A�ade un objeto a la lista de rendersToRemove_</summary>
	void removeRenderList(Draw* obj);
	///<summary>A�ade un objeto a las listas de objectsToRemove_ y rendersToRemove_</summary>
	void removeRenderUpdateLists(Draw* obj);
};


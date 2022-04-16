#pragma once

#include "Application.h"
#include "HandleEvents.h"
#include "GameManager.h"
#include <list>

class Draw;
class Button;

using namespace std;
using uint = unsigned int;

using CallBackOnClick = void(Application * App);

class GameState
{
public:
	GameState(Application* app = nullptr) : app_(app) { eventHandler_ = HandleEvents::instance(); gm_ = GameManager::instance(); };
	virtual ~GameState();
	///<summary>Renderiza todos los objetos en la lista de objectToRender_</summary>
	virtual void draw() const;//Renderiza todos los objetos en la lista de objectToRender_
	///<summary>Actualiza todos los objetos en la lista de gameObjects_</summary>
	virtual void update();
	//Para reiniciar el estado
	void resetState();
	///<summary>Maneja los eventos de todos los objetos en la lista de objectEvents_</summary>
	virtual void handleEvents();//Ejecuta los eventos de los objetos objectEvents_
	//Crea botones con un callback con parámetro Application*
	virtual void createButton(Application* app, Texture* texture, Point2D pos, Vector2D scale, CallBackOnClick* callBack);
	//Crea botones con un callback sin parametros
	virtual void createButton2(NoParCallBack* callBack, Application* app, Texture* texture, Point2D pos, Vector2D scale);
	//Crea botones con la animacion de las cervezas
	virtual void createBeerButton(Application* app, Texture* texture, Point2D pos, Vector2D scale, CallBackOnClick* callBack, GameState* gs);
	//Crea botones con la animacion de las cervezas
	virtual void createBeerButton2(NoParCallBack* callBack, Application* app, Texture* texture, Point2D pos, Vector2D scale, GameState* gs);
	//Estos metodos sirven para no dar mas de un click en los botones de un menu
	//cuando se ha hecho click en uno de ellos. Implementado tras la animacion
	//de las cervezas
	bool getButtonClick() { return buttonClicked_; };
	void setButtonClick(bool buttonClicked) { buttonClicked_ = buttonClicked; };

	///<summary>A�ade un objeto a la lista de gameObjects</summary>
	void addUpdateList(GameObject* obj);
	///<summary>A�ade un objeto como primer elemento a la lista de gameObjects</summary>
	void addUpdateListAsFirst(GameObject* obj);
	///<summary>A�ade un objeto como primer elemento a la lista de objectsToRender_</summary>
	void addRenderListAsFirst(Draw* obj);
	///<summary>A�ade un objeto a las listas de objectsToRender_ y gameObjects_ como primer elemento</summary>
	void addRenderUpdateListsAsFirst(Draw* obj);
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

	//Sirve para cargar el estado
	virtual void loadState() {};
protected:
	struct textBoxInfo {
		Texture* txt_ = nullptr;
		int x_ = 0;
		int y_ = 0;
	};
	bool buttonClicked_ = false;	//Para saber cuándo se ha hehco click en un boton
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
	//Background
	Draw* background_ = nullptr;
	//Puntero al gameManager
	GameManager* gm_ = nullptr;

	virtual void initState() = 0;
};


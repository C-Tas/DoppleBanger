#pragma once
#include "GameState.h"
#include <array>

class VisualElement;

using CallBackOnClick = void(Application * App);

class SelectLevelState :
	public GameState
{
public:
	SelectLevelState(Application* app);
	virtual ~SelectLevelState() {};

private: 
	//Imagen del mapa
	VisualElement* map_ = nullptr;

	//Mesa de fondo
	VisualElement* table_ = nullptr;

	//Imagen de la Isla Actual
	VisualElement* currIsland = nullptr;

	//Posiciones de los botones de las islas 1, 2 y 3
	const Vector2D buttonPosition_[3] = { Vector2D(0.344 * app_->getWindowWidth(), 0.2777 * app_->getWindowHeight()),
		Vector2D(0.404 * app_->getWindowWidth(), 0.7 * app_->getWindowHeight()),
		Vector2D(0.75 * app_->getWindowWidth(), 0.4222 * app_->getWindowHeight()) };		

	//Metodo privado para iniciar el estado
	void initState();
	//Crea los botones del State
	void createButtons();
}; 


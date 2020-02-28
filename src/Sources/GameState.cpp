#include "GameState.h"
//Actualiza todos los objetos que esten en la lista de objetos
void GameState::Update() {
	list<GameObject*>::iterator it = objectList_.begin();
	while (it!=objectList_.end())
	{
		//(*it)->update();
		it++;
	}
}
//Renderiza todos los objetos que esten en la lista de objetos
void GameState::Render() {
	list<GameObject*>::iterator it = objectList_.begin();
	while (it != objectList_.end())
	{
		//(*it)->Render();
		it++;
	}
}
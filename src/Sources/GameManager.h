#pragma once

#include <memory>
#include <iostream>

using namespace std;

class GameManager {
public:
	//Constructor vacío
	GameManager() {
		cout << "GameManager creado" << endl;
	}
	//Destructor
	virtual ~GameManager() {
		cout << "GameManager destruido" << endl;
	}
	//Construye un nuevo gameManger si es null
	static GameManager* instance() {
		if (instance_.get() == nullptr) {
			instance_.reset(new GameManager());
		}

		return instance_.get();
	}
	GameManager(GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;
private:
	//Puntero unico para evitar copias
	static unique_ptr<GameManager> instance_;
};




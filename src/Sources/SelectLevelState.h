#pragma once
#include "GameState.h"
#include <array>

using CallBackOnClick = void(Application * App);

class SelectLevelState :
	public GameState
{
public:
	SelectLevelState(Application* app);
	virtual ~SelectLevelState() {};

	void draw() const;
private: 
#pragma region Testeo
	Texture* map = nullptr;
	Texture* table = nullptr;
#pragma endregion

	///<summary>M�todo privado para iniciar el estado</summary>
	void initState();

	///<summary>Arrays con la informaci�n de los botones para que su creaci�n dependiendo del n�mero de islas desbloqueadas
	///sea m�s sencilla</summary>
	const array <Vector2D, 3> buttonPositions_ = { Vector2D(100, 400), Vector2D(800, 400),Vector2D(1300, 400) };
}; 


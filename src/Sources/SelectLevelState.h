#pragma once
#include "GameState.h"
#include <array>
#include "VisualElement.h"

using CallBackOnClick = void(Application * App);

class SelectLevelState :
	public GameState
{
public:
	SelectLevelState(Application* app);
	virtual ~SelectLevelState() {};

private: 
#pragma region Testeo
	VisualElement* map_ = nullptr;
	VisualElement* table_ = nullptr;
#pragma endregion

	///<summary>M�todo privado para iniciar el estado</summary>
	void initState();

	///<summary>Arrays con la informaci�n de los botones para que su creaci�n dependiendo del n�mero de islas desbloqueadas
	///sea m�s sencilla</summary>
	const array <Vector2D, 3> buttonPositions_ = { Vector2D(100, 400), Vector2D(800, 400),Vector2D(1300, 400) };
}; 


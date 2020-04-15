#pragma once
#include "GameState.h"
#include <list>


///<summary>Contenedor de la informaci�n tanto del alijo como del inventario</summary>
struct Container {
	///<summary>Lista con los objetos del inventario o del alijo</summary>
	list<InventoryButton*>* objects_;
	///<summary>"P�gina" del inventario en la que nos encontramos(es decir, en la que est�n los objetos del inventario que vemos en la interfaz)</summary>
	int page_ = 0;
	///<summary>Dinero de cada uno de las listas</summary>
	int money_ = 0;
	///<summary>Posici�n del texto con el dinero del container</summary>
	SDL_Rect moneyText = {0,0,0,0};
};

class StashState :
	public GameState
{
private:
	///<summary>Contenedor con la informaci�n del alijo</summary>
	Container stash_;
	//<summary>Contenedor con la informaci�n del inventario</summary>
	Container inventory_;
	///<summary>Textura del fondo del estado</summary>
	Texture* background_;
	///<summary>Puntero al boton seleccionado</summary>
	InventoryButton* selected_ = nullptr;
	///<summary>N�mero de elementos del inventario que se ven por pantalla</summary>
	const int INVENTORY_VISIBLE_ELEMENTS = 4;
	///<summary>N�mero de elementos del alijo que se ven por pantalla</summary>
	const int STASH_VISIBLE_ELEMENTS = 8;
	///<summary>Puntero a la textura con el texto del dinero del alijo</summary>
	Texture* stashMoneyTex_ = nullptr;
	///<summary>Puntero a la textura con el texto del dinero del inventario</summary>
	Texture* inventoryMoneyTex_ = nullptr;
	///<summary>Puntero a la textura con la descripcion del objeto seleccionado</summary>
	Texture* selectedObjectDescription_ = nullptr;
	///<summary>Tama�o de los botones</summary>
	const int BUTTON_SIZE = 0.75*(app_->getWindowHeight()/9);
	///<summary>Posici�n en y en la que se pintan las flechas para avanzar/retroceder en el inventario/alijo </summary>
	const int ARROW_ROW = (16*(app_->getWindowHeight()/50))+8;
	///<summary>Posici�n en y en la que se pintan los botones para mover el dinero entre el inventario/alijo</summary>
	const int MONEY_BUTTON_ROW = 13* (app_->getWindowHeight() / 50);
	///<summary>Posici�n en x en la que se pintan los botones de cerrar alijo, borrar objeto y cambiar de lista</summary>
	const int FUNCTIONALITY_BUTTONS_COLUMN = (9 * (app_->getWindowWidth() / 10))-13;
	///<summary>Ancho en p�xeles de un caracter</summary>
	const int FONT_WIDTH = (int)(app_->getWindowWidth()/60);
	///<summary>Alto en p�xeles de un caracter</summary>
	const int FONT_HEIGHT = (int)(1.7*FONT_WIDTH);

	///<summary>M�todo para inicializar el estado. Se le llama desde la constructora</summary>
	void initState();
	///<summary>M�todo para asignar al gameManager los nuevos valores del dinero del inventario y del alijo. Se le llama desde
	///la destructora </summary>
	void endState();

	///M�todos privados auxiliares para los callbacks
#pragma region privateCallbacks
	void advanceInventoryPage();
	void previousInventoryPage();
	void advanceStashPage();
	void previousStashPage();
	void selectObject(InventoryButton* button);
	void changeBetweenLists();
	void deleteObject();
	void addMoneyToInventory();
	void addMoneyToStash();
#pragma endregion

	///<summary>M�todo privado para pintar las dos listas con objetos de la forma que precisen</summary>
	void drawList(list<InventoryButton*>*  list_, int page, const int elemsPerPage, Vector2D iniElemPos, Vector2D distanceBetween,int elementsPerRow = 1)const ;
	///<summary>M�todo privado para saber cuantas cifras tiene el dinero tanto del inventario como del alijo (para que los numeros tengan
	///siempre el mismo tama�o)</summary>
	int nOfDigits(int n) const;
	///<summary>M�todo para volver a la p�gina anterior si se borra/cambia el ultimo elemento del alijo/inventario</summary>
	void selectedIsLastElement(Container & list_, int nVisibleElements);
	///<summary>M�todo auxiliar para actualizar los valores en los textos del dinero al cambiarlos</summary>
	void moneyChange();


public:
	///<summary>Constructora del StashState</summary>
	StashState(Application* app = nullptr) : GameState(app) { initState(); };
	///<summary>Detsructora</summary>
	virtual ~StashState() { endState(); background_ = nullptr; };

#pragma region Callbacks

	//<summary>Callbacks para cambiar elementos de este estado</summary>
	///<summary>Vuelta al barco</summary>
	static void backToPrevious(Application* app);
	///<summary>Callbacks para avanzar/retroceder las paginas del alijo/inventario </summary>
	static void callbackAdvanceInventoryPage(Application* app);
	static void callbackPreviousInventoryPage(Application* app);
	static void callbackAdvanceStashPage(Application* app);
	static void callbackPreviousStashPage(Application* app);
	
	///<summary>Selecciona el objeto sobre el que se hace click</summary>
	static void callbackSelectObject(GameState* state, InventoryButton* button);
	///<summary>Cambia de lista el objeto seleccionado</summary>
	static void callbackChangeBetweenLists(Application* app);
	///<summary>Borra el objeto seleccionado</summary>
	static void callbackDeleteObject(Application* app);
	///<summary>A�ade todo el dinero del alijo al inventario</summary>
	static void callbackAddMoneyToInventary(Application* app);
	///<summary>A�ade todo el dinero del alijo al inventario</summary>
	static void callbackAddMoneyToStash(Application* app);



#pragma endregion

	virtual void draw()const;
	virtual void update();

};


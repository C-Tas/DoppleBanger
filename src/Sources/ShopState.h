#pragma once
#include "GameState.h"
#include <list>

struct ContainerSHOP {
	///<summary>Lista con los objetos del inventario o del tienda</summary>
	list<InventoryButton*>* objects_ = nullptr;
	///<summary>"Pagina" del inventario en la que nos encontramos(es decir, en la que est�n los objetos del inventario que vemos en la interfaz)</summary>
	int page_ = 0;
	///<summary>Dinero de cada uno de las listas</summary>
	int money_ = 0;
	///<summary>Posicion del texto con el dinero del container</summary>
	SDL_Rect moneyText = { 0,0,0,0 };
	list<InventoryButton*>::iterator firstDrawn;
};

class ShopState :
	public GameState
{
private:
	///<summary>Contenedor con la informacion de la tienda</summary>
	ContainerSHOP shop_;
	//<summary>Contenedor con la informacion del inventario</summary>
	ContainerSHOP inventory_;
	///<summary>Textura del fondo del estado</summary>
	Texture* background_;
	///<summary>Puntero al boton seleccionado</summary>
	InventoryButton* selected_ = nullptr;
	///<summary>Puntero a la textura con el texto del dinero del inventario</summary>
	Texture* inventoryMoneyTex_ = nullptr;
	///<summary>Puntero a la textura con la descripcion del objeto seleccionado</summary>
	Texture* selectedObjectDescription_ = nullptr;

#pragma region Constants

	///<summary>Numero de elementos del inventario que se ven por pantalla</summary>
	const int INVENTORY_VISIBLE_ELEMENTS = 4;
	///<summary>Numero de elementos del tienda que se ven por pantalla</summary>
	const int SHOP_VISIBLE_ELEMENTS = 8;
	///<summary>Tama�o de los botones que son "cuadrados"</summary>
	const int BUTTON_SIZE = app_->getWindowHeight() / 12;
	///<summary>Tama�o de los botones que son "cuadrados"</summary>
	const Vector2D CLOSE_BUTTON_SIZE = { app_->getWindowHeight() / 15, app_->getWindowHeight() / 16 };
	///<summary>Posicion en y en la que se pintan las flechas para avanzar/retroceder en el inventario/tienda </summary>
	const int ARROW_ROW = (23 * (app_->getWindowHeight() / 100));
	///<summary>Posicion en y en la que se pintan los botones para mover el dinero entre el inventario/tienda</summary>
	const int MONEY_BUTTON_ROW = 28 * (app_->getWindowHeight() / 50);
	///<summary>Posici�n en x en la que se pintan los botones de cerrar tienda</summary>
	const int CLOSE_BUTTON_COLUMN = (9 * (app_->getWindowWidth() / 10));
	///<summary>Ancho en p�xeles de un caracter</summary>
	const int FONT_WIDTH = (app_->getWindowWidth() / 60);
	///<summary>Alto en p�xeles de un caracter</summary>
	const int FONT_HEIGHT = (int)(1.7 * FONT_WIDTH);
	///<summary>Distancia el texto númerico del dinero y el texto dinero inventario/tienda</summary>
	const int MONEY_TEXT_OFFSET = app_->getWindowWidth() / 100;
	///<summary>Número de elementos por fila que apareceran tanto en la tienda como en el inventario</summary>
	const int ELEMENTS_PER_ROW = 2;
	///<summary>Posici�n en x en la que se pintan los botones de borrar objeto y cambiar de lista</summary>
	const int FUNCTIONALITY_BUTTONS_ROW = MONEY_BUTTON_ROW;
	///<summary>Distancia entre los elementos del tienda</summary>
	const Vector2D DISTANCE_BETWEEN_ELEMENTS = { (app_->getWindowWidth() / 5), (app_->getWindowHeight() / 8) };
	///<summary>Posicion en el eje y en la que se empieza a dibujar las listas de objetos</summary>
	const int FIRST_ELEMENT_Y = (long long int)(app_->getWindowHeight() / 4) + (long long int)(app_->getWindowHeight() / 12);
	///<summary>Posición en la que se va a pintar el primer elemento de la lista del tienda</summary>
	const Vector2D FIRST_SHOP_ELEMENT = Vector2D((app_->getWindowWidth() / 9), FIRST_ELEMENT_Y);
	///<summary>Posición en la que se va a pintar el primer elemento de la lista del inventario</summary>
	const Vector2D FIRST_INVENTORY_ELEMENT = Vector2D(7 * (double)(app_->getWindowWidth() / 13), FIRST_ELEMENT_Y);
	///<summary>Tamaño de los objetos de tipo Gun</summary>
	const Vector2D GUN_SIZE = Vector2D(app_->getWindowWidth() / 12, app_->getWindowHeight() / 18);
	///<summary>Posición del Rect de las descripciones</summary>
	const SDL_Rect DESCRIPTION_RECT = { (app_->getWindowWidth() / 2) + 50, 3 * (app_->getWindowHeight() / 4) - 50, 2 * (app_->getWindowWidth() / 7), 4 * (app_->getWindowHeight() / 21) };

#pragma endregion

	///<summary>M�todo para inicializar el estado. Se le llama desde la constructora</summary>
	virtual void initState();
	///<summary>M�todo para asignar al gameManager los nuevos valores del dinero del inventario y del tienda. Se le llama desde
	///la destructora </summary>
	void endState();

	///M�todos privados auxiliares para los callbacks
#pragma region privateCallbacks
	void advanceInventoryPage();
	void previousInventoryPage();
	void advanceShopPage();
	void previousShopPage();
	void selectObject(InventoryButton* button);
	void changeBetweenLists();
	void deleteObject();
	void addMoneyToInventory();
#pragma endregion

	///<summary>M�todo privado para pintar las dos listas con objetos de la forma que precisen</summary>
	void drawList(list<InventoryButton*>* list_, list<InventoryButton*>::iterator page, const int elemsPerPage, Vector2D iniElemPos, Vector2D distanceBetween, int elementsPerRow = 1)const;
	///<summary>M�todo privado para saber cuantas cifras tiene el dinero tanto del inventario como del tienda (para que los numeros tengan
	///siempre el mismo tama�o)</summary>
	int nOfDigits(int n) const;
	///<summary>M�todo para volver a la p�gina anterior si se borra/cambia el ultimo elemento del tienda/inventario</summary>
	void selectedIsLastElement(ContainerSHOP& list_, int nVisibleElements);
	///<summary>M�todo auxiliar para actualizar los valores en los textos del dinero al cambiarlos</summary>
	void moneyChange();


public:
	///<summary>Constructora del ShopState</summary>
	ShopState(Application* app = nullptr) : GameState(app) { initState(); };
	///<summary>Detsructora</summary>
	virtual ~ShopState() { endState(); background_ = nullptr; };

#pragma region Callbacks

	//<summary>Callbacks para cambiar elementos de este estado</summary>
	///<summary>Vuelta al barco</summary>
	static void backToPrevious(Application* app);
	///<summary>Callbacks para avanzar/retroceder las paginas del tienda/inventario </summary>
	static void callbackAdvanceInventoryPage(Application* app);
	static void callbackPreviousInventoryPage(Application* app);
	static void callbackAdvanceShopPage(Application* app);
	static void callbackPreviousShopPage(Application* app);

	///<summary>Selecciona el objeto sobre el que se hace click</summary>
	static void callbackSelectObject(Application* app, InventoryButton* button);
	///<summary>Cambia de lista el objeto seleccionado</summary>
	static void callbackChangeBetweenLists(Application* app);
	///<summary>Borra el objeto seleccionado</summary>
	static void callbackDeleteObject(Application* app);
	///<summary>A�ade todo el dinero de la tienda al inventario</summary>
	static void callbackAddMoneyToInventary(Application* app);

#pragma endregion

	virtual void draw()const;
	virtual void update();
};


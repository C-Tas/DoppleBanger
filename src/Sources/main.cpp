#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "Application.h"

using namespace std;

int main(int argc, char** argv) {

	setlocale(LC_ALL, "");
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks

	Application* app = new Application();
	// USABILIDAD
	if (!app->initTracker()) {
		std::cout << "Error al inicializar el tracker\n";
		delete app;
		return 0;
	}

	app->runApp();

	delete app;
	return 0;
}
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "Application.h"

using namespace std;

int main(int argc, char** argv) {
	

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks

	Application* app = new Application();

 	app->runApp();

	delete app;
	return 0;
}
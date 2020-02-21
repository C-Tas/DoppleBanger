#pragma once
#include <iostream>
#include <vector>

using namespace std;

//Enum para las distintas imagenes del juego
typedef enum TextureId {
	//Determina la cantidad de texturas
	TexSize
};

//Enum para las distintos audios del juego
typedef enum AudioId {
	//Determina la cantidad de audios
	AudSize
};

//Vector con las rutas de las imagenes a cargar
static vector<string> texRoutes {
	("Ruta de los recursos a cargar"),
};

//Vector con las rutas de los audios a cargar
static vector<string> audRoutes{
	("Ruta de los recursos a cargar"),
};


class Resources
{
	static int textureSize() { return TexSize; };
	static int audioSize() { return AudSize; };
};


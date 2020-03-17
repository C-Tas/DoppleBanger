#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Resources
{
public:
	///<summary>Enum para las distintas imagenes del juego</summary>
	enum TextureId : int {
		//Objetos
		Timon,
		TextBox,

		//Fondos
		InventaryMenu
	};

	///<summary>Enum para las distintos audios del juego</summary>
	enum AudioId : int{
		
	};

	///<summary>Enum para las distintos fuentes del juego</summary>
	enum FontId : int {
		RETRO,
		RETROSM
	};
	
	///<summary>Struct para la informacion de las imagenes</summary>
	struct ImageInfo {
		TextureId textureId;
		string filename;
	};

	///<summary>Struct para la información del sonido</summary>
	struct SoundInfo {
		AudioId audioId;
		string filename;
	};

	///<summary>Struct para la informacion de la música</summary>
	struct MusicInfo {
		AudioId id;
		string fileName;
	};
	
	///<summary>Struct para la informacion de las fuentes</summary>
	struct FontInfo {
		FontId id;
		string fileName;
		int size;
	};

	///<summary>Vector con las rutas de las imagenes a cargar</summary>
	static vector<ImageInfo> imageRoutes;

	///<summary>Vector con las rutas de los audios a cargar</summary>
	static vector<SoundInfo> soundRoutes;

	///<summary>Vector con las rutas de la música a cargar</summary>
	static vector<MusicInfo> musicRoutes;
	
	///<summary>Vector con las rutas de las fuentes a cargar</summary>
	static vector<FontInfo> fontsRoutes;
};
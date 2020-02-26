#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Resources
{
public:
	//Enum para las distintas imagenes del juego
	enum TextureId : int {
	
	};

	//Enum para las distintos audios del juego
	enum AudioId : int{
		
	};

	struct ImageInfo {
		TextureId textureId;
		string filename;
	};

	struct SoundInfo {
		AudioId audioId;
		string filename;
	};

	struct MusicInfo {
		AudioId id;
		string fileName;
	};

	//Vector con las rutas de las imagenes a cargar
	static vector<ImageInfo> imageRoutes;

	//Vector con las rutas de los audios a cargar
	static vector<SoundInfo> soundRoutes;

	//Vector con las rutas de la música a cargar
	static vector<MusicInfo> musicRoutes;
};
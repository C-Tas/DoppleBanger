#include "Resources.h"

vector<Resources::ImageInfo> Resources::imageRoutes{
	{Timon, "../Sources/assets/timon.png"},
	{GoControls, "../Sources/assets/botonControles.png"},
	{BackButton, "../Sources/assets/volver.png"},
	{Controls, "../Sources/assets/controles.png"}
	//Para añadir nueva ruta: {TextureId, "../Sources/assets/name.png-jpg..."}
};

vector<Resources::SoundInfo> Resources::soundRoutes{
	//Para añadir nueva ruta: {AudioId, "./Sources/audio/name.mp3/wav..."}
};

vector <Resources::MusicInfo> Resources::musicRoutes{
	//Para añadir nueva ruta: {AudioId, "./Sources/audio/name.mp3/wav..."}
};

vector <Resources::FontInfo> Resources::fontsRoutes{
	//Para añadir nueva ruta: {FontId, "./Sources/fonts/name.ttf", size}
};
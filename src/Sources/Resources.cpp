#include "Resources.h"

vector<Resources::ImageInfo> Resources::imageRoutes{
	{Timon, "../Sources/assets/timon.png"}
	//Para añadir nueva ruta: {TextureId, "./Sources/images/name.png/jpg..."}
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
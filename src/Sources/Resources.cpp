#include "Resources.h"

vector<Resources::ImageInfo> Resources::imageRoutes{
	{ Timon, "../Sources/assets/timon.png" },
	{ TextBox, "../Sources/assets/whiteRectangle.png" },
	{ InventaryMenu, "../Sources/assets/InventarioFondo.png" }
	//Para añadir nueva ruta: {TextureId, "./Sources/images/name.png/jpg..."}
};

vector<Resources::SoundInfo> Resources::soundRoutes{
	//Para añadir nueva ruta: {AudioId, "./Sources/audio/name.mp3/wav..."}
};

vector <Resources::MusicInfo> Resources::musicRoutes{
	//Para añadir nueva ruta: {AudioId, "./Sources/audio/name.mp3/wav..."}
};

vector <Resources::FontInfo> Resources::fontsRoutes{
	{ RETRO, "../Sources/fonts/RetroGaming.ttf", 20 },
	{ RETROSM, "../Sources/fonts/RetroGaming.ttf", 18 }
	//Para añadir nueva ruta: {FontId, "./Sources/fonts/name.ttf", size}
};
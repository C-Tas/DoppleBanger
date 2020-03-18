#include "Resources.h"

vector<Resources::ImageInfo> Resources::imageRoutes{
	{ Timon, "../Sources/assets/timon.png" },
	{ GoControls, "../Sources/assets/botonControles.png"},
	{ BackButton, "../Sources/assets/volver.png"},
	{ Controls, "../Sources/assets/controles.png"},
	{ InventaryMenu, "../Sources/assets/InventarioFondo.png" },
	{ Scene1, "../Sources/assets/Scene1.png"},
	{ Scene2, "../Sources/assets/Scene2.png"},
	{ Scene3, "../Sources/assets/Scene3.png"},
	{ TextBox, "../Sources/assets/whiteRectangle.png" }
    ,{Dragon,"../Sources/assets/dragon.png"}
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
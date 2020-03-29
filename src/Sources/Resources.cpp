#include "Resources.h"

vector<Resources::ImageInfo> Resources::imageRoutes{
	//Interfaces
	{MenuFondo, "../Sources/assets/Interfaces/menuFondo.png"},
	{BotonMenu, "../Sources/assets/botonMenu.png"},
	{ Timon, "../Sources/assets/timon.png" },
	{ GoControls, "../Sources/assets/botonControles.png"},
	{ BackButton, "../Sources/assets/volver.png"},
	{ ForwardButton, "../Sources/assets/seguir.png"},
	{ Controls, "../Sources/assets/controles.png"},
	{ InventaryMenu, "../Sources/assets/InventarioFondo.png" },
	{ Scene1, "../Sources/assets/Scene1.png"},
	{ Scene2, "../Sources/assets/Scene2.png"},
	{ Scene3, "../Sources/assets/Scene3.png"},
	{ TextBox, "../Sources/assets/whiteRectangle.png" },
	//Sprites
	//Para añadir nueva ruta: {TextureId, "../Sources/assets/name.png-jpg..."}
	{Dragon,"../Sources/assets/dragon.png"}
	//Para añadir nueva ruta: {TextureId, "./Sources/images/name.png/jpg..."}
};

vector<Resources::SoundInfo> Resources::soundRoutes{
	//Para añadir nueva ruta: {AudioId, "./Sources/audio/name.mp3/wav..."}
};

vector <Resources::MusicInfo> Resources::musicRoutes{
	{MainTheme ,"../Sources/assets/music/mainTheme.mp3" }
	//Para añadir nueva ruta: {AudioId, "./Sources/audio/name.mp3/wav..."}
};

vector <Resources::FontInfo> Resources::fontsRoutes{
	{ RETRO, "../Sources/fonts/RetroGaming.ttf", 20 },
	{ RETROSM, "../Sources/fonts/RetroGaming.ttf", 18 }
	//Para añadir nueva ruta: {FontId, "./Sources/fonts/name.ttf", size}
};

vector <Resources::TextMsgInfo> Resources::messages_{

	//Para añadir nuevo texto: {TextureId , string "mensaje", { COLOR(0xaaffffff), FontId  }
	{ PlayText,"Nueva Partida",SDL_Color{(0,0,0,1)},RETRO },
	{ ExitText,"Salir",SDL_Color{(0,0,0,1)},RETRO },
	{ ControlsText,"Controles",SDL_Color{(0,0,0,1)},RETRO },
	{ LoadText,"Cargar Partida",SDL_Color{(0,0,0,1)},RETRO },
	{ CreditsText,"Créditos",SDL_Color{(0,0,0,1)},RETRO },
};

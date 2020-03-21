#include "Resources.h"

vector<Resources::ImageInfo> Resources::imageRoutes{
	//Botones
	{ Timon, "../Sources/assets/player/timon.png" },
	{ BotonMenu, "../Sources/assets/botones/botonMenu.png" },
	{ GoControls, "../Sources/assets/botones/botonControles.png" },
	{ BackButton, "../Sources/assets/botones/volver.png" },
	{ Resume, "../Sources/assets/botones/resume.png" },
	{ MuteOn, "../Sources/assets/botones/muteOn.png" },
	{ MuteOff, "../Sources/assets/botones/muteOff.png" },
	{ PauseButton, "../Sources/assets/botones/pauseButton.png" },

	//Interfaces
	{ Controls, "../Sources/assets/interfaces/controles.png" },
	{ MenuFondo, "../Sources/assets/interfaces/menuFondo.png" },
	{ InventaryMenu, "../Sources/assets/interfaces/InventarioFondo.png" },
	{ Pause, "../Sources/assets/interfaces/pauseFondo.png" },
	{ Scene1, "../Sources/assets/interfaces/Scene1.png" },
	{ Scene2, "../Sources/assets/interfaces/Scene2.png" },
	{ Scene3, "../Sources/assets/interfaces/Scene3.png" },
	{ TextBox, "../Sources/assets/interfaces/textBoxBg.png" },

	//Personajes
	{ Roca, "../Sources/assets/colisionables/roca.png" },
	{ Dragon,"../Sources/assets/enemigos/dragon.png" }

	//Para añadir nueva ruta: {TextureId, "../Sources/assets/name.png-jpg..."}
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

vector <Resources::TextMsgInfo> Resources::messages{

	//Para añadir nuevo texto: {TextureId , string "mensaje", { COLOR(0xaaffffff), FontId  }
	{ PlayText,"Nueva Partida",SDL_Color{(0,0,0,1)},RETRO },
	{ ExitText,"Salir",SDL_Color{(0,0,0,1)},RETRO },
	{ ControlsText,"Controles",SDL_Color{(0,0,0,1)},RETRO },
	{ LoadText,"Cargar Partida",SDL_Color{(0,0,0,1)},RETRO },
	{ CreditsText,"Créditos",SDL_Color{(0,0,0,1)},RETRO },
};

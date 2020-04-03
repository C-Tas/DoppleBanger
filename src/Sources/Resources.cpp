#include "Resources.h"

//Para añadir nueva ruta: {TextureId, "./Sources/images/name.png/jpg..."}
vector<Resources::ImageInfo> Resources::imageRoutes{
	//Botones
	{ MenuButton, "../Sources/assets/botones/botonMenu.png" },
	{ GoControls, "../Sources/assets/botones/botonControles.png" },
	{ BackButton, "../Sources/assets/botones/volver.png" },
	{ SkipButton, "../Sources/assets/botones/skipButton.png" },
	{ RestartGame, "../Sources/assets/botones/restartGame.png" },
	{ MuteOn, "../Sources/assets/botones/muteOn.png" },
	{ MuteOff, "../Sources/assets/botones/muteOff.png" },
	{ Resume, "../Sources/assets/botones/resume.png" },

	//Interfaces
	{ MenuBackground, "../Sources/assets/interfaces/menuFondo.png" },
	{ InventaryMenu, "../Sources/assets/interfaces/inventarioFondo.png" },
	{ Controls, "../Sources/assets/interfaces/controles.png" },
	{ PauseBackground, "../Sources/assets/interfaces/pauseFondo.png" },
	{ Scene1, "../Sources/assets/interfaces/Scene1.png" },
	{ Scene2, "../Sources/assets/interfaces/Scene2.png" },
	{ Scene3, "../Sources/assets/interfaces/Scene3.png" },
	{ TextBox, "../Sources/assets/interfaces/textBoxBg.png" },
	{ Ship, "../Sources/assets/interfaces/barco.png" },
	{ Table, "../Sources/assets/interfaces/mesa.png" },
	{ Map1, "../Sources/assets/interfaces/mapa1.png" },
	{ Map2, "../Sources/assets/interfaces/mapa2.png" },
	{ Map3, "../Sources/assets/interfaces/mapa3.png" },
	{ CaribbeanMap, "../Sources/assets/interfaces/caribe.png" },
	{ Spooky, "../Sources/assets/interfaces/fantasmal.png" },
	{ Volcanic, "../Sources/assets/interfaces/volcan.png" },
	{ GameOver, "../Sources/assets/interfaces/gameOver.png" },
	{ Win, "../Sources/assets/interfaces/win.png" },

	//HUD
	{  WheelHUD, "../Sources/assets/hud/timonHUD.png" },
	{  RopeHUD,	"../Sources/assets/hud/lazoHUD.png" },
	{  SkillsHUD, "../Sources/assets/hud/skillsHUD.png" },

	//Sprites
	{ Dragon,"../Sources/assets/enemigos/dragon.png"},
	{ PlayerFront, "../Sources/assets/player/frontal.png"},
	{ CrabAttack, "../Sources/assets/enemigos/crab/crab_attack.png" },
	{ MonkeyFront, "../Sources/assets/enemigos/monkey/monkeyFront.png" },

	//Interactuables
	{ Wheel, "../Sources/assets/player/timon.png" },
	{ Stash, "../Sources/assets/colisionables/alijo.png" },
	{ ShipDoor, "../Sources/assets/colisionables/trampilla.png"},
	{ ExitShip, "../Sources/assets/colisionables/exitShip.png" },

	//Colisionable
	{ Rock, "../Sources/assets/colisionables/roca.png" },
	{ Coco ,"../Sources/assets/Colisionables/coco.png" }
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

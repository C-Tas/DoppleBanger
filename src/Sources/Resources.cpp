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
	{ LeftArrow, "../Sources/assets/botones/flecha_izquierda.png"},
	{ RightArrow,"../Sources/assets/botones/flecha_derecha.png"},
	{ DeleteButton, "../Sources/assets/botones/Borrar_Boton.png"},
	{ ForwardArrow, "../Sources/assets/botones/FowardArrowButton.png"},
	{ BackwardsArrow, "../Sources/assets/botones/BackwardsArrowButton.png"},
	{ TrashButton, "../Sources/assets/botones/TrashButton.png"},
	{ ChangeButton, "../Sources/assets/botones/ChangeButton.png"},
	{ MoneyButton, "../Sources/assets/botones/MoneyButton.png"},
	{ EquippedButton, "../Sources/assets/botones/Equipar_Boton.png"},
	{ GoToInventoryAButton, "../Sources/assets/botones/InventoryButtonA.png"},
	{ GoToInventoryBButton, "../Sources/assets/botones/InventoryButtonB.png"},

	//Interfaces
	{ GoControls, "../Sources/assets/botones/botonControles.png"},
	{ BackButton, "../Sources/assets/botones/volver.png"},

	{ ButtonX, "../Sources/assets/botones/botonX.png"},
	{ ButtonUpgradeGreen, "../Sources/assets/botones/UpgradeButtonGreen.png"},
	{ ButtonUpgradeRed, "../Sources/assets/botones/UpgradeButtonRed.png"},
	{ ButtonUpgradeBlue, "../Sources/assets/botones/UpgradeButtonBlue.png"},
	{ ButtonUpgradeYellow, "../Sources/assets/botones/UpgradeButtonYellow.png"},

	//Barras Puntos de Hazaña
	{ GreenBar, "../Sources/assets/botones/greenBar.png"},
	{ BlueBar, "../Sources/assets/botones/blueBar.png"},
	{ YellowBar, "../Sources/assets/botones/yellowBar.png"},
	{ RedBar, "../Sources/assets/botones/redBar.png"},
	{ EmptyBar, "../Sources/assets/botones/emptyBar.png"},
	{ EquippedSkill, "../Sources/assets/botones/EquippedSkill.png"},

	//Skills
	{ SkillExplosionC, "../Sources/assets/skills/explosionHab.png"},
	{ SkillExplosionBN, "../Sources/assets/skills/explosionHabBN.png"},
	{ SkillGolpeFuerteC, "../Sources/assets/skills/golpeFuerteHab.png"},
	{ SkillGolpeFuerteBN, "../Sources/assets/skills/golpeFuerteHabBN.png"},
	{ SkillInvencibleC, "../Sources/assets/skills/invencibleHab.png"},
	{ SkillInvencibleBN, "../Sources/assets/skills/invencibleHabBN.png"},
	{ SkillLiberationC, "../Sources/assets/skills/liberacionHab.png"},
	{ SkillLiberationBN, "../Sources/assets/skills/liberacionHabBN.png"},
	{ SkillPerforanteC, "../Sources/assets/skills/perforanteHab.png"},
	{ SkillPerforanteBN, "../Sources/assets/skills/perforanteHabBN.png"},
	{ SkillRaudoC, "../Sources/assets/skills/raudoHab.png"},
	{ SkillRaudoBN, "../Sources/assets/skills/raudoHabBN.png"},
	{ SkillReboteC, "../Sources/assets/skills/reboteHab.png"},
	{ SkillReboteBN, "../Sources/assets/skills/reboteHabBN.png"},
	{ SkillTorbellinoC, "../Sources/assets/skills/torbellinoHab.png"},
	{ SkillTorbellinoBN, "../Sources/assets/skills/torbellinoHabBN.png"},
	{ MenuBackground, "../Sources/assets/interfaces/menuFondo.png" },
	{ PauseBackground, "../Sources/assets/interfaces/pauseFondo.png" },
	{ Controls, "../Sources/assets/interfaces/controles.png"},
	{ InventaryMenu, "../Sources/assets/interfaces/InventarioFondo.png" },
	{ SkillMenu, "../Sources/assets/interfaces/HabilidadesFondo.png" },
	{ StashMenu, "../Sources/assets/interfaces/AlijoFondo.png"},
	{ Scene1, "../Sources/assets/interfaces/Scene1.png"},
	{ Scene2, "../Sources/assets/interfaces/Scene2.png"},
	{ Scene3, "../Sources/assets/interfaces/Scene3.png"},
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

	//Sprites
	{ Dragon,"../Sources/assets/enemigos/dragon.png"},
	{ PlayerFront, "../Sources/assets/player/frontal.png"},
	{ CrabAttack, "../Sources/assets/enemigos/crab/crab_attack.png" },
	{ MonkeyFront, "../Sources/assets/enemigos/monkey/monkeyFront.png" },
	{ WolfFront, "../Sources/assets/enemigos/wolf/wolf.png" },
	
	//Animaciones
	{ PlayerShootRightAnim, "../Sources/assets/player/animaciones/disparo/disparoDcha.png" },
	{ PlayerShootLeftAnim, "../Sources/assets/player/animaciones/disparo/disparoIz.png" },
	{ PlayerShootUpAnim, "../Sources/assets/player/animaciones/disparo/disparoTop.png" },
	{ PlayerShootDownAnim, "../Sources/assets/player/animaciones/disparo/disparoDown.png" },

	//Interactuables
	{ Wheel, "../Sources/assets/player/timon.png" },
	{ Stash, "../Sources/assets/colisionables/alijo.png" },
	{ ShipDoor, "../Sources/assets/colisionables/trampilla.png"},
	{ ExitShip, "../Sources/assets/colisionables/exitShip.png"},

	//Colisionable
	{ Rock, "../Sources/assets/colisionables/roca.png" },
	{ Coco ,"../Sources/assets/Colisionables/coco.png" },

	//Equipables
	{Gun1, "../Sources/assets/Equipamiento/pistola1.png"},
	{Gloves1, "../Sources/assets/Equipamiento/Gloves.png"},
};

vector<Resources::SoundInfo> Resources::soundRoutes{
	{ Agro ,"../Sources/assets/efectos_sonido/agro.mp3" },
	{ WolfHowl ,"../Sources/assets/efectos_sonido/wolf/wolfHowl.wav" },
	{ WolfAttack ,"../Sources/assets/efectos_sonido/wolf/wolfAttack.wav" },
	{ WolfDie ,"../Sources/assets/efectos_sonido/wolf/wolfDie.wav" }

	//Para añadir nueva ruta: {AudioId, "./Sources/audio/name.mp3/wav..."}
};

vector <Resources::MusicInfo> Resources::musicRoutes{
	{ MainTheme ,"../Sources/assets/music/mainTheme.mp3" },
	{ ShipSingers ,"../Sources/assets/music/ShipSingers.mp3" }


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
	{ InventoryMoneyText, "Dinero inventario:", SDL_Color({255,255,255,1}), RETRO },
	{ StashMoneyText, "Dinero alijo:",  SDL_Color({255,255,255,1}), RETRO },
	{ CreditsText,"Creditos", SDL_Color{(0,0,0,1)},RETRO },
	{ ResumeText,"Reanudar", SDL_Color{(0,0,0,1)},RETRO },
	{ MainMenuText,"Menu principal", SDL_Color{(0,0,0,1)},RETRO },
	{ CreditsText,"Créditos",SDL_Color{(0,0,0,1)},RETRO },
	{ SkillText,"SkillMenu",SDL_Color{(0,0,0,1)},RETRO },
};

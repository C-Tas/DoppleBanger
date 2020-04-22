#include "Resources.h"
#include "GameManager.h"

//Para añadir nueva ruta: {TextureId, "./Sources/images/name.png/jpg..."}
vector<Resources::ImageInfo> Resources::imageRoutes{
	//Botones
	{ MenuButton, "../Sources/assets/botones/botonMenu.png" },
	{ PlayButton, "../Sources/assets/botones/playButton.png" },
	{ ControlsButton, "../Sources/assets/botones/controlButton.png" },
	{ CreditsButton, "../Sources/assets/botones/creditosButton.png" },
	{ ExitButton, "../Sources/assets/botones/exitButton.png" },
	{ LoadButton, "../Sources/assets/botones/loadButton.png" },
	{ GoMainMenuButton, "../Sources/assets/botones/mainMenuButton.png" },
	{ ResumeButton, "../Sources/assets/botones/resumeButton.png" },
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
	{ BackButton, "../Sources/assets/botones/volver.png"},
	{ GoToSkillsAButton,"../Sources/assets/botones/Abrir_Habilidades_01.png"},
	{ GoToSkillsBButton,"../Sources/assets/botones/Abrir_Habilidades_02.png"},
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

	//HUD
	{ WheelHUD, "../Sources/assets/hud/timonHUD.png" },
	{ RopeHUD,	"../Sources/assets/hud/lazoHUD.png" },
	{ SkillsHUD, "../Sources/assets/hud/skillsHUD.png" },
	{ CooldownHUD, "../Sources/assets/hud/cooldownHUD.png" },
	{ LifeHUD, "../Sources/assets/hud/vida.png" },
	{ ExplosionIcon, "../Sources/assets/hud/iconos/explosion.png" },
	{ GolpeFuerteIcon, "../Sources/assets/hud/iconos/golpeFuerte.png" },
	{ InvencibleIcon, "../Sources/assets/hud/iconos/invencible.png" },
	{ LiberacionIcon, "../Sources/assets/hud/iconos/liberacion.png" },
	{ PerforanteIcon, "../Sources/assets/hud/iconos/perforante.png" },
	{ RaudoIcon, "../Sources/assets/hud/iconos/raudo.png" },
	{ ReboteIcon, "../Sources/assets/hud/iconos/rebote.png" },
	{ TorbellinoIcon, "../Sources/assets/hud/iconos/torbellino.png" },

	//Objects
	{ HealthPot, "../Sources/assets/hud/iconos/vidaPot.png" },
	{ ManaPot, "../Sources/assets/hud/iconos/manaPot.png" },
	{ SpeedPot, "../Sources/assets/hud/iconos/speedPot.png" },
	{ ArmorPot, "../Sources/assets/hud/iconos/armorPot.png" },
	{ DmgPot, "../Sources/assets/hud/iconos/dmgPot.png" },
	{ CritPot, "../Sources/assets/hud/iconos/critPot.png" },

	//Sprites
	{ Dragon,"../Sources/assets/enemigos/dragon.png"},
	{ PlayerFront, "../Sources/assets/player/frontal.png"},
	{ CrabAttack, "../Sources/assets/enemigos/crab/crab_attack.png" },
	{ MonkeyFront, "../Sources/assets/enemigos/monkey/monkeyFront.png" },
	{ WolfFront, "../Sources/assets/enemigos/wolf/wolf.png" },
	{ Kraken, "../Sources/assets/enemigos/kraken/kraken.png" },
	{ Magordito, "../Sources/assets/enemigos/magordito/Magordito.png" },
	{ Rojo, "../Sources/assets/enemigos/rojo.png" },
	{ Azul, "../Sources/assets/enemigos/azul.png" },
	{ Cleon, "../Sources/assets/enemigos/cleon/cleon.png" },
	{ Cooker, "../Sources/assets/npc/cookerIdle.png" },
	{ SkeletonMusician, "../Sources/assets/npc/EsqueletoMusico.png" },

	
	//Animaciones
	{ PlayerIdleRightAnim, "../Sources/assets/player/animaciones/idle/idleDcha.png" },
	{ PlayerIdleLeftAnim, "../Sources/assets/player/animaciones/idle/idleIz.png" },
	{ PlayerIdleUpAnim, "../Sources/assets/player/animaciones/idle/idleTop.png" },
	{ PlayerIdleDownAnim, "../Sources/assets/player/animaciones/idle/idleDown.png" },
	{ PlayerMoveRightAnim, "../Sources/assets/player/animaciones/movimiento/movimientoDcha.png" },
	{ PlayerMoveLeftAnim, "../Sources/assets/player/animaciones/movimiento/movimientoIz.png" },
	{ PlayerMoveUpAnim, "../Sources/assets/player/animaciones/movimiento/movimientoTop.png" },
	{ PlayerMoveDownAnim, "../Sources/assets/player/animaciones/movimiento/movimientoDown.png" },
	{ PlayerShootRightAnim, "../Sources/assets/player/animaciones/disparo/disparoDcha.png" },
	{ PlayerShootLeftAnim, "../Sources/assets/player/animaciones/disparo/disparoIz.png" },
	{ PlayerShootUpAnim, "../Sources/assets/player/animaciones/disparo/disparoTop.png" },
	{ PlayerShootDownAnim, "../Sources/assets/player/animaciones/disparo/disparoDown.png" },
	{ PlayerMeleeRightAnim, "../Sources/assets/player/animaciones/melee/meleeDcha.png" },
	{ PlayerMeleeLeftAnim, "../Sources/assets/player/animaciones/melee/meleeIz.png" },
	{ PlayerMeleeUpAnim, "../Sources/assets/player/animaciones/melee/meleeTop.png" },
	{ PlayerMeleeDownAnim, "../Sources/assets/player/animaciones/melee/meleeDown.png" },

	//Interactuables
	{ Wheel, "../Sources/assets/player/timon.png" },
	{ Stash, "../Sources/assets/colisionables/alijo.png" },
	{ ShipDoor, "../Sources/assets/colisionables/trampilla.png" },
	{ ExitShip, "../Sources/assets/colisionables/exitShip.png" },
	{ Chest, "../Sources/assets/colisionables/cofre.png" },

	//Colisionable
	{ Rock, "../Sources/assets/colisionables/roca.png" },
	{ Coco ,"../Sources/assets/Colisionables/coco.png" },

	//Equipables
	{Gun1, "../Sources/assets/Equipamiento/pistola1.png"},
	{Gloves1, "../Sources/assets/Equipamiento/Gloves.png"},
	{Boots1, "../Sources/assets/Equipamiento/botas.png"},
	{Gloves2, "../Sources/assets/Equipamiento/Guantes2.png"},
	{Armor1,"../Sources/assets/Equipamiento/Armadura1.png" }
};

vector<Resources::SoundInfo> Resources::soundRoutes{
	{ Agro ,"../Sources/assets/efectos_sonido/agro.mp3" },
	{ WolfHowl ,"../Sources/assets/efectos_sonido/wolf/wolfHowl.wav" },
	{ WolfAttack ,"../Sources/assets/efectos_sonido/wolf/wolfAttack.wav" },
	{ WolfDie ,"../Sources/assets/efectos_sonido/wolf/wolfDie.wav" },
	{Shout, "../Sources/assets/efectos_sonido/temparr.wav"}

	//Para añadir nueva ruta: {AudioId, "./Sources/audio/name.mp3/wav..."}
};

vector <Resources::MusicInfo> Resources::musicRoutes{
	{ MainTheme ,"../Sources/assets/music/mainTheme.mp3" },
	{ ShipSingers ,"../Sources/assets/music/ShipSingers.mp3" }


	//Para añadir nueva ruta: {AudioId, "./Sources/audio/name.mp3/wav..."}
};

vector <Resources::FontInfo> Resources::fontsRoutes{
	{ RETRO, "../Sources/fonts/RetroGaming.ttf", GameManager::instance()->getFontSize() },
	{ RETROSM, "../Sources/fonts/RetroGaming.ttf", GameManager::instance()->getFontSize() / 2 }
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

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
	{ GoToShopButton, "../Sources/assets/botones/botonTienda.png"},
	{ SaveGame1, "../Sources/assets/botones/saveGame1.png"},
	{ SaveGame2, "../Sources/assets/botones/saveGame2.png"},
	{ SaveGame3, "../Sources/assets/botones/saveGame3.png"},
	{ LoadGame1, "../Sources/assets/botones/loadGame1.png"},
	{ LoadGame2, "../Sources/assets/botones/loadGame2.png"},
	{ LoadGame3, "../Sources/assets/botones/loadGame3.png"},
	{ LoadGameNull, "../Sources/assets/botones/loadGameNull.png"},
	{ LoadButtonNull, "../Sources/assets/botones/loadButtonNull.png"},
	//Animaciones de botones
	{ BeerAnim, "../Sources/assets/botones/beerAnim.png"},

	//Interfaces
	{ BackButton, "../Sources/assets/botones/volver.png"},
	{ GoToSkillsAButton,"../Sources/assets/botones/Abrir_Habilidades_01.png"},
	{ GoToSkillsBButton,"../Sources/assets/botones/Abrir_Habilidades_02.png"},
	{ ButtonX, "../Sources/assets/botones/botonX.png"},
	{ ButtonUpgradeGreen, "../Sources/assets/botones/UpgradeButtonGreen.png"},
	{ ButtonUpgradeRed, "../Sources/assets/botones/UpgradeButtonRed.png"},
	{ ButtonUpgradeBlue, "../Sources/assets/botones/UpgradeButtonBlue.png"},
	{ ButtonUpgradeYellow, "../Sources/assets/botones/UpgradeButtonYellow.png"},

	//Punteros
	{ MovementPointer, "../Sources/assets/punteros/punteroMov.png"},
	{ AttackPointer, "../Sources/assets/punteros/punteroAtaque.png"},
	{ GrabPointer, "../Sources/assets/punteros/punteroMano.png"},
	
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
	{ SkillRaudoBN, "../Sources/assets/skills/raudoHabBN.png" },
	{ SkillReboteC, "../Sources/assets/skills/reboteHab.png" },
	{ SkillReboteBN, "../Sources/assets/skills/reboteHabBN.png" },
	{ SkillTorbellinoC, "../Sources/assets/skills/torbellinoHab.png" },
	{ SkillTorbellinoBN, "../Sources/assets/skills/torbellinoHabBN.png" },

	//Interfaces
	{ MenuBackground, "../Sources/assets/interfaces/menuFondo.png" },
	{ PauseBackground, "../Sources/assets/interfaces/pauseFondo.png" },
	{ SaveLoadBackground, "../Sources/assets/interfaces/saveLoadBg.png" },
	{ Controls, "../Sources/assets/interfaces/controles.png"},
	{ InventoryMenu, "../Sources/assets/interfaces/InventarioFondo.png" },
	{ SkillMenu, "../Sources/assets/interfaces/HabilidadesFondo.png" },
	{ StashMenu, "../Sources/assets/interfaces/AlijoFondo.png"},
	{ ShopMenu, "../Sources/assets/interfaces/TiendaFondo.png"},
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
	{ PotionBG, "../Sources/assets/hud/potionBGF.png" },

		//Sprites
	{ Dragon,"../Sources/assets/enemigos/dragon.png" },
	{ PlayerFront, "../Sources/assets/player/frontal.png" },
	{ CrabAttack, "../Sources/assets/enemigos/crab/crab_attack.png" },
	{ MonkeyFront, "../Sources/assets/enemigos/monkey/monkeyFront.png" },
	{ WolfFront, "../Sources/assets/enemigos/wolf/wolf.png" },
	{ Kraken, "../Sources/assets/enemigos/kraken/kraken.png" },
	{ Magordito, "../Sources/assets/enemigos/magordito/Magordito.png" },
	{ Rojo, "../Sources/assets/enemigos/rojo.png" },
	{ Azul, "../Sources/assets/enemigos/azul.png" },
	{ Cleon, "../Sources/assets/enemigos/cleon/cleon.png" },
	{ Cooker, "../Sources/assets/npc/cookerIdle.png" },
	{ Merchant, "../Sources/assets/npc/mercaderIdle.png" },
	{ SkeletonMusician, "../Sources/assets/npc/EsqueletoMusico.png" },
	{ Cartographer, "../Sources/assets/npc/Navigator.png" },
	{Skeleton, "../Sources/assets/enemigos/skeleton/skeleton.png"},

	
	//Animaciones
	//Player
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
	{ ClonSelfDestructionRightAnim, "../Sources/assets/clon/autodestruccion/ClonRightExplosion.png" },
	{ ClonSelfDestructionLeftAnim, "../Sources/assets/clon/autodestruccion/ClonLeftExplosion.png" },
	{ ClonSelfDestructionUpAnim, "../Sources/assets/clon/autodestruccion/ClonBackExplosion.png" },
	{ ClonSelfDestructionDownAnim, "../Sources/assets/clon/autodestruccion/ClonFrontExplosion.png" },
	{ ClonShootRightAnim, "../Sources/assets/clon/disparo/ClonRightShooting.png" },
	{ ClonShootLeftAnim, "../Sources/assets/clon/disparo/ClonLeftShooting.png" },
	{ ClonShootUpAnim, "../Sources/assets/clon/disparo/ClonBackShooting.png" },
	{ ClonShootDownAnim, "../Sources/assets/clon/disparo/ClonFrontShooting.png" },
	{ ClonIdleRightAnim, "../Sources/assets/clon/idle/ClonRightIdle.png" },
    { ClonIdleLeftAnim, "../Sources/assets/clon/idle/ClonLeftIdle.png" },
    { ClonIdleUpAnim, "../Sources/assets/clon/idle/ClonBackIdle.png" },
    { ClonIdleDownAnim, "../Sources/assets/clon/idle/ClonFrontIdle.png" },
	{ ClonMeleeRightAnim, "../Sources/assets/clon/melee/ClonRightMelee.png" },
	{ ClonMeleeLeftAnim, "../Sources/assets/clon/melee/ClonLeftMelee.png" },
	{ ClonMeleeUpAnim, "../Sources/assets/clon/melee/ClonBackMelee.png" },
	{ ClonMeleeDownAnim, "../Sources/assets/clon/melee/ClonFrontMelee.png" },
	//Pumpkin
		//Idle
	{ PumpkinIdleRightAnim, "../Sources/assets/enemigos/pumpkin/Idle/calabazaIdleDer.png" },
	{ PumpkinIdleLeftAnim, "../Sources/assets/enemigos/pumpkin/Idle/calabazaIdleIzq.png" },
	{ PumpkinIdleUpAnim, "../Sources/assets/enemigos/pumpkin/Idle/calabazaIdleAtras.png" },
	{ PumpkinIdleDownAnim, "../Sources/assets/enemigos/pumpkin/Idle/calabazaIdleDelante.png" },
		//Explosion
	{ PumpkinExpRightAnim, "../Sources/assets/enemigos/pumpkin/Explosion/calabazaExplDer.png" },
	{ PumpkinExpLeftAnim, "../Sources/assets/enemigos/pumpkin/Explosion/calabazaExplIzq.png" },
	{ PumpkinExpUpAnim, "../Sources/assets/enemigos/pumpkin/Explosion/calabazaExplAtras.png" },
	{ PumpkinExpDownAnim, "../Sources/assets/enemigos/pumpkin/Explosion/calabazaExplDelante.png" },
		//Attack
	{ PumpkinAttackRightAnim, "../Sources/assets/enemigos/pumpkin/Attack/calabazaDispDer.png" },
	{ PumpkinAttackLeftAnim, "../Sources/assets/enemigos/pumpkin/Attack/calabazaDispIzq.png" },
	{ PumpkinAttackUpAnim, "../Sources/assets/enemigos/pumpkin/Attack/calabazaDispAtras.png" },
	{ PumpkinAttackDownAnim, "../Sources/assets/enemigos/pumpkin/Attack/calabazaDispDelante.png" },
		//Move
	{ PumpkinMoveRightAnim, "../Sources/assets/enemigos/pumpkin/Move/calabazaMovDer.png" },
	{ PumpkinMoveLeftAnim, "../Sources/assets/enemigos/pumpkin/Move/calabazaMovIzq.png" },
	{ PumpkinMoveUpAnim, "../Sources/assets/enemigos/pumpkin/Move/calabazaMovAtras.png" },
	{ PumpkinMoveDownAnim, "../Sources/assets/enemigos/pumpkin/Move/calabazaMovDelante.png" },
	{ MonkeyIdleRightAnim, "../Sources/assets/enemigos/monkey/idleDchaDown.png" },
	{ MonkeyIdleLeftAnim, "../Sources/assets/enemigos/monkey/idleIzTop.png" },
	{ MonkeyIdleUpAnim, "../Sources/assets/enemigos/monkey/idleDchaTop.png" },
	{ MonkeyIdleDownAnim, "../Sources/assets/enemigos/monkey/idleIzDown.png" },
	{ MonkeyShootRightAnim, "../Sources/assets/enemigos/monkey/shootDchaDown.png" },
	{ MonkeyShootLeftAnim, "../Sources/assets/enemigos/monkey/shootIzTop.png" },
	{ MonkeyShootUpAnim, "../Sources/assets/enemigos/monkey/shootDchaTop.png" },
	{ MonkeyShootDownAnim, "../Sources/assets/enemigos/monkey/shootIzDown.png" },

	//Magordito
		//Kirin
	{ Kirin, "../Sources/assets/enemigos/magordito/Kirin.png" },
		//Skeleton
	{ SkeletonIdleRightAnim, "../Sources/assets/enemigos/skeleton/IdleLadoDer.png" },
	{ SkeletonIdleLeftAnim, "../Sources/assets/enemigos/skeleton/IdleLadoIzq.png" },
	{ SkeletonIdleUpAnim, "../Sources/assets/enemigos/skeleton/IdleEspaldas.png" },
	{ SkeletonIdleDownAnim, "../Sources/assets/enemigos/skeleton/IdleFrente.png" },
	{ SkeletonAttackRightAnim, "../Sources/assets/enemigos/skeleton/ThrowingLadoDer.png" },
	{ SkeletonAttackLeftAnim, "../Sources/assets/enemigos/skeleton/ThrowingLadoIzq.png" },
	{ SkeletonAttackUpAnim, "../Sources/assets/enemigos/skeleton/ThrowingEspaldas.png" },
	{ SkeletonAttackDownAnim, "../Sources/assets/enemigos/skeleton/ThrowingFrente.png" },
	{ SkeletonMoveRightAnim, "../Sources/assets/enemigos/skeleton/MovementLadoDer.png" },
	{ SkeletonMoveLeftAnim, "../Sources/assets/enemigos/skeleton/MovementLadoIzq.png" },
	{ SkeletonMoveDownAnim, "../Sources/assets/enemigos/skeleton/MovementFrente.png" },
	{ SkeletonMoveUpAnim, "../Sources/assets/enemigos/skeleton/MovementEspaldas.png" },
		//Interactuables
	{ Wheel, "../Sources/assets/player/timon.png" },
	{ Stash, "../Sources/assets/colisionables/alijo.png" },
	{ ShipDoor, "../Sources/assets/colisionables/trampilla.png" },
	{ ExitShip, "../Sources/assets/colisionables/exitShip.png" },
	{ Chest, "../Sources/assets/colisionables/cofreAnim.png" },
	{ Bullet, "../Sources/assets/colisionables/bullet.png" },

		//Colisionable
	{ Rock, "../Sources/assets/colisionables/roca.png" },
	{ Coco ,"../Sources/assets/Colisionables/coco.png" },
	{ Bone, "../Sources/assets/enemigos/skeleton/ThrowingBone.png" },

	//Equipables
	{ Armor1,"../Sources/assets/Equipamiento/armadura1.png" },
	{ Armor2,"../Sources/assets/Equipamiento/armadura2.png" },
	{ Gloves1, "../Sources/assets/Equipamiento/guantes1.png"},
	{ Gloves2, "../Sources/assets/Equipamiento/guantes2.png"},
	{ Boots1, "../Sources/assets/Equipamiento/botas.png"},
	{ Boots2, "../Sources/assets/Equipamiento/zapatos.png" },
	{ Sword1, "../Sources/assets/Equipamiento/espada1.png" },
	{ Sword2, "../Sources/assets/Equipamiento/espada2.png" },
	{ Saber1, "../Sources/assets/Equipamiento/sable1.png" },
	{ Saber2, "../Sources/assets/Equipamiento/sable2.png" },
	{ Gun1, "../Sources/assets/Equipamiento/pistola1.png"},
	{ Gun2, "../Sources/assets/Equipamiento/pistola2.png" },
	{ ShotGun1, "../Sources/assets/Equipamiento/trabuco1.png" },
	{ ShotGun2, "../Sources/assets/Equipamiento/trabuco2.png" },

	//Tilesets de los mapas
	{Tileset1, "../Sources/assets/mapas/Isla1-1/tileset_v2.png"},
	{CollisionTile, "../Sources/assets/mapas/barco/CollisionTile.png"}
};

vector<Resources::SoundInfo> Resources::soundRoutes{
	{ Agro ,"../Sources/assets/efectos_sonido/agro.mp3" },
	{ WolfHowl ,"../Sources/assets/efectos_sonido/wolf/wolfHowl.wav" },
	{ WolfAttack ,"../Sources/assets/efectos_sonido/wolf/wolfAttack.wav" },
	{ WolfDie ,"../Sources/assets/efectos_sonido/wolf/wolfDie.wav" },
	{ MonkeyIdle ,"../Sources/assets/efectos_sonido/monkey/monoIdle.wav" },
	{ MonkeyAttack ,"../Sources/assets/efectos_sonido/monkey/monoAttack.wav" },
	{ MonkeyShoot ,"../Sources/assets/efectos_sonido/monkey/monoShoot.wav" },
	{ MonkeyDie ,"../Sources/assets/efectos_sonido/monkey/monoDie.ogg" },

	//Player
	{ Walk	  ,"../Sources/assets/efectos_sonido/player/walk.wav" },
	{ Attack1 ,"../Sources/assets/efectos_sonido/player/attack1.wav" },
	{ Attack2 ,"../Sources/assets/efectos_sonido/player/attack2.wav" },
	{ Attack3 ,"../Sources/assets/efectos_sonido/player/attack3.wav" },
	{ Attack4 ,"../Sources/assets/efectos_sonido/player/attack4.wav" },
	{ Attack5 ,"../Sources/assets/efectos_sonido/player/attack5.wav" },
	{ Attack6 ,"../Sources/assets/efectos_sonido/player/attack6.wav" },
	{ Dying   ,"../Sources/assets/efectos_sonido/player/dying.wav" },
	{ Laugh1   ,"../Sources/assets/efectos_sonido/player/laugh1.mp3" },
	{ Laugh2   ,"../Sources/assets/efectos_sonido/player/laugh2.mp3" },
	{ Laugh3   ,"../Sources/assets/efectos_sonido/player/laugh3.mp3" },
	{ Laugh4   ,"../Sources/assets/efectos_sonido/player/laugh4.mp3" },
	{ Laugh5   ,"../Sources/assets/efectos_sonido/player/laugh5.mp3" },
	{ Laugh6   ,"../Sources/assets/efectos_sonido/player/laugh6.mp3" },
	{ Laugh7   ,"../Sources/assets/efectos_sonido/player/laugh7.mp3" },
	{ Shout   ,"../Sources/assets/efectos_sonido/player/jar.mp3"},
	{ Drink   ,"../Sources/assets/efectos_sonido/player/drink.wav" },
	{ EmpoweredSkill   ,"../Sources/assets/efectos_sonido/player/EmpoweredSkill.wav"},
	{ PerforateSkill   ,"../Sources/assets/efectos_sonido/player/perforateSkill.wav"},
	{ Ricochet   ,"../Sources/assets/efectos_sonido/player/ricochet.wav"},
	{ WhirlwindSkill   ,"../Sources/assets/efectos_sonido/player/whirlwindSkill.wav"},
	{ Pistol   ,"../Sources/assets/efectos_sonido/player/pistol.wav"},
	{ Trabuco   ,"../Sources/assets/efectos_sonido/player/trabuco.wav"},
	{ SwordSound1   ,"../Sources/assets/efectos_sonido/player/sword1.flac"},
	{ SwordSound2  ,"../Sources/assets/efectos_sonido/player/sword2.flac"},
	{ SwordSound3  ,"../Sources/assets/efectos_sonido/player/sword3.wav"},
	{ SwordSound4  ,"../Sources/assets/efectos_sonido/player/sword4.aiff"},
	{ SwordSound5  ,"../Sources/assets/efectos_sonido/player/sword5.wav"},
	{ SwordSound6  ,"../Sources/assets/efectos_sonido/player/sword6.wav"},
	{ MeleeCrit  ,"../Sources/assets/efectos_sonido/player/meleeCrit.wav"},
	{ DistCrit  ,"../Sources/assets/efectos_sonido/player/distCrit.wav"},

	//Clon
	//{ Explosion   ,"../Sources/assets/efectos_sonido/clon/explosion.wav"},

	//Ship
	{ Waves ,"../Sources/assets/efectos_sonido/ship/waves.wav" },
	//Para añadir nueva ruta: {AudioId, "./Sources/audio/name.mp3/wav..."}

	//Calabaza
	{ AgroPumpkin ,"../Sources/assets/efectos_sonido/pumpkin/agro.mp3" },
	{ AttackPumpkin ,"../Sources/assets/efectos_sonido/pumpkin/attack.wav" },
	{ ExplosionPumpkin ,"../Sources/assets/efectos_sonido/pumpkin/explosion.wav" },
	{ IdlePumpkin1 ,"../Sources/assets/efectos_sonido/pumpkin/idle1.mp3" },
	{ IdlePumpkin2 ,"../Sources/assets/efectos_sonido/pumpkin/idle2.mp3" },
	{ LaughPumpkin1 ,"../Sources/assets/efectos_sonido/pumpkin/laugh1.ogg" },
	{ LaughPumpkin2 ,"../Sources/assets/efectos_sonido/pumpkin/laugh2.ogg" },
	{ LaughPumpkin3 ,"../Sources/assets/efectos_sonido/pumpkin/laugh3.ogg" },
	{ MovePumpkin ,"../Sources/assets/efectos_sonido/pumpkin/move.mp3" },
	{ TauntPumpkin1 ,"../Sources/assets/efectos_sonido/pumpkin/taunt.mp3" },
	{ TauntPumpkin2 ,"../Sources/assets/efectos_sonido/pumpkin/taunt1.mp3" }
};

vector <Resources::MusicInfo> Resources::musicRoutes{
	{ MainTheme ,"../Sources/assets/music/mainTheme.mp3" },
	{ ShipSingers ,"../Sources/assets/music/ShipSingers.mp3" },
	{ Caribbean ,"../Sources/assets/music/caribbean.mp3" }
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

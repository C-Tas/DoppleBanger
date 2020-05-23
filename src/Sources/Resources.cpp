#include "Resources.h"
#include "GameManager.h"

//Para añadir nueva ruta: {TextureId, "./Sources/images/name.png/jpg..."}
vector<Resources::ImageInfo> Resources::imageRoutes {
#pragma region Botones
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
	{ SkipStoryButton, "../Sources/assets/botones/skipStoryButton.png" },
	{ RestartGame, "../Sources/assets/botones/restartGame.png" },
	{ MuteSoundOff, "../Sources/assets/botones/muteSoundOff.png" },
	{ MuteSoundOn, "../Sources/assets/botones/muteSoundOn.png" },
	{ MuteMusicOff, "../Sources/assets/botones/muteMusicOff.png" },
	{ MuteMusicOn, "../Sources/assets/botones/muteMusicOn.png" },
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
	{ BackToShipButton, "../Sources/assets/botones/backToShipButton.png"},
	{ YesButton, "../Sources/assets/botones/yesButton.png"},
	{ NoButton, "../Sources/assets/botones/noButton.png"},
	{ GoToShipButton, "../Sources/assets/botones/goToShipButton.png"},
	{ GoToNextZoneButton, "../Sources/assets/botones/ContinueButton.png"},
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
	{ ButtonInitTutorial, "../Sources/assets/botones/botonEscucharVenancio.png"},
	{ ButtonSkipTutorial, "../Sources/assets/botones/botonPasarVenancio.png"},

	//Animaciones de botones
	{ BeerAnim, "../Sources/assets/botones/beerAnim.png"},
#pragma endregion

#pragma region Interfaces y punteros
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
	{ Scene4, "../Sources/assets/interfaces/Scene4.png"},
	{ Scene5, "../Sources/assets/interfaces/Scene5.png"},
	{ Scene6, "../Sources/assets/interfaces/Scene6.png"},
	{ Scene7, "../Sources/assets/interfaces/Scene7.png"},
	{ Scene8, "../Sources/assets/interfaces/Scene8.png"},
	{ Scene9, "../Sources/assets/interfaces/Scene9.png"},
	{ TextBox, "../Sources/assets/interfaces/textBoxBg.png" },
	{ Ship, "../Sources/assets/interfaces/barco.png" },
	{ Table, "../Sources/assets/interfaces/mesa.png" },
	{ Map1, "../Sources/assets/interfaces/mapa1.png" },
	{ Map2, "../Sources/assets/interfaces/mapa2.png" },
	{ Map3, "../Sources/assets/interfaces/mapa3.png" },
	{ GameOver1, "../Sources/assets/interfaces/endGame1.png" },
	{ GameOver2, "../Sources/assets/interfaces/endGame2.png" },
	{ Rain1, "../Sources/assets/interfaces/fondoLluvia0.png" },
	{ Rain2, "../Sources/assets/interfaces/fondoLluvia1.png" },
	{ Rain3, "../Sources/assets/interfaces/fondoLluvia2.png" },
	{ Rain4, "../Sources/assets/interfaces/fondoLluvia3.png" },
	{ Win, "../Sources/assets/interfaces/win.png" },

	//Punteros
	{ MovementPointer, "../Sources/assets/punteros/punteroMov.png"},
	{ AttackPointer, "../Sources/assets/punteros/punteroAtaque.png"},
	{ GrabPointer, "../Sources/assets/punteros/punteroMano.png"},
#pragma endregion

#pragma region HUD
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
#pragma endregion

#pragma region Inventario
	//Equipables
	{ Armor1,"../Sources/assets/Equipamiento/armadura1.png" },
	{ Armor2,"../Sources/assets/Equipamiento/armadura2.png" },
	{ Gloves1, "../Sources/assets/Equipamiento/guantes1.png" },
	{ Gloves2, "../Sources/assets/Equipamiento/guantes2.png" },
	{ Boots1, "../Sources/assets/Equipamiento/botas.png" },
	{ Boots2, "../Sources/assets/Equipamiento/zapatos.png" },
	{ Sword1, "../Sources/assets/Equipamiento/espada1.png" },
	{ Sword2, "../Sources/assets/Equipamiento/espada2.png" },
	{ Saber1, "../Sources/assets/Equipamiento/sable1.png" },
	{ Saber2, "../Sources/assets/Equipamiento/sable2.png" },
	{ Gun1, "../Sources/assets/Equipamiento/pistola1.png" },
	{ Gun2, "../Sources/assets/Equipamiento/pistola2.png" },
	{ ShotGun1, "../Sources/assets/Equipamiento/trabuco1.png" },
	{ ShotGun2, "../Sources/assets/Equipamiento/trabuco2.png" },
#pragma endregion

#pragma region Habilidades
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
#pragma endregion

#pragma region Sprites y animaciones
	//Sprites
	{ Dragon,"../Sources/assets/enemigos/dragon.png" },
	{ PlayerFront, "../Sources/assets/player/frontal.png" },
	{ MonkeyFront, "../Sources/assets/enemigos/monkey/monkeyFront.png" },
	{ WolfFront, "../Sources/assets/enemigos/wolf/wolf.png" },
	{ Kraken, "../Sources/assets/enemigos/kraken/kraken.png" },
	{ Rojo, "../Sources/assets/enemigos/rojo.png" },
	{ Azul, "../Sources/assets/enemigos/azul.png" },
	{ Cleon, "../Sources/assets/enemigos/cleon/cleon.png" },
	{ VenancioDrink, "../Sources/assets/npc/venancioDrink.png" },
	{ VenancioPushStart, "../Sources/assets/npc/venancioPushStart.png" },
	{ VenancioPushBucle, "../Sources/assets/npc/venancioPushBucle.png" },
	{ VenancioPushFinish, "../Sources/assets/npc/venancioPushFinish.png" },
	{ Merchant, "../Sources/assets/npc/mercaderIdle.png" },
	{ Cooker, "../Sources/assets/npc/cookerIdle.png" },
	{ SkeletonMusician, "../Sources/assets/npc/EsqueletoMusico.png" },
	{ Cartographer, "../Sources/assets/npc/idleCartografa.png" },
	{ Morty, "../Sources/assets/npc/idleMorty.png" },
	{ VenancioFuneral, "../Sources/assets/npc/venancioFuneral.png" },
	{ MerchantFuneral, "../Sources/assets/npc/mercaderFuneral.png" },
	{ CookerFuneral, "../Sources/assets/npc/cookerFuneral.png" },
	{ MortyFuneral, "../Sources/assets/npc/mortyFuneral.png" },
	{ CartographerFuneral, "../Sources/assets/npc/cartografaFuneral.png" },

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
	{ PlayerEmpoweredRight, "../Sources/assets/player/animaciones/golpeFuerte/golpeRight.png" },
	{ PlayerEmpoweredLeft, "../Sources/assets/player/animaciones/golpeFuerte/golpeLeft.png" },
	{ PlayerEmpoweredUp, "../Sources/assets/player/animaciones/golpeFuerte/golpeUp.png" },
	{ PlayerEmpoweredDown, "../Sources/assets/player/animaciones/golpeFuerte/golpeDown.png" },
	//Clon
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
	{ ClonVanishRightAnim ,"../Sources/assets/clon/desaparecer/vanishDer.png" },
	{ ClonVanishLeftAnim, "../Sources/assets/clon/desaparecer/vanishLeft.png" },
	{ ClonVanishDownAnim, "../Sources/assets/clon/desaparecer/vanishDown.png" },
	{ ClonVanishUpAnim, "../Sources/assets/clon/desaparecer/vanishTop.png" },
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
//crab
     {CrabAttack,"../Sources/assets/enemigos/crab/crabAttack.png" },
     {CrabWalk,"../Sources/assets/enemigos/crab/crabWalk.png"},
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
		//Skeleton
	{ SkeletonIdleRightAnim, "../Sources/assets/enemigos/skeleton/IdleLadoDer.png" },
	{ SkeletonIdleLeftAnim, "../Sources/assets/enemigos/skeleton/IdleLadoIzq.png" },
	{ SkeletonIdleUpAnim, "../Sources/assets/enemigos/skeleton/IdleEspaldas.png" },
	{ SkeletonIdleDownAnim, "../Sources/assets/enemigos/skeleton/IdleFrente.png" },
	{ SkeletonAttackRightAnim, "../Sources/assets/enemigos/skeleton/disparoDer.png" },
	{ SkeletonAttackLeftAnim, "../Sources/assets/enemigos/skeleton/disparoIz.png" },
	{ SkeletonAttackUpAnim, "../Sources/assets/enemigos/skeleton/disparoTop.png" },
	{ SkeletonAttackDownAnim, "../Sources/assets/enemigos/skeleton/disparoDown.png" },
	{ SkeletonMoveRightAnim, "../Sources/assets/enemigos/skeleton/MovementLadoDer.png" },
	{ SkeletonMoveLeftAnim, "../Sources/assets/enemigos/skeleton/MovementLadoIzq.png" },
	{ SkeletonMoveDownAnim, "../Sources/assets/enemigos/skeleton/MovementFrente.png" },
	{ SkeletonMoveUpAnim, "../Sources/assets/enemigos/skeleton/MovementEspaldas.png" },
		//Interactuables
	{ Altar, "../Sources/assets/enemigos/magordito/altar.png" },
		//Idle
	{ MagorditoIdleRight, "../Sources/assets/enemigos/magordito/idle/idleDcha.png" },
	{ MagorditoIdleLeft, "../Sources/assets/enemigos/magordito/idle/idleIz.png" },
	{ MagorditoIdleTopRight, "../Sources/assets/enemigos/magordito/idle/idleTopDcha.png" },
	{ MagorditoIdleTopLeft, "../Sources/assets/enemigos/magordito/idle/idleTopIz.png" },
	//Disparo
	//{ MagorditoShootRight, "../Sources/assets/enemigos/magordito/disparo/disparoDcha.png" },
	//{ MagorditoShootLeft, "../Sources/assets/enemigos/magordito/disparo/disparoIz.png" },
	//{ MagorditoShootDown, "../Sources/assets/enemigos/magordito/disparo/disparoDown.png" },
	//{ MagorditoShootTopRight, "../Sources/assets/enemigos/magordito/disparo/disparoTopDcha.png" },
	//{ MagorditoShootTopLeft, "../Sources/assets/enemigos/magordito/disparo/disparoTopIz.png" },
	//Viaje
	{ MagorditoTpRight, "../Sources/assets/enemigos/magordito/viaje/viajeDcha.png" },
	{ MagorditoTpLeft, "../Sources/assets/enemigos/magordito/viaje/viajeIz.png" },
	{ MagorditoTpTopRight, "../Sources/assets/enemigos/magordito/viaje/viajeTopDer.png" },
	{ MagorditoTpTopLeft, "../Sources/assets/enemigos/magordito/viaje/viajeTopIz.png" },
	//Kirin
	{ MagorditoKirinRight, "../Sources/assets/enemigos/magordito/kirin/kirinDcha.png" },
	{ MagorditoKirinLeft, "../Sources/assets/enemigos/magordito/kirin/kirinIz.png" },
	{ MagorditoKirinTopRight, "../Sources/assets/enemigos/magordito/kirin/kirinTopDcha.png" },
	{ MagorditoKirinTopLeft, "../Sources/assets/enemigos/magordito/kirin/kirinTopIz.png" },
	{ Kirin, "../Sources/assets/enemigos/magordito/kirin/rayo.png" },

#pragma region Barco
	//Interactuables
	{ Wheel, "../Sources/assets/player/timon.png" },
	{ Stash, "../Sources/assets/colisionables/alijo.png" },
	{ ShipDoor, "../Sources/assets/colisionables/trampilla.png" },
	{ ExitShip, "../Sources/assets/colisionables/exitShip.png" },
	{ Chest, "../Sources/assets/colisionables/cofreAnim.png" },
	{ Bullet, "../Sources/assets/colisionables/bullet.png" },

	//Tutorial
	{ Bottle ,"../Sources/assets/Colisionables/botella.png" },
	{ Dummy ,"../Sources/assets/Colisionables/dummyTutorial.png" },
#pragma endregion

#pragma region Colisionables y mapas
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
	{ Sword1H, "../Sources/assets/Equipamiento/espada1H.png" },
	{ Sword2H, "../Sources/assets/Equipamiento/espada2H.png" },
	{ Saber1, "../Sources/assets/Equipamiento/sable1.png" },
	{ Saber2, "../Sources/assets/Equipamiento/sable2.png" },
	{ Saber1H, "../Sources/assets/Equipamiento/sable1H.png" },
	{ Saber2H, "../Sources/assets/Equipamiento/sable2H.png" },
	{ Gun1, "../Sources/assets/Equipamiento/pistola1.png"},
	{ Gun2, "../Sources/assets/Equipamiento/pistola2.png" },
	{ ShotGun1, "../Sources/assets/Equipamiento/trabuco1.png" },
	{ ShotGun2, "../Sources/assets/Equipamiento/trabuco2.png" },

	//Tilesets de los mapas
	{ Tileset1, "../Sources/assets/mapas/Isla1-1/tileset_v2.png" },
	{ CollisionTile, "../Sources/assets/mapas/barco/CollisionTile.png" }

#pragma endregion
};

//Para añadir nueva ruta: {AudioId, "./Sources/audio/name.mp3/wav..."}
vector<Resources::AudioInfo> Resources::audioRoutes{
	//Musica principal
#pragma region MainMusic
	{ WavesSound ,"../Sources/assets/music/background/shipMusic.wav" },
	{ MainTheme ,"../Sources/assets/music/background/menuMusic.mp3" },
	{ Caribbean ,"../Sources/assets/music/caribbean.mp3" },
	{ Shop ,"../Sources/assets/music/background/shopMusic.mp3" },
	{ Storyboard ,"../Sources/assets/music/background/storyboardMusic.mp3" },
	{ FuneralTheme ,"../Sources/assets/music/funeralTheme.mp3" },

#pragma region
	//Player
#pragma region PlayerSounds
	{ WalkAudio	  ,"../Sources/assets/efectos_sonido/player/walk.wav" },
	{ Attack1 ,"../Sources/assets/efectos_sonido/player/attack1.wav" },
	{ Attack2 ,"../Sources/assets/efectos_sonido/player/attack2.wav" },
	{ Attack3 ,"../Sources/assets/efectos_sonido/player/attack3.wav" },
	{ Attack4 ,"../Sources/assets/efectos_sonido/player/attack4.wav" },
	{ Attack5 ,"../Sources/assets/efectos_sonido/player/attack5.wav" },
	{ Attack6 ,"../Sources/assets/efectos_sonido/player/attack6.wav" },
	{ DyingAudio   ,"../Sources/assets/efectos_sonido/player/dying.wav" },
	{ Laugh1   ,"../Sources/assets/efectos_sonido/player/laugh1.mp3" },
	{ Laugh2   ,"../Sources/assets/efectos_sonido/player/laugh2.mp3" },
	{ Laugh3   ,"../Sources/assets/efectos_sonido/player/laugh3.mp3" },
	{ Laugh4   ,"../Sources/assets/efectos_sonido/player/laugh4.mp3" },
	{ Laugh5   ,"../Sources/assets/efectos_sonido/player/laugh5.mp3" },
	{ Laugh6   ,"../Sources/assets/efectos_sonido/player/laugh6.mp3" },
	{ Laugh7   ,"../Sources/assets/efectos_sonido/player/laugh7.mp3" },
	{ Shout   ,"../Sources/assets/efectos_sonido/player/jar.mp3"},
	{ Drink   ,"../Sources/assets/efectos_sonido/player/drink.wav" },
	{ EmpoweredSkillAudio   ,"../Sources/assets/efectos_sonido/player/EmpoweredSkill.wav"},
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
	{ Hurt1  ,"../Sources/assets/efectos_sonido/player/hurt1.wav"},
	{ Hurt2  ,"../Sources/assets/efectos_sonido/player/hurt2.wav"},
	{ Hurt3  ,"../Sources/assets/efectos_sonido/player/hurt3.wav"},
	{ Hurt4  ,"../Sources/assets/efectos_sonido/player/hurt4.ogg"},

#pragma endregion
#pragma region ClonSounds
	//Clon
	//{ Explosion   ,"../Sources/assets/efectos_sonido/clon/explosion.wav"},
#pragma endregion

	//Lobo
#pragma region Wolf
	{ WolfHowlAudio ,"../Sources/assets/efectos_sonido/wolf/wolfHowl.wav" },
	{ WolfAttackAudio ,"../Sources/assets/efectos_sonido/wolf/wolfAttack.wav" },
	{ WolfDieAudio ,"../Sources/assets/efectos_sonido/wolf/wolfDie.wav" },
#pragma endregion
	//Mono
#pragma region Monkey
	{ MonkeyIdleSound ,"../Sources/assets/efectos_sonido/monkey/monoIdle.wav" },
	{ MonkeyAttackSound ,"../Sources/assets/efectos_sonido/monkey/monoAttack.wav" },
	{ MonkeyShootSound ,"../Sources/assets/efectos_sonido/monkey/monoShoot.wav" },
	{ MonkeyDieSound ,"../Sources/assets/efectos_sonido/monkey/monoDie.ogg" },
#pragma endregion
	//Esqueleto
#pragma region Skeleton
	{ SkeletonAttack ,"../Sources/assets/efectos_sonido/skeleton/attack.mp3" },
	{ SkeletonBoomerang ,"../Sources/assets/efectos_sonido/skeleton/boomerang.mp3" },
	{ SkeletonDeath ,"../Sources/assets/efectos_sonido/skeleton/death.mp3" },
	{ SkeletonHit1 ,"../Sources/assets/efectos_sonido/skeleton/hit1.mp3" },
	{ SkeletonHit2 ,"../Sources/assets/efectos_sonido/skeleton/hit2.mp3" },
	{ SkeletonHit3 ,"../Sources/assets/efectos_sonido/skeleton/hit3.mp3" },
	{ SkeletonIdle ,"../Sources/assets/efectos_sonido/skeleton/idle.mp3" },
#pragma endregion
	//Cangrejo
#pragma region Crab
	{ CrabAttackSound ,"../Sources/assets/efectos_sonido/crab/attack.mp3" },
	{ CrabDetection ,"../Sources/assets/efectos_sonido/crab/detection.mp3" },
	{ CrabIdle ,"../Sources/assets/efectos_sonido/crab/idle.mp3" },
#pragma endregion
	//Pirata
#pragma region Pirate
	{ PirateAttack ,"../Sources/assets/efectos_sonido/pirate/attack.mp3" },
	{ PirateShot ,"../Sources/assets/efectos_sonido/pirate/shot.mp3" },
	{ PirateDetection1 ,"../Sources/assets/efectos_sonido/pirate/detect1.mp3" },
	{ PirateDetection2 ,"../Sources/assets/efectos_sonido/pirate/detect2.mp3" },
	{ PirateIdle ,"../Sources/assets/efectos_sonido/pirate/idle.mp3" },
	{ PirateChase ,"../Sources/assets/efectos_sonido/pirate/chase.mp3" },
#pragma endregion
	//Calabaza
#pragma region Pumpkin
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
	{ TauntPumpkin2 ,"../Sources/assets/efectos_sonido/pumpkin/taunt1.mp3" },
#pragma endregion
	//Kraken
#pragma region Kraken
	{ KrakenIdle ,"../Sources/assets/efectos_sonido/kraken/idle.mp3" },
	{ KrakenInk ,"../Sources/assets/efectos_sonido/kraken/ink.wav" },
	{ KrakenSplash ,"../Sources/assets/efectos_sonido/kraken/splash.mp3" },
	{ KrakenDive ,"../Sources/assets/efectos_sonido/kraken/dive.mp3" },
	{ KrakenSurface ,"../Sources/assets/efectos_sonido/kraken/surface.mp3" },
	{ KrakenSlam1 ,"../Sources/assets/efectos_sonido/kraken/slam1.wav" },
	{ KrakenSlam2 ,"../Sources/assets/efectos_sonido/kraken/slam2.wav" },
	{ KrakenSweep1 ,"../Sources/assets/efectos_sonido/kraken/sweep1.wav" },
	{ KrakenSweep2 ,"../Sources/assets/efectos_sonido/kraken/sweep2.wav" },
	{ KrakenSweep3 ,"../Sources/assets/efectos_sonido/kraken/sweep3.wav" },
	{ KrakenDeath ,"../Sources/assets/efectos_sonido/kraken/death.wav" },
	{ KrakenMusic ,"../Sources/assets/efectos_sonido/kraken/music.wav" },
#pragma endregion

	//Magordito
	//{ IdleMagordito ,"../Sources/assets/efectos_sonido/Magordito/taunt1.mp3" },
	//{ MovementMagordito ,"../Sources/assets/efectos_sonido/Magordito/taunt1.mp3" },
	{ MagorditoDeath ,"../Sources/assets/efectos_sonido/Magordito/death.mp3" },
	{ MagorditoKirin ,"../Sources/assets/efectos_sonido/Magordito/kirin.wav" },
	{ MagorditoTeleport ,"../Sources/assets/efectos_sonido/Magordito/teleport.wav" },
	{ MagorditoResurrection ,"../Sources/assets/efectos_sonido/Magordito/resurrection.wav" },
	//{ ThemeMagordito ,"../Sources/assets/efectos_sonido/Magordito/taunt1.mp3" },
	{ Magorditolaugh1 ,"../Sources/assets/efectos_sonido/Magordito/laugh1.mp3" },
	{ Magorditolaugh2 ,"../Sources/assets/efectos_sonido/Magordito/laugh2.mp3" },
	{ Magorditolaugh3 ,"../Sources/assets/efectos_sonido/Magordito/laugh3.mp3" },
	{ Magorditolaugh4 ,"../Sources/assets/efectos_sonido/Magordito/laugh4.mp3" },
	{ MagorditoAttack1 ,"../Sources/assets/efectos_sonido/Magordito/attack1.mp3" },
	{ MagorditoAttack2 ,"../Sources/assets/efectos_sonido/Magordito/attack2.mp3" },
	{ MagorditoAttack3 ,"../Sources/assets/efectos_sonido/Magordito/attack3.mp3" },
	{ MagorditoAttack4 ,"../Sources/assets/efectos_sonido/Magordito/attack4.mp3" },
	{ MagorditoAttack5 ,"../Sources/assets/efectos_sonido/Magordito/attack5.mp3" },
	{ MagorditoAggro ,"../Sources/assets/efectos_sonido/Magordito/aggro.mp3" },

	//Tutorial
	{ Glass, "../Sources/assets/efectos_sonido/tutorial/glass.wav" },
	{ DummyDie, "../Sources/assets/efectos_sonido/tutorial/dummy.wav" },
	//NPC
	{ VenancioTalk, "../Sources/assets/efectos_sonido/tutorial/VenancioTalk.wav" },
	//Otros
	{ Agro ,"../Sources/assets/efectos_sonido/agro.mp3" },
	//inventario/tienda/alijo
	{ Pag, "../Sources/assets/efectos_sonido/inventario/page.wav" },
	{ Equip, "../Sources/assets/efectos_sonido/inventario/equip.wav" },
	{ Time, "../Sources/assets/efectos_sonido/inventario/timeBack.wav" },
	{ Gold, "../Sources/assets/efectos_sonido/inventario/gold.mp3" },
	//jarls
	{ jarl1 ,"../Sources/assets/efectos_sonido/jarl/jar1.wav" },
	{ jarl2 ,"../Sources/assets/efectos_sonido/jarl/jar2.wav" },
	{ jarl3 ,"../Sources/assets/efectos_sonido/jarl/jar3.wav" },
	{ jarl4 ,"../Sources/assets/efectos_sonido/jarl/jar4.wav" },
	{ jarl5 ,"../Sources/assets/efectos_sonido/jarl/jar5.wav" },
	{ jarl6 ,"../Sources/assets/efectos_sonido/jarl/jar6.wav" },
	{ jarl7 ,"../Sources/assets/efectos_sonido/jarl/jar7.wav" },
	{ jarl8 ,"../Sources/assets/efectos_sonido/jarl/jar8.wav" },
	{ jarl9 ,"../Sources/assets/efectos_sonido/jarl/jar9.wav" },
	{ jarl10 ,"../Sources/assets/efectos_sonido/jarl/jar10.wav" },
	{ jarl11 ,"../Sources/assets/efectos_sonido/jarl/jar11.wav" },
};

vector<Resources::AudioVolume> Resources::audioVolume{
	//Canal de musica
	{ MainMusicChannel, 7 },
	{ AuxMusicChannel1, 7 },
	{ AuxMusicChannel2, 7 },
	{ AuxMusicChannel3, 7 },

	//Canal de los botones
	{ BeerButtonChanel, 6 },

	//Canal del jugador
	{ PlayerChannel1, 10 },
	{ PlayerChannel2, 10 },
	{ PlayerChannel3, 10 },
	{ PlayerChannel4, 10 },

	//Canal del lobo
	{ WolfChannel, 6 },
	//Canal del mono
	{ MonkeyChannel, 6 },
	//Canal de la calabaza
	{ PumpkinChannel1, 6 },
	{ PumpkinChannel2, 6 },
	//Canal del esqueleto
	{ SkeletonChannel1, 40 },
	{ SkeletonChannel2, 40 },
	{ SkeletonChannel3, 40 },
	{ SkeletonChannel4, 6 },
	//Canal de la cangrejo
	{ CrabChannel1, 10 },
	{ CrabChannel2, 10 },
	//Canal del pirata
	{ PirateChannel1, 10 },
	{ PirateChannel2, 10 },
	{ PirateChannel3, 10 },
	//Canal de la kraken
	{ KrakenChannel1, 15 },
	{ KrakenChannel2, 20 },
	//canal de jarl
	{ JarlChannel, 6 },

	{ MagorditoChannel1, 6 },
	{ MagorditoChannel2, 6 },
	{ MagorditoChannel3, 6 }
};

vector <Resources::FontInfo> Resources::fontsRoutes{
	{ RETRO, "../Sources/fonts/RetroGaming.ttf", GameManager::instance()->getFontSize() },
	{ RETROSM, "../Sources/fonts/RetroGaming.ttf", GameManager::instance()->getFontSize()*3 / 4 }
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

map<char, string> Resources::tildes_{
	//o con tilde
	{
		'o', "\u00f3"
	},
	//a con tilde
	{
		'a', "\u00e1"
	},
	//i con tilde
	{
		'i', "\u00ed"
	},
	//u con tilde
	{
		'u', "\u00fa"
	},
	//e con tilde
	{
		'e', "\u00e9"
	},
	{
		'ñ', "\u00F1"
	},
	//interrogante español
	{ 
		'¿', "\u00BF" 
	},
	//exclamación española
	{
		'¡', "\u00A1"
	}
};

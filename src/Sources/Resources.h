#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include <map>

using namespace std;

class Resources
{
public:
	///<summary>Enum para las distintas imagenes del juego</summary>
	enum TextureId : int {
		//Botones
		MenuButton,
		PlayButton,
		ControlsButton,
		CreditsButton,
		ExitButton,
		LoadButton,
		GoMainMenuButton,
		ResumeButton,
		BackButton,
		SkipButton,
		SkipStoryButton,
		MuteSoundOff,
		MuteSoundOn,
		MuteMusicOff,
		MuteMusicOn,
		RestartGame,
		RightArrow,
		LeftArrow,
		EquippedButton,
		DeleteButton,
		ForwardArrow,
		BackwardsArrow,
		TrashButton,
		ChangeButton,
		MoneyButton,
		SkillText,
		ButtonX,
		ButtonUpgradeGreen,
		ButtonUpgradeRed,
		ButtonUpgradeBlue,
		ButtonUpgradeYellow,
		GoToInventoryAButton,
		GoToInventoryBButton,
		GoToSkillsAButton,
		GoToSkillsBButton,
		GoToShopButton,
		SaveGame1,
		SaveGame2,
		SaveGame3,
		LoadGame1,
		LoadGame2,
		LoadGame3,
		LoadGameNull,
		LoadButtonNull,
		ButtonInitTutorial,
		ButtonSkipTutorial,
		BackToShipButton,
		YesButton,
		NoButton,
		GoToShipButton,
		GoToNextZoneButton,
		//Animaciones de botones
		BeerAnim,

		//Punteros
		MovementPointer,
		AttackPointer,
		GrabPointer,

		//BarrasPuntosHazaña
		Controls,
		GreenBar,
		BlueBar,
		YellowBar,
		RedBar,
		EmptyBar,
		EquippedSkill,

		//SkillsIcons
		SkillExplosionC,
		SkillExplosionBN,
		SkillGolpeFuerteC,
		SkillGolpeFuerteBN,
		SkillInvencibleC,
		SkillInvencibleBN,
		SkillLiberationC,
		SkillLiberationBN,
		SkillPerforanteC,
		SkillPerforanteBN,
		SkillRaudoC,
		SkillRaudoBN,
		SkillReboteC,
		SkillReboteBN,
		SkillTorbellinoC,
		SkillTorbellinoBN,

		//Fondos
		MenuBackground,
		InventoryMenu,
		PauseBackground,
		SaveLoadBackground,
		StashMenu,//
		SkillMenu,
		ShopMenu,
		Scene1,
		Scene2,
		Scene3,
		Scene4,
		Scene5,
		Scene6,
		Scene7,
		Scene8,
		Scene9,
		TextBox,
		Ship,
		Table,
		Map1,
		Map2,
		Map3,
		GameOver1,
		GameOver2,
		Rain1,
		Rain2,
		Rain3,
		Rain4,
		Win,

		//HUD
		WheelHUD,
		RopeHUD,
		SkillsHUD,
		CooldownHUD,
		LifeHUD,
		ExplosionIcon,
		GolpeFuerteIcon,
		InvencibleIcon,
		LiberacionIcon,
		PerforanteIcon,
		RaudoIcon,
		ReboteIcon,
		TorbellinoIcon,

		//Objects
		HealthPot,
		ManaPot,
		SpeedPot,
		ArmorPot,
		DmgPot,
		CritPot,
		PotionBG,

		//Sprites
		Dragon,
		PlayerFront,
		MonkeyFront,
		WolfFront,
		Kraken,
		VenancioDrink,
		VenancioPushStart,
		VenancioPushBucle,
		VenancioPushFinish,
		Merchant,
		Cooker,
		SkeletonMusician,
		Cartographer,
		Morty,
		VenancioFuneral,
		MerchantFuneral,
		CookerFuneral,
		MortyFuneral,
		CartographerFuneral,

		Crab,
		//Bosses
		Magordito,
		Cleon,

		//gizmos
		Rojo,
		Azul,

		//Animaciones
		EntityDie,
		CrabWalk,
		CrabAttack,
		CrabIdle,

		//Player
		PlayerIdleRightAnim,
		PlayerIdleLeftAnim,
		PlayerIdleUpAnim,
		PlayerIdleDownAnim,
		PlayerMoveRightAnim,
		PlayerMoveLeftAnim,
		PlayerMoveUpAnim,
		PlayerMoveDownAnim,
		PlayerShootRightAnim,
		PlayerShootLeftAnim,
		PlayerShootUpAnim,
		PlayerShootDownAnim,
		PlayerMeleeRightAnim,
		PlayerMeleeLeftAnim,
		PlayerMeleeUpAnim,
		PlayerMeleeDownAnim,
		PlayerEmpoweredRight,
		PlayerEmpoweredLeft,
		PlayerEmpoweredUp,
		PlayerEmpoweredDown,

		//Clon
		ClonIdleRightAnim,
		ClonIdleLeftAnim,
		ClonIdleUpAnim,
		ClonIdleDownAnim,
		ClonMeleeRightAnim,
		ClonMeleeLeftAnim,
		ClonMeleeUpAnim,
		ClonMeleeDownAnim,
		ClonShootRightAnim,
		ClonShootLeftAnim,
		ClonShootUpAnim,
		ClonShootDownAnim,
			//Autodestrucción
		ClonSelfDestructionRightAnim,
		ClonSelfDestructionLeftAnim,
		ClonSelfDestructionUpAnim,
		ClonSelfDestructionDownAnim,
			//Desaparecer
		ClonVanishRightAnim,
		ClonVanishLeftAnim,
		ClonVanishDownAnim,
		ClonVanishUpAnim,

		//Calabaza
			//Idle
		PumpkinIdleRightAnim,
		PumpkinIdleLeftAnim,
		PumpkinIdleUpAnim,
		PumpkinIdleDownAnim,
			//Explosion
		PumpkinExpRightAnim,
		PumpkinExpLeftAnim,
		PumpkinExpUpAnim,
		PumpkinExpDownAnim,
			//Attack
		PumpkinAttackRightAnim,
		PumpkinAttackLeftAnim,
		PumpkinAttackUpAnim,
		PumpkinAttackDownAnim,
			//Move
		PumpkinMoveRightAnim,
		PumpkinMoveLeftAnim,
		PumpkinMoveUpAnim,
		PumpkinMoveDownAnim,
		
		//Monkey
		MonkeyIdleRightAnim,
		MonkeyIdleLeftAnim,
		MonkeyIdleUpAnim,
		MonkeyIdleDownAnim,
		MonkeyShootRightAnim,
		MonkeyShootLeftAnim,
		MonkeyShootUpAnim,
		MonkeyShootDownAnim,

		//Pirata náufrago
		PirateIdleRightAnim,
		PirateIdleLeftAnim,
		PirateIdleUpAnim,
		PirateIdleDownAnim,
		PirateMoveRightAnim,
		PirateMoveLeftAnim,
		PirateMoveUpAnim,
		PirateMoveDownAnim,
		PirateMeleeRightAnim,
		PirateMeleeLeftAnim,
		PirateMeleeUpAnim,
		PirateMeleeDownAnim,
		PirateShootRightAnim,
		PirateShootLeftAnim,
		PirateShootUpAnim,
		PirateShootDownAnim,

		//Magordito
		Altar,
			//Idle
		MagorditoIdleRight,
		MagorditoIdleLeft,
		MagorditoIdleTopRight,
		MagorditoIdleTopLeft,
			//Disparo
		MagorditoShootRight,
		MagorditoShootLeft,
		MagorditoShootDown,
		MagorditoShootTopRight,
		MagorditoShootTopLeft,
			//Viaje
		MagorditoTpRight,
		MagorditoTpLeft,
		MagorditoTpTopRight,
		MagorditoTpTopLeft,
			//Kirin
		MagorditoKirinRight,
		MagorditoKirinLeft,
		MagorditoKirinTopRight,
		MagorditoKirinTopLeft,
		Kirin,
			//Skeleton
		SkeletonIdleRightAnim,
		SkeletonIdleLeftAnim,
		SkeletonIdleUpAnim,
		SkeletonIdleDownAnim,
		SkeletonAttackRightAnim,
		SkeletonAttackLeftAnim,
		SkeletonAttackUpAnim,
		SkeletonAttackDownAnim,
		SkeletonMoveRightAnim,
		SkeletonMoveLeftAnim,
		SkeletonMoveDownAnim,
		SkeletonMoveUpAnim,
		//Interactuables
		Wheel,
		Stash,
		ShipDoor,
		ExitShip,
		Chest,
		Bullet,

		//Colsionable
		Rock,
			//Tutorial
		Bottle,
		Dummy,

		//Textos
		PlayText,
		ExitText,
		ControlsText,
		LoadText,
		CreditsText,
		ResumeText,
		MainMenuText,
		StashMoneyText,
		InventoryMoneyText,

		//proyectiles
		Coco,
		Bone,

		//Equipables
		Armor1,
		Armor2,
		Gloves1,
		Gloves2,
		Boots1,
		Boots2,
		Sword1,
		Sword1H,
		Sword2,
		Sword2H,
		Saber1,
		Saber1H,
		Saber2,
		Saber2H,
		Gun1,
		Gun2,
		ShotGun1,
		ShotGun2,

		//Tilesets de los mapas
		Tileset1,
		CollisionTile,

		//CreditState
		CreditBackground,
		fichaPrimera,
		TwitterButton,
		GitButton,
		//Avatares
		Agus,
		//Aida,
		Amaro,
		Aurora,
		Dani,
		Georgi,
		Leyre,
		Paula,
		Oscar,
		Stiven,
		//Fichas
		AgusFicha,
		//AidaFicha
		AmaroFicha,
		AuroraFicha,
		DaniFicha,
		GeorgiFicha,
		LeyreFicha,
		PaulaFicha,
		OscarFicha,
		StivenFicha,
		//agradecientos
		PanelCollaborators,
		BotonBonus,
		Bonus,
	};
	
	enum MusicChannels : int {
		//Musica auxiliar
		MainMusicChannel,
		AuxMusicChannel1,
		AuxMusicChannel2,
		AuxMusicChannel3,
		//Cantidad de canales
		NumMusicChannels
	};

	enum SoundChannels : int {
		//Canal de los botones
		BeerButtonChanel = NumMusicChannels,
		//Canal del jugador
		PlayerChannel1,
		PlayerChannel2,
		PlayerChannel3,
		PlayerChannel4,
		//Canal del lobo
		WolfChannel, 
		//Canal del mono
		MonkeyChannel,
		//Canal de la calabaza
		PumpkinChannel1,
		PumpkinChannel2,
		//Canal del esqueleto
		SkeletonChannel1,
		SkeletonChannel2,
		SkeletonChannel3,
		SkeletonChannel4,
		//Canal del congrejo
		CrabChannel1,
		CrabChannel2,
		//Canal del pirata
		EnemyPirateChannel1,
		EnemyPirateChannel2,
		EnemyPirateChannel3,
		//Canal del kraken
		KrakenChannel1,
		KrakenChannel2,
		//canal de magordito
		MagorditoChannel1,
		MagorditoChannel2,
		MagorditoChannel3,

		//Canal de jarl
		JarlChannel,
		//Numero de canales
		NumSoundChannels
	};

	///<summary>Enum para las distintos audios del juego</summary>
	enum AudioId : int {
		//Música
		MainTheme,
		Caribbean,
		Shop,
		Storyboard,
		WavesSound,
		FuneralTheme,
		CreditTheme,

		//Efectos de sonido
		Agro,

		//Efectos para el lobo
		WolfHowl,
		WolfAttack,
		WolfDie,

		//Efectos para el mono
		MonkeyIdle,
		MonkeyAttack,
		MonkeyShoot,
		MonkeyDie,

		//player
		WalkAudio,
		Attack1,
		Attack2,
		Attack3,
		Attack4,
		Attack5,
		Attack6,
		DyingAudio,
		Laugh1,
		Laugh2,
		Laugh3,
		Laugh4,
		Laugh5,
		Laugh6,
		Laugh7,
		Shout,
		Drink,
		EmpoweredSkillAudio,
		PerforateSkill,
		Ricochet,
		WhirlwindSkill,
		Pistol,
		Trabuco,
		SwordSound1,
		SwordSound2,
		SwordSound3,
		SwordSound4,
		SwordSound5,
		SwordSound6,
		MeleeCrit,
		DistCrit,
		Hurt1,
		Hurt2,
		Hurt3,
		Hurt4,

		//CLon
		Explosion,

		//Efectos para el lobo
		WolfHowlAudio,
		WolfAttackAudio,
		WolfDieAudio,

		//Efectos para el mono
		MonkeyIdleSound,
		MonkeyAttackSound,
		MonkeyShootSound,
		MonkeyDieSound,

		//Esqueleto
		SkeletonAttack,
		SkeletonBoomerang,
		SkeletonDeath,
		SkeletonHit1,
		SkeletonHit2,
		SkeletonHit3,
		SkeletonIdle,

		//Cangrejo
		CrabAttackSound,
		CrabDetection,
		CrabIdleSound,

		//Pirata
		PirateAttack,
		PirateShot,
		PirateDetection1,
		PirateDetection2,
		PirateIdle,
		PirateChase,

		//Calabaza
		AgroPumpkin,
		AttackPumpkin,
		ExplosionPumpkin,
		IdlePumpkin1,
		IdlePumpkin2,
		LaughPumpkin1,
		LaughPumpkin2,
		LaughPumpkin3,
		MovePumpkin,
		TauntPumpkin1,
		TauntPumpkin2,

		//Kraken
		KrakenIdle,
		KrakenInk,
		KrakenSplash,
		KrakenDive,
		KrakenSurface,
		KrakenSlam1,
		KrakenSlam2,
		KrakenSweep1,
		KrakenSweep2,
		KrakenSweep3,
		KrakenDeath,
		KrakenMusic,

		//Magordito
		//IdleMagordito,
		//MovementMagordito,
		MagorditoDeath,
		MagorditoKirin,
		MagorditoTeleport,
		MagorditoResurrection,
		//ThemeMagordito,
		Magorditolaugh1,
		Magorditolaugh2,
		Magorditolaugh3,
		Magorditolaugh4,
		MagorditoAttack1,
		MagorditoAttack2,
		MagorditoAttack3,
		MagorditoAttack4,
		MagorditoAttack5,
		MagorditoAggro,

		//Tutorial
		Glass,
		DummyDie,

		//NPC
		VenancioTalk,

		//Tienda/inventario/alijo
		Pag,
		Equip,
		Time,
		Gold,

		//Jarls
		jarl1,
		jarl2,
		jarl3,
		jarl4,
		jarl5,
		jarl6,
		jarl7,
		jarl8,
		jarl9,
		jarl10,
		jarl11,

	};

	///<summary>Enum para las distintos fuentes del juego</summary>
	enum FontId : int {
		RETRO,
		RETROSM
	};

	///<summary>Struct para la informacion de las imagenes</summary>
	struct ImageInfo {
		TextureId textureId;
		string filename;
	};

	///<summary>Struct para la información del sonido</summary>
	struct AudioInfo {
		AudioId audioId;
		string filename;
	};

	///<summary>Struct para la informacion de la música</summary>
	struct MusicInfo {
		AudioId id;
		string fileName;
	};

	///<summary>Struct para la informacion de las fuentes</summary>
	struct FontInfo {
		FontId id;
		string fileName;
		int size;
	};

	//Struct para definir los textos
	struct TextMsgInfo {
		TextureId id;
		string msg;
		SDL_Color color;
		FontId fontId;
	};

	struct AudioVolume
	{
		int channel;
		int volume;
	};

	///<summary>Vector con las rutas de las imagenes a cargar</summary>
	static vector<ImageInfo> imageRoutes;

	///<summary>Vector con las rutas de los audios a cargar</summary>
	static vector<AudioInfo> audioRoutes;
	
	//<summary>Vector para el volumen de cada canal</summary>	
	static vector<AudioVolume> audioVolume;

	///<summary>Vector con las rutas de la música a cargar</summary>
	static vector<MusicInfo> musicRoutes;

	///<summary>Vector con las rutas de las fuentes a cargar</summary>
	static vector<FontInfo> fontsRoutes;

	//Vector con los textos
	static vector<TextMsgInfo> messages; // initialized in .cpp

	//Diccionario de signos de puntuacion
	static map<char, string>tildes_;
};
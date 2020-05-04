#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>

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
		MuteOff,
		MuteOn,
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
		TextBox,
		Ship,
		Table,
		Map1,
		Map2,
		Map3,
		CaribbeanMap,
		Spooky,
		Volcanic,
		GameOver,
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

		//Sprites
		Dragon,
        PlayerFront,
		MonkeyFront,
		WolfFront,
		Kraken,
		Cooker,
		Merchant,
		SkeletonMusician,
		Cartographer,

		//Bosses
		Magordito,
		Cleon,
		Skeleton,

		//gizmos
		Rojo,
		Azul,

		//Animaciones
		CrabAttack,
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
		ClonSelfDestructionRightAnim,
		ClonSelfDestructionLeftAnim,
		ClonSelfDestructionUpAnim,
		ClonSelfDestructionDownAnim,
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
		MonkeyIdleRightAnim,
		MonkeyIdleLeftAnim,
		MonkeyIdleUpAnim,
		MonkeyIdleDownAnim,
		MonkeyShootRightAnim,
		MonkeyShootLeftAnim,
		MonkeyShootUpAnim,
		MonkeyShootDownAnim,
		//Magordito
			//Kirin
		Kirin,


		//Interactuables
		Wheel,
		Stash,
		ShipDoor,
		ExitShip,
		Chest,
		Bullet,

		//Colsionable
		Rock,

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

		//Equipables
		Armor1,
		Armor2,
		Gloves1,
		Gloves2,
		Boots1,
		Boots2,
		Sword1,
		Sword2,
		Saber1,
		Saber2,
		Gun1,
		Gun2,
		ShotGun1,
		ShotGun2,

		//Tilesets de los mapas
		Tileset1,
		CollisionTile
	};

	///<summary>Enum para las distintos audios del juego</summary>
	enum AudioId : int{
		//Música
		MainTheme,
		ShipSingers,
		Caribbean,

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
		Walk,
		Attack1,
		Attack2,
		Attack3,
		Attack4,
		Attack5,
		Attack6,
		Dying,
		Laugh1,
		Laugh2,
		Laugh3,
		Laugh4,
		Laugh5,
		Laugh6,
		Laugh7,
		Shout,
		Drink,
		EmpoweredSkill,
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

		//CLon
		Explosion,

		//Ship
		Waves,

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
		TauntPumpkin2
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
	struct SoundInfo {
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

	///<summary>Vector con las rutas de las imagenes a cargar</summary>
	static vector<ImageInfo> imageRoutes;

	///<summary>Vector con las rutas de los audios a cargar</summary>
	static vector<SoundInfo> soundRoutes;

	///<summary>Vector con las rutas de la música a cargar</summary>
	static vector<MusicInfo> musicRoutes;
	
	///<summary>Vector con las rutas de las fuentes a cargar</summary>
	static vector<FontInfo> fontsRoutes;

	//Vector con los textos
	static vector<TextMsgInfo> messages; // initialized in .cpp
};
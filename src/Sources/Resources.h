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
		InventaryMenu,
		PauseBackground,
		StashMenu,//
		SkillMenu,
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

		//Bosses
		Magordito,
		Cleon,

		//gizmos
		Rojo,
		Azul,

		//Animaciones
		CrabAttack,

		//Interactuables
		Wheel,
		Stash,
		ShipDoor,
		ExitShip,

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
		Gun1,
		Gloves1,
	};

	///<summary>Enum para las distintos audios del juego</summary>
	enum AudioId : int{
		//Música
		MainTheme,
		ShipSingers,

		//Efectos de sonido
		Agro,

		//Efectos para el lobo
		WolfHowl,
		WolfAttack,
		WolfDie,
		Shout //TODO: Añadir a resources el sonido del grito.
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
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
		GoControls,
		BackButton,
		SkipButton,
		MuteOff,
		MuteOn,
		Resume,
		RestartGame,

		//Fondos
		MenuBackground,
		InventaryMenu,
		Controls,
		PauseBackground,
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
		ManaHUD,
		ExplosionIcon,
		GolpeFuerteIcon,
		InvencibleIcon,
		LiberacionIcon,
		PerforanteIcon,
		RaudoIcon,
		ReboteIcon,
		TorbellinoIcon,
		HealthPot,
		ManaPot,
		SpeedPot,
		ArmorPot,
		DmgPot,
		CritPot,

		//Personajes
		Dragon,
        PlayerFront,
		MonkeyFront,

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
		//proyectiles
		Coco
	};

	///<summary>Enum para las distintos audios del juego</summary>
	enum AudioId : int{
		//Música
		MainTheme

		//Efectos de sonido
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
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
		Timon,
		BotonMenu,
		//Botones
		GoControls,
		BackButton,
		Controls,
		ButtonX,
		ButtonUpgradeGreen,
		ButtonUpgradeRed,
		ButtonUpgradeBlue,
		ButtonUpgradeYellow,
		GreenBar,
		BlueBar,
		YellowBar,
		RedBar,
		EmptyBar,

		//Skills
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
		InventaryMenu,
		SkillMenu,
		StashMenu,
		Scene1,
		Scene2,
		Scene3,
		TextBox,
		MenuFondo,

		//Personajes
		Dragon,
		Roca,
        
		//Textos
		PlayText,
		ExitText,
		ControlsText,
		LoadText,
		CreditsText,
		StashMoneyText,
		InventoryMoneyText,

		//Botones
		ForwardArrow,
		BackwardsArrow,
		TrashButton,
		ChangeButton,
		CloseButton,
		MoneyButton,
		SkillText
	};

	///<summary>Enum para las distintos audios del juego</summary>
	enum AudioId : int{
		MainTheme
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
	static vector<TextMsgInfo> messages_; // initialized in .cpp
};
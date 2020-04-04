#include "Resources.h"

vector<Resources::ImageInfo> Resources::imageRoutes{
	//Interfaces
	{MenuFondo, "../Sources/assets/interfaces/menuFondo.png"},
	{BotonMenu, "../Sources/assets/botones/botonMenu.png"},
	{ Timon, "../Sources/assets/player/timon.png" },
	{ GoControls, "../Sources/assets/botones/botonControles.png"},
	{ BackButton, "../Sources/assets/botones/volver.png"},
	{ ButtonX, "../Sources/assets/botones/botonX.png"},
	{ ButtonUpgradeGreen, "../Sources/assets/botones/UpgradeButtonGreen.png"},
	{ ButtonUpgradeRed, "../Sources/assets/botones/UpgradeButtonRed.png"},
	{ ButtonUpgradeBlue, "../Sources/assets/botones/UpgradeButtonBlue.png"},
	{ ButtonUpgradeYellow, "../Sources/assets/botones/UpgradeButtonYellow.png"},
	{ GreenBar, "../Sources/assets/botones/greenBar.png"},
	{ BlueBar, "../Sources/assets/botones/blueBar.png"},
	{ YellowBar, "../Sources/assets/botones/yellowBar.png"},
	{ RedBar, "../Sources/assets/botones/redBar.png"},
	{ EmptyBar, "../Sources/assets/botones/emptyBar.png"},
	{EquippedSkill, "../Sources/assets/botones/EquippedSkill.png"},

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


	{ Controls, "../Sources/assets/interfaces/controles.png"},
	{ InventaryMenu, "../Sources/assets/interfaces/InventarioFondo.png" },
	{ SkillMenu, "../Sources/assets/interfaces/HabilidadesFondo.png" },
	{StashMenu, "../Sources/assets/interfaces/AlijoFondo.png"},
	{ Scene1, "../Sources/assets/interfaces/Scene1.png"},
	{ Scene2, "../Sources/assets/interfaces/Scene2.png"},
	{ Scene3, "../Sources/assets/interfaces/Scene3.png"},
	{ TextBox, "../Sources/assets/interfaces/textBoxBg.png" },
	//Sprites
	{ Roca, "../Sources/assets/colisionables/roca.png" },
	//Para añadir nueva ruta: {TextureId, "../Sources/assets/name.png-jpg..."}
	{Dragon,"../Sources/assets/enemigos/dragon.png"},
	//Para añadir nueva ruta: {TextureId, "./Sources/images/name.png/jpg..."}

	//Botones
	{ForwardArrow, "../Sources/assets/botones/FowardArrowButton.png"},
	{BackwardsArrow, "../Sources/assets/botones/BackwardsArrowButton.png"},
	{TrashButton, "../Sources/assets/botones/TrashButton.png"},
	{ChangeButton, "../Sources/assets/botones/ChangeButton.png"},
	{CloseButton, "../Sources/assets/botones/CloseButton.png"},
	{MoneyButton, "../Sources/assets/botones/MoneyButton.png"},

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

vector <Resources::TextMsgInfo> Resources::messages_{

	//Para añadir nuevo texto: {TextureId , string "mensaje", { COLOR(0xaaffffff), FontId  }
	{ PlayText,"Nueva Partida",SDL_Color{(0,0,0,1)},RETRO },
	{ ExitText,"Salir",SDL_Color{(0,0,0,1)},RETRO },
	{ ControlsText,"Controles",SDL_Color{(0,0,0,1)},RETRO },
	{ LoadText,"Cargar Partida",SDL_Color{(0,0,0,1)},RETRO },
	{ CreditsText,"Créditos",SDL_Color{(0,0,0,1)},RETRO },
	{ SkillText,"SkillMenu",SDL_Color{(0,0,0,1)},RETRO },
	{InventoryMoneyText, "Dinero inventario:", SDL_Color({255,255,255,1}), RETRO},
	{StashMoneyText, "Dinero alijo:",  SDL_Color({255,255,255,1}), RETRO}
};

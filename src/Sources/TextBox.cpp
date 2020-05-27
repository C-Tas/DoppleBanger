#include "TextBox.h"
#include "HandleEvents.h"
#include "Resources.h"
#include "GameState.h"
#include "ShopState.h"
#include "Player.h"
#include "SDL_macros.h"
#include "CollisionCtrl.h"
#include "ShipState.h"
#include "tutorialState.h"
//Cada l�nea de los di�logos/descripciones se tiene que renderizar por separado para poder generar los saltos de l�nea.
//Lo relacionado con textos aparece aqu� y no en Resources para no sobrecargar dicha clase.
//Los NPCs y los bosses se encargan de llamar en su update a su respectivo textBox cuando corresponda,
//y se renderiza hasta que se presione cualquier tecla y se elimine el textBox.
//Cada objeto llama a su correspondiente descripci�n, cuando el estado abierto se lo indique,
//pas�ndo la posici�n en la que se sit�a la descripci�n de dicho estado.

//Callback del mercader para abrir la tienda
void TextBox::goShopState(Application* app)
{
	app->resetSoundsChannels();
	app->resetMusicChannels();
	app->getAudioManager()->playChannel(Resources::Shop, -1, Resources::MainMusicChannel);
	dynamic_cast<Player*>(GameManager::instance()->getPlayer())->stop();
	app->getGameStateMachine()->pushState(new ShopState(app));
}

void TextBox::nextConversation(Application* app) {
	app->getGameManager()->getPlayer()->stop();
	CollisionCtrl::instance()->nextConversation();
}

void TextBox::skipTutorial(Application* app)
{
	app->getGameManager()->desactiveTutorial();
	app->getGameManager()->resetGameManager();
	dynamic_cast<Player*>(GameManager::instance()->getPlayer())->stop();
	app->getGameStateMachine()->pushState(new ShipState(app));
}

void TextBox::nextTutorialVenancio(Application* app)
{
	dynamic_cast<Player*>(GameManager::instance()->getPlayer())->stop();
	GameManager::instance()->nextPhaseVenancio();
}
void TextBox::goToShipState(Application* app)
{
	CollisionCtrl::instance()->clearList();
	GameManager::instance()->resetIsland();
	app->getGameStateMachine()->changeState(new ShipState(app));
}

void TextBox::changeZone(Application* app)
{
	static_cast<PlayState*>(app->getCurrState())->changeZone();
}

void TextBox::unlockCookerReward(Application* app)
{
	dynamic_cast<Player*>(GameManager::instance()->getPlayer())->stop();
	GameManager::instance()->setCompleteMission(missions::gallegaEnProblemas, true);
	GameManager::instance()->setMissionRewardObtained(missions::gallegaEnProblemas, true);
}

void TextBox::unlockParrotReward(Application* app)
{
	dynamic_cast<Player*>(GameManager::instance()->getPlayer())->stop();
	GameManager::instance()->setCompleteMission(missions::masValePajaroEnMano, true);
	GameManager::instance()->setMissionRewardObtained(missions::masValePajaroEnMano, true);
}

void TextBox::unlockMortyReward(Application* app)
{
	dynamic_cast<Player*>(GameManager::instance()->getPlayer())->stop();
	GameManager::instance()->setCompleteMission(missions::papelesSiniestros, true);
	GameManager::instance()->setMissionRewardObtained(missions::papelesSiniestros, true);
}

void TextBox::unlockMusicianReward(Application* app)
{
	dynamic_cast<Player*>(GameManager::instance()->getPlayer())->stop();
	GameManager::instance()->setCompleteMission(missions::laboon, true);
	GameManager::instance()->setMissionRewardObtained(missions::laboon, true);
}

void TextBox::unlockNamiReward(Application* app)
{
	dynamic_cast<Player*>(GameManager::instance()->getPlayer())->stop();
	GameManager::instance()->setCompleteMission(missions::arlongPark, true);
	GameManager::instance()->setMissionRewardObtained(missions::arlongPark, true);
}

void TextBox::initDialog() {
	//Generamos la caja donde ir� el texto
	Texture* whiteRect = app_->getTextureManager()->getTexture(Resources::TextureId::TextBox);
	whiteRect->render(dest);

	//Comentario al final de la caja de texto
	Texture pressAnyKey(app_->getRenderer(), "Al" + Resources::tildes_["e"] + "jate para dejar de hablar >>", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x99999999) });
	pressAnyKey.render(app_->getWindowWidth() - pressAnyKey.getWidth() - lineSpacing, app_->getWindowHeight() - pressAnyKey.getHeight() - lineSpacing);
}

void TextBox::initDescription(Point2D pos) {
	//Caja donde se representa el texto de las descripciones
	dest.w = app_->getWindowWidth() / 4;
	dest.h = app_->getWindowHeight() / 7;
	dest.x = (int)round(pos.getX());
	dest.y = (int)round(pos.getY());
}

void TextBox::passZoneDialog()
{
	//Generamos la caja donde ir� el texto
	Texture* whiteRect = app_->getTextureManager()->getTexture(Resources::TextureId::TextBox);
	whiteRect->render({ 0,dest.y, dest.w, dest.h });

	dest.x = lineSpacing;
	dest.y = app_->getWindowHeight() - dest.h;

	Texture text(app_->getRenderer(), "Has llegado al final de la zona, " + Resources::tildes_["¿"] + "Deseas continuar?", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(lineSpacing, dest.y + lineSpacing);

	goToShipButton_->draw();
	goToNextZoneButton_->draw();
}


#pragma region Dialogos
void TextBox::dialogElderMan(int num) {
	initDialog();
	Texture text;
	if (GameManager::instance()->onTutorial()) {
		skipTutorial_->draw();
		skipTutorial_->update();
		auto aux = dynamic_cast<tutorialState*>(app_->getCurrState());
		if (aux && aux->isCurrTaskComplete()) {
			GameManager::instance()->nextPhaseVenancio();
			aux->currTaskIncomplete();
			aux->activeDummyCreation();
		}
		switch (GameManager::instance()->getVenancioPhase())
		{
		case 0:
			tutorialButton_->draw();
			tutorialButton_->update();
			text.loadFromText(app_->getRenderer(), "Veo que no todo el mundo necesita un taca-taca para morverse...",
				app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);
			text.loadFromText(app_->getRenderer(), "Te veo verde, " + Resources::tildes_["¿"] + "has visto lo mamad" + Resources::tildes_["i"] + "simo que estoy?, te puedo dar unos consejos.",
				app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing * 2);
			break;
		case 1:
			skipTutorial_->setPos(Vector2D{ app_->getWindowWidth() - skipTutorial_->getScaleX() - lineSpacing, dest.y + (double)lineSpacing * 3 });

			text.loadFromText(app_->getRenderer(), "Usa tu pistola con click derecho para romper esa botella que me recuerda al amor de ella.",
				app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);
			break;
		case 2:
			text.loadFromText(app_->getRenderer(), "Presionando una " + Resources::tildes_["u"] + "nica vez el click izquierdo sobre un enemigo, puedes mocharlo.",
				app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);
			text.loadFromText(app_->getRenderer(), "Te recomiendo limpiar tu espada despu" + Resources::tildes_["e"] + "s de mochar al susodicho.",
				app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing * 2);
			break;
		case 3:
			switch (num) {
			case 0:
				text.loadFromText(app_->getRenderer(), Resources::tildes_["¿"] + "Has visto que el susodicho te ha dado puntos de haza" + Resources::tildes_["ñ"] + "a?",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);
				text.loadFromText(app_->getRenderer(), "Puedes verlos en la esquina derecha de abajo. Se consiguen al ganar experiencia.",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 2);
				text.loadFromText(app_->getRenderer(), "Abre el menu de habilidades con la 'V' y s" + Resources::tildes_["u"] + "malos a la segunda rama.",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 3);

				button_->draw();
				button_->update();
				break;
			case 1:
				text.loadFromText(app_->getRenderer(), "Al desbloquear la habilidad haz click sobre esta y luego haz click sobre el acceso (Q, W, E) que te guste.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);

				text.loadFromText(app_->getRenderer(), "Ahora usa ese acesso para activar la habilidad y mocha al susodicho.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + (lineSpacing * 2));

				text.loadFromText(app_->getRenderer(), "Utilizar una habilidad te consumir" + Resources::tildes_["a"] + " man" + Resources::tildes_["a"] + ", puedes ver la cantidad que tienes en la barra", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + (lineSpacing * 3));

				text.loadFromText(app_->getRenderer(), "azul del tim" + Resources::tildes_["o"] + "n.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + (lineSpacing * 4));
				break;
			}
			break;
		case 5:
			switch (num) {
			case 0:
				text.loadFromText(app_->getRenderer(), "Algunas veces encontrar" + Resources::tildes_["a"] + "s tesoros, no lo dudes " + Resources::tildes_["¡"] + Resources::tildes_["¡"] + "m" + Resources::tildes_["o"] + "chalos a todos!!",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);
				text.loadFromText(app_->getRenderer(), "Usa el oro del cofre para comprar una poci" + Resources::tildes_["o"] + "n a ese t" + Resources::tildes_["i"] + "o mas verde que t" + Resources::tildes_["u"] + ".",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 2);
				text.loadFromText(app_->getRenderer(), "Si te sobra algo podr" + Resources::tildes_["i"] + "as comprarme un ron, " + Resources::tildes_["¿"] + "no?",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 3);
				button_->draw();
				button_->update();
				break;
			case 1:
				text.loadFromText(app_->getRenderer(), "Abre el inventario con la tecla 'C' y equ" + Resources::tildes_["i"] + "pala con el bot" + Resources::tildes_["o"] + "n verde.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);

				text.loadFromText(app_->getRenderer(), "Los objetos equipados se usan con los accesos '1' y '2' respectivamente.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + (lineSpacing * 2));

				text.loadFromText(app_->getRenderer(), "Prueba a beberte la poci" + Resources::tildes_["o"] + "n, ver" + Resources::tildes_["a"] + "s como te sube la cantidad de man" + Resources::tildes_["a"] + ".", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + (lineSpacing * 3));
				break;
			}
			break;
		case 6:
			switch (num) {
			case 0:
				skipTutorial_->setTexture(app_->getTextureManager()->getTexture(Resources::ButtonFinishTutorial));
				text.loadFromText(app_->getRenderer(), "Ten cuidado ah" + Resources::tildes_["i"] + " fuera porque si eres derrotada podr" + Resources::tildes_["e"] + " ir a salvarte",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);
				text.loadFromText(app_->getRenderer(), "pero no podr" + Resources::tildes_["e"] + " recuperar ni el oro ni los objetos que no lleves equipados.",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 2);
				text.loadFromText(app_->getRenderer(), "Y recuerda, siempre puedes confiar en tu anillo, con la tecla 'R' podr" + Resources::tildes_["a"] + "s invocarla.",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 3);
				button_->draw();
				button_->update();
				break;
			case 1:
				text.loadFromText(app_->getRenderer(), "Actuar" + Resources::tildes_["a"] + " como diana para los enemigos y disparar" + Resources::tildes_["a"] + " donde t" + Resources::tildes_["u"] + " lo hagas.",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);
				text.loadFromText(app_->getRenderer(), "Adem" + Resources::tildes_["a"] + "s podr" + Resources::tildes_["a"] + "s mejorarla con los puntos de haza" + Resources::tildes_["ñ"] + "a para que tambi" + Resources::tildes_["e"] + "n pueda mochar.",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 2);
				text.loadFromText(app_->getRenderer(), "Bueno, si me disculpas, hoy tocha pecho y biceps.",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 3);
				break;
			}
			break;
		default:
			break;
		}
	}
	else
	{

		switch (GameManager::instance()->getCurrIsland())
		{
		case Island::Caribbean:
			switch (num) {
			case 0:
				text.loadFromText(app_->getRenderer(), "Ah, eres t" + Resources::tildes_["u"] + ", muchacha. Quer" + Resources::tildes_["i"] + "a comentarte una observaci" + Resources::tildes_["o"] + "n m" + Resources::tildes_["i"] + "a.",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);
				text.loadFromText(app_->getRenderer(), "Al parecer no vamos hacia ning" + Resources::tildes_["u"] + "n lado, o al menos eso nos dicen los mapas. Sin embargo",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 2);
				text.loadFromText(app_->getRenderer(), "la ruta que llevamos es precisamente la que indica la reliquia de tu tesoro.",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 3);
				button_->draw();
				button_->update();
				break;
			case 1:
				text.loadFromText(app_->getRenderer(), "Eso hace a uno pensar...", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);

				text.loadFromText(app_->getRenderer(), "A veces hace falta perderse para encontrar lo que hace a uno seguir buscando...", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 2);

				text.loadFromText(app_->getRenderer(), "Pero no creo que el objetivo de tu mapa sea de car" + Resources::tildes_["a"] + "cter filos" + Resources::tildes_["o"] + "fico, chiquilla.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 3);
				button_->draw();
				button_->update();
				break;
			case 2:
				text.loadFromText(app_->getRenderer(), "Hace muchos a" + Resources::tildes_["ñ"] + "os, durante la guerra, o" + Resources::tildes_["i"] + " una historia, una leyenda, sobre un pirata que existi" + Resources::tildes_["o"] + " hace",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);

				text.loadFromText(app_->getRenderer(), "tanto que el propio tiempo ha perdido la cuenta de los a" + Resources::tildes_["ñ"] + "os. M" + Resources::tildes_["a"] + "s animal que hombre, este pirata", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 2);

				text.loadFromText(app_->getRenderer(), "era infame por su s" + Resources::tildes_["a"] + "dica violencia y brutalidad, saqueando a piratas, ciudadanos y gobiernos por igual.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 3);
				button_->draw();
				button_->update();
				break;
			case 3:
				text.loadFromText(app_->getRenderer(), "Se le acredita tambi" + Resources::tildes_["e"] + "n una gran creatividad, ya que no dos golpes liderados por " + Resources::tildes_["e"] + "l eran iguales,",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);

				text.loadFromText(app_->getRenderer(), "aunque todos ten" + Resources::tildes_["i"] + "an algo en com" + Resources::tildes_["u"] + "n. Las v" + Resources::tildes_["i"] + "ctimas cuyas vidas perdonaba para contar su", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 2);

				text.loadFromText(app_->getRenderer(), "historia, bueno, digamos que nunca mor" + Resources::tildes_["i"] + "an por causas naturales...", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 3);

				button_->draw();
				button_->update();
				break;

			case 4:

				text.loadFromText(app_->getRenderer(), "La leyenda tambi" + Resources::tildes_["e"] + "n mencionaba su base, en la que ocultaba todos sus botines, y que al parecer", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);

				text.loadFromText(app_->getRenderer(), "se encontraba en un archipi" + Resources::tildes_["e"] + "lago en alg" + Resources::tildes_["u"] + "n lugar de este mar. ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 2);

				button_->draw();
				button_->update();
				break;

			case 5:
				text.loadFromText(app_->getRenderer(), "Lo que hizo el pirata para evitar ataques, fue quemar cada mapa y matar a todos los cart" + Resources::tildes_["o"] + "grafos y marineros",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);

				text.loadFromText(app_->getRenderer(), "que pudieran conocer la ubicaci" + Resources::tildes_["o"] + "n de estas islas, hasta que un d" + Resources::tildes_["i"] + "a cayeron en el olvido.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 2);

				text.loadFromText(app_->getRenderer(), "A d" + Resources::tildes_["i"] + "a de hoy son poco m" + Resources::tildes_["a"] + "s que parte de su leyenda. ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 3);

				button_->draw();
				button_->update();
				break;

			case 6:
				text.loadFromText(app_->getRenderer(), "Quien sabe, a lo mejor el mapa que ahora posees sobrevivi" + Resources::tildes_["o"] + " a estos eventos...",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);

				text.loadFromText(app_->getRenderer(), "Hagas lo que hagas, no da" + Resources::tildes_["ñ"] + "es este nav" + Resources::tildes_["i"] + "o, hogar de mis recuerdos. Por favor...", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 2);
				break;
			}

			break;
		case Island::Spooky:
			switch (num) {
			case 0: 
				text.loadFromText(app_->getRenderer(), Resources::tildes_["¿"] + "Has... matado a un kraken? Incre" + Resources::tildes_["i"] + "ble... Pensaba que no exist" + Resources::tildes_["i"] + "an m" + Resources::tildes_["a"] + "s",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);
				text.loadFromText(app_->getRenderer(), "all" + Resources::tildes_["a"] + " de los cuentos e historias... Esc" + Resources::tildes_["u"] + "chame y presta atenci" + Resources::tildes_["o"] + "n, porque ",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 2);
				text.loadFromText(app_->getRenderer(), "cuando llegas a mi edad dejas a la paciencia en manos de otros m" + Resources::tildes_["a"] + "s j" + Resources::tildes_["o"] + "venes.",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 3);
				button_->draw();
				button_->update();
				break;
			case 1: 
				text.loadFromText(app_->getRenderer(), "La leyenda que te mencion" + Resources::tildes_["e"] + ", la historia del pirata m" + Resources::tildes_["a"] + "s infame de todos los mares, est" + Resources::tildes_["a"] + " tomando m" + Resources::tildes_["a"] + "s",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);
				text.loadFromText(app_->getRenderer(), "forma que me imagin" + Resources::tildes_["e"] + " posible. Nunca te cont" + Resources::tildes_["e"] + " la leyenda completa en realidad.",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 2);
				button_->draw();
				button_->update();
				break;
			case 2: 
				text.loadFromText(app_->getRenderer(),"Se cree que el pirata lleg" + Resources::tildes_["o"] + " no solo a encontrar un kraken, sino que lo encerr" + Resources::tildes_["o"] + " en sus islas," ,
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);
				text.loadFromText(app_->getRenderer(), "para siempre obligado a ser el guardi" + Resources::tildes_["a"] + "n del archipi" + Resources::tildes_["e"] + "lago. Si las islas no constan en",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 2);
				text.loadFromText(app_->getRenderer(), "ning" + Resources::tildes_["u"] + "n mapa y has matado a un kraken en una de ellas... Entonces...",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 3);
				button_->draw();
				button_->update();
				break;
			case 3:
				text.loadFromText(app_->getRenderer(), "Este archipi" + Resources::tildes_["e"] + "lago es.. el hogar del atroz Cle" + Resources::tildes_["o"] + "n, el m" + Resources::tildes_["a"] + "s pele" + Resources::tildes_["o"] + "n.",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);
				text.loadFromText(app_->getRenderer(), "Ahora mismo nos encontramos en la isla en la que tom" + Resources::tildes_["o"] + " lugar la muerte de un gran y antiguo mercenario,",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 2);
				text.loadFromText(app_->getRenderer(), "guerrero capaz de distorsionar la realidad a trav" + Resources::tildes_["e"] + "s de una t" + Resources::tildes_["e"] + "cnica hace siglos perdida.",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 3);
				button_->draw();
				button_->update();
				break;
			case 4: 
				text.loadFromText(app_->getRenderer(), "Se dice que varios gobiernos colaboraron para contratar a este asesino con el objetivo poner fin a la era ",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);
				text.loadFromText(app_->getRenderer(), "de terror del pirata. Sin embargo, una vez encontr" + Resources::tildes_["o"] + " a Cle" + Resources::tildes_["o"] + "n, este le super" + Resources::tildes_["o"] + " con creces en combate, y",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 2);
				text.loadFromText(app_->getRenderer(), "despu" + Resources::tildes_["e"] + "s de ser torturado y antes de morir, sacrific" + Resources::tildes_["o"] + " su humanidad para maldecir las ",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 3);
				text.loadFromText(app_->getRenderer(), "islas y todo lo que se encontraba en ellas. ",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing *4 );

			
				button_->draw();
				button_->update();
				
				break;
			case 5:
				text.loadFromText(app_->getRenderer(), "Una forma de venganza extrema, pero parece que efectiva, ya que se dice que desde ese d" + Resources::tildes_["i"] + "a ",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);
				text.loadFromText(app_->getRenderer(), "a mayor" + Resources::tildes_["i"] + "a de estas islas est" + Resources::tildes_["a"] + "n habitadas, pero no por seres vivos.",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 2);
				button_->draw();
				button_->update();
				break;
			case 6: 
				text.loadFromText(app_->getRenderer(), "Y este es el final de la leyenda, Cle" + Resources::tildes_["o"] + "n y su tripulaci" + Resources::tildes_["o"] + "n quedaron para siempre condenados a vivir  ",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);
				text.loadFromText(app_->getRenderer(), "estando muertos, confinados a estas islas, olvidados del mundo fuera de cuentos e historias.",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 2);
				text.loadFromText(app_->getRenderer(), "Ten cuidado, o las consecuencias podr" + Resources::tildes_["i"] + "an ser nefastas...",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 3);

				break;
			}

			break;
		case Island::Volcanic:

			text.loadFromText(app_->getRenderer(), "Esta isla... Su presencia me hiela la sangre... Mi cuerpo no deja de temblar y yo de estremecerme...", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);

			text.loadFromText(app_->getRenderer(), "Este es el final, ten cuidado, joven. Tu destino puede tomar dos caminos a partir de ahora, ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing * 2);

			text.loadFromText(app_->getRenderer(), "y uno de ellos no se lo deseo ni a mis enemigos... ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing * 3);


		default:
			break;
		}
	}

}

void TextBox::dialogMerchant(int dialog) {
	initDialog();

	if (dialog == 0) {
		Texture text(app_->getRenderer(), "Antes de que preguntes, no, no me han llegado las mascarillas.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
		text.render(lineSpacing, dest.y + lineSpacing);
	}
	else if (dialog == 1) {
		Texture text(app_->getRenderer(), "No todos los tesoros son oro camarada, pero aqu" + Resources::tildes_["i"] + " tendr" + Resources::tildes_["a"] + "s que pagarme con " + Resources::tildes_["e"] + "l.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
		text.render(lineSpacing, dest.y + lineSpacing);
	}
	else if (dialog == 2) {
		Texture text(app_->getRenderer(), "Paga una y ll" + Resources::tildes_["e"] + "vate una, paga dos y ll" + Resources::tildes_["e"] + "vate dos.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
		text.render(lineSpacing, dest.y + lineSpacing);
		text.loadFromText(app_->getRenderer(), Resources::tildes_["¿"] + "Qu" + Resources::tildes_["e"] + " te esperabas? ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
		text.render(lineSpacing, dest.y + lineSpacing * 2);
	}
	else {
		Texture text(app_->getRenderer(), Resources::tildes_["¡"] + "Arrasa con lo que veas, y generoso no seas!... Espera no, mejor se generoso y deja propina. ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
		text.render(lineSpacing, dest.y + lineSpacing);
	}

	shopButton_->draw();
	shopButton_->update();
}

void TextBox::dialogChef(bool unlock, int num) {
	initDialog();
	//Di�logo del chef cuando lo hemos desbloqueado
	if (unlock) {
		Texture text;
		if (gm_->isThatMissionPass(missions::gallegaEnProblemas) && !gm_->isThatRewardUnlocked(missions::gallegaEnProblemas)) {
			text.loadFromText(app_->getRenderer(), "Muchas gracias por ayudarme. Aqu" + Resources::tildes_["i"] + " est" + Resources::tildes_["a"] +
				" t" + Resources::tildes_["u"] + " recompensa.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);
			text.loadFromText(app_->getRenderer(), "A parte del caldito, te doy algo de oro, qu" + Resources::tildes_["e"] + " seguro que no te vendr" + Resources::tildes_["a"] + " mal.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + (lineSpacing * 2));

			unlockReward_->setCallBack(unlockCookerReward);
			unlockReward_->draw();
			unlockReward_->update();
		}
		else {
			text.loadFromText(app_->getRenderer(), "Y la levadura la tiene Pamplona" + Resources::tildes_[","] + " por eso no amasa la t" + Resources::tildes_["i"] + "a Melitona...", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);
		}
	}
	//Di�logo del chef cuando a�n est� bloqueado
	else {
		//Mientras no se hayan matado todos los enemigos
		if (gm_->getCounterEnemiesMission(missions::gallegaEnProblemas) < gm_->getEnemiesMission(missions::gallegaEnProblemas)) {
			Texture text;

			if (gm_->getCounterEnemiesMission(missions::gallegaEnProblemas) > 0) {
				text.loadFromText(app_->getRenderer(), "Necesito que mates 4 cangrejos para cocinarte un cocidito.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);
				text.loadFromText(app_->getRenderer(), "Adem" + Resources::tildes_["a"] + "s te podr" + Resources::tildes_["i"] + "a obsequiar con m" + Resources::tildes_["a"] + "s regalos.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 2);
			}
			else {
				switch (num) {
				case 0:
					text.loadFromText(app_->getRenderer(), Resources::tildes_["¡"] + "Hostia, una pirata! " + Resources::tildes_["¡"] + "No me hagas da" + Resources::tildes_["ñ"] + "o por favor!", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
					text.render(lineSpacing, dest.y + lineSpacing);

					text.loadFromText(app_->getRenderer(), "Mmm no pareces peligrosa" + Resources::tildes_["."] + Resources::tildes_["."] + Resources::tildes_["."] + " Tal vez t" + Resources::tildes_["u"] + " podr" + Resources::tildes_["i"] + "as sacarme de esta isla." + Resources::tildes_["."], app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
					text.render(lineSpacing, dest.y + (lineSpacing * 2));

					button_->draw();
					button_->update();
					break;
				case 1:
					text.loadFromText(app_->getRenderer(), "Ver" + Resources::tildes_["a"] + "s yo antes trabajaba en un barco de lujo, hasta que me ascendieron ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
					text.render(lineSpacing, dest.y + (lineSpacing));

					text.loadFromText(app_->getRenderer(), "a " + Resources::tildes_["“"] + "cocinera prescindible ejecutiva" + Resources::tildes_["“"] + " y me abandonaron en esta isla." + Resources::tildes_["."], app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
					text.render(lineSpacing, dest.y + (lineSpacing * 2));

					button_->draw();
					button_->update();
					break;
				case 2:
					text.loadFromText(app_->getRenderer(), Resources::tildes_["¡"] + "Por favor, s" + Resources::tildes_["a"] + "came de aqu" + Resources::tildes_["i"] + "! A cambio yo podr" + Resources::tildes_["i"] + "a" + Resources::tildes_["."] + Resources::tildes_["."] + Resources::tildes_["."] + " no s" +
						Resources::tildes_["e"] + Resources::tildes_["."] + Resources::tildes_["."] + Resources::tildes_["."] + " " + Resources::tildes_["¡"] + "Ser la cocinera de tu barco!", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
					text.render(lineSpacing, dest.y + (lineSpacing));

					text.loadFromText(app_->getRenderer(), "Soy una cocinera espectacular, aunque bueno" + Resources::tildes_["."] + Resources::tildes_["."] + Resources::tildes_["."] +
						" eso depende " + Resources::tildes_["¡"] + "Mi especialidad es la carne!"
						, app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
					text.render(lineSpacing, dest.y + (lineSpacing * 2));
					text.loadFromText(app_->getRenderer(), Resources::tildes_["¿"] + "Qu" + Resources::tildes_["e"] + " te parece si matas 4 cangrejos y te preparo un cocidito gallego?"
						, app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
					text.render(lineSpacing, dest.y + (lineSpacing * 3));
					break;
				}
			}
		}
		//Cuando se maten todos los enemigos hay que volver a hablar con el npc
		else {
			if (!gm_->isThatMissionPass(missions::gallegaEnProblemas)) gm_->setMissionFinished(missions::gallegaEnProblemas, true);

			Texture text(app_->getRenderer(), Resources::tildes_["¡"] + "Genial!" + Resources::tildes_["¡"] + " Con estos cangrejos es suficiente! Te espero en el barco, as" + Resources::tildes_["i"] + " cuando vuelvas ya estar" +
				Resources::tildes_["a"] + " lista la cena.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);
		}
	}
}

void TextBox::dialogMorty(bool unlock, int num) {
	initDialog();
	Texture text;
	//Di�logo del Morty cuando lo hemos desbloqueado
	if (unlock) {

		if (gm_->isThatMissionPass(missions::papelesSiniestros) && !gm_->isThatRewardUnlocked(missions::papelesSiniestros)) {
			Texture text(app_->getRenderer(), "Hey, toma esta armadura, como muestra de agradecimiento por lo de antes. Yo ya no la necesito.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);
			unlockReward_->setCallBack(unlockMortyReward);
			unlockReward_->draw();
			unlockReward_->update();
		}
		else {
			switch (num) {
			case 0:
				text.loadFromText(app_->getRenderer(), "Eh oye, pues no est" + Resources::tildes_["a"] + " nada mal el barco este ni nada. Viendo como vistes me esperaba algo bastante peor,", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);


				text.loadFromText(app_->getRenderer(), "ya sabes de qu" + Resources::tildes_["e"] + " hablo.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + (lineSpacing * 2));

				text.loadFromText(app_->getRenderer(), "Mira ya que est" + Resources::tildes_["a"] + "s aqu" + Resources::tildes_["i"] + " te explico c" + Resources::tildes_["o"] + "mo acab" + Resources::tildes_["e"] + " en esa isla si quieres.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + (lineSpacing * 3));

				button_->draw();
				button_->update();
				break;
			case 1:
				text.loadFromText(app_->getRenderer(), "En verdad no tiene mucha cosa, yo siempre quise ser panadero, " + Resources::tildes_["¿"] + "sabes ? Hacer baguettes y tal.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);

				text.loadFromText(app_->getRenderer(), "Pero claro, mis padres se pusieron tercos con que saqueara y no me dejaban dinero para la panader" + Resources::tildes_["i"] + "a, ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + (lineSpacing * 2));

				text.loadFromText(app_->getRenderer(), "as" + Resources::tildes_["i"] + " que me acab" + Resources::tildes_["e"] + " " "haciendo pirata como tanto quer" + Resources::tildes_["i"] + "an. ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + (lineSpacing * 3));

				button_->draw();
				button_->update();
				break;
			case 2:

				text.loadFromText(app_->getRenderer(), "Mira t" + Resources::tildes_["u"] + " que voy a mi primer saqueo con el t" + Resources::tildes_["i"] + "tulo de pirata calentito reci" + Resources::tildes_["e"] + "n salido de la uni que", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);

				text.loadFromText(app_->getRenderer(), "en el momento en el que pongo un pi" + Resources::tildes_["e"] + "en la condenada isla pasa a ser, literalmente, condenada.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + (lineSpacing * 2));

				text.loadFromText(app_->getRenderer(), "La maldijeron, y con ella me maldijeron a m" + Resources::tildes_["i"] + " de rebote o algo y aqu" + Resources::tildes_["i"] + " estoy, no muerto.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + (lineSpacing * 3));

				button_->draw();
				button_->update();
				break;

			case 3:

				text.loadFromText(app_->getRenderer(), "Todo porque hacer pan no da dinero, gracias por tanto mam" + Resources::tildes_["a"] + ", muy chulo todo esto la verdad.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);

				text.loadFromText(app_->getRenderer(), "Pero bueno, uno hace lo que puede con su vida, tanto t" + Resources::tildes_["u"] + " como yo, pero yo al menos me", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + (lineSpacing * 2));

				text.loadFromText(app_->getRenderer(), "preocupo un poco m" + Resources::tildes_["a"] + "s por como visto.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + (lineSpacing * 3));

				break;
			}
		}
	}
	//Di�logo del Morty cuando a�n est� bloqueado
	else {
		//Mientras no se hayan matado todos los enemigos
		if (gm_->getCounterEnemiesMission(missions::papelesSiniestros) < gm_->getEnemiesMission(missions::papelesSiniestros)) {
			switch (num) {
			case 0:
				text.loadFromText(app_->getRenderer(), Resources::tildes_["¡"] + "Hostia, que susto!", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);

				text.loadFromText(app_->getRenderer(), "Me muero, me est" + Resources::tildes_["a"] + " dando un infarto, la palmo hoy mismo ya ver" + Resources::tildes_["a"] + "s. ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + (lineSpacing * 2));

				text.loadFromText(app_->getRenderer(), "Ah no espera, que ya estoy muerto, soy un fantasma y eso.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + (lineSpacing * 3));
				button_->draw();
				button_->update();
				break;
			case 1:
				text.loadFromText(app_->getRenderer(), "Es que desde que me maldijeron en este islote alejado de la mano de dios y me quitaron el papel de ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);

				text.loadFromText(app_->getRenderer(), "liar no puedo echarme pitis y estoy de un irritable" + Resources::tildes_["."] + Resources::tildes_["."] + Resources::tildes_["."], app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + (lineSpacing * 2));


				text.loadFromText(app_->getRenderer(), "Mira, hazme el favor y mata a 4 esqueletos de por ah" + Resources::tildes_["i"] + ". Los reconocer" + Resources::tildes_["a"] + "s cuando los veas, est" + Resources::tildes_["a"] + "n en los huesos.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + (lineSpacing * 3));

				button_->draw();
				button_->update();
				break;

			case 2:
				text.loadFromText(app_->getRenderer(), "Luego voy yo, recojo mis papelitos y misi" + Resources::tildes_["o"] + "n cumplida, planazo.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);

				text.loadFromText(app_->getRenderer(), "Pues venga, al tajo, dale", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + (lineSpacing * 2));

				break;

			}
		}
		//Cuando se maten todos los enemigos hay que volver a hablar con el npc
		else {
			if (!gm_->isThatMissionPass(missions::papelesSiniestros)) gm_->setMissionFinished(missions::papelesSiniestros, true);

			text.loadFromText(app_->getRenderer(), "Esa es, buena crack, mira cuanto papelito todo junto gracias a ti. " + Resources::tildes_["¿"] + "Sabes qu" + Resources::tildes_["e"] + "? ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);


			text.loadFromText(app_->getRenderer(), "Me has ca" + Resources::tildes_["i"] + "do bien, voy a subirme a tu barco y hacerte compa" + Resources::tildes_["ñ"] + Resources::tildes_["i"] + "a en tu viaje, quieras o no. ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + (lineSpacing * 2));
			text.loadFromText(app_->getRenderer(), "B" + Resources::tildes_["a"] + "sicamente porque soy incorp" + Resources::tildes_["o"] + "reo, "" no tienes muchas formas de impedirlo seamos sinceros, ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + (lineSpacing * 3));
			text.loadFromText(app_->getRenderer(), Resources::tildes_["¡"] + "as" + Resources::tildes_["i"] + " que nos vemos en el barco, jefa!", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + (lineSpacing * 4));

		}
	}
}

void TextBox::dialogParrot(int dialog) {
	//El loro gerera una frase aleatoria cada vez que se habla con �l
	initDialog();

	if (!gm_->isThatRewardUnlocked(missions::masValePajaroEnMano)) {
		Texture text;
		text.loadFromText(app_->getRenderer(), Resources::tildes_["¡"] + "Pistachines! " + Resources::tildes_["¡"] + "Quiero pistachines!", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
		text.render(lineSpacing, dest.y + lineSpacing);
		text.loadFromText(app_->getRenderer(), "Os he visto y me preguntaba si aqu" + Resources::tildes_["i"] + " podr" + Resources::tildes_["i"] + "a comer pistachines...", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
		text.render(lineSpacing, dest.y + (lineSpacing * 2));

		unlockReward_->setCallBack(unlockParrotReward);
		unlockReward_->draw();
		unlockReward_->update();
	}
	else {
		if (dialog == 0) {
			Texture text(app_->getRenderer(), "Sin duda hay que perderse para hallar destinos inalcanzables, o de lo contrario,", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);
			text.loadFromText(app_->getRenderer(), "todo el mundo sabr" + Resources::tildes_["i"] + "a donde estan.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing * 2);
		}
		else if (dialog == 1) {
			Texture text(app_->getRenderer(), "La vida es cruel, " + Resources::tildes_["¿"] + "por qu" + Resources::tildes_["e"] + " la otra vida iba a ser distinta?", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);
		}
		else if (dialog == 2) {
			Texture text(app_->getRenderer(), "Los muertos cuentan cuentos, lo que pasa es que no los oyes.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);
		}
		else if (dialog == 3) {
			Texture text(app_->getRenderer(), "Al final no importa cuanto huyas, tendr" + Resources::tildes_["a"] + "s que enfrentar tus miedos.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);
		}
		else if (dialog == 4) {
			Texture text(app_->getRenderer(), "Quien te ataca por la espalda sabe que por delante no podr" + Resources::tildes_["a"] + ".", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);
		}
		else if (dialog == 5) {
			Texture text(app_->getRenderer(), "Mmmmm... Pistachines.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);
		}
		else if (dialog == 6) {
			Texture text(app_->getRenderer(), Resources::tildes_["¡"] + "Qu" + Resources::tildes_["e"] + " ricolinos pistachines!, quiero m" + Resources::tildes_["a"] + "s.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);
		}
		else {
			Texture text(app_->getRenderer(), "Si no dejan a nadie con vida, " + Resources::tildes_["¿"] + "qui" + Resources::tildes_["e"] + "n cuenta las historias?", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);
		}
	}
}

void TextBox::dialogSkeleton(bool unlock, int num) {
	initDialog();
	//Di�logo del músico cuando lo hemos desbloqueado
	if (unlock) {
		Texture text;
		if (gm_->isThatMissionPass(missions::laboon) && !gm_->isThatRewardUnlocked(missions::laboon)) {
			text.loadFromText(app_->getRenderer(), "Muchas gracias por ayudarme. Aquello fue como una pesadilla.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);
			text.loadFromText(app_->getRenderer(), "Cuando estaba all" + Resources::tildes_["i"] + " usaba estas pociones para tratar de defenderme de los lobos.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + (lineSpacing * 2));
			text.loadFromText(app_->getRenderer(), "Ya no las necesitar" + Resources::tildes_["e"] + ", son todas tuyas.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + (lineSpacing * 3));

			unlockReward_->setCallBack(unlockCookerReward);
			unlockReward_->draw();
			unlockReward_->update();
		}
		else {
			text.loadFromText(app_->getRenderer(), "Binkusu no sake wo todoke ni yuku yo umikaze kimakase namimakase...", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);
		}
	}
	//Di�logo del músico cuando a�n est� bloqueado
	else {
		//Mientras no se hayan matado todos los enemigos
		if (gm_->getCounterEnemiesMission(missions::laboon) < gm_->getEnemiesMission(missions::laboon)) {
			Texture text;

			if (gm_->getCounterEnemiesMission(missions::laboon) > 0) {
				text.loadFromText(app_->getRenderer(), "Por favor, ay" + Resources::tildes_["u"] + "dame y mata al menos a 5 lobos para que pueda salir de aqu" + Resources::tildes_["i"] + ".", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);
				text.loadFromText(app_->getRenderer(), "Vuelve para avisarme cuando acabes... Me da miedo arriesgarme.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 2);
			}
			else {
				switch (num) {
				case 0:
					text.loadFromText(app_->getRenderer(), Resources::tildes_["¡"] + "Oh, buen d" + Resources::tildes_["i"] + "a, se" + Resources::tildes_["ñ"] + "orita!, aunque en esta isla es algo dif" + Resources::tildes_["i"] + "cil... ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
					text.render(lineSpacing, dest.y + lineSpacing);

					text.loadFromText(app_->getRenderer(), "Sobretodo por esos lobos que patrullan por ah" + Resources::tildes_["i"] + ". En cuanto me ven se lanzan a por mis pobres y viejos huesos.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
					text.render(lineSpacing, dest.y + (lineSpacing * 2));

					text.loadFromText(app_->getRenderer(), "S" + Resources::tildes_["o"] + "lo de pensarlo se me pone la piel de gallina... Aunque bueno, yo no tengo piel, yohohoho", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
					text.render(lineSpacing, dest.y + (lineSpacing * 3));

					button_->draw();
					button_->update();
					break;
				case 1:
					text.loadFromText(app_->getRenderer(), "La verdad es que me encantar" + Resources::tildes_["i"] + "a irme de este sitio, si al menos me ayudaras y mataras a unos 5 lobos,", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
					text.render(lineSpacing, dest.y + (lineSpacing));

					text.loadFromText(app_->getRenderer(), "podr" + Resources::tildes_["i"] + "a salir de aqu" + Resources::tildes_["i"] + " sin problemas.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
					text.render(lineSpacing, dest.y + (lineSpacing * 2));

					text.loadFromText(app_->getRenderer(), "Y si me acoges en tu barco podr" + Resources::tildes_["e"] + " darte de todo lo que dispongo y tocarte buena m" + Resources::tildes_["u"] + "sica.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
					text.render(lineSpacing, dest.y + (lineSpacing * 3));
					break;
				}
			}
		}
		//Cuando se maten todos los enemigos hay que volver a hablar con el npc
		else {
			if (!gm_->isThatMissionPass(missions::laboon)) gm_->setMissionFinished(missions::laboon, true);

			Texture text(app_->getRenderer(), Resources::tildes_["¿"] + "De verdad? " + Resources::tildes_["¡"] + "Menos mal que llegaste a esta isla perdida y me salvaste, siempre te lo agradecer" + Resources::tildes_["e"] + "." , app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);
		}
	}
}

void TextBox::dialogCartographer(bool unlock, int num) {
	initDialog();
	//Di�logo del chef cuando lo hemos desbloqueado
	if (unlock) {
		Texture text;
		if (gm_->isThatMissionPass(missions::arlongPark) && !gm_->isThatRewardUnlocked(missions::arlongPark)) {
			text.loadFromText(app_->getRenderer(), "Gracias por sacarme de aquella espantosa isla. Por el camino me encontr" + Resources::tildes_["e"] , app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);
			text.loadFromText(app_->getRenderer(), "este trabuco, espero que te sea " + Resources::tildes_["u"]+"til", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing*2);
			unlockReward_->setCallBack(unlockNamiReward);
			unlockReward_->draw();
			unlockReward_->update();
		}
		else {
			switch (num) {
			case 0:
				text.loadFromText(app_->getRenderer(), "Una vez servi a alguien como t" + Resources::tildes_["u"] + ", con un sombrero de paja, pero parecido.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);

				button_->draw();
				button_->update();
				break;
			case 1:
				text.loadFromText(app_->getRenderer(), "Contigo me siento segura.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + (lineSpacing));
				break;
			}
		}
	}
	//Di�logo del chef cuando a�n est� bloqueado
	else {
		//Mientras no se hayan matado todos los enemigos
		if (gm_->getCounterEnemiesMission(missions::arlongPark) < gm_->getEnemiesMission(missions::arlongPark)) {
			Texture text;
			switch (num)
			{
			case 0:

				text.loadFromText(app_->getRenderer(), "Tienes cara de buena persona, " + Resources::tildes_["¿"] + "Puedes ayudarme a escapar de esta isla?", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);

				text.loadFromText(app_->getRenderer(), "Cle" + Resources::tildes_["o"] + "n me atrap" + Resources::tildes_["o"] + " por mis conocimientos sobre la cartograf" + Resources::tildes_["i"] + "a, pero conseg" + Resources::tildes_["i"] + " escapar ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + (lineSpacing * 2));

				text.loadFromText(app_->getRenderer(), "en un descuido que tuvo. ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + (lineSpacing * 3));

				button_->draw();
				button_->update();
				break;
			case 1:

				text.loadFromText(app_->getRenderer(), "Sin embargo, sus secuaces no han dejado de perseguirme desde entonces", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);

				text.loadFromText(app_->getRenderer(), Resources::tildes_["¿"] + "Podr" + Resources::tildes_["i"] + "as acabar con ellos? Con unos 4 bastar" + Resources::tildes_["a"] + " ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + (lineSpacing * 2));

				text.loadFromText(app_->getRenderer(), "Si lo logras, me unir" + Resources::tildes_["e"] + " a tu tripulaci" + Resources::tildes_["o"] + "n", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + (lineSpacing * 3));
				button_->draw();
				button_->update();
				break;

			case 2:
				text.loadFromText(app_->getRenderer(), "Seguro que mis conocimientos de navegaci" + Resources::tildes_["o"] + "n te ser" + Resources::tildes_["a"] + "n " + Resources::tildes_["u"] + "tiles", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);

				text.loadFromText(app_->getRenderer(), Resources::tildes_["¡"] + "Venga, vamos a ello! Si lo consigues te dar" + Resources::tildes_["e"] + " adem" + Resources::tildes_["a"] + "s algo que seguro que te ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + (lineSpacing * 2));

				text.loadFromText(app_->getRenderer(), "ser" + Resources::tildes_["a"] + " de mucha utilidad...", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + (lineSpacing * 3));
				break;
			default:
				break;
			}
			
		}
		//Cuando se maten todos los enemigos hay que volver a hablar con el npc
		else {
			if (!gm_->isThatMissionPass(missions::arlongPark)) gm_->setMissionFinished(missions::arlongPark, true);

			Texture text(app_->getRenderer(), "Muchas gracias. No pensaba que iba a salir con vida de esta...", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);

			text.loadFromText(app_->getRenderer(), "Te espero en tu barco, " + Resources::tildes_["¿"] +"Tienes mandarinas all" + Resources::tildes_["i"], app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + (lineSpacing * 2));
		}
	}
}

void TextBox::dialogKraken(bool defeated) {
	initDialog();
	//Al comenzar la batalla
	if (!defeated) {

	}
	//Al derrotar al Kraken
	else {

	}
}

void TextBox::dialogMagordito(bool defeated) {
	initDialog();
	//Al comenzar la batalla
	if (!defeated) {

	}
	//Al derrotar a Magordito
	else {

	}
}

void TextBox::dialogCleon(bool defeated) {
	initDialog();
	//Al comenzar la batalla
	if (!defeated) {

	}
	//Al derrotar a Cle�n
	else {

	}
}
#pragma endregion

#pragma region Descripciones
void TextBox::armorCaribbean() {
	Texture text(app_->getRenderer(), "Armadura Caribbean ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);
	text.loadFromText(app_->getRenderer(), "Esta armadura te permiti" + Resources::tildes_["a"], app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));
	text.loadFromText(app_->getRenderer(), "defanderte mejor de los ataques", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));

}

void TextBox::armorSpooky() {
	Texture text(app_->getRenderer(), "Armadura Spooky", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);
	text.loadFromText(app_->getRenderer(), "Aumenta tu vitalidad y tu defensa", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));
	text.loadFromText(app_->getRenderer(), "con esta espeluznante armadura", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));

}

void TextBox::glovesCaribbean() {
	Texture text(app_->getRenderer(), "Guantes Caribbean ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);
	text.loadFromText(app_->getRenderer(), "Haz tus golpes m" + Resources::tildes_["a"] + "s fuertes", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));
	text.loadFromText(app_->getRenderer(), "y certeros", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));
}

void TextBox::glovesSpooky() {
	Texture text(app_->getRenderer(), "Botas Spooky ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);
	text.loadFromText(app_->getRenderer(), "Golpea a tus enemigos", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));
	text.loadFromText(app_->getRenderer(), "con m" + Resources::tildes_["a"] + "s fuerza y precisi" + Resources::tildes_["o"] + "n", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));
}

void TextBox::bootsCaribbean() {
	Texture text(app_->getRenderer(), "Botas Caribbean", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);
	text.loadFromText(app_->getRenderer(), "Corre todo lo que puedas", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));
	text.loadFromText(app_->getRenderer(), "estas botas no te fallar" + Resources::tildes_["a"] + "n", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));
}

void TextBox::bootsSpooky() {
	Texture text(app_->getRenderer(), "Botas Spooky", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);
	text.loadFromText(app_->getRenderer(), "Ahora podr" + Resources::tildes_["a"] + "s ir mas r" + Resources::tildes_["a"] + "pido", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));
	text.loadFromText(app_->getRenderer(), "perfectas para una huida r" + Resources::tildes_["a"] + "pida", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));
}

void TextBox::swordCaribbean() {
	Texture text(app_->getRenderer(), "Espada Caribbean ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);
	text.loadFromText(app_->getRenderer(), "Con esta espada tus", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));
	text.loadFromText(app_->getRenderer(), "golpes ser" + Resources::tildes_["a"] + "n m" + Resources::tildes_["a"] + "s fuertes", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));

}
void TextBox::swordSpooky() {
	Texture text(app_->getRenderer(), "Espada Spooky ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);
	text.loadFromText(app_->getRenderer(), "Una espada ligera con", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));
	text.loadFromText(app_->getRenderer(), "la que gorpear m" + Resources::tildes_["a"] + "s r" + Resources::tildes_["a"] + "pido", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));
}

void TextBox::saberCaribbean() {
	Texture text(app_->getRenderer(), "Sable Caribbean ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);
	text.loadFromText(app_->getRenderer(), "Una sable pesado ", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));
	text.loadFromText(app_->getRenderer(), "rebanacabezas", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));
}

void TextBox::saberSpooky() {
	Texture text(app_->getRenderer(), "Sable Spooky ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);
	text.loadFromText(app_->getRenderer(), "Una sable resistente ", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));
	text.loadFromText(app_->getRenderer(), "y bien afilado", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));
}

void TextBox::pistolCaribbean() {
	Texture text(app_->getRenderer(), "Pistola Caribbean", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);
	text.loadFromText(app_->getRenderer(), " Realiza disparos m" + Resources::tildes_["a"] + "s r" + Resources::tildes_["a"] + "pidos", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));
	text.loadFromText(app_->getRenderer(), " y certeros", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));
}

void TextBox::pistolSpooky() {
	Texture text(app_->getRenderer(), "Pistola Spooky ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);
	text.loadFromText(app_->getRenderer(), "Dispara m" + Resources::tildes_["a"] + "s lejos, ning" + Resources::tildes_["u"] + "n", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));
	text.loadFromText(app_->getRenderer(), "enemigo fuera de alcance", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));
}

void TextBox::blunderbussCaribbean() {
	Texture text(app_->getRenderer(), "Trabuco Caribbean", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);
	text.loadFromText(app_->getRenderer(), "Lanza varias balas a la vez", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));
	text.loadFromText(app_->getRenderer(), "¡No hay forma de fallar!", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));
}


void TextBox::blunderbussSpooky() {
	Texture text(app_->getRenderer(), "Trabuco Spooky", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);
	text.loadFromText(app_->getRenderer(), "Mata a varios enemigos a la vez", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));
	text.loadFromText(app_->getRenderer(), "Adi" + Resources::tildes_["o"] + "s a los problemas de masas", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));
}

//POCIONES

void TextBox::lifePotion() {
	Texture text(app_->getRenderer(), "Poci" + Resources::tildes_["o"] + "n de vida:", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "Medicina de hierbas divinas que curan las", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

	text.loadFromText(app_->getRenderer(), "heridas regenerando una cantidad de vida.", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));


}

void TextBox::manaPotion() {
	Texture text(app_->getRenderer(), "Poci" + Resources::tildes_["o"] + "n de man" + Resources::tildes_["a"] + ":", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "Agua de mar tratada con magia que regenera", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

	text.loadFromText(app_->getRenderer(), "una cantidad de man" + Resources::tildes_["a"] + ".", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));
}

void TextBox::velocityPotion() {
	Texture text(app_->getRenderer(), "Poci" + Resources::tildes_["o"] + "n de velocidad:", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "Ron mezclado con aceite de trucha que", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

	text.loadFromText(app_->getRenderer(), " aumenta la velocidad de movimiento.", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));

};

void TextBox::damagePotion() {
	Texture text(app_->getRenderer(), "Poci" + Resources::tildes_["o"] + "n de da" + Resources::tildes_["ñ"] + "o:", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "Fluidos de demonio que aumentan", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

	text.loadFromText(app_->getRenderer(), "el da" + Resources::tildes_["ñ"] + "o de tus golpes. ", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));


}

void TextBox::defensePotion() {
	Texture text(app_->getRenderer(), "Poci" + Resources::tildes_["o"] + "n de defensa:", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "Sangre de gorila tratada con alquimia", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

	text.loadFromText(app_->getRenderer(), " que aumenta la resistencia.", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));
}

void TextBox::criticPotion() {
	Texture text(app_->getRenderer(), "Poci" + Resources::tildes_["o"] + "n de cr" + Resources::tildes_["i"] + "tico:", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "Sangre de " + Resources::tildes_["a"] + "guila virgen que aumenta la", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

	text.loadFromText(app_->getRenderer(), " probabilidad de cr" + Resources::tildes_["i"] + "tico", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));


}

void TextBox::Clon()
{
	Texture text(app_->getRenderer(), "Clon: invoca a un ente supremo que ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "atrae a los enemigos cercanos a el.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

	text.loadFromText(app_->getRenderer(), "Parece replicar todo lo que haces ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));

	text.loadFromText(app_->getRenderer(), "desde su posici" + Resources::tildes_["o"] + "n", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 4));

}

void TextBox::LiberationI()
{
	Texture text(app_->getRenderer(), "Liberaci" + Resources::tildes_["o"] + "n I: El clon ataca a distancia y a melee", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "con los stats al 50 % del jugador.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

}

void TextBox::LiberationII()
{
	Texture text(app_->getRenderer(), "Liberaci" + Resources::tildes_["o"] + "n II: El clon ataca a distancia y a melee", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), " con los stats al 100 % del jugador.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));
}

void TextBox::Explosion()
{
	Texture text(app_->getRenderer(), "Explosi" + Resources::tildes_["o"] + "n: causa da" + Resources::tildes_["ñ"] + "o en " + Resources::tildes_["a"] + "rea a los ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "enemigos cercanos al clon. El clon ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

	text.loadFromText(app_->getRenderer(), "desaparece tras su uso.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));

}

void TextBox::Raudo()
{
	Texture text(app_->getRenderer(), "Pistolero Raudo : aumenta la cadencia", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "de disparo del jugador.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

}
void TextBox::GolpeFuerte()
{
	Texture text(app_->getRenderer(), "Golpe Fuerte: carga da" + Resources::tildes_["ñ"] + "o al ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "siguiente ataque b" + Resources::tildes_["a"] + "sico.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

}
void TextBox::Invencible()
{
	Texture text(app_->getRenderer(), "Invencible: aumenta el da" + Resources::tildes_["ñ"] + "o y el cr" + Resources::tildes_["i"] + "tico", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "del jugador de manera permanente.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

}
void TextBox::Rebote()
{
	Texture text(app_->getRenderer(), "Rebote: durante un tiempo los disparos ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), " rebotan un n" + Resources::tildes_["u"] + "mero  limitado de veces ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

	text.loadFromText(app_->getRenderer(), " entre los enemigos cercanos. ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));


}
void TextBox::Perforador()
{
	Texture text(app_->getRenderer(), "Perforador: el siguiente disparo  ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "atraviesa unidades infligiendo da" + Resources::tildes_["ñ"] + "o a ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

	text.loadFromText(app_->getRenderer(), "los enemigos que haya en el recorrido ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));

	text.loadFromText(app_->getRenderer(), "de la bala.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 4));


}
void TextBox::Torbellino()
{
	Texture text(app_->getRenderer(), "Torbellino: realiza un ataque circular ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "infligiendo da" + Resources::tildes_["ñ"] + "o a los enemigos ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

	text.loadFromText(app_->getRenderer(), "que se encuentren cerca.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));

}
#pragma endregion
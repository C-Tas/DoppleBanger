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
#include "Armor.h"

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
	if (GameManager::instance()->getCurrIsland() == Island::Caribbean) {
		GameManager::instance()->setCurrentZone(Zone::CaribeanA);
	}
	else if (GameManager::instance()->getCurrIsland() == Island::Spooky) {
		GameManager::instance()->setCurrentZone(Zone::SpookyA);
	}
	else if (GameManager::instance()->getCurrIsland() == Island::Volcanic) {
		GameManager::instance()->setCurrentZone(Zone::Volcanic);
	}
	//GameManager::instance()->setHudActive(false);
	app->getGameStateMachine()->changeState(new ShipState(app));
}

void TextBox::changeZone(Application* app)
{
	GameManager::instance()->resetIsland();
	static_cast<PlayState*>(app->getCurrState())->changeZone();
}

void TextBox::initDialog() {
	//Generamos la caja donde ir� el texto
	Texture* whiteRect = app_->getTextureManager()->getTexture(Resources::TextureId::TextBox);
	whiteRect->render(dest);

	//Comentario al final de la caja de texto
	Texture pressAnyKey(app_->getRenderer(), "Al" + Resources::tildes_['e'] +"jate para dejar de hablar >>", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x99999999) });
	pressAnyKey.render(app_->getWindowWidth() - pressAnyKey.getWidth() - lineSpacing, app_->getWindowHeight() - pressAnyKey.getHeight() - lineSpacing);
}

void TextBox::initDescription(Point2D pos) {
	//Caja donde se representa el texto de las descripciones
	dest.w = app_->getWindowWidth() / 4;
	dest.h = app_->getWindowHeight() / 7;
	dest.x = pos.getX();
	dest.y = pos.getY();
}

void TextBox::passZoneDialog()
{
	//Generamos la caja donde ir� el texto
	Texture* whiteRect = app_->getTextureManager()->getTexture(Resources::TextureId::TextBox);
	whiteRect->render({ 0,dest.y, dest.w, dest.h });

	dest.x = lineSpacing;
	dest.y = app_->getWindowHeight() - dest.h;

	Texture text(app_->getRenderer(), "Has llegado al final de la zona, " + Resources::tildes_['¿'] +"Deseas continuar?", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
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
			text.loadFromText(app_->getRenderer(), "Te veo verde, " + Resources::tildes_['¿'] + "has visto lo mamad" + Resources::tildes_['i'] + "simo que estoy?, te puedo dar unos consejos.",
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
			text.loadFromText(app_->getRenderer(), "Presionando una " + Resources::tildes_['u'] + "nica vez el click izquierdo sobre un enemigo, puedes mocharlo.",
				app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);
			text.loadFromText(app_->getRenderer(), "Te recomiendo limpiar tu espada despu" + Resources::tildes_['e'] + "s de mochar al susodicho.",
				app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing * 2);
			break;
		case 3:
			switch (num) {
			case 0:
				text.loadFromText(app_->getRenderer(), Resources::tildes_['¿'] + "Has visto que el susodicho te ha dado puntos de haza" + Resources::tildes_['ñ'] + "a?",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);
				text.loadFromText(app_->getRenderer(), "Puedes verlos en la esquina derecha de abajo. Se consiguen al ganar experiencia.",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 2);
				text.loadFromText(app_->getRenderer(), "Abre el menu de habilidades con la 'V' y s" + Resources::tildes_['u'] + "malos a la segunda rama.",
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

				text.loadFromText(app_->getRenderer(), "Utilizar una habilidad te consumir" + Resources::tildes_['a'] + " man" + Resources::tildes_['a'] + ", puedes ver la cantidad que tienes en la barra azul del tim" + Resources::tildes_['o'] + "n.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + (lineSpacing * 3));
				break;
			}
			break;
		case 5:
			switch (num) {
			case 0:
				text.loadFromText(app_->getRenderer(), "Algunas veces encontrar" + Resources::tildes_['a'] + "s tesoros, no lo dudes " + Resources::tildes_['¡'] + Resources::tildes_['¡'] + "m" + Resources::tildes_['o'] + "chalos a todos!!",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);
				text.loadFromText(app_->getRenderer(), "Usa el oro del cofre para comprar una poci" + Resources::tildes_['o'] + "n a ese t" + Resources::tildes_['i'] + "o mas verde que t" + Resources::tildes_['u'] + ".",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 2);
				text.loadFromText(app_->getRenderer(), "Si te sobra algo podr" + Resources::tildes_['i'] + "as comprarme un ron, " + Resources::tildes_['¿'] + "no?",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 3);
				button_->draw();
				button_->update();
				break;
			case 1:
				text.loadFromText(app_->getRenderer(), "Abre el inventario con la tecla 'C' y equ" + Resources::tildes_['i'] + "pala con el bot" + Resources::tildes_['o'] + "n verde.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);

				text.loadFromText(app_->getRenderer(), "Los objetos equipados se usan con los accesos '1' y '2' respectivamente.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + (lineSpacing * 2));

				text.loadFromText(app_->getRenderer(), "Prueba a beberte la poci" + Resources::tildes_['o'] + "n, ver" + Resources::tildes_['a'] + "s como te sube la cantidad de man" + Resources::tildes_['a'] + ".", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + (lineSpacing * 3));
				break;
			}
			break;
		case 6:
			switch (num) {
			case 0:
				text.loadFromText(app_->getRenderer(), "Ten cuidado ah" + Resources::tildes_['i'] + " fuera porque si eres derrotada podr" + Resources::tildes_['e'] + " ir a salvarte",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);
				text.loadFromText(app_->getRenderer(), "pero no podr" + Resources::tildes_['e'] + " recuperar ni el oro ni los objetos que no lleves equipados.",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 2);
				text.loadFromText(app_->getRenderer(), "Y recuerda, siempre puedes confiar en tu anillo, con la tecla 'R' podr" + Resources::tildes_['a'] + "s invocarla.",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing * 3);
				button_->draw();
				button_->update();
				break;
			case 1:
				text.loadFromText(app_->getRenderer(), "Actuar" + Resources::tildes_['a'] + " como diana para los enemigos y disparar" + Resources::tildes_['a'] + " donde t" + Resources::tildes_['u'] + " lo hagas.",
					app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
				text.render(lineSpacing, dest.y + lineSpacing);
				text.loadFromText(app_->getRenderer(), "Adem" + Resources::tildes_['a'] + "s podr" + Resources::tildes_['a'] + "s mejorarla con los puntos de haza" + Resources::tildes_['ñ'] + "a para que tambi" + Resources::tildes_['e'] + "n pueda mochar.",
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
		/*//Viaje a la isla caribe�a
		if (isle == 0) {
			Texture text(app_->getRenderer(), "Frase 1...", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);

			text.loadFromText(app_->getRenderer(), "Frase 2...", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + (lineSpacing * 2));
		}
		//Viaje a la isla fantasmal
		else if (isle == 1) {

		}
		//Viaje a la isla volc�nica
		else if (isle == 2) {

		}
		//Di�logo en el barco
		else {

		}*/
	}

}

void TextBox::dialogMerchant() {
	initDialog();
	Texture text(app_->getRenderer(), "Blablabla", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(lineSpacing, dest.y + lineSpacing);

	shopButton_->draw();
	shopButton_->update();
}

void TextBox::dialogChef(bool unlock, int num) {
	initDialog();
	//Di�logo del chef cuando lo hemos desbloqueado
	if (unlock) {
		Texture text;
		switch (num) {
		case 0:
			text.loadFromText(app_->getRenderer(), "Cocinera desbloqueada, pulse la flechita para seguir hablando", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);

			text.loadFromText(app_->getRenderer(), "o vete para dejar de hablar.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + (lineSpacing * 2));

			button_->draw();
			button_->update();
			break;
		case 1:
			text.loadFromText(app_->getRenderer(), "Besos.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + (lineSpacing));
			break;
		}
	}
	//Di�logo del chef cuando a�n est� bloqueado
	else {
		//Mientras no se hayan matado todos los enemigos
		if (gm_->getCounterEnemiesMission(missions::gallegaEnProblemas) < gm_->getEnemiesMission(missions::gallegaEnProblemas)) {
			Texture text(app_->getRenderer(), "Necesito que mates 4 monos para cocinarte un cocidito gallego. Adem" +
				Resources::tildes_['a'] + "s te podr" + Resources::tildes_['i'] +  "a obsequiar con m" + Resources::tildes_['a'] + "s regalos.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);

			/*text.loadFromText(app_->getRenderer(), "'Gallego en problemas'.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + (lineSpacing * 2));*/
		}
		//Cuando se maten todos los enemigos hay que volver a hablar con el npc
		else {
			if (!gm_->isThatMissionPass(missions::gallegaEnProblemas)) gm_->setCompleteMission(missions::gallegaEnProblemas, true);

			Texture text(app_->getRenderer(), "Muchas gracias por ayudarme. Aqu" + Resources::tildes_['i'] + " est" + Resources::tildes_['a'] +
				" t" + Resources::tildes_['u'] + " recompensa", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);

			/*text.loadFromText(app_->getRenderer(), "'Gallego en problemas', despu" + Resources::tildes_['e'] + "s de esto el chef se a"
				+ Resources::tildes_['ñ'] + "ade a la lista de NPCs desbloquedos.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + (lineSpacing * 2));*/
		}
	}
}

void TextBox::dialogMorty(bool unlock, int num) {
	initDialog();
	//Di�logo del chef cuando lo hemos desbloqueado
	if (unlock) {
		Texture text;
		switch (num) {
		case 0:
			text.loadFromText(app_->getRenderer(), "Gracias por rescatarme de esa isla tan siniestra. Los lobos leprosos me dan escalofr" + 
				Resources::tildes_['i'] + "os.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);

			button_->draw();
			button_->update();
			break;
		case 1:
			text.loadFromText(app_->getRenderer(), "Ahora podr" + Resources::tildes_['e'] + "fumar tranquilo...",
				app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + (lineSpacing));
			break;
		}
	}
	//Di�logo del chef cuando a�n est� bloqueado
	else {
		//Mientras no se hayan matado todos los enemigos
		if (gm_->getCounterEnemiesMission(missions::papelesSiniestros) < gm_->getEnemiesMission(missions::papelesSiniestros)) {
			Texture text(app_->getRenderer(), "Por ahora, como no estoy en mi isla, mata 3 monos para hacer la prueba de desbloquearme. Vuelve cuando lo", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);

			text.loadFromText(app_->getRenderer(), "hayas hecho y te dar" +
				Resources::tildes_['e'] + "recompensas.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + (lineSpacing * 2));

			text.loadFromText(app_->getRenderer(), "Tengo mucho mono. Por favor, date prisa!", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + (lineSpacing * 3));
		}
		//Cuando se maten todos los enemigos hay que volver a hablar con el npc
		else {
			if (!gm_->isThatMissionPass(missions::papelesSiniestros)) gm_->setCompleteMission(missions::papelesSiniestros, true);

			Texture text(app_->getRenderer(), "Muchas gracias. Ahora me unir" + Resources::tildes_['e'] + "a tu tripulacion, as" + Resources::tildes_['i'] + 
				"que hazme hueco.",
				app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);

			text.loadFromText(app_->getRenderer(), "'Ah si! Toma esto como muestra de agradecimiento.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + (lineSpacing * 2));
		}
	}
}

void TextBox::dialogParrot() {
	//El loro gerera una frase aleatoria cada vez que se habla con �l
	int rnd = rand() % 5;
	if (rnd == 0) {

	}
	else if (rnd == 1) {

	}
	else if (rnd == 2) {

	}
	else if (rnd == 3) {

	}
	else if (rnd == 4) {

	}
}

void TextBox::dialogSkeleton(bool unlock) {
	initDialog();
	//Di�logo del esqueleto cuando lo hemos desbloqueado
	if (unlock) {
		Texture text(app_->getRenderer(), "Este lindo esqueletito es una prueba de la generación de un NPC desbloquado. Para ello se han cambiado un poco las", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
		text.render(lineSpacing, dest.y + lineSpacing);

		text.loadFromText(app_->getRenderer(), "colisiones con los NPCs, que podran reajustarse cuando se cambien las im�genes para gestionar que partes se", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
		text.render(lineSpacing, dest.y + (lineSpacing * 2));

		text.loadFromText(app_->getRenderer(), "renderizan por encima y que por debajo del jugador.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
		text.render(lineSpacing, dest.y + (lineSpacing * 3));
	}
	//Di�logo del esqueleto cuando a�n est� bloqueado
	else {

	}
}

void TextBox::dialogCartographer(bool unlock, int num) {
	initDialog();
	//Di�logo del chef cuando lo hemos desbloqueado
	if (unlock) {
		Texture text;
		switch (num) {
		case 0:
			text.loadFromText(app_->getRenderer(), "Una vez servi a alguien como tu, con un sombrero de paja, pero parecido.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
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
	//Di�logo del chef cuando a�n est� bloqueado
	else {
		//Mientras no se hayan matado todos los enemigos
		if (gm_->getCounterEnemiesMission(missions::arlongPark) < gm_->getEnemiesMission(missions::arlongPark)) {
			Texture text(app_->getRenderer(), "Ayudame a acabar con Arlong y sus secuaces. Por ahora tienes que acabar con 3 monos. Cuando", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);

			text.loadFromText(app_->getRenderer(), "hayas acabado vuelve y te dare recompensas.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + (lineSpacing * 2));
		}
		//Cuando se maten todos los enemigos hay que volver a hablar con el npc
		else {
			if (!gm_->isThatMissionPass(missions::arlongPark)) gm_->setCompleteMission(missions::arlongPark, true);

			Texture text(app_->getRenderer(), "Muchas gracias. Ahora me unire a tu tripulacion, asi que hazme hueco.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);

			text.loadFromText(app_->getRenderer(), "'Ah si! Toma esto como muestra de agradecimiento.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
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
	text.loadFromText(app_->getRenderer(), "Esta armadura te permiti" + Resources::tildes_['a'], app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
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
	text.loadFromText(app_->getRenderer(), "Haz tus golpes m" + Resources::tildes_['a'] +"s fuertes", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));
	text.loadFromText(app_->getRenderer(), "y certeros", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));
}

void TextBox::glovesSpooky() {
	Texture text(app_->getRenderer(), "Botas Spooky ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);
	text.loadFromText(app_->getRenderer(), "Golpea a tus enemigos", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));
	text.loadFromText(app_->getRenderer(), "con m" + Resources::tildes_['a'] + "s fuerza y precisi"+ Resources::tildes_['o'] + "n", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));
}

void TextBox::bootsCaribbean() {
	Texture text(app_->getRenderer(), "Botas Caribbean", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);
	text.loadFromText(app_->getRenderer(), "Corre todo lo que puedas", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));
	text.loadFromText(app_->getRenderer(), "estas botas no te fallar" + Resources::tildes_['a'] +"n", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));
}

void TextBox::bootsSpooky() {
	Texture text(app_->getRenderer(), "Botas Spooky", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);
	text.loadFromText(app_->getRenderer(), "Ahora podr"+ Resources::tildes_['a'] +"s ir mas r" + Resources::tildes_['a'] +"pido", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));
	text.loadFromText(app_->getRenderer(), "perfectas para una huida r"+ Resources::tildes_['a'] +"pida", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));
}

void TextBox::swordCaribbean() {
	Texture text(app_->getRenderer(), "Espada Caribbean ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);
	text.loadFromText(app_->getRenderer(), "Con esta espada tus", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));
	text.loadFromText(app_->getRenderer(), "golpes ser" + Resources::tildes_['a'] +"n m" + Resources::tildes_['a'] +"s fuertes", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));
	
}
void TextBox::swordSpooky() {
	Texture text(app_->getRenderer(), "Espada Spooky ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);
	text.loadFromText(app_->getRenderer(), "Una espada ligera con", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));
	text.loadFromText(app_->getRenderer(), "la que gorpear m"+ Resources::tildes_['a'] +"s r"+ Resources::tildes_['a'] +"pido", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
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
	text.loadFromText(app_->getRenderer(), " Realiza disparos m"+ Resources::tildes_['a'] +"s r"+ Resources::tildes_['a'] +"pidos", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));
	text.loadFromText(app_->getRenderer(), " y certeros", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));
}

void TextBox::pistolSpooky() {
	Texture text(app_->getRenderer(), "Pistola Spooky ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);
	text.loadFromText(app_->getRenderer(), "Dispara m"+ Resources::tildes_['a'] +"s lejos, ning"+ Resources::tildes_['u'] +"n", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
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
	text.loadFromText(app_->getRenderer(), "Adi"+ Resources::tildes_['o'] +"s a los problemas de masas", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));
}

//POCIONES

void TextBox::lifePotion() {
	Texture text(app_->getRenderer(), "Poci" + Resources::tildes_['o'] + "n de vida:", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "Medicina de hierbas divinas que curan las", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

	text.loadFromText(app_->getRenderer(), "heridas regenerando una cantidad de vida.", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));

	
}

void TextBox::manaPotion() {
	Texture text(app_->getRenderer(), "Poci" + Resources::tildes_['o'] +  "n de man" + Resources::tildes_['a'] + ":", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "Agua de mar tratada con magia que regenera", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

	text.loadFromText(app_->getRenderer(), "una cantidad de man" + Resources::tildes_['a'] + ".", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));
}

void TextBox::velocityPotion() {
	Texture text(app_->getRenderer(), "Poci" + Resources::tildes_['o'] + "n de velocidad:", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "Ron mezclado con aceite de trucha que", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

	text.loadFromText(app_->getRenderer(), " aumenta la velocidad de movimiento.", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));

};

void TextBox::damagePotion() {
	Texture text(app_->getRenderer(), "Poci" + Resources::tildes_['o'] + "n de da" + Resources::tildes_['ñ'] + "o:", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "Fluidos de demonio que aumentan", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

	text.loadFromText(app_->getRenderer(), "el da"+ Resources::tildes_['ñ'] +"o de tus golpes. ", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));

	
}

void TextBox::defensePotion() {
	Texture text(app_->getRenderer(), "Poci"+ Resources::tildes_['o'] +"n de defensa:", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "Sangre de gorila tratada con alquimia", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

	text.loadFromText(app_->getRenderer(), " que aumenta la resistencia.", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));
}

void TextBox::criticPotion() {
	Texture text(app_->getRenderer(), "Poci"+ Resources::tildes_['o'] +"n de cr"+ Resources::tildes_['i'] +"tico:", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "Sangre de "+ Resources::tildes_['a'] +"guila virgen que aumenta la", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

	text.loadFromText(app_->getRenderer(), " probabilidad de cr"+ Resources::tildes_['i'] +"tico", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
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

	text.loadFromText(app_->getRenderer(), "desde su posici" + Resources::tildes_['o'] + "n", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 4));

}

void TextBox::LiberationI()
{
	Texture text(app_->getRenderer(), "Liberaci" + Resources::tildes_['o'] + "n I: El clon ataca a distancia y a melee", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "con los stats al 50 % del jugador.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

}

void TextBox::LiberationII()
{
	Texture text(app_->getRenderer(), "Liberaci" + Resources::tildes_['o'] + "n II: El clon ataca a distancia y a melee", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), " con los stats al 100 % del jugador.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));
}

void TextBox::Explosion()
{
	Texture text(app_->getRenderer(), "Explosi" + Resources::tildes_['o'] + "n: causa da" + Resources::tildes_['ñ'] + "o en " + Resources::tildes_['a'] + "rea a los ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
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
	Texture text(app_->getRenderer(), "Golpe Fuerte: carga da" + Resources::tildes_['ñ'] + "o al ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "siguiente ataque b" + Resources::tildes_['a'] + "sico.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

}
void TextBox::Invencible()
{
	Texture text(app_->getRenderer(), "Invencible: aumenta el da" + Resources::tildes_['ñ'] + "o y el cr" + Resources::tildes_['i'] + "tico", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "del jugador de manera permanente.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

}
void TextBox::Rebote()
{
	Texture text(app_->getRenderer(), "Rebote: durante un tiempo los disparos ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), " rebotan un n" + Resources::tildes_['u'] + "mero  limitado de veces ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

	text.loadFromText(app_->getRenderer(), " entre los enemigos cercanos. ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));


}
void TextBox::Perforador()
{
	Texture text(app_->getRenderer(), "Perforador: el siguiente disparo  ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "atraviesa unidades infligiendo da" + Resources::tildes_['ñ'] + "o a ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
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

	text.loadFromText(app_->getRenderer(), "infligiendo da" + Resources::tildes_['ñ'] + "o a los enemigos ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

	text.loadFromText(app_->getRenderer(), "que se encuentren cerca.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));

}
#pragma endregion
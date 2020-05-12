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
	app->getAudioManager()->playMusic(Resources::Shop, -1);
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

void TextBox::initDialog() {
	//Generamos la caja donde ir� el texto
	Texture* whiteRect = app_->getTextureManager()->getTexture(Resources::TextureId::TextBox);
	whiteRect->render(dest);

	//Comentario al final de la caja de texto
	Texture pressAnyKey(app_->getRenderer(), "Alejate para dejar de hablar >>", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x99999999) });
	pressAnyKey.render(app_->getWindowWidth() - pressAnyKey.getWidth() - lineSpacing, app_->getWindowHeight() - pressAnyKey.getHeight() - lineSpacing);
}

void TextBox::initDescription(Point2D pos) {
	//Caja donde se representa el texto de las descripciones
	dest.w = app_->getWindowWidth() / 4;
	dest.h = app_->getWindowHeight() / 7;
	dest.x = pos.getX();
	dest.y = pos.getY();
}

#pragma region Dialogos
void TextBox::dialogElderMan() {
	if (!collisionActive_) {
		collisionActive_ = true;
		app_->getAudioManager()->setChannelVolume(80, (int)EFFECT::NPC);
		app_->getAudioManager()->playChannel(Resources::AudioId::VenancioTalk, 0, (int)EFFECT::NPC);
	}
	initDialog();
	skipTutorial_->draw();
	skipTutorial_->update();
	Texture text;
	if (GameManager::instance()->onTutorial()) {
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
			text.loadFromText(app_->getRenderer(), "No todo el mundo necesita un taca-taca para morverse...", 
				app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);
			break;
		case 1:
			text.loadFromText(app_->getRenderer(), "Destruye la botella ",
				app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);
			break;
		case 2:
			text.loadFromText(app_->getRenderer(), "Ataca al dummy con ataques a melee",
				app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);
			break;
		case 3:
			text.loadFromText(app_->getRenderer(), "Usa la habilidad de golpe fuerte",
				app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);
			break;
		case 4:
			text.loadFromText(app_->getRenderer(), "Abre el inventario y vende algo",
				app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);
			break;
		case 5:
			text.loadFromText(app_->getRenderer(), "Saca al clon",
				app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);
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
			Texture text(app_->getRenderer(), "Este es el mensaje que aparece cuando hablamos con el chef mientras no consigamos superar la mision secundaria", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);

			text.loadFromText(app_->getRenderer(), "'Gallego en problemas'.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + (lineSpacing * 2));
		}
		//Cuando se maten todos los enemigos hay que volver a hablar con el npc
		else {
			if (!gm_->isThatMissionPass(missions::gallegaEnProblemas)) gm_->setCompleteMission(missions::gallegaEnProblemas, true);

			Texture text(app_->getRenderer(), "Este es el mensaje que aparece cuando hablamos con el chef cuando hemos conseguido la mision secundaria", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);

			text.loadFromText(app_->getRenderer(), "'Gallego en problemas', despues de esto el chef se a�ade a la lista de NPCs desbloquedos.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + (lineSpacing * 2));
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
			text.loadFromText(app_->getRenderer(), "Gracias por rescatarme de esa isla tan siniestra. Los lobos leprosos me dan escalofrios.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);

			button_->draw();
			button_->update();
			break;
		case 1:
			text.loadFromText(app_->getRenderer(), "Ahora podre fumar tranquilo...", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
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

			text.loadFromText(app_->getRenderer(), "hayas hecho y te dare recompensas.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + (lineSpacing * 2));

			text.loadFromText(app_->getRenderer(), "Tengo mucho mono. Por favor, date prisa!", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + (lineSpacing * 3));
		}
		//Cuando se maten todos los enemigos hay que volver a hablar con el npc
		else {
			if (!gm_->isThatMissionPass(missions::papelesSiniestros)) gm_->setCompleteMission(missions::papelesSiniestros, true);

			Texture text(app_->getRenderer(), "Muchas gracias. Ahora me unire a tu tripulacion, asi que hazme hueco.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
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
}

void TextBox::armorSpooky() {
}

void TextBox::glovesCaribbean() {
}

void TextBox::glovesSpooky() {
}

void TextBox::bootsCaribbean() {
}

void TextBox::bootsSpooky() {
}

void TextBox::swordCaribbean() {
}

void TextBox::swordSpooky() {
}

void TextBox::saberCaribbean() {
}

void TextBox::saberSpooky() {
}

void TextBox::pistolCaribbean() {
}

void TextBox::pistolSpooky() {
}

void TextBox::blunderbussCaribbean() {
}

void TextBox::blunderbussSpooky() {
}

void TextBox::lifePotion() {
	Texture text(app_->getRenderer(), "Poci�n de vida:", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "Medicina de hierbas divinas que curan las", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

	text.loadFromText(app_->getRenderer(), "heridas regenerando una cantidad de vida.", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));

	text.loadFromText(app_->getRenderer(), "Puede contener trazas de frutos secos.", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 4));
}

void TextBox::manaPotion() {
	Texture text(app_->getRenderer(), "Poci�n de man�:", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "Agua de mar tratada con magia que regenera", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

	text.loadFromText(app_->getRenderer(), "una cantidad de man�.", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));
}

void TextBox::velocityPotion() {
	Texture text(app_->getRenderer(), "Poci�n de velocidad:", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "Ron mezclado con aceite de trucha que", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

	text.loadFromText(app_->getRenderer(), "producen hiperactividad, aumentando la", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));

	text.loadFromText(app_->getRenderer(), "velocidad de movimiento.", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 4));
}

void TextBox::damagePotion() {
	Texture text(app_->getRenderer(), "Poci�n de da�o:", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "Fluidos de demonio que fortalecen la", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

	text.loadFromText(app_->getRenderer(), "musculatura haciendo que el que la bebe", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));

	text.loadFromText(app_->getRenderer(), "inflija m�s da�o con sus golpes.", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 4));
}

void TextBox::defensePotion() {
	Texture text(app_->getRenderer(), "Poci�n de defensa:", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "Sangre de gorila tratada con alquimia", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

	text.loadFromText(app_->getRenderer(), "avanzada que aumenta la resistencia.", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));
}

void TextBox::criticPotion() {
	Texture text(app_->getRenderer(), "Poci�n de cr�tico:", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "Sangre de �guila virgen que aumenta la", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

	text.loadFromText(app_->getRenderer(), "precisi�n otorgando mayor probabilidad", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));

	text.loadFromText(app_->getRenderer(), "de cr�tico.", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 4));
}

void TextBox::Clon()
{
	Texture text(app_->getRenderer(), "Clon: invoca a un ente supremo que ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "atrae a los enemigos cercanos a el.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

	text.loadFromText(app_->getRenderer(), "Parece replicar todo lo que haces ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));

	text.loadFromText(app_->getRenderer(), "desde su posicion", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 4));

}

void TextBox::LiberationI()
{
	Texture text(app_->getRenderer(), "Liberacion I: El clon ataca con los stats", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "al 50 % del jugador.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

}

void TextBox::LiberationII()
{
	Texture text(app_->getRenderer(), "Liberacion II: El clon ataca con los ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "stats al 100 % del jugador.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));
}

void TextBox::Explosion()
{
	Texture text(app_->getRenderer(), "Explosion: causa dano en area a los ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
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
	Texture text(app_->getRenderer(), "Golpe Fuerte: carga dano al ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "siguiente ataque basico.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

}
void TextBox::Invencible()
{
	Texture text(app_->getRenderer(), "Invencible: aumenta el dano y el critico", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "del jugador de manera permanente.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

}
void TextBox::Rebote()
{
	Texture text(app_->getRenderer(), "Rebote: durante un tiempo los disparos ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), " rebotan un numero  limitado de veces ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

	text.loadFromText(app_->getRenderer(), " entre los enemigos cercanos. ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));


}
void TextBox::Perforador()
{
	Texture text(app_->getRenderer(), "Perforador: el siguiente disparo  ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "atraviesa unidades infligiendo dano a ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
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

	text.loadFromText(app_->getRenderer(), "infligiendo da�o a los enemigos ", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

	text.loadFromText(app_->getRenderer(), "que se encuentren cerca.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));

}
#pragma endregion
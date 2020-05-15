#include "TextBox.h"
#include "HandleEvents.h"
#include "Resources.h"
#include "GameState.h"
#include "ShopState.h"
#include "Player.h"
#include "SDL_macros.h"
#include "CollisionCtrl.h"

//Cada l�nea de los di�logos/descripciones se tiene que renderizar por separado para poder generar los saltos de l�nea.
//Lo relacionado con textos aparece aqu� y no en Resources para no sobrecargar dicha clase.
//Los NPCs y los bosses se encargan de llamar en su update a su respectivo textBox cuando corresponda,
//y se renderiza hasta que se presione cualquier tecla y se elimine el textBox.
//Cada objeto llama a su correspondiente descripci�n, cuando el estado abierto se lo indique,
//pas�ndo la posici�n en la que se sit�a la descripci�n de dicho estado.

//Callback del mercader para abrir la tienda
void TextBox::goShopState(Application* app)
{
	dynamic_cast<Player*>(GameManager::instance()->getPlayer())->stop();
	app->getGameStateMachine()->pushState(new ShopState(app));
}

void TextBox::nextConversation(Application* app) {
	dynamic_cast<Player*>(app->getGameManager()->getPlayer())->stop();
	CollisionCtrl::instance()->nextConversation();
}

void TextBox::initDialog() {
	//Generamos la caja donde ir� el texto
	Texture* whiteRect = app_->getTextureManager()->getTexture(Resources::TextureId::TextBox);
	whiteRect->render(dest);

	//Comentario al final de la caja de texto
	Texture pressAnyKey(app_->getRenderer(), "Aléjate para dejar de hablar >>", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x99999999) });
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
void TextBox::dialogElderMan(int isle) {
	initDialog();
	dest.x = lineSpacing;
	dest.y = app_->getWindowHeight() - dest.h;

	//Viaje a la isla caribe�a
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
			Texture text(app_->getRenderer(), "Este es el mensaje que aparece cuando hablamos con el chef mientras no consigamos superar la misión secundaria", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);

			text.loadFromText(app_->getRenderer(), "'Gallego en problemas'.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + (lineSpacing * 2));
		}
		//Cuando se maten todos los enemigos hay que volver a hablar con el npc
		else {
			gm_->setCompleteMission(missions::gallegaEnProblemas, true);
			gm_->addInventoryGold(500);
			gm_->setArchievementPoints(gm_->getAchievementPoints() + 1000);

			Texture text(app_->getRenderer(), "Este es el mensaje que aparece cuando hablamos con el chef cuando hemos conseguido la misión secundaria", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + lineSpacing);

			text.loadFromText(app_->getRenderer(), "'Gallego en problemas', después de esto el chef se a�ade a la lista de NPCs desbloquedos.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
			text.render(lineSpacing, dest.y + (lineSpacing * 2));
		}
	}
}

void TextBox::dialogMorty(bool unlock) {
	initDialog();
	//Di�logo de Morty cuando lo hemos desbloqueado
	if (unlock) {

	}
	//Di�logo de Morty cuando a�n est� bloqueado
	else {

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

		text.loadFromText(app_->getRenderer(), "colisiones con los NPCs, que podrán reajustarse cuando se cambien las im�genes para gestionar qué partes se", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
		text.render(lineSpacing, dest.y + (lineSpacing * 2));

		text.loadFromText(app_->getRenderer(), "renderizan por encima y qué por debajo del jugador.", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
		text.render(lineSpacing, dest.y + (lineSpacing * 3));
	}
	//Di�logo del esqueleto cuando a�n est� bloqueado
	else {

	}
}

void TextBox::dialogCartographer(bool unlock) {
	initDialog();
	//Di�logo de la cart�grafa cuando la hemos desbloqueado
	if (unlock) {

	}
	//Di�logo de la cart�grafa cuando a�n est� bloqueada
	else {

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
	Texture text(app_->getRenderer(), "Poci"+ Resources::tildes_['o'] +"n de vida:", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "Medicina de hierbas divinas que curan las", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

	text.loadFromText(app_->getRenderer(), "heridas regenerando una cantidad de vida.", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));

	
}

void TextBox::manaPotion() {
	Texture text(app_->getRenderer(), "Poci" + Resources::tildes_['o'] + "n de man"+ Resources::tildes_['a'] +" :", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "Agua de mar tratada con magia que regenera", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

	text.loadFromText(app_->getRenderer(), "una cantidad de man" + Resources::tildes_['a'], app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));
}

void TextBox::velocityPotion() {
	Texture text(app_->getRenderer(), "Poci" + Resources::tildes_['o'] + "n de velocidad", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + lineSpacing);

	text.loadFromText(app_->getRenderer(), "Ron mezclado con aceite de trucha que", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 2));

	text.loadFromText(app_->getRenderer(), " aumenta la velocidad de movimiento.", app_->getFontManager()->getFont(Resources::FontId::RETROSM), { COLOR(0x00000000) });
	text.render(dest.x + lineSpacing, dest.y + (lineSpacing * 3));

};

void TextBox::damagePotion() {
	Texture text(app_->getRenderer(), "Poci" + Resources::tildes_['o'] + "n de da"+ Resources::tildes_['ñ'] +"o", app_->getFontManager()->getFont(Resources::FontId::RETRO), { COLOR(0x00000000) });
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
#include "MagorditoState.h"
#include "Magordito.h"

void MagorditoState::initState()
{
	//Borramos la lista de objetos del CollisionCtrl
	collisionCtrl_->clearList();
	gm_->setOnShip(false);

	//Magordito
	Magordito* magordito = new Magordito(app_, Vector2D(W_WIN / 2, H_WIN / 2), Vector2D(W_MAGORDITO, H_MAGORDITO));
	addEnemy(magordito);

	Altar* altar = new Altar(app_, Vector2D(W_WIN / 2, 0), scaleAltar, 4);
	addRenderUpdateLists(altar);
	altar->createMobs(this);

	altar = altar = new Altar(app_, Vector2D(W_WIN / 4, H_WIN / 4), scaleAltar, 4);
	addRenderUpdateLists(altar);
	altar->createMobs(this);

	altar = altar = new Altar(app_, Vector2D(W_WIN * 3 / 4, H_WIN / 4), scaleAltar, 4);
	addRenderUpdateLists(altar);
	altar->createMobs(this);

	altar = altar = new Altar(app_, Vector2D(W_WIN / 4, H_WIN * 3 / 4), scaleAltar, 4);
	addRenderUpdateLists(altar);
	altar->createMobs(this);

	altar = altar = new Altar(app_, Vector2D(W_WIN * 3 / 4, H_WIN * 3 / 4), scaleAltar, 4);
	addRenderUpdateLists(altar);
	altar->createMobs(this);

	////Siempre se anyade el ultimo para que se renderice por encima de los demas objetos
	playerEntry_ = Vector2D((W_WIN - W_PLAYER * 4), ((H_WIN * 3 / 4) - H_PLAYER));
	player_ = new Player(app_, playerEntry_, Vector2D(W_PLAYER, H_PLAYER));
	player_->setScale(Vector2D(W_PLAYER, H_PLAYER));

	GameManager::instance()->setPlayer(player_);
	addRenderUpdateLists(player_);

	//Inicializamos el hud
	hud_ = new HUD(app_);
	player_->initSkills();

	//Añadimos el hud a objetos a renderizar
	addRenderUpdateLists(hud_);
}
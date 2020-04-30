#pragma once
#include "Collider.h"
using namespace std;

enum class ObstacleType {
	Block, 
	Plane, 
	BorderUR, 
	BorderUL, 
	BorderDR, 
	BorderDL,
	Tomb1,
	Tomb2,
	LittleRock,
	BigRock,
	Skull,

	_undefined,

};

class Obstacle : public Collider {
public:
	Obstacle(Application* app, SDL_Rect collisionArea, Texture* texture, Point2D pos, Vector2D scale) :
		Collider(app, pos, scale) {
		collisionArea_ = collisionArea;
		texture_ = texture;
	};
	virtual ~Obstacle() {};

	virtual void initObject() {};
	virtual void onCollider() {};	//No hace nada, porque lo hacen directamente las otras clases que colisionan (P.ej player)
	virtual bool update() { return false; };
	//Se redefine el m�todo draw para que tenga en cuenta la c�mara
	const virtual void draw() {
		SDL_Rect dest = getDestiny(); dest.x = dest.x - Camera::instance()->getCamera().getX(); dest.y = dest.y - Camera::instance()->getCamera().getY();
		if (currAnim_.numberFrames_ <= 0) texture_->render(dest, SDL_FLIP_NONE);
		else texture_->render(dest, frame_);
	};

	///<summary>Devuelve si el obst�culo en concreto es una pared o no</summary>
	bool isTileWall() { return isWall_; };
	///<summary>M�todo para cambiar si el obst�culo es una pared o no</summary>
	void setTileAsWall(bool isWall = true) { isWall_ = isWall; }
	///<summary>M�todo que ajusta el collider del obs�culo seg�n el tipo de tile que sea</summary>
	void adjustTileCollider();
	//<summary>M�todo para asignar el tipo type como tipo de obstaculo</summary>
	void setObstacleType(ObstacleType type) { type_ = type; };
	void setGid(int newGid) { gid = newGid; };

private:
	bool isWall_ = false;
	int gid = 0;
	ObstacleType type_ = ObstacleType::_undefined;
};
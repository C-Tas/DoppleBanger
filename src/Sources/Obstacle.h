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
	//Se redefine el método draw para que tenga en cuenta la cámara
	const virtual void draw() {
		SDL_Rect dest = getDestiny(); dest.x = dest.x - Camera::instance()->getCamera().getX(); dest.y = dest.y - Camera::instance()->getCamera().getY();
		if (currAnim_.numberFrames_ <= 0) texture_->render(dest, SDL_FLIP_NONE);
		else texture_->render(dest, frame_);
	};

	///<summary>Devuelve si el obstáculo en concreto es una pared o no</summary>
	bool isTileWall() { return isWall_; };
	///<summary>Método para cambiar si el obstáculo es una pared o no</summary>
	void setTileAsWall(bool isWall = true) { isWall_ = isWall; }
	///<summary>Método que ajusta el collider del obsáculo según el tipo de tile que sea</summary>
	void adjustTileCollider();
	//<summary>Método para asignar el tipo type como tipo de obstaculo</summary>
	void setObstacleType(ObstacleType type) { type_ = type; };
	void setGid(int newGid) { gid = newGid; };

private:
	bool isWall_ = false;
	int gid = 0;
	ObstacleType type_ = ObstacleType::_undefined;
};
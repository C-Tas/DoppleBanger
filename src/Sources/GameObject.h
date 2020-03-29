#pragma once
#include "Application.h"
#include "Vector2D.h"
#include "SDL.h"
#include "checkML.h"
#include "Resources.h"

using namespace std;
using uint = unsigned int;

class GameObject
{
protected:
	Vector2D pos_, scale_;
	Application* app_ = nullptr;
	//<summary>constructor vac�o</summary>
	GameObject() : pos_({ 0,0 }), scale_(0, 0) {};
	//<summary>constructor con par�metros</summary>
	GameObject(Application* app, Vector2D pos, Vector2D scale)
		: app_(app), pos_(pos), scale_(scale) {};
	//<summary>constructor por cop�a</summary>
	GameObject(const GameObject& other)
		: pos_(other.pos_), app_(other.app_), scale_(other.scale_) {};
	//<summary>constructor por movimiento</summary>
	GameObject(const GameObject&& other)noexcept
		: pos_(other.pos_), app_(other.app_), scale_(other.scale_) {};
	virtual void initObject() = 0;
public:
	//<summary>umetodo abstracto que lleva la logica del juego</summary>
	virtual bool update() = 0;
#pragma region Getters
	//<summary>Devuelve la posicon del objeto</summary>
	inline const Vector2D& getPos() const { return pos_; }
	//<summary>Devuelve la escala del objeto</summary>
	inline const Vector2D& getScale()const { return scale_; }
	//<summary>Devuelve la X de la pos del objeto</summary>
	inline const double getPosX() { return pos_.getX(); }
	//<summary>Devuelve la Y de la pos del objeto</summary>
	inline const double getPosY() { return pos_.getY(); }
	//<summary>Devuelve la X de la pos del objeto</summary>
	inline const double getScaleX() { return scale_.getX(); }
	//<summary>Devuelve la Y de la pos del objeto</summary>
	inline const double getScaleY() { return scale_.getY(); }
	//Dada una posición le resta el offset del objeto que invoca el método
	//de tal forma que si este se mueve a la dicha posición queda centrado en ella
	Vector2D getCenter(Vector2D pos)
	{
		Vector2D center;
		center.setX(pos.getX() - (scale_.getX() / 2));
		center.setY(pos.getY() - (scale_.getY() / 2));
		return center;
	}
#pragma endregion

#pragma region Setter
	//<summary>Setea la X de la pos del objeto</summary>
	inline void setPosX(double x) { pos_.setX(x); }
	//<summary>Setea la Y de la pos del objeto</summary>
	inline void setPosY(double y) { pos_.setY(y); }
	//<summary>Setea la pos del objeto</summary>
	inline void setPos(Vector2D newPos) { pos_.setVec(newPos); }
	//<summary>Devuelve la X de la escala del objeto</summary>
	inline void setScaleX(double x) { scale_.setX(x); }
	//<summary>Setea la Y de la escala del objeto</summary>
	inline void setScaleY(double y) { scale_.setY(y); }
	//<summary>Setea la escala de la pos del objeto</summary>
	inline void setScale(Vector2D newPos) { scale_.setVec(newPos); }
#pragma endregion
	virtual ~GameObject() {};
};
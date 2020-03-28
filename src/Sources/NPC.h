#pragma once
#include "Actor.h"
class NPC : public Actor
{
public:
	/*//<summary>Constructor tanto por defecto como por contenido si no se le pasan valores ser�n los puestos, si se le pasan valores los editara</summary>
	NPC(Application* app = nullptr, Texture* texture = nullptr, Vector2D pos = { 0,0 }, Vector2D scale = { 0,0 }, SDL_Rect collisionArea = { 0,0,0,0 }, SDL_Rect frame = {0,0,0,0},int numberFrames=0) :Actor(app, texture, pos, scale, collisionArea,frame,numberFrames) {};
	//<summary>Constructor por copia</summary>
	NPC(NPC& other) :Actor(other.app_, other.texture_, other.pos_, other.scale_, other.collisionArea_) {};
	//<summary>Constructor por movimiento<summary>
	NPC(NPC&& other)noexcept :Actor(other.app_, other.texture_, other.pos_, other.scale_, other.collisionArea_) {};
	//<summary>Destructor</summary>
	virtual~NPC() {};*/
};


#include "Obstacle.h"
#include <cmath>

void Obstacle::adjustTileCollider()
{
	switch (type_)
	{
        case ObstacleType::Block: {
            posCollision_ = Vector2D(0, scale_.getY() / 4);
            scaleCollision_ = Vector2D((scale_.getX()), 3*scale_.getY()/4);
            break; 
        }
        case ObstacleType::Plane: {
            posCollision_ = Vector2D(scale_.getX() / 3, scale_.getY() / 3);
            scaleCollision_ = Vector2D(scale_.getX() / 3, scale_.getY() / 3);
            break; 
        }
        case ObstacleType::BorderUR: {
            posCollision_ = Vector2D(4 * scale_.getX() / 7, 5* (scale_.getY() / 7));
            collisionRot_=  30;
            double aux = sqrt(pow((scale_.getY() / 4), 2) + pow((scale_.getX() / 2), 2));
            scaleCollision_ = Vector2D(9*(aux/10), aux / 2);
            break; 
        }
        case ObstacleType::BorderUL: {
            posCollision_ = Vector2D((scale_.getX() / 10), (6 * (scale_.getY() / 7))-20);
            collisionRot_ = -27;
            double aux = sqrt(pow((scale_.getY() / 4), 2) + pow((scale_.getX() / 2), 2));
            scaleCollision_ = Vector2D(aux, aux / 2);
            break; 
        }

        case ObstacleType::BorderDR: {
            posCollision_ = Vector2D(0, (scale_.getY() / 4));
            collisionRot_ = -27;
            double aux = sqrt(pow((scale_.getY() / 4), 2) + pow((scale_.getX() / 2), 2));
            scaleCollision_ = Vector2D(aux, aux / 2);
            break; 
        }
        case ObstacleType::BorderDL: {
            posCollision_ = Vector2D((scale_.getX() / 2), scale_.getY()/6);
            collisionRot_ = 30;
            double aux = sqrt(pow((scale_.getY() / 4), 2) + pow((scale_.getX() / 2), 2));
            scaleCollision_ = Vector2D(aux, aux / 2);
            break; 
        }
        case ObstacleType::Tomb1: {
            posCollision_ = Vector2D(0, scale_.getY() / 4);
            scaleCollision_ = Vector2D(2 * scale_.getX() / 3, 3 * scale_.getX() / 4);
            break;
        }
        case ObstacleType::Tomb2: {
            posCollision_ = Vector2D(scale_.getX() / 6, scale_.getY() / 4);
            scaleCollision_ = Vector2D(scale_.getX() / 2, 3 * scale_.getX() / 4);
            break;
        }
        case ObstacleType::LittleRock: {
            posCollision_ = Vector2D(0, 4*scale_.getY() / 5);
            scaleCollision_ = Vector2D(2 * scale_.getX() / 3, scale_.getY()/2);
            break;
        }
        case ObstacleType::BigRock:{
            posCollision_ = Vector2D(0, scale_.getY() / 3);
            scaleCollision_ = Vector2D(3* scale_.getX() / 4, 2*scale_.getY() / 3);
            break;
        }
        case ObstacleType::Skull: {
            posCollision_ = Vector2D(scale_.getX()/10, scale_.getY() / 2);
            scaleCollision_ = Vector2D(scale_.getX() / 2, 2*scale_.getY()/3 );
            break;
        }
        case ObstacleType::Bush1: {
            posCollision_ = Vector2D(scale_.getX() / 4, scale_.getY() / 4);
            scaleCollision_ = Vector2D(scale_.getX() / 2,  scale_.getY() / 2);
            break;
        }
        case ObstacleType::Bush2: {
            posCollision_ = Vector2D(scale_.getX() / 4, scale_.getY() /8);
            scaleCollision_ = Vector2D(2*scale_.getX() / 3, scale_.getY());
            break;
        }
        case ObstacleType::Trunk: {
            posCollision_ = Vector2D(scale_.getX() /3, 0);
            scaleCollision_ = Vector2D(scale_.getX() /4, 1.5*scale_.getY());
            break;
        }
        case ObstacleType::_undefined: {
            collisionArea_ = { 0,0,0,0 };
            posCollision_ = Vector2D(0, 0);
            scaleCollision_ = Vector2D(0, 0);
            break; 
        }
        default: {
            collisionArea_ = { 0,0,0,0 };
            posCollision_ = Vector2D(0, 0);
            scaleCollision_ = Vector2D(0, 0);
            break; 
        }
	}
}

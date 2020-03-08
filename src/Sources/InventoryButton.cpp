#include "InventoryButton.h"

InventoryButton::InventoryButton(Texture* texture, Vector2D pos, Vector2D scale, interactuable* ob, CallBackOnClick* callBack): Button(texture,pos,scale,callBack),object_(ob){
}

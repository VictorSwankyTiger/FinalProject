#ifndef Missile_H_INCLUDED
#define Missile_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [Missile object]
*/
typedef struct _Missile
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    int v;             // the velocity of projectile
    int cnt;
    Elements* player;
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} Missile;
Elements *New_Missile(int label, int x, int y);
void Missile_update(Elements *self);
void Missile_interact(Elements *self, Elements *tar);
void Missile_draw(Elements *self);
void Missile_destory(Elements *self);
void _Missile_update_position(Elements *self, int dx, int dy);
#endif

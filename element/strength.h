#ifndef Strength_H_INCLUDED
#define Strength_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [Strength object]
*/
typedef struct _Strength
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    int v;             // the velocity of projectile
    int cnt;
    Elements *player;
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} Strength;
Elements *New_Strength(int label, int x, int y);
void Strength_update(Elements *self);
void Strength_interact(Elements *self, Elements *tar);
void Strength_draw(Elements *self);
void Strength_destory(Elements *self);
void _Strength_update_position(Elements *self, int dx, int dy);
#endif

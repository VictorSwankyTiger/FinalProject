#ifndef Buff_H_INCLUDED
#define Buff_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [Buff object]
*/
typedef struct _Buff
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    int v;             // the velocity of projectile
    int cnt;
    Elements *player;
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} Buff;
Elements *New_Buff(int label, int x, int y);
void Buff_update(Elements *self);
void Buff_interact(Elements *self, Elements *tar);
void Buff_draw(Elements *self);
void Buff_destory(Elements *self);
void _Buff_update_position(Elements *self, int dx, int dy);
#endif

#ifndef Flame_H_INCLUDED
#define Flame_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [Flame object]
*/
typedef struct _Flame
{
    int x, y;          // the position of image
    int i, j;
    int sync;
    int width, height; // the width and height of image
    // int v;             // the velocity of flame
    int direction;
    int length;
    int time_cnt;
    int damge;
    bool created;
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} Flame;
Elements *New_Flame(int label, int x, int y, int direction, int length, int i, int j, int sync);
void Flame_update(Elements *self);
void Flame_interact(Elements *self, Elements *tar);
void Flame_draw(Elements *self);
void Flame_destory(Elements *self);
void _Flame_update_position(Elements *self, int dx, int dy);
#endif

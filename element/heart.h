#ifndef Heart_H_INCLUDED
#define Heart_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [Heart object]
*/
typedef struct _Heart
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    int v;             // the velocity of projectile
    int cnt;
    Elements *player;
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} Heart;
Elements *New_Heart(int label, int x, int y);
void Heart_update(Elements *self);
void Heart_interact(Elements *self, Elements *tar);
void Heart_draw(Elements *self);
void Heart_destory(Elements *self);
void _Heart_update_position(Elements *self, int dx, int dy);
#endif

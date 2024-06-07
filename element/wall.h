#ifndef Wall_H_INCLUDED
#define Wall_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [Wall object]
*/
typedef struct _Wall
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
} Wall;
Elements *New_Wall(int label, int x, int y);
void Wall_update(Elements *self);
void Wall_interact(Elements *self, Elements *tar);
void Wall_draw(Elements *self);
void Wall_destory(Elements *self);
void _Wall_update_position(Elements *self, int dx, int dy);
#endif

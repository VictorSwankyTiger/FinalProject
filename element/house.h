#ifndef House_H_INCLUDED
#define House_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [House object]
*/
typedef struct _House
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
} House;
Elements *New_House(int label, int x, int y);
void House_update(Elements *self);
void House_interact(Elements *self, Elements *tar);
void House_draw(Elements *self);
void House_destory(Elements *self);
void _House_update_position(Elements *self, int dx, int dy);
#endif

#ifndef Snow_H_INCLUDED
#define Snow_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [Snow object]
*/
typedef struct _Snow
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    int v;             // the velocity of projectile
    int cnt;
    Elements *player;
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} Snow;
Elements *New_Snow(int label, int x, int y);
void Snow_update(Elements *self);
void Snow_interact(Elements *self, Elements *tar);
void Snow_draw(Elements *self);
void Snow_destory(Elements *self);
void _Snow_update_position(Elements *self, int dx, int dy);
#endif

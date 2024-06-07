#ifndef Snow_bullet_H_INCLUDED
#define Snow_bullet_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [Snow_bullet object]
*/
typedef struct _Snow_bullet
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    int v;             // the velocity of Snow_bullet
    int direction;
    int time_cnt;
    bool created;
    int length;
    Elements *player;
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} Snow_bullet;
Elements *New_Snow_bullet(int label, int x, int y, int direction, Elements *player,int length);
void Snow_bullet_update(Elements *self);
void Snow_bullet_interact(Elements *self, Elements *tar);
void Snow_bullet_draw(Elements *self);
void Snow_bullet_destory(Elements *self);
void _Snow_bullet_update_position(Elements *self, int dx, int dy);
#endif

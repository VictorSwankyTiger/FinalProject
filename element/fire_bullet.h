#ifndef Fire_bullet_H_INCLUDED
#define Fire_bullet_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [Fire_bullet object]
*/
typedef struct _Fire_bullet
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    int v;             // the velocity of Fire_bullet
    int direction;
    int time_cnt;
    bool created;
    int length;
    Elements *player;
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} Fire_bullet;
Elements *New_Fire_bullet(int label, int x, int y, int direction, Elements *player,int length);
void Fire_bullet_update(Elements *self);
void Fire_bullet_interact(Elements *self, Elements *tar);
void Fire_bullet_draw(Elements *self);
void Fire_bullet_destory(Elements *self);
void _Fire_bullet_update_position(Elements *self, int dx, int dy);
#endif

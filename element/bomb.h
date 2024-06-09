#ifndef Bomb_H_INCLUDED
#define Bomb_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [Bomb object]
*/
typedef struct _Bomb
{
    int x, y;          // the position of image
    int i, j;
    int width, height; // the width and height of image
    int v;             // the velocity of projectile
    int cnt;
    Elements *player;
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} Bomb;
Elements *New_Bomb(int label, int x, int y, Elements *player, int i, int j);
void Bomb_update(Elements *self);
void Bomb_interact(Elements *self, Elements *tar);
void Bomb_draw(Elements *self);
void Bomb_destory(Elements *self);
void _Bomb_update_position(Elements *self, int dx, int dy);
#endif

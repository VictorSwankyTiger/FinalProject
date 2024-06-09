#ifndef Missile_bullet_H_INCLUDED
#define Missile_bullet_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [Missile_bullet object]
*/
typedef struct _Missile_bullet
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    int v;             // the velocity of Missile_bullet
    int direction;
    int time_cnt;
    bool created;
    int length;
    Elements *player;
    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    ALLEGRO_BITMAP *img;
    ALLEGRO_BITMAP *img1;
    ALLEGRO_BITMAP *img2;
    ALLEGRO_BITMAP *img3;
    Shape *hitbox; // the hitbox of object
} Missile_bullet;
Elements *New_Missile_bullet(int label, int x, int y, int direction, Elements *player,int length);
void Missile_bullet_update(Elements *self);
void Missile_bullet_interact(Elements *self, Elements *tar);
void Missile_bullet_draw(Elements *self);
void Missile_bullet_destory(Elements *self);
void _Missile_bullet_update_position(Elements *self, int dx, int dy);
#endif

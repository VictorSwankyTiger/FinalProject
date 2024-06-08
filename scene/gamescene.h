#ifndef GAMESCENE_H_INCLUDED
#define GAMESCENE_H_INCLUDED
#include "scene.h"
#include "../element/element.h"
#include "../element/charater.h"
#include "../element/charater2.h"
#include "../element/charater1.h"
#include "../element/floor.h"
#include "../element/teleport.h"
#include "../element/tree.h"
#include "../element/projectile.h"
#include "../element/fire.h"
#include "../element/house.h"
#include "../element/missile.h"
#include "../element/snow.h"
#include "../element/snow_bullet.h"
#include "../element/fire_bullet.h"
#include "../element/missile_bullet.h"



#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [game scene object]
*/
typedef enum EleType
{
    Floor_L,
    Teleport_L,
    Tree_L,
    Wall_L,
    House_L,
    Bomb_L,
    Flame_L,
    Fire_L,
    Snow_L,
    Missile_L,
    Fire_bullet_L,
    Snow_bullet_L,
    Missile_bullet_L,
    Character_L,
    Character2_L,
    Character1_L,
    Projectile_L
} EleType;
typedef struct _GameScene
{
    ALLEGRO_BITMAP *background;
    ALLEGRO_FONT *font;

    int map_data[14][15];
    int x;
    int y;
    int map_x;
    int map_y;
} GameScene;
Scene *New_GameScene(int label);
void game_scene_load_map(Scene *self);
void game_scene_register_map(Scene *self);
void game_scene_update(Scene *self);
void game_scene_draw(Scene *self);
void game_scene_destroy(Scene *self);

#endif

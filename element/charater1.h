#ifndef CHARATER1_H_INCLUDED
#define CHARATER1_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_ttf.h>

#include "element.h"
#include "../shapes/Shape.h"
#include "../algif5/src/algif.h"
#include <stdbool.h>

/*
   [Character1 object]
*/
/*
typedef enum Character1Type
{
    STOP = 0,
    MOVE,
    ATK
} Character1Type;
*/
typedef struct _Character1
{
    int x, y;
    int i,j;                        // position on the map
    int width, height;              // the width and height of image
    int move_cnt, move_limit;
    int time_cnt;                   // pause second can't move
    int bomb_cnt, bomb_limit;
    int attack_cnt, attack_limit;
    int strong_cnt, strong_limit;
    int direction;
    int live;
    int power;
    bool dir;                       // true: face to right, false: face to left
    int state;                      // the state of Character1
    int obj_state;                  // the state of recording what object Character1 grab
    ALGIF_ANIMATION *gif_status[8]; // gif for each state. 0: stop, 1: move, 2:attack
    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    
    int anime;      // counting the time of animation
    int anime_time; // indicate how long the animation
    bool new_proj;
    bool snow;      //Get Snow
    bool missile;   //Get missile
    bool fire;      //Get fire
    enum ATKMOD atk_mod;   //choose atk version
    Shape *hitbox; // the hitbox of object
    ALLEGRO_FONT *font;
} Character1;
Elements *New_Character1(int label, int x, int y,int i,int j);
void _Character1_update_position(Elements *self, int dx, int dy);
void Character1_update(Elements *self);
void Character1_interact(Elements *self, Elements *target);
void Character1_draw(Elements *self);
void Character1_destory(Elements *self);

#endif

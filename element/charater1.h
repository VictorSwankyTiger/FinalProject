#ifndef CHARATER1_H_INCLUDED
#define CHARATER1_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

#include "element.h"
#include "../shapes/Shape.h"
#include "../algif5/src/algif.h"
#include <stdbool.h>

/*
   [character object]
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
    int width, height;              // the width and height of image
    int move_cnt, move_limit;
    int bomb_cnt, bomb_limit;
    int direction;
    int live;
    bool dir;                       // true: face to right, false: face to left
    int state;                      // the state of character
    int obj_state;                  // the state of recording what object character grab
    ALGIF_ANIMATION *gif_status[3]; // gif for each state. 0: stop, 1: move, 2:attack
    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    int anime;      // counting the time of animation
    int anime_time; // indicate how long the animation
    bool snow;      //Get Snow
    bool missile;   //Get missile
    bool fire;      //Get fire
    enum ATKMOD atk_mod;
    bool new_proj;
    Shape *hitbox; // the hitbox of object
    ALLEGRO_FONT *font;

} Character1;
Elements *New_Character1(int label, int x, int y);
void _Character1_update_position(Elements *self, int dx, int dy);
void Character1_update(Elements *self);
void Character1_interact(Elements *self, Elements *target);
void Character1_draw(Elements *self);
void Character1_destory(Elements *self);

#endif

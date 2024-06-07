#ifndef CHARATER2_H_INCLUDED
#define CHARATER2_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include "element.h"
#include "../shapes/Shape.h"
#include "../algif5/src/algif.h"
#include <stdbool.h>

/*
   [character object]
*/
/*
typedef enum Character2Type
{
    STOP = 0,
    MOVE,
    ATK
} Character2Type;
*/
typedef struct _Character2
{
    int x, y;
    int width, height;              // the width and height of image
    bool dir;                       // true: face to right, false: face to left
    int state;                      // the state of character
    int obj_state;                  // the state of recording what object character grab
    ALGIF_ANIMATION *gif_status[3]; // gif for each state. 0: stop, 1: move, 2:attack
    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    int anime;      // counting the time of animation
    int anime_time; // indicate how long the animation
    bool new_proj;
    bool snow;      //Get Snow
    bool missile;   //Get missile
    bool fire;      //Get fire
    Shape *hitbox; // the hitbox of object
} Character2;
Elements *New_Character2(int label);
void _Character2_update_position(Elements *self, int dx, int dy);
void Character2_update(Elements *self);
void Character2_interact(Elements *self, Elements *target);
void Character2_draw(Elements *self);
void Character2_destory(Elements *self);

#endif

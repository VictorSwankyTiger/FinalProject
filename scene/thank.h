#ifndef GAMEOVER1_H_INCLUDED
#define GAMEOVER1_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [Gameover1 object]
*/
typedef struct _Gameover1
{
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    ALLEGRO_BITMAP *background;
    int title_x, title_y;
} Gameover1;
Scene *New_Gameover1(int label);
void gameover1_update(Scene *self);
void gameover1_draw(Scene *self);
void gameover1_destroy(Scene *self);

#endif

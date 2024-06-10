#ifndef Thank_H_INCLUDED
#define Thank_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [Thank object]
*/
typedef struct _Thank
{
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    ALLEGRO_BITMAP *background;
    int title_x, title_y;
} Thank;
Scene *New_Thank(int label);
void Thank_update(Scene *self);
void Thank_draw(Scene *self);
void Thank_destroy(Scene *self);

#endif

#ifndef Mode_H_INCLUDED
#define Mode_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [Mode object]
*/
typedef struct _Mode
{
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    ALLEGRO_BITMAP *background;
    int title_x, title_y;
} Mode;
Scene *New_Mode(int label);
void Mode_update(Scene *self);
void Mode_draw(Scene *self);
void Mode_destroy(Scene *self);

#endif

#ifndef Gameover_H_INCLUDED
#define Gameover_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [Gameover object]
*/
typedef struct _Gameover
{
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    ALLEGRO_BITMAP *background;
    int title_x, title_y;
} Gameover;
Scene *New_Gameover(int label);
void Gameover_update(Scene *self);
void Gameover_draw(Scene *self);
void Gameover_destroy(Scene *self);

#endif

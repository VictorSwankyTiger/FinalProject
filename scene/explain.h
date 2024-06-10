#ifndef Explain_H_INCLUDED
#define Explain_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [Explain object]
*/
typedef struct _Explain
{
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    ALLEGRO_BITMAP *background;
    int title_x, title_y;
} Explain;
Scene *New_Explain(int label);
void Explain_update(Scene *self);
void Explain_draw(Scene *self);
void Explain_destroy(Scene *self);

#endif

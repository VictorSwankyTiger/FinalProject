#include <allegro5/allegro_primitives.h>
#include "thank.h"
#include <stdbool.h>
/*
   [Thank function]
*/
Scene *New_Thank(int label)
{
    Thank *pDerivedObj = (Thank *)malloc(sizeof(Thank));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->background = al_load_bitmap("assets/image/credit.png");
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 40, 0);
    // Load sound
    pDerivedObj->song = al_load_sample("assets/sound/bgm.mp3");
    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    pDerivedObj->title_x = WIDTH / 2;
    pDerivedObj->title_y = HEIGHT / 2;
    // Loop the song until the display closes
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.1);
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = Thank_update;
    pObj->Draw = Thank_draw;
    pObj->Destroy = Thank_destroy;
    return pObj;
}
void Thank_update(Scene *self)
{
    if (key_state[ALLEGRO_KEY_ESCAPE])
    {
        self->scene_end = true;
        window = 0;
    }
    
    return;
}
void Thank_draw(Scene *self)
{
    Thank *Obj = ((Thank *)(self->pDerivedObj));
    al_clear_to_color(al_map_rgb(0, 0, 0));
    Thank *gs = ((Thank *)(self->pDerivedObj));
    al_draw_bitmap(gs->background, 0, 0, 0);

    //al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->title_x, Obj->title_y, ALLEGRO_ALIGN_CENTRE, "Press \"Esc\" to escape");
    //al_draw_rectangle(Obj->title_x - 150, Obj->title_y - 30, Obj->title_x + 150, Obj->title_y + 30, al_map_rgb(255, 255, 255), 0);
    al_play_sample_instance(Obj->sample_instance);
}
void Thank_destroy(Scene *self)
{
    Thank *Obj = ((Thank *)(self->pDerivedObj));
    al_destroy_font(Obj->font);
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    free(Obj);
    free(self);
}

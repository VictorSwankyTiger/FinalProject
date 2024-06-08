#include "charater.h"
#include "../scene/sceneManager.h"
#include "projectile.h"
#include "bomb.h"
#include "snow.h"
#include "snow_bullet.h"
#include "missile.h"
#include "missile_bullet.h"
#include "fire.h"
#include "fire_bullet.h"
#include "flame.h"
#include "../shapes/Rectangle.h"
#include "../algif5/src/algif.h"
#include <stdio.h>
#include <stdbool.h>
/*
   [Character function]
*/
Elements *New_Character(int label, int x, int y)
{
    Character *pDerivedObj = (Character *)malloc(sizeof(Character));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    // load character images
    char state_string[3][10] = {"stop", "move", "attack"};
    for (int i = 0; i < 3; i++)
    {
        char buffer[50];
        sprintf(buffer, "assets/image/robot%s.gif", state_string[i]);
        pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
    }
    // load effective sound
    ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/atk_sound.wav");
    pDerivedObj->atk_Sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(pDerivedObj->atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->atk_Sound, al_get_default_mixer());

    // initial the geometric information of character
    pDerivedObj->width = pDerivedObj->gif_status[0]->width;
    pDerivedObj->height = pDerivedObj->gif_status[0]->height;
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    pDerivedObj->move_cnt = 0;
    pDerivedObj->move_limit = 30;
    pDerivedObj->bomb_limit = 1;
    pDerivedObj->bomb_cnt = 0;
    pDerivedObj->live = 5;
    pDerivedObj->direction = 0;
    pDerivedObj->atk_mod = b;
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 30, 0);
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);
    pDerivedObj->dir = false; // true: face to right, false: face to left
    // initial the animation component
    pDerivedObj->state = STOP;
    pDerivedObj->new_proj = false;
    pObj->pDerivedObj = pDerivedObj;
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Flame_L;
    pObj->inter_obj[pObj->inter_len++] = Fire_L;
    pObj->inter_obj[pObj->inter_len++] = Snow_L;
    pObj->inter_obj[pObj->inter_len++] = Missile_L;
    pObj->inter_obj[pObj->inter_len++] = Fire_bullet_L;
    pObj->inter_obj[pObj->inter_len++] = Snow_bullet_L;
    pObj->inter_obj[pObj->inter_len++] = Missile_bullet_L;

    pDerivedObj->snow = false;
    pDerivedObj->missile = false;
    pDerivedObj->fire = false;
    // setting derived object function
    pObj->Draw = Character_draw;
    pObj->Update = Character_update;
    pObj->Interact = Character_interact;
    pObj->Destroy = Character_destory;
    return pObj;
}
void Character_update(Elements *self)
{
    // use the idea of finite state machine to deal with different state
    Character *chara = ((Character *)(self->pDerivedObj));
        if (key_state[ALLEGRO_KEY_SPACE])
        {
            chara->state = ATK;
        }
        else if (key_state[ALLEGRO_KEY_A])
        {
            chara->dir = false;
            chara->direction = 0;
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_D])
        {
            chara->dir = true;
            chara->direction = 1;
            chara->state = MOVE;
        }

        else if (key_state[ALLEGRO_KEY_W])
        {
            chara->dir = false;
            chara->direction = 2;
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_S])
        {
            chara->dir = true;
            chara->direction = 3;
            chara->state = MOVE;
        }

        else
        {
            chara->state = STOP;
        }
    if (chara->state == STOP)
    {
        if (key_state[ALLEGRO_KEY_SPACE])
        {
            chara->state = ATK;
        }
        else if (key_state[ALLEGRO_KEY_A])
        {
            chara->dir = false;
            chara->direction = 0;
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_D])
        {
            chara->dir = true;
            chara->direction = 1;
            chara->state = MOVE;
        }

        else if (key_state[ALLEGRO_KEY_W])
        {
            chara->dir = false;
            chara->direction = 2;
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_S])
        {
            chara->dir = true;
            chara->direction = 3;
            chara->state = MOVE;
        }

        else
        {
            chara->state = STOP;
        }
    }
    else if (chara->state == MOVE)
    {
        if (key_state[ALLEGRO_KEY_SPACE])
        {
            chara->state = ATK;
        }
        else if (key_state[ALLEGRO_KEY_A])
        {
            chara->dir = false;
            chara->direction = 0;
            _Character_update_position(self, -27.5, 0);
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_D])
        {
            chara->dir = true;
            chara->direction = 1;
            _Character_update_position(self, 27.5, 0);
            chara->state = MOVE;
        }

        else if (key_state[ALLEGRO_KEY_W])
        {
            chara->dir = false;
            chara->direction = 2;
            _Character_update_position(self, 0, -27.5);
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_S])
        {
            chara->dir = true;
            chara->direction = 3;
            _Character_update_position(self, 0, 27.5);
            chara->state = MOVE;
        }

        if (chara->gif_status[chara->state]->done)
            chara->state = STOP;
    }
    else if (chara->state == ATK)
    {
        if(chara->atk_mod == b){
            if (chara->gif_status[chara->state]->done)
            {
                chara->state = STOP;
                chara->new_proj = false;
            }
            if (chara->gif_status[ATK]->display_index == 0 && (chara->bomb_cnt < chara->bomb_limit)) //chara->new_proj == false
            {
                Elements *bomb;
                bomb = New_Bomb(Bomb_L, chara->x, chara->y, self);
                chara->bomb_cnt++;
                _Register_elements(scene, bomb);
                chara->new_proj = true;

                // Elements *pro;
                // if (chara->dir)
                // {
                //     pro = New_Projectile(Projectile_L,
                //                          chara->x + chara->width - 100,
                //                          chara->y + 10,
                //                          5);
                // }
                // else
                // {
                //     pro = New_Projectile(Projectile_L,
                //                          chara->x - 50,
                //                          chara->y + 10,
                //                          -5);
                // }
                // _Register_elements(scene, pro);
                // chara->new_proj = true;
            }
        }
        if(chara->atk_mod == s){
            if (chara->gif_status[chara->state]->done)
            {
                chara->state = STOP;
                chara->new_proj = false;
            }
            if (chara->gif_status[ATK]->display_index == 0 && (chara->bomb_cnt < chara->bomb_limit)) //chara->new_proj == false
            {
                Elements *snow;
                snow = New_Snow_bullet(Snow_bullet_L, chara->x, chara->y-60,chara->direction, self, 2);
                chara->bomb_cnt++;
                _Register_elements(scene, snow);
                chara->new_proj = true;
                chara->atk_mod = b;
            }
        }
        if(chara->atk_mod == f){
            if (chara->gif_status[chara->state]->done)
            {
                chara->state = STOP;
                chara->new_proj = false;
            }
            if (chara->gif_status[ATK]->display_index == 0 && (chara->bomb_cnt < chara->bomb_limit)) //chara->new_proj == false
            {
                Elements *fire;
                fire = New_Fire_bullet(Fire_bullet_L, chara->x, chara->y-60,chara->direction, self, 2);
                chara->bomb_cnt++;
                _Register_elements(scene, fire);
                chara->new_proj = true;
                chara->atk_mod = b;
            }
        }
        if (chara->gif_status[chara->state]->done)
        {
                chara->state = STOP;
                chara->new_proj = false;
        }
        if(chara->atk_mod == m){
            if (chara->gif_status[chara->state]->done)
            {
                chara->state = STOP;
                chara->new_proj = false;
            }
            if (chara->gif_status[ATK]->display_index == 0 && (chara->bomb_cnt < chara->bomb_limit)) //chara->new_proj == false
            {
                Elements *missile;
                missile = New_Missile_bullet(Missile_bullet_L, chara->x, chara->y-60,chara->direction, self, 2);  
                chara->bomb_cnt++;
                _Register_elements(scene, missile);
                chara->new_proj = true;
                chara->atk_mod = b;
            }
        }
    }
}
void Character_draw(Elements *self)
{
    // with the state, draw corresponding image
    Character *chara = ((Character *)(self->pDerivedObj));
    ALLEGRO_BITMAP *frame = algif_get_bitmap(chara->gif_status[chara->state], al_get_time());
    if (frame)
    {
        al_draw_bitmap(frame, chara->x, chara->y, ((chara->dir) ? ALLEGRO_FLIP_HORIZONTAL : 0));
    }
    if (chara->state == ATK && chara->gif_status[chara->state]->display_index == 2)
    {
        al_play_sample_instance(chara->atk_Sound);
    }
    char c[1];
    c[0] = chara->live +'0';
    al_draw_text(chara->font, al_map_rgb(0, 0, 0), 100, 230, ALLEGRO_ALIGN_CENTRE, c);
}
void Character_destory(Elements *self)
{
    Character *Obj = ((Character *)(self->pDerivedObj));
    al_destroy_sample_instance(Obj->atk_Sound);
    for (int i = 0; i < 3; i++)
        algif_destroy_animation(Obj->gif_status[i]);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}

void _Character_update_position(Elements *self, int dx, int dy)
{
    Character *chara = ((Character *)(self->pDerivedObj));
    chara->x += dx;
    chara->y += dy;
    Shape *hitbox = chara->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}

void Character_interact(Elements *self, Elements *tar) {
    Character *chara = ((Character *)(self->pDerivedObj));
    if (tar->label == Flame_L)
    {
        Flame *flame = (Flame *)(tar->pDerivedObj);
        if (flame->hitbox->overlap(flame->hitbox, chara->hitbox))
        {
            chara->live--;
        }
    }
    if (tar->label == Fire_L)
    {
        Fire *fire = (Fire *)(tar->pDerivedObj);
        if (fire->hitbox->overlap(fire->hitbox, chara->hitbox))
        {
            chara->atk_mod = f;
        }
    }
    if (tar->label == Snow_L)
    {
        Snow *snow = (Snow *)(tar->pDerivedObj);
        if (snow->hitbox->overlap(snow->hitbox, chara->hitbox))
        {
            chara->atk_mod = s;

        }
    }
    if (tar->label == Missile_L)
    {
        Missile *missile = (Missile *)(tar->pDerivedObj);
        if (missile->hitbox->overlap(missile->hitbox, chara->hitbox))
        {
            chara->atk_mod = m;
        }
    }
    if (tar->label == Snow_bullet_L)
    {
        Snow_bullet *freeze = (Snow_bullet *)(tar->pDerivedObj);
        if (freeze->hitbox->overlap(freeze->hitbox, chara->hitbox) && freeze->player != self)
        {
            chara->live--;
        }
    }
    if (tar->label == Fire_bullet_L)
    {
        Fire_bullet *fire = (Fire_bullet *)(tar->pDerivedObj);
        if (fire->hitbox->overlap(fire->hitbox, chara->hitbox) && fire->player != self)
        {
            chara->live--;
        }
    }
    if (tar->label == Missile_bullet_L)
    {
        Missile_bullet *missile = (Missile_bullet *)(tar->pDerivedObj);
        if (missile->hitbox->overlap(missile->hitbox, chara->hitbox)&& missile->player != self)
        {
            chara->live--;
        }
    }
    
}

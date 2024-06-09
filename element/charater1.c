#include "charater1.h"
#include "../scene/sceneManager.h"
#include "projectile.h"
#include "bomb.h"
#include "snow.h"
#include "heart.h"
#include "buff.h"
#include "strength.h"
#include "snow_bullet.h"
#include "missile.h"
#include "missile_bullet.h"
#include "fire.h"
#include "fire_bullet.h"
#include "flame.h"
#include "wall.h"
#include "../shapes/Rectangle.h"
#include "../algif5/src/algif.h"
#include <stdio.h>
#include <stdbool.h>
/*
   [Character1 function]
*/
Elements *New_Character1(int label, int x, int y, int i, int j)
{
    Character1 *pDerivedObj = (Character1 *)malloc(sizeof(Character1));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    // load Character1 images
    // char state_string[3][10] = {"stop", "move", "attack"};
    // for (int i = 0; i < 3; i++)
    // {
    //     char buffer[50];
    //     sprintf(buffer, "assets/image/robot%s.gif", state_string[i]);
    //     pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
    // }
    char direction_string[8][15] = {"left", "right", "up", "down", "leftflash", "rightflash", "upflash", "downflash"};
    for (int i = 0; i < 8; i++)
    {
        char buffer[50];
        sprintf(buffer, "assets/image/pl2%s.gif", direction_string[i]);
        pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
    }
    // load effective sound
    ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/atk_sound.wav");
    pDerivedObj->atk_Sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(pDerivedObj->atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->atk_Sound, al_get_default_mixer());

    // initial the geometric information of Character1
    pDerivedObj->width = pDerivedObj->gif_status[0]->width;
    pDerivedObj->height = pDerivedObj->gif_status[0]->height;
    pDerivedObj->i = i;
    pDerivedObj->j = j;
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    pDerivedObj->move_cnt = 0;
    pDerivedObj->move_limit = 6;
    pDerivedObj->bomb_limit = 1;
    pDerivedObj->bomb_cnt = 0;
    pDerivedObj->strong_limit = 60;
    pDerivedObj->strong_cnt = 60;
    pDerivedObj->attack_cnt = 5;
    pDerivedObj->attack_limit = 5;
    pDerivedObj->live = 5;
    pDerivedObj->direction = 0;
    pDerivedObj->power = 1;
    pDerivedObj->atk_mod = b;
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 30, 0);
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + ONE_GRID/2,
                                        pDerivedObj->y + ONE_GRID/2);
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
    pObj->inter_obj[pObj->inter_len++] = Wall_L;
    pObj->inter_obj[pObj->inter_len++] = Heart_L;
    pObj->inter_obj[pObj->inter_len++] = Buff_L;
    pObj->inter_obj[pObj->inter_len++] = Stren_L;


    pDerivedObj->snow = false;
    pDerivedObj->missile = false;
    pDerivedObj->fire = false;
    // setting derived object function
    pObj->Draw = Character1_draw;
    pObj->Update = Character1_update;
    pObj->Interact = Character1_interact;
    pObj->Destroy = Character1_destory;
    return pObj;
}
void Character1_update(Elements *self)
{
    // use the idea of finite state machine to deal with different state
    Character1 *chara = ((Character1 *)(self->pDerivedObj));
    if(chara->strong_cnt != chara->strong_limit){
        chara->strong_cnt++;
    }
    if(chara->attack_cnt != chara->attack_limit){
        chara->attack_cnt++;
    }
    if (chara->state == STOP)
    {
        if (key_state[ALLEGRO_KEY_RCTRL] && chara->attack_cnt == chara->attack_limit)
        {
            chara->state = ATK;
            chara->attack_cnt = 0;
        }

        else if (key_state[ALLEGRO_KEY_LEFT])
        {
            chara->dir = false;
            chara->direction = 0;
            if(MAP[chara->i][chara->j-1] == 0){
                chara->state = MOVE;
                chara->j--;
                chara->move_cnt++;
                _Character1_update_position(self, -ONE_GRID/chara->move_limit, 0);
            }
        }
        else if (key_state[ALLEGRO_KEY_RIGHT])
        {
            chara->dir = true;
            chara->direction = 1;
            if(MAP[chara->i][chara->j+1] == 0){
                chara->state = MOVE;
                chara->j++;
                chara->move_cnt++;
                _Character1_update_position(self, ONE_GRID/chara->move_limit, 0);
            }
        }
        else if (key_state[ALLEGRO_KEY_UP])
        {
            chara->dir = false;
            chara->direction = 2;
            if(MAP[chara->i-1][chara->j] == 0){
                chara->state = MOVE;
                chara->i--;
                chara->move_cnt++;
                _Character1_update_position(self, 0, -ONE_GRID/chara->move_limit);
            }
        }
        else if (key_state[ALLEGRO_KEY_DOWN])
        {

            chara->dir = true;
            chara->direction = 3;
            if(MAP[chara->i+1][chara->j] == 0){
                chara->state = MOVE;
                chara->i++;
                chara->move_cnt++;
                _Character1_update_position(self, 0, ONE_GRID/chara->move_limit);
            }
        }

        else
        {
            chara->state = STOP;
        }
    }
    else if (chara->state == MOVE)
    {
        if(chara->move_cnt < chara->move_limit){
            chara->move_cnt++;
            if (chara->direction == 0)
            {
                chara->dir = false;
                chara->direction = 0;
                _Character1_update_position(self, -ONE_GRID/chara->move_limit, 0);
            }
            else if (chara->direction == 1)
            {
                chara->dir = true;
                chara->direction = 1;
                _Character1_update_position(self, ONE_GRID/chara->move_limit, 0);
            }
            else if (chara->direction == 2)
            {
                chara->dir = false;
                chara->direction = 2;
                _Character1_update_position(self, 0, -ONE_GRID/chara->move_limit);
            }
            else if (chara->direction == 3)
            {
                chara->dir = true;
                chara->direction = 3;
                _Character1_update_position(self, 0, ONE_GRID/chara->move_limit);
            }
        }
        else{
            chara->move_cnt = 0;
            chara->state = STOP;
        }
    }
    else if (chara->state == ATK)
    {
        al_play_sample_instance(chara->atk_Sound);
        if(chara->atk_mod == b){
            if (chara->gif_status[chara->direction]->done)
            {
                chara->state = STOP;
                chara->new_proj = false;
            }
            if (chara->gif_status[chara->direction]->display_index == 0 && (chara->bomb_cnt < chara->bomb_limit)) //chara->new_proj == false
            {
                Elements *bomb;
                bomb = New_Bomb(Bomb_L, chara->x, chara->y, self, chara->i, chara->j);
                chara->bomb_cnt++;
                _Register_elements(scene, bomb);
                chara->new_proj = true;
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
                Elements *fire;
                if(chara->direction == 0){
                    fire = New_Snow_bullet(Snow_bullet_L, chara->x-ONE_GRID, chara->y,chara->direction, self, 2);
                    chara->bomb_cnt++;
                    _Register_elements(scene, fire);
                }
                if(chara->direction == 1){
                    fire = New_Snow_bullet(Snow_bullet_L, chara->x+ONE_GRID, chara->y,chara->direction, self, 2);
                    chara->bomb_cnt++;
                    _Register_elements(scene, fire);
                }
                if(chara->direction == 2){
                    fire = New_Snow_bullet(Snow_bullet_L, chara->x, chara->y-ONE_GRID,chara->direction, self, 2);
                    chara->bomb_cnt++;
                    _Register_elements(scene, fire);
                }
                if(chara->direction == 3){
                    fire = New_Snow_bullet(Snow_bullet_L, chara->x, chara->y+ONE_GRID,chara->direction, self, 2);
                    chara->bomb_cnt++;
                    _Register_elements(scene, fire);
                }
                chara->new_proj = true;
                chara->atk_mod = b;
                chara->state =STOP;
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
                if(chara->direction == 0){
                    fire = New_Fire_bullet(Fire_bullet_L, chara->x-ONE_GRID, chara->y,chara->direction, self, 2);
                    chara->bomb_cnt++;
                    _Register_elements(scene, fire);
                }
                if(chara->direction == 1){
                    fire = New_Fire_bullet(Fire_bullet_L, chara->x+ONE_GRID, chara->y,chara->direction, self, 2);
                    chara->bomb_cnt++;
                    _Register_elements(scene, fire);
                }
                if(chara->direction == 2){
                    fire = New_Fire_bullet(Fire_bullet_L, chara->x, chara->y-ONE_GRID,chara->direction, self, 2);
                    chara->bomb_cnt++;
                    _Register_elements(scene, fire);
                }
                if(chara->direction == 3){
                    fire = New_Fire_bullet(Fire_bullet_L, chara->x, chara->y+ONE_GRID,chara->direction, self, 2);
                    chara->bomb_cnt++;
                    _Register_elements(scene, fire);
                }
                chara->new_proj = true;
                chara->atk_mod = b;
                chara->state =STOP;
            }
        }
        if(chara->atk_mod == m){
            if (chara->gif_status[chara->direction]->done)
            {
                chara->state = STOP;
                chara->new_proj = false;
            }
            if (chara->gif_status[chara->direction]->display_index == 0 && (chara->bomb_cnt < chara->bomb_limit)) //chara->new_proj == false
            {
                Elements *missile;
                missile = New_Missile_bullet(Missile_bullet_L, chara->x, chara->y, chara->direction, self, 2);  
                chara->bomb_cnt++;
                _Register_elements(scene, missile);
                chara->new_proj = true;
                chara->atk_mod = b;
                chara->state =STOP;
            }
        }
        if (chara->gif_status[chara->direction]->done)
        {
                chara->state = STOP;
                chara->new_proj = false;
        }
    }
}
void Character1_draw(Elements *self)
{
    // with the state, draw corresponding image
    Character1 *chara = ((Character1 *)(self->pDerivedObj));
    ALLEGRO_BITMAP *frame = algif_get_bitmap(chara->gif_status[chara->direction + 4*(chara->strong_cnt != chara->strong_limit)], al_get_time());
    if (frame)
    {
        al_draw_bitmap(frame, chara->x, chara->y, 0);
    }
    if (chara->state == ATK)
    {
        al_play_sample_instance(chara->atk_Sound);
    }
    char c[1];
    c[0] = chara->live +'0';
    al_draw_text(chara->font, al_map_rgb(0, 0, 0), 90, 678, ALLEGRO_ALIGN_CENTRE, c);
}
void Character1_destory(Elements *self)
{
    Character1 *Obj = ((Character1 *)(self->pDerivedObj));
    al_destroy_sample_instance(Obj->atk_Sound);
    for (int i = 0; i < 4; i++)
        algif_destroy_animation(Obj->gif_status[i]);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}

void _Character1_update_position(Elements *self, int dx, int dy)
{
    Character1 *chara = ((Character1 *)(self->pDerivedObj));
    chara->x += dx;
    chara->y += dy;
    Shape *hitbox = chara->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}

void Character1_interact(Elements *self, Elements *tar) {
    Character1 *chara = ((Character1 *)(self->pDerivedObj));
    if (tar->label == Flame_L)
    {
        Flame *flame = (Flame *)(tar->pDerivedObj);
        if (flame->hitbox->overlap(flame->hitbox, chara->hitbox))
        {
            if(chara->strong_cnt == chara->strong_limit){
                chara->strong_cnt = 0;
                chara->live-=flame->damge;
            }
            //flame->damge = 0;
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
    if (tar->label == Heart_L)
    {
        Heart *heart = (Heart *)(tar->pDerivedObj);
        if (heart->hitbox->overlap(heart->hitbox, chara->hitbox))
        {
            chara->live ++;

        }
    }
     if (tar->label == Buff_L)
    {
        Buff *buff = (Buff *)(tar->pDerivedObj);
        if (buff->hitbox->overlap(buff->hitbox, chara->hitbox))
        {
            // chara->live ++;
            chara->power++;
        }
    }
     if (tar->label == Stren_L)
    {
        Strength *stren = (Strength *)(tar->pDerivedObj);
        if (stren->hitbox->overlap(stren->hitbox, chara->hitbox))
        {
            // chara->live ++;
            chara->bomb_limit++;
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
            // chara->state = STOP;
        }
    }
    if (tar->label == Fire_bullet_L)
    {
        Fire_bullet *fire = (Fire_bullet *)(tar->pDerivedObj);
        if (fire->hitbox->overlap(fire->hitbox, chara->hitbox) && fire->player != self)
        {
            if(chara->strong_cnt == chara->strong_limit){
                chara->strong_cnt = 0;
                chara->live--;
            }
        }            
        fire->damge = 0;

    }
    if (tar->label == Missile_bullet_L)
    {
        Missile_bullet *missile = (Missile_bullet *)(tar->pDerivedObj);
        if (missile->hitbox->overlap(missile->hitbox, chara->hitbox)&& missile->player != self)
        {
            if(chara->strong_cnt == chara->strong_limit){
                chara->strong_cnt = 0;
                chara->live--;
            }
        }
    }
    
}

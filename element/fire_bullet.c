#include "fire_bullet.h"
#include "../scene/sceneManager.h"
#include "../shapes/Circle.h"
/*
   [Fire_bullet function]
*/
Elements *New_Fire_bullet(int label, int x, int y, int direction, Elements* player,int length)
{
    Fire_bullet *pDerivedObj = (Fire_bullet *)malloc(sizeof(Fire_bullet));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/fire.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    pDerivedObj->time_cnt = 5;
    pDerivedObj->created = 0;
    pDerivedObj->direction = direction;
    pDerivedObj->player = player;
    pDerivedObj->length = length;
    // pDerivedObj->v = v;
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x + pDerivedObj->width / 2,
                                     pDerivedObj->y + pDerivedObj->height / 2,
                                     min(pDerivedObj->width, pDerivedObj->height) / 2);
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Tree_L;
    pObj->inter_obj[pObj->inter_len++] = Floor_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Fire_bullet_update;
    pObj->Interact = Fire_bullet_interact;
    pObj->Draw = Fire_bullet_draw;
    pObj->Destroy = Fire_bullet_destory;

    return pObj;
}
void Fire_bullet_update(Elements *self)
{
    Fire_bullet *Obj = ((Fire_bullet *)(self->pDerivedObj));
    Character *chara = ((Character *)(Obj->player->pDerivedObj));
    Obj->time_cnt--;
    if(!Obj->created && Obj->length){
        Elements *Fire_bullet;
        if(Obj->direction == 0){
            Fire_bullet = New_Fire_bullet(Fire_bullet_L, Obj->x, Obj->y - 55, Obj->direction,Obj->player, Obj->length-1);
            _Register_elements(scene, Fire_bullet);
        }
        if(Obj->direction == 1){
            Fire_bullet = New_Fire_bullet(Fire_bullet_L, Obj->x + 55, Obj->y, Obj->direction,Obj->player, Obj->length-1);
            _Register_elements(scene, Fire_bullet);
        }
        if(Obj->direction == 2){
            Fire_bullet = New_Fire_bullet(Fire_bullet_L, Obj->x, Obj->y + 55, Obj->direction,Obj->player, Obj->length-1);
            _Register_elements(scene, Fire_bullet);
        }
        if(Obj->direction == 3){
            Fire_bullet = New_Fire_bullet(Fire_bullet_L, Obj->x - 55, Obj->y, Obj->direction,Obj->player, Obj->length-1);
            _Register_elements(scene, Fire_bullet);
        }
        if(Obj->direction == 4){
            Fire_bullet = New_Fire_bullet(Fire_bullet_L, Obj->x, Obj->y - 55, 0,Obj->player, Obj->length-1);
            _Register_elements(scene, Fire_bullet);
        
            Fire_bullet = New_Fire_bullet(Fire_bullet_L, Obj->x + 55, Obj->y, 1,Obj->player, Obj->length-1);
            _Register_elements(scene, Fire_bullet);
        
            Fire_bullet = New_Fire_bullet(Fire_bullet_L, Obj->x, Obj->y + 55, 2,Obj->player, Obj->length-1);
            _Register_elements(scene, Fire_bullet);
        
            Fire_bullet = New_Fire_bullet(Fire_bullet_L, Obj->x - 55, Obj->y, 3,Obj->player, Obj->length-1);
            _Register_elements(scene, Fire_bullet);
        }
        Obj->created = 1;
    }

    if(Obj->time_cnt == 0){
        self->dele = true;
        chara->bomb_cnt--;
    }
    //_Fire_bullet_update_position(self, Obj->v, 0);
}
void _Fire_bullet_update_position(Elements *self, int dx, int dy)
{
    // Fire_bullet *Obj = ((Fire_bullet *)(self->pDerivedObj));
    // Obj->x += dx;
    // Obj->y += dy;
    // Shape *hitbox = Obj->hitbox;
    // hitbox->update_center_x(hitbox, dx);
    // hitbox->update_center_y(hitbox, dy);
}
void Fire_bullet_interact(Elements *self, Elements *tar)
{
    Fire_bullet *Obj = ((Fire_bullet *)(self->pDerivedObj));
    if (tar->label == Floor_L)
    {
        if (Obj->x < 0 - Obj->width)
            self->dele = true;
        else if (Obj->x > WIDTH + Obj->width)
            self->dele = true;
    }
    else if (tar->label == Tree_L)
    {
        Tree *tree = ((Tree *)(tar->pDerivedObj));
        if (tree->hitbox->overlap(tree->hitbox, Obj->hitbox))
        {
            self->dele = true;
        }
    }
}
void Fire_bullet_draw(Elements *self)
{
    Fire_bullet *Obj = ((Fire_bullet *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
    // if (Obj->v > 0)
    //     al_draw_bitmap(Obj->img, Obj->x, Obj->y, ALLEGRO_FLIP_HORIZONTAL);
    // else
    //     al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Fire_bullet_destory(Elements *self)
{
    Fire_bullet *Obj = ((Fire_bullet *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}

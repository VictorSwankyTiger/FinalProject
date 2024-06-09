#include "snow_bullet.h"
#include "../scene/sceneManager.h"
#include "../shapes/Circle.h"
#include "../shapes/Rectangle.h"
/*
   [Snow_bullet function]
*/
Elements *New_Snow_bullet(int label, int x, int y, int direction, Elements* player,int length)
{
    Snow_bullet *pDerivedObj = (Snow_bullet *)malloc(sizeof(Snow_bullet));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/freeze.png");
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
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + ONE_GRID/2,
                                        pDerivedObj->y + ONE_GRID/2);
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Tree_L;
    pObj->inter_obj[pObj->inter_len++] = Floor_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Snow_bullet_update;
    pObj->Interact = Snow_bullet_interact;
    pObj->Draw = Snow_bullet_draw;
    pObj->Destroy = Snow_bullet_destory;

    return pObj;
}
void Snow_bullet_update(Elements *self)
{
    Snow_bullet *Obj = ((Snow_bullet *)(self->pDerivedObj));
    Character *chara = ((Character *)(Obj->player->pDerivedObj));
    Obj->time_cnt--;
    if(!Obj->created && Obj->length){
        Elements *Snow_bullet;
        if(Obj->direction == 0){
            Snow_bullet = New_Snow_bullet(Snow_bullet_L, Obj->x-ONE_GRID, Obj->y, Obj->direction,Obj->player, Obj->length-1);
            _Register_elements(scene, Snow_bullet);
        }
        if(Obj->direction == 1){
            Snow_bullet = New_Snow_bullet(Snow_bullet_L, Obj->x + ONE_GRID, Obj->y, Obj->direction,Obj->player, Obj->length-1);
            _Register_elements(scene, Snow_bullet);
        }
        if(Obj->direction == 2){
            Snow_bullet = New_Snow_bullet(Snow_bullet_L, Obj->x, Obj->y - ONE_GRID, Obj->direction,Obj->player, Obj->length-1);
            _Register_elements(scene, Snow_bullet);
        }
        if(Obj->direction == 3){
            Snow_bullet = New_Snow_bullet(Snow_bullet_L, Obj->x, Obj->y+ONE_GRID, Obj->direction,Obj->player, Obj->length-1);
            _Register_elements(scene, Snow_bullet);
        }
    
        Obj->created = 1;
    }

    if(Obj->time_cnt == 0){
        self->dele = true;
        if(chara->bomb_cnt!=0)chara->bomb_cnt--;
    }
    //_Snow_bullet_update_position(self, Obj->v, 0);
}
void _Snow_bullet_update_position(Elements *self, int dx, int dy)
{
    // Snow_bullet *Obj = ((Snow_bullet *)(self->pDerivedObj));
    // Obj->x += dx;
    // Obj->y += dy;
    // Shape *hitbox = Obj->hitbox;
    // hitbox->update_center_x(hitbox, dx);
    // hitbox->update_center_y(hitbox, dy);
}
void Snow_bullet_interact(Elements *self, Elements *tar)
{
    Snow_bullet *Obj = ((Snow_bullet *)(self->pDerivedObj));
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
void Snow_bullet_draw(Elements *self)
{
    Snow_bullet *Obj = ((Snow_bullet *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
    // if (Obj->v > 0)
    //     al_draw_bitmap(Obj->img, Obj->x, Obj->y, ALLEGRO_FLIP_HORIZONTAL);
    // else
    //     al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Snow_bullet_destory(Elements *self)
{
    Snow_bullet *Obj = ((Snow_bullet *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}

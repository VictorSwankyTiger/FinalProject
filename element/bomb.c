#include "bomb.h"
#include "flame.h"
#include "../scene/sceneManager.h"
#include "../shapes/Circle.h"
#include "../shapes/Rectangle.h"
/*
   [Bomb function]
*/
Elements *New_Bomb(int label, int x, int y, Elements *player, int i, int j)
{
    Bomb *pDerivedObj = (Bomb *)malloc(sizeof(Bomb));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/bomb16_0.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    pDerivedObj->i = i;
    pDerivedObj->j = j;
    pDerivedObj->player = player;
    //pDerivedObj->v = v;
    pDerivedObj->cnt = 45;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + ONE_GRID/2,
                                        pDerivedObj->y + ONE_GRID/2);
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Tree_L;
    pObj->inter_obj[pObj->inter_len++] = Floor_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Bomb_update;
    pObj->Interact = Bomb_interact;
    pObj->Draw = Bomb_draw;
    pObj->Destroy = Bomb_destory;

    return pObj;
}
void Bomb_update(Elements *self)
{
    Bomb *Obj = ((Bomb *)(self->pDerivedObj));
    Character *chara = ((Character *)(Obj->player->pDerivedObj));
    Obj->cnt--;
    if(Obj->cnt == 0){
        Elements *flame;
        flame = New_Flame(Flame_L, Obj->x, Obj->y, 4, chara->power, Obj->i, Obj->j);
        _Register_elements(scene, flame);
        
        chara->bomb_cnt--;
        self->dele = true;
    }
    //_Bomb_update_position(self, Obj->v, 0);
}
void _Bomb_update_position(Elements *self, int dx, int dy)
{
    // Bomb *Obj = ((Bomb *)(self->pDerivedObj));
    // Obj->x += dx;
    // Obj->y += dy;
    // Shape *hitbox = Obj->hitbox;
    // hitbox->update_center_x(hitbox, dx);
    // hitbox->update_center_y(hitbox, dy);
}
void Bomb_interact(Elements *self, Elements *tar)
{
    // Bomb *Obj = ((Bomb *)(self->pDerivedObj));
    // if (tar->label == Floor_L)
    // {
    //     if (Obj->x < 0 - Obj->width)
    //         self->dele = true;
    //     else if (Obj->x > WIDTH + Obj->width)
    //         self->dele = true;
    // }
    // else if (tar->label == Tree_L)
    // {
    //     Tree *tree = ((Tree *)(tar->pDerivedObj));
    //     if (tree->hitbox->overlap(tree->hitbox, Obj->hitbox))
    //     {
    //         self->dele = true;
    //     }
    // }
}
void Bomb_draw(Elements *self)
{
    Bomb *Obj = ((Bomb *)(self->pDerivedObj));
    if (Obj->v > 0)
        al_draw_bitmap(Obj->img, Obj->x, Obj->y, ALLEGRO_FLIP_HORIZONTAL);
    else
        al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Bomb_destory(Elements *self)
{
    Bomb *Obj = ((Bomb *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}

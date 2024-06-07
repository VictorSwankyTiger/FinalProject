#include "flame.h"
#include "../scene/sceneManager.h"
#include "../shapes/Circle.h"
/*
   [Flame function]
*/
Elements *New_Flame(int label, int x, int y, int direction, int length)
{
    Flame *pDerivedObj = (Flame *)malloc(sizeof(Flame));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/explosionCenter.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    pDerivedObj->time_cnt = 60;
    pDerivedObj->created = 0;
    pDerivedObj->direction = direction;
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
    pObj->Update = Flame_update;
    pObj->Interact = Flame_interact;
    pObj->Draw = Flame_draw;
    pObj->Destroy = Flame_destory;

    return pObj;
}
void Flame_update(Elements *self)
{
    Flame *Obj = ((Flame *)(self->pDerivedObj));
    Obj->time_cnt--;
    if(!Obj->created && Obj->length){
        Elements *flame;
        if(Obj->direction == 0){
            flame = New_Flame(Flame_L, Obj->x, Obj->y - 55, Obj->direction, Obj->length-1);
            _Register_elements(scene, flame);
        }
        if(Obj->direction == 1){
            flame = New_Flame(Flame_L, Obj->x + 55, Obj->y, Obj->direction, Obj->length-1);
            _Register_elements(scene, flame);
        }
        if(Obj->direction == 2){
            flame = New_Flame(Flame_L, Obj->x, Obj->y + 55, Obj->direction, Obj->length-1);
            _Register_elements(scene, flame);
        }
        if(Obj->direction == 3){
            flame = New_Flame(Flame_L, Obj->x - 55, Obj->y, Obj->direction, Obj->length-1);
            _Register_elements(scene, flame);
        }
        if(Obj->direction == 4){
            flame = New_Flame(Flame_L, Obj->x, Obj->y - 55, 0, Obj->length-1);
            _Register_elements(scene, flame);
        
            flame = New_Flame(Flame_L, Obj->x + 55, Obj->y, 1, Obj->length-1);
            _Register_elements(scene, flame);
        
            flame = New_Flame(Flame_L, Obj->x, Obj->y + 55, 2, Obj->length-1);
            _Register_elements(scene, flame);
        
            flame = New_Flame(Flame_L, Obj->x - 55, Obj->y, 3, Obj->length-1);
            _Register_elements(scene, flame);
        }
        Obj->created = 1;
    }

    if(Obj->time_cnt == 0){
        self->dele = true;
    }
    //_Flame_update_position(self, Obj->v, 0);
}
void _Flame_update_position(Elements *self, int dx, int dy)
{
    // Flame *Obj = ((Flame *)(self->pDerivedObj));
    // Obj->x += dx;
    // Obj->y += dy;
    // Shape *hitbox = Obj->hitbox;
    // hitbox->update_center_x(hitbox, dx);
    // hitbox->update_center_y(hitbox, dy);
}
void Flame_interact(Elements *self, Elements *tar)
{
    // Flame *Obj = ((Flame *)(self->pDerivedObj));
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
void Flame_draw(Elements *self)
{
    Flame *Obj = ((Flame *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
    // if (Obj->v > 0)
    //     al_draw_bitmap(Obj->img, Obj->x, Obj->y, ALLEGRO_FLIP_HORIZONTAL);
    // else
    //     al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Flame_destory(Elements *self)
{
    Flame *Obj = ((Flame *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}

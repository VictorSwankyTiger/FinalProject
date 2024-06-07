#include "missile_bullet.h"
#include "../scene/sceneManager.h"
#include "../shapes/Circle.h"
/*
   [Missile_bullet function]
*/
Elements *New_Missile_bullet(int label, int x, int y, int direction, int length)
{
    Missile_bullet *pDerivedObj = (Missile_bullet *)malloc(sizeof(Missile_bullet));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/missile.png");
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
    pObj->Update = Missile_bullet_update;
    pObj->Interact = Missile_bullet_interact;
    pObj->Draw = Missile_bullet_draw;
    pObj->Destroy = Missile_bullet_destory;

    return pObj;
}
void Missile_bullet_update(Elements *self)
{
    Missile_bullet *Obj = ((Missile_bullet *)(self->pDerivedObj));
    Obj->time_cnt--;
    if(!Obj->created && Obj->length){
        Elements *Missile_bullet;
        if(Obj->direction == 0){
            Missile_bullet = New_Missile_bullet(Missile_bullet_L, Obj->x, Obj->y - 55, Obj->direction, Obj->length-1);
            _Register_elements(scene, Missile_bullet);
        }
        if(Obj->direction == 1){
            Missile_bullet = New_Missile_bullet(Missile_bullet_L, Obj->x + 55, Obj->y, Obj->direction, Obj->length-1);
            _Register_elements(scene, Missile_bullet);
        }
        if(Obj->direction == 2){
            Missile_bullet = New_Missile_bullet(Missile_bullet_L, Obj->x, Obj->y + 55, Obj->direction, Obj->length-1);
            _Register_elements(scene, Missile_bullet);
        }
        if(Obj->direction == 3){
            Missile_bullet = New_Missile_bullet(Missile_bullet_L, Obj->x - 55, Obj->y, Obj->direction, Obj->length-1);
            _Register_elements(scene, Missile_bullet);
        }
        if(Obj->direction == 4){
            Missile_bullet = New_Missile_bullet(Missile_bullet_L, Obj->x, Obj->y - 55, 0, Obj->length-1);
            _Register_elements(scene, Missile_bullet);
        
            Missile_bullet = New_Missile_bullet(Missile_bullet_L, Obj->x + 55, Obj->y, 1, Obj->length-1);
            _Register_elements(scene, Missile_bullet);
        
            Missile_bullet = New_Missile_bullet(Missile_bullet_L, Obj->x, Obj->y + 55, 2, Obj->length-1);
            _Register_elements(scene, Missile_bullet);
        
            Missile_bullet = New_Missile_bullet(Missile_bullet_L, Obj->x - 55, Obj->y, 3, Obj->length-1);
            _Register_elements(scene, Missile_bullet);
        }
        Obj->created = 1;
    }

    if(Obj->time_cnt == 0){
        self->dele = true;
    }
    //_Missile_bullet_update_position(self, Obj->v, 0);
}
void _Missile_bullet_update_position(Elements *self, int dx, int dy)
{
    // Missile_bullet *Obj = ((Missile_bullet *)(self->pDerivedObj));
    // Obj->x += dx;
    // Obj->y += dy;
    // Shape *hitbox = Obj->hitbox;
    // hitbox->update_center_x(hitbox, dx);
    // hitbox->update_center_y(hitbox, dy);
}
void Missile_bullet_interact(Elements *self, Elements *tar)
{
    // Missile_bullet *Obj = ((Missile_bullet *)(self->pDerivedObj));
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
void Missile_bullet_draw(Elements *self)
{
    Missile_bullet *Obj = ((Missile_bullet *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
    // if (Obj->v > 0)
    //     al_draw_bitmap(Obj->img, Obj->x, Obj->y, ALLEGRO_FLIP_HORIZONTAL);
    // else
    //     al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Missile_bullet_destory(Elements *self)
{
    Missile_bullet *Obj = ((Missile_bullet *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}

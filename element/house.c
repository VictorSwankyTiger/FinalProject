#include "house.h"
#include "../scene/sceneManager.h"
#include "../shapes/Circle.h"
#include "missile_bullet.h"
#include "fire_bullet.h"
#include "flame.h"
#include "../shapes/Rectangle.h"

/*
   [House function]
*/
Elements *New_House(int label, int x, int y)
{
    House *pDerivedObj = (House *)malloc(sizeof(House));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/box.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + ONE_GRID/2,
                                        pDerivedObj->y + ONE_GRID/2);
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Tree_L;
    pObj->inter_obj[pObj->inter_len++] = Floor_L;
    pObj->inter_obj[pObj->inter_len++] = Flame_L;
    pObj->inter_obj[pObj->inter_len++] = Missile_bullet_L;
    pObj->inter_obj[pObj->inter_len++] = Fire_bullet_L;


    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = House_update;
    pObj->Interact = House_interact;
    pObj->Draw = House_draw;
    pObj->Destroy = House_destory;

    return pObj;
}
void House_update(Elements *self)
{
    
    //_House_update_position(self, Obj->v, 0);
}
void _House_update_position(Elements *self, int dx, int dy)
{
    
}
void House_interact(Elements *self, Elements *tar)
{
    House *Obj = ((House *)(self->pDerivedObj));
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
    else if (tar->label == Fire_bullet_L)
    {
        Fire_bullet *fire = ((Fire_bullet *)(tar->pDerivedObj));
        if (fire->hitbox->overlap(fire->hitbox, Obj->hitbox))
        {
            self->dele = true;
        }
    }
    else if (tar->label == Flame_L)
    {
        Flame *fire = ((Flame *)(tar->pDerivedObj));
        if (fire->hitbox->overlap(fire->hitbox, Obj->hitbox))
        {
            self->dele = true;
        }
    }
       
}
void House_draw(Elements *self)
{
    House *Obj = ((House *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void House_destory(Elements *self)
{
    House *Obj = ((House *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}

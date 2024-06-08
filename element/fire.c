#include "fire.h"
#include "../scene/sceneManager.h"
#include "../shapes/Circle.h"
/*
   [Fire function]
*/
Elements *New_Fire(int label, int x, int y)
{
    Fire *pDerivedObj = (Fire *)malloc(sizeof(Fire));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/fire.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    pDerivedObj->player = NULL;
    //pDerivedObj->v = v;
    pDerivedObj->cnt = 60;
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x + pDerivedObj->width / 2,
                                     pDerivedObj->y + pDerivedObj->height / 2,
                                     min(pDerivedObj->width, pDerivedObj->height) / 2);
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Tree_L;
    pObj->inter_obj[pObj->inter_len++] = Floor_L;
    pObj->inter_obj[pObj->inter_len++] = Character_L;
    pObj->inter_obj[pObj->inter_len++] = Character1_L;


    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Fire_update;
    pObj->Interact = Fire_interact;
    pObj->Draw = Fire_draw;
    pObj->Destroy = Fire_destory;

    return pObj;
}
void Fire_update(Elements *self)
{
    
}
void _Fire_update_position(Elements *self, int dx, int dy)
{
}
void Fire_interact(Elements *self, Elements *tar)
{
   Fire *Obj = ((Fire *)(self->pDerivedObj));
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
    else if (tar->label == Character_L)
    {
        Character *chara = ((Character *)(tar->pDerivedObj));
        if (chara->hitbox->overlap(chara->hitbox, Obj->hitbox))
        {
            self->dele = true;
        }
    }
    else if (tar->label == Character1_L)
    {
        Character1 *chara = ((Character1 *)(tar->pDerivedObj));
        if (chara->hitbox->overlap(chara->hitbox, Obj->hitbox))
        {
            self->dele = true;
        }
    }
}

void Fire_draw(Elements *self)
{
    Fire *Obj = ((Fire *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Fire_destory(Elements *self)
{
    Fire *Obj = ((Fire *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}

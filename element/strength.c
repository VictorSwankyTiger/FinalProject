#include "strength.h"
#include "../scene/sceneManager.h"
#include "../shapes/Circle.h"
#include "../shapes/Rectangle.h"
/*
   [Strength function]
*/
Elements *New_Strength(int label, int x, int y)
{
    Strength *pDerivedObj = (Strength *)malloc(sizeof(Strength));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/Strength.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    pDerivedObj->player = NULL;
    //pDerivedObj->v = v;
    pDerivedObj->cnt = 60;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + ONE_GRID/2,
                                        pDerivedObj->y + ONE_GRID/2);
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Tree_L;
    pObj->inter_obj[pObj->inter_len++] = Floor_L;
    pObj->inter_obj[pObj->inter_len++] = Character_L;
    pObj->inter_obj[pObj->inter_len++] = Character1_L;


    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Strength_update;
    pObj->Interact = Strength_interact;
    pObj->Draw = Strength_draw;
    pObj->Destroy = Strength_destory;

    return pObj;
}
void Strength_update(Elements *self)
{
    
}
void _Strength_update_position(Elements *self, int dx, int dy)
{
}
void Strength_interact(Elements *self, Elements *tar)
{
   Strength *Obj = ((Strength *)(self->pDerivedObj));
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

void Strength_draw(Elements *self)
{
    Strength *Obj = ((Strength *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Strength_destory(Elements *self)
{
    Strength *Obj = ((Strength *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}

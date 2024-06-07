#include "snow.h"
#include "../scene/sceneManager.h"
#include "../shapes/Circle.h"
/*
   [Snow function]
*/
Elements *New_Snow(int label, int x, int y)
{
    Snow *pDerivedObj = (Snow *)malloc(sizeof(Snow));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/snow.png");
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
    pObj->Update = Snow_update;
    pObj->Interact = Snow_interact;
    pObj->Draw = Snow_draw;
    pObj->Destroy = Snow_destory;

    return pObj;
}
void Snow_update(Elements *self)
{
    
}
void _Snow_update_position(Elements *self, int dx, int dy)
{
}
void Snow_interact(Elements *self, Elements *tar)
{
   Snow *Obj = ((Snow *)(self->pDerivedObj));
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

void Snow_draw(Elements *self)
{
    Snow *Obj = ((Snow *)(self->pDerivedObj));
    if (Obj->v > 0)
        al_draw_bitmap(Obj->img, Obj->x, Obj->y, ALLEGRO_FLIP_HORIZONTAL);
    else
        al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Snow_destory(Elements *self)
{
    Snow *Obj = ((Snow *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}

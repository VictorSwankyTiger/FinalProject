#include "wall.h"
#include "../scene/sceneManager.h"
#include "../shapes/Circle.h"
/*
   [Wall function]
*/
Elements *New_Wall(int label, int x, int y)
{
    Wall *pDerivedObj = (Wall *)malloc(sizeof(Wall));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/block.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    //pDerivedObj->v = v;
  
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Tree_L;
    pObj->inter_obj[pObj->inter_len++] = Floor_L;
    pObj->inter_obj[pObj->inter_len++] = Character_L;
    pObj->inter_obj[pObj->inter_len++] = Character1_L;
    pObj->inter_obj[pObj->inter_len++] = Character1_L;

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Wall_update;
    pObj->Interact = Wall_interact;
    pObj->Draw = Wall_draw;
    pObj->Destroy = Wall_destory;

    return pObj;
}
void Wall_update(Elements *self)
{
    
    //_Wall_update_position(self, Obj->v, 0);
}
void _Wall_update_position(Elements *self, int dx, int dy)
{
    
}
void Wall_interact(Elements *self, Elements *tar)
{
    Wall *Obj = ((Wall *)(self->pDerivedObj));
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
        // if (tree->hitbox->overlap(tree->hitbox, Obj->hitbox))
        // {
        //     self->dele = true;
        // }
    }
}
void Wall_draw(Elements *self)
{
    Wall *Obj = ((Wall *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Wall_destory(Elements *self)
{
    Wall *Obj = ((Wall *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj);
    free(self);
}

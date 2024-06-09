#include "missile_bullet.h"
#include "../scene/sceneManager.h"
#include "../shapes/Circle.h"
#include "../shapes/Rectangle.h"
/*
   [Missile_bullet function]
*/
Elements *New_Missile_bullet(int label, int x, int y, int direction, Elements* player,int length)
{
    Missile_bullet *pDerivedObj = (Missile_bullet *)malloc(sizeof(Missile_bullet));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/missile.png");
    pDerivedObj->img1 = al_load_bitmap("assets/image/missile1.png");
    pDerivedObj->img2 = al_load_bitmap("assets/image/missile2.png");
    pDerivedObj->img3 = al_load_bitmap("assets/image/missile3.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/missile.mp3");
    pDerivedObj->atk_Sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(pDerivedObj->atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->atk_Sound, al_get_default_mixer());
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    pDerivedObj->time_cnt = 5;
    pDerivedObj->created = 0;
    pDerivedObj->direction = direction;
    pDerivedObj->player = player;
    pDerivedObj->length = length;
    pDerivedObj->v = 20;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + ONE_GRID/2,
                                        pDerivedObj->y + ONE_GRID/2);
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Tree_L;
    pObj->inter_obj[pObj->inter_len++] = Floor_L;
    pObj->inter_obj[pObj->inter_len++] = House_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Missile_bullet_update;
    pObj->Interact = Missile_bullet_interact;
    pObj->Draw = Missile_bullet_draw;
    pObj->Destroy = Missile_bullet_destory;
        al_play_sample_instance(pDerivedObj->atk_Sound);

    return pObj;
}
void Missile_bullet_update(Elements *self)
{
    Missile_bullet *Obj = ((Missile_bullet *)(self->pDerivedObj));
    Character *chara = ((Character *)(Obj->player->pDerivedObj));
    Obj->time_cnt--;
    if(Obj->direction == 0)
    _Missile_bullet_update_position(self, -Obj->v, 0);
    if(Obj->direction == 1)
    _Missile_bullet_update_position(self, Obj->v, 0);
    if(Obj->direction == 2)
    _Missile_bullet_update_position(self, 0,  -Obj->v);
    if(Obj->direction == 3)
    _Missile_bullet_update_position(self, 0, +Obj->v);

}
void _Missile_bullet_update_position(Elements *self, int dx, int dy)
{
    Missile_bullet *Obj = ((Missile_bullet *)(self->pDerivedObj));
    Obj->x += dx;
    Obj->y += dy;
    Shape *hitbox = Obj->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}
void Missile_bullet_interact(Elements *self, Elements *tar)
{
    Missile_bullet *Obj = ((Missile_bullet *)(self->pDerivedObj));
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
    else if (tar->label == Tree_L)
    {
        Tree *tree = ((Tree *)(tar->pDerivedObj));
        if (tree->hitbox->overlap(tree->hitbox, Obj->hitbox))
        {
            self->dele = true;
        }
    }
    else if (tar->label == House_L)
    {
        House *tree = ((House *)(tar->pDerivedObj));
        if (tree->hitbox->overlap(tree->hitbox, Obj->hitbox))
        {
            self->dele = true;
        }
    }
}
void Missile_bullet_draw(Elements *self)
{
    Missile_bullet *Obj = ((Missile_bullet *)(self->pDerivedObj));
    if(Obj->direction == 0)
    al_draw_bitmap(Obj->img3, Obj->x-ONE_GRID, Obj->y+ONE_GRID, 0);
    if(Obj->direction == 1)
    al_draw_bitmap(Obj->img1, Obj->x+ONE_GRID, Obj->y+ONE_GRID, 0);
    if(Obj->direction == 2)
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
    if(Obj->direction == 3)
    al_draw_bitmap(Obj->img2, Obj->x, Obj->y+2*ONE_GRID, 0);
}
void Missile_bullet_destory(Elements *self)
{
    Missile_bullet *Obj = ((Missile_bullet *)(self->pDerivedObj));
    al_destroy_sample_instance(Obj->atk_Sound);
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}

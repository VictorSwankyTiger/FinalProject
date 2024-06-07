#include "floor.h"
#include <stdio.h>
/*
   [floor function]
*/
Elements *New_Floor(int label)
{
    Floor *pDerivedObj = (Floor *)malloc(sizeof(Floor));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/trans.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    _Floor_load_map(pDerivedObj);
    pDerivedObj->x = 0;
    pDerivedObj->y = 0;
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Character_L;
    pObj->inter_obj[pObj->inter_len++] = Character2_L;
    pObj->inter_obj[pObj->inter_len++] = Character1_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Draw = Floor_draw;
    pObj->Update = Floor_update;
    pObj->Interact = Floor_interact;
    pObj->Destroy = Floor_destory;
    return pObj;
}
void _Floor_load_map(Floor *floor)
{
    FILE *data;
    data = fopen("assets/map/gamescene_map.txt", "r");
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            fscanf(data, "%d", &floor->map_data[i][j]);
        }
    }
    fclose(data);
}
void Floor_update(Elements *ele) {}
void Floor_interact(Elements *self, Elements *tar)
{
    if (tar->label == Character_L)
    {
        Character *chara = (Character *)(tar->pDerivedObj);
        int right_limit = WIDTH - chara->width;// / 2;
        int left_limit = (WIDTH - BOARD_W);// - chara->width / 2;
        
        int down_limit = HEIGHT - chara->height;
        int up_limit = chara->width - chara->height;
        
        if (chara->x < left_limit)
        {
            _Character_update_position(tar, (left_limit - chara->x), 0);
        }
        else if (chara->x > right_limit)
        {
            _Character_update_position(tar, (right_limit - chara->x), 0);
        }
        else if (chara->y < up_limit)
        {
            _Character_update_position(tar, 0, (up_limit - chara->y));
        }
        else if (chara->y > down_limit)
        {
            _Character_update_position(tar, 0, (down_limit - chara->y));
        }
    }

if (tar->label == Character1_L)
    {
        Character1 *chara = (Character1 *)(tar->pDerivedObj);
        int right_limit = WIDTH - chara->width;// / 2;
        int left_limit = (WIDTH - BOARD_W);// - chara->width / 2;
        
        int down_limit = HEIGHT - chara->height;
        int up_limit = chara->width - chara->height;
        
        if (chara->x < left_limit)
        {
            _Character1_update_position(tar, (left_limit - chara->x), 0);
        }
        else if (chara->x > right_limit)
        {
            _Character1_update_position(tar, (right_limit - chara->x), 0);
        }
        else if (chara->y < up_limit)
        {
            _Character1_update_position(tar, 0, (up_limit - chara->y));
        }
        else if (chara->y > down_limit)
        {
            _Character1_update_position(tar, 0, (down_limit - chara->y));
        }
    }

    if (tar->label == Character2_L)
    {
        Character2 *chara = (Character2 *)(tar->pDerivedObj);
        int right_limit = WIDTH - chara->width / 2;
        int left_limit = 205 - chara->width / 2;
        
        int down_limit = HEIGHT - chara->height ;
        int up_limit = -10 ;
        
        if (chara->x < left_limit)
        {
            _Character2_update_position(tar, (left_limit - chara->x), 0);
        }
        else if (chara->x > right_limit)
        {
            _Character2_update_position(tar, (right_limit - chara->x), 0);
        }
        else if (chara->y < up_limit)
        {
            _Character2_update_position(tar, 0, (up_limit - chara->y));
        }
        else if (chara->y > down_limit)
        {
            _Character2_update_position(tar, 0, (down_limit - chara->y));
        }
    }
}
void Floor_draw(Elements *self)
{
    Floor *Obj = ((Floor *)(self->pDerivedObj));
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (Obj->map_data[i][j])
            {
                al_draw_bitmap(Obj->img, Obj->x + j * Obj->width, Obj->y + i * Obj->height, 0);
            }
        }
    }
}
void Floor_destory(Elements *self)
{
    Floor *Obj = ((Floor *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj);
    free(self);
}

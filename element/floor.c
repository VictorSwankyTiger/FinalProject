#include "floor.h"
#include "../scene/sceneManager.h"
#include <stdio.h>
/*
   [floor function]
*/
Elements *New_Floor(int label)
{
    Floor *pDerivedObj = (Floor *)malloc(sizeof(Floor));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/barrier.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    _Floor_load_map(pDerivedObj);
    pDerivedObj->x = 0;
    pDerivedObj->y = 0;
    pDerivedObj->draw = false;

    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Character_L;
    pObj->inter_obj[pObj->inter_len++] = Character2_L;
    pObj->inter_obj[pObj->inter_len++] = Character1_L;
    pObj->inter_obj[pObj->inter_len++] = Snow_L;
    pObj->inter_obj[pObj->inter_len++] = Fire_L;
    pObj->inter_obj[pObj->inter_len++] = Missile_L;
    pObj->inter_obj[pObj->inter_len++] = Wall_L;

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
    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            fscanf(data, "%d", &floor->map_data[i][j]);
            // printf("%d ",floor->map_data[i][j]);
        }
        // printf("\n");
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

    // for (int i = 0; i < 14; i++)
    // {
    //     for (int j = 0; j < 15; j++)
    //     {
    //         if (Obj->map_data[i][j] == 1)
    //         {
    //             //al_draw_bitmap(Obj->img, Obj->x + j * Obj->width, Obj->y + i * Obj->height, 0);

    //         }
    //         if (Obj->map_data[i][j] == 2)
    //         {
    //             Elements *snow;
    //             snow = New_Snow(Snow_L, Obj->x + j * Obj->width + 190, Obj->y + i * Obj->height);
    //             _Register_elements(scene, snow);
    //         }


    //     }
    // }
}
void Floor_draw(Elements *self)
{
    // Floor *Obj = ((Floor *)(self->pDerivedObj));
    // if(Obj->draw == false){
    //     for (int i = 0; i < 14; i++)
    //     {
    //         for (int j = 0; j < 15; j++)
    //         {
    //             if (Obj->map_data[i][j] == 1)
    //             {
    //                 // al_draw_bitmap(Obj->img, Obj->x + j * Obj->width+190, Obj->y + i * Obj->height, 0);
    //                 Elements *wall;
    //                 wall = New_Wall(Wall_L, Obj->x + j * Obj->width + 190, Obj->y + i * Obj->height);
    //                 _Register_elements(scene, wall);
    //             }
    //             if (Obj->map_data[i][j] == 2)
    //             {
    //                 Elements *snow;
    //                 snow = New_Snow(Snow_L, Obj->x + j * Obj->width + 190, Obj->y + i * Obj->height);
    //                 _Register_elements(scene, snow);
    //             }
    //             if (Obj->map_data[i][j] == 3)
    //             {
    //                 Elements *fire;
    //                 fire = New_Fire(Fire_L, Obj->x + j * Obj->width + 190, Obj->y + i * Obj->height);
    //                 _Register_elements(scene, fire);
    //             }
    //             if (Obj->map_data[i][j] == 4)
    //             {
    //                 Elements *missile;
    //                 missile = New_Missile(Missile_L, Obj->x + j * Obj->width + 190, Obj->y + i * Obj->height);
    //                 _Register_elements(scene, missile);
    //             }
    //             if (Obj->map_data[i][j] == 5)
    //             {
    //                 Elements *fire;
    //                 fire = New_Fire(Fire_L, Obj->x + j * Obj->width + 190, Obj->y + i * Obj->height);
    //                 _Register_elements(scene, fire);
    //             }
    //         }
    //     }
    //     Obj->draw = true;
    // }
    
}
void Floor_destory(Elements *self)
{
    Floor *Obj = ((Floor *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj);
    free(self);
}

#include "gamescene.h"
/*
   [GameScene function]
*/
Scene *New_GameScene(int label)
{
    GameScene *pDerivedObj = (GameScene *)malloc(sizeof(GameScene));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->background = al_load_bitmap("assets/image/stage10.png");
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 15, 0);
    pDerivedObj->x = 0;
    pDerivedObj->y = 0;
    pDerivedObj->map_x = WIDTH - BOARD_W;
    pDerivedObj->map_y = 0;
    pObj->pDerivedObj = pDerivedObj;
    // register element
    _Register_elements(pObj, New_Floor(Floor_L));
    _Register_elements(pObj, New_Teleport(Teleport_L));
    _Register_elements(pObj, New_Tree(Tree_L));
    // _Register_elements(pObj, New_Wall(Wall_L,975,725));
    game_scene_load_map(pObj);
    game_scene_register_map(pObj);
    // _Register_elements(pObj, New_Fire(Fire_L,975,725));
    // _Register_elements(pObj, New_Snow(Snow_L,200,725));
    // _Register_elements(pObj, New_Fire(Fire_L,200,725));
    
    // _Register_elements(pObj, New_Missile(Missile_L,200,0));
    // setting derived object function
    pObj->Update = game_scene_update;
    pObj->Draw = game_scene_draw;
    pObj->Destroy = game_scene_destroy;
    return pObj;
}
void game_scene_load_map(Scene *self)
{
    FILE *data;
    GameScene *gs = ((GameScene *)(self->pDerivedObj));
    if(map_mode == 0)data = fopen("assets/map/gamescene_map.txt", "r");
    if(map_mode == 1)data = fopen("assets/map/scene1.txt", "r");
    if(map_mode == 2)data = fopen("assets/map/scene4.txt", "r");
    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            fscanf(data, "%d", &gs->map_data[i][j]);
        }
    }
    if(map_mode == 0)data = fopen("assets/map/item_map.txt", "r");
    if(map_mode == 1)data = fopen("assets/map/item1.txt", "r");
    if(map_mode == 2)data = fopen("assets/map/scene4.txt", "r");
    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            fscanf(data, "%d", &gs->item_map[i][j]);
        }
    }
    fclose(data);
}
void game_scene_register_map(Scene *self)
{
    GameScene *gs = ((GameScene *)(self->pDerivedObj));
    Elements *ele;
    int label;


    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (gs->item_map[i][j] == 0)
            {
                MAP[i][j] = 0;
            }
            if (gs->item_map[i][j] == 1)
            {
                Elements *wall;
                wall = New_Wall(Wall_L, gs->map_x + j * ONE_GRID  , gs->map_y + i * ONE_GRID);
                _Register_elements(self, wall);

                MAP[i][j] = 1;
            }
            if (gs->item_map[i][j] == 2)
            {
                Elements *chara;
                chara = New_Character(Character_L, gs->map_x + j * ONE_GRID , gs->map_y + i * ONE_GRID, i, j);
                _Register_elements(self, chara);

                MAP[i][j] = 0;
            }
            if (gs->item_map[i][j] == 3)
            {
                Elements *chara;
                chara = New_Character1(Character1_L, gs->map_x + j * ONE_GRID , gs->map_y + i * ONE_GRID, i, j);
                _Register_elements(self, chara);

                MAP[i][j] = 0;
            }

            if (gs->item_map[i][j] == 4)
            {
                Elements *snow;
                snow = New_Snow(Snow_L, gs->map_x + j * ONE_GRID , gs->map_y + i * ONE_GRID);
                _Register_elements(self, snow);

                MAP[i][j] = 0;
            }
            if (gs->item_map[i][j] == 5)
            {
                Elements *fire;
                fire = New_Fire(Fire_L, gs->map_x + j * ONE_GRID , gs->map_y + i * ONE_GRID);
                _Register_elements(self, fire);

                MAP[i][j] = 0;
            }
            if (gs->item_map[i][j] == 6)
            {
                Elements *missile;
                missile = New_Missile(Missile_L, gs->map_x + j * ONE_GRID , gs->map_y + i * ONE_GRID);
                _Register_elements(self, missile);
                
                MAP[i][j] = 0;
            }
            if (gs->item_map[i][j] == 7)
            {
                Elements *fire;
                fire = New_Fire(Fire_L, gs->map_x + j * ONE_GRID , gs->map_y + i * ONE_GRID);
                _Register_elements(self, fire);

                MAP[i][j] = 0;
            }
            if (gs->item_map[i][j] == 8)
            {
                Elements *house;
                house = New_House(House_L, gs->map_x + j * ONE_GRID , gs->map_y + i * ONE_GRID,i,j);
                _Register_elements(self, house);

                MAP[i][j] = 2;
            }
            if (gs->item_map[i][j] == 9)
            {
                Elements *heart;
                heart = New_Buff(Buff_L, gs->map_x + j * ONE_GRID , gs->map_y + i * ONE_GRID);
                _Register_elements(self, heart);
                MAP[i][j] = 0;
            }
            if (gs->item_map[i][j] == 10)
            {
                Elements *heart;
                heart = New_Strength(Stren_L, gs->map_x + j * ONE_GRID , gs->map_y + i * ONE_GRID);
                _Register_elements(self, heart);
                MAP[i][j] = 0;
            }
            
        }
    }


    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (gs->map_data[i][j] == 0)
            {
                MAP[i][j] = 0;
            }
            if (gs->map_data[i][j] == 1)
            {
                Elements *wall;
                wall = New_Wall(Wall_L, gs->map_x + j * ONE_GRID  , gs->map_y + i * ONE_GRID);
                _Register_elements(self, wall);

                MAP[i][j] = 1;
            }
            if (gs->map_data[i][j] == 2)
            {
                Elements *chara;
                chara = New_Character(Character_L, gs->map_x + j * ONE_GRID , gs->map_y + i * ONE_GRID, i, j);
                _Register_elements(self, chara);

                MAP[i][j] = 0;
            }
            if (gs->map_data[i][j] == 3)
            {
                Elements *chara;
                chara = New_Character1(Character1_L, gs->map_x + j * ONE_GRID , gs->map_y + i * ONE_GRID, i, j);
                _Register_elements(self, chara);

                MAP[i][j] = 0;
            }

            if (gs->map_data[i][j] == 4)
            {
                Elements *snow;
                snow = New_Snow(Snow_L, gs->map_x + j * ONE_GRID , gs->map_y + i * ONE_GRID);
                _Register_elements(self, snow);

                MAP[i][j] = 0;
            }
            if (gs->map_data[i][j] == 5)
            {
                Elements *fire;
                fire = New_Fire(Fire_L, gs->map_x + j * ONE_GRID , gs->map_y + i * ONE_GRID);
                _Register_elements(self, fire);

                MAP[i][j] = 0;
            }
            if (gs->map_data[i][j] == 6)
            {
                Elements *missile;
                missile = New_Missile(Missile_L, gs->map_x + j * ONE_GRID , gs->map_y + i * ONE_GRID);
                _Register_elements(self, missile);
                
                MAP[i][j] = 0;
            }
            if (gs->map_data[i][j] == 7)
            {
                Elements *fire;
                fire = New_Fire(Fire_L, gs->map_x + j * ONE_GRID , gs->map_y + i * ONE_GRID);
                _Register_elements(self, fire);

                MAP[i][j] = 0;
            }
            if (gs->map_data[i][j] == 8)
            {
                Elements *house;
                house = New_House(House_L, gs->map_x + j * ONE_GRID , gs->map_y + i * ONE_GRID,i,j);
                _Register_elements(self, house);

                MAP[i][j] = 2;
            }
            if (gs->map_data[i][j] == 9)
            {
                Elements *heart;
                heart = New_Buff(Buff_L, gs->map_x + j * ONE_GRID , gs->map_y + i * ONE_GRID);
                _Register_elements(self, heart);
                MAP[i][j] = 0;
            }
            if (gs->map_data[i][j] == 10)
            {
                Elements *heart;
                heart = New_Strength(Stren_L, gs->map_x + j * ONE_GRID , gs->map_y + i * ONE_GRID);
                _Register_elements(self, heart);
                MAP[i][j] = 0;
            }
            
        }
    }

}
void game_scene_update(Scene *self)
{
    // update every element
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        allEle.arr[i]->Update(allEle.arr[i]);
    }

    // run interact for every element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        // run every interact object
        for (int j = 0; j < ele->inter_len; j++)
        {
            int inter_label = ele->inter_obj[j];
            ElementVec labelEle = _Get_label_elements(self, inter_label);
            for (int i = 0; i < labelEle.len; i++)
            {
                ele->Interact(ele, labelEle.arr[i]);
            }
        }
    }
    // remove element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        if (ele->dele)
            _Remove_elements(self, ele);
    }

    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        if (ele->label == Character_L){
            Character *chara = (Character *)ele->pDerivedObj;
            if(chara->live <= 0){
                self->scene_end = true;
                window = 3;
                return;
            }
        }
        if (ele->label == Character1_L){
            Character1 *chara = (Character1 *)ele->pDerivedObj;
            if(chara->live <= 0){
                self->scene_end = true;
                window = 2;
                return;
            }
        }
       
    }

    if (key_state[ALLEGRO_KEY_P])
    {
        self->scene_end = true;
        window = 0;
        return;
    }
}
void game_scene_draw(Scene *self)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    GameScene *gs = ((GameScene *)(self->pDerivedObj));
    al_draw_bitmap(gs->background, 0, 0, 0);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }
    al_draw_text(gs->font, al_map_rgb(0, 0, 0), 100, 785, ALLEGRO_ALIGN_CENTRE, "Press P");
    ALLEGRO_BITMAP *logout = al_load_bitmap("assets/image/logout.png");
    al_draw_bitmap(logout, 5, 780, 0);
}
void game_scene_destroy(Scene *self)
{
    GameScene *Obj = ((GameScene *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background;
    al_destroy_bitmap(background);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Destroy(ele);
    }
    free(Obj);
    free(self);
}

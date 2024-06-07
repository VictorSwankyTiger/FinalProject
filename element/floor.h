#ifndef FLOOR_H_INCLUDED
#define FLOOR_H_INCLUDED
#include "element.h"
#include "charater.h"
#include "charater2.h"
#include "charater1.h"
#include "fire.h"
#include "snow.h"
#include "missile.h"
#include "wall.h"
//#include "wall.h"
//#include "building.h"
#include "../scene/gamescene.h" // for element label
/*
   [floor object]
*/
typedef struct _Floor
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    bool draw;
    ALLEGRO_BITMAP *img;

    int map_data[14][15];
} Floor;

Elements *New_Floor(int label);
void _Floor_load_map(Floor *floor);
void Floor_update(Elements *self);
void Floor_interact(Elements *self, Elements *tar);
void Floor_draw(Elements *self);
void Floor_destory(Elements *self);

#endif

#ifndef SCENEMANAGER_H_INCLUDED
#define SCENEMANAGER_H_INCLUDED
#include "scene.h"
extern Scene *scene;
typedef enum SceneType
{
    Menu_L = 0,
    GameScene_L,
    GameOver1_L,
    GameOver_L,
} SceneType;
void create_scene(SceneType);

#endif
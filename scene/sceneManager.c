#include "sceneManager.h"
#include "menu.h"
#include "gamescene.h"
#include "gameover1.h"
#include "gameover.h"
Scene *scene = NULL;
void create_scene(SceneType type)
{
    switch (type)
    {
    case Menu_L:
        scene = New_Menu(Menu_L);
        break;
    case GameScene_L:
        scene = New_GameScene(GameScene_L);
        break;
    case GameOver_L:
        scene = New_Gameover(GameOver_L);
        break;
    case GameOver1_L:
        scene = New_Gameover1(GameOver1_L);
        break;
    
    default:
        break;
    }
}
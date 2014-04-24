//
//  HSceneManager.cpp
//  Bejeweled
//
//  Created by wilford on 14-1-3.
//
//

#include "HSceneManager.h"

HSceneManager* HSceneManager::instance = NULL;

void HSceneManager::changeScene(M_SCENE m_scene,void* data){
    HScene* scene = NULL;
    
    switch (m_scene) {
        case M_SCENE_LOGO:
            scene = LogoScene::create();
            break;
        case M_SCENE_GAME:
            scene = GameScene::create();
            break;
        case M_SCENE_MENU:
            scene = MenuScene::create();
            break;
        default:
            scene = MainScene::create();
            break;
    }
    if (scene) {
        scene->addSceneChangeEvent(this,h_scenechangeEvent(HSceneManager::changeScene));
        scene->setData(data);
        LoadingScene::Load(scene);
    }
    HWindowsManager::S()->closeAllWindows();
}



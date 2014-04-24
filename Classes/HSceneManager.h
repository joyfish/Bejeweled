//
//  HSceneManager.h
//  Bejeweled
//
//  Created by wilford on 14-1-3.
//
//

#ifndef __Bejeweled__HSceneManager__
#define __Bejeweled__HSceneManager__

#include "cocos2d.h"
#include "LogoScene.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "MainScene.h"

USING_NS_CC;

class HSceneManager : public CCObject{
public:
    static HSceneManager* S(){
        if (instance==NULL) {
            instance = new HSceneManager();
        }
        return instance;
    }
    
    void release(){
        CC_SAFE_DELETE(instance);
    }
    
    void changeScene(M_SCENE m_scene,void* data);
    
private:
    static HSceneManager* instance;
};

#endif /* defined(__Bejeweled__HSceneManager__) */

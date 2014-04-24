//
//  MenuScene.h
//  Bejeweled
//
//  Created by wilford on 14-1-6.
//
//

#ifndef __Bejeweled__MenuScene__
#define __Bejeweled__MenuScene__

#include "HScene.h"
#include "Setting.h"
#include "GameReady.h"
#include "GameLose.h"
#include "GameWin.h"
#include "GamePause.h"
#include "HoleModeShow.h"
#include "HoleModeResult.h"
#include "HoleModeInfo.h"
#include "HoleModeOpenTips.h"
#include "ToolBuy.h"
#include "GameStart.h"
#include "Shop.h"
#include "ShopBuyed.h"
#include "QuickBuy.h"
#include "RewardGet.h"
#include "GameQuit.h"

class MenuScene : public HScene,public cocos2d::CCKeypadDelegate{
public:
    CREATE_FUNC(MenuScene);
    
	virtual void onEnter();
    
    virtual void onExit(){
        HScene::onExit();
        CCDirector::sharedDirector()->getKeypadDispatcher()->removeDelegate(this);
    }
    
    virtual void keyBackClicked() {
//        if (!HWindowsManager::S()->hasWindowsShowed()) {
//            onBackClicked(NULL);
//        }
         GameQuit::show(m_layer);
    }
    
    virtual void loadResource();
	virtual void ReleaseResource();
    
    void onSettingClicked(CCObject* sender);
    void onBackClicked(CCObject* sender);
    void onPlayClicked(CCObject* sender);

    void onStarMovedOver(CCNode* o);
private:
    
};

#endif /* defined(__Bejeweled__MenuScene__) */

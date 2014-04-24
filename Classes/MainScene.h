//
//  MainScene.h
//  Bejeweled
//
//  Created by wilford on 14-1-8.
//
//

#ifndef __Bejeweled__MainScene__
#define __Bejeweled__MainScene__

#include "HScene.h"
#include "QuickBuy.h"
#include "Shop.h"
#include "GameStartShow.h"
#include "ShareWindow.h"
#include "Achievement.h"
#include "AchieveCompleted.h"
#include "HoleModeInfo.h"
#include "HoleModeShow.h"
#include "HoleModeOpenTips.h"
#include "Bao.h"
#include "BaoGet.h"
#include "GameQuit.h"
#include "SeaModeInfo.h"
#include "SeaModeShow.h"
#include "SeaModeOpenTips.h"
#include "TurnTable.h"

class MainScene : public HScene,public cocos2d::CCKeypadDelegate{
public:
    CREATE_FUNC(MainScene);
    
	virtual void onEnter();
    
    virtual void onExit(){
        HScene::onExit();
         CCDirector::sharedDirector()->getKeypadDispatcher()->removeDelegate(this);
    }
    virtual void update(float dt);
    
    
    bool updateTurnTable();
    bool updateAchievement();
    bool updateBao();
    bool updateHoleNewShow(){
        if (HWindowsManager::S()->hasWindowsShowed()) {
            return false;
        }
        if (G::g_hole_isOpened) {
            if (!G::g_hole_isNewShowed) {
                HoleModeOpenTips::show(m_layer);
                G::g_hole_isNewShowed = true;
                HPersistence::S()->SaveToFile();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
                HJNI::callumeng("event6");
#endif
            }
        }
        return false;
    }
    
    bool updateSeaNewShow(){
        if (HWindowsManager::S()->hasWindowsShowed()) {
            return false;
        }
        if (G::g_sea_isOpened) {
            if (!G::g_sea_isNewShowed) {
                SeaModeOpenTips::show(m_layer);
                G::g_sea_isNewShowed = true;
                HPersistence::S()->SaveToFile();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
                HJNI::callumeng("event7");
#endif
            }
        }
        return false;
    }
    
    virtual void loadResource();
	virtual void ReleaseResource();
    
    virtual void keyBackClicked() {
//        if (!HWindowsManager::S()->hasWindowsShowed()) {
//            onBack(NULL);
//        }
         GameQuit::show(m_layer);
    }
    
    void PopStage(UIWidget* icon_stage,float delay);

private:
    void showTreeAnim(bool fromTop = true);
    void onTreeAnimOver(CCNode* sender);
    void rePositionInnerForStage();
    
    void onTreeScrolled(CCObject* sender);
    void onSilderChanged(CCObject* sender);
    
    float initStage();
    void initBaoItems();
    void initCloud();
    
    void CLOUD_FADE_OUT(UIWidget* cloud){
        cloud->setTouchEnable(false);
        UIWidget* cloud_left = cloud->getChildByName("CLOUD_LEFT");
        UIWidget* cloud_up = cloud ->getChildByName("CLOUD_UP");
        UIWidget* cloud_right = cloud->getChildByName("CLOUD_RIGHT");
        UIWidget* label_click_me = cloud->getChildByName("LABEL_CLICK_ME");
        label_click_me->runAction(CCFadeOut::create(0.4f));
        cloud_left->runAction(CCFadeOut::create(0.4f));
        cloud_left->runAction(CCMoveBy::create(0.4f, ccp(-320, 0)));
        cloud_up->runAction(CCFadeOut::create(0.4f));
        cloud_up->runAction(CCMoveBy::create(0.4f, ccp(-320, 0)));
        cloud_right->runAction(CCFadeOut::create(0.4f));
        cloud_right->runAction(CCMoveBy::create(0.4f, ccp(320, 0)));
    }
    
    void updatePowerRecovery();
    void updateMainBtns();
    
    void onBack(CCObject* sender){
         G::G_playEffect(RES_MUSIC_NORMAL_CLICK);
        changeScene(M_SCENE_MENU);
    }
    
    void onQuickCoin(CCObject* sender);
    void onQuickPower(CCObject* sender);
    void onQuickBook(CCObject* sender);
    
    void onShopClicked(CCObject* sender);
    void onShareClicked(CCObject* sender);
    void onAchieveClicked(CCObject* sender);
    void onBaoClicked(CCObject* sender);
    void onTurnTableClicked(CCObject* sender);
    
    void onBaoItemClicked(CCObject* sender);
    
    void onHole(CCObject* sender);
    void onSea(CCObject* sender);
    
    void onStageClicked(CCObject* sender);
    
    void StartGame();
    
    void onCloudClicked(CCObject* sender);
    
    UIWidget* icon_stages[MAX_STAGE];
    COCO_UISCROLLVIEW* tree_scrollView;
    COCO_UISCROLLVIEW* sky_scrollview;
    COCO_UISLIDER* tree_bar;
    
    UILabelAtlas* m_powers;
    UILabelBMFont* m_coins;
    UILabelAtlas* m_books;
    UILabelBMFont* m_power_recovery_time;
    
    
    UIWidget* m_share_btn;
    UIWidget* m_shop_btn;
    UIWidget* m_achievement_btn;
    UIWidget* m_bao_btn;
    UIWidget* m_turntable_btn;
    
    UIWidget* m_hole_btn;
    UIWidget* m_sea_btn;
    bool m_turn_table_showed;
};

#endif /* defined(__Bejeweled__MainScene__) */

//
//  GameStartShow.h
//  Bejeweled
//
//  Created by wilford on 14-3-19.
//
//

#ifndef __Bejeweled__GameStartShow__
#define __Bejeweled__GameStartShow__

#include "HCCWindow.h"
#include "QuickBuy.h"
#include "HJNI.h"
#include "GameHelpMaskTips.h"

class GameStartShow : public HCCWindow{
    public:
    GameStartShow()
    :helpMask(NULL)
    ,m_help_id(-1)
    {
    }
    
    WINDOW_SINGTON_SHOW(GameStartShow)
    
    void addGameStartEvent(CCObject* target,SEL_VOIDCALLBACK selector){
        m_gamestartListener = target;
        m_gamestartSelector = selector;
    }
    
    AddVoidEvent(addCloseEvent, m_closeListener, m_closeSelector)
    
    protected:
    virtual void update(float dt);
    virtual void startAnim();
    
    private:
    void onStartGame(CCObject* sender);
    void onCloseClick(CCObject* sender){
        G::G_playEffect(RES_MUSIC_NORMAL_CLICK);
        if (!m_closeListener||!m_closeSelector) {
            closeWindow();
        }
        DoVoidEvent(m_closeListener, m_closeSelector);
    }
    
    void onShowLockOutOver(CCNode* sender,void* data){
        UIWidget* icon = (UIWidget*)data;
        showHelpMask(icon->getTag()*2);
    }
    
    void showHelpMask(int id){
        m_help_id = id;
        helpMask = CCUIHELPER->createWidgetFromJsonFile("HELP_MASK.json");
        helpMask->setZOrder(m_tips->getZOrder()+5);
        m_layer->addWidget(helpMask);
        UIPanel* top = (UIPanel*)helpMask->getChildByName("TOP");
        UIPanel* bottom =  (UIPanel*)helpMask->getChildByName("BOTTOM");
        UIPanel* left =  (UIPanel*)helpMask->getChildByName("LEFT");
        UIPanel* right =  (UIPanel*)helpMask->getChildByName("RIGHT");
       
        
        UIWidget* arrow_container = helpMask->getChildByName("ARROW_CONTAINER");
        arrow_container->setVisible(false);
        
        COCO_UIIMAGEVIEW* mask_img = COCO_UIIMAGEVIEW::create();
        CCPoint mask_pos = CCPointZero;
        int helpMask_id = 0;
        switch (id) {
            case 0://道具步数引导
            {
                mask_img -> setTexture("ccs/help/help_mask_20.png");
                helpMask_id = 35;
                mask_pos = G::getWorldPosition(m_tool_btns[0]);
                mask_pos.y+=40;
            }
                break;
            case 1://道具步数操作完成引导
            {
                mask_img -> setTexture("ccs/help/help_mask_21.png");
                helpMask_id = 36;
                UIWidget* btn_start = m_tips->getChildByName("btn_start");
                mask_pos = G::getWorldPosition(btn_start);
            }
                break;
            case 2://道具时间引导
            {
                mask_img -> setTexture("ccs/help/help_mask_20.png");
                helpMask_id = 37;
                mask_pos = G::getWorldPosition(m_tool_btns[1]);
                mask_pos.y+=40;
            }
                break;
            case 3://道具时间操作完成引导
            {
                mask_img -> setTexture("ccs/help/help_mask_21.png");
                helpMask_id = 38;
                UIWidget* btn_start = m_tips->getChildByName("btn_start");
                mask_pos = G::getWorldPosition(btn_start);
            }
                break;
            case 4://道具星星引导
            {
                mask_img -> setTexture("ccs/help/help_mask_20.png");
                helpMask_id = 39;
                mask_pos = G::getWorldPosition(m_tool_btns[2]);
                mask_pos.y+=40;
            }
                break;
            case 5://道具星星操作完成引导
            {
                mask_img -> setTexture("ccs/help/help_mask_21.png");
                helpMask_id = 40;
                UIWidget* btn_start = m_tips->getChildByName("btn_start");
                mask_pos = G::getWorldPosition(btn_start);
            }
                break;
                
            default:
                break;
        }
        helpMask->addChild(mask_img);
        mask_img->setPosition(mask_pos);
        CCSize mask_size =mask_img->getSize();
        CCRect rect = CCRectMake(mask_pos.x- mask_size.width/2, mask_pos.y-mask_size.height/2, mask_size.width, mask_size.height);
        CCSize screenSize = _pScreenSize;
        top->setPosition(ccp(0,rect.getMaxY()));
        top->setSize(CCSizeMake(screenSize.width,screenSize.height-rect.getMaxY()));
        bottom->setPosition(ccp(0,0));
        bottom->setSize(CCSizeMake(screenSize.width,rect.getMinY()));
        left->setPosition(ccp(0,rect.getMinY()));
        left->setSize(CCSizeMake(rect.getMinX(),rect.getMaxY()-rect.getMinY()));
        right->setPosition(ccp(rect.getMaxX(),rect.getMinY()));
        right->setSize(CCSizeMake(screenSize.width-rect.getMaxX(),rect.getMaxY()-rect.getMinY()));
        top->setBackGroundColorOpacity(255*7/10);
        bottom->setBackGroundColorOpacity(255*7/10);
        left->setBackGroundColorOpacity(255*7/10);
        right->setBackGroundColorOpacity(255*7/10);
        
        GameHelpMaskTips::show(m_layer,new GameHelpParam(helpMask_id,0));

    }
    
    void closeHelpMask(){
        if (helpMask) {
            helpMask->removeFromParent();
//            helpMask->runAction(CCSequence::create(CCDelayTime::create(0.5f),CCCallFuncND::create(this, callfuncND_selector(G::G_callbackRemoveUIWidget2), helpMask),NULL));
            helpMask = NULL;
        }
        if (GameHelpMaskTips::S()) {
            HWindowsManager::S()->closeWindow(GameHelpMaskTips::S());
        }
    }
    
    void onToolClick(CCObject* sender);
    
    static GameStartShow* instance;
    
    CCObject* m_closeListener;
    SEL_VOIDCALLBACK m_closeSelector;
    CCObject* m_gamestartListener;
    SEL_VOIDCALLBACK m_gamestartSelector;
    
    UIWidget* m_tool_btns[3];
    int m_tool_count[3];
    
    UIWidget* helpMask;
    int m_help_id;
};

#endif /* defined(__Bejeweled__GameStartShow__) */

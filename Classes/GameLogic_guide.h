//
//  GameLogic_guide.h
//  Bejeweled
//
//  Created by wilford on 14-3-9.
//
//

#ifndef __Bejeweled__GameLogic_guide__
#define __Bejeweled__GameLogic_guide__

#include "GameLogic_gameover.h"
#include "GameHelpMaskTips.h"
#include "GameStart.h"

typedef void (CCObject::*SEL_SHOWGAMEREADY)(GAMEMODE_TYPE mode);
#define h_showGameReady(_SELECTOR) (SEL_SHOWGAMEREADY)(&_SELECTOR)


class GameLogic_guide:public GameLogic_gameover{
    
public:
    void addGameReadyEvent(CCObject* target,SEL_SHOWGAMEREADY selector){
        m_showGameReady_listener = target;
        m_showGameReady_selector = selector;
    }
    
protected:
    GameLogic_guide()
    :m_showGameReady_listener(NULL)
    ,m_showGameReady_selector(NULL)
    ,m_gameReady_showed(false)
    ,m_gameStart_showed(false)
    ,mask_img(NULL)
    ,m_mask_fade_state(0)
    {
        m_max_mask_opacity = 255*7/10;
    }
    
    void showGameReady(GAMEMODE_TYPE mode);
    
    void updateGameReady();
    
    void updateGameStart();
    
    void updateGuide(float dt);
    
    void nextGuide();
    
    void FadeInMask();
    
    void FadeOutMask();
    
    void updateMaskOpacity(float dt);
    
    virtual void closeGuide();
    
    UIWidget* helpMask;
    
    CCObject* m_showGameReady_listener;
    SEL_SHOWGAMEREADY m_showGameReady_selector;
    
    COCO_UIIMAGEVIEW* mask_img;
    UIPanel* mask_panel[4];
    
    bool m_gameReady_showed;
    bool m_gameStart_showed;
    
    int m_mask_fade_state;//0 透明度不变 1 fadein 2 fadeout
    int m_current_mask_opacity;
    int m_max_mask_opacity;
};

#endif /* defined(__Bejeweled__GameLogic_guide__) */

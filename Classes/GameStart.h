//
//  GameStart.h
//  Bejeweled
//
//  Created by wilford on 14-1-10.
//
//

#ifndef __Bejeweled__GameStart__
#define __Bejeweled__GameStart__

#include "HCCWindow.h"
#include "QuickBuy.h"

class GameStart : public HCCWindow{
public:
    WINDOW_SINGTON_SHOW(GameStart)
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
        if (m_isClosed) {
            return;
        }
         //G::G_playEffect(RES_MUSIC_NORMAL_CLICK);
        m_isClosed = true;
        closeWindow();
        DoVoidEvent(m_closeListener, m_closeSelector);
    }
    
    static GameStart* instance;
    
    CCObject* m_closeListener;
    SEL_VOIDCALLBACK m_closeSelector;
    CCObject* m_gamestartListener;
    SEL_VOIDCALLBACK m_gamestartSelector;
    float m_open_time;
    float m_isClosed;
    
};


#endif /* defined(__Bejeweled__GameStart__) */

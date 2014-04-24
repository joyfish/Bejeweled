//
//  SeaModeShow.h
//  Bejeweled
//
//  Created by wilford on 14-3-30.
//
//

#ifndef __Bejeweled__SeaModeShow__
#define __Bejeweled__SeaModeShow__

#include "HCCWindow.h"
#include "QuickBuy.h"

class SeaModeShow : public HCCWindow{
public:
    WINDOW_SINGTON_SHOW(SeaModeShow)
    
    AddVoidEvent(addGameStartEvent, m_gamestartListener, m_gameStartSelector);
    AddVoidEvent(addCloseEvent, m_closeListener, m_closeSelector);
    
protected:
    virtual void update(float dt);
    virtual void startAnim();
    
    
private:
    void onGameStart(CCObject* sender);
    void onCloseClicked(CCObject* sender);
    
    void onWindowClosed();
    
    CCObject* m_gamestartListener;
    SEL_VOIDCALLBACK m_gameStartSelector;
    CCObject* m_closeListener;
    SEL_VOIDCALLBACK m_closeSelector;
    static SeaModeShow* instance;
};

#endif /* defined(__Bejeweled__SeaModeShow__) */

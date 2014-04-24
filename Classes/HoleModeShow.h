//
//  HoleModeShow.h
//  Bejeweled
//
//  Created by wilford on 13-12-31.
//
//

#ifndef __Bejeweled__HoleModeShow__
#define __Bejeweled__HoleModeShow__

#include "HCCWindow.h"
#include "QuickBuy.h"

class HoleModeShow : public HCCWindow{
public:
    WINDOW_SINGTON_SHOW(HoleModeShow)
    
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
    static HoleModeShow* instance;
};

#endif /* defined(__Bejeweled__HoleModeShow__) */

//
//  GameLose.h
//  Bejeweled
//
//  Created by wilford on 14-1-9.
//
//

#ifndef __Bejeweled__GameLose__
#define __Bejeweled__GameLose__

#include "HCCWindow.h"

class GameLose : public HCCWindow{
public:
    WINDOW_SINGTON_SHOW(GameLose)
    AddVoidEvent(addHomeEvent, m_homeListener, m_homeSelector)
    AddVoidEvent(addRetryEvent, m_retryListener, m_retrySelector)
    AddVoidEvent(addNextStageEvent, m_nextStageListener, m_nextStageSelector)
    
protected:
    virtual void startAnim();
private:
    void onHome(CCObject* sender);
    void onReTry(CCObject* sender);
    void onBuyNext(CCObject* sender);
    static GameLose* instance;
    
    CCObject* m_homeListener;
    SEL_VOIDCALLBACK m_homeSelector;
    CCObject* m_retryListener;
    SEL_VOIDCALLBACK m_retrySelector;
    CCObject* m_nextStageListener;
    SEL_VOIDCALLBACK m_nextStageSelector;
};


#endif /* defined(__Bejeweled__GameLose__) */

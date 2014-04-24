//
//  GameWin.h
//  Bejeweled
//
//  Created by wilford on 14-1-9.
//
//

#ifndef __Bejeweled__GameWin__
#define __Bejeweled__GameWin__

#include "HCCWindow.h"

class GameWin : public HCCWindow{
public:
    WINDOW_SINGTON_SHOW(GameWin)
    
    AddVoidEvent(addHomeEvent, m_homeListener, m_homeSelector)
    AddVoidEvent(addRetryEvent, m_retryListener, m_retrySelector)
    AddVoidEvent(addNextEvent, m_nextListener, m_nextSelector)
    
protected:
    virtual void startAnim();
private:
    void onHome(CCObject* sender);
    void onReStart(CCObject* sender);
    void onNext(CCObject* sender);
    
    int m_star;
    static GameWin* instance;
    
    CCObject* m_homeListener;
    SEL_VOIDCALLBACK m_homeSelector;
    CCObject* m_retryListener;
    SEL_VOIDCALLBACK m_retrySelector;
    CCObject* m_nextListener;
    SEL_VOIDCALLBACK m_nextSelector;
};

#endif /* defined(__Bejeweled__GameWin__) */

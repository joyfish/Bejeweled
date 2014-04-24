//
//  GamePause.h
//  Bejeweled
//
//  Created by wilford on 14-1-9.
//
//

#ifndef __Bejeweled__GamePause__
#define __Bejeweled__GamePause__

#include "HCCWindow.h"

class GamePause : public HCCWindow{
public:
    WINDOW_SINGTON_SHOW(GamePause)
    AddVoidEvent(addHomeEvent, m_homeListener, m_homeSelector)
    AddVoidEvent(addRetryEvent, m_retryListener, m_retrySelector)
    
protected:
    virtual void startAnim();
private:
    void onHome(CCObject* sender);
    void onReStart(CCObject* sender);
    void onContinue(CCObject* sender);
    static GamePause* instance;
    CCObject* m_homeListener;
    SEL_VOIDCALLBACK m_homeSelector;
    CCObject* m_retryListener;
    SEL_VOIDCALLBACK m_retrySelector;
};

#endif /* defined(__Bejeweled__GamePause__) */

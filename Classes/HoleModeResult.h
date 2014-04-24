//
//  HoleModeResult.h
//  Bejeweled
//
//  Created by wilford on 14-1-3.
//
//

#ifndef __Bejeweled__HoleModeResult__
#define __Bejeweled__HoleModeResult__

#include "HCCWindow.h"
#include "HoleModeShow.h"

class HoleModeResult : public HCCWindow{
public:
    WINDOW_SINGTON_SHOW(HoleModeResult)
    AddVoidEvent(addHomeEvent, m_homeListener, m_homeSelector);
    AddVoidEvent(addRestartEvent, m_restartListener, m_restartSelector);
    
protected:
    virtual void startAnim();
    
private:
    void onHome(CCObject* sender);
    void onRestart(CCObject* sender);
    
    int m_star;
    int m_totaldepth;
    int m_currentdepth;
    CCArray* m_rewards;
    static HoleModeResult* instance;
    CCObject* m_restartListener;
    SEL_VOIDCALLBACK m_restartSelector;
    CCObject* m_homeListener;
    SEL_VOIDCALLBACK m_homeSelector;
};

#endif /* defined(__Bejeweled__HoleModeResult__) */

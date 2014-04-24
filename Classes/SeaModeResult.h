//
//  SeaModeResult.h
//  Bejeweled
//
//  Created by wilford on 14-3-30.
//
//

#ifndef __Bejeweled__SeaModeResult__
#define __Bejeweled__SeaModeResult__

#include "HCCWindow.h"
#include "HoleModeShow.h"

class SeaModeResult : public HCCWindow{
public:
    WINDOW_SINGTON_SHOW(SeaModeResult)
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
    COCO_UILOADINGBAR* m_bar;
    int m_bar_percent;
    CCArray* m_rewards;
    static SeaModeResult* instance;
    CCObject* m_restartListener;
    SEL_VOIDCALLBACK m_restartSelector;
    CCObject* m_homeListener;
    SEL_VOIDCALLBACK m_homeSelector;
};

#endif /* defined(__Bejeweled__SeaModeResult__) */

//
//  GameEndBuy.h
//  Bejeweled
//
//  Created by wilford on 14-3-20.
//
//

#ifndef __Bejeweled__GameEndBuy__
#define __Bejeweled__GameEndBuy__

#include "HCCWindow.h"
#include "RewardGet.h"


class GameEndBuy : public HCCWindow{
    public:
    WINDOW_SINGTON_SHOW(GameEndBuy);
    AddVoidEvent(addLoseListener, m_lose_listener, m_lose_selector)
    AddVoidEvent(addContinueListener, m_continue_listener, m_continue_selector)
    virtual void update(float dt);
    
    protected:
    virtual void startAnim();
    void onCloseClicked(CCObject* sender);
    void onContinue(CCObject* sender);
    
    private:
    static GameEndBuy* instance;
    CCObject* m_lose_listener;
    SEL_VOIDCALLBACK m_lose_selector;
    CCObject* m_continue_listener;
    SEL_VOIDCALLBACK m_continue_selector;
};


#endif /* defined(__Bejeweled__GameEndBuy__) */

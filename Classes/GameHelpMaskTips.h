//
//  GameHelpMaskTips.h
//  Bejeweled
//
//  Created by wilford on 14-1-15.
//
//

#ifndef __Bejeweled__GameHelpMaskTips__
#define __Bejeweled__GameHelpMaskTips__

#include "HCCWindow.h"


class GameHelpMaskTips : public HCCWindow{
public:
    GameHelpMaskTips()
    :m_gameHelpMaskClosed_selector(NULL)
    ,m_gameHelpMaskClosed_listener(NULL)
    {
    
    }
    
    AddVoidEvent(addGameHelpMaskClosedEvent, m_gameHelpMaskClosed_listener, m_gameHelpMaskClosed_selector)
    
    WINDOW_SINGTON_SHOW(GameHelpMaskTips);
    void m_close(){
        closeWindow();
    }
    
    virtual void startAnim(); 

    
private:
    void onHelpMaskClosed(CCObject* obj){
        DoVoidEvent(m_gameHelpMaskClosed_listener, m_gameHelpMaskClosed_selector)
    }
    
    static GameHelpMaskTips* instance;
    CCObject* m_gameHelpMaskClosed_listener;
    SEL_VOIDCALLBACK m_gameHelpMaskClosed_selector;
};

#endif /* defined(__Bejeweled__GameHelpMaskTips__) */

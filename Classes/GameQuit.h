//
//  GameQuit.h
//  Bejeweled
//
//  Created by wilford on 14-1-17.
//
//

#ifndef __Bejeweled__GameQuit__
#define __Bejeweled__GameQuit__

#include "HCCWindow.h"

class GameQuit : public HCCWindow{
public:
    WINDOW_SINGTON_SHOW(GameQuit);
    
protected:
    virtual void startAnim();
    
private:
    void onCloseClicked(CCObject* sender);
    void onGameQuit(CCObject* sender);
    static GameQuit* instance;
};

#endif /* defined(__Bejeweled__GameQuit__) */

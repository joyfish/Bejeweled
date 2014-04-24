//
//  GameReady.h
//  Bejeweled
//
//  Created by wilford on 14-1-7.
//
//

#ifndef __Bejeweled__GameReady__
#define __Bejeweled__GameReady__

#include "HCCWindow.h"

class GameReady : public HCCWindow{
public:
    WINDOW_SINGTON_SHOW(GameReady)
    
protected:
    virtual void update(float dt);
    
private:
    void Play(GAMEMODE_TYPE mode);
    void onWindowClose(CCNode* sender);
    
    static GameReady* instance;
};


#endif /* defined(__Bejeweled__GameReady__) */

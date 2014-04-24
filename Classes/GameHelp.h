//
//  GameHelp.h
//  Bejeweled
//
//  Created by wilford on 14-1-15.
//
//

#ifndef __Bejeweled__GameHelp__
#define __Bejeweled__GameHelp__

#include "HCCWindow.h"

class GameHelp : public HCCWindow{
public:
    WINDOW_SHOW(GameHelp)
    
protected:
    virtual void startAnim();
    
private:
    void onClose(CCObject* sender);
};

#endif /* defined(__Bejeweled__GameHelp__) */

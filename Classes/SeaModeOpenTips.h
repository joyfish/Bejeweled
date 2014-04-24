//
//  SeaModeOpenTips.h
//  Bejeweled
//
//  Created by wilford on 14-3-30.
//
//

#ifndef __Bejeweled__SeaModeOpenTips__
#define __Bejeweled__SeaModeOpenTips__

#include "HCCWindow.h"

class SeaModeOpenTips : public HCCWindow{
public:
    WINDOW_SINGTON_SHOW(SeaModeOpenTips)
    
protected:
    virtual void startAnim();
    
private:
    void onCloseClicked(CCObject* sender);
    
    static SeaModeOpenTips* instance;
};

#endif /* defined(__Bejeweled__SeaModeOpenTips__) */

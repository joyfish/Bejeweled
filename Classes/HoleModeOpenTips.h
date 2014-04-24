//
//  HoleModeOpenTips.h
//  Bejeweled
//
//  Created by wilford on 14-1-9.
//
//

#ifndef __Bejeweled__HoleModeOpenTips__
#define __Bejeweled__HoleModeOpenTips__

#include "HCCWindow.h"

class HoleModeOpenTips : public HCCWindow{
public:
    WINDOW_SINGTON_SHOW(HoleModeOpenTips)
    
protected:
    virtual void startAnim();
    
private:
    void onCloseClicked(CCObject* sender);
    
    static HoleModeOpenTips* instance;
};


#endif /* defined(__Bejeweled__HoleModeOpenTips__) */

//
//  HoleModeInfo.h
//  Bejeweled
//
//  Created by wilford on 14-1-9.
//
//

#ifndef __Bejeweled__HoleModeInfo__
#define __Bejeweled__HoleModeInfo__

#include "HCCWindow.h"

class HoleModeInfo : public HCCWindow{
public:
    WINDOW_SINGTON_SHOW(HoleModeInfo)
    
protected:
    virtual void startAnim();
    
private:
    void onCloseClicked(CCObject* sender);
    
    static HoleModeInfo* instance;
};

#endif /* defined(__Bejeweled__HoleModeInfo__) */

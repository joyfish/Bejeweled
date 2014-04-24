//
//  SeaModeInfo.h
//  Bejeweled
//
//  Created by wilford on 14-3-30.
//
//

#ifndef __Bejeweled__SeaModeInfo__
#define __Bejeweled__SeaModeInfo__

#include "HCCWindow.h"

class SeaModeInfo : public HCCWindow{
public:
    WINDOW_SINGTON_SHOW(SeaModeInfo)
    
protected:
    virtual void startAnim();
    
private:
    void onCloseClicked(CCObject* sender);
    
    static SeaModeInfo* instance;
};

#endif /* defined(__Bejeweled__SeaModeInfo__) */

//
//  BaoInfo.h
//  Bejeweled
//
//  Created by wilford on 14-1-17.
//
//

#ifndef __Bejeweled__BaoInfo__
#define __Bejeweled__BaoInfo__

#include "HCCWindow.h"

class BaoInfo : public HCCWindow{
public:
    WINDOW_SINGTON_SHOW(BaoInfo);
    
protected:
    virtual void startAnim();
    
private:
    void initInfo(int id);
    void onCloseClicked(CCObject* sender);
    static BaoInfo* instance;
};

#endif /* defined(__Bejeweled__BaoInfo__) */

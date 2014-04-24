//
//  BaoGet.h
//  Bejeweled
//
//  Created by wilford on 14-1-17.
//
//

#ifndef __Bejeweled__BaoGet__
#define __Bejeweled__BaoGet__

#include "HCCWindow.h"

class BaoGet : public HCCWindow{
public:
    WINDOW_SINGTON_SHOW(BaoGet);
    
protected:
    virtual void startAnim();
    
private:
    void initInfo(int id);
    void onCloseClicked(CCObject* sender);
    static BaoGet* instance;
};

#endif /* defined(__Bejeweled__BaoGet__) */

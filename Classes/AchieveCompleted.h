//
//  AchieveCompleted.h
//  Bejeweled
//
//  Created by wilford on 14-1-16.
//
//

#ifndef __Bejeweled__AchieveCompleted__
#define __Bejeweled__AchieveCompleted__

#include "HCCWindow.h"

class AchieveCompleted : public HCCWindow{
public:
    WINDOW_SINGTON_SHOW(AchieveCompleted);
    
protected:
    virtual void startAnim();
    
private:
    void onCloseClicked(CCObject* sender);
    static AchieveCompleted* instance;
};

#endif /* defined(__Bejeweled__AchieveCompleted__) */

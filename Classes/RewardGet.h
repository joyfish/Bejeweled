//
//  RewardGet.h
//  Bejeweled
//
//  Created by wilford on 14-1-10.
//
//

#ifndef __Bejeweled__RewardGet__
#define __Bejeweled__RewardGet__

#include "HCCWindow.h"


class RewardGet : public HCCWindow{
public:
    WINDOW_SINGTON_SHOW(RewardGet)
    
protected:
    virtual void startAnim();
    void initItems(CCArray* rewards);
    
private:
    void onClose(CCObject* sender);
    
    static RewardGet* instance;
};

#endif /* defined(__Bejeweled__RewardGet__) */

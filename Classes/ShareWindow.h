//
//  Share.h
//  Bejeweled
//
//  Created by wilford on 14-1-15.
//
//

#ifndef __Bejeweled__Share__
#define __Bejeweled__Share__

#include "HCCWindow.h"
#include "RewardGet.h"


class Share : public HCCWindow{
public:
    WINDOW_SINGTON_SHOW(Share);
    virtual void update(float dt);
    
protected:
    virtual void startAnim();
    void onCloseClicked(CCObject* sender);
    void onQZone(CCObject* sender);
    void onWeixin(CCObject* sender);
	void onSina(CCObject* sender);
    
private:
    static Share* instance;
    UIWidget* btns[MAX_SHARE];
    UIWidget* des[MAX_SHARE];
    UIWidget* hasGot[MAX_SHARE];
};

#endif /* defined(__Bejeweled__Share__) */

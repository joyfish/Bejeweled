//
//  NormalTips.h
//  Bejeweled
//
//  Created by wilford on 14-1-14.
//
//

#ifndef __Bejeweled__NormalTips__
#define __Bejeweled__NormalTips__

#include "HCCWindow.h"

class NormalTips : public HCCWindow{
public:
    WINDOW_SHOW(NormalTips)
    
protected:
    void initDialog(int id,int param);
    virtual void startAnim();
    
private:
    void onClose(CCObject* sender);
    
};

#endif /* defined(__Bejeweled__NormalTips__) */

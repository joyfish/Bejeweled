//
//  QuickBuy.h
//  Bejeweled
//
//  Created by wilford on 14-1-10.
//
//

#ifndef __Bejeweled__QuickBuy__
#define __Bejeweled__QuickBuy__

#include "HCCWindow.h"
#include "NormalTips.h"
#include "Shop.h"

class QuickBuy : public HCCWindow{
public:
    WINDOW_SINGTON_SHOW(QuickBuy)
    
protected:
    void initQuickTip(UIWidget* tips,int type);
    virtual void startAnim();
    virtual void endAnim();
    
private:
    void onBuy(CCObject* sender);
    void onClose(CCObject* sender);
    
    static QuickBuy* instance;
    UIWidget* add_tips;
    int m_type;
};

#endif /* defined(__Bejeweled__QuickBuy__) */

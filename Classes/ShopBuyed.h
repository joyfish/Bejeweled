//
//  ShopBuyed.h
//  Bejeweled
//
//  Created by wilford on 14-1-10.
//
//

#ifndef __Bejeweled__ShopBuyed__
#define __Bejeweled__ShopBuyed__

#include "HCCWindow.h"

class ShopBuyed : public HCCWindow{
public:
    WINDOW_SHOW(ShopBuyed)
    
protected:
    virtual void startAnim();
    void initItems(CCArray* rewards);
    
private:
    void onBuyAgain(CCObject* sender);
    void onClose(CCObject* sender);
    
   // static ShopBuyed* instance;
};

#endif /* defined(__Bejeweled__ShopBuyed__) */

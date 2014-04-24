//
//  Shop.h
//  Bejeweled
//
//  Created by wilford on 14-1-10.
//
//

#ifndef __Bejeweled__Shop__
#define __Bejeweled__Shop__

#include "HCCWindow.h"
#include "UIScrollViewBar.h"
#include "ShopBuyed.h"
#include "NormalTips.h"

class Shop : public HCCWindow{
public:
    WINDOW_SINGTON_SHOW(Shop)
    
protected:
    virtual void releaseRes(){
        HCCWindow::releaseRes();
    }
    virtual void startAnim();
    virtual void update(float dt);
    void resetItems();
    
private:
    void onItemBuy(CCObject* sender);
    void onClose(CCObject* sender);
    
    
    COCO_UISCROLLVIEW* m_scroll_view;
    int m_last_maxPower;
    bool m_last_th_hasbuyed;
    bool m_last_ts_hasbuyed;
    UIScrollViewBar* m_bar;
    CCArray* m_items;
    UILabelBMFont* m_coin;
    static Shop* instance;
};

#endif /* defined(__Bejeweled__Shop__) */

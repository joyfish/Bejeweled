//
//  ToolBuy.h
//  Bejeweled
//
//  Created by wilford on 14-1-9.
//
//

#ifndef __Bejeweled__ToolBuy__
#define __Bejeweled__ToolBuy__

#include "HCCWindow.h"
#include "QuickBuy.h"

class ToolBuy : public HCCWindow{
public:
    WINDOW_SINGTON_SHOW(ToolBuy)
    
protected:
    virtual void startAnim();
    virtual void update(float dt);
    
private:
    void onCloseClicked(CCObject* sender);
    void onBuy(CCObject* sender);
    void onAddCoin(CCObject* sender);
    
    int m_tool_id;
    int m_count;
    int m_price;
    int m_curren_coin;
    UILabelBMFont* mCoin;
    static ToolBuy* instance;
};

#endif /* defined(__Bejeweled__ToolBuy__) */

//
//  TurnTable.h
//  Bejeweled
//
//  Created by wilford on 14-4-9.
//
//

#ifndef __Bejeweled__TurnTable__
#define __Bejeweled__TurnTable__

#include "HCCWindow.h"

class TurnTable : public HCCWindow{
public:
    WINDOW_SINGTON_SHOW(TurnTable)

    
protected:
    virtual void startAnim();
    
private:
    void onStart();
    
    int getTarget();
    
    void scrollToID(int id);
    
    void RotateOver();
    
    void showReward();
    
    void onCloseClick(CCObject sender);
    
    UIWidget* Rewards;
    UIWidget* arrow;
    UIWidget* m_show;
    UIWidget* circle_up;
    UIWidget* circle_down;
    int m_current_angle;
    COCO_UIBUTTON* btn_start;
    static TurnTable* instance;

};

#endif /* defined(__Bejeweled__TurnTable__) */

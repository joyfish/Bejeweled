//
//  Setting.h
//  Bejeweled
//
//  Created by wilford on 14-1-6.
//
//

#ifndef __Bejeweled__Setting__
#define __Bejeweled__Setting__

#include "HCCWindow.h"

class Setting : public HCCWindow{
public:
    Setting()
    :HCCWindow()
    ,setting_changed(false)
    {}
    WINDOW_SINGTON_SHOW(Setting)
    
protected:
    virtual void update(float dt);
    
private:
    void onSettingChanged(CCObject* sender);
    void onSettingSave(CCObject* sender);
    void onCloseClicked(CCObject* sender);
    

    COCO_UIIMAGEVIEW *b_on;
    COCO_UIIMAGEVIEW *b_off;
    COCO_UIIMAGEVIEW *e_on;
    COCO_UIIMAGEVIEW *e_off;
    
    bool m_isbackground;
    bool m_iseffect;
    bool setting_changed;
    static Setting* instance;
};

#endif /* defined(__Bejeweled__Setting__) */

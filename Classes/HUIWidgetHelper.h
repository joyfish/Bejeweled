//
//  HUIWidgetHelper.h
//  Bejeweled
//
//  Created by wilford on 14-1-1.
//
//

#ifndef __Bejeweled__HUIWidgetHelper__
#define __Bejeweled__HUIWidgetHelper__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class HUIWidgetHelper{
public:
    HUIWidgetHelper(UIWidget* widget);
    ~HUIWidgetHelper();
    
    void setTouchEnable(bool enabled);
    
private:
    void touchDisable(UIWidget* widget);
    
    UIWidget* m_widget;
    CCArray* m_touchEnabledchildren;
};

#endif /* defined(__Bejeweled__HUIWidgetHelper__) */

//
//  HUIWidgetHelper.cpp
//  Bejeweled
//
//  Created by wilford on 14-1-1.
//
//

#include "HUIWidgetHelper.h"

HUIWidgetHelper::HUIWidgetHelper(UIWidget* widget):
m_touchEnabledchildren(NULL),
m_widget(widget)
{}

HUIWidgetHelper::~HUIWidgetHelper(){
    if (m_touchEnabledchildren) {
        m_touchEnabledchildren->removeAllObjects();
    }
    CC_SAFE_DELETE(m_touchEnabledchildren);
}

void HUIWidgetHelper::setTouchEnable(bool enabled){
    if (enabled) {
        if (m_touchEnabledchildren) {
            CCObject* obj;
            CCARRAY_FOREACH(m_touchEnabledchildren,obj){
                UIWidget* child = (UIWidget*)obj;
                child->setTouchEnable(true);
            }
            m_touchEnabledchildren->removeAllObjects();
        }
    }else{
        if (!m_touchEnabledchildren) {
            m_touchEnabledchildren=new CCArray();
        }else
            m_touchEnabledchildren->removeAllObjects();
        touchDisable(m_widget);
    }
}

void HUIWidgetHelper::touchDisable(UIWidget* widget){
    if (!widget) {
        return;
    }
    
    if (widget->isTouchEnabled()) {
        m_touchEnabledchildren->addObject(widget);
        widget->setTouchEnable(false);
    }
    CCArray* w_childern = widget->getChildren();
    CCObject* obj;
    CCARRAY_FOREACH(w_childern, obj){
        UIWidget* child = (UIWidget*)obj;
        touchDisable(child);
    }
}
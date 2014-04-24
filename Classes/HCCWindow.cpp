//
//  HCCWindow.cpp
//  Bomb
//
//  Created by wilford on 13-12-20.
//
//

#include "HCCWindow.h"

HCCWindow::HCCWindow()
:m_tips(NULL)
,m_layer(NULL)
,m_widgetHelper(NULL)
,m_windowclosedListener(NULL)
,m_windowclosedselector(NULL)
,m_autoCenter(true)
,m_anim_type(WINDOW_ANIM_TOP)
{}

HCCWindow::~HCCWindow(){
	CC_SAFE_DELETE(m_widgetHelper);
    m_layer = NULL;
}

void HCCWindow::show(){
       if(m_tips){
        //UIPanel* _panel = (UIPanel*)m_tips;
        //_panel->setBackGroundColorOpacity(0);
        m_layer->addWidget(m_tips);
        m_tips->setZOrder(HWindowsManager::S()->getTopZOrder());
        setZOrder(m_tips->getZOrder());
        UIWidget* m_bg = m_tips->getChildByName("bg");
        if (m_autoCenter) {
             m_bg->setPosition(_pCenter);
        }
        if (m_bg) {
             m_widgetHelper = new HUIWidgetHelper(m_bg);
        }
    }
    HWindowsManager::S()->pushWindow(this);
    startAnim();
}

void HCCWindow::onClose(){
    HWindowsManager::S()->closeWindow(this);
}

void HCCWindow::close(){
    HIWindow::close();
    if (m_tips) {
        m_tips->removeFromParentAndCleanup(true);
        m_tips = NULL;
    }
}

void HCCWindow::setTocuhEnable(bool enabled){
    if (m_widgetHelper) {
        m_widgetHelper->setTouchEnable(enabled);
    }
}

void HCCWindow::closeWindow(){
    setTocuhEnable(false);
    endAnim();
}

void HCCWindow::startAnim(){
    if (m_tips!=NULL) {
        UIWidget* tips_bg = m_tips->getChildByName("bg");
        CCPoint pre_pos = tips_bg->getPosition();
        //tips_bg->runAction(CCFadeIn::create(0.1f));
        
        switch (m_anim_type) {
            case WINDOW_ANIM_TOP:
                tips_bg->setPosition(ccp(pre_pos.x, _pTop+480));
                tips_bg->runAction(CCSequence::create(CCMoveTo::create(0.3f, ccp(pre_pos.x, pre_pos.y-20)),CCMoveTo::create(0.1f, ccp(pre_pos.x, pre_pos.y+10)),CCMoveTo::create(0.1f, ccp(pre_pos.x, pre_pos.y)),NULL));
                break;
            case WINDOW_ANIM_RIGHT:
                tips_bg->setPosition(ccp(_pRight+640, pre_pos.y));
                tips_bg->runAction(CCSequence::create(CCMoveTo::create(0.3f, ccp(pre_pos.x-20, pre_pos.y)),CCMoveTo::create(0.1f, ccp(pre_pos.x+20, pre_pos.y)),CCMoveTo::create(0.1f, ccp(pre_pos.x, pre_pos.y)),NULL));
                break;
            default:
                break;
        }
      
    }

}

void HCCWindow::endAnim(){
    if (m_tips!=NULL) {
        UIWidget* tips_bg = m_tips->getChildByName("bg");
        CCPoint pre_pos = tips_bg->getPosition();
        //tips_bg->runAction(CCSequence::create(CCDelayTime::create(0.3f),CCFadeOut::create(0.1f),NULL));
        switch (m_anim_type) {
            case WINDOW_ANIM_TOP:
                tips_bg->runAction(CCSequence::create(CCMoveTo::create(0.1f, ccp(pre_pos.x, pre_pos.y-20)),CCMoveTo::create(0.3f,ccp(pre_pos.x, _pTop+480)),CCCallFuncN::create(this,callfuncN_selector(HCCWindow::onCloseAnimOver)), NULL));
                break;
            case WINDOW_ANIM_RIGHT:
                tips_bg->runAction(CCSequence::create(CCMoveTo::create(0.1f, ccp(pre_pos.x-20, pre_pos.y)),CCMoveTo::create(0.3f,ccp(pre_pos.x+640, pre_pos.y)),CCCallFuncN::create(this,callfuncN_selector(HCCWindow::onCloseAnimOver)), NULL));
                break;
            default:
                break;
        }

    }
}

void HCCWindow::onCloseAnimOver(CCNode* sender){
    if (m_windowclosedListener&&m_windowclosedselector) {
        (m_windowclosedListener->*m_windowclosedselector)();
    }
    onClose();
}
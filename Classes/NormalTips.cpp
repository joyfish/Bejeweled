//
//  NormalTips.cpp
//  Bejeweled
//
//  Created by wilford on 14-1-14.
//
//

#include "NormalTips.h"


void NormalTips::init(void *data){
    m_tips = CCUIHELPER->createWidgetFromJsonFile("NormalTips.json");
    NormalTipsParam* param = (NormalTipsParam*)data;
    int id = 0;
    int p = -1;
    if (param) {
        id = param->id;
        p = param->param;
    }
    CC_SAFE_DELETE(param);
    initDialog(id,p);
    setAnimType(WINDOW_ANIM_RIGHT);
}

void NormalTips::startAnim(){
    HCCWindow::startAnim();
    UIWidget* btn_close = m_tips->getChildByName("btn_close");
    PopNode(btn_close,0.4f);
    btn_close->addReleaseEvent(this, coco_releaseselector(NormalTips::onClose));
}

void NormalTips::initDialog(int id,int param){
    CCDictionary* _strings = CCDictionary::createWithContentsOfFile("data/normaltips.plist");
    UILabelBMFont* label = (UILabelBMFont*)m_tips->getChildByName("label");
    IntToStringFormat(_desKey, "tips_%d", id);
    CCString* _c_des = (CCString*)_strings->objectForKey(_desKey);
    if (param == -1) {
        label->setText(_c_des->getCString());
    }else{
        IntToStringFormat(_s_des, _c_des->getCString(),param);
        label->setText(_s_des);
    }
    CCSize labelSize= label->getSize();
    labelSize.height+=200;
    UIWidget* bg = m_tips->getChildByName("bg");
    bg->setSize(CCSizeMake(568, labelSize.height));
    UIWidget* btn_close = m_tips->getChildByName("btn_close");
    btn_close->setPosition(ccp(226,labelSize.height/2-69));
    _strings->release();
}


void NormalTips::onClose(cocos2d::CCObject *sender){
     G::G_playEffect(RES_MUSIC_NORMAL_CLICK);
    closeWindow();
}
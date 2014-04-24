//
//  BaoInfo.cpp
//  Bejeweled
//
//  Created by wilford on 14-1-17.
//
//

#include "BaoInfo.h"

void BaoInfo::init(void *data){
    m_tips = CCUIHELPER->createWidgetFromJsonFile("BaoInfo.json");
    BaoInfoParam* param = (BaoInfoParam*)data;
    int id = 0;
    if (param) {
        id = param->id;
    }
    CC_SAFE_DELETE(param);
    initInfo(id);
    setAnimType(WINDOW_ANIM_RIGHT);
}

void BaoInfo::initInfo(int id){
    BAO_INFO* info = (BAO_INFO*)G::g_bao_infos->objectAtIndex(id);
    UILabelBMFont* _name = (UILabelBMFont*)m_tips->getChildByName("name");
    UILabelBMFont* _des = (UILabelBMFont*)m_tips->getChildByName("label_from");
    UILabelBMFont* _from = (UILabelBMFont*)m_tips->getChildByName("label_des");
    UIImageView* _icon = (UIImageView*)m_tips->getChildByName("icon");
    CCDictionary* _strings = CCDictionary::createWithContentsOfFile("data/bao.plist");
    IntToStringFormat(_namekey,"bao_name_%d" , id);
    IntToStringFormat(_deskey,"bao_des_%d" , id);
    IntToStringFormat(_fromkey,"bao_from_%d" , id);
    CCString* _s_name = (CCString*)_strings->objectForKey(_namekey);
    CCString* _s_des = (CCString*)_strings->objectForKey(_deskey);
    CCString* _s_from = (CCString*)_strings->objectForKey(_fromkey);
    char _c_from[30];
    if (baos_level[id]>=0) {
        IntToStringFormat(_tmp_from,_s_from->getCString() , baos_level[id])
        sprintf(_c_from, "<%s>",_tmp_from);
    }else{
        sprintf(_c_from, "<%s>",_s_from->getCString());
    }
   
    
    _name->setText(_s_name->getCString());
    _des->setScale(1.2f);
    _des->setText(_s_des->getCString());
    _from->setText(_c_from);
    _from->setScale(1.2f);
    _from->setAnchorPoint(_nLeft);
    _from->setPosition(ccp(_des->getPosition().x, _des->getPosition().y-_des->getSize().height-40));
    _strings->release();
   
    IntToStringFormat(_iconName, "bao/icon_%d.png", id)
    _icon->setTexture(_iconName);
    if(baos_type[info->id]!=BAO_FROM_TREE&&baos_type[info->id]!=BAO_FROM_TURNTABLE){
        _icon->setScale(1.2f);
    }
    
    
    if (!info->isGot) {
//        IntToStringFormat(_iconName, "bao/icon_%d_a.png", id)
//        _icon->setTexture(_iconName);
         _icon->setColor(ccc3(0, 0, 0));
    }else{
        
         _icon->setColor(ccc3(255, 255, 255));
    }
}

void BaoInfo::startAnim(){
    HCCWindow::startAnim();
    UIWidget* btn_close = m_tips->getChildByName("btn_close");
    btn_close->setTouchEnable(true);
    btn_close->addReleaseEvent(this, coco_releaseselector(BaoInfo::onCloseClicked));
    PopNode(btn_close, 0.4f);
}

void BaoInfo::onCloseClicked(CCObject* sender){
    closeWindow();
}

BaoInfo* BaoInfo::instance;
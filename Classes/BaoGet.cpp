//
//  BaoGet.cpp
//  Bejeweled
//
//  Created by wilford on 14-1-17.
//
//

#include "BaoGet.h"

void BaoGet::init(void *data){
    m_tips = CCUIHELPER->createWidgetFromJsonFile("BaoGet.json");
    BaoInfoParam* param = (BaoInfoParam*)data;
    int id = 0;
    if (param) {
        id = param->id;
    }
    CC_SAFE_DELETE(param);
    initInfo(id);
    setAnimType(WINDOW_ANIM_RIGHT);
}

void BaoGet::initInfo(int id){
    BAO_INFO* info = (BAO_INFO*)G::g_bao_infos->objectAtIndex(id);
    UIImageView* _icon = (UIImageView*)m_tips->getChildByName("icon");
    UILabelBMFont* _name = (UILabelBMFont*)m_tips->getChildByName("name");
    CCDictionary* _strings = CCDictionary::createWithContentsOfFile("data/bao.plist");
    IntToStringFormat(_namekey,"bao_name_%d" , id);
    CCString* _s_name = (CCString*)_strings->objectForKey(_namekey);
    _name->setText(_s_name->getCString());
    _strings->release();

    IntToStringFormat(_iconName, "bao/icon_%d.png", id)
    _icon->setTexture(_iconName);
    if(baos_type[info->id]!=BAO_FROM_TREE&&baos_type[info->id]!=BAO_FROM_TURNTABLE){
        _icon->setScale(1.2f);
    }

    if (!info->isGot) {
        _icon->setColor(ccc3(0, 0, 0));
//        IntToStringFormat(_iconName, "bao/icon_%d_a.png", id)
//        _icon->setTexture(_iconName);
    }else{
         _icon->setColor(ccc3(255,255, 255));
    }
}

void BaoGet::startAnim(){
    HCCWindow::startAnim();
    UIWidget* btn_close = m_tips->getChildByName("btn_close");
    btn_close->setTouchEnable(true);
    btn_close->addReleaseEvent(this, coco_releaseselector(BaoGet::onCloseClicked));
    PopNode(btn_close, 0.4f);
}

void BaoGet::onCloseClicked(CCObject* sender){
    closeWindow();
}

BaoGet* BaoGet::instance;
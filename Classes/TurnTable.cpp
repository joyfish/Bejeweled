//
//  TurnTable.cpp
//  Bejeweled
//
//  Created by wilford on 14-4-9.
//
//

#include "TurnTable.h"

TurnTable* TurnTable::instance = NULL;

void TurnTable::init(void *data){
    m_tips = CCUIHELPER->createWidgetFromJsonFile("TurnTable.json");
    btn_start = (UIButton*)m_tips->getChildByName("btn_start");
    arrow = m_tips->getChildByName("arrow");
    m_show = m_tips->getChildByName("show");
    circle_up = m_tips->getChildByName("circle_up");
    circle_down = m_tips->getChildByName("circle_down");
    Rewards = m_tips->getChildByName("Rewards");
    m_show->setVisible(false);
    Rewards->setVisible(false);
    UIPanel* panel = (UIPanel*)Rewards;
    panel->setBackGroundColorOpacity(150);
    m_current_angle = 0;
    if (G::turntable_count == 0) {
        btn_start->disable();
    }
}

void TurnTable::startAnim(){
    HCCWindow::startAnim();
    UIWidget* btn_close = m_tips->getChildByName("btn_close");
    PopNode(btn_start, 0.4f);
    PopNode(btn_close, 0.8f);
    btn_start->addReleaseEvent(this, coco_releaseselector(TurnTable::onStart));
    btn_close->addReleaseEvent(this, coco_releaseselector(TurnTable::onCloseClick));
}

void TurnTable::onStart(){
    btn_start->disable();
    scrollToID(getTarget());
}

int TurnTable::getTarget(){
    int rand = t_getRandom(100);
    int id = 0;
    int rates[] = {0,6,2,75,7,2,2,7};
    int total_rate = 0;
    for (int i=0; i<8; i++) {
        total_rate+=rates[i];
        if (rand<total_rate) {
            id = i;
            break;
        }
    }
    
    switch (id) {
        case 0://99挑战卷
            G::G_getReward(8, 99);
       
            break;
        case 1://iphone
        {
            
            BAO_INFO* info = (BAO_INFO*)G::g_bao_infos->objectAtIndex(42);
            if (!info->isGot) {
                info->isGot = true;
                HPersistence::S()->SaveBao(42);
            }
        }
            G::G_getReward(0, 2500);
            break;
        case 2://锤子+5
            G::G_getReward(4, 5);
            break;
        case 3://1000金币
            G::G_getReward(0, 1000);
            break;
        case 4://+5换位
            G::G_getReward(5, 5);
            break;
        case 5://ipad
        {
            BAO_INFO* info = (BAO_INFO*)G::g_bao_infos->objectAtIndex(41);
            if (!info->isGot) {
                info->isGot = true;
                HPersistence::S()->SaveBao(41);
            }
        }
            G::G_getReward(0, 2500);
            break;
        case 6://+5步数
            G::G_getReward(3, 5);
            break;
        case 7://2000金币
            G::G_getReward(0, 2000);
            break;
        default:
            break;
    }
    
    G::turntable_count--;
    G::turntable_count = MAX(0,G::turntable_count);
    
    CCDictionary* _dic = CCDictionary::createWithContentsOfFile("data/normaltips.plist");
    IntToStringFormat(_key, "turntable_reward_%d", id)
    CCString* des = (CCString*)_dic->objectForKey(_key);
    UILabelBMFont* label = (UILabelBMFont*)Rewards->getChildByName("Rewards_des");
    label->setText(des->getCString());
    _dic->release();

    HPersistence::S()->SaveToFile();
    return id;
}

void TurnTable::scrollToID(int id){
    int angle = id* 360/8;
    float rotate_angle = angle-m_current_angle+720;
    m_current_angle = angle;
    circle_up->runAction(CCSequence::create(CCRotateBy::create(1.0f, 360*5),CCRotateBy::create(3.0f, -rotate_angle),CCCallFunc::create(this, callfunc_selector(TurnTable::RotateOver)),NULL));
    circle_down->runAction(CCSequence::create(CCRotateBy::create(1.0f, 360*5),CCRotateBy::create(3.0f, -rotate_angle),NULL));
    arrow->runAction(CCSequence::create(CCRotateBy::create(0.1f, 60),CCRepeat::create(CCSequence::create(CCRotateBy::create(0.3f,-30),CCRotateBy::create(0.3f, 30),NULL),3),CCRepeat::create(CCSequence::create(CCRotateBy::create(0.4f,-45),CCRotateBy::create(0.4f, 45),NULL),2),CCRotateBy::create(0.5f, -60),NULL));
}

void TurnTable::RotateOver(){
    if (G::turntable_count>0) {
        btn_start->active();
    }
    m_show->runAction(CCRepeat::create(CCSequence::create(CCShow::create(),CCDelayTime::create(0.2f),CCHide::create(),CCDelayTime::create(0.2f), NULL), 5));
    showReward();
}

void TurnTable::showReward(){
    Rewards->runAction(CCSequence::create(CCDelayTime::create(0.2f),CCShow::create(),CCDelayTime::create(4),CCHide::create(),NULL));
}

void TurnTable::onCloseClick(cocos2d::CCObject sender){
    closeWindow();
}

//
//  ToolBuy.cpp
//  Bejeweled
//
//  Created by wilford on 14-1-9.
//
//

#include "ToolBuy.h"

ToolBuy* ToolBuy::instance = NULL;

void ToolBuy::init(void *data){
    ToolBuyParam* param = (ToolBuyParam*)data;
    m_tool_id = 0;
    m_count = 0;
    if (param) {
        m_tool_id = param->tool_id;
        m_count = param->buy_count;
    }
    
    ToolInfo* info = (ToolInfo*)G::g_toolinfos->objectAtIndex(m_tool_id);
    m_price = info->price * m_count;
    
    m_tips = CCUIHELPER->createWidgetFromJsonFile("ToolBuy.json");
    UIImageView* title_label = (UIImageView*)m_tips->getChildByName("title_label");
    mCoin = (UILabelBMFont*)m_tips->getChildByName("mCoin");
    UILabelBMFont* mCost = (UILabelBMFont*)m_tips->getChildByName("mCost");
    UILabelBMFont* mBuyCount = (UILabelBMFont*)m_tips->getChildByName("mBuyCount");
    UILabelBMFont* mDes = (UILabelBMFont*)m_tips->getChildByName("tool_des");
    UIImageView* mIcon = (UIImageView*)m_tips->getChildByName("Icon");
    IntToStringFormat(_titlePath, "tools/buy/title_%d.png", m_tool_id);
    title_label->setTexture(_titlePath);
    m_curren_coin = G::G_getCoin();
    IntToString(_coin, m_curren_coin);
    mCoin->setText(_coin);
    IntToStringFormat(_price,"X%d", m_price);
    mCost->setText(_price);
    IntToStringFormat(_count, "X%d", m_count);
    mBuyCount->setText(_count);
    CCDictionary* _strings = CCDictionary::createWithContentsOfFile("data/tool_des.plist");
    IntToStringFormat(_key, "tool_%d", m_tool_id);
    CCString* _str = (CCString*)_strings->objectForKey(_key);
    mDes->setText(_str->getCString());
    _strings->release();
    IntToStringFormat(_iconPath, "tools/icon_%d.png", m_tool_id);
    mIcon->setTexture(_iconPath);
}

void ToolBuy::startAnim(){
    HCCWindow::startAnim();
    UIWidget* btn_add = m_tips->getChildByName("btn_coin_add");
    UIWidget* btn_buy = m_tips->getChildByName("btn_OK");
    UIWidget* btn_close = m_tips->getChildByName("btn_close");
    
    PopNode(btn_add, 0.4f);
    PopNode(btn_buy, 0.4f);
    PopNode(btn_close, 0.8f);
    
    btn_add->addReleaseEvent(this, coco_releaseselector(ToolBuy::onAddCoin));
    btn_buy->addReleaseEvent(this, coco_releaseselector(ToolBuy::onBuy));
    btn_close->addReleaseEvent(this, coco_releaseselector(ToolBuy::onCloseClicked));
}

void ToolBuy::update(float dt){
    HCCWindow::update(dt);
    if (m_curren_coin!=G::G_getCoin()) {
        m_curren_coin = G::G_getCoin();
        IntToString(_coin, m_curren_coin);
        mCoin->setText(_coin);
    }
}

void ToolBuy::onCloseClicked(cocos2d::CCObject *sender){
    closeWindow();
}

void ToolBuy::onAddCoin(cocos2d::CCObject *sender){
    //弹出金币充值
    QuickBuy::show(m_layer,new QuickBuyParam(1));
}

void ToolBuy::onBuy(cocos2d::CCObject *sender){
    
    if (G::G_costCoin(m_price)) {
        G::G_getReward(m_tool_id+2, m_count);
        closeWindow();
    }else{
        //弹出金币充值
        QuickBuy::show(m_layer,new QuickBuyParam(1));
    }
}
//
//  Share.cpp
//  Bejeweled
//
//  Created by wilford on 14-1-15.
//
//

#include "ShareWindow.h"



void Share::init(void *data){
   m_tips = CCUIHELPER->createWidgetFromJsonFile("SHARE_TIPS.json");
}

void Share::update(float dt){
	 for (int i=0; i<MAX_SHARE; i++) {
	if (btns[i]) {
	btns[i]->setVisible(!G::g_share_reward_got[i]);
	}
	if (hasGot[i]) {
	hasGot[i]->setVisible(G::g_share_reward_got[i]);
	}
	if (des[i]) {
	des[i]->setVisible(!G::g_share_reward_got[i]);
	}
	}
}

void Share::startAnim(){
	HCCWindow::startAnim();
	UIWidget* btn_close = m_tips->getChildByName("TIP_BTN_CLOSE");
	btns[2]= m_tips->getChildByName("WEIBO_BTN");
	btns[0]= m_tips->getChildByName("QZONE_BTN");
	btns[1] = m_tips->getChildByName("WEIXIN_BTN");
	for (int i=0; i<MAX_SHARE; i++) {
		IntToStringFormat(_desName, "DES_%d", i);
		des[i] = m_tips->getChildByName(_desName);
		IntToStringFormat(_hasGotName, "GOT_%d", i);
		hasGot[i] = m_tips->getChildByName(_hasGotName);
	}
	PopNode(btns[2],0.4f);
	PopNode(btns[0],0.4f);
	PopNode(btns[1],0.4f);
	PopNode(btn_close,0.8f);
	btn_close->addReleaseEvent(this, coco_releaseselector(Share::onCloseClicked));
	btns[0]->addReleaseEvent(this, coco_releaseselector(Share::onQZone));
	btns[2]->addReleaseEvent(this, coco_releaseselector(Share::onSina));
	btns[1]->addReleaseEvent(this, coco_releaseselector(Share::onWeixin));
}

void Share::onCloseClicked(CCObject* sender){
    closeWindow();
}

void Share::onQZone(cocos2d::CCObject *sender){
	 CCArray* rewards = CCArray::create();
	rewards->addObject(new RewardInfo(1,10));
	RewardGet::show(m_layer,new RewardsParams(rewards));
	G::g_share_reward_got[0]=true;
	HPersistence::S()->SaveToFile();
}

void Share::onSina(CCObject* sender){
	CCArray* rewards = CCArray::create();
	for (int i=0; i<MAX_TOOL_COUNT; i++) {
		rewards->addObject(new RewardInfo(i+2,1));
	}
	RewardGet::show(m_layer,new RewardsParams(rewards));
	G::g_share_reward_got[2]=true;
	HPersistence::S()->SaveToFile();
}

void Share::onWeixin(cocos2d::CCObject *sender){
	CCArray* rewards = CCArray::create();
	rewards->addObject(new RewardInfo(0,2000));
	RewardGet::show(m_layer,new RewardsParams(rewards));
	G::g_share_reward_got[1]=true;
	HPersistence::S()->SaveToFile();
}

Share* Share::instance;
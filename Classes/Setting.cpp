//
//  Setting.cpp
//  Bejeweled
//
//  Created by wilford on 14-1-6.
//
//

#include "Setting.h"

Setting* Setting::instance = NULL;

void Setting::init(void *data){
    setting_changed = true;
    m_isbackground = G::g_mIsBackgroundMusicOn;
    m_iseffect = G::g_mIsEffectVolumeOn;
    m_tips = CCUIHELPER->createWidgetFromJsonFile("Setting.json");
    UIWidget* btn_close = m_tips->getChildByName("btn_close");
    btn_close->addReleaseEvent(this, coco_releaseselector(Setting::onCloseClicked));
    UIWidget* btn_save = m_tips->getChildByName("btn_save");
    btn_save->addReleaseEvent(this, coco_releaseselector(Setting::onSettingSave));
    
    UIWidget* background = m_tips->getChildByName("backgroundMusic");
	{
		b_on =(UIImageView*)background->getChildByName("on");
        b_off = (UIImageView*)background->getChildByName("off");
		b_on->addReleaseEvent(this,coco_releaseselector(Setting::onSettingChanged));
		b_off->addReleaseEvent(this,coco_releaseselector(Setting::onSettingChanged));
        b_on->setTag(0);
        b_off->setTag(1);
	}
    
    UIWidget* effect = m_tips->getChildByName("effect");
	{
        e_on =(UIImageView*)effect->getChildByName("on");
		e_off = (UIImageView*)effect->getChildByName("off");
		e_on->addReleaseEvent(this,coco_releaseselector(Setting::onSettingChanged));
		e_off->addReleaseEvent(this,coco_releaseselector(Setting::onSettingChanged));
        e_on->setTag(2);
        e_off->setTag(3);
	}
}

void Setting::update(float dt){
    if (setting_changed) {
        b_on ->setTexture(m_isbackground?"setting/voiceOn_down.png":"setting/voiceOn_up.png");
        b_off ->setTexture(m_isbackground?"setting/voiceOff_up.png":"setting/voiceOff_down.png");
        e_on->setTexture(m_iseffect?"setting/voiceOn_down.png":"setting/voiceOn_up.png");
        e_off ->setTexture(m_iseffect?"setting/voiceOff_up.png":"setting/voiceOff_down.png");
        setting_changed = false;
    }
}


void Setting::onSettingChanged(cocos2d::CCObject *sender){
    UIWidget* btn = (UIWidget*)sender;
    int tag = btn ->getTag();
    if (tag/2==0) {
        if (m_isbackground!=(tag%2==0)) {
            m_isbackground = !m_isbackground;
            setting_changed = true;
        }
    }else{
        if (m_iseffect!=(tag%2==0)) {
            m_iseffect = !m_iseffect;
            setting_changed = true;
        }
    }
}

void Setting::onSettingSave(cocos2d::CCObject *sender){
     G::G_playEffect(RES_MUSIC_NORMAL_CLICK);
    G::G_setBackGroundMusicState(m_isbackground,RES_MUSIC_MENU_BG);
    G::G_setEffectState(m_iseffect);
    HPersistence::S()->SaveToFile();
    closeWindow();
}

void Setting::onCloseClicked(cocos2d::CCObject *sender){
     G::G_playEffect(RES_MUSIC_NORMAL_CLICK);
    closeWindow();
}
//
//  LogoScene.cpp
//  Bejeweled
//
//  Created by wilford on 14-1-3.
//
//

#include "LogoScene.h"

void LogoScene::onEnter(){
    HScene::onEnter();
    G::g_gamescene_type = GAMESCENE_LOGO;
    UIPanel* bg = UIPanel::create();
    m_layer->addWidget(bg);
    bg->setBackGroundColorType(LAYOUT_COLOR_SOLID);
    bg->setBackGroundColorOpacity(255);
    bg->setBackGroundColor(ccc3(24, 11, 24));
    bg->setSize(CCSizeMake(640, 1138));
    
    UIImageView* logo = UIImageView::create();
    logo->setTexture("logo/logo.png");
    bg->addChild(logo);
    logo->setPosition(ccp(_pCenter.x, _pCenter.y+200));
    
    CCPoint pos[4]= {
        ccp(-30,76),
        ccp(-76,-84),
        ccp(60,0),
        ccp(120,30)
    };
    stars = new CCArray();
    for (int i=0; i<4; i++) {
        UIImageView* star = UIImageView::create();
        star->setTexture("logo/star.png");
        star->setPosition(pos[i]);
        logo->addChild(star);
        stars->addObject(star);
        star->setScale(0);
    }
    
    UIImageView* label = UIImageView::create();
    label->setTexture("logo/label.png");
    bg->addChild(label);
    label->setPosition(ccp(_pCenter.x, _pCenter.y-300));

//    if (!G::g_has_first_saved) {
//        UILabelBMFont* label = UILabelBMFont::create();
//        label->setFntFile("font/font.fnt");
//        label->setColor(ccc3(255, 255, 255));
//        CCDictionary* strings = CCDictionary::createWithContentsOfFile("data/normaltips.plist");
//        const  CCString* s = strings->valueForKey("first_load");
//        label->setText(s->getCString());
//        strings->release();
//        bg->addChild(label);
//        label->setPosition(ccp(_pCenter.x, _pCenter.y-200));
//    }
    
    
    schedule(schedule_selector(LogoScene::PLAY_STAR), 0.5f);
    schedule(schedule_selector(LogoScene::openMenu), 1.5f);
}


void LogoScene::PLAY_STAR(float t){
    int id = t_getRandom(4);
    UIImageView* star = (UIImageView*)stars->objectAtIndex(id);
    if (star->getRenderer()->numberOfRunningActions()==0) {
        star->runAction(CCSequence::create(CCScaleTo::create(0.4f, 1.2f),CCScaleTo::create(0.4f, 0),NULL));
    }
}

void LogoScene::loadResource(){
    HScene::loadResource();
//    addTextureName("logo/logo.png");
//    addTextureName("logo/star.png");
//    addTextureName("logo/label.png");
}

void LogoScene::ReleaseResource(){
    HScene::ReleaseResource();
//    releaseTexture("logo/logo.png");
//    releaseTexture("logo/star.png");
//    releaseTexture("logo/label.png");
}



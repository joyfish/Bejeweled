//
//  MainScene.cpp
//  Bejeweled
//
//  Created by wilford on 14-1-8.
//
//

#include "MainScene.h"

void MainScene::onEnter(){
    HScene::onEnter();
    G::g_gamescene_type = GAMESCENE_MAIN;
    m_turn_table_showed = false;
    CCDirector::sharedDirector()->getKeypadDispatcher()->addDelegate(this);
    G::G_playBackGroundMusic(RES_MUSIC_MAIN_BG);
    UIWidget* main = CCUIHELPER->createWidgetFromJsonFile("GameMain.json");
    m_layer->addWidget(main);

    CCSize screenSize =AutoSceneSize::S()->getScreenSize();
    
    sky_scrollview = (UIScrollView*)main->getChildByName("SKY_SCROLL");
    sky_scrollview->setSize(screenSize);
    Layout* sky_inner = sky_scrollview->getInnerContainer();
    CCPoint sky_pos = sky_inner->getPosition();
    sky_inner->setPosition(ccp(sky_pos.x,0));
    
    tree_scrollView = (UIScrollView*)main->getChildByName("main_scroll_view");
    tree_scrollView->setSize(screenSize);
    float stage_height = initStage();
    tree_scrollView->setInnerContainerSize(CCSizeMake(screenSize.width, stage_height+300));
    tree_scrollView->addScrollChildrenEvent(this,coco_ScrollChildrenSelector(MainScene::onTreeScrolled));
    Layout* tree_inner = tree_scrollView->getInnerContainer();
    CCPoint tree_pos = tree_inner->getPosition();
    tree_inner->setPosition(ccp(tree_pos.x, 0));
    
    UIWidget* tree_bar_panel = main->getChildByName("tree_bar_panel");
    tree_bar_panel->setZOrder(10);
    tree_bar_panel->setPosition(ccp(591, _pCenter.y));
    
    tree_bar = (UISlider*)main->getChildByName("tree_bar");
    tree_bar->addPercentChangedEvent(this, coco_percentchangedselector(MainScene::onSilderChanged));
    tree_bar->setPercent(0);
    
    
    UIWidget* power_bg = main->getChildByName("power_bg");
    m_powers = (UILabelAtlas*)power_bg->getChildByName("power_count");
    char _powerStr[30];
    sprintf(_powerStr, "%d",G::G_getPower());
    m_powers->setStringValue(_powerStr);
//    for (int i=0; i<MAX_POWER; i++) {
//        IntToStringFormat(_powerName, "power_%d", i);
//        m_powers[i] =(UIImageView*)power_bg->getChildByName(_powerName);
//        if (i<G::g_maxPower) {
//            m_powers[i]->setTexture("main/icon_power_down.png");
//        }else{
//            m_powers[i]->setTexture("main/icon_x.png");
//        }
//    }
    power_bg->setTouchEnable(true);
    power_bg->addReleaseEvent(this, coco_releaseselector(MainScene::onQuickPower));
    
    UIWidget* book_bg = main->getChildByName("book_bg");
    UIWidget* coin_bg = main->getChildByName("coin_bg");
    
    m_coins = (UILabelBMFont*)coin_bg->getChildByName("coin_count");
    m_books = (UILabelAtlas*)book_bg->getChildByName("num");
    IntToString(_coinNum, G::G_getCoin());
    m_coins->setText(_coinNum);
    IntToString(_bookNum, G::G_getBook());
    m_books->setStringValue(_bookNum);
    
    if (G::g_sea_isOpened||G::g_hole_isOpened) {
        book_bg->setVisible(true);
        book_bg->setTouchEnable(true);
        book_bg->addReleaseEvent(this, coco_releaseselector(MainScene::onQuickBook));
    }else{
        book_bg->setVisible(false);
        book_bg->setTouchEnable(false);
    }
   
//    book_bg->setTouchEnable(true);
//    book_bg->addReleaseEvent(this, coco_releaseselector(MainScene::onQuickBook));
    
    coin_bg ->setTouchEnable(true);
    coin_bg->addReleaseEvent(this, coco_releaseselector(MainScene::onQuickCoin));
    
    UIWidget* top = main->getChildByName("top");
    top->setPosition(ccp(0, _pTop+80));
    UIWidget* bottom = main->getChildByName("Bottom");
    bottom->setPosition(ccp(0, _pBottom));
    
    m_shop_btn = main->getChildByName("btn_shop");
    m_shop_btn->setTouchEnable(true);
    m_shop_btn->addReleaseEvent(this, coco_releaseselector(MainScene::onShopClicked));
   // m_shop_btn->setPosition(ccp(m_shop_btn->getPosition().x,m_shop_btn->getPosition().y+250));
    
    m_turntable_btn = main->getChildByName("btn_turntable");
    m_turntable_btn->setTouchEnable(true);
    m_turntable_btn->addReleaseEvent(this, coco_releaseselector(MainScene::onTurnTableClicked));
    
    m_share_btn = main->getChildByName("btn_share");
    m_share_btn->setVisible(false);
//    m_share_btn->setTouchEnable(true);
//    m_share_btn->addReleaseEvent(this, coco_releaseselector(MainScene::onShareClicked));
//    m_share_btn->setVisible(G::G_hasShare());
//    m_share_btn->setVisible(false);
    m_share_btn->setTouchEnable(false);
    
    m_achievement_btn = main->getChildByName("btn_achievement");
    m_achievement_btn->setVisible(true);
    m_achievement_btn->setTouchEnable(true);
    //m_achievement_btn->setTouchEnable(true);
    m_achievement_btn->addReleaseEvent(this, coco_releaseselector(MainScene::onAchieveClicked));
    
    m_bao_btn = main->getChildByName("btn_bao");
    m_bao_btn->setVisible(true);
    m_bao_btn->setTouchEnable(true);
    m_bao_btn->addReleaseEvent(this,coco_releaseselector(MainScene::onBaoClicked));
    
    UIWidget* btn_back = main->getChildByName("btn_tree_back");
    btn_back->setTouchEnable(true);
    btn_back->addReleaseEvent(this, coco_releaseselector(MainScene::onBack));
    
    m_hole_btn = main->getChildByName("btn_secret");
    m_hole_btn->setVisible(true);
    m_hole_btn->setTouchEnable(true);
    //m_hole_btn->setTouchEnable(false);
    m_hole_btn->setPosition(ccp(111, 164));
    UIWidget* wind = m_hole_btn->getChildByName("wind");
    if (!G::g_hole_isOpened) {
        wind->setVisible(false);
    }
    wind->runAction(CCRepeatForever::create(CCRotateBy::create(5, -360)));
    m_hole_btn->addReleaseEvent(this, coco_releaseselector(MainScene::onHole));
    m_sea_btn = main->getChildByName("btn_sea");
    m_sea_btn->addReleaseEvent(this, coco_releaseselector(MainScene::onSea));
    m_sea_btn->setVisible(true);
    m_sea_btn->setTouchEnable(true);
    //m_sea_btn->setTouchEnable(false);
    
    m_power_recovery_time = (UILabelBMFont*)main->getChildByName("back_time");
    m_power_recovery_time->setZOrder(1);
    m_power_recovery_time->setVisible(false);
    
    UIWidget* collect_bg = main->getChildByName("collect_bg");
    UILabelBMFont* _pecent_label = (UILabelBMFont*)collect_bg->getChildByName("percent");
    UILabelAtlas* _star_label = (UILabelAtlas*)collect_bg->getChildByName("star");
    int _percent = G::G_getTotalStar()*100 / G::G_getMaxStar();
    IntToStringFormat(_s_pecent, "%d%%", _percent);
    IntToString(_s_star, G::G_getTotalStar());
    _pecent_label->setText(_s_pecent);
    _star_label->setStringValue(_s_star);
    
    
    initBaoItems();
    initCloud();
    
    if (!G::tree_scroll_has_showed) {
        showTreeAnim();
        G::tree_scroll_has_showed = true;
        HPersistence::S()->SaveToFile();
    }else{
        rePositionInnerForStage();
    }
}

void MainScene::initBaoItems(){
    for (int i=0; i<MAX_BAO_TREE_COUNT; i++) {
        BAO_INFO* info = (BAO_INFO*) G::g_bao_infos->objectAtIndex(baos_tree_ids[i]);
        if (info->isGot) {
            continue;
        }
        IntToStringFormat(_stageName, "aaaaa_%d", baos_level[baos_tree_ids[i]]-1)
        UIWidget* icon_stage = tree_scrollView->getChildByName(_stageName);
        if (!icon_stage) {
            continue;
        }
        UIImageView* baoitem = UIImageView::create();
        IntToStringFormat(_iconName, "bao/icon_%d.png",baos_tree_ids[i]);
        baoitem->setTexture(_iconName);
        baoitem->setPosition(ccp(icon_stage->getPosition().x,icon_stage->getPosition().y-30));
        tree_scrollView->addChild(baoitem);
        baoitem->setZOrder(10);
        baoitem->setTouchEnable(true);
        baoitem->setTag(baos_tree_ids[i]);
        baoitem->addReleaseEvent(this, coco_releaseselector(MainScene::onBaoItemClicked));
    }
}

void MainScene::initCloud(){
    for (int i=0; i<MAX_CLOUD+1; i++) {
        if (i<MAX_CLOUD) {
            if(G::g_cloud_isOpened[i])
                continue;
        }
        UIWidget* cloud = CCUIHELPER->createWidgetFromJsonFile("CLOUD.json");
        cloud -> addReleaseEvent(this, coco_releaseselector(MainScene::onCloudClicked));
        UIWidget* label_end = cloud->getChildByName("LABEL_END");
        UIWidget* label_star = cloud->getChildByName("STAR");
        UIWidget* label_click = cloud->getChildByName("LABEL_CLICK_ME");
        cloud->setTag(i);
        if (i<MAX_CLOUD) {
            int needStar = (i+1)*CLOUD_PADDING*3/2;
            int cloudLevel = (i+1)*CLOUD_PADDING;
            if (needStar <=G::G_getTotalStar()) {
                label_end->setVisible(false);
                label_star->setVisible(false);
                label_click->setVisible(true);
                UIWidget* backlight = label_click->getChildByName("BACK_LIGHT");
                UIWidget* arrow = label_click->getChildByName("ARROW");
                backlight->runAction(CCRepeatForever::create(CCRotateBy::create(6, 360)));
                arrow->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(0.2f,ccp(0, 7)), CCMoveBy::create(0.15f, ccp(0, -7)),NULL)));
            }else{
                label_click->setVisible(false);
                label_end->setVisible(false);
                label_star->setVisible(true);
                UILabelAtlas* num = (UILabelAtlas*)label_star->getChildByName("NUM");
                UILabelAtlas* num_star = (UILabelAtlas*)label_star->getChildByName("NUM_STAR");
                UIWidget* label_1 = label_star->getChildByName("LABEL_1");
                IntToString(_starNum,needStar);
                num->setStringValue(_starNum);
                num_star->setStringValue(_starNum);
                label_1->setPosition(ccp(num->getPosition().x+num->getSize().width, num->getPosition().y));
            }
            IntToStringFormat(_stageName, "aaaaa_%d",cloudLevel-1)
            UIWidget* icon_stage = tree_scrollView->getChildByName(_stageName);
            cloud->setPosition(ccp(0,icon_stage->getPosition().y-100));

        }else{
            label_click->setVisible(false);
            label_end->setVisible(true);
            label_star->setVisible(false);
            IntToStringFormat(_stageName, "aaaaa_%d",MAX_STAGE-1)
            UIWidget* icon_stage = tree_scrollView->getChildByName(_stageName);
            cloud->setPosition(ccp(0,icon_stage->getPosition().y));
        }
        tree_scrollView->addChild(cloud);
        cloud->setZOrder(19);
    }
}

void MainScene::update(float dt){
    HScene::update(dt);
    
    char _powerStr[30];
    sprintf(_powerStr, "%d",G::G_getPower());
    m_powers->setStringValue(_powerStr);
//    for (int i=0; i<MAX_POWER; i++) {
//        if (i<G::g_maxPower) {
//            m_powers[i]->setTexture("main/icon_power_down.png");
//        }else{
//            m_powers[i]->setTexture("main/icon_x.png");
//        }
//        UIWidget* power_up = m_powers[i]->getChildByName("power");
//        if (i<G::G_getPower()) {
//            power_up->setVisible(true);
//        }else{
//            power_up->setVisible(false);
//        }
//    }
    IntToString(_coinNum, G::G_getCoin());
    m_coins->setText(_coinNum);
    IntToString(_bookNum, G::G_getBook());
    m_books->setStringValue(_bookNum);
    updatePowerRecovery();
    updateMainBtns();
    if(updateAchievement())
        return;
    
    if (updateBao()) {
        return;
    }
//
    if (updateHoleNewShow()) {
        return;
    }
    
    if (updateSeaNewShow()) {
        return;
    }
    if (updateTurnTable()) {
        return;
    }
}

bool MainScene::updateTurnTable(){
    if (HWindowsManager::S()->hasWindowsShowed()) {
        return true;
    }
    if (m_turn_table_showed) {
        return false;
    }
    if (G::turntable_count>0) {
        TurnTable::show(m_layer);
    }
    m_turn_table_showed = true;
    return false;
}

bool MainScene::updateAchievement()
{
    if (HWindowsManager::S()->hasWindowsShowed()) {
        return true;
    }
    for (unsigned int i=0; i<G::g_achieve_infos->count(); i++) {
        ACHIEVE_INFO* info = (ACHIEVE_INFO*)G::g_achieve_infos->objectAtIndex(i);
        if (info->is_complete&&!info->new_showed&&info->isOpened) {
            AchieveCompleted::show(m_layer,new AchieveCompletedParam(i));
            info->new_showed = true;
            HPersistence::S()->SaveAchievement(i);
            return true;
        }
    }
    return false;
}

bool MainScene::updateBao(){
    if (HWindowsManager::S()->hasWindowsShowed()) {
        return true;
    }
    for (unsigned int i=0; i<G::g_bao_infos->count(); i++) {
        BAO_INFO* info = (BAO_INFO*)G::g_bao_infos->objectAtIndex(i);
        if (info->isGot&&!info->isShowed) {
            BaoGet::show(m_layer,new BaoInfoParam(i));
            info->isShowed = true;
            HPersistence::S()->SaveBao(i);
            return true;
        }
    }
    return false;
}

void MainScene::updatePowerRecovery(){
    if (G::G_getPower()==G::g_maxPower) {
        if (!m_power_recovery_time->isVisible()) {
            m_power_recovery_time->setVisible(true);
        }
        m_power_recovery_time->setText("MAX");
    }else{
        if (!m_power_recovery_time->isVisible()) {
            m_power_recovery_time->setVisible(true);
        }
        int rest_time = POWER_ROCOVERY_TIME - G::G_checkPowerRecovery(this, h_voidcallback(HPersistence::SaveToFile));
        int sec = rest_time%60;
        int min = rest_time/60;
        char s[30];
        sprintf(s, sec>=10?"%d":"0%d", sec);
        char m[30];
        sprintf(m, min>=10?"%d":"0%d",min);
        char time_v[30];
        sprintf(time_v, "%s:%s",m,s);
        m_power_recovery_time->setText(time_v);
    }
}

void MainScene::updateMainBtns(){
//    if (m_share_btn) {
//        UIWidget* warn = m_share_btn->getChildByName("warn");
//        if (G::G_hasShare()) {
//            if (!warn->isVisible()) {
//                warn->setVisible(true);
//                warn->runAction(CCRepeatForever::create(CCSequence::create(CCScaleTo::create(0.2f, 1.2f),CCScaleTo::create(0.3f, 1.0f),NULL)));
//            }
//        }else{
//            if (m_share_btn->isVisible()) {
//                m_share_btn->setVisible(false);
//                m_share_btn->setTouchEnable(false);
//            }
//        }
//    }
    if (m_achievement_btn) {
        UIWidget* warn = m_achievement_btn->getChildByName("warn");
        if (G::G_hasNewAchieveCompleted()) {
            if (!warn->isVisible()) {
                warn->setVisible(true);
                warn->runAction(CCRepeatForever::create(CCSequence::create(CCScaleTo::create(0.2f, 1.2f),CCScaleTo::create(0.3f, 1.0f),NULL)));
            }
        }else{
            warn->setVisible(false);
        }
    }
    
    if (m_bao_btn) {
        UIWidget* warn = m_bao_btn->getChildByName("warn");
        if (G::G_hasNewBaoGet()) {
            if (!warn->isVisible()) {
                warn->setVisible(true);
                warn->runAction(CCRepeatForever::create(CCSequence::create(CCScaleTo::create(0.2f, 1.2f),CCScaleTo::create(0.3f, 1.0f),NULL)));
            }
        }else{
            warn->setVisible(false);
        }
    }
    
    if (m_turntable_btn) {
        UIWidget* warn = m_turntable_btn->getChildByName("warn");
        if (G::turntable_count>0) {
            if (!warn->isVisible()) {
                warn->setVisible(true);
                warn->runAction(CCRepeatForever::create(CCSequence::create(CCScaleTo::create(0.2f, 1.2f),CCScaleTo::create(0.3f, 1.0f),NULL)));
            }
        }else{
            warn->setVisible(false);
        }
    }

    if (m_hole_btn) {
        UIWidget* wind = m_hole_btn->getChildByName("wind");
        if (wind) {
            if (G::g_hole_isOpened) {
                wind->setVisible(true);
            }else
                wind->setVisible(false);
        }
    }
    
}

void MainScene::loadResource(){
    HScene::loadResource();
    addTextureName("main/btn_achievement_up.png");
    addTextureName("main/btn_achievement_down.png");
    addTextureName("main/btn_bao_up.png");
    addTextureName("main/btn_bao_down.png");
    addTextureName("main/btn_sea_down.png");
    addTextureName("main/btn_secret_down.png");
    addTextureName("main/btn_share_up.png");
    addTextureName("main/btn_share_down.png");
    addTextureName("main/btn_shop_up.png");
    addTextureName("main/btn_shop_down.png");
    addTextureName("main/cloud_down.png");
    addTextureName("main/icon_bg.png");
    addTextureName("main/icon_book.png");
    addTextureName("main/power_icon.png");
    addTextureName("main/icon_coin.png");
    addTextureName("main/icon_stage_close.png");
    addTextureName("main/icon_stage_open.png");
    addTextureName("main/star_collect_bg.png");
    addTextureName("main/start_on.png");
    addTextureName("main/star_off.png");
    addTextureName("main/tree_bar_1.png");
    addTextureName("main/tree_bar_2.png");
    addTextureName("main/tree_bar_3.png");
    addTextureName("main/tree_bg_bottom.png");
    addTextureName("main/tree_bg_middle.png");
}

void MainScene::ReleaseResource(){
    HScene::ReleaseResource();
    releaseTexture("main/btn_achievement_up.png");
    releaseTexture("main/btn_achievement_down.png");
    releaseTexture("main/btn_bao_up.png");
    releaseTexture("main/btn_bao_down.png");
    releaseTexture("main/btn_sea_down.png");
    releaseTexture("main/btn_secret_down.png");
    releaseTexture("main/btn_share_up.png");
    releaseTexture("main/btn_share_down.png");
    releaseTexture("main/btn_shop_up.png");
    releaseTexture("main/btn_shop_down.png");
    releaseTexture("main/cloud_down.png");
    releaseTexture("main/icon_bg.png");
    releaseTexture("main/icon_book.png");
    releaseTexture("main/power_icon.png");
    releaseTexture("main/icon_coin.png");
    releaseTexture("main/icon_stage_close.png");
    releaseTexture("main/icon_stage_open.png");
    releaseTexture("main/star_collect_bg.png");
    releaseTexture("main/start_on.png");
    releaseTexture("main/star_off.png");
    releaseTexture("main/tree_bar_1.png");
    releaseTexture("main/tree_bar_2.png");
    releaseTexture("main/tree_bar_3.png");
    releaseTexture("main/tree_bg_bottom.png");
    releaseTexture("main/tree_bg_middle.png");
}

void MainScene::rePositionInnerForStage(){
    CCSize tree_size = tree_scrollView->getSize();
    CCSize tree_inner_size = tree_scrollView->getInnerContainerSize();
    Layout* tree_inner = tree_scrollView->getInnerContainer();
    UIWidget* _icon_stage = icon_stages[G::G_getCurrentStage()-1];
    float y_offset = _icon_stage->getPosition().y-_pCenter.y;
    float tree_max_offset = tree_inner_size.height-tree_size.height;
    y_offset = MAX(0,y_offset);
    y_offset = MIN(tree_max_offset, y_offset);
    CCPoint tree_pos = tree_inner->getPosition();
    tree_inner->setPosition(ccp(tree_pos.x,-y_offset));
    float percent = y_offset/tree_max_offset;
    tree_bar->setPercent(percent*100);
}

void MainScene::showTreeAnim(bool isfromtop){
    tree_bar->setTouchEnable(false);
    tree_scrollView->setTouchEnable(false);
    Layout* tree_inner = tree_scrollView->getInnerContainer();
    CCSize tree_size = tree_scrollView->getSize();
    CCSize tree_inner_size = tree_scrollView->getInnerContainerSize();
    float tree_max_offset = tree_inner_size.height-tree_size.height;
    CCPoint tree_pos = tree_inner->getPosition();
    if (isfromtop) {
        tree_inner->setPosition(ccp(tree_pos.x,-tree_max_offset));
    }
    tree_inner->runAction(CCSequence::create(CCMoveTo::create(1.0f, ccp(tree_pos.x, 0)),CCCallFuncN::create(this, callfuncN_selector(MainScene::onTreeAnimOver)), NULL));

}



void MainScene::onTreeAnimOver(cocos2d::CCNode *sender){
    tree_bar->setTouchEnable(true);
    tree_scrollView->setTouchEnable(true);
    Layout* tree_inner = tree_scrollView->getInnerContainer();
    CCSize tree_size = tree_scrollView->getSize();
    CCSize tree_inner_size = tree_scrollView->getInnerContainerSize();
    float tree_max_offset = tree_inner_size.height-tree_size.height;
    float tree_offset = abs((long)tree_inner->getPosition().y);
    float percent = tree_offset/tree_max_offset;
    tree_bar->setPercent(percent*100);
}

void MainScene::onTreeScrolled(cocos2d::CCObject *sender){
    Layout* tree_inner = tree_scrollView->getInnerContainer();
    CCSize tree_size = tree_scrollView->getSize();
    CCSize tree_inner_size = tree_scrollView->getInnerContainerSize();
    float tree_max_offset = tree_inner_size.height-tree_size.height;
    float tree_offset = abs((long)tree_inner->getPosition().y);
    float percent = tree_offset/tree_max_offset;
    Layout* sky_inner = sky_scrollview->getInnerContainer();
    CCSize sky_size = sky_scrollview->getSize();
    CCSize sky_inner_size = sky_scrollview->getInnerContainerSize();
    float sky_max_offset = sky_inner_size.height- sky_size.height;
    float sky_offset = sky_max_offset*percent;
    CCPoint pos = sky_inner->getPosition();
    sky_inner->setPosition(ccp(pos.x,-sky_offset));
    tree_bar->setPercent(percent*100);
}

void MainScene::onSilderChanged(cocos2d::CCObject *sender){
    int percent = tree_bar->getPercent();
    Layout* tree_inner = tree_scrollView->getInnerContainer();
    CCSize tree_size = tree_scrollView->getSize();
    CCSize tree_inner_size = tree_scrollView->getInnerContainerSize();
    float tree_max_offset = tree_inner_size.height-tree_size.height;
    float tree_offset = tree_max_offset*percent/100;
    CCPoint tree_pos = tree_inner->getPosition();
    tree_inner->setPosition(ccp(tree_pos.x, -tree_offset));
    Layout* sky_inner = sky_scrollview->getInnerContainer();
    CCSize sky_size = sky_scrollview->getSize();
    CCSize sky_inner_size = sky_scrollview->getInnerContainerSize();
    float sky_max_offset = sky_inner_size.height- sky_size.height;
    float sky_offset = sky_max_offset*percent/100;
    CCPoint pos = sky_inner->getPosition();
    sky_inner->setPosition(ccp(pos.x,-sky_offset));


}

float MainScene::initStage(){
    float max_height = 0;
    
    int mid_tree_count =(MAX_STAGE-7)%c_stage_middle_count == 0?(MAX_STAGE-7)/c_stage_middle_count:(MAX_STAGE-7)/c_stage_middle_count+1;
    
    for (int i=0; i<mid_tree_count; i++) {
        UIImageView* tree_mid = UIImageView::create();
        tree_mid->setTexture("main/tree_bg_middle.png");
        tree_scrollView->addChild(tree_mid);
        tree_mid->setPosition(ccp(360, 1214+c_middle_tree_padding*i));
    }
    
    for (int i=0; i<MAX_STAGE; i++) {
        UIWidget* icon_stage = CCUIHELPER->createWidgetFromJsonFile("IconStage.json");
        icon_stages[i] = icon_stage;
        if (i<c_stage_bottom_count) {
            icon_stage->setPosition(stage_bottom_pos[i]);
            max_height = MAX(stage_middle_pos[i].y,max_height);
        }else{
            int mid_id = i-c_stage_bottom_count;
            CCPoint pos = stage_middle_pos[mid_id%c_stage_middle_count];
            pos.y+=mid_id/c_stage_middle_count *c_middle_tree_padding;
            icon_stage->setPosition(pos);
            max_height = MAX(pos.y,max_height);
        }
        
        icon_stage->setZOrder(3);

        char n[10];
        sprintf(n,"%d",i+1);
        UILabelAtlas* num = (UILabelAtlas*)icon_stage->getChildByName("num");
        //num->setColor(ccc3(231, 245, 9));
        num->setStringValue(n);
        
        UIImageView* star[3];
        for (int j=0; j<3; j++) {
            char starName[20];
            sprintf(starName, "star_%d",j);
            star[j] = (UIImageView*)icon_stage->getChildByName(starName);
        }
        UIImageView* icon = (UIImageView*)icon_stage->getChildByName("icon");
        UIImageView* icon_off = (UIImageView*)icon_stage->getChildByName("icon_off");
        icon->setTag(i);
        
        StageInfo* info = (StageInfo*)G::g_stageInfos->objectAtIndex(i);
        
        if (info->isOpened) {
            icon->addReleaseEvent(this, coco_releaseselector(MainScene::onStageClicked));
            icon->setTouchEnable(true);
            for (int j=0; j<3; j++) {
                if (j<info->stars) {
                    star[j]->setTexture("main/start_on.png");
                }else
                    star[j]->setTexture("main/star_off.png");
            }
            
            UIWidget* light = icon_stage->getChildByName("light");
            if (G::G_getCurrentStage()==i+1) {
                UIImageView* arrow = UIImageView::create();
                arrow->setTexture("main/arrow.png");
                tree_scrollView -> addChild(arrow);
                arrow->setPosition(ccp(icon_stage->getPosition().x,icon_stage->getPosition().y+10));
                arrow->setAnchorPoint(_nBottom);
                arrow->setZOrder(20);
                arrow->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(0.2f,ccp(0, 7)), CCMoveBy::create(0.15f, ccp(0, -7)),NULL)));
                light->setScale(1.5f);
                light->setVisible(true);
                light->runAction(CCRepeatForever::create(CCRotateBy::create(6, 360)));
            }
            
            if (!info->isShowed&&G::G_getCurrentStage()==i+1) {
                if (G::tree_scroll_has_showed) {
                    PopStage(icon_stage,0.2f);
                }else{
                    PopStage(icon_stage,1.2f);
                }
                info->isShowed = true;
                HPersistence::S()->SaveStage(i);
            }else{
                icon->setVisible(true);
                icon_off->setVisible(false);
            }
        }else{
            icon->setTexture("main/icon_stage_close.png");
            icon->setTouchEnable(false);
            icon->setVisible(false);
            icon_off->setVisible(true);
            num->setVisible(false);
            for (int j=0; j<3; j++) {
                star[j]->setVisible(false);
            }
        }
        
        tree_scrollView->addChild(icon_stage);
        IntToStringFormat(_stageName, "aaaaa_%d", i);
        icon_stage->setName(_stageName);
        
    }
    return max_height;
}

void MainScene::PopStage(cocos2d::extension::UIWidget *icon_stage,float delay){
    UIWidget* icon = icon_stage->getChildByName("icon");
    UIWidget* icon_off = icon_stage->getChildByName("icon_off");
    icon_off->runAction(CCSequence::create(CCDelayTime::create(delay+0.2f),CCScaleTo::create(0.3f, 0),NULL));
    PopApple(icon, delay+0.6f);
    for (int j=0; j<3; j++) {
        IntToStringFormat(starName, "star_%d",j);
        UIWidget* star = icon_stage->getChildByName(starName);
        PopNode(star,delay+0.6f);
    }
}

void MainScene::onQuickCoin(cocos2d::CCObject *sender){
    G::G_playEffect(RES_MUSIC_NORMAL_CLICK);
    QuickBuy::show(m_layer,new QuickBuyParam(1));
}

void MainScene::onQuickPower(cocos2d::CCObject *sender){
    G::G_playEffect(RES_MUSIC_NORMAL_CLICK);
    QuickBuy::show(m_layer,new QuickBuyParam(3));
}

void MainScene::onQuickBook(cocos2d::CCObject *sender){
    G::G_playEffect(RES_MUSIC_NORMAL_CLICK);
    QuickBuy::show(m_layer,new QuickBuyParam(5));
}

void MainScene::onShopClicked(cocos2d::CCObject *sender){
    G::G_playEffect(RES_MUSIC_NORMAL_CLICK);
    Shop::show(m_layer);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    HJNI::callumeng("event1");
#endif
}

void MainScene::onShareClicked(cocos2d::CCObject* sender){
    Share::show(m_layer);
}

void MainScene::onAchieveClicked(cocos2d::CCObject *sender){
    Achievement::show(m_layer);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    HJNI::callumeng("event3");
#endif
}

void MainScene::onBaoClicked(cocos2d::CCObject *sender){
    Bao::show(m_layer);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    HJNI::callumeng("event2");
#endif
}

void MainScene::onTurnTableClicked(cocos2d::CCObject *sender){
    TurnTable::show(m_layer);
}

void MainScene::onStageClicked(cocos2d::CCObject *sender){
    UIWidget* u = (UIWidget*)sender;
    G::G_playEffect(RES_MUSIC_NORMAL_CLICK);
    G::G_loadGameMap(GAMEMODE_STAGE,u->getTag());
    GameStartShow* game_start_show =  GameStartShow::show(m_layer);
    game_start_show->addGameStartEvent(this, h_voidcallback(MainScene::StartGame));
}

void MainScene::onHole(cocos2d::CCObject *sender){
    if (G::g_hole_isOpened) {
        HoleModeShow* hole_show = HoleModeShow::show(m_layer);
        hole_show->addGameStartEvent(this, h_voidcallback(MainScene::StartGame));
    }else{
        HoleModeInfo::show(m_layer);
    }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    HJNI::callumeng("event4");
#endif
}

void MainScene::onSea(cocos2d::CCObject *sender){
    if (G::g_sea_isOpened) {
        SeaModeShow* sea_show = SeaModeShow::show(m_layer);
        sea_show->addGameStartEvent(this, h_voidcallback(MainScene::StartGame));
    }else{
        SeaModeInfo::show(m_layer);
    }
    //NormalTips::show(m_layer,new NormalTipsParam(3));
}

void MainScene::onBaoItemClicked(cocos2d::CCObject *sender){
    UIWidget* baoitem = (UIWidget*)sender;
    int id = baoitem->getTag();
    if (baos_level[id]>=G::G_getCurrentStage()+1) {
        NormalTips::show(m_layer,new NormalTipsParam(6,baos_level[id]));
    }else{
        if (id == 16) {//½ð²ù×Ó
            G::g_hole_isOpened = true;
        }
        BAO_INFO* info = (BAO_INFO*)G::g_bao_infos->objectAtIndex(id);
        info->isGot = true;
        baoitem->setTouchEnable(false);
        ScaleOutNode(baoitem, 0);
        HPersistence::S()->SaveBao(id);
        HPersistence::S()->SaveToFile();
    }
}

void MainScene::onCloudClicked(cocos2d::CCObject *sender){
    UIWidget* cloud = (UIWidget*)sender;
    int id = cloud->getTag();
    if (id<MAX_CLOUD) {
        int needStar = (id+1)*CLOUD_PADDING*3/2;
        if (needStar<=G::G_getTotalStar()) {
            G::g_cloud_isOpened[id]= true;
            CLOUD_FADE_OUT(cloud);
            HPersistence::S()->SaveToFile();
        }else{
            NormalTips::show(m_layer,new NormalTipsParam(4));
        }
    }else{
        NormalTips::show(m_layer,new NormalTipsParam(5));
    }
}

void MainScene::StartGame(){
    changeScene(M_SCENE_GAME);
}


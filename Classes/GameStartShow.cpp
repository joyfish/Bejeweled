//
//  GameStartShow.cpp
//  Bejeweled
//
//  Created by wilford on 14-3-19.
//
//

#include "GameStartShow.h"


void GameStartShow::init(void *data){
    m_gamestartListener = NULL;
    m_gamestartSelector = NULL;
    m_closeListener = NULL;
    m_closeSelector = NULL;
    CCDictionary* _dic = CCDictionary::createWithContentsOfFile("data/normaltips.plist");
    m_tips = CCUIHELPER->createWidgetFromJsonFile("GameStartShow.json");
    UIWidget* title = m_tips->getChildByName("title_bg");
    UILabelAtlas* num_stage = (UILabelAtlas*)title->getChildByName("num");
    UIWidget* left = title->getChildByName("title_0");
    UIWidget* right = title->getChildByName("title_1");
    IntToString(_stage, G::g_game_stage+1);
    num_stage->setStringValue(_stage);
    CCPoint num_pos = num_stage->getPosition();
    CCSize num_size = num_stage->getSize();
    left->setPosition(ccp(num_pos.x-num_size.width/2-50,num_pos.y));
    right->setPosition(ccp(num_pos.x+num_size.width/2+50,num_pos.y));
    
    StageInfo* stage_info = (StageInfo*)G::g_stageInfos->objectAtIndex(G::g_game_stage);
    for (int i=0; i<3; i++) {
        IntToStringFormat(_starName, "Star%d", i+1);
        UIWidget* _star = m_tips->getChildByName(_starName);
        if (i<stage_info->stars) {
            _star->setVisible(true);
        }else{
            _star->setVisible(false);
        }
    }
    UILabelBMFont* _target = (UILabelBMFont*)m_tips->getChildByName("label_lose_condition");
    CCString* _target_des;
    if (G::g_game_lose_conditions[LOSE_CONDITION_TIME]>0) {
        _target_des = (CCString*)_dic->objectForKey("game_start_time_target");
    }else{
        _target_des = (CCString*)_dic->objectForKey("game_start_step_target");
    }
    _target->setText(_target_des->getCString());
    
    
    
    int tool_ids[3] = {1,0,5};
    for (int i=0; i<3; i++) {
        G::g_game_buff[i] = 0;
        IntToStringFormat(_btnName, "tool_%d_bg", i);
        m_tool_btns[i] = m_tips->getChildByName(_btnName);
        ToolInfo* info = (ToolInfo*)G::g_toolinfos->objectAtIndex(tool_ids[i]);
        m_tool_count[i]= info->getHoldCount();
        UIWidget* tool_icon = m_tool_btns[i]->getChildByName("tool_icon");
        UIWidget* go = tool_icon->getChildByName("go");
        go->setVisible(false);
        UIWidget* used_num = tool_icon->getChildByName("usednum");
        used_num->setVisible(false);
        UILabelBMFont* hold_num = (UILabelBMFont*)tool_icon->getChildByName("holdnum");
        UIWidget* coin_cost = tool_icon->getChildByName("coin_cost");
        UILabelBMFont* cost_num = (UILabelBMFont*)coin_cost->getChildByName("num");
        IntToString(_cost, tool_prices[tool_ids[i]])
        cost_num ->setText(_cost);
        if (info->getHoldCount()>0) {
            coin_cost->setVisible(false);
            hold_num->setVisible(true);
            IntToString(_hold, info->getHoldCount());
            hold_num->setText(_hold);
        }else{
            coin_cost->setVisible(true);
            hold_num->setVisible(false);
        }
        UIWidget* lock = m_tool_btns[i]->getChildByName("lock");
        CCString* _lock_des = (CCString*)_dic->objectForKey("game_start_lock_des");
        IntToStringFormat(_lock_d, _lock_des->getCString(), tool_open_level[tool_ids[i]]+1);
        UILabelBMFont* label_lock = (UILabelBMFont*)lock->getChildByName("des");
        label_lock->setText(_lock_d);
        
        if (info->new_showed) {
            lock->setVisible(false);
            tool_icon->setVisible(true);
        }else{
            lock->setVisible(true);
            tool_icon->setVisible(false);
        }
    }
    
    _dic ->release();
}

void GameStartShow::update(float dt){
    //int tool_ids[3] = {1,0,5};
    for (int i=0; i<3; i++) {
        if (m_tool_btns[i]) {
            //ToolInfo* info = (ToolInfo*)G::g_toolinfos->objectAtIndex(tool_ids[i]);
            UIWidget* tool_icon = m_tool_btns[i]->getChildByName("tool_icon");
            UIWidget* go = tool_icon->getChildByName("go");
            UILabelAtlas* used_num = (UILabelAtlas*)tool_icon->getChildByName("usednum");
            UILabelBMFont* hold_num = (UILabelBMFont*)tool_icon->getChildByName("holdnum");
            UIWidget* coin_cost = tool_icon->getChildByName("coin_cost");
            if (m_tool_count[i]>G::g_game_buff[i]) {
                hold_num->setVisible(true);
                coin_cost->setVisible(false);
                IntToString(_num,m_tool_count[i]-G::g_game_buff[i]);
                hold_num->setText(_num);
            }else{
                hold_num->setVisible(false);
                coin_cost->setVisible(true);
            }
            if (G::g_game_buff[i]>0) {
                go->setVisible(true);
                used_num->setVisible(true);
                IntToString(_num, G::g_game_buff[i]);
                used_num->setStringValue(_num);
            }else{
                go->setVisible(false);
                used_num->setVisible(false);
            }
        }
    }
    if (m_help_id!=-1) {
        if (!GameHelpMaskTips::S()) {
            showHelpMask(m_help_id+1);
            m_help_id = -1;
        }
    }
}

void GameStartShow::startAnim(){
    HCCWindow::startAnim();
    UIWidget* btn_close = m_tips->getChildByName("btn_close");
    PopNode(btn_close, 0.4f);
    btn_close->setTouchEnable(true);
    btn_close->addReleaseEvent(this, coco_releaseselector(GameStartShow::onCloseClick));
    UIWidget* btn_start = m_tips->getChildByName("btn_start");
    PopNode(btn_start, 0.8f);
    btn_start->addReleaseEvent(this, coco_releaseselector(GameStartShow::onStartGame));
    
    int tool_ids[3] = {1,0,5};
    for (int i=0; i<3; i++) {
        ToolInfo* info = (ToolInfo*)G::g_toolinfos->objectAtIndex(tool_ids[i]);
        if (G::g_game_stage>=tool_open_level[tool_ids[i]]) {
            UIWidget* tool_icon = m_tool_btns[i]->getChildByName("tool_icon");
            if (!info->new_showed) {
                UIWidget* lock = m_tool_btns[i]->getChildByName("lock");
                lock->runAction(CCSequence::create(CCDelayTime::create(0.8f),CCScaleTo::create(0.2f, 0),CCHide::create(),NULL));
                tool_icon->setVisible(true);
                PopNode(tool_icon, 1.0f);
                tool_icon->runAction(CCSequence::create(CCDelayTime::create(1.0f),CCCallFuncND::create(this, callfuncND_selector(GameStartShow::onShowLockOutOver),tool_icon), NULL));
                info->new_showed=true;
                HPersistence::S()->SaveToFile();
            }
            tool_icon->setTag(i);
            if ((i == 0&& G::g_game_lose_conditions[LOSE_CONDITION_STEP]>0)||
                (i == 1&& G::g_game_lose_conditions[LOSE_CONDITION_TIME]>0)||
                i==2) {
                tool_icon->setTouchEnabled(true);
                tool_icon->addReleaseEvent(this, coco_releaseselector(GameStartShow::onToolClick));
            }else{
                tool_icon->setColor(ccc3(128, 128, 128));
            }
           
        }
    }
}



void GameStartShow::onToolClick(cocos2d::CCObject *sender){
    if (helpMask) {
        closeHelpMask();
        //showHelpMask(m_help_id+1);
    }
    UIWidget* u = (UIWidget*)sender;
    int tag = u->getTag();
    int tool_ids[3] = {1,0,5};
//    ToolInfo* info = (ToolInfo*)G::g_toolinfos->objectAtIndex(tool_ids[tag]);
    int cost =0;
    for (int i=0; i<3; i++) {
        if (G::g_game_buff[i]>=m_tool_count[i]) {
            cost += (G::g_game_buff[i]-m_tool_count[i])*tool_prices[tool_ids[i]];
            if (i==tag) {
                cost+=tool_prices[tool_ids[i]];
            }
        }
    }
    if (cost > G::G_getCoin()) {
        QuickBuy::show(m_layer,new QuickBuyParam(0));
        return;
    }
//    if (info->getHoldCount()>0) {
//        info->setHoldCount(info->getHoldCount()-1);
//    }else{
//        if (!G::G_costCoin(tool_prices[tool_ids[tag]])) {
//            QuickBuy::show(m_layer,new QuickBuyParam(0));
//            return;
//        }
//    }
//    HPersistence::S()->SaveToFile();
    G::g_game_buff[tag]++;
}

void GameStartShow::onStartGame(cocos2d::CCObject *sender){
    closeHelpMask();
    G::G_checkPowerRecovery(this, h_voidcallback(HPersistence::SaveToFile));
    if (G::G_costPower(1)) {
        int cost =0;
        int tool_ids[3] = {1,0,5};
        for (int i=0; i<3; i++) {
            ToolInfo* info = (ToolInfo*)G::g_toolinfos->objectAtIndex(tool_ids[i]);
            
            if (G::g_game_buff[i]>=m_tool_count[i]) {
                cost += (G::g_game_buff[i]-m_tool_count[i])*tool_prices[tool_ids[i]];
                info->setHoldCount(0);
            }else{
                info->setHoldCount(m_tool_count[i]-G::g_game_buff[i]);
            }
        }
        G::G_costCoin(cost);

        G::G_playEffect(RES_MUSIC_GAME_START);
        if (m_gamestartListener&&m_gamestartSelector) {
            (m_gamestartListener->*m_gamestartSelector)();
        }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        IntToStringFormat(_level, "level%d", G::g_game_stage+1);
        HJNI::umengstartLevel(_level);
#endif
        HPersistence::S()->SaveStage(G::g_game_stage);
        HPersistence::S()->SaveToFile();
    }else{
        QuickBuy::show(m_layer,new QuickBuyParam(2));
    }
}

GameStartShow* GameStartShow::instance;
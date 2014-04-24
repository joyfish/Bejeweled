//
//  GameLogic_ui.cpp
//  Test
//
//  Created by wilford on 14-3-6.
//
//

#include "GameLogic_ui.h"
#include "QuickBuy.h"


void GameLogic_ui::ShowGamePause(CCObject* sender){
    if (!isInCustomTime()) {
        return;
    }
    if (IsRefreshTime()) {
        return;
    }
    if (m_tool_mask) {
        return;
    }

    if (m_gamePause_listener&&m_gamePause_selector) {
        (m_gamePause_listener->*m_gamePause_selector)();
    }
    
}



void GameLogic_ui::UseTool(int tool_id,int pos_id){
    if (m_blocks[pos_id]->getBottomType() == BLOCK_BOTTOM_GUN||
        m_blocks[pos_id]->getBottomType() == BLOCK_BOTTOM_COIL_GUN||
        m_blocks[pos_id]->getBottomType() == BLOCK_BOTTOM_SPACE
        )
    {
        //showXAnim(pos_id);
        return;
    }

    
    switch(tool_id){
        case 4:
        if(!MagicTool(pos_id)){
            showXAnim(pos_id);
            return;
        }
            showMagicAnim(pos_id);
            break;
        case 2:
        if(!BombTool(pos_id)){
            showXAnim(pos_id);
            return;
        }
        showHammerAnim(pos_id);
            break;
    }
    UIWidget* _icon = toolwidget[tool_id]->getChildByName("tool_icon");
    _icon->runAction(CCScaleTo::create(0.1f,1.0f));
    m_tool_selected = -1;
    clearToolMask();
    HPersistence::S()->SaveToFile();
    
}

bool GameLogic_ui::MagicTool(int pos_id){
    if (m_gems[pos_id]->isEmpty()) {
        return false;
    }
    if(m_gems[pos_id]->getType() == GEM_NORMAL){
        showSeaHurt(200, pos_id);
        if (t_getRandom(2)) {
            createGem(pos_id,(GEM_H*10+m_gems[pos_id]->getColor()),0.4f);
        }else{
            createGem(pos_id,(GEM_V*10+m_gems[pos_id]->getColor()),0.4f);
        }
        
        //selected_tool_id = -1;
        clearHelp();
        return  true;
    }
    return false;
}

bool GameLogic_ui::BombTool(int pos_id){
    if (m_blocks[pos_id]->getBottomType() == BLOCK_BOTTOM_GUN||
        m_blocks[pos_id]->getBottomType() == BLOCK_BOTTOM_COIL_GUN) {
        return false;
    }
    
    if(m_blocks[pos_id]->getTopType()!=BLOCK_TOP_NONE){
        Bomb(pos_id,0.2f);
        clearHelp();
        return true;
    }
    if(m_gems[pos_id]->getType() == GEM_GOLD)
        return false;
    if (!m_gems[pos_id]->isEmpty()) {
        Bomb(pos_id,0.2f);
        clearHelp();
        return true;
    }
    return false;
}

void GameLogic_ui::updateToolBtns(){
    for (int i=0; i<MAX_TOOL_COUNT; i++) {
        ToolInfo* info = (ToolInfo*)G::g_toolinfos->objectAtIndex(i);
        if (toolwidget[i] != NULL) {
            if (!info->new_showed&&G::g_game_mode==GAMEMODE_STAGE) {
                continue;
            }
            UIWidget* cost_bg =toolwidget[i]->getChildByName("cost");
            UIWidget* count_bg = toolwidget[i]->getChildByName("count");
            if (info->getHoldCount()<=0) {
                cost_bg->setVisible(true);
                count_bg->setVisible(false);
            }else{
                cost_bg->setVisible(false);
                count_bg->setVisible(true);
                UILabelBMFont* _count_num = (UILabelBMFont*)count_bg->getChildByName("num");
                IntToString(_num, info->getHoldCount())
                _count_num->setText(_num);
            }
        }
    }
    if (m_coin_num) {
        IntToString(_coin_num,G::G_getCoin());
        m_coin_num->setText(_coin_num);
    }
}

void GameLogic_ui::ToolBuy(int id,int count){
    if( m_tool_buy_listener && m_tool_buy_selector){
        (m_tool_buy_listener->*m_tool_buy_selector)(id,count);
    }
}

void GameLogic_ui::OnControllerButtonClicked(CCObject* sender){
    CCLOG("onToucc");
    if (!hasHelp()&&!isInGuide) {
        return;
    }
    if (m_tool_selected != -1) {
        return;
    }
    
    G::G_playEffect(RES_MUSIC_GAME_TOOL);
    
    UIWidget* u = (UIWidget*)sender;
    
    u->runAction(CCSequence::create(
                                    CCScaleTo::create(0.2f,1.1f,1.1f),
                                    CCScaleTo::create(0.2f,1,1),
                                    NULL
                                    ));
    
    int tag = u->getTag();
    
   
    
    if (!G::G_costTool(tag)) {
        QuickBuy::show(m_layer,new QuickBuyParam(0));
        return;
    }
    HPersistence::S()->SaveToFile();
    
    
    G::G_playEffect(RES_MUSIC_GAME_TOOL);
    
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //    char val[30];
    //    sprintf(val,"stage_%d",G::g_game_stage+1);
    //    G
    //    Tool::callumengs(UMENG_TOOL_EVENT,"tool_use",val,NULL);
#endif
    
    switch(tag){
        case TOOL_TYPE_TIME:
            if(m_lose_conditions[LOSE_CONDITION_TIME]>0){
                m_lose_conditions_now[LOSE_CONDITION_TIME] += 20;
                G::G_Add_Achievement_Complete(16);
//                if (m_lose_conditions_now[LOSE_CONDITION_TIME]>20) {
//                    UIWidget* btn = toolwidget[0];
//                    if (btn != NULL) {
//                        btn -> stopAllActions();
//                    }
//                }
            }
            break;
        case TOOL_TYPE_STEP:
            if(m_lose_conditions[LOSE_CONDITION_STEP]>0){
                m_lose_conditions_now[LOSE_CONDITION_STEP]+=5;
                G::G_Add_Achievement_Complete(24);
//                if (m_lose_conditions_now[LOSE_CONDITION_STEP]>5) {
//                    UIWidget* btn = toolwidget[2];
//                    if (btn != NULL) {
//                        btn -> stopAllActions();
//                    }
//                }
            }
      
            break;
        case TOOL_TYPE_REFRESH:
            RefreshGems();
            achieve_count->use_reposion_bomb_count++;
            //RePositionGems();
            //achieve_count->use_reposion_bomb_count++;
            break;
        case TOOL_TYPE_SPECIAL:
        case TOOL_TYPE_HAMMER:
        {
            UIWidget* icon = u->getChildByName("tool_icon");
            icon->runAction(CCScaleTo::create(0.1f, 1.5f));
            m_tool_selected = tag;
            showToolMask(tag);
        }
            break;
        case TOOL_TYPE_STAR:
            showNormalTips(2);
            achieve_count->use_star_count++;
            score_rate += 0.05f;
            //SHOW_NORMAL_TIPS(4);
            break;
    }
    
    if (isInGuide) {
        closeGuide();
    }
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    char val[30];
    sprintf(val,"stage_%d",G::g_game_stage+1);
    IntToStringFormat(_toolUse, "tool_use_%d", tag);
    HJNI::callumengs("propsUseEvent",_toolUse,val,NULL);
#endif
}

void GameLogic_ui::initToolBtns(UIWidget* parent){
    int show_btn_count = 0;
    
    CCDictionary* _dic = CCDictionary::createWithContentsOfFile("data/tool_des.plist");
    
    vector<int> tool_ids;
    
    for (int i=0; i<MAX_TOOL_COUNT; i++) {
        toolwidget[i] = NULL;
        if (i == TOOL_TYPE_STEP||
            i == TOOL_TYPE_TIME||
            i == TOOL_TYPE_STAR) {
            continue;
        }
        tool_ids.push_back(i);
    }
    
    for (int i = 0; i < tool_ids.size(); i++){
        for (int j = 1; j < tool_ids.size() - i; j++)
            if (tool_open_level[tool_ids[j - 1]] >tool_open_level[ tool_ids[j]]){
                int tmp = tool_ids[j-1];
                tool_ids[j-1] = tool_ids[j];
                tool_ids[j] = tmp;
            }
    }
              
    
    
    for(int x=0;x<tool_ids.size();x++){
        int i = tool_ids[x];
//        toolwidget[i] = NULL;
//        if (i == TOOL_TYPE_STEP||
//            i == TOOL_TYPE_TIME||
//            i == TOOL_TYPE_STAR) {
//            continue;
//        }
        
        char btnName[30];
        sprintf(btnName,"BTN_TOOL_BG_0%d",i);
        
        UIWidget* btn_tool = CCUIHELPER->createWidgetFromJsonFile("ToolBtn.json");
        
        
        parent->addChild(btn_tool);
        btn_tool->setPosition(ccp(-315+show_btn_count*110+52,52));
        btn_tool->setName(btnName);
        
        UIWidget* count_bg = btn_tool->getChildByName("count");
        count_bg->setVisible(false);
        UIWidget* cost_bg = btn_tool->getChildByName("cost");
        cost_bg->setVisible(false);
        UILabelBMFont* _cost_num = (UILabelBMFont*)cost_bg->getChildByName("num");
        IntToString(_cost, tool_prices[i]);
        _cost_num->setText(_cost);
        
        COCO_UIIMAGEVIEW* tool_icon = (COCO_UIIMAGEVIEW*) btn_tool->getChildByName("tool_icon");
        IntToStringFormat(_iconName, "tools/icon_%d.png",i);
        tool_icon->setTexture(_iconName);
        tool_icon ->setVisible(false);
        COCO_UIIMAGEVIEW* btn_tool_bg = (COCO_UIIMAGEVIEW*)btn_tool->getChildByName("tool_bg");
        
        toolwidget[i] = btn_tool_bg;
        tool_icon->setScale(1.0f);
        tool_icon->setTouchEnable(false);
        
        btn_tool_bg->addReleaseEvent(this,coco_releaseselector(GameLogic_ui::OnControllerButtonClicked));
        btn_tool_bg->setTag(i);
        show_btn_count++;
        
        UIWidget* lock = btn_tool->getChildByName("lock");
        lock->setVisible(false);
        UIWidget* lock_stage = btn_tool_bg->getChildByName("lock_stage");
        lock_stage->setVisible(false);
        
        UILabelBMFont* label_lock = (UILabelBMFont*)lock_stage->getChildByName("label");
        CCString* _des = (CCString*)_dic->objectForKey("lock_stage");
        char _d[30];
        sprintf(_d, _des->getCString(),tool_open_level[i]+1);
        label_lock->setText(_d);
        
        ToolInfo* info = (ToolInfo*) G::g_toolinfos->objectAtIndex(i);
        if (G::g_game_stage>=tool_open_level[i]||G::g_game_mode!=GAMEMODE_STAGE||info->new_showed) {
            
            if (info->getHoldCount()>0) {
                UILabelBMFont* _count_num = (UILabelBMFont*)count_bg->getChildByName("num");
                IntToString(_count, info->getHoldCount());
                _count_num->setText(_count);
                count_bg->setVisible(true);
            }else{
                cost_bg->setVisible(true);
            }
            count_bg->setVisible(true);
            if (!info->new_showed&&G::g_game_mode==GAMEMODE_STAGE) {
                ToolOpenAnim(btn_tool,0.4f);
                info->new_showed = true;
                HPersistence::S()->SaveToFile();
            }else{
                tool_icon->setVisible(true);
            }
            btn_tool_bg->setTouchEnable(true);
        }else{
            lock->setVisible(true);
            btn_tool_bg->setTouchEnable(false);
            lock_stage->setVisible(true);
        }
    }
    if (show_btn_count>0) {
        switch (G::g_game_mode) {
            case GAMEMODE_STAGE:
                 parent->setPosition(ccp(320+(MAX_TOOL_COUNT-show_btn_count)*110/2+30,_pBottom-80));
                break;
            case GAMEMODE_HOLE:
                 parent->setPosition(ccp(320+(MAX_TOOL_COUNT-show_btn_count)*110/2+80,_pBottom-80));
                break;
            case GAMEMODE_SEA:
                 parent->setPosition(ccp(320+(MAX_TOOL_COUNT-show_btn_count)*110/2+30,_pBottom-80));
                break;
            default:
                break;
        }
        parent->runAction(CCMoveBy::create(0.2f, ccp(0,80)));
    }
    _dic->release();
}

void GameLogic_ui::ToolOpenAnim(UIWidget* tool,float delay){
    UIWidget* lock = tool->getChildByName("lock");
    //UIWidget* count_bg = tool->getChildByName("count_bg");
    UIWidget* icon = tool->getChildByName("tool_icon");
    icon->setVisible(true);
    lock->setVisible(true);
    icon->setScale(0);
    icon->runAction(CCSequence::create(CCDelayTime::create(0.4f+delay),CCScaleTo::create(0.4f, 1.0f),NULL));
    icon->runAction(CCSequence::create(CCDelayTime::create(0.4f+delay),CCRotateBy::create(0.4f, 360),NULL));
    lock->runAction(CCSequence::create(CCDelayTime::create(delay),CCRotateBy::create(1.0f, 360),NULL));
    lock->runAction(CCSequence::create(CCDelayTime::create(delay),CCScaleTo::create(1.0f, 0),NULL));
//    count_bg->runAction(CCSequence::create(CCDelayTime::create(1.0f+delay),CCShow::create(),NULL));
}

void GameLogic_ui::initUI(){
    
    UIWidget* gameUI = CCUIHELPER->createWidgetFromJsonFile("GameUI.json");
    
    m_ui_layer->addWidget(gameUI);
    
    COCO_UIBUTTON* btn_back = (COCO_UIBUTTON*)gameUI->getChildByName("btn_back");
    btn_back->addReleaseEvent(this,coco_releaseselector(GameLogic_ui::ShowGamePause));
    
    UIPanel* top_panel = (UIPanel*)m_ui_layer->getWidgetByName("Top");
    UIPanel* bottom_panel = UIPanel::create();
    m_ui_layer->addWidget(bottom_panel);
    top_panel->setPosition(ccp(0,_pTop-20));
    bottom_panel->setPosition(ccp(_pCenter.x, _pBottom));
    
    initToolBtns(bottom_panel);
    
    UIImageView* _coin_bg = UIImageView::create();
    _coin_bg->setTexture("normalgame/coin_bg.png");
    m_ui_layer->addWidget(_coin_bg);
    switch (G::g_game_mode) {
        case GAMEMODE_STAGE:
            _coin_bg->setPosition(ccp(_pLeft+100, _pBottom+60));
            break;
        case GAMEMODE_HOLE:
        {
            float offsety =  (_pScreenSize.height - 960)/2;
            _coin_bg->setPosition(ccp(_pLeft+100, _pBottom+840+offsety));
        }
            break;
        case GAMEMODE_SEA:
            _coin_bg->setPosition(ccp(_pLeft+100, _pBottom+60));
            break;
        default:
            break;
    }
   
    m_coin_num = UILabelBMFont::create();
    m_coin_num ->setFntFile("font/font.fnt");
    _coin_bg->addChild(m_coin_num);
    m_coin_num->setPosition(ccp(22, -14));
    
    UIWidget* bar_bg = gameUI->getChildByName("bar_bg");
    bar_bg->setZOrder(10);
    m_score_bar = (UILoadingBar*)m_ui_layer->getWidgetByName("bar");
    
     UIWidget* score_bar_bg = m_ui_layer->getWidgetByName("bar_bg");
    
    if (G::g_game_mode != GAMEMODE_STAGE) {
        score_bar_bg->setVisible(false);
    }
    
    
    UILabelBMFont* scoreLabel = UILabelBMFont::create();
    scoreLabel->setFntFile("font/font.fnt");
    scoreLabel->setColor(ccc3(255,0,0));
    m_score_bar->addChild(scoreLabel);
    scoreLabel->setTag(13);
    m_score_num = NULL;
//    m_score_num = UILabelBMFont::create();
//    m_score_num->setFntFile("font/font.fnt");
//    m_score_bar->addChild(m_score_num);
    ///m_score_num->setColor(ccc3(255, 0, 0));
    
    
    int percent = m_score_current*100/m_score_max;
    m_score_bar->setPercent(percent);
    
    
    float pos_flag_2 = 565*(float)m_score_2star/(float)m_score_max-565/2;
    float pos_flag_3 = 565*(float)m_score_3star/(float)m_score_max-565/2;
    
    CCLog("flag_2 %f,flag_3 %f",pos_flag_2,pos_flag_3);
    
    flag_2 = COCO_UIIMAGEVIEW::create();
    flag_3 = COCO_UIIMAGEVIEW::create();
    
    m_score_bar->addChild(flag_2);
    m_score_bar->addChild(flag_3);
    flag_2->setTexture("normalgame/flag_2_down.png");
    flag_3->setTexture("normalgame/flag_3_down.png");
    flag_2->setZOrder(2);
    flag_3->setZOrder(3);
    flag_2->setPosition(ccp(pos_flag_2, 5));
    flag_3->setPosition(ccp(pos_flag_3, 5));
    
    flag_2->setColor(ccc3(254, 254, 254));
    flag_3->setColor(ccc3(254, 254, 254));
    
    PopNode(flag_2, 0.2f);
    PopNode(flag_3, 0.4f);
    
    UIWidget* title = gameUI->getChildByName("title");
    if (G::g_game_mode!= GAMEMODE_STAGE) {
        title->setVisible(false);
    }
    
    UIWidget* win_condition_bg = m_ui_layer->getWidgetByName("win_conditon");
    win_condition_bg->setPosition(ccp(338, -100));
    
    
    for(int i=0;i<4;i++){
        char cName[30];
        sprintf(cName,"target_bg_%d",i+1);
        COCO_UIIMAGEVIEW* win_condition = (COCO_UIIMAGEVIEW*)m_ui_layer->getWidgetByName(cName);
        win_condition->setVisible(false);
    }
    
    //	UILabelAtlas* num_stage = (UILabelAtlas*)m_layer->getWidgetByName("stage_num");
    //	char stageStr[4];
    //	sprintf(stageStr,"%d",G::g_game_stage+1);
    //	num_stage->setStringValue(stageStr);
    //
    //	CCPoint nPoint = num_stage->getPosition();
    //	UIImageView* label_win_condition_title_0 = (UIImageView*)m_layer->getWidgetByName("left");
    //	label_win_condition_title_0->setPosition(ccp(nPoint.x-num_stage->getRect().size.width-4,nPoint.y));
    
    
    int _condition_count = 0;
    for(int i=0;i<WIN_CONDITION_MAX;i++){
        m_label_win_conditions[i] = NULL;
        m_win_condition_icons[i] = NULL;
        m_win_condition_progress[i]= NULL;
        if (i==WIN_CONDITION_SCORE) {
            continue;
        }
        if(m_win_conditions[i]>0){
            for(int j=0;j<4;j++){
                char cName[30];
                sprintf(cName,"target_bg_%d",j+1);
                UIWidget* win_condition = m_ui_layer->getWidgetByName(cName);
                if(!win_condition->isVisible()){
                    win_condition->setVisible(true);
                    
                    COCO_UIIMAGEVIEW* icon = (COCO_UIIMAGEVIEW*)win_condition->getChildByName("icon");
                    m_win_condition_icons[i] = icon;
                    IntToStringFormat(_iconPath, "icons/icon_gem_%d.png", i);
                    icon->setTexture(_iconPath);
                    //icon->setScale(0.7f);
                    m_label_win_conditions[i] = (UILabelBMFont*)win_condition->getChildByName("num");
                    IntToStringFormat(cText,"0/%d", m_win_conditions[i]);
                    m_label_win_conditions[i]->setText(cText);
                    UIWidget* arrow = win_condition->getChildByName("arrow");
                    arrow->setVisible(false);
                    _condition_count++;
                    m_win_condition_progress[i] = (UILoadingBar*)win_condition->getChildByName("progress");
                    m_win_condition_progress[i]->setPercent(0);
                    break;
                }
            }
        }
    }
    
    float _offsetX = 0;
    float _offsetY = 0;
    if (_condition_count>2) {
        _offsetY=50;
    }
    if(_condition_count>1){
        _offsetX = 140;
    }
    for (int i=0; i<_condition_count; i++) {
        char cName[30];
        sprintf(cName,"target_bg_%d",i+1);
        UIWidget* win_condition = m_ui_layer->getWidgetByName(cName);
        CCPoint pos = ccp(-_offsetX/2+i%2*_offsetX,_offsetY/2-i/2*_offsetY);
        CCLOG("offsetX %f,  x = %f, y= %f",_offsetX, pos.x,pos.y);
        win_condition->setPosition(pos);
        PopNode(win_condition, 0.5f);
    }
    
    
    m_label_win_conditions[WIN_CONDITION_SCORE] = NULL;
    UIWidget* win_condition = m_ui_layer->getWidgetByName("score_bg");
    win_condition->setVisible(false);
    if(m_win_conditions[WIN_CONDITION_SCORE]>0){
        win_condition->setVisible(true);
        m_label_win_conditions[WIN_CONDITION_SCORE] = (UILabelBMFont*)win_condition->getChildByName("num");
        IntToStringFormat(cText, "0/%d", m_win_conditions[WIN_CONDITION_SCORE])
        m_label_win_conditions[WIN_CONDITION_SCORE]->setText(cText);
    }
    
    UIWidget* icon_time = gameUI->getChildByName("time_icon");
    UIWidget* icon_step = gameUI->getChildByName("step_icon");
    time_or_step_bg = gameUI->getChildByName("icon_bg");
    if(m_lose_conditions[LOSE_CONDITION_TIME]>0){
        icon_time->setVisible(true);
        icon_step->setVisible(false);
    }else if(m_lose_conditions[LOSE_CONDITION_STEP]>0){
        icon_time->setVisible(false);
        icon_step->setVisible(true);
    }else{
        time_or_step_bg->setVisible(false);
    }
    
    if (G::g_game_mode== GAMEMODE_HOLE) {
        time_or_step_bg->setVisible(false);
    }
    else
    {
        PopNode(time_or_step_bg, 0.3f);
        if (G::g_game_mode == GAMEMODE_SEA) {
            CCPoint pre_pos = time_or_step_bg->getPosition();
            time_or_step_bg->setPosition(ccp(pre_pos.x-20,pre_pos.y-70));
        }
    }
    
    num_time_or_step = (UILabelAtlas*)m_ui_layer->getWidgetByName("time_or_step_num");
    if(m_lose_conditions[LOSE_CONDITION_TIME]>0){
        char t[10];
        int tmpt = floor(m_lose_conditions_now[LOSE_CONDITION_TIME]);
        char sec[4];
        sprintf(sec,tmpt%60>=10?"%d":"0%d",tmpt%60);
        char min[4];
        sprintf(min,tmpt/60>=10?"%d":"0%d",tmpt/60);
        sprintf(t,"%s:%s",min,sec);
        num_time_or_step->setStringValue(t);
    }else if(m_lose_conditions[LOSE_CONDITION_STEP]>0){
        char s[10];
        int tmps = floor(m_lose_conditions_now[LOSE_CONDITION_STEP]);
        sprintf(s,"%d",tmps);
        num_time_or_step->setStringValue(s);
    }
}

void GameLogic_ui::showWinConditionAnim(int id){
    if (m_win_condition_icons[id]) {
        if (m_win_condition_icons[id]->getRenderer()->numberOfRunningActions()==0) {
            m_win_condition_icons[id]->runAction(CCSequence::create(CCScaleTo::create(0.2f, 1.5f),CCScaleTo::create(0.2f, 0.7f),CCScaleTo::create(0.2f, 1.1f),CCScaleTo::create(0.2f, 1.0f),NULL));
        }
    }
}

void GameLogic_ui::updateSea(float dt){
    
    if (G::g_game_mode!=GAMEMODE_SEA) {
        return;
    }
    
    if (game_state != GAME_STATE_PLAY ) {
        return;
    }
    
    if (HWindowsManager::S()->hasWindowsShowed()) {
        return;
    }
    
    if (m_tool_selected !=-1) {
        return;
    }

    m_sea_bar->setPercent(m_sea_blood*100/m_sea_max_blood);
    
    if (m_sea_blood == 0) {
        game_lose();
    }
}

void GameLogic_ui::updateHole(float dt){
    
    if (G::g_game_mode!=GAMEMODE_HOLE) {
        return;
    }
    
    char n_score[10];
    sprintf(n_score,"%d",m_hole_score);
    m_hole_score_num->setStringValue(n_score);
    
    if (game_state != GAME_STATE_PLAY ) {
        return;
    }
    
    if (HWindowsManager::S()->hasWindowsShowed()) {
        return;
    }
    
    if (m_tool_selected !=-1) {
        return;
    }
    
    
    Lose_Condition_Add(LOSE_CONDITION_TIME,dt);
//    m_lose_conditions_now[LOSE_CONDITION_TIME]-=dt;
//    m_lose_conditions_now[LOSE_CONDITION_TIME] = MAX(0,m_lose_conditions_now[LOSE_CONDITION_TIME]);
    
    int t = floor(m_lose_conditions_now[LOSE_CONDITION_TIME]);
    char n_t[10];
    sprintf(n_t, "%d:%d",t/60,t%60);
    m_hole_time_num->setStringValue(n_t);
    m_hole_bar->setPercent(t*100/maxHoleTime);
    
//    if (m_lose_conditions_now[LOSE_CONDITION_TIME] == 0) {
//        game_lose();
//    }
    
    int m = m_hole_level*20;
    for (int i=0; i<4; i++) {
        if (m%10==m_hole_m%10) {
            m/=10;
            m_hole_m/=10;
            continue;
        }
        char n_m[3];
        sprintf(n_m, "%d",m%10);
        m/=10;
        m_hole_m/=10;
        CCPoint pos = m_hole_num[i]->getPosition();
        UIWidget* parent = m_hole_num[i]->getParent();
        m_hole_num[i]->runAction(CCSequence::create(CCMoveBy::create(0.3f, ccp(0, 50)),CCCallFuncND::create(this, callfuncND_selector(G::G_callbackRemoveUIWidget), m_hole_num[i]),NULL));
        m_hole_num[i] = UILabelAtlas::create();
        m_hole_num[i]->setProperty(n_m, "hole/m_num.png", 20, 28, "0");
        m_hole_num[i]->setPosition(ccp(pos.x,pos.y-50));
        parent->addChild(m_hole_num[i]);
        m_hole_num[i]->runAction(CCMoveBy::create(0.3f, ccp(0, 50)));
    }
    m_hole_m = m_hole_level*20;
}

void GameLogic_ui::updateConditions(float dt){
    //if(!IsTaskOver&&!HWindowsManager::S()->hasWindowsShowed())
    if (G::g_game_mode==GAMEMODE_HOLE) {
        return;
    }
    
    if (game_state == GAME_STATE_PLAY && !HWindowsManager::S()->hasWindowsShowed() && m_tool_selected ==-1) {
        Lose_Condition_Add(LOSE_CONDITION_TIME,dt);
        m_time_caculate+=dt;
    }
    
    if (game_state == GAME_STATE_PLAY) {
        if ((m_lose_conditions[LOSE_CONDITION_TIME]>0&&m_lose_conditions_now[LOSE_CONDITION_TIME]<30)||
            (m_lose_conditions[LOSE_CONDITION_STEP]>0&&m_lose_conditions_now[LOSE_CONDITION_STEP]<3)) {
            if (time_or_step_bg->getRenderer()->numberOfRunningActions()==0) {
                time_or_step_bg->runAction(CCRepeatForever::create(CCSequence::create( CCScaleTo::create(0.2f, 1.2f),CCScaleTo::create(0.3f, 1.0f),NULL)));
            }
        }else{
            time_or_step_bg->setScale(1);
            time_or_step_bg->stopAllActions();
        }
    }else{
        time_or_step_bg->setScale(1);
        time_or_step_bg->stopAllActions();
    }
    
    if(m_lose_conditions[LOSE_CONDITION_TIME]>0){
        char t[20];
        int tmpt = floor(m_lose_conditions_now[LOSE_CONDITION_TIME]);
        char sec[4];
        sprintf(sec,tmpt%60>=10?"%d":"0%d",tmpt%60);
        char min[4];
        sprintf(min,tmpt/60>=10?"%d":"0%d",tmpt/60);
        sprintf(t,"%s:%s",min,sec);
        if (num_time_or_step!=NULL) {
            num_time_or_step->setStringValue(t);
        }
        
    }else if(m_lose_conditions[LOSE_CONDITION_STEP]>0){
        char s[10];
        int tmps = floor(m_lose_conditions_now[LOSE_CONDITION_STEP]);
        sprintf(s,"%d",tmps);
        if (num_time_or_step!=NULL) {
            num_time_or_step->setStringValue(s);
        }
        
    }
    
    int percent;
    if (m_score_current>m_score_max) {
        percent = 100;
    }else{
        percent = m_score_current*100/m_score_max;

    }
    if (m_score_num) {
        char _score[30];
        sprintf(_score,"%d/%d", m_score_current,m_score_max);
        m_score_num->setText(_score);
    }
    m_score_bar->setPercent(percent);
    
    if (m_score_current>=m_score_2star) {
        if (flag_2) {
            
            if (flag_2->getColor().r == 254) {
                flag_2->setTexture("normalgame/flag_2.png");
                flag_2->setColor(ccc3(255, 255, 255));
            }
        }
        
    }
    
    if (m_score_current>=m_score_3star) {
        if (flag_3) {
            if (flag_3->getColor().r == 254) {
                flag_3->setTexture("normalgame/flag_3.png");
                flag_3->setColor(ccc3(255, 255, 255));
            }
        }
    }
    
    
    for(int i=0;i<WIN_CONDITION_MAX;i++){
        if(m_label_win_conditions[i]!=NULL){
            char n[20];
            sprintf(n,"%d/%d",m_win_conditions_now[i],m_win_conditions[i]);
            m_label_win_conditions[i]->setText(n);
            if(m_win_conditions[i]==m_win_conditions_now[i]){
                UIWidget* g = m_label_win_conditions[i]->getParent()->getParent()->getChildByName("arrow");
                if (g!=NULL) {
                    g->setVisible(true);
                }
                //m_label_win_conditions[i]->setColor(ccc3(0,255,0));
            }
            if (m_win_condition_progress[i]!=NULL) {
                int percent =m_win_conditions_now[i]*100/m_win_conditions[i];
                m_win_condition_progress[i]->setPercent(percent);
            }
        }
    }
}

void GameLogic_ui::RotateEye(){
    if (m_sea_eye_left->numberOfRunningActions()==0&&
        m_sea_eye_right->numberOfRunningActions()==0) {
        m_sea_eye_left->runAction(CCRotateBy::create(0.9f, -1080));
        m_sea_eye_right->runAction(CCRotateBy::create(0.9f, 1080));
        
        CCPoint headP = ccp((m_sea_eye_left->getPositionX()+m_sea_eye_right->getPositionX())/2,(m_sea_eye_left->getPositionY()+m_sea_eye_right->getPositionY())/2);
        CCPoint effectP = ccp(headP.x+t_getRandom(150)-75,headP.y+t_getRandom(60)+20);
        CCSprite* bomb_effect = CCSprite::create();
        CCAnimation* animation = CCAnimation::create();
        for (int i=0; i<5; i++) {
            char _name[30];
            sprintf(_name, "block_bomb_effect_t_2_%d.png",i);
            animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(_name));
        }
        animation->setDelayPerUnit(0.08f);
        CCAnimate* animate = CCAnimate::create(animation);
        bomb_effect->runAction(CCSequence::create(animate,CCCallFuncN::create(this, callfuncN_selector(GameLogic_ui::DestroyOnCB)),NULL));
        m_special_layer->addChild(bomb_effect);
        bomb_effect->setPosition(effectP);
        
    }
}

void GameLogic_ui::SeaMouthOut(){
    if (m_sea_mouth->numberOfRunningActions()==0) {
        m_sea_mouth->runAction(CCSequence::create(CCScaleTo::create(0.15f, 1.5f),
                                                  CCScaleTo::create(0.3f, 1.0f),NULL));
    }
}

void GameLogic_ui::showSeaHurt(int hurt, int pos){
    if (G::g_game_mode!=GAMEMODE_SEA) {
        return;
    }
    m_sea_blood -= hurt;
    m_sea_blood = MAX(0,m_sea_blood);
    
    if (m_sea_blood == 0) {
        game_lose();
    }
    
    
    CCSprite* light = CCSprite::create("sea/light.png");
    m_special_layer ->addChild(light,100);
    light->setPosition(GetBlockPos(pos));
    light->runAction(CCSequence::create(CCMoveTo::create(0.5f, ccp(_pCenter.x,_pCenter.y+340)),CCCallFunc::create(this, callfunc_selector(GameLogic_ui::RotateEye)), CCCallFuncN::create(this, callfuncN_selector(GameLogic_ui::DestroyOnCB)),NULL));
    
//    CCLabelAtlas* numAtlas = CCLabelAtlas::create("","game/score_num_blue.png",26,35,'0');
//    char num[20];
//    sprintf(num,"%d",hurt);
//    numAtlas->setString(num);
//    m_score_layer->addChild(numAtlas);
//    numAtlas->setPosition(GetBlockPos(pos));
//    numAtlas->setAnchorPoint(_nCenter);
//    numAtlas->runAction(
//                        CCSequence::create(
//                                           CCMoveBy::create(0.5f,ccp(0,30)),
//                                           CCCallFuncN::create(numAtlas,callfuncN_selector(GameLogic_ui::DestroyOnCB)),
//                                           NULL
//                                           )
//                        );

}

void GameLogic_ui::showHoleScore(GEM_TYPE type, int pos){
    if (G::g_game_mode!=GAMEMODE_HOLE) {
        return;
    }
    if (type<GEM_HOLE_WALL||type>GEM_HOLE_SPECIAL_7) {
        return;
    }
    int tscore = hole_scores[type-GEM_HOLE_WALL];
    tscore *= score_rate;
    CCLabelAtlas* numAtlas = CCLabelAtlas::create("","game/score_num_blue.png",26,35,'0');
    char num[20];
    sprintf(num,"%d",tscore);
    numAtlas->setString(num);
    m_score_layer->addChild(numAtlas);
    numAtlas->setPosition(GetBlockPos(pos));
    numAtlas->setAnchorPoint(_nCenter);
    numAtlas->runAction(
                            CCSequence::create(
                                               CCMoveBy::create(0.5f,ccp(0,30)),
                                               CCCallFuncN::create(numAtlas,callfuncN_selector(GameLogic_ui::DestroyOnCB)),
                                               NULL
                                               )
    );
    m_hole_score+=tscore;
    show_score_effect(GetBlockPos(pos), G::getWorldPosition(m_hole_score_num));
}

void GameLogic_ui::show_score_effect(cocos2d::CCPoint from, cocos2d::CCPoint to){
    CCSprite* score_effect = CCSprite::create("score_effect_0.png");
    m_score_layer->addChild(score_effect);
    score_effect->setPosition(from);
    CCAnimation* animation = CCAnimation::create();
    for (int i=0; i<4; i++) {
        IntToStringFormat(_name, "score_effect_%d.png", i);
        CCRect rect = CCRectMake(0, 0, 55, 55);
        animation->addSpriteFrameWithTexture(CCTextureCache::sharedTextureCache()->addImage(_name),rect);
    }
    animation->setDelayPerUnit(0.1f);
    animation->setLoops(-1);
    CCAnimate* animate = CCAnimate::create(animation);
    score_effect->runAction(animate);
    score_effect->runAction(CCSequence::create(CCMoveTo::create(0.5f, to),CCCallFuncN::create(this, callfuncN_selector(GameLogic_ui::DestroyOnCB)),NULL));
}

void GameLogic_ui::showScore(int score, int pos){
    if(score == 0)
        return;
    score *= score_rate;
    achieve_count->score_last_light+=score;
    Score_Add(score);
    if (pos == -1) {
        return;
    }
    
    CCLabelAtlas* numAtlas = CCLabelAtlas::create("","game/score_num_blue.png",26,35,'0');
    char num[20];
    sprintf(num,"%d",score);
    numAtlas->setString(num);
    m_score_layer->addChild(numAtlas);
    
    numAtlas->setPosition(GetBlockPos(pos));
    numAtlas->setAnchorPoint(_nCenter);
    numAtlas->runAction(CCSequence::create(CCMoveBy::create(0.5f,ccp(0,30)),CCCallFuncN::create(numAtlas,callfuncN_selector(GameLogic_ui::DestroyOnCB)),NULL));
    show_score_effect(GetBlockPos(pos), G::getWorldPosition(m_score_bar));
}

void GameLogic_ui::showScore(GEM_TYPE type,GEM_COLOR color,int pos){
    if (G::g_game_mode != GAMEMODE_STAGE) {
        return;
    }
    int score = 0;
    switch (type) {
        case GEM_NORMAL:
        case GEM_TIME:
        case GEM_TIME_BOMB:
        case GEM_EGG:
        case GEM_SPECIAL:
            score = 10;
            break;
        case GEM_COIL:
            score = 15;
            break;
        case GEM_H:
        case GEM_V:
        case GEM_BEE:
            score = 100;
        case GEM_AREA:
            score = 150;
            break;
        case GEM_MAGIC:
        case GEM_MAGIC_AREA:
        case GEM_MAGIC_NORMAL:
        case GEM_MAGIC_VH:
        case GEM_2MAGIC:
        case GEM_GOLD:
            score = 200;
            break;
        case GEM_3AREA:
            score = 300;
            break;
        case GEM_3VH:
            score = 250;
            break;
        case GEM_VH:
            score = 200;
            break;
        default:
            break;
    }
    showScore(score, pos);
}

void GameLogic_ui::showHammerAnim(int pos){
    UIImageView* hammer = UIImageView::create();
    hammer->setTexture("tools/icon_2.png");
    m_ui_layer->addWidget(hammer);
    hammer->setZOrder(99);
    CCPoint p = GetBlockPos(pos);
    hammer->setPosition(ccp(p.x+50,p.y));
    hammer->setAnchorPoint(ccp(0.72f, 0.23f));
    hammer->setRotation(50);
    hammer->runAction(CCSequence::create(CCRotateBy::create(0.2f, -80),CCCallFuncN::create(this, callfuncN_selector(GameLogic_ui::DestroyOnCB)),NULL));
}

void GameLogic_ui::showMagicAnim(int pos){
    UIImageView* magic = UIImageView::create();
    magic->setTexture("tools/icon_4.png");
    m_ui_layer->addWidget(magic);
    magic->setZOrder(99);
    CCPoint p = GetBlockPos(pos);
    magic->setPosition(ccp(p.x+20,p.y-20));
    magic->setAnchorPoint(ccp(0.72f, 0.21f));
    magic->setRotation(50);
    magic->runAction(CCSequence::create(CCRotateBy::create(0.5f, -360),CCCallFuncN::create(this, callfuncN_selector(GameLogic_ui::DestroyOnCB)),NULL));
}

void GameLogic_ui::showXAnim(int pos){
    UIImageView* x = UIImageView::create();
    x->setTexture("normalgame/x.png");
    m_ui_top_layer->addWidget(x);
    x->setZOrder(1);
    CCPoint p = GetBlockPos(pos);
    x->setPosition(ccp(p.x,p.y));
    x->setOpacity(0);
    x->runAction(CCSequence::create(CCFadeIn::create(0.2f), CCDelayTime::create(0.5f),CCFadeOut::create(0.2f),CCCallFuncN::create(this, callfuncN_selector(GameLogic_ui::DestroyOnCB)),NULL));
}




void GameLogic_ui::showToolMask(int id){
    if (m_tool_mask) {
        return;
    }
    if (toolwidget[id]==NULL) {
        return;
    }
    
    CCDrawNode* Stencil = (CCDrawNode*)m_mask_clipper->getStencil();
    Stencil->clear();
    for (int i=0; i<BLOCK_NUM_WH; i++) {
        if (m_blocks[i]->getBottomType() == BLOCK_BOTTOM_SPACE||
            m_blocks[i]->getBottomType() == BLOCK_BOTTOM_GUN||
            m_blocks[i]->getBottomType() == BLOCK_BOTTOM_COIL_GUN) {
            continue;
        }
        clip(m_mask_clipper,GetBlockPos(i), BLOCK_WH);
    }

    m_tool_mask = CCLayerColor::create(ccc4(0, 0, 0, 0), _pScreenSize.width , _pScreenSize.height);
    m_mask_clipper->addChild(m_tool_mask);
    
    m_tool_mask->runAction(CCSequence::create(CCDelayTime::create(0.3f),CCFadeTo::create(0.3f, 255*7/10),NULL));
    IntToStringFormat(_titleName, "tools/tool_title_%d.png", id);
    CCSprite* title = CCSprite::create(_titleName);
    m_tool_mask->addChild(title);
    title->setPosition(ccp(_pCenter.x,_pTop-180));
    
}

void GameLogic_ui::clearToolMask(){
    if (m_tool_mask==NULL) {
        return;
    }
    m_tool_mask->runAction(CCSequence::create(CCFadeOut::create(0.3f),CCCallFuncN::create(this, callfuncN_selector(GameLogic_ui::DestroyOnCB)),NULL));
    m_tool_mask = NULL;
}

void GameLogic_ui::initCombo(){
    combo_label_sprite = CCSprite::create("game/combo_label.png");
    m_combo_layer->addChild(combo_label_sprite);
    combo_label_sprite->setPosition(ccp(_pCenter.x+(70-26)/2,_pCenter.y));
    combo_label_sprite->setAnchorPoint(_nRight);
    combo_num = CCLabelAtlas::create("1","game/score_num_green.png",26,35,'0');
    m_combo_layer->addChild(combo_num);
    combo_num->setPosition(ccp(_pCenter.x+(70-26)/2,_pCenter.y));
    combo_num->setAnchorPoint(_nLeft);
    m_combo_layer->setVisible(false);
    combo_score_num = CCLabelAtlas::create("1000","game/score_num_green.png",26,35,'0');
    m_game_parent->addChild(combo_score_num,21);
    combo_score_num->setAnchorPoint(_nCenter);
    combo_score_num->setVisible(false);
    m_combo = 0;
}

void GameLogic_ui::Combo(){
    if (game_state != GAME_STATE_PLAY && game_state != GAME_STATE_PAUSE) {
        return;
    }
    m_combo++;
    
    if(achieve_count->combo_count<m_combo)
        achieve_count->combo_count = m_combo;
    
    if (m_combo<2) {
        return;
    }
    //        switch(m_combo){
    //            case 2:
    //                SHOW_COMBO_STR(0);
    //                break;
    //            case 5:
    //                SHOW_COMBO_STR(1);
    //                break;
    //            case 8:
    //                SHOW_COMBO_STR(2);
    //                break;
    //            case 11:
    //                SHOW_COMBO_STR(3);
    //                break;
    //            case 14:
    //                SHOW_COMBO_STR(4);
    //                break;
    //        }
    
    char num[5];
    sprintf(num,"%d",m_combo-1);
    combo_num->setString(num);
    combo_label_sprite->setOpacity(255);
    combo_num->setOpacity(255);
    
    CCNode* parent = combo_num->getParent();
    parent->stopAllActions();
    parent->setScale(1);
    parent->runAction(CCSequence::create(CCShow::create(),CCScaleTo::create(0.1f,1.3f),CCScaleTo::create(0.1f,1.2f),CCDelayTime::create(0.8f),CCHide::create(),NULL));
    combo_num->stopAllActions();
    combo_num->runAction(CCSequence::create(CCDelayTime::create(0.2f),CCFadeOut::create(0.8f),NULL));
    combo_label_sprite->stopAllActions();
    combo_label_sprite->runAction(CCSequence::create(CCDelayTime::create(0.2f),CCFadeOut::create(0.8f),NULL));
    
    char combScore[10];
    int combs = (m_combo-1)*30*score_rate;
    sprintf(combScore,"%d",combs);
    combo_score_num->setString(combScore);
    Score_Add(combs);
    combo_score_num->stopAllActions();
    combo_score_num->setPosition(ccp(_pRight-160,_pTop-120));
    combo_score_num->runAction(CCSequence::create(CCShow::create(),CCMoveBy::create(0.5f,ccp(0,30)),CCHide::create(),NULL));
    combo_score_num->runAction(CCFadeOut::create(0.5f));
}

void GameLogic_ui::drawBackground(){
    switch (G::g_game_mode) {
        case GAMEMODE_STAGE:
            drawNormalBackground();
            break;
        case GAMEMODE_HOLE:
            drawHoleBackground();
            break;
        case GAMEMODE_SEA:
            drawSeaBackground();
            break;
        default:
            break;
    }
}

void GameLogic_ui::drawNormalBackground(){
    CCSprite* bg = CCSprite::create("game_bg.jpg");
    bg->setPosition(_pCenter);
    m_game_parent->addChild(bg,0);
}

void GameLogic_ui::drawHoleBackground(){
    CCNode* bg_top = CCNode::create();
    m_game_parent->addChild(bg_top,4);
    CCNode* bg = CCNode::create();
    m_game_parent->addChild(bg,0);
    
    float offsety =  (_pScreenSize.height - 960)/2;
    bg->setPosition(ccp(0, offsety));
    bg_top->setPosition(ccp(0, offsety));
    
    CCSprite* top = CCSprite::create("hole/top.jpg");
    CCSprite* middle = CCSprite::create("hole/middle.jpg");
    CCSprite* bottom = CCSprite::create("hole/bottom.png");
    CCSprite* bottom1 = CCSprite::create("hole/bottom1.png");
    bottom1->setAnchorPoint(_nTopLeft);
    bg->addChild(middle);
    bg_top->addChild(top);
    bg_top->addChild(bottom);
    bg_top->addChild(bottom1);
    top->setAnchorPoint(_nBottomLeft);
    middle->setAnchorPoint(_nBottomLeft);
    bottom->setAnchorPoint(_nBottomLeft);
    bottom1->setPosition(ccp(0, 0));
    bottom->setPosition(ccp(0,0));
    middle->setPosition(ccp(0,123));
    top->setPosition(ccp(0, 123+639));
    
    
    
    UILayer* layer = UILayer::create();
    layer->setPosition(ccp(0, offsety));
    m_game_parent->addChild(layer,10);
    m_hole_bar = UISlider::create();
    m_hole_bar->setProgressBarTexture("hole/bar_up.png");
    m_hole_bar->setBarTexture("hole/bar_down.png");
    layer->addWidget(m_hole_bar);
    m_hole_bar->setPosition(ccp(_pCenter.x,920));
    m_hole_bar->setPercent(100);
    
    m_hole_clock_img = UIImageView::create();
    m_hole_clock_img->setTexture("tools/icon_0.png");
    m_hole_bar ->addChild(m_hole_clock_img);
    m_hole_clock_img->setPosition(ccp(-200, 0));
    m_hole_clock_img->setScale(0.6f);
    
    m_hole_time_num = UILabelAtlas::create();
    m_hole_time_num->setProperty("2:00", "hole/time_num.png", 25,26, "0");
    m_hole_bar->addChild(m_hole_time_num);
    
    m_hole_score_num = UILabelAtlas::create();
    m_hole_score_num->setProperty("10000", "hole/score_num.png", 38, 41, "0");
    UIImageView* img = UIImageView::create();
    img->setTexture("hole/score_label.png");
    layer->addWidget(m_hole_score_num);
    layer->addWidget(img);
    img->setPosition(ccp(286, 845));
    m_hole_score_num->setPosition(ccp(350, 845));
    m_hole_score_num->setAnchorPoint(_nLeft);
    
    UIScrollView* container = UIScrollView::create();
    container->setSize(CCSizeMake(140, 45));
    layer->addWidget(container);
    container->setPosition(ccp(156-72-70,65-24));
    
    m_hole_num = new UILabelAtlas*[4];
    for (int i=0; i<4; i++) {
        m_hole_num[i] = UILabelAtlas::create();
        m_hole_num[i]->setProperty("0", "hole/m_num.png", 20, 28, "0");
        m_hole_num[i]->setPosition(ccp(54-i*36+70, 24));
        container->addChild(m_hole_num[i]);
    }
    //
    //        CCLOG("3333");
    //
    CCSprite* line = CCSprite::create("hole/line.png");
    line->setAnchorPoint(_nLeft);
    bg_top->addChild(line);
    line->setPosition(ccp(0, 267));
    
    
    //        float offsetY = (_pScreenSize.height-960)/2;
    //
    //        bg_top->setPosition(ccp(0, offsetY));
    //        bg->setPosition(ccp(0, offsetY));
    //        layer->setPosition(ccp(0,offsetY));
    char n_score[10];
    sprintf(n_score,"%d",m_hole_score);
    m_hole_score_num->setStringValue(n_score);
    
}

void GameLogic_ui::drawSeaBackground(){
    CCSprite* bg = CCSprite::create("sea_bg.jpg");
    bg->setPosition(_pCenter);
    m_game_parent->addChild(bg,0);
    
    m_sea_eye_left = CCSprite::create("sea/eye.png");
    m_game_parent->addChild(m_sea_eye_left,1);
    m_sea_eye_left->setPosition(ccp(300,_pCenter.y + 345));
    m_sea_eye_right = CCSprite::create("sea/eye.png");
    m_game_parent->addChild(m_sea_eye_right,1);
    m_sea_eye_right->setPosition(ccp(387,_pCenter.y + 353));
    m_sea_mouth = CCSprite::create("sea/mouth.png");
    m_game_parent->addChild(m_sea_mouth,1);
    m_sea_mouth->setPosition(ccp(347, _pCenter.y+320));
//    m_sea_mouth->runAction(CCRepeatForever::create(CCSequence::create(CCHide::create(),CCDelayTime::create(0.2f),CCShow::create(),CCDelayTime::create(0.2f),NULL)));
    
    UILayer* layer = UILayer::create();
    m_game_parent->addChild(layer,10);
    m_sea_bar = UISlider::create();
    m_sea_bar->setProgressBarTexture("sea/game_bar_up.png");
    m_sea_bar->setBarTexture("sea/game_bar_down.png");
    layer->addWidget(m_sea_bar);
    m_sea_bar->setPosition(ccp(_pCenter.x,_pTop-70));
    m_sea_bar->setPercent(100);
    
    m_sea_heart_img = UIImageView::create();
    m_sea_heart_img->setTexture("sea/game_bar_icon.png");
    m_sea_bar ->addChild(m_sea_heart_img);
    m_sea_heart_img->setPosition(ccp(-200, 0));
}

void GameLogic_ui::updateHoleRise()
{
    if (G::g_game_mode!=GAMEMODE_HOLE) {
        return;
    }
    
    if (HWindowsManager::S()->hasWindowsShowed()) {
        return;
    }

    for (int i=0; i< BLOCK_NUM_WH-BLOCK_NUM_W*2; i++) {
        if (m_gems[i]->IsHoleWall()) {
            return;
        }
    }
    
    if (!hasHelp()) {
        return;
    }
    
    clearHelp();

    HoleRise();
    m_lose_conditions_now[LOSE_CONDITION_TIME] += maxRerwardTime - m_hole_level;
    m_hole_clock_img->runAction(CCSequence::create(CCScaleTo::create(0.3f, 1),CCScaleTo::create(0.3f, 0.6f),NULL));
    m_hole_level++;
}

void GameLogic_ui::HoleRise(){
    for (int i=BLOCK_NUM_W; i<BLOCK_NUM_W*3; i++) {
        CCPoint pre_pos = GetBlockPos(i);
        m_gems[i]->MoveToAndClear(0.4f, ccp(pre_pos.x,pre_pos.y+BLOCK_WH*2));
    }
    for (int i=BLOCK_NUM_W*3; i<BLOCK_NUM_WH; i++) {
        if (m_gems[i]->isEmpty()) {
            continue;
        }
        m_gems[i]->toGemObject(m_gems[i-BLOCK_NUM_W*2]);
        m_gems[i-BLOCK_NUM_W*2]->MoveWithNoCheck(0.4f);
    }
    bool create_special = false;
    for (int i=BLOCK_NUM_WH-BLOCK_NUM_W*2; i<BLOCK_NUM_WH; i++) {
        int id = GEM_HOLE_WALL;
        int percent = t_getRandom(100);
        
        int need =0;
        
        int num = create_special? 5:4;
        
        int tmpLevel;
        tmpLevel = MIN(m_hole_level, maxHoleLevel);
        
        for (int i=0; i<num; i++) {
            need+= hole_wall_rates[tmpLevel/2][i];
            if (percent<need) {
                id =  GEM_HOLE_NORMAL + i;
                break;
            }
        }
        
        if (id >= GEM_HOLE_SPECIAL_1) {
            create_special = true;
        }
        
        m_gems[i]->newGem(id*10+GEM_COLOR_NOCOLOR);
        CCPoint pre_pos = GetBlockPos(i);
        m_gems[i]->replaceGem(ccp(pre_pos.x,pre_pos.y-BLOCK_WH*2));
        m_gems[i]->MoveWithNoCheck(0.4f);
    }
}
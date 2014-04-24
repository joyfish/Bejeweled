//
//  GameLogic_guide.cpp
//  Bejeweled
//
//  Created by wilford on 14-3-9.
//
//

#include "GameLogic_guide.h"
#include "HoleModeShow.h"


void GameLogic_guide::showGameReady(GAMEMODE_TYPE mode){
    if (m_showGameReady_listener&&m_showGameReady_selector) {
        (m_showGameReady_listener->*m_showGameReady_selector)(mode);
    }
}

void GameLogic_guide::updateGameStart(){
    if (game_state != GAME_STATE_PLAY) {
        return;
    }
    if (m_gameStart_showed) {
        return;
    }
    if (!isInCustomTime()) {
        return;
    }
    switch (G::g_game_mode) {
        case GAMEMODE_STAGE:
            GameStart::show(m_layer);
            break;
        case GAMEMODE_HOLE:
             //HoleModeShow::show(m_ui_layer);
            break;
        case GAMEMODE_SEA:
            break;
        default:
            break;
    }
   
    m_gameStart_showed = true;
}

void GameLogic_guide::updateGameReady(){
//    if (game_state != GAME_STATE_PLAY) {
//        return;
//    }
    if (m_gameReady_showed) {
        return;
    }
    if (!isInCustomTime()) {
        return;
    }
    if (m_lose_conditions[LOSE_CONDITION_TIME]>0) {
        showGameReady(MODE_TIME);
    }else{
        showGameReady(MODE_STEP);
    }
    m_gameReady_showed = true;
}

void GameLogic_guide::updateGuide(float dt){
    if (G::g_game_mode!= GAMEMODE_STAGE) {
        return;
    }
    updateMaskOpacity(dt);
    
    if (game_state == GAME_STATE_END) {
        return;
    }
    if (!isInCustomTime()) {
        return;
    }
    unsigned int next_step = m_guide_step+1;
    if (next_step>=G::g_help_infos[G::g_game_stage].size()) {
        return;
    }
    if (isInGuide) {
        return;
    }
    CCLOG("game_state %d",game_state);
    nextGuide();
}

void GameLogic_guide::nextGuide(){
    m_guide_step++;
    unsigned int step = m_guide_step;
    if (step>=G::g_help_infos[G::g_game_stage].size()) {
        return;
    }
    HELP_INFO* help_info = G::g_help_infos[G::g_game_stage][m_guide_step];
    if (G::g_help_infos[G::g_game_stage][m_guide_step]->isShowed) {
        return;
    }
    G::g_help_infos[G::g_game_stage][m_guide_step]->isShowed = true;
        HPersistence::S()->SaveToFile();
    helpMask = CCUIHELPER->createWidgetFromJsonFile("HELP_MASK.json");
    helpMask->setZOrder(10);
    m_ui_layer->addWidget(helpMask);
    UIPanel* top = (UIPanel*)helpMask->getChildByName("TOP");
    mask_panel[0] = top;
    UIPanel* bottom =  (UIPanel*)helpMask->getChildByName("BOTTOM");
    mask_panel[1] = bottom;
    UIPanel* left =  (UIPanel*)helpMask->getChildByName("LEFT");
    mask_panel[2] = left;
    UIPanel* right =  (UIPanel*)helpMask->getChildByName("RIGHT");
    mask_panel[3] = right;
    
    CCPoint pos = GetBlockPos(help_info->target_block_id);
    CCRect rect = CCRectMake(0,0,0,0);
    pos.x-=BLOCK_WH/2;
    pos.y -= BLOCK_WH/2;
    char actionName[30];
    m_guide_from_block_id = help_info->target_block_id;
    m_guide_to_block_id = 0;
    UIWidget* arrow_container = helpMask->getChildByName("ARROW_CONTAINER");
    if (m_guide_from_block_id>0) {
        switch(help_info->dir){
            case 1:
                //rect = CCRectMake(pos.x,pos.y,BLOCK_WH,BLOCK_WH*2);
                sprintf(actionName,"UP_MOVE");
                m_guide_to_block_id = m_guide_from_block_id-BLOCK_NUM_W;
                break;
            case 2:
                //rect = CCRectMake(pos.x,pos.y-BLOCK_WH,BLOCK_WH,BLOCK_WH*2);
                sprintf(actionName,"DOWN_MOVE");
                m_guide_to_block_id = m_guide_from_block_id+BLOCK_NUM_W;
                break;
            case 3:
                //rect = CCRectMake(pos.x-BLOCK_WH,pos.y,BLOCK_WH*2,BLOCK_WH);
                sprintf(actionName,"LEFT_MOVE");
                m_guide_to_block_id = m_guide_from_block_id-1;
                break;
            case 4:
                //rect = CCRectMake(pos.x,pos.y,BLOCK_WH*2,BLOCK_WH);
                sprintf(actionName,"RIGHT_MOVE");
                m_guide_to_block_id = m_guide_from_block_id+1;
                break;
        }
        
        CCPoint arrow_pos = GetBlockPos(help_info->target_block_id);
        arrow_pos.x -=10;
        arrow_pos.y +=25;
        arrow_container->setPosition(arrow_pos);
        
        if ( help_info->dir > 0) {
            ActionObject* move_action = ActionManager::shareManager()->getActionByName("HELP_MASK.json",actionName);
            move_action->setLoop(true);
            move_action->play();
        }
    }else{
        arrow_container->setVisible(false);
    }
    
    mask_img = NULL;
    
    if (help_info->mask_id>0) {
        mask_img = COCO_UIIMAGEVIEW::create();
        mask_img->setTouchEnable(true);
        IntToStringFormat(_maskName, "ccs/help/help_mask_%d.png", help_info->mask_id);
        mask_img->setTexture(_maskName);
        CCPoint mask_pos = CCPointZero;
        switch (help_info->mask_id) {
            case 9://步数
            {
                CCPoint _pos = G::getWorldPosition(time_or_step_bg);
                mask_pos = ccp(_pos.x+30,_pos.y+20);
            }
                
            case 15://过关条件
                for (int i=0; i<WIN_CONDITION_MAX; i++) {
                    if(m_win_condition_icons[i]){
                        CCPoint _pos = G::getWorldPosition(m_win_condition_icons[i]);
                        mask_pos = ccp(_pos.x+35,_pos.y);
                        break;
                    }
                }
                break;
            case 16://步数
            {
                CCPoint _pos = G::getWorldPosition(time_or_step_bg);
                mask_pos = ccp(_pos.x,_pos.y);
            }
                break;
            case 17:
                mask_pos =G::getWorldPosition(toolwidget[TOOL_TYPE_HAMMER]);
                mask_img->setTouchEnable(false);
                break;
            case 18:
                mask_pos =G::getWorldPosition(toolwidget[TOOL_TYPE_REFRESH]);
                mask_img->setTouchEnable(false);
                break;
            case 19:
                mask_pos =G::getWorldPosition(toolwidget[TOOL_TYPE_SPECIAL]);
                mask_img->setTouchEnable(false);
                break;
            default:
                mask_pos = GetBlockPos(help_info->mask_pos_id);
                break;
        }

        if (help_info->mask_id == 9||
            help_info->mask_id == 15||
            help_info->mask_id == 16) {
            arrow_container->setVisible(true);
            arrow_container->setPosition(ccp(mask_pos.x+20, mask_pos.y-30));
//            UIWidget* u = arrow_container->getChildByName("HELP_ARROW");
//            u->setAnchorPoint(_nCenter);
            arrow_container->runAction(CCRepeatForever::create(CCSequence::create(CCMoveTo::create(0.6f, ccp(mask_pos.x-30,mask_pos.y-30)),CCMoveTo::create(0.6f, ccp(mask_pos.x+30,mask_pos.y-30)), NULL)));
        }
        
        
        helpMask->addChild(mask_img);
        mask_img->setPosition(mask_pos);
        CCSize mask_size =mask_img->getSize();
        rect = CCRectMake(mask_pos.x- mask_size.width/2, mask_pos.y-mask_size.height/2, mask_size.width, mask_size.height);
    }
    
    CCSize screenSize = _pScreenSize;
    top->setPosition(ccp(0,rect.getMaxY()));
    top->setSize(CCSizeMake(screenSize.width,screenSize.height-rect.getMaxY()));
    bottom->setPosition(ccp(0,0));
    bottom->setSize(CCSizeMake(screenSize.width,rect.getMinY()));
    left->setPosition(ccp(0,rect.getMinY()));
    left->setSize(CCSizeMake(rect.getMinX(),rect.getMaxY()-rect.getMinY()));
    right->setPosition(ccp(rect.getMaxX(),rect.getMinY()));
    right->setSize(CCSizeMake(screenSize.width-rect.getMaxX(),rect.getMaxY()-rect.getMinY()));
    
    
    
    if(help_info->tips_id>=0&&help_info->tips_id<999){
        GameHelpMaskTips* helpMaskTips = GameHelpMaskTips::show(m_ui_layer,new GameHelpParam(help_info->tips_id,help_info->tips_in_type));
        helpMaskTips->addGameHelpMaskClosedEvent(this, h_voidcallback(GameLogic_guide::closeGuide));
    }
    
    updateMaskOpacity(0);
    //helpMask->runAction(CCFadeIn::create(10.0f));
    FadeInMask();
    isInGuide = true;
}

void GameLogic_guide::FadeInMask(){
    for (int i=0; i<4; i++) {
        if (mask_panel[i]) {
            mask_panel[i]->setBackGroundColorOpacity(0);
            //mask_panel[i]->runAction(CCFadeIn::create(1.0f));
        }
    }
    m_current_mask_opacity = 0;
    m_mask_fade_state = 1;
    if (mask_img) {
        mask_img->setOpacity(0);
        mask_img->runAction(CCFadeIn::create(0.3f));
    }
}

void GameLogic_guide::FadeOutMask(){
    //        for (int i=0; i<4; i++) {
    //            if (mask_panel[i]) {
    //                m_mask_fade_state = 2;
    //                //mask_panel[i]->runAction(CCFadeOut::create(1.0f));
    //            }
    //        }
    m_mask_fade_state = 2;
    if (mask_img) {
        mask_img->runAction(CCFadeOut::create(0.3f));
    }
}

void GameLogic_guide::updateMaskOpacity(float dt){
    
    if (m_mask_fade_state == 1) {
        if (m_max_mask_opacity>m_current_mask_opacity) {
            m_current_mask_opacity += m_max_mask_opacity*dt*10/3;
            m_current_mask_opacity = MIN(m_current_mask_opacity, m_max_mask_opacity);
            for (int i=0; i<4; i++) {
                if (mask_panel[i]) {
                    mask_panel[i]->setBackGroundColorOpacity(m_current_mask_opacity);
                }
            }
        }else{
            m_mask_fade_state = 0;
        }
        
        
    }else if(m_mask_fade_state == 2) {
        if (m_current_mask_opacity>0) {
            m_current_mask_opacity -= m_max_mask_opacity*dt*10/3;
            m_current_mask_opacity = MAX(m_current_mask_opacity, 0);
            for (int i=0; i<4; i++) {
                if (mask_panel[i]) {
                    mask_panel[i]->setBackGroundColorOpacity(m_current_mask_opacity);
                }
            }
        }else{
            if (helpMask) {
                helpMask->removeFromParent();
                helpMask = NULL;
            }
            m_mask_fade_state = 0;
        }
    }
}

void GameLogic_guide::closeGuide(){
    //        if (helpMask) {
    //            helpMask->removeFromParent();
    //        }
    
    FadeOutMask();
    if (GameHelpMaskTips::S()) {
        GameHelpMaskTips::S()->m_close();
    }
    
    isInGuide = false;
}
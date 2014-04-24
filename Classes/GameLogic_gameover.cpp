//
//  GameLogic_gameover.cpp
//  Test
//
//  Created by wilford on 14-3-7.
//
//

#include "GameLogic_gameover.h"
#include "GameEndBuy.h"


void GameLogic_gameover::GameWin(int score){
    if (m_game_win_listener&&m_game_win_selector) {
        (m_game_win_listener->*m_game_win_selector)(score);
    }
    checkAchievement();
}

void GameLogic_gameover::GameLose(){
    if(m_game_lose_selector&&m_game_lose_listener){
        (m_game_lose_listener->*m_game_lose_selector)();
    }
}

void GameLogic_gameover::HoleResult(int hole_score, int hole_m){
    if(m_hole_result_listener&&m_hole_result_selector){
        (m_hole_result_listener->*m_hole_result_selector)(hole_score,hole_m);
    }
}

void GameLogic_gameover::SeaResult(int hurt, int max_blood){
    if (m_sea_result_listener&&m_sea_result_selector) {
        (m_sea_result_listener->*m_sea_result_selector)(hurt,max_blood);
    }
}


bool GameLogic_gameover::ClearAllSpecialBomb(){
    
    bool hasSpecial = false;
    int delayTime = 0.5f;
    for (int i=0; i<BLOCK_NUM_WH; i++) {
        if (m_gems[i]->getType() == GEM_H||
            m_gems[i]->getType() == GEM_V||
            m_gems[i]->getType() == GEM_AREA||
            m_gems[i]->getType() == GEM_MAGIC) {
            Bomb(i,delayTime);
            delayTime +=0.5f;
            hasSpecial = true;
        }
    }
    return hasSpecial;
}

void GameLogic_gameover::BonusTimeEffect(){
    CCSprite* bonusTime_0 = CCSprite::create("game/bonusTime_0.png");
    CCSprite* bonusTime_1 = CCSprite::create("game/bonusTime_1.png");
    CCSprite* bonusTime_bg = CCSprite::create("game/bonusTime_bg.png");
    m_score_layer->addChild(bonusTime_bg);
    m_score_layer->addChild(bonusTime_0);
    m_score_layer->addChild(bonusTime_1);
    
    bonusTime_bg->setPosition(_pCenter);
    bonusTime_0->setPosition(_pCenter);
    bonusTime_1->setPosition(_pCenter);
    
    
    bonusTime_0->setScale(1.5f);
    bonusTime_0->runAction(CCSequence::create(CCScaleTo::create(0.1f,1),CCCallFuncN::create(this,callfuncN_selector(GameLogic_gameover::DestroyOnCB)),NULL));
    bonusTime_1->runAction(CCSequence::create(CCHide::create(),CCDelayTime::create(0.1f),CCShow::create(),CCDelayTime::create(1),CCCallFuncN::create(this,callfuncN_selector(GameLogic_gameover::DestroyOnCB)),NULL));
    bonusTime_bg->runAction(CCSequence::create(CCHide::create(),CCDelayTime::create(0.1f),CCShow::create(),CCDelayTime::create(1),CCCallFuncN::create(bonusTime_0,callfuncN_selector(GameLogic_gameover::DestroyOnCB)),NULL));
    bonusTime_bg->runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(CCScaleTo::create(0.1f,1,2),CCScaleTo::create(0.1f,2,2),NULL)));
    
}

bool GameLogic_gameover::CostAllStep(){
    int PosS[BLOCK_NUM_WH];
    //int ids[BLOCK_NUM_WH];
    int len = 0;
    int count = m_lose_conditions_now[LOSE_CONDITION_STEP];
    for (int i=0; i<BLOCK_NUM_WH; i++) {
        if (!m_blocks[i]->canMoveIn()) {
            continue;
        }
        if (m_gems[i]->isEmpty()) {
            continue;
        }
        
        if (!m_blocks[i]->isMatchColor()) {
            continue;
        }
        
        if (m_gems[i]->getType()!= GEM_NORMAL) {
            continue;
        }
        
        PosS[len]=i;
        //ids[len] = len;
        len++;
    }
    
    count = MIN(len, count);
    float delay = 0;
    CCPoint fromPos = ccp(_pLeft+82,_pTop-72);
    for (int i=0; i<count; i++) {
        int id = t_getRandom(len);
        int pos = PosS[id];
        CCSprite* trail = CCSprite::create("game/bonusTime_trail.png");
        m_score_layer->addChild(trail);
        trail->setAnchorPoint(_nRight);
        trail->setVisible(false);
        float offset_delay = FlyNodeTo(trail, fromPos, GetBlockPos(pos), 0.1f,true,delay);
        
        if (t_getRandom(2)) {
            createGem(pos, GEM_H*10+m_gems[pos]->getColor(),offset_delay,count*0.5f+0.5f);
        }else{
            createGem(pos, GEM_V*10+m_gems[pos]->getColor(),offset_delay,count*0.5f+0.5f);
        }
        
        
        delay += 0.5f;
        PosS[id] = PosS[len-1];
        len--;
    }
    
    if (count>0) {
        BonusTimeEffect();
        for (int i=0;i<count;i++) {
            m_delay_cost_step.push_back(0.5f*i+0.5f);
        }
        return true;
    }else{
        return false;
    }
}

void GameLogic_gameover::updateDelayCostStep(float dt){
    vector<float>::iterator it = m_delay_cost_step.begin();
    while (it!=m_delay_cost_step.end()) {
        *it-=dt;
        *it = MAX(0,*it);
        if (*it == 0) {
            G::G_playEffect(RES_MUSIC_OVERLIGHT);
            m_lose_conditions_now[LOSE_CONDITION_STEP]--;
            m_lose_conditions_now[LOSE_CONDITION_STEP] = MAX(0,m_lose_conditions_now[LOSE_CONDITION_STEP]);
            it = m_delay_cost_step.erase(it);
            showScore(1000);
        }else
            it++;
    }
}

void GameLogic_gameover::showGameWinAnim(){
    m_win_anim_showed = true;
    for (int i=0; i<BLOCK_NUM_WH; i++) {
        if (!m_blocks[i]->isMatchColor()) {
            continue;
        }
        if (m_gems[i]->isEmpty()) {
            continue;
        }
        m_gems[i]->showGameWinAnim(0.4f+0.1f*(i%BLOCK_NUM_W));
    }
}

void GameLogic_gameover::showGameEndBuy(){
    if (m_game_end_buy_listener&&m_game_end_buy_selector) {
        (m_game_lose_listener->*m_game_end_buy_selector)(this,h_voidcallback(GameLogic_gameover::onGameEndLose), h_voidcallback(GameLogic_gameover::onGameEndContiue));
    }
//    GameEndBuy* game_end_buy = GameEndBuy::show(m_ui_layer);
//    game_end_buy->addLoseListener(this, h_voidcallback(GameLogic_gameover::onGameEndLose));
//    game_end_buy->addContinueListener(this, h_voidcallback(GameLogic_gameover::onGameEndContiue));
}

void GameLogic_gameover::onGameEndContiue(){
    if (m_lose_conditions[LOSE_CONDITION_TIME]>0) {
        m_lose_conditions_now[LOSE_CONDITION_TIME]+=10;
    }else{
        m_lose_conditions_now[LOSE_CONDITION_STEP]+=5;
    }
    game_state = GAME_STATE_PLAY;
}

void GameLogic_gameover::onGameEndLose(){
    showLoseResult();
}

void GameLogic_gameover::updateGameOver(){
    switch (game_state) {
        case GAME_STATE_WIN:
            if (isInCustomTime()) {
                if (ClearAllSpecialBomb()) {
                    break;
                }
                if (CostAllStep()) {
                    break;
                }
                
                if (!m_win_anim_showed) {
                    showGameWinAnim();
                    break;
                }
                
                game_state = GAME_STATE_END;
                GameWin(m_score_current);
                CCLOG("game_end");
            }
            break;
        case GAME_STATE_LOSE:
            if (isInCustomTime()) {
                if ((m_lose_conditions[LOSE_CONDITION_TIME]>0&&m_lose_conditions_now[LOSE_CONDITION_TIME]==0)||
                    (m_lose_conditions[LOSE_CONDITION_STEP]>0&&m_lose_conditions_now[LOSE_CONDITION_STEP]==0)) {
                    showGameEndBuy();
                    return;
                }
                showLoseResult();
                CCLOG("game_end");
            }
            break;
        default:
            break;
    }
}

void GameLogic_gameover::showLoseResult(){
    game_state = GAME_STATE_END;
    switch (G::g_game_mode) {
        case GAMEMODE_STAGE:
            GameLose();
            break;
        case GAMEMODE_HOLE:
            HoleResult(m_hole_score, m_hole_m);
            break;
        case GAMEMODE_SEA:
            if (m_lose_conditions[LOSE_CONDITION_TIME] - m_lose_conditions_now[LOSE_CONDITION_TIME]<=60) {
                G::G_Add_Achievement_Complete(34);
            }
            SeaResult(m_sea_max_blood - m_sea_blood, m_sea_max_blood);
            break;
            
        default:
            break;
    }
    checkAchievement();
}
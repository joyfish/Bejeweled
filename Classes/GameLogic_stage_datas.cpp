//
//  GameLogic_stage_datas.cpp
//  Test
//
//  Created by wilford on 14-3-6.
//
//

#include "GameLogic_stage_datas.h"


void GameLogic_stage_datas::showNormalTips(int tips_id){
    if (m_showNormalTips_listener&&m_showNormalTips_selector) {
        (m_showNormalTips_listener->*m_showNormalTips_selector)(tips_id);
    }
}


void GameLogic_stage_datas::Score_Add(int score){
    m_score_current+=score;
//    if (m_score_current>m_score_max) {
//        m_score_current = m_score_max;
//    }
    Win_Condition_Add(WIN_CONDITION_SCORE,score);
    
}

void GameLogic_stage_datas::showWinConditionAnim(int id){}

void GameLogic_stage_datas::Win_Condition_Add(int condition_id,int num){
    if(condition_id<0||condition_id>=WIN_CONDITION_MAX){
        return;
    }
    if (m_win_conditions_now[condition_id]<m_win_conditions[condition_id]) {
        m_win_conditions_now[condition_id]+=num;
        m_win_conditions_now[condition_id] = MIN(m_win_conditions[condition_id], m_win_conditions_now[condition_id]);
        showWinConditionAnim(condition_id);
    }
    //		for(int i=0;i<WIN_CONDITION_MAX;i++){
    //            if(m_win_conditions_now[i]>m_win_conditions[i])
    //                m_win_conditions_now[i] = m_win_conditions[i];
    //		}
    
    if (Win_Condition_Finished()) {
        game_win();
    }
}

bool GameLogic_stage_datas::Win_Condition_Finished(){
    bool isAllZero = true;
    for(int i=0;i< WIN_CONDITION_MAX ;i++){
        if(m_win_conditions[i]!=0)
            isAllZero = false;
    }
    if(isAllZero)
        return false;
    
    for(int i=0;i<WIN_CONDITION_MAX;i++){
        if(m_win_conditions_now[i]<m_win_conditions[i])
            return false;
    }
    return true;
}

void GameLogic_stage_datas::Lose_Condition_Add(LOSE_CONDITION condition_id,float num){
    if(condition_id<0||condition_id>=LOSE_CONDITION_MAX)
        return;
    
    //float pre =m_lose_conditions_now[condition_id];
    if (m_lose_conditions_now[condition_id]>0) {
        m_lose_conditions_now[condition_id]-=num;
        m_lose_conditions_now[condition_id] = MAX(0,m_lose_conditions_now[condition_id]);
    }
    
    
    
    if (Lose_Condition_Finished()) {
        game_lose();
    }
    
}

bool GameLogic_stage_datas::Lose_Condition_Finished(){
    for(int i=0;i<LOSE_CONDITION_MAX;i++){
        if(m_lose_conditions[i]>0){
            if(m_lose_conditions_now[i]<=0)
                return true;
        }
    }
    return false;
}

void GameLogic_stage_datas::game_win(){
    if (game_state != GAME_STATE_WIN && game_state != GAME_STATE_END) {
        achieve_count->score_last_light=0;
        game_state = GAME_STATE_WIN;
        CCLOG("game_win");
        
    }
}

void GameLogic_stage_datas::game_lose(){
    if (game_state == GAME_STATE_PLAY||game_state == GAME_STATE_PAUSE) {
        achieve_count->score_last_light=0;
        game_state = GAME_STATE_LOSE;
        CCLOG("game_lose");
    }
}

void GameLogic_stage_datas::checkAchievement(){
     CCLOG("checkAchievement");
    G::G_Set_SingleRound_Achievement_Complete(0, achieve_count->bomb_count_single_move);
    G::G_Set_SingleRound_Achievement_Complete(1, achieve_count->score_last_light);
    G::G_Set_SingleRound_Achievement_Complete(2, achieve_count->combo_count);
    G::G_Set_SingleRound_Achievement_Complete(3, achieve_count->exchange_count);
    G::G_Set_SingleRound_Achievement_Complete(4, achieve_count->combine_count);
    G::G_Set_SingleRound_Achievement_Complete(5, achieve_count->create_magic_count);
    G::G_Set_SingleRound_Achievement_Complete(15, achieve_count->special_bomb_count_single_move );
    G::G_Set_SingleRound_Achievement_Complete(18, achieve_count->use_reposion_bomb_count);
    G::G_Set_SingleRound_Achievement_Complete(20, achieve_count->use_star_count);
    G::G_Set_SingleRound_Achievement_Complete(27, achieve_count->hole_gold_count);
    G::G_Set_SingleRound_Achievement_Complete(26, m_hole_score);
    G::G_Set_SingleRound_Achievement_Complete(29, m_hole_m);
    G::G_Set_SingleRound_Achievement_Complete(32, achieve_count->sea_wall_count);
    G::G_Set_SingleRound_Achievement_Complete(36, achieve_count->sea_vircus_count);
    
    if (m_score_current>=15000) {
        G::G_Add_Achievement_Complete(6);
    }else{
        G::G_Add_Achievement_Complete(6, 0);
    }
    if(m_score_current>=30000){
        G::G_Add_Achievement_Complete(7);
    }
    G::G_Set_Achievement_Complete(13,G::G_getTotalStar());
    
    HPersistence::S()->SaveToFile();
}
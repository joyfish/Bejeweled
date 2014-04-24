//
//  GameLogic_gameover.h
//  Test
//
//  Created by wilford on 14-3-7.
//
//

#ifndef __Test__GameLogic_gameover__
#define __Test__GameLogic_gameover__

#include "GameLogic_ui.h"

typedef void (CCObject::*SEL_GAME_WIN)(int score);
#define h_game_win(_SELECTOR) (SEL_GAME_WIN)(&_SELECTOR)
typedef void (CCObject::*SEL_GAME_LOSE)();
#define h_game_lose(_SELECTOR) (SEL_GAME_LOSE)(&_SELECTOR)
typedef void (CCObject::*SEL_HOLE_RESULT)(int score,int m);
#define h_hole_result(_SELECTOR) (SEL_HOLE_RESULT)(&_SELECTOR)
typedef void (CCObject::*SEL_SEA_RESULT)(int hurt,int max_blood);
#define h_sea_result(_SELECTOR) (SEL_HOLE_RESULT)(&_SELECTOR)
typedef void (CCObject::*SEL_GAME_END_BUY)(CCObject* target,SEL_VOIDCALLBACK gameEndSelector,SEL_VOIDCALLBACK gameContinueSelector);
#define h_game_end_buy(_SELECTOR) (SEL_GAME_END_BUY)(&_SELECTOR)

class GameLogic_gameover: public GameLogic_ui{
   
public:
    void addGameWinEvent(CCObject* target,SEL_GAME_WIN selector){
        this->m_game_win_listener = target;
        this->m_game_win_selector = selector;
    }
    
    void addGameLoseEvent(CCObject* target,SEL_GAME_LOSE selector){
        this->m_game_lose_listener = target;
        this->m_game_lose_selector = selector;
    }
    
    void addHoleResultEvent(CCObject* target,SEL_HOLE_RESULT selector){
        this->m_hole_result_listener = target;
        this->m_hole_result_selector = selector;
    }
    
    void addSeaResultEvent(CCObject* target,SEL_SEA_RESULT selector){
        this->m_sea_result_listener = target;
        this->m_sea_result_selector = selector;
    }
    
    void addGameEndBuyEvent(CCObject* target,SEL_GAME_END_BUY selector){
        this->m_game_end_buy_listener = target;
        this->m_game_end_buy_selector = selector;
    }
    
protected:
    GameLogic_gameover()
    :m_win_anim_showed(false)
    ,m_game_lose_listener(NULL)
    ,m_game_lose_selector(NULL)
    ,m_game_win_listener(NULL)
    ,m_game_win_selector(NULL)
    ,m_hole_result_listener(NULL)
    ,m_hole_result_selector(NULL)
    ,m_sea_result_listener(NULL)
    ,m_sea_result_selector(NULL)
    ,m_game_end_buy_selector(NULL)
    ,m_game_end_buy_listener(NULL)
    {
    
    }
    
    
    void GameWin(int score);
    
    void GameLose();
    
    void HoleResult(int hole_score,int hole_m);
    
    void SeaResult(int hurt,int max_blood);
    
    bool ClearAllSpecialBomb();
    
    void BonusTimeEffect();
    
    bool CostAllStep();
    
    void updateDelayCostStep(float dt);
    
    void showGameWinAnim();
    
    void updateGameOver();
    
    void showGameEndBuy();
    
    void onGameEndLose();
    void onGameEndContiue();
    
    void showLoseResult();
    
    
    
    CCObject* m_game_win_listener;
    SEL_GAME_WIN m_game_win_selector;
    CCObject* m_game_lose_listener;
    SEL_GAME_LOSE m_game_lose_selector;
    CCObject* m_hole_result_listener;
    SEL_HOLE_RESULT m_hole_result_selector;
    CCObject* m_sea_result_listener;
    SEL_SEA_RESULT m_sea_result_selector;
    CCObject* m_game_end_buy_listener;
    SEL_GAME_END_BUY m_game_end_buy_selector;
    bool m_win_anim_showed;
    vector<float> m_delay_cost_step;
};

#endif /* defined(__Test__GameLogic_gameover__) */

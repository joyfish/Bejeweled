//
//  GameLogic_stage_datas.h
//  Test
//
//  Created by wilford on 14-3-6.
//
//

#ifndef __Test__GameLogic_stage_datas__
#define __Test__GameLogic_stage_datas__

#include "cocos2d.h"
#include "HDefine.h"
#include "HPersistence.h"

USING_NS_CC;

typedef void (CCObject::*SEL_SHOWNORMALTIPS)(int id);
#define h_showNormalTips(_SELECTOR) (SEL_SHOWNORMALTIPS)(&_SELECTOR)

class GameLogic_stage_datas:public CCObject{
    
public:
    bool isInGuide;
    GAME_STATE getGameState(){
        return game_state;
    }
    
    void setGameState(GAME_STATE state){
        game_state  = state;
    }
    
    void addShowNormalTipsEvent(CCObject* target,SEL_SHOWNORMALTIPS selector){
        this->m_showNormalTips_listener = target;
        this->m_showNormalTips_selector = selector;
    }
    
protected:
    GameLogic_stage_datas()
    :m_score_current(0)
    ,score_rate(1.0f)
    ,game_state(GAME_STATE_PLAY)
    ,m_tool_selected(-1)
    ,m_showNormalTips_listener(NULL)
    ,m_showNormalTips_selector(NULL)
    ,m_guide_step(-1)
    ,isInGuide(false)
    ,m_hole_score(0)
    ,m_hole_maxTime(120)
    ,m_hole_time(120)
    ,m_hole_m(0)
    ,m_step_caculate(0)
    ,m_time_caculate(0)
    ,m_hole_level(0)
    ,m_sea_blood(_SEA_MAX_BLOOD)
    ,m_sea_max_blood(_SEA_MAX_BLOOD)
    ,achieve_count(NULL)
    {
    }
    
    ~GameLogic_stage_datas(){
        CC_SAFE_DELETE(achieve_count);
    }
    
    void showNormalTips(int tips_id);

    
    void Score_Add(int score);
    
    virtual void showWinConditionAnim(int id);
    
    void Win_Condition_Add(int condition_id,int num = 1);
    
	bool Win_Condition_Finished();
    
	void Lose_Condition_Add(LOSE_CONDITION condition_id,float num = 1);
    
	bool Lose_Condition_Finished();
    
    void game_win();
    
    void game_lose();
    
    void checkAchievement();
    
    int m_win_conditions[WIN_CONDITION_MAX];
    float m_lose_conditions[LOSE_CONDITION_MAX];
    int m_win_conditions_now[WIN_CONDITION_MAX];
    float m_lose_conditions_now[LOSE_CONDITION_MAX];
    int m_score_max;
    int m_score_3star;
    int m_score_2star;
    int m_score_current;
    float score_rate;
    GAME_STATE game_state;
    int m_tool_selected;
    
    
    int m_guide_step;
    int m_guide_from_block_id;
    int m_guide_to_block_id;
    
    int m_hole_score;
    float m_hole_time;
    int m_hole_level;
    int m_hole_maxTime;
    int m_hole_m;
    
    int m_sea_blood;
    int m_sea_max_blood;
    
    int m_step_caculate;
    float m_time_caculate;
    
    CCObject* m_showNormalTips_listener;
    SEL_SHOWNORMALTIPS m_showNormalTips_selector;
    
    vector<int> bao_ids;//有可能掉落的宝藏元素
    
    ACHIEVE_COUNT* achieve_count;
};

#endif /* defined(__Test__GameLogic_stage_datas__) */

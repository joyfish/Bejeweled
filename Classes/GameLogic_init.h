//
//  GameLogic_init.h
//  Test
//
//  Created by wilford on 14-3-5.
//
//

#ifndef __Test__GameLogic_init__
#define __Test__GameLogic_init__

#include "GameLogic_refresh.h"
#include "DataInputScream.h"

class GameLogic_init: public GameLogic_refresh{
public:
    GameLogic_init()
    :m_max_gem_egg_count(0)
    ,m_max_gem_timebomb_count(0)
    ,m_max_gem_time_count(0)
    ,m_max_gold_count(0)

    ,m_clipper(NULL)
    ,m_block_bottom_layer(NULL)
    ,m_block_mid_layer(NULL)
    ,m_block_top_layer(NULL)
    ,m_block_offset(CCPointZero)
    ,m_special_layer(NULL)
    ,m_gem_layer(NULL)
    ,m_game_parent(NULL)
    {
        for (int i=0; i<WIN_CONDITION_MAX; i++) {
            m_win_conditions[i] = 0;
            m_win_conditions_now[i] = 0;
        }
        for (int i=0; i<LOSE_CONDITION_MAX; i++) {
            m_lose_conditions[i] = 0;
            m_lose_conditions_now[i] = 0;
        }
        
    }
    
    CCPoint GetBlockPos(int pos_id);
protected:

    
    virtual void DoSpecialBomb(SPECIAL_BOMB_TYPE bomb_type,GEM_COLOR color,int pos,float delay)=0;
    
    void LoadMap(int stage);
    
    void initGem();
    void initBlock();
    
    void clip(CCClippingNode* clipping, cocos2d::CCPoint _center, float wh);
    void initClip();
    
    void initBlockOffset();
    
    int blockdatas[BLOCK_NUM_WH];
    int gemdatas[BLOCK_NUM_WH];
    
    
    int m_max_gold_count;//场上最多存在的皇冠数
    int m_max_gem_time_count;//场上最多存在的精灵+5数量
    int m_max_gem_egg_count;//场上最多存在的蛋?数量
    int m_max_gem_timebomb_count;//场上最多存在的定时炸弹的数量
    
    CCPoint m_block_offset;
    CCLayer* m_special_layer;
    CCLayer* m_gem_layer;
    CCSpriteBatchNode* m_block_bottom_layer;
    CCSpriteBatchNode* m_block_mid_layer;
    CCSpriteBatchNode* m_block_top_layer;
    CCLayer* m_score_layer;
    CCLayer* m_combo_layer;
    
//    CCObject* m_doSpecialBombListener;
//    SEL_DOSPECIALBOMB m_doSpecialBombSelector;
//    CCObject* m_getPosListener;
//    SEL_GETPOS m_getPosSelector;
    
    CCClippingNode* m_clipper;
    CCClippingNode* m_mask_clipper;
    CCNode* m_game_parent;
};

#endif /* defined(__Test__GameLogic_init__) */

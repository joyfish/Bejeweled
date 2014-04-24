//
//  GameLogic_bomb.h
//  Test
//
//  Created by wilford on 14-3-5.
//
//

#ifndef __Test__GameLogic_bomb__
#define __Test__GameLogic_bomb__

#include "GemObject.h"
#include "BlockObject.h"
#include "GameLogic_stage_datas.h"

class BeeInfos:public CCObject{
public:
    int count;
    GEM_COLOR color;
    
    BeeInfos()
    :count(0)
    ,color(GEM_COLOR_NOCOLOR){
		autorelease();
    }
};


class GameLogic_bomb : public GameLogic_stage_datas{
    
protected:
    GameLogic_bomb(){
        m_bees = new CCArray();
        for (int i=0; i<BLOCK_NUM_WH; i++) {
            m_gems[i]=new GemObject();
        }
        for (int i=0; i<BLOCK_NUM_WH; i++) {
            m_blocks[i] = new BlockObject();
        }
    }
    
    ~GameLogic_bomb(){
        m_bees->removeAllObjects();
        CC_SAFE_DELETE(m_bees);
        for (int i=0;i<BLOCK_NUM_WH; i++) {
            CC_SAFE_DELETE(m_gems[i]);
        }
        for (int i=0; i<BLOCK_NUM_WH; i++) {
            CC_SAFE_DELETE(m_blocks[i]);
        }
    }
    
    void updatePreBomb(float dt);
    
    void Bomb(int pos,float delay = -1,bool isSpecialBomb = false);
    
    int* getSidesPosS(int pos);
    
    virtual void showScore(GEM_TYPE type,GEM_COLOR color,int pos){}
    virtual void showHoleScore(GEM_TYPE type,int pos){}
    virtual void showSeaHurt(int hurt,int pos){}
    
    BlockObject* m_blocks[BLOCK_NUM_WH];
    GemObject* m_gems[BLOCK_NUM_WH];
    
    CCArray* m_bees;
};

#endif /* defined(__Test__GameLogic_bomb__) */

//
//  GameLogic_special_bomb.h
//  Test
//
//  Created by wilford on 14-3-6.
//
//

#ifndef __Test__GameLogic_special_bomb__
#define __Test__GameLogic_special_bomb__

#include "GameLogic_delaycreate.h"

class SpecialBomb:public CCObject{
public:
    SPECIAL_BOMB_TYPE bomb_type;
    GEM_COLOR color;
    int pos;
    float delayTime;
    
    SpecialBomb()
    :pos(-1)
    ,delayTime(0)
    {
		autorelease();
    }
    
    void update(float dt){
        if (delayTime>0) {
            delayTime-=dt;
            delayTime = MAX(0, delayTime);
        }
    }
};

class GameLogic_special_bomb:public GameLogic_delaycreate{
public:
    GameLogic_special_bomb()
    {
        m_special_bombs = new CCArray();
    }
    
    ~GameLogic_special_bomb(){
        m_special_bombs->removeAllObjects();
        CC_SAFE_DELETE(m_special_bombs);
    }
    
    
    
protected:
    
    void updateSpecialBombs(float dt);
    
    
    virtual void DoSpecialBomb(SPECIAL_BOMB_TYPE bomb_type,GEM_COLOR color,int pos,float delay);
    
    
    void DestroyOnCB(CCNode* node);
    
    void DoSpecialBomb(SPECIAL_BOMB_TYPE bomb_type,GEM_COLOR color,int pos);
    
    float FlyNodeTo(CCNode* node,CCPoint from,CCPoint to,float duration,bool destoryOnOver = false,float delay = 0);
    
    CCArray* m_special_bombs;
    CCSpriteBatchNode* m_special_bomb_layer;
};

#endif /* defined(__Test__GameLogic_special_bomb__) */

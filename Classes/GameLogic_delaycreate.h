//
//  GameLogic_delaycreate.h
//  Test
//
//  Created by wilford on 14-3-6.
//
//

#ifndef __Test__GameLogic_delaycreate__
#define __Test__GameLogic_delaycreate__

#include "GameLogic_init.h"

class GameLogic_delaycreate : public GameLogic_init{

public:
    GameLogic_delaycreate()
    {
        m_delay_create_gems = new CCArray();
    }
    
    ~GameLogic_delaycreate(){
        m_delay_create_gems->removeAllObjects();
        CC_SAFE_DELETE(m_delay_create_gems);
    }
    
protected:
    void updateCreateGems(float dt);
    
    void createGem(int pos, int id, float delay = 0,float bomb_delay =-2){
        m_delay_create_gems->addObject(new DelayGemCreate(pos,id,delay,bomb_delay));
    }
};

#endif /* defined(__Test__GameLogic_delaycreate__) */

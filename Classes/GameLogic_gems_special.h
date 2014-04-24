//
//  GameLogic_gems_special.h
//  Test
//
//  Created by wilford on 14-3-6.
//
//

#ifndef __Test__GameLogic_gems_special__
#define __Test__GameLogic_gems_special__

#include "GameLogic_special_bomb.h"

class GameLogic_gems_special : public GameLogic_special_bomb{
    
protected:
    GameLogic_gems_special()
    :m_has_update_time_bomb(true)
    {
    }
    
    void updateBees();
    void updateTimeBombs();
    void DoBee(GEM_COLOR color,int count);
    void DoBee(int count);
    
    bool m_has_update_time_bomb;//该步定时炸弹是否计时
};

#endif /* defined(__Test__GameLogic_gems_special__) */

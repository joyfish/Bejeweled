//
//  GameLogic_gem_update.h
//  Test
//
//  Created by wilford on 14-3-6.
//
//

#ifndef __Test__GameLogic_gem_update__
#define __Test__GameLogic_gem_update__

#include "GameLogic_gems_special.h"

class GameLogic_gem_update : public GameLogic_gems_special{

protected:
    void updateGems(float dt){
        for (int i=0; i<BLOCK_NUM_WH; i++) {
            m_gems[i]->update(dt);
        }
    }
    
    void updateGemMove(){
        int flag = t_getRandom(2);
        for (int y = BLOCK_NUM_H-1;y>=0;y--) {
            if(flag){
                for (int x = BLOCK_NUM_W-1; x>=0; x--) {
                    int id = x+y*BLOCK_NUM_W;
                    checkGemMove(id);
                }
            }else{
                for (int x = 0; x<BLOCK_NUM_W ; x++) {
                    int id = x+y*BLOCK_NUM_W;
                    checkGemMove(id);
                }
            }
        }
    }
    
    int getDoorOutPosByID(int door_id);
    
    void checkGemMove(int pos);
    
    void checkGoldAsMoveFromGun(int pos);
};

#endif /* defined(__Test__GameLogic_gem_update__) */

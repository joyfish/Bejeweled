//
//  GameLogic_help.h
//  Test
//
//  Created by wilford on 14-3-5.
//
//

#ifndef __Test__GameLogic_help__
#define __Test__GameLogic_help__

#include "GameLogic_match.h"
#include "HWindowsManager.h"

class GameLogic_help : public GameLogic_match{
public:
	bool isInCustomTime();

protected:
    GameLogic_help(){}
    
    bool hasHelp(){
        for (int i=0; i<BLOCK_NUM_WH; i++) {
            if (m_gems[i]->IsHelping()) {
                return true;
            }
        }
        return false;
    }
    
    void clearHelp(){
        for (int i=0; i<BLOCK_NUM_WH; i++) {
            m_gems[i]->clearHelpAnim();
        }
    }
    
    bool canGemMoveToBlock(int from,int to);
    
    void updateHelp();
    
    virtual void RefreshGems(){}
    
    CCArray* m_delay_create_gems;
};

#endif /* defined(__Test__GameLogic_help__) */

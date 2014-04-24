//
//  GameLogic.h
//  Test
//
//  Created by wilford on 14-3-6.
//
//

#ifndef __Test__GameLogic__
#define __Test__GameLogic__

#include "GameLogic_guide.h"


class GameLogic:public GameLogic_guide{
public:
    GameLogic(CCNode* parent)
    :m_selected_pos(-1)
    {
        this->m_game_parent = parent;
    }
    
    void init(int stage);
    
    void GameUpdate(float dt);
    
    bool mTouchBegan(CCPoint pos);
    
    void mTouchMoved(CCPoint pos);
    
    void mTouchEnded(CCPoint pos);
protected:
    
	void selectGem(int pos);
    
	void unselectGem();
    
    void exChangeGems(int pos1,int pos2);
    void NextRound();
    
    bool checkExChange(int pos1,int pos2);
    
    bool checkExChangeSpecialGem(int pos1,int pos2);
    
    bool checkExChangeMagicGem(int pos1,int pos2);
    int m_selected_pos;
};

#endif /* defined(__Test__GameLogic__) */

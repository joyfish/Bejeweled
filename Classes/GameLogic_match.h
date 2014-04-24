//
//  GameLogic_match.h
//  Test
//
//  Created by wilford on 14-3-5.
//
//

#ifndef __Test__GameLogic_match__
#define __Test__GameLogic_match__

#include "GameLogic_bomb.h"

class NewSpcialGemInfos:public CCObject{
public:
    int gem_v_count;
    int gem_h_count;
    int gem_magic_count;
    int gem_area_count;
    int pos;
    NewSpcialGemInfos(int pos)
    :gem_area_count(0)
    ,gem_h_count(0)
    ,gem_v_count(0)
    ,gem_magic_count(0)
    {
        autorelease();
        this->pos = pos;
    }
    
    bool hasNewSpecialGem(){
        return gem_v_count>0||gem_h_count>0||gem_magic_count>0||gem_area_count>0;
    }
};


class GameLogic_match: public GameLogic_bomb{
    
protected:
    
    GameLogic_match()
    :m_combo(0)
    {}
    
    virtual void Combo(){}
    
    void updateMatchColor();
    
    bool matchColors(int pos,int* gem_ids);
    
    bool IsMatchColor(int pos,int newPos);
    
    void matchColor(int pos);
    
    bool isMatchIgnorePos(int pos);
    
    void AddMatchClearPos(vector<int> clear_pos);
    
    bool matchColors(int pos,bool ishelp = false);
    
    int getEmptyPosRound(int pos);

    vector<int> m_match_ignore_pos;
    vector<int> m_match_clear_pos;
    vector<NewSpcialGemInfos*> m_match_new_gem_type;
    int m_combo;
};

#endif /* defined(__Test__GameLogic_match__) */

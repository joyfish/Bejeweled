//
//  GameLogic_gems_special.cpp
//  Test
//
//  Created by wilford on 14-3-6.
//
//

#include "GameLogic_gems_special.h"

void GameLogic_gems_special::updateBees(){
    CCObject* obj;
    CCARRAY_FOREACH(m_bees, obj){
        BeeInfos* bee_infos = (BeeInfos*)obj;
        if (bee_infos->color == GEM_COLOR_NOCOLOR) {
            DoBee(bee_infos->count);
        }else{
            DoBee(bee_infos->color,bee_infos->count);
        }
    }
    m_bees->removeAllObjects();
}

void GameLogic_gems_special::updateTimeBombs(){
    if (m_has_update_time_bomb) {
        return;
    }
    if (!isInCustomTime()) {
        return;
    }
    if (game_state != GAME_STATE_PLAY) {
        return;
    }
    
    for (int i=0; i<BLOCK_NUM_WH; i++) {
        if (m_blocks[i]->m_IsLastRoundTopNewCreated) {
            continue;
        }
        if (m_blocks[i]->getBottomType() == BLOCK_BOTTOM_GUN||
            m_blocks[i]->getBottomType() == BLOCK_BOTTOM_COIL_GUN) {
            continue;
        }
        if(m_gems[i]->IsTimeBombType()){
            m_gems[i]->cutTimeBomb();
            if (m_gems[i]->getTimeBombLife()==0) {
                //”Œœ∑ ß∞‹
                game_lose();
            }
        }
    }
    
    m_has_update_time_bomb = true;
}

void GameLogic_gems_special::DoBee(GEM_COLOR color,int count){
    int beePosS[BLOCK_NUM_WH];
    int ids[BLOCK_NUM_WH];
    int len = 0;
    for (int i=0; i<BLOCK_NUM_WH; i++) {
        if (m_gems[i]->HasBee()) {
            continue;
        }
        if (!m_blocks[i]->canMoveIn()) {
            continue;
        }
        if (m_gems[i]->isEmpty()) {
            continue;
        }
        
        if (!m_blocks[i]->isMatchColor()) {
            continue;
        }
        
        if (m_gems[i]->getColor()!=color) {
            continue;
        }
        beePosS[len]=i;
        ids[len] = len;
        len++;
    }
    
    //CCLOG("beelen %d",len);
    count = MIN(len, count);
    //CCLOG("count %d",count);
    for (int i=0; i<count; i++) {
        int id = ids[t_getRandom(len)];
        //CCLOG("beePos %d id %d",beePosS[id],m_gems[beePosS[id]]->id);
        m_gems[beePosS[id]]->PlayBee();
        ids[id] = ids[len-1];
        len--;
    }
}

void GameLogic_gems_special::DoBee(int count){
    int beePosS[BLOCK_NUM_WH];
    int ids[BLOCK_NUM_WH];
    int len = 0;
    for (int i=0; i<BLOCK_NUM_WH; i++) {
        if (m_gems[i]->HasBee()) {
            continue;
        }
        if (!m_blocks[i]->canMoveIn()) {
            continue;
        }
        
        if (!m_blocks[i]->isMatchColor()) {
            continue;
        }
        
        if (m_gems[i]->isEmpty()) {
            continue;
        }
        
        if (m_gems[i]->getType()!=GEM_NORMAL) {
            continue;
        }
        
        beePosS[len]=i;
        ids[len] = len;
        len++;
    }
    
    count = MIN(len, count);
    for (int i=0; i<count; i++) {
        int id = ids[t_getRandom(len)];
        //CCLOG("beePos %d id %d",beePosS[id],m_gems[beePosS[id]]->id);
        m_gems[beePosS[id]]->PlayBee();
        ids[id] = ids[len-1];
        len--;
    }
}
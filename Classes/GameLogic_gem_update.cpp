//
//  GameLogic_gem_update.cpp
//  Test
//
//  Created by wilford on 14-3-6.
//
//

#include "GameLogic_gem_update.h"

int GameLogic_gem_update::getDoorOutPosByID(int door_id){
    for (int i=0; i<BLOCK_NUM_WH; i++) {
        if (m_blocks[i]->getBottomType()==BLOCK_BOTTOM_DOOR_OUT) {
            if (m_blocks[i]->getBottomNum()==door_id) {
                return i;
            }
        }
    }
    return -1;
}

void GameLogic_gem_update:: checkGemMove(int pos){
    
    if (m_gems[pos]->isEmpty()) {
        return;
    }
    
    if (m_gems[pos]->IsMoving()) {
        return;
    }
    
    if (m_gems[pos]->HasBee()) {
        return;
    }
    
    if (m_blocks[pos]->IsTopBombing()) {
        return;
    }
    
    if (!m_blocks[pos]->canMoveOut()) {
        return;
    }
    
    if (m_blocks[pos] ->getBottomType() == BLOCK_BOTTOM_DOOR_IN) {
        int door_id = m_blocks[pos]->getBottomNum();
        int door_out_pos = getDoorOutPosByID(door_id);
        if (door_out_pos == -1) {
            return;
        }
        
        if (!m_blocks[door_out_pos]->canDoorMoveIn()) {
            return;
        }
        if (m_gems[door_out_pos]->IsBombing()) {
            return;
        }
        if (m_gems[door_out_pos]->id>0) {
            return;
        }
        m_blocks[pos]->playDoorAnimation();
        m_blocks[door_out_pos]->playDoorAnimation();
        m_gems[pos]->toGemObject(m_gems[door_out_pos]);
        m_gems[door_out_pos]->DoorMove();
        return;
    }
    
    if (!m_blocks[pos]->canMoveOutFromDir(ROPE_DIR_DOWN)&&
        !m_blocks[pos]->canMoveOutFromDir(ROPE_DIR_LEFT)&&
        !m_blocks[pos]->canMoveOutFromDir(ROPE_DIR_RIGHT)) {
        return;
    }
    
    int tmpx = pos%BLOCK_NUM_W;
    int tmpy = pos/BLOCK_NUM_W;
    int tmpy_d = tmpy+1;
    int tmpx_l = tmpx-1;
    int tmpx_r = tmpx+1;
    if (tmpy_d>=BLOCK_NUM_H) {
        return;
    }
    
    do{//判定下方
        int tmpPosD = tmpx+tmpy_d*BLOCK_NUM_W;
        
        if (!m_gems[tmpPosD]->isEmpty()) {
            break;
        }
        
        if (m_blocks[tmpPosD]->IsTopBombing()) {
            return;
        }
        
        if (!m_blocks[tmpPosD]->canMoveInFromDir(ROPE_DIR_UP)) {
            break;
        }
        if (m_gems[tmpPosD]->IsBombing()) {
            break;
        }
        
        
        //CCLOG("[%d]: %d -> %d",m_gems[pos]->id, pos,tmpPosD);
        checkGoldAsMoveFromGun(pos);
        m_gems[pos]->toGemObject(m_gems[tmpPosD]);
        m_gems[tmpPosD]->Move();
        m_blocks[pos]->playCoilGunAnimation();
        return;
    }while(0);
    
    if (m_blocks[pos]->getBottomType()==BLOCK_BOTTOM_GUN||
        m_blocks[pos]->getBottomType()==BLOCK_BOTTOM_COIL_GUN) {
        return;
    }
    
    do{//判定左下
        if (tmpx_l < 0 ) {
            break;
        }
        
        int tmpPosL = tmpx_l+tmpy*BLOCK_NUM_W;
        
        
        
        if (m_blocks[tmpPosL]->canMoveOutFromDir(ROPE_DIR_DOWN)) {
            break;
        }
        
        int tmpPosDL = tmpx_l + tmpy_d*BLOCK_NUM_W;
        
        if (!m_gems[tmpPosDL]->isEmpty()) {
            break;
        }
        
        if (m_blocks[tmpPosDL]->IsTopBombing()) {
            return;
        }
        
        if (m_gems[tmpPosDL]->IsBombing()) {
            break;
        }
        
        if (m_blocks[tmpPosDL]->getBottomType() == BLOCK_BOTTOM_DOOR_OUT) {
            break;
        }
        
        if (!m_blocks[pos]->canMoveOutFromDir(ROPE_DIR_LEFT)&&!m_blocks[pos]->canMoveOutFromDir(ROPE_DIR_DOWN)) {
            break;
        }
        if (!m_blocks[tmpPosDL]->canMoveInFromDir(ROPE_DIR_RIGHT)&&!m_blocks[tmpPosDL]->canMoveInFromDir(ROPE_DIR_UP)) {
            break;
        }
        
        if (!m_blocks[pos]->canMoveOutFromDir(ROPE_DIR_DOWN)&&!m_blocks[tmpPosDL]->canMoveInFromDir(ROPE_DIR_UP)) {
            break;
        }
        
        if (!m_blocks[pos]->canMoveOutFromDir(ROPE_DIR_LEFT)&&!m_blocks[tmpPosDL]->canMoveInFromDir(ROPE_DIR_RIGHT)) {
            break;
        }
        
        
        checkGoldAsMoveFromGun(pos);
        m_gems[pos]->toGemObject(m_gems[tmpPosDL]);
        m_gems[tmpPosDL]->Move();
        m_blocks[pos]->playCoilGunAnimation();
        return;
        
    }while (0);
    
    do{ //判定右下
        if (tmpx_r >= BLOCK_NUM_W ) {
            break;
        }
        
        int tmpPosR = tmpx_r+tmpy*BLOCK_NUM_W;
        
        
        if (m_blocks[tmpPosR]->canMoveOutFromDir(ROPE_DIR_DOWN)) {
            break;
        }
        
        int tmpPosDR = tmpx_r + tmpy_d*BLOCK_NUM_W;
        
        
        if (!m_gems[tmpPosDR]->isEmpty()) {
            break;
        }
        
        if (m_blocks[tmpPosDR]->IsTopBombing()) {
            return;
        }
        
        if (m_gems[tmpPosDR]->IsBombing()) {
            break;
        }
        
        if (m_blocks[tmpPosDR]->getBottomType() == BLOCK_BOTTOM_DOOR_OUT) {
            break;
        }
        
        if (!m_blocks[pos]->canMoveOutFromDir(ROPE_DIR_RIGHT)&&!m_blocks[pos]->canMoveOutFromDir(ROPE_DIR_DOWN)) {
            break;
        }
        if (!m_blocks[tmpPosDR]->canMoveInFromDir(ROPE_DIR_LEFT)&&!m_blocks[tmpPosDR]->canMoveInFromDir(ROPE_DIR_UP)) {
            break;
        }
        
        if (!m_blocks[pos]->canMoveOutFromDir(ROPE_DIR_DOWN)&&!m_blocks[tmpPosDR]->canMoveInFromDir(ROPE_DIR_UP)) {
            break;
        }
        
        if (!m_blocks[pos]->canMoveOutFromDir(ROPE_DIR_RIGHT)&&!m_blocks[tmpPosDR]->canMoveInFromDir(ROPE_DIR_LEFT)) {
            break;
        }
        
        checkGoldAsMoveFromGun(pos);
        m_gems[pos]->toGemObject(m_gems[tmpPosDR]);
        m_gems[tmpPosDR]->Move();
        m_blocks[pos]->playCoilGunAnimation();
        return;
        
    }while (0);
}

void GameLogic_gem_update::checkGoldAsMoveFromGun(int pos){
    if (m_blocks[pos]->getBottomType() == BLOCK_BOTTOM_GUN) {
        int gold_count = 0;
        for (int i=0; i<BLOCK_NUM_WH; i++) {
            if (m_gems[i]->getType() == GEM_GOLD) {
                gold_count++;
            }
        }
        if (gold_count>=m_max_gold_count) {
            return;
        }
        if (gold_count+m_win_conditions_now[WIN_CONDITION_GOLD]>=m_win_conditions[WIN_CONDITION_GOLD]) {
            return;
        }
        
        if (gold_count == 0) {
            m_gems[pos]->create(GEM_GOLD*10+GEM_COLOR_NOCOLOR);
        }else{
            if (t_getRandom(2)) {
                m_gems[pos]->create(GEM_GOLD*10+GEM_COLOR_NOCOLOR);
            }
        }
    }
}
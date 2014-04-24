//
//  GameLogic_help.cpp
//  Test
//
//  Created by wilford on 14-3-5.
//
//

#include "GameLogic_help.h"

bool GameLogic_help::canGemMoveToBlock(int from,int to){
    if (!m_blocks[from]->canMoveOut()) {
        return false;
    }
    ROPE_DIR rope_dir = ROPE_DIR_NONE;
    int tmpx1 = from%BLOCK_NUM_W;
    int tmpy1 = from/BLOCK_NUM_W;
    int tmpx2 = to%BLOCK_NUM_W;
    int tmpy2 = to/BLOCK_NUM_W;
    if ((tmpx1==tmpx2)&&(tmpy1==tmpy2-1)) {//从上移入to
        rope_dir = ROPE_DIR_UP;
    }
    if ((tmpx1 == tmpx2) && (tmpy1 == tmpy2+1)) {//从下移入to
        rope_dir = ROPE_DIR_DOWN;
    }
    if ((tmpx1 == tmpx2-1)&&(tmpy1 == tmpy2)) {//从左移入to
        rope_dir = ROPE_DIR_LEFT;
    }
    if ((tmpx1 == tmpx2+1)&&(tmpy1 == tmpy2)) {//从右移入to
        rope_dir = ROPE_DIR_RIGHT;
    }
    if (rope_dir > 0) {//从上下左右移入的状态才判定
        if (m_blocks[to]->canMoveInFromDir(rope_dir)) {
            return true;
        }
        return false;
    }
    return false;
}

bool GameLogic_help::isInCustomTime(){
    if (HWindowsManager::S()->hasWindowsShowed()) {
        return false;
    }
    
    if (m_delay_create_gems->count()>0) {
        return false;
    }
    
	for (int i=0; i<BLOCK_NUM_WH; i++) {
		if (m_gems[i]->IsMoving()) {
			return false;
		}
		if (m_gems[i]->IsBombing()) {
			return false;
		}
		if (m_gems[i]->IsPreBomb()) {
			return false;
		}
		if (m_gems[i]->HasBee()) {
			return false;
		}
		if (m_blocks[i]->IsTopBombing()) {
			return false;
		}
        if (m_gems[i]->hasGameWinAnim()) {
            return false;
        }
	}
	return true;
}

void GameLogic_help::updateHelp(){
    if (isInGuide) {
        return;
    }
	if (hasHelp()) {
		if (!isInCustomTime()) {
			clearHelp();
		}
		return;
	}
    
    if (game_state != GAME_STATE_PLAY) {
        return;
    }
    
	if (!isInCustomTime()) {
		return;
	}
    
	for (int i=0; i<BLOCK_NUM_WH; i++) {
		if (m_gems[i]->id == 0) {
			continue;
		}
		if (!m_blocks[i]->canMoveIn()) {
			continue;
		}
		int tmpx = i%BLOCK_NUM_W;
		int tmpy = i/BLOCK_NUM_W;
        int tmpx_r = tmpx+1;
        int tmpy_d = tmpy+1;
        do{
            if (tmpx_r>=BLOCK_NUM_W) {
                break;
            }
            int tmpPos = tmpx_r+tmpy*BLOCK_NUM_W;
            if (m_gems[tmpPos]->isEmpty()) {
                break;
            }
            if (!canGemMoveToBlock(i, tmpPos)) {
                break;
            }
            if (!canGemMoveToBlock(tmpPos, i)) {
                break;
            }
            
            m_gems[i]->exChangeWithGemObject(m_gems[tmpPos]);
            
            if (matchColors(i,true)) {
                m_gems[i]->exChangeWithGemObject(m_gems[tmpPos]);
                return;
            }
            if (matchColors(tmpPos,true)) {
                m_gems[i]->exChangeWithGemObject(m_gems[tmpPos]);
                return;
            }
            m_gems[i]->exChangeWithGemObject(m_gems[tmpPos]);
        }while(0);
        
        do{
            if (tmpy_d>=BLOCK_NUM_H) {
                break;
            }
            int tmpPos = tmpx+tmpy_d*BLOCK_NUM_W;
            if (m_gems[tmpPos]->isEmpty()) {
                break;
            }
            if (!canGemMoveToBlock(i, tmpPos)) {
                break;
            }
            if (!canGemMoveToBlock(tmpPos, i)) {
                break;
            }
            
            m_gems[i]->exChangeWithGemObject(m_gems[tmpPos]);
            
            if (matchColors(i,true)) {
                m_gems[i]->exChangeWithGemObject(m_gems[tmpPos]);
                return;
            }
            if (matchColors(tmpPos,true)) {
                m_gems[i]->exChangeWithGemObject(m_gems[tmpPos]);
                return;
            }
            m_gems[i]->exChangeWithGemObject(m_gems[tmpPos]);
        }while(0);
    }
    
    if (!hasHelp()) {
        RefreshGems();
    }
}
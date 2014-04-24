//
//  GameLogic_block_update.cpp
//  Test
//
//  Created by wilford on 14-3-6.
//
//

#include "GameLogic_block_update.h"

void GameLogic_block_update::updateDestroyedBlock(){
    for (int i=0; i<BLOCK_NUM_WH; i++) {
        if (m_blocks[i]->getTopType()!=BLOCK_TOP_NONE) {
            if (m_blocks[i]->getTopNum() == 0) {
                BLOCK_TOP_TYPE type = m_blocks[i]->getTopType();
                switch (type) {
                    case BLOCK_TOP_DIRTY:
                        m_has_destroyed_dirty = true;
                        break;
                    case BLOCK_TOP_EGG:
                        m_blocks[i]->newTop(BLOCK_TOP_EGG);
                        DoBlockEggEffect();
                        break;
                    case BLOCK_TOP_WALL:
                        Win_Condition_Add(WIN_CONDITION_WALL);
                        break;
                    case BLOCK_TOP_VIRUS:
                        Win_Condition_Add(WIN_CONDITION_VIRUS);
                        showSeaHurt(30, i);
                        if (G::g_game_mode == GAMEMODE_SEA) {
                            achieve_count->sea_vircus_count++;
                        }
                        m_gems[i]->isNewMoveOver = true;
                        break;
                    case BLOCK_TOP_BIG_ICE:
                        m_gems[i]->isNewMoveOver = true;
                        break;
                    case BLOCK_TOP_PRISON:
                        Win_Condition_Add(WIN_CONDITION_PRISON);
                        m_gems[i]->isNewMoveOver = true;
                        break;
                    case BLOCK_TOP_SEA_WALL:
                        achieve_count->sea_wall_count++;
                        G::G_Add_Achievement_Complete(33);
                        showSeaHurt(500, i);
                    default:
                        break;
                }
                if (m_blocks[i]->getTopNum() == 0) {
                    m_blocks[i]->setTopType(BLOCK_TOP_NONE);
                    m_blocks[i]->resetBlock();
                }
            }
        }
        
        if (m_blocks[i]->getMidType() != BLOCK_MID_NONE ) {
            if (m_blocks[i]->getMidNum() == 0) {
                BLOCK_MID_TYPE  type = m_blocks[i]->getMidType();
                switch (type) {
                    case BLOCK_MID_ICE:
                        Win_Condition_Add(WIN_CONDITION_ICE);
                        break;
                    default:
                        break;
                }
                m_blocks[i]->setMidType(BLOCK_MID_NONE);
                m_blocks[i]->resetBlock();
            }
        }
        
    }
}

void GameLogic_block_update::DoBlockEggEffect(){//精灵蛋消除后的特效
    int count = 3;//制造污染物的数量
    int effectPosS[BLOCK_NUM_WH];
    int ids[BLOCK_NUM_WH];
    int len = 0;
    for (int i=0; i<BLOCK_NUM_WH; i++) {
        if (m_gems[i]->HasBee()) {
            continue;
        }
        if (!m_blocks[i]->canMoveIn()) {
            continue;
        }
        
        if (m_blocks[i]->getTopType() != BLOCK_TOP_NONE) {
            continue;
        }
        
        if (m_gems[i]->isEmpty()) {
            continue;
        }
        
        if (m_gems[i]->IsMoving()) {
            continue;
        }
        
        if (m_gems[i]->IsPreBomb()) {
            continue;
        }
        
        if (m_gems[i]->getType()!=GEM_NORMAL) {
            continue;
        }
        
        effectPosS[len]=i;
        ids[len] = len;
        len++;
    }
    
    count = MIN(len, count);
    for (int i=0; i<count; i++) {
        int id = ids[t_getRandom(len)];
        //m_gems[effectPosS[id]]->clear();
        m_gems[effectPosS[id]]->create(GEM_COIL*10+GEM_COLOR_NOCOLOR);
        //m_blocks[effectPosS[id]]->newTop(BLOCK_TOP_DIRTY);
        ids[id] = ids[len-1];
        len--;
    }
}

void GameLogic_block_update::updateSeeVirus(){
    if (G::g_game_mode!=GAMEMODE_SEA) {
        return;
    }
    if (m_has_new_seavirus) {
        return;
    }
    
    if (!isInCustomTime()) {
        return;
    }
    if (game_state != GAME_STATE_PLAY) {
        return;
    }
    if (m_step_caculate%4!=0) {
        return;
    }
    
    int seaviruscount = 0;
    
    for (int i=0; i<BLOCK_NUM_WH; i++) {
        if (m_blocks[i]->getTopType() == BLOCK_TOP_VIRUS) {
            seaviruscount++;
        }
    }
    
    if (seaviruscount>=6) {
        return;
    }
    
    int PosS[BLOCK_NUM_WH];
    int PosCount = 0;
    for (int i=0; i<BLOCK_NUM_WH; i++) {
        if (!m_blocks[i]->canMoveIn()) {
            continue;
        }
        if (m_blocks[i]->getTopType()!= BLOCK_TOP_NONE) {
            continue;
        }
        if (m_gems[i]->isEmpty()) {
            continue;
        }
        if (m_gems[i]->getType()!=GEM_NORMAL) {
            continue;
        }
        
        PosS[PosCount++] = i;
    }
    
    int count  = MIN(3, PosCount);
    
    for (int i=0; i<count; i++) {
        int id =t_getRandom(PosCount);
        int p = PosS[id];
        m_blocks[p]->newTop(BLOCK_TOP_VIRUS);
        PosS[id] = PosS[PosCount-1];
        PosCount--;
    }
    
    
    SeaMouthOut();
    m_has_new_seavirus =true;

}

void GameLogic_block_update::updateSeaWall(){
    if (G::g_game_mode!=GAMEMODE_SEA) {
        return;
    }
    if (m_has_new_seawall) {
        return;
    }
    if (!isInCustomTime()) {
        return;
    }
    if (game_state != GAME_STATE_PLAY) {
        return;
    }
    if (m_step_caculate%6!=0) {
        return;
    }
    
    int seawallcount = 0;
    
    for (int i=0; i<BLOCK_NUM_WH; i++) {
        if (m_blocks[i]->getTopType() == BLOCK_TOP_SEA_WALL) {
            seawallcount++;
        }
    }
    
    if (seawallcount>=4) {
        return;
    }
    
    int PosS[BLOCK_NUM_WH];
    int PosCount = 0;
    for (int i=0; i<BLOCK_NUM_WH; i++) {
        if (!m_blocks[i]->canMoveIn()) {
            continue;
        }
        if (m_blocks[i]->getTopType()!= BLOCK_TOP_NONE) {
            continue;
        }
        if (m_gems[i]->getType()!=GEM_NORMAL) {
            continue;
        }
        
        PosS[PosCount++] = i;
    }
    
    if (PosCount>0) {
        int p = PosS[t_getRandom(PosCount)];
        m_gems[p]->clear();
        m_blocks[p]->newTop(BLOCK_TOP_SEA_WALL);
    }
    
    
    m_has_new_seawall =true;
}

void GameLogic_block_update::updateDirtys(){
    if (m_has_destroyed_dirty) {
        return;
    }
    if (m_has_infected_dirty) {
        return;
    }
    if (!isInCustomTime()) {
        return;
    }
    
    if (game_state != GAME_STATE_PLAY) {
        return;
    }
    
    int dirtyPosS[BLOCK_NUM_WH];
    int PosCount = 0;
    for (int i=0; i<BLOCK_NUM_WH; i++) {
        if (m_blocks[i]->m_IsLastRoundTopNewCreated) {
            continue;
        }
        if (m_blocks[i]->getTopType()==BLOCK_TOP_DIRTY||
            m_blocks[i]->getBottomType() == BLOCK_BOTTOM_DIRTY_RES) {
            int* sides = getSidesPosS(i);
            for (int j=0; j<4; j++) {
                int side = sides[j];
                if (side==-1) {
                    continue;
                }
                
                if (!m_blocks[side]->canMoveIn()) {
                    continue;
                }
                
                if (m_blocks[side]->getTopType()!= BLOCK_TOP_NONE) {
                    continue;
                }
                
                if (m_gems[side]->isEmpty()) {
                    continue;
                }
                
                if (m_gems[side]->getType()!=GEM_NORMAL) {
                    continue;
                }
                
                dirtyPosS[PosCount++] = side;
                break;
            }
            CC_SAFE_DELETE(sides);
        }
    }
    
    if (PosCount>0) {
        int p = dirtyPosS[t_getRandom(PosCount)];
        m_gems[p]->clear();
        m_blocks[p]->newTop(BLOCK_TOP_DIRTY);
    }
    
    
    m_has_infected_dirty =true;
}

void GameLogic_block_update::updateVirus(){
    if (m_has_moved_virus) {
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
        if (m_blocks[i]->m_IsnewMoveInTop) {
            continue;
        }
        if (m_blocks[i]->getTopType() == BLOCK_TOP_VIRUS) {
            int* sides = getSidesPosS(i);
            for (int j=0; j<4; j++) {
                int side = sides[j];
                if (side==-1) {
                    continue;
                }
                
                if (!m_blocks[side]->canMoveIn()) {
                    continue;
                }
                if (m_blocks[side]->getTopType()!= BLOCK_TOP_NONE) {
                    continue;
                }
                if (m_gems[side]->isEmpty()) {
                    continue;
                }
                m_blocks[i]->moveTopToBlockObject(m_blocks[side]);
                break;
            }
            CC_SAFE_DELETE(sides);
        }
    }
    
    m_has_moved_virus = true;
}

void GameLogic_block_update::updateBlockGun(){
    int gem_egg_count = 0;
    int gem_timebomb_count = 0;
    int gem_time_count = 0;
    int gem_coil_count = 0;
    for (int i=0; i<BLOCK_NUM_WH; i++) {
        if (m_gems[i]->getType() == GEM_EGG) {
            gem_egg_count++;
        }
        if (m_gems[i]->IsTimeBombType()) {
            gem_timebomb_count++;
        }
        if (m_gems[i]->getType() == GEM_TIME) {
            gem_time_count++;
        }
        if (m_gems[i]->getType() == GEM_COIL) {
            gem_coil_count++;
        }
    }
    
    for (int i=0; i<BLOCK_NUM_WH; i++) {
        if (m_blocks[i]->getBottomType() == BLOCK_BOTTOM_GUN) {
            if (m_gems[i]->isEmpty()) {
                int color = getCreateGemColor(i);
                if (m_max_gem_egg_count>gem_egg_count) {
                    if (!t_getRandom(20)) {
                        m_gems[i]->newGem(GEM_EGG*10+color);
                        m_gems[i]->m_gem_container->setVisible(false);
                        gem_egg_count++;
                        continue;
                    }
                }
                if (m_max_gem_timebomb_count>gem_timebomb_count) {
                    if (!t_getRandom(30)) {
                        m_gems[i]->newGem((GEM_TIME_BOMB+10)*10+color);
                        m_gems[i]->m_gem_container->setVisible(false);
                        gem_timebomb_count++;
                        continue;
                    }
                }
                if (m_max_gem_time_count>gem_time_count) {
                    if (!t_getRandom(20)) {
                        m_gems[i]->newGem(GEM_TIME*10+color);
                        m_gems[i]->m_gem_container->setVisible(false);
                        gem_time_count++;
                        continue;
                    }
                }
                
                bool hasCreateBao = false;
                vector<int>::iterator it = bao_ids.begin();
                while(it!=bao_ids.end()){
                    int rand = t_getRandom(100);
                    if (rand<10) {
                        int bao_id = *it;
                        m_gems[i]->bao_id = bao_id;
                        m_gems[i]->newGem(GEM_BAO*10+GEM_COLOR_NOCOLOR);
                        m_gems[i]->m_gem_container->setVisible(false);
                        it = bao_ids.erase(it);
                        hasCreateBao = true;
                        break;
                    }
                    it++;
                }
                if (hasCreateBao) {
                    continue;
                }
                
                m_gems[i]->newGem(color);
                m_gems[i]->m_gem_container->setVisible(false);
            }
        }
        
        if (m_blocks[i]->getBottomType() == BLOCK_BOTTOM_COIL_GUN) {
            if (m_gems[i]->isEmpty()) {
                int color = getCreateGemColor(i);
                if (t_getRandom(3)==0&&gem_coil_count<10) {
                    m_gems[i]->newGem(GEM_COIL*10+GEM_COLOR_NOCOLOR);
                }else{
                    m_gems[i]->newGem(color);
                }
                m_gems[i]->m_gem_container->setVisible(false);
            }
        }
    }
}

int GameLogic_block_update::getCreateGemColor(int pos){
    int m_colorsNum[GEM_COLOR_NOCOLOR-1];
    int m_colorsID[GEM_COLOR_NOCOLOR-1];
//    int maxCount = 0;
//    int maxColor = 0;
    
    for (int i=0; i<GEM_COLOR_NOCOLOR-1; i++) {
        m_colorsNum[i]=0;
        m_colorsID[i]=i+1;
    }
    
    for (int i=0; i<BLOCK_NUM_WH; i++) {
        int color =m_gems[i]->getColor();
        if (color<=m_maxColor&&color>0) {
            m_colorsNum[color-1]++;
        }
    }
    
    int j, k;
    int flag;
    
    flag = m_maxColor;
    while (flag > 0)
    {
        k = flag;
        flag = 0;
        for (j = 1; j < k; j++){
            if (m_colorsNum[j - 1] < m_colorsNum[j])
            {
                int tmp = m_colorsNum[j-1];
                m_colorsNum[j-1]=m_colorsNum[j];
                m_colorsNum[j] = tmp;
                tmp = m_colorsID[j-1];
                m_colorsID[j-1]=m_colorsID[j];
                m_colorsID[j]= tmp;
                flag = j;
            }
        }
    }
    
//    for (int i=0; i<m_maxColor-1; i++) {
//        if (m_colorsNum[i]>maxCount) {
//            maxCount = m_colorsNum[i];
//            maxColor = i+1;
//        }
//    }
    
    int allowSameColorCount = 2;
    int color = 0;
    bool isAllowColor = false;
    for (int i=0; i<allowSameColorCount; i++) {
        pos += BLOCK_NUM_W;
        if (pos >= BLOCK_NUM_WH) {
            isAllowColor = true;
            break;
        }
        if (color == 0) {
            color = m_gems[pos]->getColor();
        }
        if (color == 0||color == GEM_COLOR_NOCOLOR) {
            isAllowColor = true;
            break;
        }
        if (m_gems[pos]->getColor()!=color) {
            isAllowColor = true;
            break;
        }
    }
    
    vector<int> newColors;
    for (int i=1; i<=m_maxColor; i++) {
        if (!isAllowColor) {
            if (i==color) {
                continue;
            }
        }
        if (i == m_colorsID[0]||
            i == m_colorsID[1]){
            continue;
        }
        newColors.push_back(i);
    }
    
    int returnColor = newColors[t_getRandom(newColors.size())];
    newColors.clear();
    return returnColor;
}

void GameLogic_block_update::updateMagnet(){
    for (int i=0; i<BLOCK_NUM_WH; i++) {
        if (m_blocks[i]->getBottomType() == BLOCK_BOTTOM_MAGNET) {
            if (m_gems[i]->getType() != GEM_GOLD)
                continue;
            if (m_gems[i]->IsMoving()) {
                continue;
            }
            m_gems[i]->GoldOut();
            GoldOut(i);
        }
    }
}

void GameLogic_block_update::GoldOut(int pos)
{
    Win_Condition_Add(WIN_CONDITION_GOLD);
    G::G_playEffect(RES_MUSIC_GOLD_OUT);
}
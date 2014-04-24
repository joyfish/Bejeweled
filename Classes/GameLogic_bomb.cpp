//
//  GameLogic_bomb.cpp
//  Test
//
//  Created by wilford on 14-3-5.
//
//

#include "GameLogic_bomb.h"

void GameLogic_bomb::updatePreBomb(float dt){
    for (int i=0; i<BLOCK_NUM_WH; i++) {
        m_gems[i]->updatePreBomb(dt);
        if (m_gems[i] -> m_bomb_delayTime == 0) {
            if (!m_gems[i] -> IsMoving()) {
                Bomb(i,-1,m_gems[i]->isBombBySpecial);
                m_gems[i]->isBombBySpecial = false;
            }
        }
    }
}

void GameLogic_bomb::Bomb(int pos,float delay,bool isSpecialBomb){
    if (m_blocks[pos]->Bomb()) {
        if (delay!=-1) {
            m_gems[pos]->Bomb(delay);
            m_gems[pos]->isBombBySpecial = isSpecialBomb;
        }else{
            GEM_TYPE gem_type = m_gems[pos]->getType();
            GEM_COLOR gem_color = m_gems[pos]->getColor();
            if (m_gems[pos]->Bomb()) {
                if (gem_color>0&&gem_color<GEM_COLOR_NOCOLOR) {
                    if (m_win_conditions[WIN_CONDITION_COLOR_0+gem_color-1]>0) {
                        Win_Condition_Add(WIN_CONDITION_COLOR_0+gem_color-1);
                    }
                }
                showHoleScore(gem_type, pos);
                showScore(gem_type, gem_color, pos);
                
                switch (gem_type) {
                    case GEM_AREA:
                    case GEM_MAGIC:
                    case GEM_H:
                    case GEM_V:
                    case GEM_VH:
                    case GEM_2MAGIC:
                    case GEM_3AREA:
                    case GEM_MAGIC_NORMAL:
                    case GEM_MAGIC_AREA:
                    case GEM_MAGIC_VH:
                    case GEM_3VH:
                        achieve_count->special_bomb_count_single_move++;
                    case GEM_NORMAL:
                    case GEM_TIME:
                    case GEM_SPECIAL:
                        achieve_count->bomb_count_single_move++;
                        break;
                        
                    default:
                        break;
                }
                
                switch (gem_type) {
                    case GEM_TIME://+5Ãë±¦Ê¯
                        m_lose_conditions_now[LOSE_CONDITION_TIME]+=5;
                        break;
                    case GEM_SPECIAL://¾«Áé£¿
                    {
                        int flag = t_getRandom(3);
                        if (flag == 0) {
                            m_gems[pos]->create(GEM_H*10+gem_color);
                        }else if (flag == 1) {
                            m_gems[pos]->create(GEM_V*10+gem_color);
                        }else{
                            m_gems[pos]->create(GEM_AREA*10+gem_color);
                        }
                    }
                        break;
                    case GEM_BEE://ÃÛ·ä
                    {
                        BeeInfos* bee_infos = new BeeInfos();
                        bee_infos->color = gem_color;
                        bee_infos->count = 3;
                        m_bees->addObject(bee_infos);
                    }
                        break;
                    case GEM_EGG://µ°
                    {
                        int flag = t_getRandom(6);
                        if (flag == 0) {
                            m_gems[pos]->create(GEM_SPECIAL*10+gem_color);
                        }else if(flag == 1){
                            m_gems[pos]->create((GEM_TIME_BOMB+10)*10+gem_color);
                        }else if(flag == 2){
                            m_blocks[pos]->newTop(BLOCK_TOP_WALL,3);
                            m_blocks[pos]->m_IsTopNewCreated = true;
                        }else if(flag == 3){
                            m_blocks[pos]->newTop(BLOCK_TOP_WALL,4);
                            m_blocks[pos]->m_IsTopNewCreated = true;
                        }else if(flag == 4){
                            m_blocks[pos]->newTop(BLOCK_TOP_DIRTY);
                            m_blocks[pos]->m_IsTopNewCreated = true;
                        }else{
                            m_blocks[pos]->newTop(BLOCK_TOP_BIG_ICE);
                            m_blocks[pos]->m_IsTopNewCreated = true;
                        }
                    }
                    case GEM_COIL:
                    return;
                    case GEM_BAO:
                        return;
                    default:
                        break;
                }
                
                if (gem_type>=GEM_HOLE_WALL&&gem_type<=GEM_HOLE_SPECIAL_7) {
                    return;
                }
                

                
                //                    if (m_blocks[pos]->getTopType()== BLOCK_TOP_PRISON) {
                //                        m_blocks[pos]->BombTop();
                //                    }
                
                if (m_blocks[pos]->getMidType() == BLOCK_MID_ICE) {
                    m_blocks[pos]->BombMid();
                }
                
                
                
                if (!isSpecialBomb) {
                    int* sidesPs = getSidesPosS(pos);
                    for (int i=0; i<4; i++) {
                        int sidePos = sidesPs[i];
                        if (sidePos == -1) {
                            continue;
                        }
                        
                        if (m_blocks[sidePos]->getBottomType() == BLOCK_BOTTOM_COIL_GUN||
                            m_blocks[sidePos]->getBottomType() == BLOCK_BOTTOM_GUN||
                            m_blocks[sidePos]->getBottomType() == BLOCK_BOTTOM_SPACE) {
                            continue;
                        }
                        
                        if (m_gems[sidePos]->getType() == GEM_COIL) {
                            Bomb(sidePos);
//                            m_gems[sidePos]->Bomb();
//							showScore(GEM_COIL, GEM_COLOR_NOCOLOR, sidePos);
                        }
                        
                        if (m_gems[sidePos]->getType() == GEM_BAO) {
                            CCLOG("bao_id %d",m_gems[sidePos]->bao_id);
                            BAO_INFO* info = (BAO_INFO*)G::g_bao_infos->objectAtIndex(m_gems[sidePos]->bao_id);
                            if (info->id == 16) {
                                G::g_hole_isOpened = true;
                            }else if(info->id == 33){
                                G::g_sea_isOpened = true;
                            }
                            info->isGot = true;
                            HPersistence::S()->SaveToFile();
                            HPersistence::S()->SaveBao(m_gems[sidePos]->bao_id);
                            Bomb(sidePos);
                        }
                        
                        
                        if (m_gems[sidePos]->IsHoleWall()) {
                            Bomb(sidePos);
                        }
                        
                        BLOCK_TOP_TYPE top_type = m_blocks[sidePos]->getTopType();
                        if (top_type == BLOCK_TOP_EGG||
                            top_type == BLOCK_TOP_DIRTY||
                            top_type == BLOCK_TOP_BIG_ICE||
                            top_type == BLOCK_TOP_VIRUS||
                            top_type == BLOCK_TOP_WALL||
                            top_type == BLOCK_TOP_SEA_WALL) {
                            m_blocks[sidePos]->BombTop();
                        }
                    }
                    CC_SAFE_DELETE(sidesPs);
                }
            }
        }
    }
}

int* GameLogic_bomb::getSidesPosS(int pos){
    int tmp[4];
    for (int i=0; i<4; i++) {
        tmp[i] = -1;
    }
    int tmpx = pos%BLOCK_NUM_W;
    int tmpy = pos/BLOCK_NUM_W;
    
    if (tmpy+1 < BLOCK_NUM_H) {//ÏÂ
        tmp[0] = tmpx + (tmpy+1)*BLOCK_NUM_W;
    }
    if (tmpy-1 >= 0) {//ÉÏ
        tmp[1] = tmpx+ (tmpy-1)*BLOCK_NUM_W;
    }
    if (tmpx-1 >=0) {//×ó
        tmp[2] = tmpx-1 + tmpy*BLOCK_NUM_W;
    }
    if (tmpx+1 < BLOCK_NUM_W) {//ÓÒ
        tmp[3] = tmpx+1 + tmpy*BLOCK_NUM_W;
    }
    
    //        for (int i=0; i<4; i++) {
    //            std::cout<<"tmp"<<tmp[i]<<" ";
    //        }
    //        std::cout<<"\n";
    
    
    int ids[4] = {0,1,2,3};
    int count = 4;
    int* ps = new int[4];
    for (int i=0; i<4; i++) {
        int id = t_getRandom(count);
        ps[i] = tmp[ids[id]];
        ids[id] = ids[count-1];
        count--;
    }
    
    //        for (int i=0; i<4; i++) {
    //            std::cout<<"ps"<<ps[i]<<" ";
    //        }
    //        std::cout<<"\n";
    
    return ps;
}


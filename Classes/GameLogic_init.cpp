//
//  GameLogic_init.cpp
//  Test
//
//  Created by wilford on 14-3-5.
//
//

#include "GameLogic_init.h"

void GameLogic_init::LoadMap(int stage){
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    IntToStringFormat(_mapPath, "/mnt/sdcard/maps/m%d", stage);
//#else
//    IntToStringFormat(_mapPath, "maps/m%d", stage);
//#endif
//    
//    
//    //	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
//    //#else
//    //    CCDirector::sharedDirector()->end();
//    //#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    //    exit(0);
//    //#endif
//    //#endif
//    //IntToStringFormat(_mapPath, "maps/m%d", stage);
//    CCLOG("loadPath : %s",_mapPath);
//    DataInputStream* dis = DataInputStream::loadFileWithPath(_mapPath);
//    if (dis) {
//        m_maxColor = dis->readChar();
//        //m_maxColor = 6;
//        m_max_gold_count = dis->readChar();
//        //m_max_gold_count = 2;
//        m_max_gem_time_count = dis->readChar();
//        //m_max_gem_time_count = 1;
//        m_max_gem_egg_count = dis->readChar();
//        //m_max_gem_egg_count = 1;
//        m_max_gem_timebomb_count = dis->readChar();
//        //m_max_gem_timebomb_count = 1;
//
//		m_score_3star = dis->readInt();
//		m_score_2star = m_score_3star*0.7f;
//		m_score_max = m_score_3star*1.04f;
//
//		for (int i=0;i<WIN_CONDITION_MAX;i++)
//		{
//			m_win_conditions[i] = dis->readInt();
//		}
//		
//		for (int i=0;i<LOSE_CONDITION_MAX;i++)
//		{
//			 m_lose_conditions_now[i]=m_lose_conditions[i] = dis->readInt();
//		}
//        
//        
//        
//        for (int i=0; i<BLOCK_NUM_WH; i++) {
//            blockdatas[i] = dis->readInt();
//        }
//        for(int i=0;i<BLOCK_NUM_WH;i++){
//            gemdatas[i] = dis->readShort();
//        }
//        
//        CC_SAFE_DELETE(dis);
//    }
    
    
    m_maxColor = G::g_game_maxColorCount;
    //m_maxColor = 6;
    m_max_gold_count = G::g_game_max_gold_count;
    //m_max_gold_count = 2;
    m_max_gem_time_count = G::g_game_max_gem_time_count;
    //m_max_gem_time_count = 1;
    m_max_gem_egg_count =G::g_game_max_gem_egg_count;
    //m_max_gem_egg_count = 1;
    m_max_gem_timebomb_count = G::g_game_max_gem_timebomb_count;
    
    m_score_3star = G::g_game_star_score;
    m_score_2star = G::g_game_star2_score;
    m_score_max = m_score_3star*1.04f;
    score_rate = 1 + 5.0f*G::g_game_buff[2]/100.0f;
    
    for (int i=0;i<WIN_CONDITION_MAX;i++)
    {
        m_win_conditions[i] = G::g_game_win_conditions[i];
    }
    
    for (int i=0;i<LOSE_CONDITION_MAX;i++)
    {
        m_lose_conditions_now[i]=m_lose_conditions[i] = G::g_game_lose_conditions[i];
    }
    m_lose_conditions_now[LOSE_CONDITION_STEP]+=G::g_game_buff[0]*5;
    m_lose_conditions_now[LOSE_CONDITION_TIME]+=G::g_game_buff[1]*10;
    
    
    
    for (int i=0; i<BLOCK_NUM_WH; i++) {
        blockdatas[i] = G::g_game_blocks[i];
    }
    for(int i=0;i<BLOCK_NUM_WH;i++){
        gemdatas[i] = G::g_game_gems[i];
    }
    
    for (int i=0; i<MAX_BAO; i++) {
        BAO_INFO* info = (BAO_INFO*)G::g_bao_infos->objectAtIndex(i);
        if (info->isGot)
            continue;
        int rand = t_getRandom(100);
        if (rand<=90) {
            continue;
        }
        if (baos_type[i]==BAO_FROM_HOLE&&G::g_game_mode == GAMEMODE_HOLE) {
            bao_ids.push_back(i);
        }
        if (baos_type[i] == BAO_FROM_SEA && G::g_game_mode == GAMEMODE_SEA) {
            bao_ids.push_back(i);
        }
        if (baos_type[i] == BAO_FROM_STAGE && G::g_game_mode == GAMEMODE_STAGE) {
            if (baos_level[i]==G::g_game_stage+1) {
                bao_ids.push_back(i);
            }
        }
    }
    
}

void GameLogic_init::initGem(){
    int tmp[BLOCK_NUM_WH] = {
        0,0,0,0,0,0,0,0,0,
        0,3104,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,
        0,0,0,23,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,4,0,
        0,0,1,1,4,3,5,0,0,
        0,0,3,73,4,3,3203,0,0,
        0,1,1,1,23,1,3,3,0,
        0,999,999,999,999,999,999,999,0,
    };
    
    int gem_ids[BLOCK_NUM_WH];
    
    for (int i=0; i<BLOCK_NUM_WH; i++) {
        m_gems[i]->AddGetPosEvent(this,h_getPos(GameLogic_init::GetBlockPos));
        m_gems[i]->AddDoSpecialBombEvent(this , h_doSpecialBomb(GameLogic_init::DoSpecialBomb));
        m_gems[i]->setGemLayer(m_gem_layer,m_special_layer);
        m_gems[i]->pos = i;
        
        if (!m_blocks[i]->canInsertGem()) {
            continue;
        }
        if (m_blocks[i]->getBottomType() == BLOCK_BOTTOM_GUN||
            m_blocks[i]->getBottomType() == BLOCK_BOTTOM_COIL_GUN) {
            continue;
        }
       
        
        m_gems[i]->id = gemdatas[i];
        //m_gems[i]->id = tmp[i];
        
        if (m_gems[i]->id == 999) {
            m_gems[i]->id = 0;
            continue;
        }
//        if (m_gems[i]->getType() == GEM_TIME_BOMB) {
//            m_blocks[i]->setIsNewWithGem(false);
//            continue;
//        }
        
        if (m_blocks[i]->getTopType() == BLOCK_TOP_VIRUS||
            m_blocks[i]->getTopType() == BLOCK_TOP_PRISON||
            m_blocks[i]->getTopType() == BLOCK_TOP_BIG_ICE) {
            m_blocks[i]->setIsNewWithGem(true);
            continue;
        }
        
        if (m_gems[i]->id == 0) {
            m_gems[i]->id = t_getRandom(m_maxColor)+1;
        }else{
            m_blocks[i]->setIsNewWithGem(true);
        }
    }
    
    for (int i=0; i<BLOCK_NUM_WH; i++) {
        gem_ids[i]=m_gems[i]->id;
    }
    
//    bool has_match_color = false;
//    for (int i=0; i<BLOCK_NUM_WH;i++) {
//        if (matchColors(i, gem_ids)) {
//            has_match_color = true;
//        }
//    }
    

   	if (hasMatchColor()) {
        updata(true);
    }else{
        updata();
    }

    
    
    for (int i=0; i<BLOCK_NUM_WH; i++) {
        if (data[i]>0) {
            m_gems[i]->id = data[i];
        }
        //            m_gems[i]->newGem(m_gems[i]->id);
        m_blocks[i]->setIsNewWithGem(false);
    }
    
//    int gem_ids[BLOCK_NUM_WH];
//    for (int i =0; i<BLOCK_NUM_WH; i++) {
//        gem_ids[i] = m_gems[i]->id;
//    }
//    for (int i=0; i<BLOCK_NUM_WH; i++) {
//        if (matchColors(i, gem_ids)) {
//            CCLOG("[matchColor]: %d [%d]",i,gem_ids[i]);
//        }
//        
//    }
    
    for (int i=0; i<BLOCK_NUM_WH; i++) {
        if (m_gems[i]->IsHoleWall()) {
            m_gems[i]->newGem(m_gems[i]->id);
            continue;
        }
        m_delay_scalein_gems->addObject(new DelayGemCreate(i,m_gems[i]->id,(i/BLOCK_NUM_W)*0.2f));
    }
    
}

void GameLogic_init::initBlock(){
    int tmp[BLOCK_NUM_WH] = {
        0x000080,0x000080,0x000080,0x000080,0x000080,0x000080,0x000000,0x000080,0x000000,
        0x000010,0x000010,0x000010,0x000010,0x001010,0x000010,0x000040,0x000010,0x000000,
        0x000010,0x130010,0x000010,0x130010,0x000010,0x000010,0x000010,0x000010,0x000000,
        0x000010,0x000010,0x000010,0x000010,0x000010,0x000010,0x000010,0x000010,0x000000,
        0x000010,0x000010,0x000010,0x000010,0x000010,0x000010,0x000010,0x000010,0x000000,
        0x000010,0x000030,0x000010,0x000010,0x000010,0x000010,0x000010,0x000010,0x000000,
        0x000010,0x000010,0x001110,0x000010,0x000010,0x000010,0x000010,0x000010,0x000000,
        0x000010,0x610010,0x511210,0x000010,0x000010,0x000010,0x000010,0x000010,0x000000,
        0x310010,0x310010,0x310010,0x310010,0x000010,0x000010,0x310010,0x310010,0x310010,
        0x000010,0x000010,0x000010,0x000010,0x000010,0x000010,0x000010,0x000010,0x000010,
    };
    for (int i=0; i<BLOCK_NUM_WH; i++) {
        m_blocks[i]->pos = i;
        m_blocks[i]->AddGetPosEvent(this,h_getPos(GameLogic_init::GetBlockPos));
        m_blocks[i]->setBlockLayer(m_block_bottom_layer,m_block_mid_layer,m_block_top_layer,m_special_layer);
        m_blocks[i]->id = blockdatas[i];
        //m_blocks[i]->id = tmp[i];
    }
    
    initBlockOffset();
    
    for (int i=0; i<BLOCK_NUM_WH; i++) {
        
        m_blocks[i]->create(m_blocks[i]->id);
    }
}

void GameLogic_init::clip(CCClippingNode* clipping, cocos2d::CCPoint _center, float wh){
    CCDrawNode *stencil = (CCDrawNode*)clipping->getStencil();
    CCPoint rectangle[4];
    rectangle[0] = ccp(_center.x-wh/2, _center.y-wh/2);
    rectangle[1] = ccp(_center.x+wh/2, _center.y-wh/2);
    rectangle[2] = ccp(_center.x+wh/2,_center.y+wh/2);
    rectangle[3] = ccp(_center.x-wh/2, _center.y+wh/2);
    ccColor4F white = {0, 0, 0, 1};
    stencil->drawPolygon(rectangle, 4, white, 1, white);
}

void GameLogic_init::initClip(){
    for (int i=0; i<BLOCK_NUM_WH; i++) {
        if (m_blocks[i]->getBottomType() == BLOCK_BOTTOM_SPACE||
            m_blocks[i]->getBottomType() == BLOCK_BOTTOM_GUN||
            m_blocks[i]->getBottomType() == BLOCK_BOTTOM_COIL_GUN) {
            continue;
        }
        clip(m_clipper,GetBlockPos(i), BLOCK_WH);
    }
}

CCPoint GameLogic_init::GetBlockPos(int pos_id){
    float x = m_block_offset.x + pos_id%BLOCK_NUM_W*BLOCK_WH;
    float y = m_block_offset.y - pos_id/BLOCK_NUM_W*BLOCK_WH;
    return ccp(x,y);
    //return CCPointZero;
}

void GameLogic_init::initBlockOffset(){
    m_block_offset = CCPointZero;
    float minX = 0;
    float minY = 0;
    float maxX = 0;
    float maxY = 0;
    bool first = true;
    for (int i=0; i<BLOCK_NUM_WH; i++) {
        if (m_blocks[i]->getBottomType() == BLOCK_BOTTOM_SPACE||
            m_blocks[i]->getBottomType() == BLOCK_BOTTOM_GUN||
            m_blocks[i]->getBottomType() == BLOCK_BOTTOM_COIL_GUN) {
            continue;
        }
        
        //if (m_blocks[i]>0) {
        CCPoint pos = GetBlockPos(i);
        if (first) {
            minX = pos.x;
            minY = pos.y;
            maxX = pos.x;
            maxY = pos.y;
            first = false;
        }else{
            minX = MIN(minX,pos.x);
            minY = MIN(minY,pos.y);
            maxX = MAX(maxX,pos.x);
            maxY = MAX(maxY,pos.y);
        }
        // }
        
    }
    CCPoint _center = ccp((maxX+minX)/2,(minY+maxY)/2);
    switch (G::g_game_mode) {
        case GAMEMODE_STAGE:
            m_block_offset = ccp(_pCenter.x -_center.x,_pCenter.y -_center.y-50);
            break;
        case GAMEMODE_HOLE:
        {
            float offsety =  (_pScreenSize.height - 960)/2;
            m_block_offset = ccp(_pCenter.x -_center.x,_pBottom + 762 + BLOCK_WH/2+offsety);
        }
            break;
        case GAMEMODE_SEA:
            m_block_offset = ccp(_pCenter.x -_center.x,_pCenter.y -_center.y-50);
            break;
        default:
            break;
    }
   
    CCLOG("%f,%f",m_block_offset.x,m_block_offset.y);
}

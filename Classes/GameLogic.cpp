//
//  GameLogic.cpp
//  Test
//
//  Created by wilford on 14-3-6.
//
//

#include "GameLogic.h"

void GameLogic::init(int stage){
    m_gem_layer = CCLayer::create();
    m_game_parent->addChild(m_gem_layer,4);
    m_block_top_layer = CCSpriteBatchNode::create("Blocks.pvr.ccz");
    m_block_mid_layer = CCSpriteBatchNode::create("Blocks.pvr.ccz");
    m_block_bottom_layer = CCSpriteBatchNode::create("Blocks.pvr.ccz");
    m_clipper = CCClippingNode::create();
    m_special_bomb_layer = CCSpriteBatchNode::create("special_bomb_effect.pvr.ccz");
    m_clipper->setStencil(CCDrawNode::create());
    m_clipper->setInverted(false);
    m_clipper->addChild(m_special_bomb_layer);
    m_special_bomb_layer->setPosition(CCPointZero);
    m_game_parent->addChild(m_block_bottom_layer,2);
    m_game_parent->addChild(m_block_mid_layer,3);
    m_game_parent->addChild(m_block_top_layer,5);
    m_special_layer = CCLayer::create();
    m_game_parent->addChild(m_special_layer,7);
    m_game_parent->addChild(m_clipper,10);
    m_mask_clipper = CCClippingNode::create();
    m_mask_clipper->setStencil(CCDrawNode::create());
    m_mask_clipper->setInverted(true);
    m_game_parent->addChild(m_mask_clipper,11);
    m_ui_layer = UILayer::create();
    m_game_parent->addChild(m_ui_layer,6);
    m_ui_top_layer = UILayer::create();
    m_game_parent->addChild(m_ui_top_layer,12);
    achieve_count = new ACHIEVE_COUNT();
    
    m_score_layer = CCLayer::create();
    m_game_parent->addChild(m_score_layer,11);
    m_combo_layer = CCLayer::create();
    m_game_parent->addChild(m_combo_layer,20);
    m_combo_layer->setPosition(ccp(_pRight-160-_pCenter.x,_pTop-50-_pCenter.y));
    LoadMap(stage);
    drawBackground();
    initBlock();
    initGem();
    initClip();
    initUI();
    initCombo();
    
//    CCLayerColor* layerColor = CCLayerColor::create(ccc4(0, 0, 0, 255*7/10), _pScreenSize.width , _pScreenSize.height);
//    m_mask_clipper->addChild(layerColor,12);

    
    //game_state = GAME_STATE_WIN;
}

void GameLogic::GameUpdate(float dt){
    updateToolBtns();
    updateScaleInAndOutGems(dt);
    if (IsRefreshTime()) {
        return;
    }
    updateDelayCostStep(dt);
    
    updateBlocks(dt);
    updateBlockGun();
    updateGems(dt);
    updateMagnet();
    updateGemMove();
    updateMatchColor();
    updateSpecialBombs(dt);
    updateCreateGems(dt);
    updateDestroyedBlock();
    updateBees();
    updatePreBomb(dt);
    updateGameStart();
    updateGameReady();
    updateGuide(dt);
    updateGameOver();    
    updateTimeBombs();
    updateSeeVirus();
    updateSeaWall();
    updateDirtys();
    updateVirus();
    updateHelp();
    updateHole(dt);
    updateHoleRise();
    updateSea(dt);
    updateConditions(dt);
}

bool GameLogic::mTouchBegan(CCPoint pos){
    if (game_state != GAME_STATE_PLAY&&!isInGuide) {
        return false;
    }
    if (!hasHelp()&&!isInGuide) {
        return false;
    }
    
    for(int i=0;i<BLOCK_NUM_H*BLOCK_NUM_W;i++){
        CCPoint iPos = GetBlockPos(i);
        iPos.x-=_pCenter.x;
        iPos.y-=_pCenter.y;
        CCRect rect = CCRectMake(iPos.x-BLOCK_WH/2,iPos.y-BLOCK_WH/2,BLOCK_WH,BLOCK_WH);
        if(rect.containsPoint(pos)){
            if (m_tool_selected>=0) {
                UseTool(m_tool_selected,i);
				return false;
            }
            
            if(!m_blocks[i]->canMoveOut())
                return false;
            if (!m_blocks[i]->canMoveIn()) {
                return false;
            }
            
            if(m_gems[i]->isEmpty()){
                unselectGem();
                return false;
            }
            
            if (m_selected_pos!=-1)
            {
                if(m_selected_pos != i)
                {
                    if (isInGuide) {
                        if (i!=m_guide_to_block_id) {
                            return false;
                        }else{
                            closeGuide();
                        }
                    }
                    if (abs(m_selected_pos-i)==1||
                        abs(m_selected_pos-i)==BLOCK_NUM_W)
                    {
                        exChangeGems(m_selected_pos, i);
                        unselectGem();
                        return false;
                    }
                    
                }
            }
            
            if (isInGuide) {
                if (i!=m_guide_from_block_id) {
                    return false;
                }
            }
            
            selectGem(i);
            return true;
        }
    }
    return false;
}

void GameLogic::mTouchMoved(CCPoint pos){
    if (m_selected_pos == -1) {
        return;
    }
    
    for(int i=0;i<BLOCK_NUM_H*BLOCK_NUM_W;i++){
        CCPoint iPos = GetBlockPos(i);
        iPos.x-=_pCenter.x;
        iPos.y-=_pCenter.y;
        CCRect rect = CCRectMake(iPos.x-BLOCK_WH/2,iPos.y-BLOCK_WH/2,BLOCK_WH,BLOCK_WH);
        if(rect.containsPoint(pos)){
            if(m_selected_pos != i){
                if (isInGuide) {
                    if (i!=m_guide_to_block_id) {
                        return;
                    }else{
                        closeGuide();
                    }
                }
                exChangeGems(m_selected_pos, i);
                unselectGem();
            }
            break;
        }
    }
}

void GameLogic::mTouchEnded(CCPoint pos){}

void GameLogic::selectGem(int pos){
    unselectGem();
    int tmpx = pos%BLOCK_NUM_W;
    int tmpy = pos/BLOCK_NUM_W;
    if (tmpx-1>=0)
    {
        if (tmpy-1>=0)//左上
        {
            int tmpPos = (tmpx-1)+(tmpy-1)*BLOCK_NUM_W;
            m_gems[tmpPos]->Look(EYE_DIR_RIGHT_DOWN);
        }
        if(tmpy+1<BLOCK_NUM_H){//左下
            int tmpPos = (tmpx-1)+(tmpy+1)*BLOCK_NUM_W;
            m_gems[tmpPos]->Look(EYE_DIR_RIGHT_UP);
        }
        int tmpPos = (tmpx-1)+tmpy*BLOCK_NUM_W;//左
        m_gems[tmpPos]->Look(EYE_DIR_RIGHT);
    }
    if (tmpx+1<BLOCK_NUM_W)
    {
        if (tmpy-1>=0)//右上
        {
            int tmpPos = (tmpx+1)+(tmpy-1)*BLOCK_NUM_W;
            m_gems[tmpPos]->Look(EYE_DIR_LEFT_DOWN);
        }
        if(tmpy+1<BLOCK_NUM_H){//右下
            int tmpPos = (tmpx+1)+(tmpy+1)*BLOCK_NUM_W;
            m_gems[tmpPos]->Look(EYE_DIR_LEFT_UP);
        }
        int tmpPos = (tmpx+1)+tmpy*BLOCK_NUM_W;//右
        m_gems[tmpPos]->Look(EYE_DIR_LEFT);
    }
    if (tmpy-1>=0)//上
    {
        int tmpPos = tmpx+(tmpy-1)*BLOCK_NUM_W;
        m_gems[tmpPos]->Look(EYE_DIR_DOWN);
    }
    if(tmpy+1<BLOCK_NUM_H){//下
        int tmpPos = tmpx+(tmpy+1)*BLOCK_NUM_W;
        m_gems[tmpPos]->Look(EYE_DIR_UP);
    }
    m_selected_pos = pos;
}

void GameLogic::unselectGem(){
    if (m_selected_pos == -1)
    {
        return;
    }
    
    int tmpx = m_selected_pos%BLOCK_NUM_W;
    int tmpy = m_selected_pos/BLOCK_NUM_W;
    
    for (int i=-1;i<2;i++)
    {
        for (int j = -1;j<2;j++)
        {
            int x = tmpx + i;
            int y = tmpy + j;
            if (x<0||x>=BLOCK_NUM_W)
            {
                continue;
            }
            if (y<0||y>=BLOCK_NUM_H)
            {
                continue;
            }
            int p = x+y*BLOCK_NUM_W;
            if (p == m_selected_pos)
            {
                continue;
            }
            
            m_gems[p]->Look(EYE_DIR_NONE);
        }
    }
    
    m_selected_pos = -1;
    
}

void GameLogic::exChangeGems(int pos1,int pos2){
    
    if (m_gems[pos1]->id == 0) {
        return;
    }
    if (m_gems[pos2]->id == 0) {
        return;
    }
    
    if (m_gems[pos1]->IsHoleWall()) {
        return;
    }
    
    if (m_gems[pos2]->IsHoleWall()) {
        return;
    }
    
    if (!canGemMoveToBlock(pos1, pos2)) {
        return;
    }
    
    if (!canGemMoveToBlock(pos2, pos1)) {
        return;
    }
    
    if (checkExChangeMagicGem(pos1, pos2)) {
        NextRound();
        clearHelp();
        return;
    }
    
    if (checkExChange(pos1, pos2)) {
        NextRound();
        clearHelp();
        m_combo = 0;
        m_gems[pos1]->exChangeWithGemObject(m_gems[pos2]);
        m_gems[pos1]->Move();
        m_gems[pos2]->Move();
        m_gems[pos1]->IsExchangeMove = true;
        m_gems[pos2]->IsExchangeMove = true;
    }else{
        clearHelp();
        m_gems[pos1]->MoveGoAndBack(pos2);
        m_gems[pos2]->MoveGoAndBack(pos1);
        m_gems[pos1]->IsExchangeMove = true;
        m_gems[pos2]->IsExchangeMove = true;
    }
    
}

void GameLogic::NextRound(){//操作完成进入新的一步
    m_has_moved_virus = false;
    m_has_destroyed_dirty = false;
    m_has_infected_dirty = false;
    m_has_update_time_bomb = false;
    m_has_new_seawall = false;
    m_has_new_seavirus = false;
    for (int i=0; i<BLOCK_NUM_WH; i++) {
        if (m_blocks[i]->getBottomType() == BLOCK_BOTTOM_GUN||
            m_blocks[i]->getBottomType() == BLOCK_BOTTOM_COIL_GUN) {
            continue;
        }
        m_blocks[i]->m_IsLastRoundTopNewCreated = false;
    }
    if(achieve_count->bomb_count_single_move<100)
        achieve_count->bomb_count_single_move = 0;
    if(achieve_count->special_bomb_count_single_move<7)
        achieve_count->special_bomb_count_single_move=0;
    achieve_count->exchange_count ++;
    if (achieve_count->use_reposion_bomb_count<3) {
        achieve_count->use_reposion_bomb_count = 0;
    }
    Lose_Condition_Add(LOSE_CONDITION_STEP);
    m_step_caculate++;
}

bool GameLogic::checkExChange(int pos1,int pos2){
    if (checkExChangeSpecialGem(pos1, pos2)) {
        return true;
    }
    
    int gem_ids[BLOCK_NUM_WH];
    for (int i=0; i<BLOCK_NUM_WH; i++) {
        gem_ids[i] = m_gems[i]->id;
    }
    int tmp = gem_ids[pos1];
    gem_ids[pos1] = gem_ids[pos2];
    gem_ids[pos2] = tmp;
    if (matchColors(pos1, gem_ids)) {
        return true;
    }
    if (matchColors(pos2, gem_ids)) {
        return true;
    }
    return false;
}

bool GameLogic::checkExChangeSpecialGem(int pos1,int pos2){
    int type1= m_gems[pos1]->getType();
    int type2 = m_gems[pos2]->getType();
    int color1 = m_gems[pos1]->getColor();
    
    if ((type1 == GEM_V && type2 == GEM_V)||
        (type1 == GEM_H && type2 == GEM_H)||
        (type1 == GEM_V && type2 == GEM_H)||
        (type1 == GEM_H && type2 == GEM_V)) {
        m_gems[pos1]->id = GEM_VH*10+color1;
        m_gems[pos2]->id %= 10;
        m_gems[pos1]->Bomb(0);
        return  true;
    }
    if ((type1==GEM_AREA && type2 == GEM_V)||
        (type1==GEM_AREA && type2 == GEM_H)||
        (type1==GEM_H && type2 == GEM_AREA)||
        (type1==GEM_V && type2 == GEM_AREA)) {
        m_gems[pos1]->id = GEM_3VH*10+color1;
        m_gems[pos2]->id %= 10;
        m_gems[pos1]->Bomb(0);
        return true;
    }
    if (type1 == GEM_AREA&&type2 == GEM_AREA) {
        m_gems[pos1]->id = GEM_3AREA*10+color1;
        m_gems[pos2]->id %= 10;
        m_gems[pos1]->Bomb(0);
        return true;
    }
    return false;
}

bool GameLogic::checkExChangeMagicGem(int pos1,int pos2){
    int type1= m_gems[pos1]->getType();
    int type2 = m_gems[pos2]->getType();
    int color1 = m_gems[pos1]->getColor();
    int color2 = m_gems[pos2]->getColor();
    
    if ((type1 == GEM_MAGIC && type2 == GEM_V)||
        (type1 == GEM_MAGIC && type2 == GEM_H)) {
        m_gems[pos1]->id = GEM_MAGIC_VH*10+color2;
        m_gems[pos1]->Bomb(0);
        return  true;
    }
    if ((type2 == GEM_MAGIC && type1 == GEM_V)||
        (type2 == GEM_MAGIC && type1 == GEM_H)) {
        m_gems[pos2]->id = GEM_MAGIC_VH*10+color1;
        m_gems[pos2]->Bomb(0);
        return  true;
    }
    if (type1 == GEM_MAGIC && type2 == GEM_AREA) {
        m_gems[pos1]->id = GEM_MAGIC_AREA*10+color2;
        m_gems[pos1]->Bomb(0);
        return  true;
    }
    if (type2 == GEM_MAGIC && type1 == GEM_AREA) {
        m_gems[pos2]->id = GEM_MAGIC_AREA*10+color1;
        m_gems[pos2]->Bomb(0);
        return  true;
    }
    if ((type1 == GEM_MAGIC && type2 == GEM_MAGIC)||
        (type2 == GEM_MAGIC && type1 == GEM_MAGIC)) {
        m_gems[pos1]->id = GEM_2MAGIC*10+color1;
        m_gems[pos1]->Bomb(0);
        m_gems[pos2]->Bomb(0);
        return  true;
    }
    
    if (type1 == GEM_MAGIC && color2 != GEM_COLOR_NOCOLOR) {
        m_gems[pos1]->id = GEM_MAGIC_NORMAL*10+color2;
        m_gems[pos1]->Bomb(0);
        return  true;
    }
    
    if (type2 == GEM_MAGIC && color1 != GEM_COLOR_NOCOLOR) {
        m_gems[pos2]->id = GEM_MAGIC_NORMAL*10+color1;
        m_gems[pos2]->Bomb(0);
        return  true;
    }
    return false;
}
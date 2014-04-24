//
//  GameScene.cpp
//  Bejeweled
//
//  Created by wilford on 14-1-5.
//
//

#include "GameScene.h"
#include <iostream>
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "HJNI.h"
#endif

void GameScene::onEnter(){
    HScene::onEnter();
    G::g_gamescene_type = GAMESCENE_GAME;
    CCLOG("GameOnEnter");
    G::G_playBackGroundMusic(RES_MUSIC_GAME_BG);
    ZipUtils::ccSetPvrEncryptionKeyPart(0, 0x965b1a0e);
    ZipUtils::ccSetPvrEncryptionKeyPart(1, 0xfb2cb339);
    ZipUtils::ccSetPvrEncryptionKeyPart(2, 0x8cc83a4d);
    ZipUtils::ccSetPvrEncryptionKeyPart(3, 0xfb6f0ffb);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Gems.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Blocks.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("normal_bomb_effect.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("special_bomb_effect.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("block_bomb_effect.plist");

    m_game_logic = new GameLogic(this);
    m_game_logic->setMLayer(m_layer);
    m_game_logic->init(G::g_game_stage);
    m_game_logic->addGameLoseEvent(this, h_game_lose(GameScene::ShowGameLose));
    m_game_logic->addGameWinEvent(this, h_game_win(GameScene::ShowGameWin));
    m_game_logic->addToolBuyEvent(this, h_toolBuy(GameScene::ShowToolBuy));
    m_game_logic->addShowNormalTipsEvent(this, h_showNormalTips(GameScene::ShowNormalTips));
    m_game_logic->addGamePauseEvent(this, h_gamePause(GameScene::ShowGamePause));
    m_game_logic->addGameReadyEvent(this, h_showGameReady(GameScene::ShowGameReady));
    m_game_logic->addHoleResultEvent(this, h_hole_result(GameScene::ShowHoleResult));
    m_game_logic->addSeaResultEvent(this, h_sea_result(GameScene::ShowSeaResult));
    m_game_logic->addGameEndBuyEvent(this, h_game_end_buy(GameScene::showGameEndBuy));

    CCDirector::sharedDirector()->getKeypadDispatcher()->addDelegate(this);
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
//    SimpleAudioEngine::sharedEngine()->preloadEffect(RES_MUSIC_BOMB_0);
//    SimpleAudioEngine::sharedEngine()->preloadEffect(RES_MUSIC_BOMB_1);
//    SimpleAudioEngine::sharedEngine()->preloadEffect(RES_MUSIC_BOMB_2);
}

void GameScene::onExit(){
    HScene::onExit();
    CC_SAFE_DELETE(m_game_logic);
    CCDirector::sharedDirector()->getKeypadDispatcher()->removeDelegate(this);
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    SimpleAudioEngine::sharedEngine()->unloadEffect(RES_MUSIC_BOMB_0);
    SimpleAudioEngine::sharedEngine()->unloadEffect(RES_MUSIC_BOMB_1);
    SimpleAudioEngine::sharedEngine()->unloadEffect(RES_MUSIC_BOMB_2);
}

//void GameScene::clip(cocos2d::CCPoint _center, float wh){
//    CCDrawNode *stencil = (CCDrawNode*)m_clipper->getStencil();
//    CCPoint rectangle[4];
//    rectangle[0] = ccp(_center.x-wh/2, _center.y-wh/2);
//    rectangle[1] = ccp(_center.x+wh/2, _center.y-wh/2);
//    rectangle[2] = ccp(_center.x+wh/2,_center.y+wh/2);
//    rectangle[3] = ccp(_center.x-wh/2, _center.y+wh/2);
//    ccColor4F white = {0, 0, 0, 1};
//    stencil->drawPolygon(rectangle, 4, white, 1, white);
//}

void GameScene::update(float dt){
    HScene::update(dt);
    if (m_game_logic) {
        m_game_logic->GameUpdate(dt);
        if (HWindowsManager::S()->hasWindowsShowed()) {
            if (m_game_logic->getGameState()== GAME_STATE_PLAY) {
                m_game_logic->setGameState(GAME_STATE_PAUSE);
            }
        }else{
            if (m_game_logic->getGameState() == GAME_STATE_PAUSE) {
                m_game_logic->setGameState(GAME_STATE_PLAY);
            }
        }
    }
}

//void GameScene::updateToolBtns(){
//    for (int i=0; i<MAX_TOOL_COUNT; i++) {
//        ToolInfo* info = (ToolInfo*)G::g_toolinfos->objectAtIndex(i);
//        if (toolwidget[i] != NULL) {
//            if (!info->new_showed&&G::g_game_mode==GAMEMODE_STAGE) {
//                continue;
//            }
//            UILabelBMFont* num = (UILabelBMFont*)toolwidget[i]->getChildByName("count");
//            IntToString(_num, info->getHoldCount());
//            num->setText(_num);
//            UIWidget* btn_add = toolwidget[i]->getChildByName("btn_add");
//            if (info->getHoldCount()<=0) {
//                btn_add->setVisible(true);
//            }else{
//                btn_add->setVisible(false);
//            }
//        }
//    }
//}

bool GameScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    if (!m_game_logic) {
        return false;
    }
     return m_game_logic->mTouchBegan(convertTouchToNodeSpaceAR(pTouch));
//	if((helpLayer->getChildrenCount()==0||HWindowsManager::S()->hasWindowsShowed())&&help_mask==NULL)
//		return false;
//    
//	CCPoint pos = convertTouchToNodeSpaceAR(pTouch);
//    
//	for(int i=0;i<BLOCK_NUM_H*BLOCK_NUM_W;i++){
//		CCPoint iPos = GetBlockPos(i);
//		iPos.x-=_pCenter.x;
//		iPos.y-=_pCenter.y;
//		CCRect rect = CCRectMake(iPos.x-BLOCK_WH/2,iPos.y-BLOCK_WH/2,BLOCK_WH,BLOCK_WH);
//		if(rect.containsPoint(pos)){
////			if(help_mask!=NULL){
////				HELP_INFO* help_info = (HELP_INFO*)GlobaData::shared()->help_infos->objectAtIndex(currentStage);
////				if(help_info->target_block_id != i)
////					return false;
////			}
//            
//			if(blocks_id[i]==BLOCK_GEM_START){
//				return false;
//			}
//            
//			if(selected_tool_id>=0){
//				UseTool(selected_tool_id,i);
//				return false;
//			}
//            
//			if(GetGemType(i)&GEM_BEHAVIOUR_NOMOVE||gems_id[i]==0)
//				return false;
//			selected_id = i;
//			return true;
//		}
//	}
//	return false;
}

void GameScene::ccTouchMoved(CCTouch *pTouch,CCEvent *pEvent){
    if (m_game_logic) {
        m_game_logic-> mTouchMoved(convertTouchToNodeSpaceAR(pTouch));
    }
//	if(selected_id == -1)
//		return;
//	CCPoint pos = convertTouchToNodeSpaceAR(pTouch);
//    
//	for(int i=0;i<BLOCK_NUM_H*BLOCK_NUM_W;i++){
//		CCPoint iPos = GetBlockPos(i);
//		iPos.x-=_pCenter.x;
//		iPos.y-=_pCenter.y;
//		CCRect rect = CCRectMake(iPos.x-BLOCK_WH/2,iPos.y-BLOCK_WH/2,BLOCK_WH,BLOCK_WH);
//		if(rect.containsPoint(pos)){
//			if(selected_id != i){
//				if(help_mask!=NULL){
//					HELP_INFO* help_info = (HELP_INFO*)G::g_help_infos->objectAtIndex(G::g_game_stage);
//					int t_id = 0;
//					int t_x = help_info->target_block_id%BLOCK_NUM_W;
//					int t_y = help_info->target_block_id/BLOCK_NUM_W;
//					switch(help_info->dir){
//                        case 0:
//                            t_y--;
//                            break;
//                        case 1:
//                            t_y++;
//                            break;
//                        case 2:
//                            t_x--;
//                            break;
//                        case 3:
//                            t_x++;
//                            break;
//					}
//					if((t_x>=0&&t_x<BLOCK_NUM_W)||(t_y>=0&&t_y<BLOCK_NUM_H)){
//						t_id = GetPosidByXY(t_x,t_y);
//					}
//                    
//					if(t_id != i)
//						return;
//				}
//                
//				if(GetGemType(i)&GEM_BEHAVIOUR_NOMOVE||blocks_id[i]==BLOCK_GEM_START||gems_id[i]==0)
//					return;
//                
//				if(selected_id == i+BLOCK_NUM_W||
//                   selected_id == i-BLOCK_NUM_W||
//                   selected_id==i-1||
//                   selected_id==i+1){
//                    ExChangeGem(selected_id,i);
//                    HIDE_HELP_MASK();
//				}
//				selected_id = -1;
//			}
//			break;
//		}
//	}
}

void GameScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
    if (m_game_logic) {
        m_game_logic->mTouchEnded(convertTouchToNodeSpaceAR(pTouch));
    }
}

//void GameScene::ScheduleGameThread(float dt){
//    if (isPreShow) {
//        return;
//    }
//	ScheduleBomb();
//	if(magicbox_flying_count>0)
//		return;
//	ScheduleCheckGemByTag();
//	ScheduleCheckGemsMoveOver();
//	ScheduleHelp();
//}
//
//void GameScene::ScheduleCheckGemsMoveOver(){
//	CCObject* obj;
//	CCARRAY_FOREACH(gemMoveOverArray,obj){
//		GemParams* param = (GemParams*)obj;
//		GameScene* scene = (GameScene*)param->scene;
//		if(scene->gems_id[param->pos_id] == 0)
//			continue;
//		if(param->id == GEM_COLOR_GOLD){
//			if(IsBottomBlock(param->pos_id)){
//				scene->Win_Condition_Add(8);
//				scene->PlayBottomOutAction(param->pos_id);
//                G::G_Add_Achievement_Complete(12);
//			}
//		}else
//			scene->CheckBomb(param->pos_id,scene->gems_id);
//	}
//	gemMoveOverArray->removeAllObjects();
//}
//
//void GameScene::ScheduleBomb(){
//	
//    
//	while(bombArray->count()>0){
//		if(bombArray->count()>3){
//			CCObject* o;
//			CCARRAY_FOREACH(bombArray,o){
//				GemParams* p = (GemParams*)o;
//				if(p->score<15&&p->score>0)
//					p->score = 15;
//			}
//		}
//		CCObject* obj;
//		CCArray* tmpBombArray = CCArray::create();
//		int currentCount = 0;
//		for(unsigned int i=0;i<bombArray->count();i++){
//			tmpBombArray->addObject(bombArray->objectAtIndex(i));
//			bombArray->removeObjectAtIndex(i);
//			i--;
//			if(++currentCount>=BOMB_MAX_COUNT)
//				break;
//		}
//        
//		int count = 0;
//        
//		CCARRAY_FOREACH(tmpBombArray,obj){
//			GemParams* param = (GemParams*)obj;
//			if(param->bombtype>=0){
//				if(blocks_id[param->pos_id]>=10){
//					ClearWall(param->pos_id);
//				}else{
//					if(Bomb(param->pos_id,param->id,param->bombtype)){
//						if(param->id/10 == GEM_BOMB_COLOREDWALL)
//							Win_Condition_Add(9);
//						else{
//							BombSpecialEffect(param->pos_id);
//							ClearColorWall(param->pos_id,param->id%10);
//							ShowScore(param->score,param->pos_id,0);
//						}
//					}
//				}
//			}else{
//				Bomb(param->pos_id,param->pre_id,0);
//				CREATE_GEM(param->id,param->pos_id);
//				BombSpecialEffect(param->pos_id);
//				ClearColorWall(param->pos_id,param->id%10);
//				ShowScore(param->score,param->pos_id,0);
//				//Win_Condition_Add(param->id%10-1);
//			}
//			count++;
//            if(!IsBonusTime&&!IsTaskOver)
//                achieve_count->bomb_count_single_move++;
//			//CCLOG("count %d,score %d",count,param->score);
//		}
//		
//		tmpBombArray->removeAllObjects();
//		CC_SAFE_DELETE(tmpBombArray);
//	}
//}
//
//void GameScene::SchedulePreBomb(float t){
//	if(magicbox_flying_count>0)
//		return;
//	if(bonusTime_count>0)
//		return;
//	if(gem_creating_count>0)
//		return;
//    
//	if(bombArray->count()==0){
//		for(unsigned int i=0;i<bombGemNodes->count();i++){
//			for(unsigned int j=0;j<bombGemNodes->count()-1-i;j++){
//				CCNode* node1 = (CCNode*)(bombGemNodes->objectAtIndex(j));
//				CCNode* node2 = (CCNode*)(bombGemNodes->objectAtIndex(j+1));
//				if(node1->getTag()>node2->getTag()){
//					bombGemNodes->exchangeObjectAtIndex(j,j+1);
//				}
//			}
//		}
//        /*
//         CCARRAY_FOREACH(bombGemNodes,obj){
//         CCNode* node = (CCNode*)obj;
//         CCLOG("---- %d",node->getTag());
//         }*/
//        
//		while(bombGemNodes->count()>0){
//			CCNode* node = (CCNode*)bombGemNodes->objectAtIndex(0);
//			if(node!=NULL){
//				int pos_id = node->getTag();
//				int id = gems_id[pos_id];
//				//CCLOG("bombGemNodes %d",pos_id);
//				gems_id[pos_id] = 0;
//				BeginBomb(new GemParams(pos_id,id,1));
//				Combo();
//				//bombGemNodes->removeObjectAtIndex(0);
//				break;
//			}
//			bombGemNodes->removeObjectAtIndex(0);
//		}
//		return;
//	}
//    
//}
//
//bool GameScene::Bomb(int pos_id,int id,int type){
//	if(pos_id == -1)
//		return false;
//	if(blocks_id[pos_id]==BLOCK_GEM_START)
//		return false;
//	if(id == 0){
//		if(gems_id[pos_id] == 0)
//			return false;
//		id = gems_id[pos_id];
//	}
//    
//	CLEAR_GEM(pos_id);
//    
//	if(id%10<7&&id/10!=GEM_BOMB_COLOREDWALL){
//        ShowPot(id%10,pos_id);
//		Win_Condition_Add(id%10-1);
//	}
//    
//    if((id>10&&id/10!=GEM_BOMB_COLOREDWALL)&&!IsTaskOver&&!IsBonusTime){
//        achieve_count->special_bomb_count_single_move++;
//    }
//    
//    if (id/10!=GEM_BOMB_COLOREDWALL) {
//         G::G_Add_Achievement_Complete(11);
//    }
//    
//	if(id>10){
//		int x = pos_id%BLOCK_NUM_W;
//		int y = pos_id/BLOCK_NUM_W;
//		switch(id/10){
//            case GEM_BOMB_V:
//                for(y =0;y<BLOCK_NUM_H;y++){
//                    BeginBomb(new GemParams(GetPosidByXY(x,y),gems_id[GetPosidByXY(x,y)],1,10));
//                }
//                type =1;
//                break;
//            case GEM_BOMB_H:
//                for(x =0;x<BLOCK_NUM_W;x++){
//                    BeginBomb(new GemParams(GetPosidByXY(x,y),gems_id[GetPosidByXY(x,y)],1,10));
//                    //Bomb(GetPosidByXY(x,y),gems_id[GetPosidByXY(x,y)],1);
//                }
//                type =1;
//                break;
//            case GEM_BOMB_AREA:{
//                int r = 2;
//                for(int i = 0;i <= r;i++){
//                    for(int j = 0;j<= r-i;j++){
//                        int id1 = GetPosidByXY(x+i,y+j);
//                        int id2 = GetPosidByXY(x-i,y+j);
//                        int id3 = GetPosidByXY(x-i,y-j);
//                        int id4 = GetPosidByXY(x+i,y-j);
//                        if(id1!=-1)
//                            BeginBomb(new GemParams(id1,gems_id[id1],2,10));
//                        if(id2!=-1)
//                            BeginBomb(new GemParams(id2,gems_id[id2],2,10));
//                        if(id3!=-1)
//                            BeginBomb(new GemParams(id3,gems_id[id3],2,10));
//                        if(id4!=-1)
//                            BeginBomb(new GemParams(id4,gems_id[id4],2,10));
//                    }
//                }
//                type = 2;
//            }
//                break;
//            case GEM_BOMB_VH:
//			{
//				for(int x1=0;x1< BLOCK_NUM_W;x1++){
//					BeginBomb(new GemParams(GetPosidByXY(x1,y),gems_id[GetPosidByXY(x1,y)],1,10));
//				}
//				for(int y1 = 0;y1<BLOCK_NUM_H;y1++){
//					BeginBomb(new GemParams(GetPosidByXY(x,y1),gems_id[GetPosidByXY(x,y1)],1,10));
//				}
//			}
//                break;
//            case GEM_BOMB_3H:
//			{
//				for(int y1=y-1;y1<=y+1;y1++){
//					if(y1<0)
//						continue;
//					if(y>=BLOCK_NUM_H)
//						continue;
//					for(int x1 = 0;x1<BLOCK_NUM_W;x1++){
//						BeginBomb(new GemParams(GetPosidByXY(x1,y1),gems_id[GetPosidByXY(x1,y1)],1,10));
//					}
//				}
//			}
//                break;
//            case GEM_BOMB_3V:
//			{
//				for(int x1=x-1;x1<=x+1;x1++){
//					if(x1<0)
//						continue;
//					if(x>=BLOCK_NUM_W)
//						continue;
//					for(int y1 = 0;y1<BLOCK_NUM_H;y1++){
//						BeginBomb(new GemParams(GetPosidByXY(x1,y1),gems_id[GetPosidByXY(x1,y1)],1,10));
//					}
//				}
//			}
//                break;
//            case GEM_BOMB_3AREA:
//			{
//				int r = 4;
//				for(int i = 0;i <= r;i++){
//					for(int j = 0;j<= r-i;j++){
//						int id1 = GetPosidByXY(x+i,y+j);
//						int id2 = GetPosidByXY(x-i,y+j);
//						int id3 = GetPosidByXY(x-i,y-j);
//						int id4 = GetPosidByXY(x+i,y-j);
//						if(id1!=-1)
//							BeginBomb(new GemParams(id1,gems_id[id1],2,10));
//						if(id2!=-1)
//							BeginBomb(new GemParams(id2,gems_id[id2],2,10));
//						if(id3!=-1)
//							BeginBomb(new GemParams(id3,gems_id[id3],2,10));
//						if(id4!=-1)
//							BeginBomb(new GemParams(id4,gems_id[id4],2,10));
//					}
//				}
//			}
//                break;
//            case GEM_BOMB_MAGIC:
//            case GEM_BOMB_MAGIC_H:
//            case GEM_BOMB_MAGIC_V:
//            case GEM_BOMB_MAGIC_NORMAL:
//            case GEM_BOMB_MAGIC_AREA:
//            case GEM_BOMB_2MAGIC:
//                BombMagicBox(id,pos_id);
//                return true;
//            case GEM_BOMB_COLOREDWALL:
//                id %=10;
//                break;
//		}
//	}
//    
//	if(type > 0){
//		CCSprite* back_effect = CCSprite::createWithSpriteFrameName("bomb_gem_special_bg.png");
//		back_effect->setPosition(GetBlockPos(pos_id));
//		gemBackLayer->addChild(back_effect);
//		back_effect->runAction(
//                               CCSequence::create(
//                                                  CCFadeOut::create(0.3f),
//                                                  CCCallFuncN::create(back_effect,callfuncN_selector(GameScene::DestroyOnEnded)),
//                                                  NULL
//                                                  )
//                               );
//	}
//    
//	CCSprite* bomb_effect = CCSprite::create();
//    
//    
//	CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
//    
//	CCAnimation* effect_anim = CCAnimation::create();
//	switch(type){
//        case 0:
//            for(int i=0;i<4;i++){
//                char animName[30];
//                sprintf(animName,"effect_bomb_0_%d.png",i);
//                effect_anim->addSpriteFrame(frameCache->spriteFrameByName(animName));
//            }
//            G::G_playEffect(RES_MUSIC_BOMB_0);
//            break;
//        case 1:
//            for(int i=0;i<8;i++){
//                char animName[30];
//                sprintf(animName,"effect_bomb_1_%d.png",i);
//                effect_anim->addSpriteFrame(frameCache->spriteFrameByName(animName));
//            }
//            G::G_playEffect(RES_MUSIC_BOMB_1);
//            break;
//        case 2:
//            //effect_anim->addSpriteFrame(frameCache->spriteFrameByName("effect_bomb_0_7.png"));
//            for(int i=1;i<8;i++){
//                char animName[30];
//                sprintf(animName,"effect_bomb_1_%d.png",i);
//                effect_anim->addSpriteFrame(frameCache->spriteFrameByName(animName));
//            }
//            G::G_playEffect(RES_MUSIC_BOMB_2);
//            break;
//	}
//	if(effect_anim->getFrames()->count()==0)
//		return false;
//    
//	effect_anim->setDelayPerUnit(0.1f);
//    
//	CCAnimate* effect_animate = CCAnimate::create(effect_anim);
//    
//	CCActionInterval* effect_action = (CCActionInterval*)(CCSequence::create(
//                                                                             effect_animate,
//                                                                             CCCallFuncN::create(bomb_effect,callfuncN_selector(GameScene::DestroyOnEnded)),
//                                                                             NULL
//                                                                             ));
//    
//	CCSprite* bomb_gem = CCSprite::createWithSpriteFrameName("gem_1.png");
//    
//	CCAnimation* bomb_gem_anim = CCAnimation::create();
//	for(int i=0;i<5;i++){
//		char b[30];
//		sprintf(b,"bomb_gem_%d_%d.png",id%10,i);
//		bomb_gem_anim->addSpriteFrame(frameCache->spriteFrameByName(b));
//	}
//    
//	
//    
//	bomb_gem_anim->setDelayPerUnit(0.05f);
//	CCAnimate* bomb_gem_animate = CCAnimate::create(bomb_gem_anim);
//    
//	CCActionInterval* bomb_gem_action = (CCActionInterval*)(CCSequence::create(
//                                                                               bomb_gem_animate,
//                                                                               CCCallFuncN::create(bomb_gem,callfuncN_selector(GameScene::DestroyOnEnded)),
//                                                                               NULL
//                                                                               ));
//    
//    
//    
//	bomb_effect->setPosition(GetBlockPos(pos_id));
//	gemFrontLayer->addChild(bomb_effect,3);
//	bomb_effect->runAction(effect_action);
//	bomb_effect->setTag(pos_id);
//    
//	bomb_gem->setPosition(GetBlockPos(pos_id));
//	gemLayer->addChild(bomb_gem);
//	bomb_gem->runAction(bomb_gem_action);
//	bomb_gem->setTag(pos_id);
//	return true;
//}
//
//void GameScene::ShowPot(int color_id,int pos_id){
//    if (IsTaskOver) {
//        return;
//    }
//    
//    if (IsBonusTime) {
//        return;
//    }
//    
//	char potName[20];
//    
//    if (color_id==7) {
//        return;
//    }
//    
//    if (win_conditions[color_id-1]==0) {
//        return;
//    }
//    
//	sprintf(potName,"game/pot_%d.png",color_id);
//    CCPoint targetPos = ccp(_pLeft+72,_pTop-160);
//    if (label_win_conditions[color_id-1]!=NULL) {
//        targetPos = G::getWorldPosition(label_win_conditions[color_id-1]);
//    }
//	
//	for(int i=0;i<3;i++){
//		CCSprite* pot = CCSprite::create(potName);
//		CCPoint pos = GetBlockPos(pos_id);
//		pos.x += -20 + t_getRandom(40);
//		pos.y += -20 + t_getRandom(40);
//		pot->setPosition(pos);
//		scoreLayer->addChild(pot);
//		MoveWithParabola(pot,pos,targetPos,i*0.05f,0.7f);
//	}
//}
//
//
//void GameScene::ScheduleCheckGemByTag(){
//	for(int i=BLOCK_NUM_WH-1;i>=0;i--){
//		CCNode* gem = gemLayer->getChildByTag(i);
//		if(gem == NULL)
//			continue;
//        
//		if(gems_id[i]>0){
//			CheckGemMove(i);
//		}
//	}
//}
//
//void GameScene::ScheduleHelp(){
//    
//    if(help_mask!=NULL){
//		return;
//	}
//    if (help_step == 0) {
//        SHOW_HELP_MASK();
//        return;
//    }
//    
//    if(IsOnPlaying())
//		return;
//    
//    if (HWindowsManager::S()->hasWindowsShowed()) {
//        return;
//    }
//    
//    if (help_step == 1) {
//        SHOW_HELP_TIPS();
//        return;
//    }
//
//    
//    if (!pre_clock_isShowed) {
//        if (G::g_game_mode == GAMEMODE_HOLE) {
//            GameReady::show(m_layer,new GameReadyModeParam(MODE_TIME));
//            pre_clock_isShowed = true;
//            return;
//        }
//        if(lose_conditions[0]>0){
//            GameReady::show(m_layer,new GameReadyModeParam(MODE_TIME));
//        }else{
//            GameReady::show(m_layer,new GameReadyModeParam(MODE_STEP));
//        }
//        pre_clock_isShowed = true;
//        return;
//    }
//    
//	
//    
//    
//	if(helpLayer->getChildrenCount()>0)
//		return;
//	
//	if(IsBonusTime){
//		StartBonusTime();
//		return;
//	}
//	if(bonusTime_count>0)
//		return;
//    
//	if(bombGemNodes->count()>0)
//		return;
//	
//	if(win_or_lose == 1){
//        if (!game_result_showed) {
//            GameWin* game_win =  GameWin::show(m_layer,new GameWinParam(currentScore));
//            game_win->addHomeEvent(this, h_voidcallback(GameScene::ReturnHome));
//            game_win->addRetryEvent(this, h_voidcallback(GameScene::Retry));
//            game_win->addNextEvent(this, h_voidcallback(GameScene::NextStage));
//            game_result_showed = true;
//            checkAchievement();
//        }
//        
//		//SHOW_WIN_TIPS();
//		unschedule(schedule_selector(GameScene::SchedulePreBomb));
//		unschedule(schedule_selector(GameScene::ScheduleGameThread));
//		return;
//	}
//    
//	if(win_or_lose == -1){
//		if(Win_Condition_Finished()){
//			TaskFinished();
//			//unschedule(schedule_selector(GameScene::UpdateConditions));
//			win_or_lose = 1;
//			return;
//		}
//	}
//    
//    if (isUnLimitedMode()) {
//        if (checkRise()) {
//            return;
//        }
//    }
//    
//    
//	if(!HasGold()&&has_gold&&win_conditions_now[8]<win_conditions[8])
//		to_create_gold = true;
//	
//	for(int i=0;i<BLOCK_NUM_WH;i++){
//		int x = i%BLOCK_NUM_W;
//		int y = i/BLOCK_NUM_W;
//		if(x+1<BLOCK_NUM_W){
//			if(CanExChange(i,GetPosidByXY(x+1,y),false)){
//				ShowHelp(i,GetPosidByXY(x+1,y));
//				return;
//			}
//		}
//		if(y+1<BLOCK_NUM_H){
//			if(CanExChange(i,GetPosidByXY(x,y+1),false)){
//				ShowHelp(i,GetPosidByXY(x,y+1));
//				return;
//			}
//		}
//	}
//    
//	RePositionGems();
//}
//
//void GameScene::ClearColorWall(int pos_id,int color)
//{
//    int x = pos_id%BLOCK_NUM_W;
//    int y = pos_id/BLOCK_NUM_W;
//    for(int x1 = x-1;x1<=x+1;x1++){
//        for(int y1 = y-1;y1<=y+1;y1++){
//            if(x1 == x || y1== y){
//                int p_id = GetPosidByXY(x1,y1);
//                if(gems_id[p_id]/10 == GEM_BOMB_COLOREDWALL){
//                    if(gems_id[p_id]%10 == color){
//                        BeginBomb(new GemParams(p_id,gems_id[p_id],0,0));
//                        //Win_Condition_Add(9);
//                    }
//                }
//            }
//        }
//    }
//    
//}
//
//void GameScene::ClearWall(int pos_id){
//    if (pos_id==-1) {
//        return;
//    }
//	if(blocks_id[pos_id]<10)
//		return;
//	CCNode* node = blockLayer->getChildByTag(pos_id);
//	if(node == NULL)
//		return;
//	if(node->numberOfRunningActions()>0)
//		return;
//	node->removeFromParentAndCleanup(true);
//    
//    
//    if (isUnLimitedMode()) {
//        showUnlimitScore(blocks_id[pos_id], pos_id);
//    }
//    
//	if(blocks_id[pos_id]-BLOCK_WALL == BLOCK_ICE&&!isUnLimitedMode()){
//		CCSprite* tmpIceSprite = CCSprite::createWithSpriteFrameName("ice.png");
//		blockLayer->addChild(tmpIceSprite);
//		tmpIceSprite->setPosition(GetBlockPos(pos_id));
//		tmpIceSprite->setTag(pos_id+100);
//	}
//    
//	CCAnimation* wall_bomb_anim = CCAnimation::create();
//    if (blocks_id[pos_id]>=BLOCK_HOLE_WALL&&blocks_id[pos_id]<=BLOCK_HOLE_MID_3) {
//        for(int i=0;i<5;i++){
//            char name[20];
//            int a_id =blocks_id[pos_id]-BLOCK_HOLE_WALL;
//            if (a_id==0) {
//                a_id =1;
//            }
//            sprintf(name,"u%d_%d.png",a_id,i);
//            wall_bomb_anim->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name));
//        }
//    }else{
//        for(int i=0;i<7;i++){
//            char name[20];
//            sprintf(name,"bomb_wall_%d.png",i);
//            wall_bomb_anim->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name));
//        }
//    }
//	wall_bomb_anim->setDelayPerUnit(0.05f);
//    
//	CCAnimate* wall_bomb_animate = CCAnimate::create(wall_bomb_anim);
//    
//	CCSprite* wall_effect = CCSprite::createWithSpriteFrameName("bomb_wall_0.png");
//	wall_effect->setTag(pos_id);
//	blockLayer->addChild(wall_effect);
//	wall_effect->setPosition(GetBlockPos(pos_id));
//	wall_effect->runAction(
//                           CCSequence::create(
//                                              wall_bomb_animate,
//                                              CCCallFuncND::create(this,callfuncND_selector(GameScene::CallBackBlockClearOver),this),
//                                              NULL
//                                              )
//                           );
//	Win_Condition_Add(7);
//    G::G_playEffect (RES_MUSIC_WALL_BLOCK);
//}
//
//void GameScene::ClearIce(int pos_id){
//	if(blocks_id[pos_id]!=2)
//		return;
//	CCNode* node = blockLayer->getChildByTag(pos_id);
//	if(node == NULL)
//		return;
//	if(node->numberOfRunningActions()>0)
//		return;
//	node->runAction(CCSequence::create(
//                                       CCMoveBy::create(0.4f,ccp(0,-30)),
//                                       CCCallFuncND::create(node,callfuncND_selector(GameScene::CallBackBlockClearOver),this),
//                                       NULL
//                                       ));
//	node->runAction(CCFadeOut::create(0.4f));
//	Win_Condition_Add(6);
//	G::G_playEffect(RES_MUSIC_ICE_BLOCK);
//}
//
//void GameScene::CallBackBlockClearOver(CCNode* sender,void* scene){
//	GameScene* gameS = (GameScene*)scene;
//	int pos_id = sender->getTag();
//	if(gameS->blocks_id[pos_id]/10 == BLOCK_WALL/10&&!isUnLimitedMode()){
//		sender->removeFromParentAndCleanup(true);
//		gameS->blocks_id[pos_id] -= BLOCK_WALL;
//		if(gameS->blocks_id[pos_id]== BLOCK_ICE){
//			CCSprite* iceSprite = CCSprite::createWithSpriteFrameName("ice.png");
//			blockLayer->addChild(iceSprite);
//			iceSprite->setPosition(GetBlockPos(pos_id));
//			iceSprite->setTag(pos_id);
//			CCNode* node = gameS->blockLayer->getChildByTag(pos_id+100);
//			if(node!=NULL)
//				node->removeFromParentAndCleanup(true);
//		}
//	}else{
//		sender->removeFromParentAndCleanup(true);
//		gameS->blocks_id[pos_id] = 1;
//	}
//}


void GameScene::loadResource(){
    HScene::loadResource();
    //addTextureName("game/Blocks.pvr.czz");
    //addTextureName("game/Gems.pvr.czz");
    addTextureName("game/game_bg.jpg");
    //addTextureName("game/special_bomb_effect.pvr.czz");
//    addTextureName("hole/score_label.png");
//    addTextureName("hole/middle.jpg");
//    addTextureName("hole/top.jpg");
//    addTextureName("hole/bottom.jpg");
}

void GameScene::ReleaseResource(){
    HScene::ReleaseResource();
    //releaseTexture("game/Blocks.pvr.czz");
    //releaseTexture("game/Gems.pvr.czz");
    releaseTexture("game/game_bg.jpg");
    //releaseTexture("game/special_bomb_effect.pvr.czz");
//    releaseTexture("hole/score_label.png");
//    releaseTexture("hole/middle.jpg");
//    releaseTexture("hole/top.jpg");
//    releaseTexture("hole/bottom.jpg");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("Gems.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("Blocks.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("normal_bomb_effect.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("special_bomb_effect.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("block_bomb_effect.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("game/border.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("game/gem.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("game/arrow_anim.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("game/effect_bomb_0.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("game/effect_bomb_1.plist");
}


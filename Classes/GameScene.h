//
//  GameScene.h
//  Bejeweled
//
//  Created by wilford on 14-1-5.
//
//

#ifndef __Bejeweled__GameScene__
#define __Bejeweled__GameScene__

#include "HScene.h"
#include "HTools.h"
#include "GameLose.h"
#include "GameWin.h"
#include "GameReady.h"
#include "GamePause.h"
#include "ToolBuy.h"
#include "GameStart.h"
#include "GameStartShow.h"
#include "HoleModeShow.h"
#include "SeaModeShow.h"
#include "NormalTips.h"
#include "GameHelp.h"
#include "GameHelpMaskTips.h"
#include "HoleModeResult.h"
#include "SeaModeResult.h"
#include "GameQuit.h"
#include "GameLogic.h"
#include "GameEndBuy.h"
#include "support/zip_support/ZipUtils.h"





class GameScene : public HScene,public cocos2d::CCTouchDelegate,public cocos2d::CCKeypadDelegate{
public:
	virtual void onEnter();
	virtual void onExit();
	CREATE_FUNC(GameScene);
    
    virtual void loadResource();
	virtual void ReleaseResource();
    
    virtual void update(float dt);
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch,CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void keyBackClicked() {
//        if (!HWindowsManager::S()->hasWindowsShowed()) {
//            changeScene(M_SCENE_MAIN);
//        }
        if (m_game_logic) {
            if (!m_game_logic->isInCustomTime()) {
                return;
            }
        }
        GameQuit::show(m_layer);
    }
    
    void ReturnHome(){
        changeScene(M_SCENE_MAIN);
    }
    
    void Retry(){
        switch (G::g_game_mode) {
            case GAMEMODE_STAGE:
            {
                GameStartShow* game_start_show = GameStartShow::show(m_layer);
                game_start_show->addGameStartEvent(this, h_voidcallback(GameScene::ReOpenGame));
                game_start_show->addCloseEvent(this, h_voidcallback(GameScene::ReturnHome));
            }
                break;
            case GAMEMODE_HOLE:
            {
                HoleModeShow* hole_show = HoleModeShow::show(m_layer);
                hole_show->addGameStartEvent(this, h_voidcallback(GameScene::ReOpenGame));
                hole_show->addCloseEvent(this, h_voidcallback(GameScene::ReturnHome));
            }
                break;
            case GAMEMODE_SEA:
            {
                SeaModeShow* sea_show = SeaModeShow::show(m_layer);
                sea_show->addGameStartEvent(this, h_voidcallback(GameScene::ReOpenGame));
                sea_show->addCloseEvent(this, h_voidcallback(GameScene::ReturnHome));
            }
                break;
            default:
                break;
        }
       
    }
    
    void NextStage(){
        int next_stage = G::g_game_stage+1;
        if (next_stage>= MAX_STAGE) {
            ReturnHome();
            return;
        }
        G::G_loadGameMap(GAMEMODE_STAGE,next_stage);
        GameStartShow* game_start_show = GameStartShow::show(m_layer);
        game_start_show->addGameStartEvent(this, h_voidcallback(GameScene::ReOpenGame));
        game_start_show->addCloseEvent(this, h_voidcallback(GameScene::ReturnHome));
    }
    
    void ReOpenGame(){
        changeScene(M_SCENE_GAME);
    }
    
    void ShowGameWin(int score){
        GameWin* game_win =  GameWin::show(m_layer,new GameWinParam(score));
        game_win->addHomeEvent(this, h_voidcallback(GameScene::ReturnHome));
        game_win->addRetryEvent(this, h_voidcallback(GameScene::Retry));
        game_win->addNextEvent(this, h_voidcallback(GameScene::NextStage));
    }
    
    void ShowGameLose(){
        GameLose* game_lose = GameLose::show(m_layer);
        game_lose->addHomeEvent(this, h_voidcallback(GameScene::ReturnHome));
        game_lose->addRetryEvent(this, h_voidcallback(GameScene::Retry));
        game_lose->addNextStageEvent(this, h_voidcallback(GameScene::NextStage));
    }
    
    void ShowToolBuy(int id,int count){
        ToolBuy::show(m_layer,new ToolBuyParam(id,count));
    }
    
    void ShowNormalTips(int tips_id){
        NormalTips::show(m_layer,new NormalTipsParam(tips_id));
    }
    
    void ShowGamePause(){
         G::G_playEffect(RES_MUSIC_NORMAL_CLICK);
        GamePause* game_pause = GamePause::show(m_layer);
        game_pause->addHomeEvent(this, h_voidcallback(GameScene::ReturnHome));
        game_pause->addRetryEvent(this, h_voidcallback(GameScene::Retry));
    }
    
    void ShowGameReady(GAMEMODE_TYPE mode){
        GameReady::show(m_layer,new GAMEMODE_TYPE(mode));
    }
    
    void ShowHoleResult(int hole_score,int hole_m){
        HoleModeResult* hole_result =  HoleModeResult::show(m_layer,new HoleModeResultParam(hole_score,hole_m));
        hole_result->addHomeEvent(this, h_voidcallback(GameScene::ReturnHome));
        hole_result->addRestartEvent(this, h_voidcallback(GameScene::Retry));
    }
    
    void ShowSeaResult(int hurt,int max_blood){
        SeaModeResult* sea_result =  SeaModeResult::show(m_layer,new SeaModeResultParam(hurt,max_blood));
        sea_result->addHomeEvent(this, h_voidcallback(GameScene::ReturnHome));
        sea_result->addRestartEvent(this, h_voidcallback(GameScene::Retry));
    }
    
    void showGameEndBuy(CCObject* target,SEL_VOIDCALLBACK gameEndSelector,SEL_VOIDCALLBACK gameContinueSelector){
        GameEndBuy* game_end_buy = GameEndBuy::show(m_layer);
        game_end_buy->addLoseListener(target, gameEndSelector);
        game_end_buy->addContinueListener(target, gameContinueSelector);
    }
    
//private:
//    void initParams();
//    void initSpriteFrames();
//    void initData();
//    void initLayers();
//    void initUI();
//    void drawHoleBackground();
//    void drawBackground();
//    void drawBorder();
//    void DrawBorder(int pos_id,int corner,int flag = -1);
//    void initGems();
//    void clip(CCPoint _center,float wh);
//    
//    void ScheduleBomb();
//	void ScheduleCheckGemByTag();
//	void ScheduleHelp();
//	void ScheduleCheckGemsMoveOver();
//    
//	void SchedulePreBomb(float t);
//	void ScheduleGameThread(float t);
//    
//    CCPoint GetBlockPos(int x,int y){return GetBlockPos(GetPosidByXY(x,y));}
//	CCPoint GetBlockPos(int pos_id);
//    
//    bool IsSpaceBlock(int x,int y){
//        int pos_id = GetPosidByXY(x,y);
//        return IsSpaceBlock(pos_id);
//    }
//    
//    bool IsSpaceBlock(int pos_id){
//        return blocks_id[pos_id] == BLOCK_SPACE||
//        blocks_id[pos_id] == BLOCK_HOLE||
//        blocks_id[pos_id] == BLOCK_GEM_START;
//    }
//    
//    int GetPosidByXY(int x,int y){
//        if(x<0||x>=BLOCK_NUM_W)
//            return -1;
//        if(y<0||y>=BLOCK_NUM_H)
//            return -1;
//        return x+y*BLOCK_NUM_W;
//    }
//    
//    bool IsBottomBlock(int pos_id){
//        for(int i=pos_id+BLOCK_NUM_W;i<BLOCK_NUM_WH;i+=BLOCK_NUM_W){
//            if(blocks_id[i]>0){
//                return false;
//            }
//        }
//        return true;
//    }
//    
//    void Win_Condition_Add(int condition_id,int num = 1){
//		if(condition_id<0||condition_id>=MAX_WIN_CONDITIONS){
//			return;
//		}
//		win_conditions_now[condition_id]+=num;
//		for(int i=0;i<MAX_WIN_CONDITIONS;i++){
//            if(win_conditions_now[i]>win_conditions[i])
//                win_conditions_now[i] = win_conditions[i];
//		}
//	}
//    
//	bool Win_Condition_Finished(){
//		bool isAllZero = true;
//		for(int i=0;i< MAX_WIN_CONDITIONS ;i++){
//			if(win_conditions[i]!=0)
//				isAllZero = false;
//		}
//		if(isAllZero)
//			return false;
//        
//		for(int i=0;i<MAX_WIN_CONDITIONS;i++){
//			if(win_conditions_now[i]<win_conditions[i])
//				return false;
//		}
//		return true;
//	}
//    
//	void Lose_Condition_Add(int condition_id,float num = 1){
//		if(condition_id<0||condition_id>=MAX_LOSE_CONDITIONS)
//			return;
//        
//        float pre =lose_conditions_now[condition_id];
//		lose_conditions_now[condition_id]-=num;
//        if (condition_id == 1&&!IsTaskOver&&!IsBonusTime) {
////            if(lose_conditions_now[condition_id]==5){
////                UIWidget* btn = GameControllerLayer->getWidgetByName("BTN_TOOL_BG_02");
////                if (btn!=NULL) {
////                    btn->runAction(CCRepeatForever::create(CCSequence::create(CCScaleTo::create(0.4f, 1.3f),CCScaleTo::create(0.4f, 1),NULL)));
////                }
////                
////            }
//        }
//        if (condition_id == 0&&!IsTaskOver&&!IsBonusTime) {
////            if(lose_conditions_now[condition_id]<21&&pre>=21){
////                UIWidget* btn = GameControllerLayer->getWidgetByName("BTN_TOOL_BG_00");
////                if (btn!=NULL) {
////                    btn->runAction(CCRepeatForever::create(CCSequence::create(CCScaleTo::create(0.4f, 1.3f),CCScaleTo::create(0.4f, 1),NULL)));
////                }
////            }
//        }
//        
//		if(Lose_Condition_Finished()&&helpLayer->getChildrenCount()>0){
//			win_or_lose = 0;
//			ClearHelp();
//            if (!game_result_showed) {
//                GameLose* game_lose = GameLose::show(m_layer);
//                game_lose->addHomeEvent(this, h_voidcallback(GameScene::ReturnHome));
//                game_lose->addRetryEvent(this, h_voidcallback(GameScene::Retry));
//                game_result_showed = true;
//                checkAchievement();
//            }
//            
//			//unschedule(schedule_selector(GameScene::UpdateConditions));
//			unschedule(schedule_selector(GameScene::SchedulePreBomb));
//			unschedule(schedule_selector(GameScene::ScheduleGameThread));
//		}
//		for(int i=0;i<MAX_LOSE_CONDITIONS;i++){
//            if(lose_conditions_now[i]<0)
//                lose_conditions_now[i] = 0;
//		}
//	}
//    
//	bool Lose_Condition_Finished(){
//		for(int i=0;i<MAX_LOSE_CONDITIONS;i++){
//			if(lose_conditions[i]>0){
//				if(lose_conditions_now[i]<=0)
//					return true;
//			}
//		}
//		return false;
//	}
//    
//	void ADD_SCORE(int score){
//		currentScore+=score;
//		Win_Condition_Add(MAX_WIN_CONDITIONS-1,score);
//	}
//    
//    void ClearHelp(){
//		helpLayer->removeAllChildrenWithCleanup(true);
//	}
//    
//    void PlayBottomOutAction(int pos_id){
//        //GlobaData::shared()->ADD_ACHIEVEMENT_COMPLETE(12);
//        CCNode* gem = gemLayer->getChildByTag(pos_id);
//        CCNode* gemBack = gemBackLayer->getChildByTag(pos_id);
//        CCNode* gemFront = gemFrontLayer->getChildByTag(pos_id);
//        CCPoint pos = GetBlockPos(pos_id);
//        CCPoint targetPos = ccp(_pLeft+100,_pTop-100);
//        if (label_win_conditions[8]!=NULL) {
//            targetPos = G::getWorldPosition(label_win_conditions[8]);
//        }
//        if(gem!=NULL){
//            gem->setTag(-1);
//            gem->setZOrder(200);
//            MoveWithParabola((CCSprite*)gem,pos,targetPos,0,0.7f);
//        }
//        
//        if(gemBack!=NULL){
//            gemBack->setTag(-1);
//            gemBack->setZOrder(200);
//            MoveWithParabola((CCSprite*)gemBack,pos,targetPos,0,0.7f);
//        }
//        
//        if(gemFront!=NULL){
//            gemFront->setTag(-1);
//            gemFront->setZOrder(200);
//            MoveWithParabola((CCSprite*)gemFront,pos,targetPos,0,0.7f);
//        }
//        
//        schedule(schedule_selector(GameScene::PlayBottomOutEffect),0.6f);
//        
//    }
//    
//    void PlayBottomOutEffect(float dt){
//        G::G_playEffect (RES_MUSIC_GOLD_OUT);
//        unschedule(schedule_selector(GameScene::PlayBottomOutEffect));
//    }
//    
//    void MoveWithParabola(CCSprite* mSprite,CCPoint startPoint, CCPoint endPoint, float delayTime,float time){
//        float sx = startPoint.x;
//        float sy = startPoint.y;
//        float ex = startPoint.x+600;
//        float ey = startPoint.y+400;
//        
//        int h = mSprite->getContentSize().height*0.5;
//        ccBezierConfig bezier;
//        bezier.controlPoint_1 = ccp(sx, sy);
//        bezier.controlPoint_2 = ccp(sx+(ex-sx)*0.5, sy+(ey-sy)*0.5);
//        bezier.endPosition = ccp(endPoint.x-30, endPoint.y+h);
//        CCBezierTo *actionMove = CCBezierTo::create(time,bezier);//actionWithDuration(time,bezier);//(time bezier:bezier];
//        mSprite->runAction(
//                           CCSequence::create(
//                                              CCDelayTime::create(delayTime),
//                                              actionMove,
//                                              CCCallFuncN::create(mSprite,callfuncN_selector(GameScene::DestroyOnEnded)),
//                                              NULL
//                                              )
//                           );
//    }
//    
//    void DestroyOnEnded(CCNode* sender){
//        sender->removeFromParentAndCleanup(true);
//    }
//
//    
//    void removeSameColor(int color,int* colors,int* len);
//
//    void CLEAR_GEM(int pos_id);
//	void CREATE_GEM(int id,int pos_id,bool BombAfterCreate = false);
//    void CallBackCreateEffectOver(CCNode* sender,void* gemParam);
//	void CallBackCreateEffectOverAndBomb(CCNode* sender,void* gemParam);
//
//    
//    int GetGemType(int x,int y){return GetGemType(GetPosidByXY(x,y));}
//	int GetGemType(int pos_id);
//    int GetBlockType(int x,int y){return GetBlockType(GetPosidByXY(x,y));}
//    int GetBlockType(int pos_id);
//    bool CheckGemMove(int pos_id);
//    void StartMoveGem(int fromtag,int totag,float speed = 0,bool moveOverShowEffect = true);
//    void CheckBomb(int pos_id,int* gems_id);
//    void Combo();
//	void SHOW_COMBO_STR(int id);
//	void BeginBomb(GemParams* param);
//    void CallBackGemMovedOver(CCNode* sender,void* gemParam);
//    void MoveOverEffect(int pos_id);
//    
//    void BombSpecialEffect(int pos_id){
//        int x = pos_id%BLOCK_NUM_W;
//        int y = pos_id/BLOCK_NUM_W;
//        for(int x1 = x-1;x1<=x+1;x1++){
//            for(int y1 = y-1;y1<=y+1;y1++){
//                if(x1 == x&& y1 == y){
//                    ClearIce(GetPosidByXY(x1,y1));
//                }else if(x1 == x || y1== y){
//                    ClearWall(GetPosidByXY(x1,y1));
//                }
//            }
//        }
//    }
//    
//    bool Bomb(int pos_id,int id,int type);
//    void ShowPot(int color_id,int pos_id);
//    
//    void BombMagicBox(int id,int pos_id);
//    
//    void CallBackMagicBoxMoveOver(CCNode* sender,void* gemParam);
//    
//    bool IsOnPlaying(){
//        for(int i=0;i<BLOCK_NUM_WH;i++){
//            CCNode* gem = gemLayer->getChildByTag(i);
//            if(gem!=NULL){
//                if(gem->numberOfRunningActions()>0)
//                    return true;
//            }
//        }
//        if(bombArray->count()>0)
//            return true;
//        if(bombGemNodes->count()>0)
//            return true;
//        return false;
//    }
//    
//    bool HasGold(){
//		for(int i=0;i<BLOCK_NUM_WH;i++){
//			if(gems_id[i]==GEM_COLOR_GOLD){
//				return true;
//			}
//		}
//		return false;
//	}
//    
//    void RePositionGems();
//
//    
//    void ClearColorWall(int pos_id,int color);
//    void ClearWall(int pos_id);
//    void ClearIce(int pos_id);
//    void CallBackBlockClearOver(CCNode* sender,void* scene);
//    
//    void TaskFinished();
//    
//    void StartBonusTime();
//    
//    void CallBackBonusTrailReached(CCNode* sender,void* gemParam);
//
//    int CanExChange(int id1,int id2,bool isDo);
//    bool CheckCanBom(int pos_id,int pre_id);
//    void ExChangeGem(int id1,int id2);
//    
//    void GemMoveToAndBack(int fromid,int toid);
//    
//    void ShowHelp(int id1,int id2);
//    
//    void UpdateConditions(float dt);
//    
//    bool isUnLimitedMode(){
//        return G::g_game_mode == GAMEMODE_HOLE;
//    }
//    
//    void ON_BACK_MAIN_CLICK(CCObject* sender);
//    
//    void ShowScore(int score,int pos_id,int type){
//        if (isUnLimitedMode()) {
//            return;
//        }
//        if(score <= 0)
//            return;
//        score *= score_rate;
//        achieve_count->score_last_light+=score;
//        ADD_SCORE(score);
//        CCLabelAtlas* numAtlas = CCLabelAtlas::create("","game/score_num_blue.png",26,35,'0');
//        char num[20];
//        sprintf(num,"%d",score);
//        numAtlas->setString(num);
//        scoreLayer->addChild(numAtlas);
//        numAtlas->setPosition(GetBlockPos(pos_id));
//        numAtlas->runAction(
//                            CCSequence::create(
//                                               CCMoveBy::create(0.5f,ccp(0,30)),
//                                               CCCallFuncN::create(numAtlas,callfuncN_selector(GameScene::DestroyOnEnded)),
//                                               NULL
//                                               )
//                            );
//    }
//    
//    
//    void OnControllerButtonClicked(CCObject* sender);
//    
//    void UseTool(int tool_id,int pos_id);
//    
//    bool MagicTool(int pos_id);
//    
//    bool BombTool(int pos_id);
//    
//    
//    void ReturnHome(){
//        changeScene(M_SCENE_MAIN);
//    }
//    
//    void Retry(){
//        GameStart* game_start = GameStart::show(m_layer);
//        game_start->addGameStartEvent(this, h_voidcallback(GameScene::ReOpenGame));
//        game_start->addCloseEvent(this, h_voidcallback(GameScene::ReturnHome));
//    }
//    
//    void NextStage(){
//        int next_stage = G::g_game_stage+1;
//        if (next_stage>= MAX_STAGE) {
//            ReturnHome();
//            return;
//        }
//        G::G_loadGameMap(GAMEMODE_STAGE,next_stage);
//        GameStart* game_start = GameStart::show(m_layer);
//        game_start->addGameStartEvent(this, h_voidcallback(GameScene::ReOpenGame));
//        game_start->addCloseEvent(this, h_voidcallback(GameScene::ReturnHome));
//    }
//    
//    void ReOpenGame(){
//        changeScene(M_SCENE_GAME);
//    }
//    
//    void InitCombo(){
//        CCLayer* comboLayer = CCLayer::create();
//        this->addChild(comboLayer,20);
//        comboLayer->setPosition(ccp(_pRight-160-_pCenter.x,_pTop-50-_pCenter.y));
//        combo_label_sprite = CCSprite::create("game/combo_label.png");
//        comboLayer->addChild(combo_label_sprite);
//        combo_label_sprite->setPosition(ccp(_pCenter.x+(70-26)/2,_pCenter.y));
//        combo_label_sprite->setAnchorPoint(_nRight);
//        combo_num = CCLabelAtlas::create("1","game/score_num_green.png",26,35,'0');
//        comboLayer->addChild(combo_num);
//        combo_num->setPosition(ccp(_pCenter.x+(70-26)/2,_pCenter.y));
//        combo_num->setAnchorPoint(_nLeft);
//        comboLayer->setVisible(false);
//        combo_score_num = CCLabelAtlas::create("1000","game/score_num_green.png",26,35,'0');
//        this->addChild(combo_score_num,21);
//        combo_score_num->setAnchorPoint(_nCenter);
//        combo_score_num->setVisible(false);
//        combo = 0;
//    }
//    
//    void ToolOpenAnim(UIWidget* tool,float delay){
//        UIWidget* lock = tool->getChildByName("lock");
//        UIWidget* count_bg = tool->getChildByName("count_bg");
//        UIWidget* icon = tool->getChildByName("tool_icon");
//        icon->setVisible(true);
//        lock->setVisible(true);
//        icon->setScale(0);
//        icon->runAction(CCSequence::create(CCDelayTime::create(0.4f+delay),CCScaleTo::create(0.4f, 0.8f),NULL));
//        icon->runAction(CCSequence::create(CCDelayTime::create(0.4f+delay),CCRotateBy::create(0.4f, 360),NULL));
//        lock->runAction(CCSequence::create(CCDelayTime::create(delay),CCRotateBy::create(1.0f, 360),NULL));
//        lock->runAction(CCSequence::create(CCDelayTime::create(delay),CCScaleTo::create(1.0f, 0),NULL));
//        count_bg->runAction(CCSequence::create(CCDelayTime::create(1.0f+delay),CCShow::create(),NULL));
//    }
//    
//    void initBlockOffset(){
//        float minX = 0;
//        float minY = 0;
//        float maxX = 0;
//        float maxY = 0;
//        bool first = true;
//        for (int i=0; i<BLOCK_NUM_WH; i++) {
//            if (blocks_id[i]>0) {
//                CCPoint pos = GetBlockPos(i);
//                if (first) {
//                    minX = pos.x;
//                    minY = pos.y;
//                    maxX = pos.x;
//                    maxY = pos.y;
//                    first = false;
//                }else{
//                    minX = MIN(minX,pos.x);
//                    minY = MIN(minY,pos.y);
//                    maxX = MAX(maxX,pos.x);
//                    maxY = MAX(maxY,pos.y);
//                }
//            }
//        }
//        CCPoint _center = ccp((maxX+minX)/2,(minY+maxY)/2);
//        m_block_offset = ccp(_pCenter.x -_center.x,_pCenter.y -_center.y-30);
//    }
//    
//    void SHOW_HELP_MASK(){
//        if (G::g_game_stage>=MAX_STAGE) {
//            help_step++;
//            return;
//        }
//        
//        HELP_INFO* help_info = (HELP_INFO*)G::g_help_infos->objectAtIndex(G::g_game_stage);
//        if(help_info->target_block_id == 0||help_info->isShowed||help_step!=0){
//            help_step++;
//            return;
//        }
//        ClearHelp();
//        
//        help_mask = CCUIHELPER->createWidgetFromJsonFile("HELP_MASK.json");
//        help_mask->setZOrder(10);
//        m_layer->addWidget(help_mask);
//        UIPanel* top = (UIPanel*)help_mask->getChildByName("TOP");
//        UIPanel* bottom =  (UIPanel*)help_mask->getChildByName("BOTTOM");
//        UIPanel* left =  (UIPanel*)help_mask->getChildByName("LEFT");
//        UIPanel* right =  (UIPanel*)help_mask->getChildByName("RIGHT");
//        
//        CCPoint pos = GetBlockPos(help_info->target_block_id);
//        CCRect rect = CCRectMake(0,0,0,0);
//        pos.x-=BLOCK_WH/2;
//        pos.y -= BLOCK_WH/2;
//        char actionName[30];
//        switch(help_info->dir){
//            case 0:
//                rect = CCRectMake(pos.x,pos.y,BLOCK_WH,BLOCK_WH*2);
//                sprintf(actionName,"UP_MOVE");
//                break;
//            case 1:
//                rect = CCRectMake(pos.x,pos.y-BLOCK_WH,BLOCK_WH,BLOCK_WH*2);
//                sprintf(actionName,"DOWN_MOVE");
//                break;
//            case 2:
//                rect = CCRectMake(pos.x-BLOCK_WH,pos.y,BLOCK_WH*2,BLOCK_WH);
//                sprintf(actionName,"LEFT_MOVE");
//                break;
//            case 3:
//                rect = CCRectMake(pos.x,pos.y,BLOCK_WH*2,BLOCK_WH);
//                sprintf(actionName,"RIGHT_MOVE");
//                break;
//        }
//        
//        CCSize screenSize = _pScreenSize;
//        top->setPosition(ccp(0,rect.getMaxY()));
//        top->setSize(CCSizeMake(screenSize.width,screenSize.height-rect.getMaxY()));
//        bottom->setPosition(ccp(0,0));
//        bottom->setSize(CCSizeMake(screenSize.width,rect.getMinY()));
//        left->setPosition(ccp(0,rect.getMinY()));
//        left->setSize(CCSizeMake(rect.getMinX(),rect.getMaxY()-rect.getMinY()));
//        right->setPosition(ccp(rect.getMaxX(),rect.getMinY()));
//        right->setSize(CCSizeMake(screenSize.width-rect.getMaxX(),rect.getMaxY()-rect.getMinY()));
//        
//        UIWidget* arrow_container = help_mask->getChildByName("ARROW_CONTAINER");
//        CCPoint arrow_pos = GetBlockPos(help_info->target_block_id);
//        arrow_pos.x -=10;
//        arrow_pos.y +=25;
//        arrow_container->setPosition(arrow_pos);
//        
//        if(help_info->tips_id>0){
//            GameHelpMaskTips::show(m_layer,new GameHelpParam(help_info->tips_id));
////            char tipsName[30];
////            sprintf(tipsName,"HELP_MASK_TIPS_%d.json",help_info->tips_id);
////            UIWidget* help_tips = CCUIHELPER->createWidgetFromJsonFile(tipsName);
////            help_mask->addChild(help_tips);
////            help_tips->setZOrder(30);
//        }
//        
//        ActionObject* move_action = ActionManager::shareManager()->getActionByName("HELP_MASK.json",actionName);
//        move_action->setLoop(true);
//        move_action->play();
//    }
//    
//    void HIDE_HELP_MASK(){
//        if(help_mask!=NULL){
//            GameHelpMaskTips::S()->m_close();
//            help_mask->removeFromParentAndCleanup(true);
//            help_mask = NULL;
//            help_step++;
//        }
//    }
//    
//    void SHOW_HELP_TIPS(){
//        int currentStage = G::g_game_stage;
//        if (currentStage>=MAX_STAGE) {
//            help_step++;
//            return;
//        }
//        HELP_INFO* help_info = (HELP_INFO*)G::g_help_infos->objectAtIndex(currentStage);
//        if(help_info->isShowed||help_step!=1){
//            help_step++;
//            return;
//        }
//        help_info->isShowed = true;
//        help_step++;
//        HPersistence::S()->SaveToFile();
//        if (help_info->des_id == 0) {
//            return;
//        }
//        
//        GameHelp::show(m_layer,new GameHelpParam(help_info->des_id-1));
////        sprintf(tipsName,"UI/Help_%d.json",);
////        help_tips = CCUIHELPER ->createWidgetFromJsonFile(tipsName);
////        m_layer->addWidget(help_tips);
////        help_tips->setZOrder(20);
////        UIButton* btn_ok = (UIButton*)help_tips->getChildByName("BTN_OK");
////        btn_ok->addReleaseEvent(this,coco_releaseselector(GameScene::HIDE_HELP_TIPS));
////        
////        UIWidget* tips_bg = help_tips->getChildByName("BG");
////        tips_bg->runAction(CCSequence::create(
////                                              UICOMMON::TIPS_FADEIN(tips_bg),
////                                              NULL
////                                              ));
////        tips_array->addObject(help_tips);
//    }
//    
//    void HelpTipsClosed(){
//        HELP_INFO* info = (HELP_INFO*)G::g_help_infos->objectAtIndex(G::g_game_stage);
//        info->isShowed = true;
//        help_step++;
//        HPersistence::S()->SaveToFile();
//    }
//    
//    void SchedulePreShow(float dt){
//        isPreShow = false;
//    }
//    
//    void checkAchievement(){
//        
//        G::G_Set_SingleRound_Achievement_Complete(0, achieve_count->bomb_count_single_move);
//        G::G_Set_SingleRound_Achievement_Complete(1, achieve_count->score_last_light);
//        G::G_Set_SingleRound_Achievement_Complete(2, achieve_count->combo_count);
//        G::G_Set_SingleRound_Achievement_Complete(3, achieve_count->exchange_count);
//        G::G_Set_SingleRound_Achievement_Complete(4, achieve_count->combine_count);
//        G::G_Set_SingleRound_Achievement_Complete(5, achieve_count->create_magic_count);
//        G::G_Set_SingleRound_Achievement_Complete(15, achieve_count->special_bomb_count_single_move );
//        G::G_Set_SingleRound_Achievement_Complete(18, achieve_count->use_reposion_bomb_count);
//        G::G_Set_SingleRound_Achievement_Complete(20, achieve_count->use_star_count);
//        G::G_Set_SingleRound_Achievement_Complete(27, achieve_count->hole_gold_count);
//        G::G_Set_SingleRound_Achievement_Complete(26, unlimit_score);
//        G::G_Set_SingleRound_Achievement_Complete(29, unlimit_m);
//
//        if (currentScore>=15000) {
//            G::G_Add_Achievement_Complete(6);
//        }else{
//            G::G_Add_Achievement_Complete(6, 0);
//        }
//        if(currentScore>=30000){
//            G::G_Add_Achievement_Complete(7);
//        }
//        G::G_Set_Achievement_Complete(13,G::G_getTotalStar());
//
//        
//        HPersistence::S()->SaveToFile();
//    }
//    
//    void onHoleRestart(){
//        HoleModeShow* hole_show = HoleModeShow::show(m_layer);
//        hole_show -> addCloseEvent(this, h_voidcallback(GameScene::ReturnHome));
//        hole_show->addGameStartEvent(this, h_voidcallback(GameScene::ReOpenGame));
//    }
//    
//    void updateHole(float dt);
//    
//    void LoadHoleMode();
//    
//    void rise();
//    
//    void riseBlock();
//    
//    bool initRiseBlock(int pos,bool create_special);
//    
//    bool checkRise();
//    
//    void showUnlimitScore(int id,int pos_id);
//    
//    void riseAndDestroyGem(int pos);
//    
//    int blocks_id[BLOCK_NUM_WH];
//    int gems_id[BLOCK_NUM_WH];
//    int m_max_color_count;
//    
//    int win_conditions[MAX_WIN_CONDITIONS];
//	int win_conditions_now[MAX_WIN_CONDITIONS];
//	float lose_conditions[MAX_LOSE_CONDITIONS];
//	float lose_conditions_now[MAX_LOSE_CONDITIONS];
//
//    
//    CCSpriteBatchNode* blockLayer;
//    CCLayer* gemBackLayer;
//    CCSpriteBatchNode* gemLayer;
//    CCLayer* gemFrontLayer;
//    CCClippingNode* m_clipper;
//    
//    CCLayer* helpLayer;
//    CCLayer* scoreLayer;
//    
//    CCArray* bombGemNodes;
//	CCArray* bombArray;
//	CCArray* gemMoveOverArray;
//    
//	int gem_creating_count;
//	int magicbox_flying_count;
//	int bonusTime_count;
//	bool IsTaskOver;
//	bool IsBonusTime;
//	bool to_create_gold;
//	bool has_gold;
//	int combo;
//    
//    int currentScore;
//	int maxScore;
//	int win_or_lose;
//	UILabelBMFont** label_win_conditions;
//	COCO_UILOADINGBAR* score_bar;
//	UILabelAtlas* num_time_or_step;
//    UIWidget* time_or_step_bg;
//    
//    UIWidget* toolwidget[MAX_TOOL_COUNT];
//    
//	int star_2_score;
//	int star_3_score;
//    
//    CCSprite* combo_label_sprite;
//	CCLabelAtlas* combo_num;
//	CCLabelAtlas* combo_score_num;
//    
//	UIWidget* tool_use_mask;
//	UIWidget* help_mask;
//	UIWidget* help_tips;
//	int help_step ;
//    
//	int selected_id;
//	int selected_tool_id;
//	float score_rate;
//	bool isclocked;
//	static GameScene* m_shared;
//    ACHIEVE_COUNT* achieve_count;
//    
//    bool pre_clock_isShowed;
//    float scoreBar_percent;
//    
//    int unlimit_score;
//    int unlimit_level;
//    float unlimit_time;
//    int unlimit_m;
//    COCO_UISLIDER* unlimit_time_bar;
//    UILabelAtlas* unlimit_time_num;
//    UILabelAtlas* unlimit_score_num;
//    UILabelAtlas** unlimit_m_nums;
//    COCO_UIIMAGEVIEW* unlimit_clock_img;
//    
//    bool game_result_showed;
//    CCPoint m_block_offset;
//    bool isPreShow;
//    
//    COCO_UIIMAGEVIEW* flag_2;
//    COCO_UIIMAGEVIEW* flag_3;
     GameLogic* m_game_logic;
};

#endif /* defined(__Bejeweled__GameScene__) */

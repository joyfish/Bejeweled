//
//  GemObject.h
//  Test
//
//  Created by wilford on 14-3-5.
//
//

#ifndef __Test__GemObject__
#define __Test__GemObject__

#include "ElementBase.h"
#include "HTools.h"
#include "HDefine.h"
#include "HGloba.h"
#include "AutoSceneSize.h"

using namespace std;

typedef void (CCObject::*SEL_DOSPECIALBOMB)(SPECIAL_BOMB_TYPE bomb_type,GEM_COLOR color,int pos,float delay);
#define h_doSpecialBomb(_SELECTOR) (SEL_DOSPECIALBOMB)(&_SELECTOR)

class GemObject:public CCObject,public ElementBase{
public:
    CCNode* m_bee_container;//蜜蜂容器
    CCNode* m_gem_container;//宝石容器
    float m_bomb_delayTime;//延迟爆炸时间
    bool m_IsNewCreated;//当前帧新生成的宝石
    bool IsExchangeMove;//这次移动是否是交换的移动
    bool isBombBySpecial;//被特效宝石引爆
    bool isNewMoveOver;//是否刚移动完
    int bao_id;

    GemObject()
    :isMoving(false)
    ,isBombing(false)
    ,isNewMoveOver(false)
    ,m_IsNewCreated(false)
    ,m_has_bee(false)
    ,m_bomb_time(0)
    ,m_bomb_delayTime(-1)
    ,m_doSpecailBombListener(NULL)
    ,m_doSpecialBombSelector(NULL)
    ,m_gem_layer(NULL)
    ,m_special_layer(NULL)
    ,m_gem_container(NULL)
    ,m_bee_container(NULL)
    ,IsExchangeMove(false)
    ,isBombBySpecial(false)
    ,ElementBase()
    ,bao_id(-1)
    {
        m_sprites.clear();
    }
    
	~GemObject(){
		m_sprites.clear();
	}
    
    void DestoryOnCB(CCNode* node){
        node->removeFromParent();
    }
    
    void setGemLayer(CCLayer* layer,CCLayer* special_layer){
        m_gem_layer = layer;
        m_special_layer = special_layer;
    }
	   
    void create(int new_id);
    void clear();
    
    void addGemSprite(const char* spriteName=NULL,CCPoint _pos = CCPointZero);
    void newGem(int new_id);
    
    void replaceGem(CCPoint pos);
    
    void ScaleOut();
    void ScaleIn();
    
    void update(float dt);
    
    ///////细节动画
    void Look(EYE_DIR dir);//眼睛移动
    void Blink();//眨眼
    
    void updatePreBomb(float dt);//刷新延迟爆炸时间
    void Bomb(float delayTime);//延迟爆炸
    bool Bomb();//宝石爆炸
    void BombEffect();//爆炸特效
    void GoldOut();//皇冠到达出口
    
    void playJumpAnim(float delay, int repeat_times, int tag = -1);
    void showGameWinAnim(float delay);
    bool hasGameWinAnim();
    void showHelpAnim();//播放帮助动画
    void clearHelpAnim();//清除帮助动画
    
    //////////////////宝石类型
    GEM_TYPE getType(){return (GEM_TYPE)(id/10);}
    GEM_COLOR getColor(){return (GEM_COLOR)(id%10);}
    bool IsTimeBombType(){return id/1000 == GEM_TIME_BOMB/100;}
    bool IsSpecialGem();
    bool IsHoleWall(){return getType()>=GEM_HOLE_WALL&&getType()<=GEM_HOLE_SPECIAL_7;}
    ///////////////////////////////////////////
    
    //*******************宝石移动****************
    void exChangeWithGemObject(GemObject* target);//2个GemObject互换信息
    void toGemObject(GemObject* target);//把当前GemObject信息移入指定GemObject
    void MoveGoAndBack(int toPos);//到指定目标然后返回
    void Move(float duration = 0.06f);//普通移动
    void MoveWithNoCheck(float duration = 0.06f);
    void DoorMove();//传送门移动
    void MoveToAndClear(float duration,CCPoint to);
    //*****************************************
    
    //*****************宝石状态******************
    bool isEmpty(){ return id == 0; }
    bool IsPreBomb(){ return m_bomb_delayTime>=0; }
    bool IsMoving(){ return isMoving; }
    bool IsBombing(){ return isBombing; }
    bool IsHelping(){
        if (m_gem_container) {
            return m_gem_container->getActionByTag(99) != NULL;
        }
        return false;
    }
    bool HasBee(){ return m_has_bee; }
    bool IsNewMoveOver(){
        if (isNewMoveOver) {
            isNewMoveOver = false;
            return true;
        }
        return false;
    }
    //******************************************
    
    //**********   蜜蜂特效   *****************
    CCSprite* addBeeSprite(const char* spriteName,CCPoint _pos = CCPointZero);
    void PlayBee();
    void StopBee();
    void onBeePlayOver(CCNode* node){
        StopBee();
    }
    //*************************************
    
    //********** 定时炸弹 *************
    int getTimeBombLife(){return (id/10)%GEM_TIME_BOMB;}
    void setTimeBombLife(int life);
    void cutTimeBomb();//定时炸弹计时
    //********************************
    
    void AddDoSpecialBombEvent(CCObject* target,SEL_DOSPECIALBOMB selector);
    
private:
    void DoSpecialBomb(SPECIAL_BOMB_TYPE bomb_type,GEM_COLOR color,int pos,float delay);
    void MoveOver(CCNode* node);
    void MoveOverWithNoCheck(CCNode* node);
    
private:
    vector<CCSprite*> m_sprites;//当前渲染的精灵集
    CCObject* m_doSpecailBombListener;
    SEL_DOSPECIALBOMB m_doSpecialBombSelector;
    CCLayer* m_gem_layer;
    CCLayer* m_special_layer;
    bool isMoving;//是否在移动
    bool isBombing;//是否在爆炸
    bool m_has_bee;//有蜜蜂
    float m_bomb_time;//爆炸持续时间

};

#endif /* defined(__Test__GemObject__) */

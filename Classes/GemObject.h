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
    CCNode* m_bee_container;//�۷�����
    CCNode* m_gem_container;//��ʯ����
    float m_bomb_delayTime;//�ӳٱ�ըʱ��
    bool m_IsNewCreated;//��ǰ֡�����ɵı�ʯ
    bool IsExchangeMove;//����ƶ��Ƿ��ǽ������ƶ�
    bool isBombBySpecial;//����Ч��ʯ����
    bool isNewMoveOver;//�Ƿ���ƶ���
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
    
    ///////ϸ�ڶ���
    void Look(EYE_DIR dir);//�۾��ƶ�
    void Blink();//գ��
    
    void updatePreBomb(float dt);//ˢ���ӳٱ�ըʱ��
    void Bomb(float delayTime);//�ӳٱ�ը
    bool Bomb();//��ʯ��ը
    void BombEffect();//��ը��Ч
    void GoldOut();//�ʹڵ������
    
    void playJumpAnim(float delay, int repeat_times, int tag = -1);
    void showGameWinAnim(float delay);
    bool hasGameWinAnim();
    void showHelpAnim();//���Ű�������
    void clearHelpAnim();//�����������
    
    //////////////////��ʯ����
    GEM_TYPE getType(){return (GEM_TYPE)(id/10);}
    GEM_COLOR getColor(){return (GEM_COLOR)(id%10);}
    bool IsTimeBombType(){return id/1000 == GEM_TIME_BOMB/100;}
    bool IsSpecialGem();
    bool IsHoleWall(){return getType()>=GEM_HOLE_WALL&&getType()<=GEM_HOLE_SPECIAL_7;}
    ///////////////////////////////////////////
    
    //*******************��ʯ�ƶ�****************
    void exChangeWithGemObject(GemObject* target);//2��GemObject������Ϣ
    void toGemObject(GemObject* target);//�ѵ�ǰGemObject��Ϣ����ָ��GemObject
    void MoveGoAndBack(int toPos);//��ָ��Ŀ��Ȼ�󷵻�
    void Move(float duration = 0.06f);//��ͨ�ƶ�
    void MoveWithNoCheck(float duration = 0.06f);
    void DoorMove();//�������ƶ�
    void MoveToAndClear(float duration,CCPoint to);
    //*****************************************
    
    //*****************��ʯ״̬******************
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
    
    //**********   �۷���Ч   *****************
    CCSprite* addBeeSprite(const char* spriteName,CCPoint _pos = CCPointZero);
    void PlayBee();
    void StopBee();
    void onBeePlayOver(CCNode* node){
        StopBee();
    }
    //*************************************
    
    //********** ��ʱը�� *************
    int getTimeBombLife(){return (id/10)%GEM_TIME_BOMB;}
    void setTimeBombLife(int life);
    void cutTimeBomb();//��ʱը����ʱ
    //********************************
    
    void AddDoSpecialBombEvent(CCObject* target,SEL_DOSPECIALBOMB selector);
    
private:
    void DoSpecialBomb(SPECIAL_BOMB_TYPE bomb_type,GEM_COLOR color,int pos,float delay);
    void MoveOver(CCNode* node);
    void MoveOverWithNoCheck(CCNode* node);
    
private:
    vector<CCSprite*> m_sprites;//��ǰ��Ⱦ�ľ��鼯
    CCObject* m_doSpecailBombListener;
    SEL_DOSPECIALBOMB m_doSpecialBombSelector;
    CCLayer* m_gem_layer;
    CCLayer* m_special_layer;
    bool isMoving;//�Ƿ����ƶ�
    bool isBombing;//�Ƿ��ڱ�ը
    bool m_has_bee;//���۷�
    float m_bomb_time;//��ը����ʱ��

};

#endif /* defined(__Test__GemObject__) */

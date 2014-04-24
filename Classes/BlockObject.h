//
//  BlockObject.h
//  Test
//
//  Created by wilford on 14-3-5.
//
//

#ifndef __Test__BlockObject__
#define __Test__BlockObject__

#include "ElementBase.h"
#include "HTools.h"
#include "HDefine.h"
#include "HGloba.h"
#include "AutoSceneSize.h"

using namespace std;

class BlockObject:public CCObject, public ElementBase{
public:
    
    bool m_IsnewMoveInTop;
    bool m_IsTopNewCreated;
    bool m_IsLastRoundTopNewCreated;
    
    BlockObject()
    :m_hasMidBombed(false)
    ,m_hasTopBombed(false)
    ,m_IsTopBombing(false)
    ,m_IsLastRoundTopNewCreated(false)
    ,m_top_bomb_time(0)
    ,m_IsnewMoveInTop(false)
    ,m_IsTopNewCreated(false)
    ,m_bottom_layer(NULL)
    ,m_top_layer(NULL)
    ,m_mid_layer(NULL)
    ,m_hasMidChanged(false)
    ,m_hasTopChanged(false)
    ,m_bottom_rotate(NULL)
    ,m_special_layer(NULL)
    ,ElementBase(){
        m_top_sprites.clear();
        m_mid_sprites.clear();
    }
    
	~BlockObject(){
		m_top_sprites.clear();
		m_mid_sprites.clear();
	}
    
    void DestoryOnCB(CCNode* node){
        node->removeFromParent();
    }
    
    void update(float dt);
    
    void setBlockLayer(CCSpriteBatchNode* bottom,CCSpriteBatchNode* mid,CCSpriteBatchNode* top,CCLayer* special);
    
    void create(int newid);
    
    void newTop(BLOCK_TOP_TYPE top_type,int life = 0);
    
    void addTopSprite(const char* spriteName,CCPoint pos);
    void clearTopSprites();
    void drawTop();
    
    void addMidSprite(const char* spriteName,CCPoint pos);
    void clearMidSprites();
    void drawMid();
    
    void drawBottom();
    
    void playCoilGunAnimation();
    void playDoorAnimation();
    
    void moveTop();
    void moveTopToBlockObject(BlockObject* blockObj);
    
    bool Bomb();
    
    void BombMid();
    void BombTop();
    

    void Blink();
    
    void resetBlock();
    
    int getNum(int p){return (id>>(p*4))&0xf;}
    void setNum(int p,int num){
        num &= 0xf;
        id |= 0xf<<(4*p);
        id &= (num<<(4*p))|~(0xf<<(4*p));
    }
    
    BLOCK_BOTTOM_TYPE getBottomType(){return (BLOCK_BOTTOM_TYPE)getNum(1);}
    void setBottomType(BLOCK_BOTTOM_TYPE type){setNum(1, type);}
    int getBottomNum(){return getNum(0);}
    void setBottomNum(int num){setNum(0, num);}
    
    BLOCK_MID_TYPE getMidType(){return  (BLOCK_MID_TYPE)getNum(3);}
    void setMidType(BLOCK_MID_TYPE type);
    int getMidNum(){return getNum(2);}
    void setMidNum(int num);
    
    BLOCK_TOP_TYPE getTopType(){return (BLOCK_TOP_TYPE)getNum(5);}
    void setTopType(BLOCK_TOP_TYPE type);
    int getTopNum(){return getNum(4);}
    void setTopNum(int num);
    
    bool isMatchColor();
    bool canMoveInFromDir(ROPE_DIR dir);
    bool canMoveOutFromDir(ROPE_DIR dir);
    bool canMoveOut();
    bool canMoveIn();
    bool canDoorMoveIn();
    bool canInsertGem();
    
    bool IsTopBombing(){return m_IsTopBombing;}
    
    bool IsNewWithGem();
    void setIsNewWithGem(bool hasGem);
    
    void onSeaWallPlayOver(CCNode* node){
        node->setPosition(ccp(node->getPositionX(), node->getPositionY()+50));
        node->setAnchorPoint(_nCenter);
    }
    
private:
    
    vector<CCSprite*> m_top_sprites;
    vector<CCSprite*> m_mid_sprites;
    CCSpriteBatchNode* m_top_layer;
    CCSpriteBatchNode* m_mid_layer;
    CCSpriteBatchNode* m_bottom_layer;
    CCSprite* m_bottom_rotate;
    CCLayer* m_special_layer;
    bool m_hasTopChanged;//中层地块发生了变化
    bool m_hasMidChanged;//下层地块发生了变化
    bool m_hasTopBombed;//当前帧顶层发生过爆炸
    bool m_hasMidBombed;//当前帧中层发生过爆炸
    bool m_IsTopBombing;//最上层元素在播放爆炸动画
    float m_top_bomb_time;//最上层元素爆炸剩余时间
};


#endif /* defined(__Test__BlockObject__) */

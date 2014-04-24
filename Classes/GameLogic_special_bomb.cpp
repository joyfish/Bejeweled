//
//  GameLogic_special_bomb.cpp
//  Test
//
//  Created by wilford on 14-3-6.
//
//

#include "GameLogic_special_bomb.h"


void GameLogic_special_bomb::updateSpecialBombs(float dt){
    CCObject* obj;
    CCArray* toRemove = CCArray::create();
    
    CCARRAY_FOREACH(m_special_bombs, obj){
        SpecialBomb* special_bomb = (SpecialBomb*)obj;
        special_bomb->update(dt);
        if (special_bomb->delayTime == 0) {
            toRemove ->addObject(obj);
            DoSpecialBomb(special_bomb->bomb_type, special_bomb->color, special_bomb->pos);
        }
    }
    if (toRemove->count()>0)
    {
        m_special_bombs->removeObjectsInArray(toRemove);
    }
    
    toRemove->release();
}

void GameLogic_special_bomb::DoSpecialBomb(SPECIAL_BOMB_TYPE bomb_type,GEM_COLOR color,int pos,float delay){
    SpecialBomb* special_bomb = new SpecialBomb();
    special_bomb->bomb_type = bomb_type;
    special_bomb->color = color;
    special_bomb->pos = pos;
    special_bomb->delayTime = delay;
    m_special_bombs->addObject(special_bomb);
}


void GameLogic_special_bomb::DestroyOnCB(CCNode* node){
    node->removeFromParent();
}

void GameLogic_special_bomb::DoSpecialBomb(SPECIAL_BOMB_TYPE bomb_type,GEM_COLOR color,int pos){
    if (pos < 0 || pos >= BLOCK_NUM_WH) {
        return;
    }
    int tmpx = pos%BLOCK_NUM_W;
    int tmpy = pos/BLOCK_NUM_W;
    
    switch (bomb_type) {
        case SPECIAL_BOMB_H:
            for (int i=0; i<BLOCK_NUM_W; i++) {
                int tmpPos = i+tmpy*BLOCK_NUM_W;
                if (tmpPos == pos) {
                    continue;
                }
                if (m_gems[tmpPos]->IsSpecialGem()&&m_gems[tmpPos]->getType()!=GEM_H) {
                    Bomb(tmpPos,0.4f,true);
                }else{
                    //Bomb(tmpPos,abs(tmpx-i)*0.04f);
                    Bomb(tmpPos,0,true);
                }
            }
        {
            CCSprite* m_bomb_effect = CCSprite::createWithSpriteFrameName("gem_special_h_0.png");
            CCAnimation* animation = CCAnimation::create();
            for (int i=0; i<5; i++) {
                IntToStringFormat(_name, "gem_special_h_%d.png", i)
                animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(_name));
                
            }
            animation->setDelayPerUnit(0.1f);
            CCAnimate* animate = CCAnimate::create(animation);
            m_bomb_effect->runAction(CCSequence::create(animate,CCCallFuncN::create(this, callfuncN_selector(GameLogic_special_bomb::DestroyOnCB)),NULL));
            m_special_bomb_layer->addChild(m_bomb_effect);
            m_bomb_effect->setPosition(ccp(_pCenter.x,GetBlockPos(pos).y));
        }
        //SimpleAudioEngine::sharedEngine()->stopAllEffects();
        
        G::G_playEffect(RES_MUSIC_BOMB_1);
            break;
        case SPECIAL_BOMB_V:
            for (int i=0; i<BLOCK_NUM_H; i++) {
                int tmpPos = tmpx+i*BLOCK_NUM_W;
                if (tmpPos == pos) {
                    continue;
                }
                if (m_gems[tmpPos]->IsSpecialGem()&&m_gems[tmpPos]->getType()!=GEM_V) {
                    Bomb(tmpPos,0.4f,true);
                }else{
                    Bomb(tmpPos,0,true);
                    //Bomb(tmpPos,abs(tmpy-i)*0.04f);
                }
            }
        {
            CCSprite* m_bomb_effect = CCSprite::createWithSpriteFrameName("gem_special_h_0.png");
            CCAnimation* animation = CCAnimation::create();
            for (int i=0; i<5; i++) {
                IntToStringFormat(_name, "gem_special_h_%d.png", i)
                animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(_name));
                
            }
            animation->setDelayPerUnit(0.1f);
            CCAnimate* animate = CCAnimate::create(animation);
            m_bomb_effect->runAction(CCSequence::create(animate,CCCallFuncN::create(this, callfuncN_selector(GameLogic_special_bomb::DestroyOnCB)),NULL));
            m_special_bomb_layer->addChild(m_bomb_effect);
            m_bomb_effect->setRotation(90);
            switch (G::g_game_mode) {
                case GAMEMODE_STAGE:
                    m_bomb_effect->setPosition(ccp(GetBlockPos(pos).x,_pCenter.y-50));
                    break;
                case GAMEMODE_HOLE:
                {
                    float offsety =  (_pScreenSize.height - 960)/2;
                    m_bomb_effect->setPosition(ccp(GetBlockPos(pos).x,_pBottom + 762 + BLOCK_WH/2+offsety));
                }
                    break;
                case GAMEMODE_SEA:
                    m_bomb_effect->setPosition(ccp(GetBlockPos(pos).x,_pCenter.y-50));
                    break;
                default:
                    m_bomb_effect->setPosition(ccp(GetBlockPos(pos).x,_pCenter.y-30));
                    break;
            }
        }
         G::G_playEffect(RES_MUSIC_BOMB_1);
            break;
        
       
        case SPECIAL_BOMB_AREA:
        {
            int d = 2;
            for (int i=-d ;i<=d; i++) {
                int _x = tmpx+i;
                if (_x<0||_x>=BLOCK_NUM_W) {
                    continue;
                }
                for (int j = -d; j<=d; j++) {
                    if (abs(i)+abs(j)>d) {
                        continue;
                    }
                    int _y = tmpy+j;
                    if (_y<0||_y>=BLOCK_NUM_H) {
                        continue;
                    }
                    int tmpPos = _x+_y*BLOCK_NUM_W;
                    if (tmpPos == pos) {
                        continue;
                    }
                    if (m_gems[tmpPos]->IsSpecialGem()) {
                        Bomb(tmpPos,0.4f,true);
                    }else{
                        Bomb(tmpPos,0,true);
                        //Bomb(tmpPos,(abs(i)+abs(j))*0.1f);
                    }
                }
            }
            
            CCSprite* m_bomb_effect = CCSprite::createWithSpriteFrameName("gem_special_area_0.png");
            CCAnimation* animation = CCAnimation::create();
            for (int i=0; i<3; i++) {
                IntToStringFormat(_name, "gem_special_area_%d.png", i)
                animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(_name));
                
            }
            animation->setDelayPerUnit(0.1f);
            CCAnimate* animate = CCAnimate::create(animation);
            m_bomb_effect->runAction(CCSequence::create(animate,CCCallFuncN::create(this, callfuncN_selector(GameLogic_special_bomb::DestroyOnCB)),NULL));
            m_special_bomb_layer->addChild(m_bomb_effect);
            m_bomb_effect->setPosition(GetBlockPos(pos));
        }
        G::G_playEffect(RES_MUSIC_BOMB_2);
            break;
        case SPECIAL_BOMB_3AREA:
        {
            int d = 3;
            for (int i=-d ;i<=d; i++) {
                int _x = tmpx+i;
                if (_x<0||_x>=BLOCK_NUM_W) {
                    continue;
                }
                for (int j = -d; j<=d; j++) {
                    if (abs(i)+abs(j)>d) {
                        continue;
                    }
                    int _y = tmpy+j;
                    if (_y<0||_y>=BLOCK_NUM_H) {
                        continue;
                    }
                    int tmpPos = _x+_y*BLOCK_NUM_W;
                    if (tmpPos == pos) {
                        continue;
                    }
                    if (m_gems[tmpPos]->IsSpecialGem()) {
                        Bomb(tmpPos,0.4f,true);
                    }else{
                        Bomb(tmpPos,0,true);
                        //Bomb(tmpPos,(abs(i)+abs(j))*0.1f);
                    }
                }
            }
            CCSprite* m_bomb_effect = CCSprite::createWithSpriteFrameName("gem_special_area_0.png");
            CCAnimation* animation = CCAnimation::create();
            for (int i=0; i<3; i++) {
                IntToStringFormat(_name, "gem_special_area_%d.png", i)
                animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(_name));
                
            }
            animation->setDelayPerUnit(0.1f);
            CCAnimate* animate = CCAnimate::create(animation);
            m_bomb_effect->runAction(CCSequence::create(animate,CCCallFuncN::create(this, callfuncN_selector(GameLogic_special_bomb::DestroyOnCB)),NULL));
            m_special_bomb_layer->addChild(m_bomb_effect);
            m_bomb_effect->setPosition(GetBlockPos(pos));
        }
        //SimpleAudioEngine::sharedEngine()->stopAllEffects();
        G::G_playEffect(RES_MUSIC_BOMB_2);
            break;
        case SPECIAL_BOMB_MAGIC_VH:
            if (color == GEM_COLOR_NOCOLOR) {
                break;
            }
        {
            float bombDelay = 1.0f;
            for (int i=0; i<BLOCK_NUM_WH; i++) {
                if (!m_blocks[i]->isMatchColor()) {
                    continue;
                }
                
                if (i == pos) {
                    continue;
                }
                
                if (m_gems[i]->getColor() == color) {
                    CCSprite* magic_fly = CCSprite::create("magic_fly.png");
                    magic_fly->setAnchorPoint(ccp(0.8f,0.5f));
                    m_special_layer->addChild(magic_fly);
                    float delay = FlyNodeTo(magic_fly, GetBlockPos(pos), GetBlockPos(i), 0.12f,true);
                    
                    if (!m_gems[i]->IsSpecialGem()) {
                        if (t_getRandom(2)) {
                            createGem(i, GEM_V*10+color,delay,bombDelay);
                            //m_gems[i]->create(GEM_V*10+color);
                        }else{
                            createGem(i, GEM_H*10+color,delay,bombDelay);
                            // m_gems[i]->create(GEM_H*10+color);
                        }
                    }else{
                        Bomb(i,delay + bombDelay);
                    }
                    
                    //                        m_gems[i]->m_IsNewCreated = false;
                    //                        Bomb(i,bombDelay);
                    bombDelay+=0.5f;
                }
            }
        }
        G::G_playEffect(RES_MUSIC_BOMB_3);
            break;
        case SPECIAL_BOMB_MAGIC_AREA:
            if (color == GEM_COLOR_NOCOLOR) {
                break;
            }
        {
            float bombDelay = 1.0f;
            for (int i=0; i<BLOCK_NUM_WH; i++) {
                if (!m_blocks[i]->isMatchColor()) {
                    continue;
                }
                if (i == pos) {
                    continue;
                }
                
                if (m_gems[i]->getColor() == color) {
                    CCSprite* magic_fly = CCSprite::create("magic_fly.png");
                    magic_fly->setAnchorPoint(ccp(0.8f,0.5f));
                    m_special_layer->addChild(magic_fly);
                    float delay = FlyNodeTo(magic_fly, GetBlockPos(pos), GetBlockPos(i), 0.12f,true);
                    if (!m_gems[i]->IsSpecialGem()) {
                        createGem(i, GEM_AREA*10+color,delay,bombDelay);
                    }else{
                        Bomb(i,delay+bombDelay);
                    }
                    bombDelay+=0.5f;
                }
            }
        }
        G::G_playEffect(RES_MUSIC_BOMB_3);
            break;
        case SPECIAL_BOMB_MAGIC_NORMAL:
            if (color == GEM_COLOR_NOCOLOR) {
                color = (GEM_COLOR)(t_getRandom(m_maxColor)+1);
            }
        {
            float bombDelay = 0.5f;
            for (int i=0; i<BLOCK_NUM_WH; i++) {
                if (!m_blocks[i]->isMatchColor()) {
                    continue;
                }
                if (i == pos) {
                    continue;
                }
                
                if (m_gems[i]->getColor() == color) {
                    CCSprite* magic_fly = CCSprite::create("magic_fly.png");
                    magic_fly->setAnchorPoint(ccp(0.8f,0.5f));
                    m_special_layer->addChild(magic_fly);
                    float delay = FlyNodeTo(magic_fly, GetBlockPos(pos), GetBlockPos(i), 0.12f,true);
                    
                    if (m_gems[i]->IsSpecialGem()) {
                        Bomb(i,delay+bombDelay);
                        bombDelay+=0.5f;
                    }else{
                        Bomb(i,delay);
                    }
                }
            }
            
        }
        G::G_playEffect(RES_MUSIC_BOMB_3);
            break;
        case SPECIAL_BOMB_2MAGIC:
        {
            for (int i=0; i<BLOCK_NUM_WH; i++) {
                if (!m_blocks[i]->isMatchColor()) {
                    continue;
                }
                if (i == pos) {
                    continue;
                }
                
                
                if (m_gems[i]->IsPreBomb()||
                    m_gems[i]->IsBombing()) {
                    continue;
                }
                
                CCSprite* magic_fly = CCSprite::create("magic_fly.png");
                magic_fly->setAnchorPoint(ccp(0.8f,0.5f));
                m_special_layer->addChild(magic_fly);
                float delay =  FlyNodeTo(magic_fly, GetBlockPos(pos), GetBlockPos(i), 0.1f,true);
                
                Bomb(i,delay);
                
            }
        }
        G::G_playEffect(RES_MUSIC_BOMB_3);
            break;
        default:
            break;
    }
}

float GameLogic_special_bomb::FlyNodeTo(CCNode* node,CCPoint from,CCPoint to,float duration,bool destoryOnOver,float delay ){
    node->setPosition(from);
    float offsetX = to.x-from.x;
    float offsetY = to.y-from.y;
    float angle = 0;
    if(offsetX == 0){
        if(offsetY==0)
            return 0;
        else if(offsetY>0){
            angle = 90;
        }else if(offsetY<0){
            angle = -90;
        }
    }else {
        angle = atan(offsetY/offsetX)*180/3.14f;
        if(offsetX<0){
            angle +=180;
        }
    }
    float distance = sqrtf(offsetX*offsetX+offsetY*offsetY);
    float _duration = duration*distance/100;
    _duration = MIN(_duration, 0.5f);
    node->setRotation(-angle);
    if (destoryOnOver) {
        node->runAction(CCSequence::create(CCDelayTime::create(delay),CCShow::create(),CCMoveTo::create(_duration, to),CCCallFuncN::create(this, callfuncN_selector(GameLogic_special_bomb::DestroyOnCB)),NULL));
    }else{
        node->runAction(CCSequence::create(CCDelayTime::create(delay),CCShow::create(), CCMoveTo::create(_duration, to),NULL));
    }
    return _duration+delay;
}
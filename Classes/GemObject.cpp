//
//  GemObject.cpp
//  Test
//
//  Created by wilford on 14-3-5.
//
//

#include "GemObject.h"

void GemObject::Look(EYE_DIR dir){
    if (isEmpty())
    {
        return;
    }
    
    int type = getType();
    int color = getColor();
    vector<CCPoint*> _offsets;
    switch(type){
        case GEM_NORMAL:
        {
            switch(color){
                case 1:
                {
                    CCPoint offsets[] =
                    {
                        ccp(0,0),
                        ccp(0,3),
                        ccp(0,-8),
                        ccp(-8,-2),
                        ccp(7,-5),
                        ccp(-8,3),
                        ccp(7,-3),
                        ccp(-8,-8),
                        ccp(7,-8)
                    };
                    _offsets.push_back(offsets);
                }
                    break;
                case 2:
                {
                    CCPoint offsets[] = {
                        ccp(0,0),
                        ccp(0,2),
                        ccp(0,-5),
                        ccp(-10,0),
                        ccp(7,0),
                        ccp(-10,2),
                        ccp(7,2),
                        ccp(-10,-5),
                        ccp(7,-5)
                    };
                    _offsets.push_back(offsets);
                }
                    break;
                case 3:
                {
                    CCPoint offsets1[] = {
                        ccp(0,0),
                        ccp(0,2),
                        ccp(0,-5),
                        ccp(-5,-1),
                        ccp(5,-1),
                        ccp(-5,2),
                        ccp(5,2),
                        ccp(-5,-5),
                        ccp(5,-5)
                    };
                    CCPoint offsets2[] = {
                        ccp(0,0),
                        ccp(0,2),
                        ccp(0,-5),
                        ccp(-4,-1),
                        ccp(4,-1),
                        ccp(-4,2),
                        ccp(4,2),
                        ccp(-4,-5),
                        ccp(4,-5)
                    };
                    _offsets.push_back(offsets1);
                    _offsets.push_back(offsets2);
                    if (m_sprites[1])
                    {
                        CCAction* eyeAction = CCMoveTo::create(0.3f,offsets1[dir]);
                        eyeAction->setTag(50);
                        m_sprites[1]->stopActionByTag(50);
                        m_sprites[1]->runAction(eyeAction);
                    }
                }
                    break;
                case 4:
                {
                    CCPoint offsets[] = {
                        ccp(0,0),
                        ccp(0,6),
                        ccp(0,-5),
                        ccp(-8,0),
                        ccp(6,0),
                        ccp(-8,6),
                        ccp(6,6),
                        ccp(-8,-5),
                        ccp(6,-5)
                    };
                    _offsets.push_back(offsets);
                }
                    break;
                case 5:
                {
                    CCPoint offsets1[] = {
                        ccp(0,0),
                        ccp(0,3),
                        ccp(0,-5),
                        ccp(-7,-1),
                        ccp(5,-1),
                        ccp(-7,3),
                        ccp(5,3),
                        ccp(-7,-5),
                        ccp(5,-5)
                    };
                    CCPoint offsets2[] = {
                        ccp(0,0),
                        ccp(0,3),
                        ccp(0,-5),
                        ccp(-5,-1),
                        ccp(7,-1),
                        ccp(-5,3),
                        ccp(7,3),
                        ccp(-5,-5),
                        ccp(7,-5)
                    };
                    _offsets.push_back(offsets1);
                    _offsets.push_back(offsets2);
                }
                    break;
                case 6:
                {
                    CCPoint offsets1[] = {
                        ccp(0,0),
                        ccp(0,4),
                        ccp(0,-4),
                        ccp(-5,0),
                        ccp(5,0),
                        ccp(-5,4),
                        ccp(5,4),
                        ccp(-5,-4),
                        ccp(5,-4)
                    };
                    CCPoint offsets2[] = {
                        ccp(0,0),
                        ccp(0,3),
                        ccp(0,-3),
                        ccp(-3,0),
                        ccp(3,0),
                        ccp(-3,3),
                        ccp(3,3),
                        ccp(-3,-3),
                        ccp(3,-3)
                    };
                    _offsets.push_back(offsets1);
                    _offsets.push_back(offsets2);
                    
                }
                    break;
            }
        }
            break;
    }
    for (unsigned int i=0; i<_offsets.size(); i++) {
        if (m_sprites[i+1])
        {
            CCAction* eyeAction;
            if (dir == EYE_DIR_NONE) {
                eyeAction = CCMoveTo::create(0.3f,_offsets[i][dir]);
            }else{
                eyeAction = CCSequence::create(CCMoveTo::create(0.3f,_offsets[i][dir]),CCDelayTime::create(0.2f),CCMoveTo::create(0.3f,_offsets[i][0]),NULL);
            }
            eyeAction->setTag(50);
            m_sprites[i+1]->stopActionByTag(50);
            m_sprites[i+1]->runAction(eyeAction);
        }
    }
    
}

void GemObject::create(int new_id){
    m_IsNewCreated = true;
    newGem(new_id);
    ScaleIn();
    if (getType()==GEM_V||
        getType()==GEM_H||
        getType()==GEM_AREA||
        getType()==GEM_MAGIC) {
        CCSprite* special_out = CCSprite::createWithSpriteFrameName("gem_special_out.png");
        m_special_layer->addChild(special_out);
        special_out->setPosition(GetPos(pos));
        special_out->setOpacity(128);
        special_out->runAction(CCSequence::create(CCFadeOut::create(1.0f),CCCallFuncN::create(this, callfuncN_selector(GemObject::DestoryOnCB)),NULL));
        special_out->runAction(CCScaleTo::create(0.2f, 1.7f));
        G::G_playEffect(RES_MUSIC_CREATE_1);
    }
}

void GemObject::clear(){
    id = 0;
    StopBee();
    if (!m_gem_container) {
        return;
    }
    m_gem_container->removeFromParentAndCleanup(true);
    m_gem_container = NULL;
    m_sprites.clear();
}

void GemObject::addGemSprite(const char* spriteName,CCPoint _pos) {
    if (!m_gem_container) {
        return;
    }
    CCSprite* sprite;
    if (spriteName) {
        sprite = CCSprite::createWithSpriteFrameName(spriteName);
    }else{
        sprite = CCSprite::create();
    }
    
    m_gem_container->addChild(sprite);
    sprite->setPosition(_pos);
    m_sprites.push_back(sprite);
}

void GemObject::Blink(){
    if (!m_gem_container) {
        return;
    }
    GEM_TYPE type = getType();
    GEM_COLOR color = getColor();
    switch (type) {
        case GEM_NORMAL://∆’Õ®±¶ Ø
        case GEM_TIME://+5√Î±¶ Ø
        {
            CCSprite* anim_sprite;
            if (getColor()==3||getColor()==5||getColor()==6) {
                anim_sprite = m_sprites[5];
            }else{
                anim_sprite = m_sprites[4];
            }
            if (anim_sprite->numberOfRunningActions()>0) {
                return;
            }
            CCAnimation* animation = CCAnimation::create();
            for (int i=0; i<2; i++) {
                char _name[30];
                sprintf(_name, "gem_0_%d_e_%d.png",color,i);
                animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(_name));
            }
            animation->setDelayPerUnit(0.1f);
            //animation->setLoops(-1);
            CCAnimate* animate = CCAnimate::create(animation);
            anim_sprite->runAction(animate);
            anim_sprite->runAction(CCSequence::create(CCShow::create(), animate,CCDelayTime::create(0.15f),CCHide::create(), NULL));
        }
            break;
        case GEM_BEE:
        {
            if (m_sprites[6]->numberOfRunningActions()>0) {
                return;
            }
            CCAnimation* animation = CCAnimation::create();
            for (int i=0; i<2; i++) {
                char _name[30];
                sprintf(_name, "gem_7_%d_e_%d.png",color,i);
                animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(_name));
            }
            animation->setDelayPerUnit(0.1f);
            //animation->setLoops(-1);
            CCAnimate* animate = CCAnimate::create(animation);
            m_sprites[6]->runAction(animate);
            m_sprites[6]->runAction(CCSequence::create(CCShow::create(), animate,CCDelayTime::create(0.15f),CCHide::create(), NULL));
        }
            break;
        case GEM_COIL:
        {
            if (m_sprites[3]->numberOfRunningActions()>0) {
                return;
            }
            CCAnimation* animation = CCAnimation::create();
            for (int i=0; i<2; i++) {
                char _name[30];
                sprintf(_name, "gem_10_d_%d.png",i);
                animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(_name));
            }
            animation->setDelayPerUnit(0.1f);
            //animation->setLoops(-1);
            CCAnimate* animate = CCAnimate::create(animation);
            m_sprites[3]->runAction(animate);
            m_sprites[3]->runAction(CCSequence::create(CCShow::create(), animate,CCDelayTime::create(0.15f),CCHide::create(), NULL));
        }
            break;
        default:
            break;
    }
}

void GemObject::newGem(int new_id){
    clear();
    id = new_id;
    if (isEmpty()) {
        return;
    }
    isMoving = false;
    isBombing = false;
    m_bomb_delayTime = -1;
    
    CCPoint _centerPos = GetPos();
    
    if (!m_gem_container) {
        m_gem_container = CCNode::create();
        m_gem_layer->addChild(m_gem_container);
        m_gem_container->setPosition(_centerPos);
    }
    
    GEM_TYPE type = getType();
    GEM_COLOR color = getColor();
    switch (type) {
        case GEM_HOLE_WALL:
        case GEM_HOLE_NORMAL:
        case GEM_HOLE_MID_1:
        case GEM_HOLE_MID_2:
        case GEM_HOLE_MID_3:
            IntToStringFormat(_a_spriteName, "gem_%d_a_0.png", type);
            addGemSprite(_a_spriteName);
            break;
        case GEM_NORMAL://∆’Õ®±¶ Ø
        case GEM_TIME://+5√Î±¶ Ø
        {
            IntToStringFormat(_a_spriteName, "gem_0_%d_a.png", color);
            addGemSprite(_a_spriteName);
            //—€æ¶
            if (getColor()==3||getColor()==5||getColor()==6) {
                IntToStringFormat(_b1_spriteName, "gem_0_%d_b1.png", color);
                addGemSprite(_b1_spriteName);
                IntToStringFormat(_b2_spriteName, "gem_0_%d_b2.png", color);
                addGemSprite(_b2_spriteName);
            }else{
                IntToStringFormat(_b_spriteName, "gem_0_%d_b.png", color);
                addGemSprite(_b_spriteName);
            }
            IntToStringFormat(_c_spriteName, "gem_0_%d_c.png", color);
            addGemSprite(_c_spriteName);
            IntToStringFormat(_d_spriteName, "gem_0_%d_d.png", color);
            addGemSprite(_d_spriteName);
            IntToStringFormat(_e_spriteName, "gem_0_%d_e_0.png", color);
            addGemSprite(_e_spriteName);
            
            if (getColor()==3||getColor()==5||getColor()==6) {
                m_sprites[5]->setVisible(false);
            }else{
                m_sprites[4]->setVisible(false);
            }
            
            if (type == GEM_TIME) {
                IntToStringFormat(t_f_spriteName, "gem_5_%d_a.png", color);
                addGemSprite(t_f_spriteName);
            }
        }
            break;
        case GEM_V:// ˙œ˚±¶ Ø
        case GEM_H://∫·œ˚±¶ Ø
        case GEM_AREA://±¨’®±¶ Ø
        {
            int frameCounts[3] = {6,10,8};
            char _a_spriteName[30];
            sprintf(_a_spriteName,"gem_%d_%d_a_0.png",type,color);
            addGemSprite(_a_spriteName);
            CCAnimation* _a_animation = CCAnimation::create();
            for (int i=0; i<frameCounts[type-GEM_V]; i++) {
                char frameName[30];
                sprintf(frameName, "gem_%d_%d_a_%d.png",type,color,i);
                _a_animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName));
                switch (type) {
                    case GEM_V:
                        if (i == 0||i==3) {
                            _a_animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName));
                            _a_animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName));
                        }
                        if (i==3) {
                            _a_animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName));
                        }
                        break;
                    case GEM_H:
                        if (i == 0||i==5) {
                            _a_animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName));
                            _a_animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName));
                        }
                        if (i==5) {
                            _a_animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName));
                        }
                        break;
                    default:
                        break;
                }
            }
            _a_animation ->setLoops(-1);
            
            _a_animation ->setDelayPerUnit(0.1f);
            
            if (type == GEM_H) {
                _a_animation ->setDelayPerUnit(0.07f);
            }else if(type == GEM_V)
                _a_animation->setDelayPerUnit(0.08f);
            CCAnimate* _a_animate = CCAnimate::create(_a_animation);
            m_sprites[0]->runAction(_a_animate);
            addGemSprite();
            
            CCAnimation* _b_animation = CCAnimation::create();
            if (type == GEM_V||type == GEM_H) {
                for (int i=0; i<5; i++) {
                    IntToStringFormat(frameName, "gem_1_b_%d.png",i);
                    _b_animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName));
                }
                _b_animation ->setLoops(-1);
                _b_animation ->setDelayPerUnit(0.1f);
                if (type == GEM_H) {
                    m_sprites[1]->setRotation(90);
                }
            }else{
                for (int i=0; i<6; i++) {
                    IntToStringFormat(frameName, "gem_3_b_%d.png",i);
                    _b_animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName));
                }
                _b_animation ->setLoops(-1);
                _b_animation ->setDelayPerUnit(0.1f);
            }
            
            CCAnimate* _b_animate = CCAnimate::create(_b_animation);
            m_sprites[1]->runAction(_b_animate);
            
        }
            break;
        case GEM_MAGIC://ƒß∑Ω
        {
            addGemSprite("gem_4_a.png");
            addGemSprite("gem_4_b.png");
            addGemSprite("gem_4_c.png");
            m_sprites[1] ->runAction(CCRepeatForever::create(CCRotateBy::create(3.0f, 360)));
            m_sprites[2]->runAction(CCRepeatForever::create(CCSequence::create(CCFadeTo::create(0.8f, 50),CCFadeTo::create(0.8f, 255),NULL)));
        }
            break;
        case GEM_SPECIAL://æ´¡È?
        {
            IntToStringFormat(_a_spriteName, "gem_6_%d_a.png", color)
            addGemSprite(_a_spriteName);
        }
            break;
        case GEM_BEE://√€∑‰
        {
            IntToStringFormat(_a_spriteName, "gem_7_%d_a.png", color)
            addGemSprite(_a_spriteName);
            addGemSprite("gem_7_b1.png");
            addGemSprite("gem_7_b2.png");
            IntToStringFormat(_c_spriteName, "gem_7_%d_c.png", color)
            addGemSprite(_c_spriteName);
            IntToStringFormat(_d1_spriteName, "gem_7_%d_d1.png", color)
            addGemSprite(_d1_spriteName,ccp(-23, 5));
            m_sprites[4]->runAction(CCRepeatForever::create(CCSequence::create(CCRotateBy::create(0.5f, 30),CCRotateBy::create(0.2f, -30),NULL)));
            IntToStringFormat(_d2_spriteName, "gem_7_%d_d2.png", color)
            addGemSprite(_d2_spriteName,ccp(23, 5));
            m_sprites[5]->runAction(CCRepeatForever::create(CCSequence::create(CCRotateBy::create(0.5f, -30),CCRotateBy::create(0.2f, 30),NULL)));
            IntToStringFormat(_e_spriteName, "gem_7_%d_e_0.png", color)
            addGemSprite(_e_spriteName);
            m_sprites[6]->setVisible(false);
            
        }
            break;
        case GEM_EGG://µ∞
        {
            IntToStringFormat(_a_spriteName, "gem_8_%d_a.png", color)
            addGemSprite(_a_spriteName);
        }
            break;
        case GEM_COIL://Œ√œ„
        {
            addGemSprite("gem_10_a.png");
            addGemSprite("gem_10_b.png");
            addGemSprite("gem_10_c.png");
            addGemSprite("gem_10_d_0.png");
            m_sprites[3]->setVisible(false);
        }
            break;
        case GEM_GOLD://ª π⁄
        {
            addGemSprite("gem_11_a.png");
        }
            break;
        case GEM_BAO:
        {
            if (!m_gem_container) {
                return;
            }
            IntToStringFormat(_spriteName, "bao/icon_%d.png", bao_id)
            CCSprite* sprite  = CCSprite::create(_spriteName);
            m_gem_container->addChild(sprite);
            sprite->setPosition(CCPointZero);
            m_sprites.push_back(sprite);
        }
            break;
            
        default:
            break;
    }
    
    if (IsTimeBombType()) {
        CCLOG("%d",id);
        IntToStringFormat(_a_spriteName, "gem_300_%d_a.png", color)
        addGemSprite(_a_spriteName);
        IntToStringFormat(_num_spriteName, "gem_300_b_%d.png", getTimeBombLife());
        addGemSprite(_num_spriteName,ccp(-11,-6));
    }
    
}

void GemObject::replaceGem(cocos2d::CCPoint pos){
    if (m_gem_container) {
        m_gem_container->setPosition(pos);
    }
}

void GemObject::ScaleOut(){
    if (m_gem_container) {
        m_gem_container->setScale(1);
        m_gem_container->runAction(CCSequence::create(CCScaleTo::create(0.1f, 1.5f),CCScaleTo::create(0.2f, 0.3f),CCCallFuncN::create(this, callfuncN_selector(GemObject::DestoryOnCB)),NULL));
        m_gem_container = NULL;
        m_sprites.clear();
    }
}

void GemObject::ScaleIn(){
    if (m_gem_container) {
        m_gem_container->setScale(0);
        m_gem_container->runAction(CCSequence::create(CCScaleTo::create(0.3f, 1.3f),CCScaleTo::create(0.1f, 0.8f),CCScaleTo::create(0.1f, 1.1f),CCScaleTo::create(0.1f, 1.0f),NULL));
    }
}

void GemObject::update(float dt){
    if (IsBombing()) {
        m_bomb_time-=dt;
        m_bomb_time = MAX(0, m_bomb_time);
        if (m_bomb_time == 0) {
            isBombing = false;
        }
    }
    if (m_IsNewCreated) {
        m_IsNewCreated = false;
    }
    
//    if (t_getRandom(200)==0) {
//        Blink();
//    }
}

void GemObject::updatePreBomb(float dt){
    if (m_bomb_delayTime>0) {
        m_bomb_delayTime-=dt;
        m_bomb_delayTime = MAX(0, m_bomb_delayTime);
    }
}

void GemObject::Bomb(float delayTime){
    if (m_IsNewCreated) {
        return;
    }
    if (m_bomb_delayTime!=-1) {
//        if (delayTime>m_bomb_delayTime) {
//            return;
//        }
        return;
    }
    
    m_bomb_delayTime = delayTime;
}

bool GemObject::Bomb(){
    m_bomb_delayTime = -1;
    if (isEmpty()) {
        return false;
    }
    
    if (m_IsNewCreated) {
        return false;
    }
    
    GEM_TYPE  type = getType();
    
    if (type==GEM_GOLD) {
        return false;
    }
    isBombing = true;
    m_bomb_time = 0.5f;
    
    switch (type) {
     
        
        default:
        G::G_playEffect(RES_MUSIC_BOMB_0);
        break;
    }
    
    switch (type) {
        case GEM_V:
            DoSpecialBomb(SPECIAL_BOMB_V, getColor(), pos, 0);
            break;
        case GEM_H:
            DoSpecialBomb(SPECIAL_BOMB_H, getColor(), pos, 0);
            break;
        case GEM_AREA:
            DoSpecialBomb(SPECIAL_BOMB_AREA, getColor(), pos, 0);
            break;
        case GEM_VH:
            DoSpecialBomb(SPECIAL_BOMB_V, getColor(), pos, 0);
            DoSpecialBomb(SPECIAL_BOMB_H, getColor(), pos, 0.5f);
            
            break;
        case GEM_MAGIC:
        case GEM_MAGIC_NORMAL:
            DoSpecialBomb(SPECIAL_BOMB_MAGIC_NORMAL, getColor(), pos, 0);
            m_bomb_time = 1.0f;
            break;
        case GEM_3VH:
        {
            int tmpx = pos%BLOCK_NUM_W;
            int tmpy = pos/BLOCK_NUM_W;
            if (tmpy-1>=0) {
                int tmpPos = tmpx+(tmpy-1)*BLOCK_NUM_W;
                DoSpecialBomb(SPECIAL_BOMB_H, getColor(), tmpPos, 0.5f);
            }
            if (tmpy+1<BLOCK_NUM_H) {
                int tmpPos = tmpx+(tmpy+1)*BLOCK_NUM_W;
                DoSpecialBomb(SPECIAL_BOMB_H, getColor(), tmpPos, 0.5f);
            }
            DoSpecialBomb(SPECIAL_BOMB_H, getColor(), pos, 0.5f);
            
            if (tmpx-1>=0) {
                int tmpPos = tmpx-1 +tmpy*BLOCK_NUM_W;
                DoSpecialBomb(SPECIAL_BOMB_V, getColor(), tmpPos, 0);
            }
            if (tmpx+1<BLOCK_NUM_W) {
                int tmpPos = tmpx+1 +tmpy*BLOCK_NUM_W;
                DoSpecialBomb(SPECIAL_BOMB_V, getColor(), tmpPos, 0);
            }
            DoSpecialBomb(SPECIAL_BOMB_V, getColor(), pos, 0);
        }
            break;
        case GEM_3AREA:
            DoSpecialBomb(SPECIAL_BOMB_3AREA, getColor(), pos, 0);
            break;
        case GEM_MAGIC_VH:
            DoSpecialBomb(SPECIAL_BOMB_MAGIC_VH, getColor(), pos, 0);
            m_bomb_time = 1.0f;
            break;
        case GEM_MAGIC_AREA:
            DoSpecialBomb(SPECIAL_BOMB_MAGIC_AREA, getColor(), pos, 0);
            m_bomb_time = 1.0f;
            break;
        case GEM_2MAGIC:
            DoSpecialBomb(SPECIAL_BOMB_2MAGIC, getColor(), pos, 0);
            m_bomb_time = 1.0f;
            break;
        default:
            break;
    }
    
    
    switch (type) {
        case GEM_BEE:
            if (m_gem_container) {
                m_gem_container->retain();
                m_gem_layer->removeChild(m_gem_container,false);
                m_special_layer->addChild(m_gem_container);
                m_gem_container->release();
                
                CCPoint _centerPos = GetPos(pos);
                CCPoint to;
                if (_centerPos.x>_pScreenSize.width/2)
                {
                    to = ccp(_pScreenSize.width,_centerPos.y);
                }else{
                    to = ccp(0,_centerPos.y);
                }
                
                float distance = abs((long)(to.x-_centerPos.x));
                
                float _duration = distance/320;
                
                m_gem_container->runAction(CCSequence::create(CCMoveTo::create(_duration, to),CCCallFuncN::create(this, callfuncN_selector(GemObject::DestoryOnCB)), NULL));
                m_gem_container->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(0.1f, ccp(0, 30)),CCMoveBy::create(0.2f, ccp(0, -60)),CCMoveBy::create(0.1f,ccp(0, 30)),NULL)));
                m_gem_container = NULL;
                m_sprites[4]->runAction(CCRepeatForever::create(CCSequence::create(CCRotateBy::create(0.3f, 40),CCRotateBy::create(0.15f, -40),NULL)));
                m_sprites[5]->runAction(CCRepeatForever::create(CCSequence::create(CCRotateBy::create(0.3f, -40),CCRotateBy::create(0.15f, 40),NULL)));
                m_sprites.clear();
            }
            break;
        case GEM_COIL:
        {
            CCSprite* bomb_effect = CCSprite::create();
            CCAnimation* animation = CCAnimation::create();
            for (int i=0; i<5; i++) {
                char _name[30];
                sprintf(_name, "block_bomb_effect_t_2_%d.png",i);
                animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(_name));
            }
            animation->setDelayPerUnit(0.08f);
            CCAnimate* animate = CCAnimate::create(animation);
            bomb_effect->runAction(CCSequence::create(animate,CCCallFuncN::create(this, callfuncN_selector(GemObject::DestoryOnCB)),NULL));
            m_special_layer->addChild(bomb_effect);
            bomb_effect->setPosition(GetPos(pos));
            if (m_gem_container) {
                m_gem_container->removeFromParentAndCleanup(true);
                m_gem_container = NULL;
            }
            m_sprites.clear();
        }
            break;
        case GEM_MAGIC:
        case GEM_MAGIC_AREA:
        case GEM_MAGIC_NORMAL:
        case GEM_MAGIC_VH:
        case GEM_2MAGIC:
            break;
        default:
            break;
    }
    
    if (IsHoleWall()) {
        CCSprite* bomb_effect = CCSprite::create();
        CCAnimation* animation = CCAnimation::create();
        for (int i=0; i<5; i++) {
            char _name[30];
            sprintf(_name, "block_bomb_effect_t_2_%d.png",i);
            animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(_name));
        }
        animation->setDelayPerUnit(0.08f);
        CCAnimate* animate = CCAnimate::create(animation);
        bomb_effect->runAction(CCSequence::create(animate,CCCallFuncN::create(this, callfuncN_selector(GemObject::DestoryOnCB)),NULL));
        m_special_layer->addChild(bomb_effect);
        bomb_effect->setPosition(GetPos(pos));
        if (m_gem_container) {
            m_gem_container->removeFromParentAndCleanup(true);
            m_gem_container = NULL;
        }
        m_sprites.clear();
    }
    
    ScaleOut();
    if (type != GEM_BEE&&type != GEM_COIL&&!IsHoleWall()&&type!=GEM_BAO) {
        BombEffect();
    }
    
    clear();
    return true;
}

void GemObject::BombEffect(){
    CCSprite* bomb_effect = CCSprite::createWithSpriteFrameName("normal_bomb_effect_0.png");
    bomb_effect->setPosition(GetPos(pos));
    m_special_layer ->addChild(bomb_effect);
    CCAnimation* animation = CCAnimation::create();
    for (int i=0; i<9; i++) {
        IntToStringFormat(_name, "normal_bomb_effect_%d.png", i);
        animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(_name));
    }
    animation->setDelayPerUnit(0.1f);
    CCAnimate* animate = CCAnimate::create(animation);
    bomb_effect->runAction(CCSequence::create(animate,CCCallFuncN::create(this, callfuncN_selector(GemObject::DestoryOnCB)),NULL));
}


void GemObject::GoldOut(){
    isBombing = true;
    m_bomb_time = 0.5f;
    m_bomb_delayTime = -1;
    ScaleOut();
    clear();
}

void GemObject::playJumpAnim(float delay, int repeat_times,int tag){
    if (m_gem_container) {
        CCAction* action1 = CCSequence::create(CCDelayTime::create(delay),CCRepeat::create(CCSequence::create( CCScaleTo::create(0.15f, 0.8f,1.2f), CCScaleTo::create(0.2f, 1.0f), CCScaleTo::create(0.2f, 1.2f,0.8f),CCScaleTo::create(0.2f, 1),CCDelayTime::create(0.5f), NULL),repeat_times),NULL);
        
        CCAction* action2 = CCSequence::create(CCDelayTime::create(delay),CCRepeat::create(CCSequence::create( CCMoveBy::create(0.15f, ccp(0,20)),CCMoveBy::create(0.2f, ccp(0, -20)),CCMoveBy::create(0.2f, ccp(0, -10)),CCMoveBy::create(0.2f, ccp(0, 10)),CCDelayTime::create(0.5f), NULL),repeat_times),NULL);
        if (tag !=-1) {
            action1->setTag(tag);
            action2->setTag(tag+1);
        }
        
        m_gem_container->runAction(action1);
        m_gem_container->runAction(action2);
    }
}

void GemObject::showGameWinAnim(float delay){
    playJumpAnim(delay,1,50);
}

bool GemObject::hasGameWinAnim(){
    if (m_gem_container) {
        if (m_gem_container->getActionByTag(50)) {
            return true;
        }
    }
    return false;
}


void GemObject::showHelpAnim(){
    playJumpAnim(5.0, 999,98);
//    if (m_gem_container) {
//        CCAction* helpAction = CCSequence::create(CCDelayTime::create(1.0f),CCRepeat::create(CCSequence::create( CCScaleTo::create(0.15f, 0.8f,1.2f), CCScaleTo::create(0.2f, 1.0f), CCScaleTo::create(0.2f, 1.2f,0.8f),CCScaleTo::create(0.2f, 1),CCDelayTime::create(0.5f), NULL),99),NULL);
//        
//        CCAction* helpAction2 = CCSequence::create(CCDelayTime::create(1.0f),CCRepeat::create(CCSequence::create( CCMoveBy::create(0.15f, ccp(0,20)),CCMoveBy::create(0.2f, ccp(0, -20)),CCMoveBy::create(0.2f, ccp(0, -10)),CCMoveBy::create(0.2f, ccp(0, 10)),CCDelayTime::create(0.5f), NULL),99),NULL);
//        helpAction->setTag(99);
//        helpAction2->setTag(98);
//        m_gem_container->runAction(helpAction);
//        m_gem_container->runAction(helpAction2);
//    }
}

void GemObject::clearHelpAnim(){
    if (m_gem_container) {
        m_gem_container->setScale(1);
        m_gem_container->setPosition(GetPos(pos));
        m_gem_container->stopActionByTag(99);
        m_gem_container->stopActionByTag(98);
    }
}

void GemObject::setTimeBombLife(int life){
    id = getColor()+(GEM_TIME_BOMB+life)*10;
    if (m_sprites[1]) {
        IntToStringFormat(_num_spriteName, "gem_300_b_%d.png",life);
        CCSpriteFrame *frame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(_num_spriteName);
        m_sprites[1]->setDisplayFrame(frame);
        m_sprites[1]->stopAllActions();
        if (life>3) {
            m_sprites[1]->runAction(CCSequence::create(CCScaleTo::create(0.1f, 2.0f),CCScaleTo::create(0.2f, 1.0f),NULL));
        }else{
            m_sprites[1]->runAction(CCSequence::create(CCScaleTo::create(0.1f, 2.0f),CCScaleTo::create(0.3f, 0.9f),CCRepeat::create(CCSequence::create(CCScaleTo::create(0.15f, 1.5f),CCScaleTo::create(0.3f, 0.9f),NULL), 99), NULL));
        }
    }
}

void GemObject::cutTimeBomb(){
    int life = getTimeBombLife();
    if (life>0) {
        life--;
        setTimeBombLife(life);
    }
}

bool GemObject::IsSpecialGem(){
    if (getType() == GEM_V||
        getType() == GEM_H||
        getType() == GEM_AREA||
        getType() == GEM_MAGIC) {
        return true;
    }
    return false;
}

void GemObject::exChangeWithGemObject(GemObject* target){
    int tmp_id = target->id;
    target -> id = id;
    id = tmp_id;
    vector<CCSprite*> tmp_sprites;
    tmp_sprites.clear();
    for (unsigned int i=0; i< target->m_sprites.size(); i++) {
        tmp_sprites.push_back(target->m_sprites[i]);
    }
    target->m_sprites.clear();
    for (unsigned int i=0; i<m_sprites.size(); i++) {
        target->m_sprites.push_back(m_sprites[i]);
    }
    m_sprites.clear();
    for (unsigned int i=0; i<tmp_sprites.size(); i++) {
        m_sprites.push_back(tmp_sprites[i]);
    }
    CCNode* tmp = target->m_gem_container;
    target->m_gem_container = m_gem_container;
    m_gem_container = tmp;
    float tmpdelay = m_bomb_delayTime;
    m_bomb_delayTime = target->m_bomb_delayTime;
    target->m_bomb_delayTime = tmpdelay;
    
    int tmp_bao_id = target->bao_id;
    target->bao_id = bao_id;
    bao_id = tmp_bao_id;
    
}

void GemObject::toGemObject(GemObject* target){
    target->id = id;
    for (unsigned int i=0; i<m_sprites.size(); i++) {
        target->m_sprites.push_back(m_sprites[i]);
    }
    target->m_gem_container = m_gem_container;
    m_gem_container = NULL;
    m_sprites.clear();
    target->m_bomb_delayTime =m_bomb_delayTime;
    id = 0;
    m_bomb_delayTime = -1;
    target->bao_id = bao_id;
    bao_id = -1;
}

void GemObject::MoveGoAndBack(int toPos){
    CCPoint to = GetPos(toPos);
    CCPoint from = GetPos(pos);
    CCPoint offset = ccp(to.x-from.x,to.y-from.y);
    CCPoint boffset = ccp(-offset.x,-offset.y);
    isMoving = true;
    if (m_gem_container) {
        m_gem_container->runAction(CCSequence::create(CCMoveBy::create(0.15f, offset),CCMoveBy::create(0.15f,boffset),CCCallFuncN::create(this, callfuncN_selector(GemObject::MoveOver)),NULL));
    }
}

void GemObject::Move(float duration){
    isMoving = true;
    isNewMoveOver = false;
    if (m_gem_container) {
        m_gem_container->setVisible(true);
        CCPoint to = GetPos(pos);
        m_gem_container->runAction(CCSequence::create(CCMoveTo::create(duration, to),CCCallFuncN::create(this, callfuncN_selector(GemObject::MoveOver)),NULL));
    }
}

void GemObject::MoveWithNoCheck(float duration){
    isMoving = true;
    isNewMoveOver = false;
    if (m_gem_container) {
        m_gem_container->setVisible(true);
        CCPoint to = GetPos(pos);
        m_gem_container->runAction(CCSequence::create(CCMoveTo::create(duration, to),CCCallFuncN::create(this, callfuncN_selector(GemObject::MoveOverWithNoCheck)),NULL));
    }
}

void GemObject::DoorMove(){
    isMoving = true;
    isNewMoveOver = false;
    if (m_gem_container) {
        m_gem_container->setVisible(true);
        CCPoint to = GetPos(pos);
        m_gem_container->runAction(CCSequence::create(CCMoveBy::create(0.03f,ccp(0,-BLOCK_WH/2)),CCPlace::create(ccp(to.x,to.y+BLOCK_WH/2)), CCMoveBy::create(0.03f, ccp(0, -BLOCK_WH/2)),CCCallFuncN::create(this, callfuncN_selector(GemObject::MoveOver)),NULL));
    }
}


void GemObject::MoveToAndClear(float duration,CCPoint to){
    if (m_gem_container) {
        m_gem_container->setVisible(true);
        m_gem_container->runAction(CCSequence::create(CCMoveTo::create(duration,to),CCCallFuncN::create(this, callfuncN_selector(GemObject::DestoryOnCB)),NULL));
        m_gem_container = NULL;
        m_sprites.clear();
    }
    clear();
}

CCSprite* GemObject::addBeeSprite(const char* spriteName,CCPoint _pos){
    if (!m_bee_container) {
        m_bee_container = CCNode::create();
        m_special_layer->addChild(m_bee_container);
    }
    CCSprite* sprite = CCSprite::createWithSpriteFrameName(spriteName);
    sprite->setPosition(_pos);
    m_bee_container->addChild(sprite);
    return sprite;
}


void GemObject::PlayBee(){//≤•∑≈√€∑‰∂Øª≠
    //√€∑‰∂Øª≠
    if (m_has_bee) {
        return;
    }
    GEM_COLOR color = getColor();
    CCPoint to = GetPos(pos);
    CCPoint from;
    if (to.x<=_pScreenSize.width/2) {
        from = ccp(to.x-_pScreenSize.width/2, to.y);
    }else{
        from = ccp(to.x+_pScreenSize.width/2, to.y);
    }
    IntToStringFormat(_a_spriteName, "gem_7_%d_a.png", color)
    addBeeSprite(_a_spriteName);
    addBeeSprite("gem_7_b1.png");
    addBeeSprite("gem_7_b2.png");
    IntToStringFormat(_c_spriteName, "gem_7_%d_c.png", color)
    addBeeSprite(_c_spriteName);
    IntToStringFormat(_d1_spriteName, "gem_7_%d_d1.png", color)
    CCSprite* m_d1 = addBeeSprite(_d1_spriteName,ccp(-23, 5));
    m_d1->runAction(CCRepeatForever::create(CCSequence::create(CCRotateBy::create(0.1f, 45),CCRotateBy::create(0.1f, -45),NULL)));
    IntToStringFormat(_d2_spriteName, "gem_7_%d_d2.png", color)
    CCSprite* m_d2 = addBeeSprite(_d2_spriteName,ccp(23, 5));
    m_d2->runAction(CCRepeatForever::create(CCSequence::create(CCRotateBy::create(0.1f, -45),CCRotateBy::create(0.1f, 45),NULL)));
    m_bee_container->setPosition(from);
    m_bee_container->runAction(CCSequence::create(CCDelayTime::create(0.6f), CCMoveTo::create(1.0f, to),CCCallFuncN::create(this, callfuncN_selector(GemObject::onBeePlayOver)), NULL));
    m_bee_container->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(0.1f, ccp(0, 30)),CCMoveBy::create(0.2f, ccp(0, -60)),CCMoveBy::create(0.1f,ccp(0, 30)),NULL)));
    Bomb(1.6f);
    m_has_bee = true;
}

void GemObject::StopBee(){
    //Õ£÷π√€∑‰∂Øª≠
    if(m_bee_container){
        m_bee_container->removeFromParentAndCleanup(true);
        m_bee_container = NULL;
    }
    m_has_bee = false;
}


void GemObject::AddDoSpecialBombEvent(CCObject* target,SEL_DOSPECIALBOMB selector){//ÃÌº”Ãÿ ‚±¶ Ø±¨’®–ßπ˚º‡Ã˝
    this->m_doSpecailBombListener = target;
    this->m_doSpecialBombSelector = selector;
}

void GemObject::DoSpecialBomb(SPECIAL_BOMB_TYPE bomb_type,GEM_COLOR color,int pos,float delay){
    if (m_doSpecailBombListener&&m_doSpecialBombSelector) {
        (m_doSpecailBombListener->*m_doSpecialBombSelector)(bomb_type,color,pos,delay);
    }
}

void GemObject::MoveOver(CCNode* node){
    if (m_gem_container) {
        m_gem_container->setPosition(GetPos(pos));
    }
    isNewMoveOver = true;
    isMoving = false;
}

void GemObject::MoveOverWithNoCheck(cocos2d::CCNode *node){
    if (m_gem_container) {
        m_gem_container->setPosition(GetPos(pos));
    }
    isMoving = false;
}
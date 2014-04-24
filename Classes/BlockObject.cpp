//
//  BlockObject.cpp
//  Test
//
//  Created by wilford on 14-3-5.
//
//

#include "BlockObject.h"

void BlockObject::update(float dt){
    m_hasTopBombed = false;
    m_hasMidBombed = false;
    m_IsnewMoveInTop = false;
    m_IsTopNewCreated = false;
    if (m_IsTopBombing) {
        m_top_bomb_time-=dt;
        m_top_bomb_time = MAX(0, m_top_bomb_time);
        if (m_top_bomb_time == 0) {
            m_IsTopBombing = false;
        }
    }
//    if (!t_getRandom(200)) {
//        Blink();
//    }
}

void BlockObject::setBlockLayer(CCSpriteBatchNode* bottom,CCSpriteBatchNode* mid,CCSpriteBatchNode* top,CCLayer* special){
    m_bottom_layer = bottom;
    m_mid_layer = mid;
    m_top_layer = top;
    m_special_layer = special;
}

void BlockObject::create(int newid){
    id = newid;
    if (id == 0) {
        return;
    }
    drawBottom();
    drawMid();
    drawTop();
}


void BlockObject::newTop(BLOCK_TOP_TYPE top_type,int life){
    m_IsLastRoundTopNewCreated = true;
    setTopType(top_type);
    switch (top_type) {
        case BLOCK_TOP_BIG_ICE:
        case BLOCK_TOP_DIRTY:
        case BLOCK_TOP_VIRUS:
            setTopNum(1);
            break;
        case BLOCK_TOP_WALL:
            setTopNum(life);
            break;
        case BLOCK_TOP_EGG:
            setTopNum(3);
            break;
        case BLOCK_TOP_SEA_WALL:
            setTopNum(3);
        default:
            break;
    }
    drawTop();
    switch (top_type) {
        case BLOCK_TOP_DIRTY:
        case BLOCK_TOP_BIG_ICE:
        case BLOCK_TOP_PRISON:
        case BLOCK_TOP_VIRUS:
        case BLOCK_TOP_EGG:
        case BLOCK_TOP_WALL:
        //case BLOCK_TOP_SEA_WALL:
            for (unsigned int i=0; i<m_top_sprites.size(); i++) {
                if (m_top_sprites[i]) {
                    m_top_sprites[i]->setScale(0);
                    m_top_sprites[i]->runAction(CCSequence::create(CCScaleTo::create(0.3f, 1.3f),CCScaleTo::create(0.1f, 0.8f),CCScaleTo::create(0.1f, 0.11f),CCScaleTo::create(0.1f, 1.0f),NULL));
                }
            }
            break;
        case BLOCK_TOP_SEA_WALL:
            m_top_sprites[0]->setPosition(ccp(m_top_sprites[0]->getPositionX(),m_top_sprites[0]->getPositionY()-50));
            m_top_sprites[0]->setAnchorPoint(_nBottom);
            m_top_sprites[0]->setScaleY(0);
            m_top_sprites[0]->runAction(CCSequence::create(CCScaleTo::create(0.2f, 1,1.3f),CCScaleTo::create(0.1f, 1,0.8f),CCScaleTo::create(0.1f, 1,1.1f),CCScaleTo::create(0.1f, 1.0f),CCCallFuncN::create(this, callfuncN_selector(BlockObject::onSeaWallPlayOver)), NULL));
            
            break;
            
        default:
            break;
    }
}

void BlockObject::addTopSprite(const char* spriteName,CCPoint pos){
    CCSprite* sprite = CCSprite::createWithSpriteFrameName(spriteName);
    sprite->setPosition(pos);
    m_top_layer->addChild(sprite);
    m_top_sprites.push_back(sprite);
}

void BlockObject::clearTopSprites(){
    for (unsigned int i=0; i<m_top_sprites.size(); i++) {
        if (m_top_sprites[i]) {
            m_top_sprites[i]->removeFromParentAndCleanup(true);
        }
    }
    m_top_sprites.clear();
}


void BlockObject::Blink(){
    BLOCK_TOP_TYPE type = getTopType();
    switch (type) {
        case BLOCK_TOP_VIRUS:
        {
            if (m_top_sprites[3]==NULL) {
                return;
            }
            if (m_top_sprites[3]->numberOfRunningActions()>0) {
                return;
            }
            CCAnimation* animation = CCAnimation::create();
            for (int i=0; i<3; i++) {
                char _name[30];
                sprintf(_name, "block_t_51_c_%d.png",i);
                animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(_name));
            }
            animation->setDelayPerUnit(0.1f);
            CCAnimate* animate = CCAnimate::create(animation);
            m_top_sprites[3]->runAction(CCSequence::create(CCShow::create(),animate, CCHide::create(),NULL));
        }
            break;
        case BLOCK_TOP_EGG:
        {
            if (getTopNum()!=1)
                return;
            if (m_top_sprites[2]==NULL) {
                return;
            }
            if (m_top_sprites[2]->numberOfRunningActions()>0) {
                return;
            }
            CCAnimation* animation = CCAnimation::create();
            for (int i=0; i<2; i++) {
                char _name[30];
                sprintf(_name, "block_t_61_c_%d.png",i);
                animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(_name));
            }
            animation->setDelayPerUnit(0.1f);
            CCAnimate* animate = CCAnimate::create(animation);
            m_top_sprites[2]->runAction(CCSequence::create(CCShow::create(),animate,CCDelayTime::create(0.15f),CCHide::create(),NULL));
        }
            break;
        default:
            break;
    }
}

void BlockObject::drawTop(){
    m_hasTopChanged = false;
    if (!m_top_layer) {
        return;
    }
    BLOCK_TOP_TYPE type = getTopType();
    int _top = type*10+getTopNum();
    if (getTopNum() == 0 ||getTopType()==BLOCK_TOP_NONE) {
        switch (type) {
            case BLOCK_TOP_DIRTY:
            case BLOCK_TOP_BIG_ICE:
            case BLOCK_TOP_PRISON:
            case BLOCK_TOP_VIRUS:
            case BLOCK_TOP_WALL:
            case BLOCK_TOP_EGG:
            {

            }
                break;
            case BLOCK_TOP_SEA_WALL:
            {
                m_top_sprites[0]->runAction(CCSequence::create(CCScaleTo::create(0.1f, 1.5f),CCScaleTo::create(0.2f, 0.3f),CCCallFuncN::create(this, callfuncN_selector(BlockObject::DestoryOnCB)),NULL));
                m_top_sprites.clear();
            }
                break;
            default:
                break;
                
        }
        clearTopSprites();
        return;
    }
    
    clearTopSprites();
    CCPoint _centPos = GetPos(pos);
    
    IntToStringFormat(_a, "block_t_%d_a.png", _top)
    addTopSprite(_a, _centPos);
    
    switch (type) {
        case BLOCK_TOP_DIRTY:
        {
            IntToStringFormat(_b, "block_t_%d_b.png", _top)
            addTopSprite(_b, _centPos);
            m_top_sprites[1]->runAction(CCRepeatForever::create(CCRotateBy::create(4.0f, 360)));
        }
            break;
        case BLOCK_TOP_VIRUS:{
            IntToStringFormat(_b1, "block_t_%d_b1.png", _top)
            addTopSprite(_b1, _centPos);
            IntToStringFormat(_b2, "block_t_%d_b2.png", _top)
            addTopSprite(_b2, _centPos);
            IntToStringFormat(_c, "block_t_%d_c_0.png", _top)
            addTopSprite(_c, _centPos);
            m_top_sprites[3]->setVisible(false);
        }
            break;
        case BLOCK_TOP_EGG:
            if (getTopNum()==1) {
                IntToStringFormat(_b, "block_t_%d_b.png", _top)
                addTopSprite(_b, _centPos);
                IntToStringFormat(_c, "block_t_%d_c_0.png", _top)
                addTopSprite(_c, _centPos);
                m_top_sprites[2]->setVisible(false);
            }
            break;
        default:
            break;
    }
}

void BlockObject::addMidSprite(const char* spriteName,CCPoint pos){
    CCSprite* sprite = CCSprite::createWithSpriteFrameName(spriteName);
    sprite->setPosition(pos);
    m_mid_layer->addChild(sprite);
    m_mid_sprites.push_back(sprite);
}

void BlockObject::clearMidSprites(){
    for (unsigned int i=0; i<m_mid_sprites.size(); i++) {
        if (m_mid_sprites[i]) {
            m_mid_sprites[i]->removeFromParentAndCleanup(true);
        }
    }
    m_mid_sprites.clear();
}

void BlockObject::drawMid(){
    m_hasMidChanged = false;
    if (!m_mid_layer) {
        return;
    }
    
    clearMidSprites();
    
    if (getMidNum() == 0 || getMidType() == BLOCK_MID_NONE) {
        return;
    }
    
    CCPoint _centPos = GetPos(pos);
    BLOCK_MID_TYPE type = getMidType();
    int _mid = getMidType()*10+getMidNum();
    
    switch (type) {
        case BLOCK_MID_ICE:
            IntToStringFormat(_iceName, "block_m_%d_a.png", _mid);
            addMidSprite(_iceName, _centPos);
            break;
            
        default:
            break;
    }
}

void BlockObject::drawBottom(){
    if (!m_bottom_layer) {
        return;
    }
    
    BLOCK_BOTTOM_TYPE bottom_type = getBottomType();
    int bottom_num = getBottomNum();
    CCPoint _centerPos = GetPos(pos);
    if (bottom_type!=BLOCK_BOTTOM_SPACE
        &&bottom_type!=BLOCK_BOTTOM_GUN
        &&bottom_type!=BLOCK_BOTTOM_COIL_GUN
        &&G::g_game_mode == GAMEMODE_STAGE) {
        CCSprite* block = CCSprite::createWithSpriteFrameName("block.png");
        block->setPosition(_centerPos);
        m_bottom_layer->addChild(block);
    }
    
    switch (bottom_type) {
        case BLOCK_BOTTOM_ROPE://绳子 0 无绳子 1 上 2 右 4 下 8 左
            if (bottom_num&2) {
                CCSprite* rope_r = CCSprite::createWithSpriteFrameName("rope.png");
                rope_r->setPosition(ccp(_centerPos.x+BLOCK_WH/2,_centerPos.y));
                m_top_layer->addChild(rope_r);
            }
            if (bottom_num&4) {
                CCSprite* rope_d = CCSprite::createWithSpriteFrameName("rope.png");
                rope_d->setRotation(90);
                rope_d->setPosition(ccp(_centerPos.x,_centerPos.y-BLOCK_WH/2));
                m_top_layer->addChild(rope_d);
            }
            break;
        case BLOCK_BOTTOM_DOOR_IN://传送门入口
        {
            CCSprite* door_in = CCSprite::createWithSpriteFrameName("block_b_3_a.png");
            door_in->setPosition(_centerPos);
            m_bottom_layer->addChild(door_in);
            CCSprite* door_effect = CCSprite::createWithSpriteFrameName("block_door_effect.png");
            door_effect->setPosition(ccp(_centerPos.x, _centerPos.y-BLOCK_WH/2+7));
            m_top_layer->addChild(door_effect);
            door_effect->runAction(CCRepeatForever::create(CCSequence::create(CCScaleTo::create(0, 0.2f),CCScaleTo::create(0.8f, 1.3f),NULL)));
            m_bottom_rotate = CCSprite::createWithSpriteFrameName("block_door_effect_0.png");
            m_bottom_rotate->setPosition(ccp(_centerPos.x, _centerPos.y-BLOCK_WH/2+7));
            m_top_layer->addChild(m_bottom_rotate);
            m_bottom_rotate->setVisible(false);
        }
            break;
        case BLOCK_BOTTOM_DOOR_OUT://传送门出口
        {
            CCSprite* door_out = CCSprite::createWithSpriteFrameName("block_b_4_a.png");
            door_out->setPosition(_centerPos);
            m_top_layer->addChild(door_out);
            CCSprite* door_effect = CCSprite::createWithSpriteFrameName("block_door_effect.png");
            door_effect->setPosition(ccp(_centerPos.x, _centerPos.y+BLOCK_WH/2-7));
            m_top_layer->addChild(door_effect);
            door_effect->runAction(CCRepeatForever::create(CCSequence::create(CCFadeIn::create(0),CCScaleTo::create(0, 0.2f),CCScaleTo::create(0.8f, 1.1f),CCFadeOut::create(0.4f),NULL)));
            m_bottom_rotate = CCSprite::createWithSpriteFrameName("block_door_effect_0.png");
            m_bottom_rotate->setPosition(ccp(_centerPos.x, _centerPos.y+BLOCK_WH/2-7));
            m_top_layer->addChild(m_bottom_rotate);
            m_bottom_rotate->setVisible(false);
        }
            break;
        case BLOCK_BOTTOM_DIRTY_RES://污染源
        {
            CCSprite* _res = CCSprite::createWithSpriteFrameName("block_b_5_a.png");
            _res->setPosition(_centerPos);
            m_bottom_layer->addChild(_res);
            m_bottom_rotate = CCSprite::createWithSpriteFrameName("block_b_5_b.png");
            m_bottom_rotate->setPosition(_centerPos);
            m_bottom_layer->addChild(m_bottom_rotate);
            m_bottom_rotate->runAction(CCRepeatForever::create(CCRotateBy::create(4.0f, 360)));
            
        }
            break;
        case BLOCK_BOTTOM_MAGNET://吸铁石
        {
            CCSprite* magnet = CCSprite::createWithSpriteFrameName("block_b_6_a.png");
            magnet->setPosition(_centerPos);
            m_top_layer->addChild(magnet);
        }
            break;
        case BLOCK_BOTTOM_COIL_GUN ://元素1发射器
        {
            CCSprite* gun = CCSprite::createWithSpriteFrameName("block_b_7_a.png");
            gun->setPosition(_centerPos);
            m_top_layer->addChild(gun);
            m_bottom_rotate = CCSprite::createWithSpriteFrameName("block_b_7_b.png");
            m_bottom_rotate->setPosition(ccp(_centerPos.x-1, _centerPos.y-25));
            m_top_layer->addChild(m_bottom_rotate);
        }
            break;
        case BLOCK_BOTTOM_GUN://普通元素发射器
            break;
        default:
            break;
    }
}

void BlockObject::playCoilGunAnimation(){
    if (getBottomType() != BLOCK_BOTTOM_COIL_GUN) {
        return;
    }
    if (m_bottom_rotate) {
        if (m_bottom_rotate->numberOfRunningActions()==0) {
            m_bottom_rotate->runAction(CCRotateBy::create(0.6f, 180));
            
        }
    }
}

void BlockObject::playDoorAnimation(){
    if (getBottomType()!=BLOCK_BOTTOM_DOOR_IN&&
        getBottomType()!=BLOCK_BOTTOM_DOOR_OUT) {
        return;
    }
    if (m_bottom_rotate) {
        if (m_bottom_rotate->numberOfRunningActions()==0) {
            CCAnimation* animation = CCAnimation::create();
            for (int i=0; i<6; i++) {
                IntToStringFormat(_name, "block_door_effect_%d.png", i);
                animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(_name));
            }
            animation->setDelayPerUnit(0.1f);
            CCAnimate* animate = CCAnimate::create(animation);
            m_bottom_rotate->runAction(CCSequence::create(CCShow::create(),animate,CCHide::create(),NULL));
        }
    }
}

void BlockObject::moveTop(){
    if (m_top_sprites.size()==0) {
        return;
    }
    if (!m_top_sprites[0]) {
        return;
    }
    CCPoint to = GetPos(pos);
    CCPoint from = m_top_sprites[0]->getPosition();
    CCPoint offset = ccp(to.x-from.x,to.y-from.y);
    for (unsigned int i=0; i<m_top_sprites.size(); i++) {
        if (m_top_sprites[i]) {
            m_top_sprites[i]->runAction(CCMoveBy::create(0.3f, offset));
            m_top_sprites[i]->runAction(CCSequence::create(CCScaleTo::create(0.15f, 1.5f),CCScaleTo::create(0.15f, 1.0f),NULL));
        }
    }
}

void BlockObject::moveTopToBlockObject(BlockObject* blockObj){
    if (blockObj->getTopType() == BLOCK_TOP_NONE) {
        blockObj->setTopType(getTopType());
        blockObj->setTopNum(getTopNum());
        setTopType(BLOCK_TOP_NONE);
        setTopNum(0);
        for (unsigned int i=0; i<m_top_sprites.size(); i++) {
            blockObj->m_top_sprites.push_back(m_top_sprites[i]);
        }
        m_top_sprites.clear();
        blockObj->moveTop();
        blockObj->m_IsnewMoveInTop = true;
        resetBlock();
    }
}

bool BlockObject::Bomb(){
    bool isGemBomb = true;
    if (getBottomType() == BLOCK_BOTTOM_GUN||
        getBottomType() == BLOCK_BOTTOM_COIL_GUN||
        getBottomType() == BLOCK_BOTTOM_DIRTY_RES||
        getBottomType() == BLOCK_BOTTOM_SPACE) {
        isGemBomb = false;
    }
    
    
    switch (getTopType()) {
        case BLOCK_TOP_BIG_ICE:
        case BLOCK_TOP_DIRTY:
        case BLOCK_TOP_EGG:
        case BLOCK_TOP_WALL:
        case BLOCK_TOP_VIRUS:
        case BLOCK_TOP_PRISON:
        case BLOCK_TOP_SEA_WALL:
            isGemBomb = false;
            BombTop();
            break;
        default:
            break;
    }
    
    return isGemBomb;
}

void BlockObject::BombMid(){
    if (!m_hasMidBombed) {
        m_hasMidBombed = true;
        int life = getMidNum();
        life--;
        life = MAX(0, life);
        setMidNum(life);
        resetBlock();
        G::G_playEffect(RES_MUSIC_BOMB_4);
    }
}

void  BlockObject::BombTop(){
    if (m_IsTopNewCreated) {
        return;
    }
    if (!m_hasTopBombed) {
        m_hasTopBombed = true;
        int life = getTopNum();
        life--;
        life = MAX(0, life);
        setTopNum(life);
        m_IsTopBombing = true;
        m_top_bomb_time = 0.5f;
        int type = getTopType();
        switch (type) {
            case BLOCK_TOP_WALL:
            case BLOCK_TOP_PRISON:
            case BLOCK_TOP_DIRTY:
            case BLOCK_TOP_BIG_ICE:
            case BLOCK_TOP_EGG:
            case BLOCK_TOP_VIRUS:
            {
                int anim_id = type;
                if (anim_id == 5) {
                    anim_id = 2;
                }
                int frame_counts[7]={0,5,5,6,4,0,0};
                CCSprite* bomb_effect = CCSprite::create();
                CCAnimation* animation = CCAnimation::create();
                for (int i=0; i<frame_counts[anim_id]; i++) {
                    char _name[30];
                    sprintf(_name, "block_bomb_effect_t_%d_%d.png",anim_id,i);
                    animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(_name));
                }
                animation->setDelayPerUnit(0.08f);
                CCAnimate* animate = CCAnimate::create(animation);
                bomb_effect->runAction(CCSequence::create(animate,CCCallFuncN::create(this, callfuncN_selector(BlockObject::DestoryOnCB)),NULL));
                m_special_layer->addChild(bomb_effect);
                bomb_effect->setPosition(GetPos(pos));
                G::G_playEffect(RES_MUSIC_BOMB_4);
            }
                break;
                
            default:
                break;
        }
        resetBlock();
    }
}

void BlockObject::resetBlock(){
    if (m_hasTopChanged) {
        drawTop();
    }
    if (m_hasMidChanged) {
        drawMid();
    }
}

void BlockObject::setMidType(BLOCK_MID_TYPE type){
    if (type == getMidType()) {
        return;
    }
    setNum(3,type);
    m_hasMidChanged = true;
}


void BlockObject::setMidNum(int num){
    if (num == getMidNum()) {
        return;
    }
    setNum(2,num);
    m_hasMidChanged = true;
}


void BlockObject::setTopType(BLOCK_TOP_TYPE type){
    if (type == getTopType()) {
        return;
    }
    setNum(5, type);
    m_hasTopChanged = true;
}


void BlockObject::setTopNum(int num){
    if (num == getTopNum()) {
        return;
    }
    setNum(4, num);
    m_hasTopChanged = true;
}


bool BlockObject::isMatchColor(){
    if (getBottomType() == BLOCK_BOTTOM_SPACE||//空白
        getBottomType() == BLOCK_BOTTOM_DIRTY_RES||//污染源
        getBottomType() == BLOCK_BOTTOM_COIL_GUN||//元素1发射器
        getBottomType() == BLOCK_BOTTOM_GUN||//发射器
        getTopType() == BLOCK_TOP_WALL||//墙面
        getTopType() == BLOCK_TOP_DIRTY||//污染物
        getTopType() == BLOCK_TOP_BIG_ICE||//大冰块
        getTopType() == BLOCK_TOP_VIRUS||//病毒体
        getTopType() == BLOCK_TOP_EGG//精灵蛋
        ) {
        return false;
    }
    return true;
}

bool BlockObject::canMoveInFromDir(ROPE_DIR dir){
    if (!canMoveIn()) {
        return false;
    }
    if (getBottomType()==BLOCK_BOTTOM_ROPE) {
        if (getBottomNum()&dir) {
            return false;
        }
    }
    if (getBottomType() == BLOCK_BOTTOM_DOOR_IN && dir == ROPE_DIR_DOWN) {
        return false;
    }
    if (getBottomType() == BLOCK_BOTTOM_DOOR_OUT && dir == ROPE_DIR_UP) {
        return false;
    }
    return true;
}

bool BlockObject::canMoveOutFromDir(ROPE_DIR dir){
    if (!canMoveOut()) {
        return false;
    }
    if (getBottomType() == BLOCK_BOTTOM_ROPE) {
        if (getBottomNum()&dir) {
            return false;
        }
    }
    if (getBottomType()==BLOCK_BOTTOM_DOOR_IN&&dir == ROPE_DIR_DOWN) {
        return false;
    }
    if (getBottomType()==BLOCK_BOTTOM_DOOR_OUT&&dir == ROPE_DIR_UP) {
        return false;
    }
    return true;
}

bool BlockObject::canMoveOut(){
    if (getBottomType() == BLOCK_BOTTOM_SPACE||
        getBottomType() == BLOCK_BOTTOM_DIRTY_RES||
        getTopType() == BLOCK_TOP_BIG_ICE||
        getTopType() == BLOCK_TOP_DIRTY||
        getTopType() == BLOCK_TOP_EGG||
        getTopType() == BLOCK_TOP_PRISON||
        getTopType() == BLOCK_TOP_VIRUS||
        getTopType() == BLOCK_TOP_WALL||
        getTopType() == BLOCK_TOP_SEA_WALL)
    {
        return false;
    }
    return true;
}

bool BlockObject::canMoveIn(){
    if (getBottomType() == BLOCK_BOTTOM_SPACE||
        getBottomType() == BLOCK_BOTTOM_COIL_GUN||
        getBottomType() == BLOCK_BOTTOM_DIRTY_RES||
        getBottomType() == BLOCK_BOTTOM_GUN||
        getTopType() == BLOCK_TOP_DIRTY||
        getTopType() == BLOCK_TOP_EGG||
        getTopType() == BLOCK_TOP_WALL||
        getTopType() == BLOCK_TOP_SEA_WALL)
    {
        return false;
    }
    return true;
}

bool BlockObject::canDoorMoveIn(){
    if (getBottomType() == BLOCK_BOTTOM_SPACE||
        getBottomType() == BLOCK_BOTTOM_COIL_GUN||
        getBottomType() == BLOCK_BOTTOM_DIRTY_RES||
        getBottomType() == BLOCK_BOTTOM_GUN||
        getTopType() == BLOCK_TOP_BIG_ICE||
        getTopType() == BLOCK_TOP_DIRTY||
        getTopType() == BLOCK_TOP_EGG||
        getTopType() == BLOCK_TOP_PRISON||
        getTopType() == BLOCK_TOP_VIRUS||
        getTopType() == BLOCK_TOP_WALL)
    {
        return false;
    }
    return true;
}

bool BlockObject::canInsertGem(){
    if (getBottomType() == BLOCK_BOTTOM_SPACE||
        getBottomType() == BLOCK_BOTTOM_DIRTY_RES||
        getTopType() == BLOCK_TOP_DIRTY||
        getTopType() == BLOCK_TOP_EGG||
        getTopType() == BLOCK_TOP_WALL||
        getTopType() == BLOCK_TOP_SEA_WALL) {
        return false;
    }
    return true;
}

bool BlockObject::IsNewWithGem(){
    if (getNum(6)==1) {
        return true;
    }else{
        return false;
    }
}

void BlockObject::setIsNewWithGem(bool hasGem){
    if (hasGem) {
        setNum(6, 1);
    }else{
        setNum(6, 0);
    }
}
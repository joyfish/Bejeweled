//
//  GameLogic_delaycreate.cpp
//  Test
//
//  Created by wilford on 14-3-6.
//
//

#include "GameLogic_delaycreate.h"


void GameLogic_delaycreate::updateCreateGems(float dt){
    CCObject* obj;
    CCArray* toRmove = CCArray::create();
    CCARRAY_FOREACH(m_delay_create_gems, obj){
        DelayGemCreate* create_gem = (DelayGemCreate*)obj;
        create_gem->delayTime-=dt;
        create_gem->delayTime = MAX(0, create_gem->delayTime);
        if (create_gem->delayTime == 0) {
            toRmove->addObject(create_gem);
            m_gems[create_gem->pos]->create(create_gem->new_id);
            m_gems[create_gem->pos]->m_IsNewCreated = false;
            if (create_gem->bomb_delay>=-1) {
                 Bomb(create_gem->pos,create_gem->bomb_delay);
            }
        }
    }
    
    m_delay_create_gems->removeObjectsInArray(toRmove);
    toRmove->removeAllObjects();
}
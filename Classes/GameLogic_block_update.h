//
//  GameLogic_block_update.h
//  Test
//
//  Created by wilford on 14-3-6.
//
//

#ifndef __Test__GameLogic_block_update__
#define __Test__GameLogic_block_update__

#include "GameLogic_gem_update.h"

class GameLogic_block_update:public GameLogic_gem_update{
    
protected:
    GameLogic_block_update()
    :m_has_moved_virus(true)
    ,m_has_destroyed_dirty(false)
    ,m_has_infected_dirty(true)
    ,m_has_new_seawall(true)
    ,m_has_new_seavirus(true)
    {
    }
    
    void updateDestroyedBlock();
    void DoBlockEggEffect();//���鵰���������Ч
    
    void updateDirtys();
    
    void updateSeeVirus();
    void updateSeaWall();

    void updateVirus();
    void updateBlocks(float dt){
        for (int i = 0; i<BLOCK_NUM_WH; i++) {
            m_blocks[i]->update(dt);
        }
    }
    
    void updateBlockGun();
    
    int getCreateGemColor(int pos);
    
    void updateMagnet();
    void GoldOut(int pos);
    
    virtual void SeaMouthOut(){}
    
    
    bool m_has_moved_virus;//�ò��Ƿ��ƶ���������
    bool m_has_destroyed_dirty;//�ò��Ƿ�����Ⱦ�ﱻ����
    bool m_has_infected_dirty;//�ò��Ƿ��Ⱦ����Ⱦ��
    bool m_has_new_seawall;
    bool m_has_new_seavirus;
};

#endif /* defined(__Test__GameLogic_block_update__) */

//
//  GameLogic_refresh.h
//  Test
//
//  Created by wilford on 14-3-5.
//
//

#ifndef __Test__GameLogic_refresh__
#define __Test__GameLogic_refresh__

#include "GameLogic_help.h"

class DelayGemCreate:public CCObject{
public:
    int pos;
    int new_id;
    float delayTime;
    float bomb_delay;
    DelayGemCreate(int pos,int new_id,float delayTime,float bomb_delay=-1){
		autorelease();
        this->pos = pos;
        this->new_id = new_id;
        this->delayTime = delayTime;
        this->bomb_delay = bomb_delay;
    }
};

class DelayGemClear:public CCObject{
public:
    int pos;
    float delayTime;
    
    DelayGemClear(int pos,float delayTime)
    {
		autorelease();
        this->pos = pos;
        this->delayTime = delayTime;
    }
};

class GameLogic_refresh : public GameLogic_help{
public:
    
	bool IsRefreshTime(){//是否在刷新地图
		if (m_delay_scalein_gems) {
			if (m_delay_scalein_gems->count()>0) {
				return true;
			}
		}

		if (m_delay_scaleout_gems) {
			if (m_delay_scaleout_gems->count()>0) {
				return true;
			}
		}

		return false;
	}
    
private:
    void checkdata();
    
    bool isclear(int index);
    
    void checkSgem();
    
    void insertSgem(int index, int c){
        data[index] = c;
    }
    
    void insertNgem(int index, int c){
        data[index] = c;
        if (c>0) {
            NCNUM[c-1]--;
        }
        
    }
    
    bool SearchAddgems(int type, int c);
    void addgem();
    
    int getNCAllNum();
    
    void getmaxColor();
    
   
    
    
protected:
    bool hasMatchColor(){
        int tmp_gems[BLOCK_NUM_WH];
        for (int i=0; i<BLOCK_NUM_WH; i++) {
            if (data[i]>0) {
                tmp_gems[i]= data[i];
            }else{
                tmp_gems[i] = m_gems[i]->id;
            }
        }
        for (int i=0; i<BLOCK_NUM_WH; i++) {
            if (tmp_gems[i]== 0) {
                continue;
            }
            if (!m_blocks[i]->canMoveIn()) {
                continue;
            }
            int tmpx = i%BLOCK_NUM_W;
            int tmpy = i/BLOCK_NUM_W;
            int tmpx_r = tmpx+1;
            int tmpy_d = tmpy+1;
            do{
                if (tmpx_r>=BLOCK_NUM_W) {
                    break;
                }
                int tmpPos = tmpx_r+tmpy*BLOCK_NUM_W;
                if (tmp_gems[tmpPos]==0) {
                    break;
                }
                if (!canGemMoveToBlock(i, tmpPos)) {
                    break;
                }
                if (!canGemMoveToBlock(tmpPos, i)) {
                    break;
                }
                
                int tmp = tmp_gems[i];
                tmp_gems[i] = tmp_gems[tmpPos];
                tmp_gems[tmpPos] = tmp;
                
                if (matchColors(i,tmp_gems)) {
                    return true;
                }
                if (matchColors(tmpPos,tmp_gems)) {
                    return true;
                }
                tmp = tmp_gems[i];
                tmp_gems[i] = tmp_gems[tmpPos];
                tmp_gems[tmpPos] = tmp;
            }while(0);
            
            do{
                if (tmpy_d>=BLOCK_NUM_H) {
                    break;
                }
                int tmpPos = tmpx+tmpy_d*BLOCK_NUM_W;
                if (tmp_gems[tmpPos]==0) {
                    break;
                }
                if (!canGemMoveToBlock(i, tmpPos)) {
                    break;
                }
                if (!canGemMoveToBlock(tmpPos, i)) {
                    break;
                }
                
                int tmp = tmp_gems[i];
                tmp_gems[i] = tmp_gems[tmpPos];
                tmp_gems[tmpPos] = tmp;
                
                if (matchColors(i,tmp_gems)) {
                    return true;
                }
                if (matchColors(tmpPos,tmp_gems)) {
                    return true;
                }
                tmp = tmp_gems[i];
                tmp_gems[i] = tmp_gems[tmpPos];
                tmp_gems[tmpPos] = tmp;
            }while(0);
        }
        return false;
    }
    
	GameLogic_refresh()
	{
		m_delay_scalein_gems = new CCArray();
		m_delay_scaleout_gems = new CCArray();
	}



	~GameLogic_refresh(){
		m_delay_scalein_gems->removeAllObjects();
		CC_SAFE_DELETE(m_delay_scalein_gems);
		m_delay_scaleout_gems->removeAllObjects();
		CC_SAFE_DELETE(m_delay_scaleout_gems);
		S_gemlist.clear();
		gemindexlist.clear();
	}

	bool updata(bool isnew = false);
    
    bool updateData(int type,bool isnew);
    
    void updateScaleInAndOutGems(float dt);
      
    virtual void RefreshGems();
    
    
    int m_maxColor;
    
    CCArray* m_delay_scaleout_gems;
    CCArray* m_delay_scalein_gems;
    
    std::vector<int> S_gemlist;
	std::vector<int> gemindexlist;
	int data[BLOCK_NUM_WH];
	int NCNUM[GEM_COLOR_NOCOLOR-1];
	int NCLIST[GEM_COLOR_NOCOLOR-1];
	int SCNUM[GEM_COLOR_NOCOLOR-1];
};

#endif /* defined(__Test__GameLogic_refresh__) */

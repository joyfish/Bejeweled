//
//  GameLogic_refresh.cpp
//  Test
//
//  Created by wilford on 14-3-5.
//
//

#include "GameLogic_refresh.h"

void GameLogic_refresh::updateScaleInAndOutGems(float dt){
    CCObject* obj;
    CCArray* toRmove = CCArray::create();
    CCARRAY_FOREACH(m_delay_scaleout_gems, obj){
        DelayGemClear* clear_gem = (DelayGemClear*)obj;
        clear_gem->delayTime-=dt;
        clear_gem->delayTime = MAX(0, clear_gem->delayTime);
        if (clear_gem->delayTime == 0) {
            toRmove->addObject(clear_gem);
            m_gems[clear_gem->pos]->ScaleOut();
            m_gems[clear_gem->pos]->clear();
        }
    }
    
    m_delay_scaleout_gems->removeObjectsInArray(toRmove);
    toRmove->removeAllObjects();
    
    CCARRAY_FOREACH(m_delay_scalein_gems, obj){
        DelayGemCreate* create_gem = (DelayGemCreate*)obj;
        create_gem->delayTime-=dt;
        create_gem->delayTime = MAX(0, create_gem->delayTime);
        if (create_gem->delayTime == 0) {
            toRmove->addObject(create_gem);
            m_gems[create_gem->pos]->newGem(create_gem->new_id);
            m_gems[create_gem->pos]->ScaleIn();
        }
    }
    m_delay_scalein_gems->removeObjectsInArray(toRmove);
    toRmove->release();
}

bool GameLogic_refresh::updateData(int type,bool isnew){
    
    checkdata();
    getmaxColor();
    checkSgem();
    if(!isnew){
        //            //for(int i =0; i < GEM_COLOR_NOCOLOR-1; i++){
        int c = 1+t_getRandom(m_maxColor);
        while(NCNUM[c-1]< 3){
            c = 1+t_getRandom(m_maxColor);
        }
        
        
        if(!SearchAddgems(type,c)){
            CCLOG("noInsertPlace!!");
        }
        
        //if(SearchAddgems(0,1+t_getRandom(GEM_COLOR_NOCOLOR-1)))
        //	break;
        //	}
    }
    addgem();
    return hasMatchColor();
}

bool GameLogic_refresh::updata(bool isnew){
	
    int types[4] = {0,1,2,3};
    int len = 4;
    while (len>=0) {
        int type_id = t_getRandom(len);
        int type = types[type_id];
        if (updateData(type,isnew)) {
            return true;
        }
        types[type_id]= types[len-1];
        len--;
    }
    
    
    return false;
    //    //m_maxColor = GEM_COLOR_NOCOLOR;
    //    checkdata();
    //    getmaxColor();
    //    checkSgem();
    //    		if(!isnew){
    //    //            //for(int i =0; i < GEM_COLOR_NOCOLOR-1; i++){
    //    int c = 1+t_getRandom(m_maxColor-1);
    //    while(NCNUM[c-1]< 3){
    //        c = 1+t_getRandom(m_maxColor-1);
    //    }
    //
    //
    //    if(!SearchAddgems(t_getRandom(4),c)){
    //        CCLOG("noInsertPlace!!");
    //    }
    //
    //    //if(SearchAddgems(0,1+t_getRandom(GEM_COLOR_NOCOLOR-1)))
    //    //	break;
    //    //	}
    //           }
    //
    //    addgem();
}


void GameLogic_refresh::checkdata(){
    S_gemlist.clear();
    gemindexlist.clear();
    for(int i =0; i < GEM_COLOR_NOCOLOR-1; i++){
        NCNUM[i] = 0;
        SCNUM[i] = 0;
    }
    
    for(int i = 0; i < BLOCK_NUM_WH; i++)
    {
        data[i] = -1;
        
		if (m_gems[i]->isEmpty()) {
			if(m_blocks[i]->IsNewWithGem()){
				gemindexlist.push_back(i);
				data[i] = 0;
			}
			continue;
		}
        
        if(m_gems[i]->getType() == GEM_NORMAL&& m_gems[i]->getColor() != GEM_COLOR_NOCOLOR){
            if(m_blocks[i]->getTopType() == 0&&m_blocks[i]->getBottomType() != BLOCK_BOTTOM_COIL_GUN&&m_blocks[i]->getBottomType() != BLOCK_BOTTOM_GUN){
                if(!m_blocks[i]->IsNewWithGem()){
                    gemindexlist.push_back(i);
                    NCNUM[m_gems[i]->getColor()-1]++;
                    data[i] = 0;
                }
                else
                    data[i] = m_gems[i]->id;
            }
            else if(m_blocks[i]->getTopType() == BLOCK_TOP_PRISON){
                data[i] = m_gems[i]->id;
            }
        }
        else if(m_gems[i]->getType() !=  GEM_GOLD&&m_gems[i]->getType() != GEM_NORMAL&& m_gems[i]->getColor() != GEM_COLOR_NOCOLOR){
            if(m_blocks[i]->getTopType() == 0&&m_blocks[i]->getBottomType() != BLOCK_BOTTOM_COIL_GUN&&m_blocks[i]->getBottomType() != BLOCK_BOTTOM_GUN){
                if(m_gems[i]->IsTimeBombType()){
                    data[i] = m_gems[i]->id;
                }else if(!m_blocks[i]->IsNewWithGem()){
					gemindexlist.push_back(i);
                    S_gemlist.push_back(m_gems[i]->id);
                    SCNUM[m_gems[i]->getColor()-1]++;
                    data[i] = 0;
                }
                else
                    data[i] = m_gems[i]->id;
                
            }
            else if(m_blocks[i]->getTopType() == BLOCK_TOP_PRISON){
				gemindexlist.push_back(i);
                data[i] = m_gems[i]->id;
            }
        }
    }
}

bool GameLogic_refresh::isclear(int index){
    if(data[index] == 0 && m_blocks[index]->getBottomType() != BLOCK_BOTTOM_SPACE&&m_blocks[index]->getBottomType() != BLOCK_BOTTOM_DIRTY_RES&&m_blocks[index]->getBottomType() != BLOCK_BOTTOM_COIL_GUN&&m_blocks[index]->getBottomType() != BLOCK_BOTTOM_GUN)
        return true;
    return false;
}

void GameLogic_refresh::checkSgem(){
    for ( int i = 0; i < S_gemlist.size();)
    {
        int c =t_getRandom(gemindexlist.size()-1);
        int index = gemindexlist[c];
        int id = S_gemlist[i];
        while(!isclear(index)){
            c =t_getRandom(gemindexlist.size()-1);
            index = gemindexlist[c];
        }
        insertSgem(index, id);
        while(matchColors(index, data)){
            insertSgem(index, 0);
            index = BLOCK_NUM_W+t_getRandom(BLOCK_NUM_WH-BLOCK_NUM_W);
        }
        S_gemlist.erase(S_gemlist.begin());
        
    }
}

bool GameLogic_refresh::SearchAddgems(int type, int c){
    for(int i = BLOCK_NUM_W; i <  BLOCK_NUM_WH; i++){
        switch(type){
            case 0:
                if(i%BLOCK_NUM_W+2< BLOCK_NUM_W&&i/BLOCK_NUM_W+1 < BLOCK_NUM_H){
                    if(isclear(i)&&isclear(i+1)&&isclear(i+2)&&isclear(i+BLOCK_NUM_W)&&isclear(i+BLOCK_NUM_W+1)&&isclear(i+BLOCK_NUM_W+2))
                    {
                        insertNgem(i,c);
                        if(matchColors(i, data)){
                            data[i] =0;
                            NCNUM[c-1]++;
                            continue;
                        }
                        insertNgem(i+2,c);
                        if(matchColors(i+2, data)){
                            data[i]=0;
                            data[i+2]=0;
                            NCNUM[c-1]+= 2;
                            continue;
                        }
                        insertNgem(i+BLOCK_NUM_W+1,c);
                        if(matchColors(i+BLOCK_NUM_W+1, data)){
                            data[i] = 0;
                            data[i+2]=0;
                            data[i+BLOCK_NUM_W+1]=0;
                            NCNUM[c-1]+= 3;
                            continue;
                        }
                        
                        return true;
                    }
                }
                break;
            case 1:
                if(i%BLOCK_NUM_W+1< BLOCK_NUM_W&&i/BLOCK_NUM_W+2 < BLOCK_NUM_H){
                    if(isclear(i)&&isclear(i+1)&&isclear(i+BLOCK_NUM_W)&&isclear(i+BLOCK_NUM_W+1)&&isclear(i+2*BLOCK_NUM_W)&&isclear(i+2*BLOCK_NUM_W+1))
                    {
                        insertNgem(i,c);
                        if(matchColors(i, data)){
                            data[i]=0;
                            NCNUM[c-1]++;
                            continue;
                        }
                        insertNgem(i+BLOCK_NUM_W,c);
                        if(matchColors(i+BLOCK_NUM_W, data)){
                            data[i]=0;
                            data[i+BLOCK_NUM_W]=0;
                            NCNUM[c-1]+= 2;
                            continue;
                        }
                        insertNgem(i+2*BLOCK_NUM_W+1,c);
                        if(matchColors(i+2*BLOCK_NUM_W+1, data)){
							data[i]=0;
							data[i+BLOCK_NUM_W]=0;
							data[i+2*BLOCK_NUM_W+1]=0;
                            NCNUM[c-1]+= 3;
                            continue;
                        }
                        
                        return true;
                    }
                }
                break;
            case 2:
                if(i%BLOCK_NUM_W+3< BLOCK_NUM_W){
                    if(isclear(i)&&isclear(i+1)&&isclear(i+2)&&isclear(i+3))
                    {
                        insertNgem(i,c);
                        if(matchColors(i, data)){
                            data[i]=0;
                            NCNUM[c-1]++;
                            continue;
                        }
                        insertNgem(i+1,c);
                        if(matchColors(i+1, data)){
                            data[i]=0;
                            data[i+1]=0;
                            NCNUM[c-1]+= 2;
                            continue;
                        }
                        insertNgem(i+3,c);
                        if(matchColors(i+3, data)){
                            data[i]=0;
                            data[i+1]=0;
                            data[i+3]=0;
                            NCNUM[c-1]+= 3;
                            continue;
                        }
                        
                        return true;
                    }
                }
                break;
            case 3:
                if(i/BLOCK_NUM_W+3< BLOCK_NUM_H){
                    if(isclear(i)&&isclear(i+BLOCK_NUM_W)&&isclear(i+2*BLOCK_NUM_W)&&isclear(i+3*BLOCK_NUM_W))
                    {
                        insertNgem(i,c);
                        if(matchColors(i, data)){
                            data[i]=0;
                            NCNUM[c-1]++;
                            continue;
                        }
                        insertNgem(i+BLOCK_NUM_W,c);
                        if(matchColors(i+BLOCK_NUM_W, data)){
                            data[i]=0;
                            data[i+BLOCK_NUM_W]=0;
                            NCNUM[c-1]+= 2;
                            continue;
                        }
                        insertNgem(i+3*BLOCK_NUM_W,c);
                        if(matchColors(i+3*BLOCK_NUM_W, data)){
                            insertNgem(i,0);
                            insertNgem(i+BLOCK_NUM_W,0);
                            insertNgem(i+3*BLOCK_NUM_W,0);
                            NCNUM[c-1]+= 3;
                            continue;
                        }
                        
                        return true;
                    }
                }
                break;
        }
        
    }
    return false;
}

void GameLogic_refresh::addgem(){
    for(int i = BLOCK_NUM_WH-1; i >= BLOCK_NUM_W; i--){
        bool isadd = false;
        if(getNCAllNum() > 0&&isclear(i)){
            getmaxColor();
            for(int j =t_getRandom(m_maxColor/2); j < m_maxColor; j++){
                if(!isadd){
                    insertNgem(i,NCLIST[j]);
                    if(matchColors(i, data)){
                        insertNgem(i,0);
                        NCNUM[NCLIST[j]-1]++;
                    }
                    else{
                        isadd = true;
						
						/*if (i==BLOCK_NUM_WH-1)
                         {
                         data[i] = 1;
                         CCLOG("lastgem11 %d",data[i]);
                         }*/
					}
                }
            }
			/*if (i==BLOCK_NUM_WH-1)
             {
             CCLOG("lastgem11 %d",data[i]);
             }*/
			
			/*if (data[BLOCK_NUM_WH-1]!=1)
             {
             CCLOG("lastgem11 %d %d",i, data[BLOCK_NUM_WH-1]);
             }
             */
			
        }
    }
    //if(getNCAllNum() > 0){
    for(int i = BLOCK_NUM_WH-1; i >= BLOCK_NUM_W; i--){
        bool isadd = false;
        // if(isclear(i)){
        //       getmaxColor();
        //       for(int j =0; j < m_maxColor; j++){
        //                if(!isadd){
        //                    insertNgem(i,j+1);
        //                    if(matchColors(i, data)){
        //                        insertNgem(i,0);
        //                    }
        //                    else
        //                        isadd = true;
        //                }
        if(isclear(i)){
            getmaxColor();
            //                    if(NCNUM[NCLIST[0] - 1] == 0){
            if(gemindexlist.size()>0){
                
                while(!isadd){
                    insertNgem(i,t_getRandom(m_maxColor)+1);
                    if(matchColors(i, data)){
                        insertNgem(i,0);
                    }
                    else{
                        isadd = true;
                        /*if (i==BLOCK_NUM_WH-1)
                         {
                         CCLOG("lastgem22 %d",data[i]);
                         }*/
                    }
                }
                //                    }
                //                    else {
                //                        for(int j =0; j < m_maxColor-1; j++){
                //                            if(!isadd){
                //                                insertNgem(i,j+1);
                //                                if(matchColors(i, data)){
                //                                    insertNgem(i,0);
                //                                }
                //                                else
                //                                    isadd = true;
                //                            }
                //                        }
                //                    }
            }
			//	}
            // }
        }
		
		/*if (data[BLOCK_NUM_WH-1]!=1)
         {
         CCLOG("lastgem22 %d %d",i, data[BLOCK_NUM_WH-1]);
         }*/
    }
    //}
}

int GameLogic_refresh::getNCAllNum(){
    int t = 0;
    for(int i =0; i < GEM_COLOR_NOCOLOR-1; i++){
        t +=NCNUM[i];
    }
    return t;
}



void GameLogic_refresh::getmaxColor(){
    int tempNCNUM[GEM_COLOR_NOCOLOR-1];
    for(int i =0; i < GEM_COLOR_NOCOLOR-1; i++){
        NCLIST[i] = i+1;
        tempNCNUM[i] = NCNUM[i];
    }
    for(int i = 0;i<GEM_COLOR_NOCOLOR-1;i++){
        for(int j = i;j<GEM_COLOR_NOCOLOR-1;j++){
            if(tempNCNUM[i]<= tempNCNUM[j]){
                int temp = tempNCNUM[i];
                tempNCNUM[i] = tempNCNUM[j];
                tempNCNUM[j] = temp;
                temp = NCLIST[i];
                NCLIST[i] = NCLIST[j];
                NCLIST[j] = temp;
            }
        }
    }
}

void GameLogic_refresh::RefreshGems(){
    clearHelp();
    if(!updata()){
        game_lose();
        return;
    }
    
    float delay = 0;
    for (int y =0; y<BLOCK_NUM_H; y++) {
        bool hasData = false;
        for (int x=0; x<BLOCK_NUM_W; x++) {
            int id = x+y*BLOCK_NUM_W;
            if (data[id]>0) {
                hasData = true;
                m_delay_scaleout_gems->addObject(new DelayGemClear(id,delay));
            }
        }
        if (hasData) {
            delay+=0.2f;
        }
    }
    
    float lastdelay = delay;
    delay = 0;
    
    for (int y =0; y<BLOCK_NUM_H; y++) {
        bool hasData = false;
        for (int x=0; x<BLOCK_NUM_W; x++) {
            int id = x+y*BLOCK_NUM_W;
            if (data[id]>0) {
                hasData = true;
                m_delay_scalein_gems->addObject(new DelayGemCreate(id,data[id],lastdelay+delay));
            }
        }
        if (hasData) {
            delay+=0.2f;
        }
    }
    
//    for (int i=0; i<BLOCK_NUM_WH; i++) {
//        if(data[i]>0){
//            //m_gems[i]->clear();
//            m_delay_scaleout_gems->addObject(new DelayGemClear(i,(i/BLOCK_NUM_W)*0.2f));
//        }
//    }
    
//    for (int i=0; i<BLOCK_NUM_WH; i++) {
//        if(data[i]>0){
//            //m_gems[i]->newGem(data[i]);
//            m_delay_scalein_gems->addObject(new DelayGemCreate(i,data[i],2.0f+(i/BLOCK_NUM_W)*0.2f));
//        }
//    }
    
    //        int gem_ids[BLOCK_NUM_WH];
    //        for (int i =0; i<BLOCK_NUM_WH; i++) {
    //            gem_ids[i] = m_gems[i]->id;
    //        }
    //        for (int i=0; i<BLOCK_NUM_WH; i++) {
    //            if (matchColors(i, gem_ids)) {
    //                CCLOG("[matchColor]: %d [%d]",i,gem_ids[i]);
    //            }
    //        }
    
}
//
//  GameLogic_match.cpp
//  Test
//
//  Created by wilford on 14-3-5.
//
//

#include "GameLogic_match.h"




void GameLogic_match::updateMatchColor(){
    for (int i=0; i<BLOCK_NUM_WH; i++) {
        if (!m_gems[i]->IsNewMoveOver()) {
            continue;
        }
        if (!m_gems[i]->IsExchangeMove&&!m_gems[i]->IsHoleWall()) {
            G::G_playEffect(RES_MUSIC_GEM_COLLIDER);
            if (m_gems[i]->m_gem_container) {
                m_gems[i]->m_gem_container->runAction(CCSequence::create(CCScaleTo::create(0.06f, 1.2f,0.8f),CCScaleTo::create(0.1f, 1),NULL));
                m_gems[i]->m_gem_container->runAction(CCSequence::create(CCMoveBy::create(0.06f, ccp(0, -10)),CCMoveBy::create(0.1f, ccp(0, 10)),NULL));
            }
        }else{
            m_gems[i]->IsExchangeMove = false;
        }
        
        matchColors(i);
    }
}

bool GameLogic_match::matchColors(int pos,int* gem_ids){
    if (pos >= BLOCK_NUM_WH||pos<0) {
        return false;
    }
    
    if (gem_ids[pos] <= 0) {
        return false;
    }
    
    if (!m_blocks[pos]->isMatchColor()) {
        //CCLOG("[machColor]:invalid block");
        return false;
    }
    
    if (gem_ids[pos]%10 == GEM_COLOR_NOCOLOR) {//无色宝石不参与匹配
        //CCLOG("[machColor]:noColor gem");
        return false;
    }
    
    int _color = gem_ids[pos]%10;
    
    CCPoint offsets[4][2]={
        {ccp(-1,0),ccp(-2, 0)},
        {ccp(1,0),ccp(2, 0)},
        {ccp(0,-1),ccp(0, -2)},
        {ccp(0, 1),ccp(0, 2)}
    };
    int _count;
    
    for (int i=0; i<4 ; i++) {
        for (int j=0; j<2; j++) {
            if (i%2==0&&j==0) {
                _count =1;
            }
            int tmpx = pos%BLOCK_NUM_W;
            int tmpy = pos/BLOCK_NUM_W;
            tmpx += offsets[i][j].x;
            tmpy += offsets[i][j].y;
            if (tmpx < 0) {
                break;
            }
            if (tmpx>=BLOCK_NUM_W) {
                break;
            }
            if (tmpy<0){
                break;
            }
            if (tmpy>=BLOCK_NUM_H) {
                break;
            }
            int tmpPos = tmpy*BLOCK_NUM_W+tmpx;
            if (!m_blocks[tmpPos]->isMatchColor()) {
                break;
            }
            
            if (gem_ids[tmpPos]%10 != _color) {
                break;
            }
            
            _count++;
            if (_count>=3) {
                return true;
            }
        }
    }
    
    return  false;
}

bool GameLogic_match::IsMatchColor(int pos,int newPos){
    if (!m_blocks[newPos]->isMatchColor()){
        return false;
    }
    
    if (m_gems[newPos]->IsMoving()) {
        return false;
    }
    
    if (m_gems[newPos]->HasBee())
    {
        return false;
    }
    
    
    if (m_gems[newPos]->getColor() == GEM_COLOR_NOCOLOR) {//无色宝石不参与匹配
        return false;
    }
    
    if (m_gems[newPos]->getColor()!=m_gems[pos]->getColor()) {
        return false;
    }
    
    return true;
}

void GameLogic_match::matchColor(int pos){
    if (isMatchIgnorePos(pos)){
        return;
    }
    m_match_ignore_pos.push_back(pos);
    if (pos >= BLOCK_NUM_WH||pos<0) {
        return;
    }
    
    if (!m_blocks[pos]->isMatchColor()) {
        return;
    }
    
    if (m_gems[pos]->isEmpty()) {
        return;
    }
    
    if (m_gems[pos] ->IsMoving()) {
        return;
    }
    
    if (m_gems[pos]->HasBee())
    {
        return;
    }
    
    
    
    if (m_gems[pos]->getColor() == GEM_COLOR_NOCOLOR) {//无色宝石不参与匹配
        return;
    }
    
    vector<int> _hPos;
    vector<int> _vPos;
    _hPos.push_back(pos);
    _vPos.push_back(pos);
    
    int _ofx = -1;
    while (true) {//左
        int tmpx = pos%BLOCK_NUM_W;
        int tmpy = pos/BLOCK_NUM_W;
        tmpx += _ofx;
        if (tmpx<0) {
            break;
        }
        int tmpPos = tmpy*BLOCK_NUM_W+tmpx;
        if (!IsMatchColor(pos, tmpPos)) {
            break;
        }
        _hPos.push_back(tmpPos);
        //            _hcount++;
        //            hGems->addObject(m_gems[tmpPos]);
        _ofx--;
    }
    _ofx = 1;
    while (true) {//右
        int tmpx = pos%BLOCK_NUM_W;
        int tmpy = pos/BLOCK_NUM_W;
        tmpx += _ofx;
        if (tmpx>=BLOCK_NUM_W) {
            break;
        }
        int tmpPos = tmpy*BLOCK_NUM_W+tmpx;
        if (!IsMatchColor(pos, tmpPos)) {
            break;
        }
        _hPos.push_back(tmpPos);
        //            _hcount++;
        //            hGems->addObject(m_gems[tmpPos]);
        _ofx++;
    }
    
    int _ofy = -1;
    while (true) {//上
        int tmpx = pos%BLOCK_NUM_W;
        int tmpy = pos/BLOCK_NUM_W;
        tmpy += _ofy;
        if (tmpy<0) {
            break;
        }
        int tmpPos = tmpy*BLOCK_NUM_W+tmpx;
        
        if (!IsMatchColor(pos, tmpPos)) {
            break;
        }
        _vPos.push_back(tmpPos);
        //            _vcount++;
        //            vGems->addObject(m_gems[tmpPos]);
        _ofy--;
    }
    
    _ofy = 1;
    while (true) {//下
        int tmpx = pos%BLOCK_NUM_W;
        int tmpy = pos/BLOCK_NUM_W;
        tmpy += _ofy;
        if (tmpy>=BLOCK_NUM_H) {
            break;
        }
        int tmpPos = tmpy*BLOCK_NUM_W+tmpx;
        
        if (!IsMatchColor(pos, tmpPos)) {
            break;
        }
        _vPos.push_back(tmpPos);
        //            _vcount++;
        //            vGems->addObject(m_gems[tmpPos]);
        _ofy++;
    }
    
    if (_vPos.size()<3) {
        _vPos.clear();
    }
    if (_hPos.size()<3) {
        _hPos.clear();
    }
    
    
    AddMatchClearPos(_vPos);
    AddMatchClearPos(_hPos);
    
    NewSpcialGemInfos* infos = new NewSpcialGemInfos(pos);
    if (_vPos.size()>=3&&_hPos.size()>=3) {
        infos->gem_area_count++;
    }
    if (_vPos.size()>=5) {
        infos->gem_magic_count++;
    }else if(_vPos.size()>=4){
        infos->gem_h_count++;
    }
    if (_hPos.size()>=5) {
        infos->gem_magic_count++;
    }else if(_hPos.size()>=4){
        infos->gem_v_count++;
    }
    
    
    if (infos->hasNewSpecialGem()) {
        if (infos->gem_area_count==0) {
            if (m_match_new_gem_type.size()==0) {
                m_match_new_gem_type.push_back(infos);
            }
        }else{
            m_match_new_gem_type.push_back(infos);
        }
    }
    
    for (unsigned int i=0; i<_vPos.size(); i++) {
        matchColor(_vPos[i]);
    }
    for (unsigned int i=0; i<_hPos.size(); i++) {
        matchColor(_hPos[i]);
    }
    
    _vPos.clear();
    _hPos.clear();
}

bool GameLogic_match::isMatchIgnorePos(int pos){
    for (vector<int>::iterator it= m_match_ignore_pos.begin(); it<m_match_ignore_pos.end(); it++) {
        if (*it == pos) {
            return true;
        }
    }
    return false;
}

void GameLogic_match::AddMatchClearPos(vector<int> clear_pos){
    if (clear_pos.size()==0) {
        return;
    }
    m_match_clear_pos.insert(m_match_clear_pos.begin(), clear_pos.begin(),clear_pos.end());
    //         cout<<"--------start--------\n";
    //        for (int i=0; i<m_match_clear_pos.size(); i++) {
    //            cout<<m_match_clear_pos[i]<<" ";
    //        }
    //        cout<<"\n";
    //        cout<<"remove ";
    
    /*vector<int>::iterator it = m_match_clear_pos.begin();
     while(it!=m_match_clear_pos.end()){
     it = m_match_clear_pos.erase(it);
     }*/
    
    vector<int>::iterator it = m_match_clear_pos.begin();
    while(it!=m_match_clear_pos.end()){
        vector<int>::iterator tmpit = it+1;
        bool isErased = false;
        while(tmpit!=m_match_clear_pos.end()){
            if (*it==*tmpit)
            {
                it = m_match_clear_pos.erase(it);
                isErased = true;
                break;
            }
            tmpit++;
        }
        if (!isErased)
        {
            it++;
        }
    }
    
    //   for (vector<int>::iterator it = m_match_clear_pos.begin(); it<m_match_clear_pos.end(); it++) {
    //       for (vector<int>::iterator tmpit = it+1; tmpit<m_match_clear_pos.end(); tmpit++) {
    //           if (*it == *tmpit) {
    //               //cout<<*it<<" ";
    //
    //               it = m_match_clear_pos.erase(it);
    //it--;
    //               break;
    //           }
    //       }
    //   }
    //        cout<<"\n";
    //        for (int i=0; i<m_match_clear_pos.size(); i++) {
    //            cout<<m_match_clear_pos[i]<<" ";
    //        }
    //        cout<<"\n";
}

bool GameLogic_match::matchColors(int pos,bool ishelp){
    m_match_ignore_pos.clear();
    m_match_clear_pos.clear();
    m_match_new_gem_type.clear();
    int color = m_gems[pos]->getColor();
    
    matchColor(pos);
    
    bool hasBombs = false;
    
    if (m_match_clear_pos.size()>0) {
        if (!ishelp) {
            Combo();
        }
        hasBombs = true;
    }
    
    if (m_match_new_gem_type.size()>1) {
        vector<NewSpcialGemInfos*>::iterator it;
        for ( it= m_match_new_gem_type.begin();it<m_match_new_gem_type.end();it++) {
            NewSpcialGemInfos* infos = *it;
            if (infos->gem_area_count==0) {
                m_match_new_gem_type.erase(it);
                it--;
            }
        }
    }
    
    for (unsigned int i=0; i<m_match_clear_pos.size();i++) {
        if (ishelp) {
            m_gems[m_match_clear_pos[i]]->showHelpAnim();
        }else{
            Bomb(m_match_clear_pos[i]);
        }
    }
    //        if (m_match_clear_pos.size()>0) {
    //            CCLOG("clear_count %ld",m_match_clear_pos.size());
    //        }
    //
    //        for (int i=0; i<m_match_new_gem_type.size(); i++) {
    //            cout<<"gem_v_count "<<m_match_new_gem_type[i]->gem_v_count
    //            <<" gem_h_count "<<m_match_new_gem_type[i]->gem_h_count
    //            <<" gem_area_count "<<m_match_new_gem_type[i]->gem_area_count
    //            <<" gem_magic_count "<<m_match_new_gem_type[i]->gem_magic_count
    //            <<" pos "<<m_match_new_gem_type[i]->pos;
    //        }
    
    // return hasBombs;
    
    if (ishelp) {
        return hasBombs;
    }
    
    for (unsigned int i=0; i< m_match_new_gem_type.size(); i++) {
        NewSpcialGemInfos* infos = m_match_new_gem_type[i];
        if (!m_gems[infos->pos]->isEmpty()) {
            continue;
        }
        
        if (!m_blocks[infos->pos]->canInsertGem()) {
            continue;
        }
        for (int j=0; j<infos->gem_area_count; j++) {
            int _p;
            if (m_gems[infos->pos]->isEmpty()) {
                _p = infos->pos;
            }else{
                _p = getEmptyPosRound(infos->pos);
            }
            if (_p!=-1) {
                m_gems[_p]->create(GEM_AREA*10+color);
                showSeaHurt(200, _p);
                if (G::g_game_mode == GAMEMODE_SEA) {
                    G::G_Add_Achievement_Complete(35);
                }
                achieve_count->combine_count++;
            }
        }
        for (int j=0; j<infos->gem_magic_count; j++) {
            int _p;
            if (m_gems[infos->pos]->isEmpty()) {
                _p = infos->pos;
            }else{
                _p = getEmptyPosRound(infos->pos);
            }
            if (_p!=-1) {
                m_gems[_p]->create(GEM_MAGIC*10+GEM_COLOR_NOCOLOR);
                G::G_Add_Achievement_Complete(8);
                achieve_count->create_magic_count++;
                achieve_count->combine_count++;
                showSeaHurt(200, _p);
                if (G::g_game_mode == GAMEMODE_SEA) {
                    G::G_Add_Achievement_Complete(35);
                }
            }
        }
        for (int j=0; j<infos->gem_h_count; j++) {
            int _p;
            if (m_gems[infos->pos]->isEmpty()) {
                _p = infos->pos;
            }else{
                _p = getEmptyPosRound(infos->pos);
            }
            if (_p!=-1) {
                m_gems[_p]->create(GEM_H*10+color);
                showSeaHurt(200, _p);
                if (G::g_game_mode == GAMEMODE_SEA) {
                    G::G_Add_Achievement_Complete(35);
                }
                achieve_count->combine_count++;
            }
        }
        for (int j=0; j<infos->gem_v_count; j++) {
            int _p;
            if (m_gems[infos->pos]->isEmpty()) {
                _p = infos->pos;
            }else{
                _p = getEmptyPosRound(infos->pos);
            }
            if (_p!=-1) {
                m_gems[_p]->create(GEM_V*10+color);
                showSeaHurt(200, _p);
                if (G::g_game_mode == GAMEMODE_SEA) {
                    G::G_Add_Achievement_Complete(35);
                }
                achieve_count->combine_count++;
            }
        }
    }
    
    m_match_ignore_pos.clear();
    m_match_clear_pos.clear();
    m_match_new_gem_type.clear();
    
    return hasBombs;
}

int GameLogic_match::getEmptyPosRound(int pos){
    int* sidesPs = getSidesPosS(pos);
    
    for (int i=0; i<4; i++) {
        int side = sidesPs[i];
        if ( side == -1) {
            continue;
        }
        if (m_blocks[side]->canInsertGem()) {
            if (m_gems[side]->isEmpty()) {
                CC_SAFE_DELETE(sidesPs);
                return side;
            }
        }
    }
    
    CC_SAFE_DELETE(sidesPs);
    return  -1;
}

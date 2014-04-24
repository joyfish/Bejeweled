//
//  HPersistence.cpp
//  Bejeweled
//
//  Created by wilford on 14-1-6.
//
//

#include "HPersistence.h"

HPersistence* HPersistence::instance = NULL;

std::string HPersistence::getStringForKey(const char* pKey)
{
    std::string data = CCUserDefault::sharedUserDefault()->getStringForKey(pKey);
    data = ParseData(data);
    return data;;
}

void HPersistence::setStringForKey(const char* pKey,const char* value)
{
    std::string data = value;
    data = SaveData(reinterpret_cast<const unsigned char*>(data.c_str()), data.length());
    CCUserDefault::sharedUserDefault()->setStringForKey(pKey, data);
}


int HPersistence::getIntForKey(const char* pKey,int d){
    std::string tmp = getStringForKey(pKey);
    if(tmp.empty()){
        return d;
    }else{
        return atoi(tmp.c_str());
    }
}

void HPersistence::setIntForKey(const char* pKey,int value){
    char tmp[20];
    sprintf(tmp,"%d",value);
    setStringForKey(pKey,tmp);
}

bool HPersistence::getBoolForKey(const char* pKey,bool b){
    std::string tmp = getStringForKey(pKey);
    if(tmp.empty()){
        return b;
    }else{
        if(tmp == "true"){
            return true;
        }else
            return false;
    }
}

void HPersistence::setBoolForKey(const char* pKey,bool value){
    if(value){
        setStringForKey(pKey,"true");
    }else
        setStringForKey(pKey,"false");
}

void HPersistence::LoadGameData(){
    
    G::g_maxPower = getIntForKey("game_max_power", INIT_POWER);
    G::G_setCoin(getIntForKey("game_coin", INIT_COIN));
   // G::g_mPower = getIntForKey("game_power", 7+45);
    if (G::g_mPower  > G::g_maxPower) {
        G::g_last_power_recovery_time = G::G_getCurrentTime();
    }
    G::G_setPower(getIntForKey("game_power", INIT_POWER));
    G::G_setBook(getIntForKey("game_book", INIT_BOOK ));
    G::g_mIsBackgroundMusicOn = getBoolForKey("m_bgm", true);
    G::g_mIsEffectVolumeOn = getBoolForKey("m_soundEffect", true);
    G::g_stageInfos->removeAllObjects();
    for(int i=0;i<MAX_STAGE;i++){
        StageInfo* info;
        char key_IsOpen[30];
        sprintf(key_IsOpen,"stage_%d_isopen",i);
        char key_IsPlay[30];
        sprintf(key_IsPlay,"stage_%d_isplay",i);
        char key_Stars[30];
        sprintf(key_Stars,"stage_%d_stars",i);
        bool isopen ;
        
        if(i==0){
            isopen = getBoolForKey(key_IsOpen,true);
        }else{
            isopen = getBoolForKey(key_IsOpen,false);
        }
        
        char key_IsShowed[30];
        sprintf(key_IsShowed, "stage_%d_isShowed",i);
        bool isShowed = getBoolForKey(key_IsShowed,false);
        
        bool isplay = getBoolForKey(key_IsPlay,false);
        int stars = getIntForKey(key_Stars,0);
        
//        isopen = true;
//        stars = 3;

//        if (i<11) {
//            isopen = true;
//            stars = 3;
//        }
        
        info = new StageInfo(isopen,isplay,stars,isShowed);
        G::g_stageInfos->addObject(info);
    }
    
    G::g_toolinfos->removeAllObjects();
    for (int i =0;i<MAX_TOOL_COUNT;i++) {
        ToolInfo* info = new ToolInfo();
        IntToStringFormat(hold_key, "tool_hold_%d",i);
        info->setHoldCount(getIntForKey(hold_key, 1));
        IntToStringFormat(show_key, "tool_new_showed_%d",i);
        info->new_showed = getBoolForKey(show_key, false);
        info->price = tool_prices[i];
        G::g_toolinfos->addObject(info);
    }
    
    for(unsigned int i=0;i<G::g_achieve_infos->count();i++){
        ACHIEVE_INFO* info = (ACHIEVE_INFO*)G::g_achieve_infos->objectAtIndex(i);
        char a_c_key[30];
        sprintf(a_c_key, "achieve_c_%d",i);
        char a_s_key[30];
        sprintf(a_s_key, "achieve_s_%d",i);
        info->complete = getIntForKey(a_c_key, 0);
        info->achieve_completed_showed = getBoolForKey(a_s_key, false);
        char show_key[30];
        sprintf(show_key, "achieve_new_showed_%d",i);
        info->new_showed = getBoolForKey(show_key, false);
        IntToStringFormat(_time_key, "achieve_complete_time_%d", i)
        info->complete_time = getIntForKey(_time_key,0);
        IntToStringFormat(_complete_key, "achieve_is_complete_%d", i)
        info->is_complete = getBoolForKey(_complete_key, false);
        IntToStringFormat(_new_key, "achieve_isNew_%d", i)
        info->isNew = getBoolForKey(_new_key, true);
    }
    
    for(unsigned int i=0;i<G::g_help_infos.size();i++){
        for (unsigned int j=0; j<G::g_help_infos[i].size(); j++) {
            char h_key[30];
            sprintf(h_key,"help_info_%d_%d",i,j);
            G::g_help_infos[i][j]->isShowed = getBoolForKey(h_key,false);
        }
//        HELP_INFO* help_info = (HELP_INFO*)G::g_help_infos->objectAtIndex(i);
//        char h_key[30];
//        sprintf(h_key,"help_info_%d",i);
//        help_info->isShowed = getBoolForKey(h_key,false);
    }
    
    G::g_hole_max_score = getIntForKey("unlimit_top_score", 0);
    G::g_hole_total_depth = getIntForKey("unlimit_total_dist", 0);
    
    G::tree_scroll_has_showed = getBoolForKey("tree_scroll_showed", false);
 
    G::g_last_power_recovery_time = getIntForKey("last_power_recovery_time",G::G_getCurrentTime());
    
    for (int i=0; i<MAX_SHARE; i++) {
        char got_key[30];
        sprintf(got_key, "share_reward_got_%d",i);
        G::g_share_reward_got[i]= getBoolForKey(got_key, false);
    }
    
    G::g_hole_isOpened = getBoolForKey("hole_opened",false);
   //G::g_hole_isOpened = true;
    G::g_hole_isNewShowed = getBoolForKey("hole_showed", false);
    
    G::g_sea_isOpened = getBoolForKey("sea_opened",false);
   // G::g_sea_isOpened = true;
    G::g_sea_isNewShowed = getBoolForKey("sea_showed", false);
    
    for (int i=0; i<MAX_BAO; i++) {
        BAO_INFO* info = new BAO_INFO();
        info->id = i;
        IntToStringFormat(_getKey, "bao_isget_%d", i);
        IntToStringFormat(_showKey, "bao_show_%d", i);
        IntToStringFormat(_newKey, "bao_new_%d", i);
        info->isGot = getBoolForKey(_getKey, false);
        info->isShowed = getBoolForKey(_showKey, false);
        info->isNew = getBoolForKey(_newKey, true);
        G::g_bao_infos->addObject(info);
    }
    
    for (int i=0; i<MAX_CLOUD; i++) {
        IntToStringFormat(_cloudOpenKey, "cloud_open_%d", i);
        G::g_cloud_isOpened[i] = getBoolForKey(_cloudOpenKey, false);
    }
    G::g_has_first_saved = getBoolForKey("has_first_saved", false);
    
    long currentTime = G::G_getCurrentTime();
    struct tm *ptm = localtime((time_t*)& currentTime);
    G::turntable_time = getIntForKey("turntable_time",ptm->tm_mday);
    G::turntable_count = getIntForKey("turntable_count", 1);
    if (ptm->tm_mday!=G::turntable_time) {
        G::turntable_count = 1;
    }
    
    G::turntable_time = ptm->tm_mday;
    
    CCLOG("turntable_time %ld",G::turntable_time);
    
//    if (G::turntable_count==0) {
//        long currentTime = G::G_getCurrentTime();
//        struct tm *ptm1 = localtime((time_t*)& G::turntable_time);
//        struct tm *ptm2 = localtime((time_t*)& currentTime);
//        if (ptm1->tm_mday!=ptm2->tm_mday) {
//            G::turntable_count = 1;
//        }
////        if (G::G_getCurrentTime()>G::turntable_time) {
////            struct tm *ptm1 = localtime((time_t*)& G::turntable_time);
////            struct tm *ptm2 = localtime((time_t*)& currentTime);
////            if (ptm1->tm_mday!=ptm2->tm_mday) {
////                G::turntable_count = 1;
////            }
////        }
//    }
//    
//    long currentTime = G::G_getCurrentTime();
//    CCLOG("currentTime %ld",currentTime);
//
//    
//    struct tm *ptm1 = localtime((time_t*)& G::turntable_time);
//    struct tm *ptm2 = localtime((time_t*)& currentTime);
//    CCLOG("tm_day1 %d  tmp_day2 %d",ptm1->tm_mday,ptm2->tm_mday);
//    if (ptm1->tm_mday!=ptm2->tm_mday) {
//        G::turntable_count = 1;
//    }
//    G::turntable_time = G::G_getCurrentTime();
    
    G::shop_th_has_buyed = getBoolForKey("shop_th_has_buyed", false);
    G::shop_ts_has_buyed = getBoolForKey("shop_ts_has_buyed", false);
    //G::turntable_count = 99;
}

void HPersistence::SaveStage(int stage_id){
    StageInfo* info = (StageInfo*)G::g_stageInfos->objectAtIndex(stage_id);
    if(info==NULL)
        return;
    char key_IsOpen[30];
    sprintf(key_IsOpen,"stage_%d_isopen",stage_id);
    char key_IsPlay[30];
    sprintf(key_IsPlay,"stage_%d_isplay",stage_id);
    char key_Stars[30];
    sprintf(key_Stars,"stage_%d_stars",stage_id);
    setBoolForKey(key_IsOpen,info->isOpened);
    setBoolForKey(key_IsPlay,info->isPlayed);
    setIntForKey(key_Stars,info->stars);
    char key_IsShowed[30];
    sprintf(key_IsShowed, "stage_%d_isShowed",stage_id);
    setBoolForKey(key_IsShowed,info->isShowed);
    
    CCUserDefault::sharedUserDefault()->flush();
}

void HPersistence::SaveAchievement(int id){
    ACHIEVE_INFO* info = (ACHIEVE_INFO*)G::g_achieve_infos->objectAtIndex(id);
    if (info == NULL) {
        return;
    }
    char a_c_key[30];
    sprintf(a_c_key, "achieve_c_%d",id);
    char a_s_key[30];
    sprintf(a_s_key, "achieve_s_%d",id);
    setIntForKey(a_c_key, info->complete);
    setBoolForKey(a_s_key, info->achieve_completed_showed);
    char show_key[30];
    sprintf(show_key, "achieve_new_showed_%d",id);
    setBoolForKey(show_key, info->new_showed);
    IntToStringFormat(_time_key, "achieve_complete_time_%d", id)
    setIntForKey(_time_key, info->complete_time);
    IntToStringFormat(_complete_key, "achieve_is_complete_%d", id)
    setBoolForKey(_complete_key, info->is_complete);
    IntToStringFormat(_new_key, "achieve_isNew_%d", id)
    setBoolForKey(_new_key, info->isNew);
    
    CCUserDefault::sharedUserDefault()->flush();
}

void HPersistence::SaveBao(int id){
    BAO_INFO* info = (BAO_INFO*)G::g_bao_infos->objectAtIndex(id);
    if (info ==  NULL) {
        return;
    }
    IntToStringFormat(_getKey, "bao_isget_%d", id);
    IntToStringFormat(_showKey, "bao_show_%d", id);
    IntToStringFormat(_newKey, "bao_new_%d", id);
    setBoolForKey(_getKey,  info->isGot);
    setBoolForKey(_showKey, info->isShowed );
    setBoolForKey(_newKey, info->isNew);
    
    CCUserDefault::sharedUserDefault()->flush();
}


void HPersistence::SaveToFile(){
    setIntForKey("game_max_power", G::g_maxPower);
    setIntForKey("game_coin", G::G_getCoin());
    setIntForKey("game_power",G::G_getPower());
    //setIntForKey("game_power",G::g_mPower);
    setIntForKey("game_book", G::G_getBook());
    setBoolForKey("m_bgm", G::g_mIsBackgroundMusicOn);
    setBoolForKey("m_soundEffect", G::g_mIsEffectVolumeOn);
    
    //SaveStage(0);
//    for(int i=0;i<MAX_STAGE;i++){
//        StageInfo* info = (StageInfo*)G::g_stageInfos->objectAtIndex(i);
//        if(info==NULL)
//            continue;
//        char key_IsOpen[30];
//        sprintf(key_IsOpen,"stage_%d_isopen",i);
//        char key_IsPlay[30];
//        sprintf(key_IsPlay,"stage_%d_isplay",i);
//        char key_Stars[30];
//        sprintf(key_Stars,"stage_%d_stars",i);
//        setBoolForKey(key_IsOpen,info->isOpened);
//        setBoolForKey(key_IsPlay,info->isPlayed);
//        setIntForKey(key_Stars,info->stars);
//        char key_IsShowed[30];
//        sprintf(key_IsShowed, "stage_%d_isShowed",i);
//        setBoolForKey(key_IsShowed,info->isShowed);
//    }
    for (int i =0;i<MAX_TOOL_COUNT;i++) {
        ToolInfo* info = (ToolInfo*)G::g_toolinfos->objectAtIndex(i);
        IntToStringFormat(hold_key, "tool_hold_%d",i);
        setIntForKey(hold_key, info->getHoldCount());
        IntToStringFormat(show_key, "tool_new_showed_%d",i);
        setBoolForKey(show_key,  info->new_showed);
    }
    
    
    for(unsigned int i=0;i<G::g_help_infos.size();i++){
        for (unsigned int j=0; j<G::g_help_infos[i].size(); j++) {
            char h_key[30];
            sprintf(h_key,"help_info_%d_%d",i,j);
            setBoolForKey(h_key,G::g_help_infos[i][j]->isShowed);
        }
        //        HELP_INFO* help_info = (HELP_INFO*)G::g_help_infos->objectAtIndex(i);
        //        char h_key[30];
        //        sprintf(h_key,"help_info_%d",i);
        //        help_info->isShowed = getBoolForKey(h_key,false);
    }
//    int help_max_count = G::g_help_infos->count();
//    for(int i=0;i<help_max_count;i++){
//        HELP_INFO* help_info = (HELP_INFO*)G::g_help_infos->objectAtIndex(i);
//        char h_key[30];
//        sprintf(h_key,"help_info_%d",i);
//        setBoolForKey(h_key,help_info->isShowed);
//    }
    for(unsigned int i=0;i<G::g_achieve_infos->count();i++){
        ACHIEVE_INFO* info = (ACHIEVE_INFO*)G::g_achieve_infos->objectAtIndex(i);
        char a_c_key[30];
        sprintf(a_c_key, "achieve_c_%d",i);
        char a_s_key[30];
        sprintf(a_s_key, "achieve_s_%d",i);

        setIntForKey(a_c_key, info->complete);
        

        setBoolForKey(a_s_key, info->achieve_completed_showed);
        
        char show_key[30];
        sprintf(show_key, "achieve_new_showed_%d",i);

        setBoolForKey(show_key, info->new_showed);
        
        IntToStringFormat(_time_key, "achieve_complete_time_%d", i)

        setIntForKey(_time_key, info->complete_time);
        IntToStringFormat(_complete_key, "achieve_is_complete_%d", i)
  
        setBoolForKey(_complete_key, info->is_complete);
        
        IntToStringFormat(_new_key, "achieve_isNew_%d", i)
   
        setBoolForKey(_new_key, info->isNew);
    }
    

    setIntForKey("unlimit_top_score",  G::g_hole_max_score );
    setIntForKey("unlimit_total_dist", G::g_hole_total_depth);
    
    setBoolForKey("tree_scroll_showed", G::tree_scroll_has_showed);
    
    setIntForKey("last_power_recovery_time", G::g_last_power_recovery_time);
    
//    for (int i=0; i<MAX_SHARE; i++) {
//        char got_key[30];
//        sprintf(got_key, "share_reward_got_%d",i);
//        setBoolForKey(got_key, G::g_share_reward_got[i]);
//    }
    
    setBoolForKey("hole_opened", G::g_hole_isOpened);
    setBoolForKey("hole_showed", G::g_hole_isNewShowed);
    
    setBoolForKey("sea_opened", G::g_sea_isOpened);
    setBoolForKey("sea_showed", G::g_sea_isNewShowed);
    
//    for (unsigned int i=0; i<MAX_BAO; i++) {
//        BAO_INFO* info = (BAO_INFO*)G::g_bao_infos->objectAtIndex(i);
//        info->id = i;
//        IntToStringFormat(_getKey, "bao_isget_%d", i);
//        IntToStringFormat(_showKey, "bao_show_%d", i);
//        IntToStringFormat(_newKey, "bao_new_%d", i);
//        setBoolForKey(_getKey,  info->isGot);
//        setBoolForKey(_showKey, info->isShowed );
//        setBoolForKey(_newKey, info->isNew);
//    }
    
    
    for (int i=0; i<MAX_CLOUD; i++) {
        IntToStringFormat(_cloudOpenKey, "cloud_open_%d", i);
        setBoolForKey(_cloudOpenKey, G::g_cloud_isOpened[i]);
    }

    G::g_has_first_saved = true;
    setBoolForKey("has_first_saved", true);
    
    setIntForKey("turntable_time", G::turntable_time);
    setIntForKey("turntable_count", G::turntable_count);
    
    setBoolForKey("shop_th_has_buyed", G::shop_th_has_buyed);
    setBoolForKey("shop_ts_has_buyed",  G::shop_ts_has_buyed);
    
    CCUserDefault::sharedUserDefault()->flush();
}
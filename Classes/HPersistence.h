//
//  HPersistence.h
//  Bejeweled
//
//  Created by wilford on 14-1-6.
//
//

#ifndef Bejeweled_HPersistence_h
#define Bejeweled_HPersistence_h
#include "DataBase64.h"
#include "HGloba.h"
#include "cocos2d.h"

USING_NS_CC;

class BoolSave:public CCObject{
public:
    char* key;
    bool value;
    BoolSave(const char* key,bool value){
        autorelease();
        this->key = new char[30];
        sprintf(this->key, "%s",key);
        this->value = value;
    }
    ~BoolSave(){
        CC_SAFE_DELETE(key);
    }
};

class IntSave:public CCObject{
public:
    char* key;
    int value;
    IntSave(const char* key,int value){
        autorelease();
        this->key = new char[30];
        sprintf(this->key, "%s",key);
        this->value = value;
    }
    ~IntSave(){
        CC_SAFE_DELETE(key);
    }
};


class StrSave:public CCObject{
public:
    char* key;
    char* value;
    StrSave(const char* key,const char* value){
        autorelease();
        this->key = new char[30];
        sprintf(this->key, "%s",key);
        this->value = new char[30];
        sprintf(this->value, "%s",value);
    }
    
    ~StrSave(){
        CC_SAFE_DELETE(key);
        CC_SAFE_DELETE(value);
    }
};




class HPersistence{
public:
    static HPersistence* S(){
        if (!instance) {
            instance = new HPersistence();
        }
        return instance;
    }
    void release(){CC_SAFE_DELETE(instance);}
    
    HPersistence(){
        m_int_save_list = new CCArray();
        m_bool_save_list = new CCArray();
        m_str_save_list = new CCArray();
        is_in_save = false;
    }
    
    ~HPersistence(){
        m_int_save_list->release();
        m_bool_save_list->release();
        m_str_save_list->release();
    }
    
    
    std::string getStringForKey(const char* pKey);
    void setStringForKey(const char* pKey,const char* value);
    int getIntForKey(const char* pKey,int d);
    void setIntForKey(const char* pKey,int value);
    bool getBoolForKey(const char* pKey,bool b);
    void setBoolForKey(const char* pKey,bool value);
    
    void LoadGameData();
    void SaveToFile();
    
    void SaveStage(int stage_id);
    void SaveAchievement(int id);
    void SaveBao(int id);
    
    void AsynchSaveInt(const char* key,int value){
        CCLOG("add %s %d",key,value);
        m_int_save_list->addObject(new IntSave(key,value));
    }
    void AsynchSaveBool(const char* key,bool value){
        m_bool_save_list->addObject(new BoolSave(key,value));
    }
    void AsynchSavaStr(const char* key,const char* value){
        m_str_save_list->addObject(new StrSave(key,value));
    }
    
    void AsynchSaveToFile(){
        AsynchSaveInt("game_max_power", G::g_maxPower);
        AsynchSaveInt("game_coin", G::G_getCoin());
        AsynchSaveInt("game_power",G::G_getPower());
        AsynchSaveInt("game_book", G::G_getBook());
        AsynchSaveBool("m_bgm", G::g_mIsBackgroundMusicOn);
        AsynchSaveBool("m_soundEffect", G::g_mIsEffectVolumeOn);
 
        for (int i =0;i<MAX_TOOL_COUNT;i++) {
            ToolInfo* info = (ToolInfo*)G::g_toolinfos->objectAtIndex(i);
            IntToStringFormat(hold_key, "tool_hold_%d",i);
            AsynchSaveInt(hold_key, info->getHoldCount());
            IntToStringFormat(show_key, "tool_new_showed_%d",i);
            AsynchSaveBool(show_key,  info->new_showed);
        }
        
        for(unsigned int i=0;i<G::g_help_infos.size();i++){
            for (unsigned int j=0; j<G::g_help_infos[i].size(); j++) {
                char h_key[30];
                sprintf(h_key,"help_info_%d_%d",i,j);
                AsynchSaveBool(h_key,G::g_help_infos[i][j]->isShowed);
            }
        }
        

        for(unsigned int i=0;i<G::g_achieve_infos->count();i++){
            ACHIEVE_INFO* info = (ACHIEVE_INFO*)G::g_achieve_infos->objectAtIndex(i);
            char a_c_key[30];
            sprintf(a_c_key, "achieve_c_%d",i);
            char a_s_key[30];
            sprintf(a_s_key, "achieve_s_%d",i);
            AsynchSaveInt(a_c_key, info->complete);
            AsynchSaveBool(a_s_key, info->achieve_completed_showed);
            char show_key[30];
            sprintf(show_key, "achieve_new_showed_%d",i);
            AsynchSaveBool(show_key, info->new_showed);
            IntToStringFormat(_time_key, "achieve_complete_time_%d", i)
            AsynchSaveInt(_time_key, info->complete_time);
            IntToStringFormat(_complete_key, "achieve_is_complete_%d", i)
            AsynchSaveBool(_complete_key, info->is_complete);
            IntToStringFormat(_new_key, "achieve_isNew_%d", i)
            AsynchSaveBool(_new_key, info->isNew);
        }
        
        AsynchSaveInt("unlimit_top_score",  G::g_hole_max_score );
        AsynchSaveInt("unlimit_total_dist", G::g_hole_total_depth);
        
        AsynchSaveBool("tree_scroll_showed", G::tree_scroll_has_showed);
        
        AsynchSaveInt("last_power_recovery_time", G::g_last_power_recovery_time);
        
        
        AsynchSaveBool("hole_opened", G::g_hole_isOpened);
        AsynchSaveBool("hole_showed", G::g_hole_isNewShowed);
        
        AsynchSaveBool("sea_opened", G::g_sea_isOpened);
        AsynchSaveBool("sea_showed", G::g_sea_isNewShowed);
        
        
        
        for (int i=0; i<MAX_CLOUD; i++) {
            IntToStringFormat(_cloudOpenKey, "cloud_open_%d", i);
            AsynchSaveBool(_cloudOpenKey, G::g_cloud_isOpened[i]);
        }
        
        G::g_has_first_saved = true;
        AsynchSaveBool("has_first_saved", true);
        
        AsynchSaveInt("turntable_time", G::turntable_time);
        AsynchSaveInt("turntable_count", G::turntable_count);
    }
    
    void update(float dt){
        if (m_int_save_list->count()==0&&
            m_bool_save_list->count() ==0&&
            m_str_save_list->count() == 0) {
            return;
        }
        is_in_save = true;
        int startTime = getMinTime();
        while (m_int_save_list->count()>0) {
            int offsetTime = getMinTime()-startTime;
            if (offsetTime>50) {
                return;
            }
            IntSave* int_save = (IntSave*)m_int_save_list->objectAtIndex(0);
            //CCLOG("%s %d",int_save->key,int_save->value);
            setIntForKey(int_save->key, int_save->value);
            m_int_save_list->removeObjectAtIndex(0);
        }

        while (m_bool_save_list->count()>0) {
            int offsetTime = getMinTime()-startTime;
            if (offsetTime>50) {
                return;
            }
            BoolSave* bool_save = (BoolSave*)m_bool_save_list->objectAtIndex(0);
            //CCLOG("%s %d",bool_save->key,bool_save->value);
            setBoolForKey(bool_save->key, bool_save->value);
            m_bool_save_list->removeObjectAtIndex(0);
        }
        while (m_str_save_list->count()>0) {
            int offsetTime = getMinTime()-startTime;
            if (offsetTime>50) {
                return;
            }
            StrSave* str_save = (StrSave*)m_str_save_list->objectAtIndex(0);
            setStringForKey(str_save->key, str_save->value);
            m_str_save_list->removeObjectAtIndex(0);
        }
        
        G::g_has_first_saved = true;
        setBoolForKey("has_first_saved", true);
        
        CCUserDefault::sharedUserDefault()->flush();
        is_in_save = false;
    }
    
    long getMinTime(){
        struct timeval tv;
        gettimeofday(&tv,NULL);
        //long start = ((long)tv.tv_sec)*1000+(long)t_start.tv_usec/1000;
        return ((long)tv.tv_sec)*1000+(long)tv.tv_usec/1000;
    }
    
    void printTimeOffset(const char* begin){
        CCLOG("[%s] offsetTime %ld",begin,G::G_getCurrentTime()-m_time);
        m_time = G::G_getCurrentTime();
    }
    
    bool is_in_save;
private:
    CCArray* m_int_save_list;
    CCArray* m_bool_save_list;
    CCArray* m_str_save_list;
    static HPersistence* instance;
    long m_time;
};

#endif

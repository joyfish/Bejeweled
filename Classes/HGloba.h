//
//  HGloba.h
//  Bejeweled
//
//  Created by wilford on 14-1-3.
//
//

#ifndef Bejeweled_HGloba_h
#define Bejeweled_HGloba_h

//这里定义全局静态变量(变量g_开头 方法G_开头)

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "HDefine.h"
#include "HParams.h"
#include "HTools.h"
#include "HSelectors.h"
#include "DataInputScream.h"
#include <iostream>
using namespace CocosDenshion;
using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;

#define ScaleOutNode(__N__,__DELAY__)\
__N__->setScale(1);\
__N__->runAction(CCSequence::create(CCDelayTime::create(__DELAY__),CCScaleTo::create(0.1f, 1.2f),CCScaleTo::create(0.1f, 0),NULL));\

#define PopApple(__N__,__DELAY__)\
__N__->setScale(0);\
__N__->runAction(CCSequence::create(CCDelayTime::create(__DELAY__),CCScaleTo::create(0.2f, 1.5f),CCScaleTo::create(0.15f, 0.7f),CCScaleTo::create(0.1f, 1.2f),CCScaleTo::create(0.1f, 0.9f),CCScaleTo::create(0.1f, 1.0f),NULL));\

#define PopNode(__N__,__DELAY__)\
__N__->setScale(0);\
__N__->runAction(CCSequence::create(CCDelayTime::create(__DELAY__),CCScaleTo::create(0.2f, 1.2f),CCScaleTo::create(0.1f, 0.9f),CCScaleTo::create(0.1f, 1.0f),NULL));\

#define PopNodeS(__N__,__DELAY__)\
__N__->setScale(0);\
__N__->runAction(CCSequence::create(CCDelayTime::create(__DELAY__),CCScaleTo::create(0.2f, 1.1f),CCScaleTo::create(0.1f, 0.95f),CCScaleTo::create(0.1f, 1.0f),NULL));\

#define PopNodeQ(__N__,__DELAY__)\
__N__->setScale(0);\
__N__->runAction(CCSequence::create(CCDelayTime::create(__DELAY__),CCScaleTo::create(0.14f, 1.4f),CCScaleTo::create(0.07f, 0.8f),CCScaleTo::create(0.07f, 1.0f),NULL));\

#define IntToStringFormat(__TARGET__,__FORMAT__,__INT__)\
char __TARGET__[30];\
sprintf(__TARGET__,__FORMAT__,__INT__);\

#define IntToString(__TARGET__,__INT__) IntToStringFormat(__TARGET__,"%d",__INT__)

#define SetDepthNum(__UILABELATLAS_ARR__,__COUNT__,__Value__)\
{\
    int tmpNum = __Value__;\
    for (int i=0; i<__COUNT__; i++) {\
        IntToString(n, tmpNum%10)\
        tmpNum/=10;\
        __UILABELATLAS_ARR__[i]->setStringValue(n);\
    }\
}

#define ScrollDepthNum(__UILABELATLAS_ARR_,__COUNT__,__PRE__,__CURRENT__)\
{\
    int pre = __PRE__;\
    int current = __CURRENT__;\
    for (int i=0; i<__COUNT__; i++) {\
        if (current%10==pre%10) {\
            current/=10;\
            pre/=10;\
            continue;\
        }\
        IntToString(n, current%10);\
        current/=10;\
        pre/=10;\
        CCPoint pos = __UILABELATLAS_ARR_[i]->getPosition();\
        UIWidget* parent = __UILABELATLAS_ARR_[i]->getParent();\
        __UILABELATLAS_ARR_[i]->runAction(CCSequence::create(CCDelayTime::create(0.5f), CCMoveBy::create(0.3f, ccp(0, 50)),CCCallFuncND::create(this, callfuncND_selector(G::G_callbackRemoveUIWidget2),mNums[i]),NULL));\
        __UILABELATLAS_ARR_[i] = UILabelAtlas::create();\
        __UILABELATLAS_ARR_[i]->setProperty(n, "numbers/num3.png", 20, 28, "0");\
        __UILABELATLAS_ARR_[i]->setPosition(ccp(pos.x,pos.y-50));\
        parent->addChild(__UILABELATLAS_ARR_[i]);\
        __UILABELATLAS_ARR_[i]->runAction(CCSequence::create(CCDelayTime::create(0.5f), CCMoveBy::create(0.3f, ccp(0, 50)),NULL));\
    }\
}


#define AddVoidEvent(__FUNCNAME__, __TARGET__,__SELECTOR__)\
void __FUNCNAME__(CCObject* target,SEL_VOIDCALLBACK selector){\
__TARGET__ = target;\
__SELECTOR__ = selector;\
}

#define DoVoidEvent(__TARGET__,__SELECTOR)\
if (__TARGET__&&__SELECTOR) {\
    (__TARGET__->*__SELECTOR)();\
}

class StageInfo : public cocos2d::CCObject{
public:
	bool isOpened;
	bool isPlayed;
    bool isShowed;
	int stars;
    
    StageInfo(){
        this->autorelease();
    }
    
	StageInfo(bool isOpened,bool isPlayed,int stars,bool isShowed){
		this->autorelease();
        this->isShowed = isShowed;
		this->isOpened = isOpened;
		this->isPlayed = isPlayed;
		this->stars = stars;
	}
};


class ToolInfo : public cocos2d::CCObject{
public:
	int price;
    bool new_showed;
    
    ToolInfo(){
        autorelease();
    }
    
	ToolInfo(int price,int hold_count,bool new_showed){
		autorelease();
        this->price = price;
        this->hold_count = hold_count;
        this->new_showed = new_showed;
	}
    
    void setHoldCount(int count){
        hold_count = count+60;
    }
    
    int getHoldCount(){
        return hold_count-60;
    }
    
private:
    int hold_count;
};

class RewardInfo : public CCObject{
public:
    int id;
    int count;
    RewardInfo(int id,int count){
        this->autorelease();
        this->id = id;
        this->count = count;
    }
};

class HELP_INFO : public cocos2d::CCObject{
public:
	int target_block_id;
	int dir;
    int mask_id;
    int mask_pos_id;
	int tips_id;
	int tips_in_type;
	bool isShowed;
	HELP_INFO(){
		autorelease();
		isShowed = false;
	}
};

class ACHIEVE_INFO:public CCObject{
public:
    int id;
    int complete;
    int require;
    bool achieve_completed_showed;
    int type;//0 关卡，1 洞穴 2 其他
    bool new_showed;
    bool isOpened;
    long complete_time;
    bool is_complete;
    bool isNew;
    ACHIEVE_INFO(){
        autorelease();
    }
    
    void addComplete(int count){
        complete+=count;
        complete = MIN(complete,require);
        checkComplete();
    }
    
    void setComplete(int complete){
        this->complete = complete;
        this->complete  = MIN(this->complete , require);
        this->complete  = MAX(this->complete , 0);
        checkComplete();
    }
    
    void checkComplete(){
        if (isCompleted()) {
            if (!is_complete) {
                complete_time = time(NULL);
                is_complete = true;
            }
        }else{
            if (complete>0) {
                complete_time = 1;
            }else{
                complete_time = 0;
            }
        }
    }
private:
    bool isCompleted(){
        return complete==require;
    }

};

class ACHIEVE_COUNT{
public:
    int bomb_count_single_move;//单步消除宝石数
    int score_last_light;//最后狂欢获得分数
    int combo_count;//连击数
    int exchange_count;//配对
    int combine_count;//制造特效宝石
    int create_magic_count;//制造魔方
    int special_bomb_count_single_move;//引爆特效宝石
    int use_reposion_bomb_count;//使用换位道具
    int use_star_count;//星星道具
    
    int hole_gold_count;//洞穴模式消除金矿
    int sea_wall_count;//海底模式消除触角
    int sea_vircus_count;//海底模式消除病毒
    
    ACHIEVE_COUNT()
    :bomb_count_single_move(0)
    ,score_last_light(0)
    ,combo_count(0)
    ,exchange_count(0)
    ,combine_count(0)
    ,create_magic_count(0)
    ,special_bomb_count_single_move(0)
    ,use_reposion_bomb_count(0)
    ,hole_gold_count(0)
    ,use_star_count(0)
    ,sea_wall_count(0)
    ,sea_vircus_count(0)
    {
    }
};

class BAO_INFO:public CCObject{
public:
    int id;
    bool isGot;//是否获得过
    bool isShowed;//是否展示过
    bool isNew;//是否是新宝藏(在宝藏界面里查看过)
    BAO_INFO(){
        autorelease();
    }
};


enum BUY_TYPE{
    BUY_TYPE_NONE,
    BUY_TYPE_NORMAL,
    BUY_TYPE_QUICK
};

enum SORT_TYPE{
    SORT_ASC,//升序
    SORT_DESC//降序
};

class G{
public:
    
    static void G_sortUIWidgetByName(CCArray* widgets,SORT_TYPE type){
        int j, k;
        int flag;
        
        int n = widgets->count();
        
        flag = n;
        while (flag > 0)
        {
            k = flag;
            flag = 0;
            for (j = 1; j < k; j++){
                UIWidget* u1 = (UIWidget*)widgets->objectAtIndex(j-1);
                UIWidget* u2 = (UIWidget*)widgets->objectAtIndex(j);
                if (type == SORT_ASC) {
                    if (strcmp(u1->getName(), u2->getName())>0) {
                        widgets->exchangeObject(u1,u2);
                        flag =j;
                    }
                }else{
                    if (strcmp(u1->getName(), u2->getName())<0) {
                        widgets->exchangeObject(u1,u2);
                        flag =j;
                    }
                }
            }
        }
    }
    
    static CCPoint getWorldPosition(UIWidget* widget){
        CCPoint pos = widget->getPosition();
        do{
            UIWidget* parent = widget->getParent();
            if(parent == NULL)
                break;
            widget = parent;
            pos.x += parent->getPosition().x;
            pos.y += parent->getPosition().y;
        }while(true);
        return pos;
    }
    
    static void G_removeAllUIWidgets(CCArray* widgets){
        CCObject* obj;
        CCARRAY_FOREACH(widgets, obj){
            UIWidget* u = (UIWidget*)obj;
            if (u) {
                u->removeFromParentAndCleanup(true);
            }
        }
        widgets->removeAllObjects();
    }
    
    static CCSize G_orderUIWiddget(CCArray* widgets,CCPoint start_pos,int line_num,float padding_w,float padding_h){
        if (line_num == 0||widgets==NULL) {
            return CCSizeMake(0, 0);
        }
        CCObject* obj;
        int id = 0;
        CCARRAY_FOREACH(widgets, obj){
            UIWidget* u = (UIWidget*)obj;
            CCPoint pos;
            pos.x=start_pos.x+id%line_num*padding_w;
            pos.y=start_pos.y+id/line_num*padding_h;
            u->setPosition(pos);
            id++;
        }
        int count = widgets->count();
        float width = count>=line_num?line_num*padding_w:count*padding_w;
        float height = (count/line_num+1)*padding_h;
        return CCSizeMake( width, height);
    }
    
    void G_callbackRemoveUIWidget(CCObject* obj){
        UIWidget* u = (UIWidget*)obj;
        u->removeFromParentAndCleanup(true);
    }
    
    void G_callbackRemoveUIWidget2(CCNode* sender,void* data){
        UIWidget* u = (UIWidget*)data;
        u->removeFromParentAndCleanup(true);
    }
    
    static long G_getCurrentTime()
    {
        struct timeval tv;
        gettimeofday(&tv,NULL);
        return tv.tv_sec;
    }
    
    
    //精力值
    static long g_last_power_recovery_time;
    static int g_mPower;
    static int g_maxPower;
    
    static int G_getPower(){
        return g_mPower -45;
    }
    
    static void G_setPower(int power){
        if (power > g_maxPower) {
            power = g_maxPower;
            g_last_power_recovery_time = G_getCurrentTime();
        }
        g_mPower = power + 45;
    }


    
    static int G_checkPowerRecovery(CCObject* target,SEL_VOIDCALLBACK savefunc){
        int pass_time = G_getCurrentTime()-g_last_power_recovery_time;
        int power_recovery_count = pass_time/POWER_ROCOVERY_TIME;
            
        if (power_recovery_count>0) {
            g_last_power_recovery_time += power_recovery_count*POWER_ROCOVERY_TIME;
            G_setPower(G_getPower()+power_recovery_count);
            DoVoidEvent(target, savefunc);
        }
        return pass_time-power_recovery_count*POWER_ROCOVERY_TIME;
    }
    
    static bool G_costPower(int cost){
        if (G_getPower()>=cost) {
            G_setPower(G_getPower()-cost);
            return true;
        }else{
            return false;
        }
    }
    
    //金币
    static int g_mCoin;
    
    static int G_getCoin(){
        return g_mCoin - 200;
    }
    
    static void G_setCoin(int coin){
        g_mCoin = coin + 200;
    }
    
    static bool G_costCoin(int cost){
        if (G_getCoin()>=cost) {
            G_setCoin(G_getCoin()-cost);
            return true;
        }else{
            return false;
        }
    }
    
    //勇气卷
    static int g_mBook;
    
    static int G_getBook(){
        return g_mBook -100;
    }
    
    static void G_setBook(int book){
        g_mBook = book + 100;
    }
    
    static bool G_costBook(int cost){
        if (G_getBook()>=cost) {
            G_setBook(G_getBook()-cost);
            return true;
        }else{
            return false;
        }
    }
    
    //当前场景
    static void* g_currentScene;
    
    
    //声音
    
    //背景音乐是否开启
    static bool g_mIsBackgroundMusicOn;
    //音效是否开启
    static bool g_mIsEffectVolumeOn;
    
    static vector<const char*> g_m_played_effects;
    
    static void G_playBackGroundMusic(const char* path){
        if(g_mIsBackgroundMusicOn)
            SimpleAudioEngine::sharedEngine()->playBackgroundMusic(path,true);
    }
    
    static void G_playEffect(const char* path,bool loop = false){
        if(g_mIsEffectVolumeOn){
            for (int i=0; i<g_m_played_effects.size(); i++) {
                if (strcmp(path, g_m_played_effects[i])==0) {
                    return;
                }
            }
            SimpleAudioEngine::sharedEngine()->playEffect(path,loop);
            g_m_played_effects.push_back(path);
        }
    }
    
    static void G_setBackGroundMusicState(bool isOn,const char* backgroundmusic = NULL){
        if(g_mIsBackgroundMusicOn!=isOn){
            g_mIsBackgroundMusicOn = isOn;
            if(g_mIsBackgroundMusicOn){
                if(backgroundmusic!=NULL)
                    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(backgroundmusic,true);
            }else{
                SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
            }
        }
    }
    
    static void G_setEffectState(bool isOn){
        if(g_mIsEffectVolumeOn!= isOn){
            g_mIsEffectVolumeOn = isOn;
        }
    }
    
    static int G_getCurrentStage(){
        int stage_id = 0;
        CCObject* obj;
        CCARRAY_FOREACH(g_stageInfos, obj){
            StageInfo* info = (StageInfo*)obj;
            if (info->isOpened) {
                stage_id++;
            }
        }
        return stage_id;
    }
    
    static int G_getTotalStar(){
        int star = 0 ;
        for (int i = 0; i<MAX_STAGE; i++) {
            StageInfo* info = (StageInfo*)g_stageInfos->objectAtIndex(i);
            star += info->stars;
        }
        return star;
    }
    
    static int G_getMaxStar(){
        return MAX_STAGE*3;
    }
    
    static CCArray* g_stageInfos;//StageInfo 关卡信息
    
    static bool tree_scroll_has_showed;//树下滑动画播放过了
    
    static void G_getReward(int id,int count){
        CCLOG("get_reward %d  %d",id,count);
        switch (id) {
            case 0: //金币
                G_setCoin(G_getCoin()+count);
                break;
            case 1:
                G_setPower(G_getPower()+count);
                break;
            case 2://闹钟
            case 3://增步器
            case 4://锤子
            case 5://换位
            case 6://点金棒
            case 7://星星
            {
                ToolInfo* info = (ToolInfo*)g_toolinfos->objectAtIndex(id-2);
                info->setHoldCount(info->getHoldCount()+count);
            }
                break;
            case 8://勇气卷
                G_setBook(G_getBook()+count);
                break;
            case 9://精力扩展卷
                g_maxPower += count;
                if (g_maxPower>MAX_POWER) {
                    g_maxPower=MAX_POWER;
                }
                G_setPower(g_maxPower);
                break;
            default:
                break;
        }
    }
    
    static void G_getRewards(CCArray* rewards){
        if (rewards) {
            for (unsigned int i=0; i<rewards->count(); i++) {
                RewardInfo* info = (RewardInfo*)rewards->objectAtIndex(i);
                if (info) {
                    G_getReward(info->id, info->count);
                }

            }
//            CCARRAY_FOREACH(rewards, obj){
//                RewardInfo* info = (RewardInfo*)obj;
//                CCLOG("----bbbb----");
//                if (info) {
//                    CCLOG("----cccc----");
//                    G_getReward(info->id, info->count);
//                }
//            }
        }
    }
    
    static CCArray* g_toolinfos;//ToolInfo 道具信息
    
    static int g_hole_max_score;//洞穴最高分
    
    static int g_hole_total_depth;//洞穴总深度
    
    static BUY_TYPE g_last_buytype;//上一次购买类型
    static int g_last_buyid;
    
    //游戏相关
    static int g_game_buff[3];
    
    static int g_game_win_conditions[WIN_CONDITION_MAX];
    static int g_game_lose_conditions[LOSE_CONDITION_MAX];
    static int g_game_blocks[BLOCK_NUM_WH];
    static int g_game_gems[BLOCK_NUM_WH];
    static int g_game_maxColorCount;

    static int g_game_max_gold_count;
    static int g_game_max_gem_time_count;
    static int g_game_max_gem_egg_count;
    static int g_game_max_gem_timebomb_count;
    static int g_game_star2_score;//2星分数
    static int g_game_star_score;//3星分数
    static GAMEMODE g_game_mode;
    static int g_game_stage ;
    
    static void G_loadGameMap(GAMEMODE mode,int stage){
        g_game_mode = mode;
        g_game_stage = stage;
        DataInputStream* dis = NULL;
        switch (mode) {
        case GAMEMODE_STAGE:
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//            IntToStringFormat(_mapPath, "/mnt/sdcard/maps/m%d", stage);
//#else
//            IntToStringFormat(_mapPath, "maps/m%d", stage);
//#endif
            IntToStringFormat(_mapPath, "maps/m%d", stage);
            dis = DataInputStream::loadFileWithPath(_mapPath);
        break;
        case GAMEMODE_HOLE:
            {
                g_game_maxColorCount = GEM_COLOR_NOCOLOR-1;
                g_game_max_gold_count = 0;
                g_game_max_gem_time_count = 0;
                g_game_max_gem_egg_count = 0;
                g_game_max_gem_timebomb_count = 0;
                
                g_game_star2_score = 0;
                g_game_star_score = 100;
                
                
                for (int i=0;i<WIN_CONDITION_MAX;i++)
                {
                    g_game_win_conditions[i] = 0;
                }
                
                
                for (int i=0;i<LOSE_CONDITION_MAX;i++)
                {
                    g_game_lose_conditions[i] = 0;
                }
                
                g_game_lose_conditions[LOSE_CONDITION_TIME] = 120;
                
                
                for (int i=0; i<BLOCK_NUM_WH; i++) {
                    g_game_blocks[i] = 0x10;
                    if (i/BLOCK_NUM_W == 0) {
                        g_game_blocks[i] = 0x80;
                    }
                }
                std::vector<int> blockPlist;
                for(int i=0;i<BLOCK_NUM_WH;i++){
                    g_game_gems[i] = 0;
                    if (i/BLOCK_NUM_W>=BLOCK_NUM_H-4) {
                        g_game_gems[i] = GEM_HOLE_WALL*10+GEM_COLOR_NOCOLOR;
                        blockPlist.push_back(i);
                    }
                }
                
                for (int i=0;i<6;i++) {
                    int rand = t_getRandom(blockPlist.size());
                    g_game_gems[blockPlist[rand]] = GEM_HOLE_NORMAL*10+GEM_COLOR_NOCOLOR;
                    vector<int>::iterator it = blockPlist.begin()+rand;
                    blockPlist.erase(it);
                }
            }
        break;
        case GAMEMODE_SEA:
            {
                g_game_maxColorCount = GEM_COLOR_NOCOLOR-1;
                g_game_max_gold_count = 0;
                g_game_max_gem_time_count = 0;
                g_game_max_gem_egg_count = 0;
                g_game_max_gem_timebomb_count = 0;
                
                g_game_star2_score = 0;
                g_game_star_score = 100;
                
                
                for (int i=0;i<WIN_CONDITION_MAX;i++)
                {
                    g_game_win_conditions[i] = 0;
                }
                
                
                for (int i=0;i<LOSE_CONDITION_MAX;i++)
                {
                    g_game_lose_conditions[i] = 0;
                }
                
                g_game_lose_conditions[LOSE_CONDITION_TIME] = 100;
                int b[BLOCK_NUM_WH-BLOCK_NUM_W];
                int l = BLOCK_NUM_WH-BLOCK_NUM_W;
                for (int i=0; i<BLOCK_NUM_WH; i++) {
                    g_game_blocks[i] = 0x10;
                    if (i/BLOCK_NUM_W == 0) {
                        g_game_blocks[i] = 0x80;
                    }else{
                        b[i-BLOCK_NUM_W] = i;
                    }
                }
               
                for(int i=0;i<BLOCK_NUM_WH;i++){
                    g_game_gems[i] = 0;
                }
                
                for (int i=0; i<6; i++) {
                    int rand = t_getRandom(l);
                    g_game_blocks[b[rand]] = 0x730010;
                    b[rand] = b[l-1];
                    l--;
                }
            }
        break;
        default:
        break;
        }
        
        for (int i=0; i<3; i++) {
            g_game_buff[i] = 0;
        }
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//        IntToStringFormat(_mapPath, "/mnt/sdcard/maps/m%d", stage);
//#else
//        IntToStringFormat(_mapPath, "maps/m%d", stage);
//#endif
        
        //	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
        //#else
        //    CCDirector::sharedDirector()->end();
        //#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        //    exit(0);
        //#endif
        //#endif
        //IntToStringFormat(_mapPath, "maps/m%d", stage);

        if (dis) {
            g_game_maxColorCount = dis->readChar();
            //m_maxColor = 6;
            g_game_max_gold_count = dis->readChar();
            //m_max_gold_count = 2;
            g_game_max_gem_time_count = dis->readChar();
            //m_max_gem_time_count = 1;
            g_game_max_gem_egg_count = dis->readChar();
            //m_max_gem_egg_count = 1;
            g_game_max_gem_timebomb_count = dis->readChar();
            //m_max_gem_timebomb_count = 1;
            
            g_game_star2_score = dis->readInt();
            g_game_star_score = dis->readInt();

            
            for (int i=0;i<WIN_CONDITION_MAX;i++)
            {
                g_game_win_conditions[i] = dis->readInt();
            }
            
            
            for (int i=0;i<LOSE_CONDITION_MAX;i++)
            {
                g_game_lose_conditions[i] = dis->readInt();
            }
            
//            g_game_lose_conditions[LOSE_CONDITION_TIME] = 30;
//            g_game_lose_conditions[LOSE_CONDITION_STEP] = 0;
            
            for (int i=0; i<BLOCK_NUM_WH; i++) {
                g_game_blocks[i] = dis->readInt();
            }
            for(int i=0;i<BLOCK_NUM_WH;i++){
                g_game_gems[i] = dis->readShort();
            }
//            g_game_gems[BLOCK_NUM_W] = 47;
//            g_game_gems[BLOCK_NUM_W+1]=47;
            
            CC_SAFE_DELETE(dis);
        }
//        g_game_mode = mode;
//        g_game_stage = stage;
//        DataInputStream* dis = NULL;
//        switch (mode) {
//            case GAMEMODE_STAGE:
//                IntToStringFormat(_mapPath, "map/m%d", stage);
//                dis = DataInputStream::loadFileWithPath(_mapPath);
//                break;
//            case GAMEMODE_HOLE:
//                dis = DataInputStream::loadFileWithPath("map/m_hole");
//                break;
//            case GAMEMODE_SEA:
//                break;
//                
//            default:
//                break;
//        }
//        if (dis) {
//            g_game_maxColorCount = dis->readChar();
//            dis->readInt();
//            g_game_star_score = dis->readInt();
//            for (int i=0; i<MAX_WIN_CONDITIONS; i++) {
//                g_game_win_conditions[i] = dis->readShort();
//            }
//            for (int i=0; i<MAX_LOSE_CONDITIONS; i++) {
//                g_game_lose_conditions[i] = dis->readShort();
//            }
//            for (int i=0; i<BLOCK_NUM_WH; i++) {
//                g_game_blocks[i] = dis->readChar();
////                if (i%BLOCK_NUM_W==0) {
////                    std::cout<<"\n";
////                }
////                std::cout<<g_game_blocks[i]<<" ";
//                if (mode == GAMEMODE_HOLE) {
//                    if (i>=BLOCK_NUM_WH-BLOCK_NUM_W*4) {
//                        g_game_blocks[i] = BLOCK_HOLE_WALL;
//                    }
//                }
//                if (g_game_blocks[i]== 255) {
//                    g_game_blocks[i] = -1;
//                }
//            }
//            for(int i=0;i<BLOCK_NUM_WH;i++){
//                g_game_gems[i] = dis->readShort();
//            }
//            CC_SAFE_DELETE(dis);
//        }
    }
    
    static bool G_costTool(int id){
        ToolInfo* info  = (ToolInfo*)G::g_toolinfos->objectAtIndex(id);
        if (info->getHoldCount()>0) {
            info->setHoldCount(info->getHoldCount()-1);
            return true;
        }else{
            if (G::G_getCoin()>=tool_prices[id]) {
                G::G_setCoin(G::G_getCoin()-tool_prices[id]);
                return true;
            }
        }
        return false;
    }
    
    static void G_loadConfig(){
        CCDictionary* _string = CCDictionary::createWithContentsOfFile("a.plist");
        for (int i = 0; i<MAX_SHOP_ITEM_COUNT; i++) {
            IntToStringFormat(_key, "v%d", i);
            CCString* _s_key = (CCString*)_string->objectForKey(_key);
            shop_item_prices[i] = _s_key->intValue()/100;
        }
        
        for (int i = 0; i<MAX_QUICK_BUY; i++) {
            IntToStringFormat(_key, "qv%d", i);
            CCString* _s_key = (CCString*)_string->objectForKey(_key);
            quick_buy_prices[i] = _s_key->intValue()/100;
        }
        _string->release();
        
        DataInputStream* dis = DataInputStream::loadFileWithPath("config/h");
        
        g_help_infos.clear();
        for(int i=0;i<MAX_STAGE;i++){
            vector<HELP_INFO*> help_infos;
            g_help_infos.push_back(help_infos);
        }
        
        int index =0;
        while (true) {
            int stage = d_guides[index][0];
            if (stage == 999) {
                break;
            }
            stage--;
            HELP_INFO* help_info = new HELP_INFO();
            help_info->retain();
            int x = d_guides[index][1];
            int y = d_guides[index][2];
            help_info->target_block_id = x+y*BLOCK_NUM_W;
            help_info->dir = d_guides[index][3];
            int mask_x = d_guides[index][4];
            int mask_y = d_guides[index][5];
            help_info->mask_id = d_guides[index][6];
            help_info->mask_pos_id = mask_x+mask_y*BLOCK_NUM_W;
            help_info->tips_id = d_guides[index][7];
            help_info->tips_in_type = d_guides[index][8];
            g_help_infos[stage].push_back(help_info);
            index++;
        }
        
        CC_SAFE_DELETE(dis);
        
        dis = DataInputStream::loadFileWithPath("config/a");
        
        int max_achieve = dis->readChar();
        
        for (int i = 0 ; i < max_achieve ; i++ ) {
            ACHIEVE_INFO* achieve_info = new ACHIEVE_INFO();
            achieve_info->id = i;
            achieve_info->type = dis->readShort();
            achieve_info->require = dis->readInt();
			int isopen = dis->readShort();
            achieve_info->isOpened =  isopen?true:false;
            g_achieve_infos->addObject(achieve_info);
        }
        CC_SAFE_DELETE(dis);
    }

    
    static vector<vector<HELP_INFO*> > g_help_infos;
    static CCArray* g_achieve_infos;
    
    static void G_Set_Achievement_Complete(int id,int complete){
        ACHIEVE_INFO* info = (ACHIEVE_INFO*)g_achieve_infos->objectAtIndex(id);
        info->setComplete(complete);
    }
    
    static void G_Set_SingleRound_Achievement_Complete(int id,int complete){
        ACHIEVE_INFO* info = (ACHIEVE_INFO*)g_achieve_infos->objectAtIndex(id);
        if (!info->is_complete) {
            CCLOG("set_singleround_achievement %d %d",id,complete);
            if (complete>info->complete) {
                info->setComplete(complete);
            }
        }
        
    }
    
    static void G_Add_Achievement_Complete(int id,int count = 1){
        ACHIEVE_INFO* info = (ACHIEVE_INFO*)g_achieve_infos->objectAtIndex(id);
        info->addComplete(count);
    }
    
    static void G_initAchievement_Item(ACHIEVE_INFO* info, cocos2d::extension::UIWidget *item){
        CCDictionary* _strings = CCDictionary::createWithContentsOfFile("data/achieve.plist");
        IntToStringFormat(_aNameKey, "achieve_name_%d", info->id);
        IntToStringFormat(_desKey, "achieve_des_%d", info->id);
        CCString* _aName = (CCString*)_strings->objectForKey(_aNameKey);
        CCString* _aDes = (CCString*)_strings->objectForKey(_desKey);
        CCString* _progress = (CCString*)_strings->objectForKey("progress_des");
        CCString* _complete = (CCString*)_strings->objectForKey("complete_des");
        COCO_UIIMAGEVIEW* _icon = (COCO_UIIMAGEVIEW*)item->getChildByName("icon");
        IntToStringFormat(_iconName, "achievement/icon_%d.png", info->type);
        _icon->setTexture(_iconName);
        COCO_UIIMAGEVIEW* bg = (COCO_UIIMAGEVIEW*)item->getChildByName("item_bg");
        UILabelBMFont* _name = (UILabelBMFont*)item->getChildByName("name");
        UILabelBMFont* _des = (UILabelBMFont*)item->getChildByName("label_1");
        _des->setScale(0.9f);
        UILabelBMFont* _progress_label = (UILabelBMFont*)item->getChildByName("label_2");
        
        if (info->complete == 0) {
            _progress_label->setColor(ccc3(129,129,129));
        }else{
            if(info->is_complete){
                _progress_label->setColor(ccc3(255,162,0));
            }else{
                _progress_label->setColor(ccc3(0,169,0));
            }
        }
        
        char _p[50];

		if (info->is_complete) {
		_des->setColor(ccc3(64 , 17 , 15));
		bg->setTexture("achievement/inner_bg_1.png");
		struct tm *ptm = localtime((time_t*)&info->complete_time);
		char tmp[100];
		strftime(tmp, sizeof(tmp), "%Y.%m.%d", ptm);
		sprintf(_p, _complete->getCString(),tmp);
		}else{
		_des->setColor(ccc3(129, 129, 129));
		bg->setTexture("achievement/inner_bg_2.png");
		sprintf(_p, _progress->getCString(),info->complete,info->require);
		}

		_name->setText(_aName->getCString());
		_des->setText(_aDes->getCString());
        
        _progress_label->setText(_p);
        
        _strings->release();
    }
    
    static bool G_hasNewAchieveCompleted(){
        for (unsigned int i=0; i<g_achieve_infos->count(); i++) {
            ACHIEVE_INFO* info = (ACHIEVE_INFO*)g_achieve_infos->objectAtIndex(i);
            if (info->is_complete&&info->isNew&&info->isOpened) {
                return true;
            }
        }
        return false;
    }
    
    static bool G_hasNewBaoGet(){
        for (unsigned int i=0; i<g_bao_infos->count(); i++) {
            BAO_INFO* info = (BAO_INFO*)g_bao_infos->objectAtIndex(i);
            if (info->isGot&&info->isNew&&baos_opened[i]) {
                return true;
            }
        }
        return false;
    }

    
    static bool g_share_reward_got[MAX_SHARE];
    
    static bool G_hasShare()
    {
        bool has_share = false;
        for (int i=0; i<MAX_SHARE; i++) {
            if (!G::g_share_reward_got[i]) {
                has_share = true;
                break;
            }
        }
        return has_share;
    }
    
    
    static bool g_hole_isOpened;
    static bool g_hole_isNewShowed;
    static bool g_sea_isOpened;
    static bool g_sea_isNewShowed;

    
    static CCArray* g_bao_infos;//BAO_INFO
    
    static bool g_cloud_isOpened[MAX_CLOUD];
    
    static bool g_has_first_saved;
    
    static int shop_item_prices[MAX_SHOP_ITEM_COUNT];
    
    static bool shop_th_has_buyed;
    static bool shop_ts_has_buyed;
    
    static int quick_buy_prices[MAX_QUICK_BUY];
    
    static long turntable_time;//每日抽奖上次更新次数时间
    static int turntable_count;//每日抽奖次数
    
    static GAMESCENE_TYPE g_gamescene_type;
};

#endif

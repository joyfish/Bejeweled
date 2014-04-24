//
//  HParams.h
//  Bejeweled
//
//  Created by wilford on 14-1-3.
//
//

#ifndef Bejeweled_HParams_h
#define Bejeweled_HParams_h

//这里定义界面件传递参数的结构

enum GAMEMODE_TYPE{
    MODE_TIME,//时间
    MODE_STEP//步数
};

class GameReadyModeParam{//游戏开始读秒参数传递
public:
    GAMEMODE_TYPE mode;
    GameReadyModeParam(GAMEMODE_TYPE mode){
        this->mode = mode;
    }
};

enum GAMETARGET_TYPE{
    TARGET_SCORE,//目标分数
    TARGET_CLEAR //清除目标
};

class GameLoseParam{//游戏失败参数传递
public:
    GAMETARGET_TYPE type;
    GameLoseParam(GAMETARGET_TYPE type){
        this->type = type;
    }
};

enum GAMEMODE{
    GAMEMODE_STAGE,//关卡模式
    GAMEMODE_HOLE, //洞穴模式
    GAMEMODE_SEA//深海模式
};


class GameWinParam{
public:
    int score;
    GameWinParam(int score){
        this->score = score;
    }
};

class HoleModeResultParam{
public:
    int hole_score;
    int depth;//这次的深度
    HoleModeResultParam(int hole_score,int depth){
        this->hole_score = hole_score;
        this->depth = depth;
    }
};

class SeaModeResultParam{
public:
    int hurt;
    int max_blood;
    SeaModeResultParam(int hurt,int max_blood){
        this->hurt = hurt;
        this->max_blood = max_blood;
    }
};

class ToolBuyParam{
public:
    int tool_id;
    int buy_count;
    ToolBuyParam(int tool_id,int buy_count){
        this->tool_id = tool_id;
        this->buy_count = buy_count;
    }
};

class GameStartParam{
public:
    int stage;
    int* win_conditions;//0 ~ 5 宝石 6 冰块 7 墙面 8 皇冠 9 有色砖块  10 分数
    int* lose_conditions;//0 时间 1 步数
    GameStartParam(int stage,int* win_conditions,int* lose_conditions){
        this->stage = stage;
        this->win_conditions = win_conditions;
        this->lose_conditions = lose_conditions;
    }
};

class RewardsParams{
public:
    CCArray* rewards;
    RewardsParams(CCArray* rewards){
        this->rewards = rewards;
    }
    
    ~RewardsParams(){
        rewards->removeAllObjects();
        CC_SAFE_DELETE(rewards);
    }
};

class NormalTipsParam{
public:
    int id;
    int param;
    NormalTipsParam(int id){
        this->id = id;
        param = -1;
    }
    NormalTipsParam(int id,int param){
        this->id = id;
        this->param = param;
    }
};

class GameHelpParam{
public:
    int id;
    int window_type;
    GameHelpParam(int id,int window_type){
        this->id = id;
        this->window_type = window_type;
    }
};


class QuickBuyParam{
public:
    int type;//0 金币不足 1 金币充值 2 精力不足 3 精力补充 4 勇气卷不足 5 勇气卷补充
    QuickBuyParam(int type){
        this->type = type;
    }
};

class AchieveCompletedParam{
public:
    int id;
    AchieveCompletedParam(int id){
        this->id = id;
    }

};

class BaoInfoParam{
public:
    int id;
    BaoInfoParam(int id){
        this->id = id;
    }
};


#endif

//
//  HParams.h
//  Bejeweled
//
//  Created by wilford on 14-1-3.
//
//

#ifndef Bejeweled_HParams_h
#define Bejeweled_HParams_h

//���ﶨ���������ݲ����Ľṹ

enum GAMEMODE_TYPE{
    MODE_TIME,//ʱ��
    MODE_STEP//����
};

class GameReadyModeParam{//��Ϸ��ʼ�����������
public:
    GAMEMODE_TYPE mode;
    GameReadyModeParam(GAMEMODE_TYPE mode){
        this->mode = mode;
    }
};

enum GAMETARGET_TYPE{
    TARGET_SCORE,//Ŀ�����
    TARGET_CLEAR //���Ŀ��
};

class GameLoseParam{//��Ϸʧ�ܲ�������
public:
    GAMETARGET_TYPE type;
    GameLoseParam(GAMETARGET_TYPE type){
        this->type = type;
    }
};

enum GAMEMODE{
    GAMEMODE_STAGE,//�ؿ�ģʽ
    GAMEMODE_HOLE, //��Ѩģʽ
    GAMEMODE_SEA//�ģʽ
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
    int depth;//��ε����
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
    int* win_conditions;//0 ~ 5 ��ʯ 6 ���� 7 ǽ�� 8 �ʹ� 9 ��ɫש��  10 ����
    int* lose_conditions;//0 ʱ�� 1 ����
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
    int type;//0 ��Ҳ��� 1 ��ҳ�ֵ 2 �������� 3 �������� 4 �������� 5 ��������
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

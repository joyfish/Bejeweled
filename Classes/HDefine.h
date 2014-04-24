//
//  HDefine.h
//  Bejeweled
//
//  Created by wilford on 14-1-5.
//
//

#ifndef Bejeweled_HDefine_h
#define Bejeweled_HDefine_h

#include "cocos2d.h"

USING_NS_CC;

#define RES_MUSIC_MENU_BG "menu_background.mp3"
#define RES_MUSIC_MAIN_BG "main_background.mp3"
#define RES_MUSIC_GAME_BG "game_background.mp3"
#define RES_MUSIC_GEM_COLLIDER "gem_collider.mp3"
#define RES_MUSIC_BOMB_0 "bomb_0.ogg"
#define RES_MUSIC_BOMB_1 "bomb_1.ogg"
#define RES_MUSIC_BOMB_2 "bomb_2.ogg"
#define RES_MUSIC_BOMB_3 "bomb_3.mp3"
#define RES_MUSIC_BOMB_4 "bomb_4.mp3"
#define RES_MUSIC_CREATE_1 "create_1.ogg"
#define RES_MUSIC_CREATE_2 "create_1.ogg"
#define RES_MUSIC_CREATE_3 "create_3.ogg"
#define RES_MUSIC_GAMEOVER "gameOver.ogg"
#define RES_MUSIC_SUCCESS "success.ogg"
#define RES_MUSIC_GAME_TOOL "game_tool_click.ogg"
#define RES_MUSIC_OVERLIGHT "overlight.ogg"
#define RES_MUSIC_ICE_BLOCK "ice_block.ogg"
#define RES_MUSIC_WALL_BLOCK "wall_block.ogg"
#define RES_MUSIC_LAST_TIME "last_time.ogg"
#define RES_MUSIC_MENU_START "menu_start.ogg"
#define RES_MUSIC_GAME_START "game_start.ogg"
#define RES_MUSIC_TOOL_BUY "tool_buy_click.ogg"
#define RES_MUSIC_NORMAL_CLICK "normal_click.ogg"
#define RES_MUSIC_GOLD_OUT "gold_out.ogg"

#define COCO_UIIMAGEVIEW cocos2d::extension::UIImageView
#define COCO_UIBUTTON cocos2d::extension::UIButton
#define COCO_UISCROLLVIEW cocos2d::extension::UIScrollView
#define COCO_UISLIDER cocos2d::extension::UISlider
#define COCO_UILOADINGBAR cocos2d::extension::UILoadingBar

#define POWER_ROCOVERY_TIME 540 //�������ָ�ʱ��



const int c_stage_bottom_count = 7;
const CCPoint stage_bottom_pos[c_stage_bottom_count] = {
    ccp(400,402),   //0
    ccp(292,458),   //1
    ccp(196, 554),  //2
    ccp(317, 606),  //3
    ccp(414, 681),  //4
    ccp(312, 743),  //5
    ccp(265, 860),  //6
};

const int c_stage_middle_count = 8;
const int c_middle_tree_padding = 673;

const CCPoint stage_middle_pos[c_stage_middle_count]={
    ccp(437, 966), //0
    ccp(324, 1021), //1
    ccp(243, 1129), //2
    ccp(400, 1174), //3
    ccp(460, 1300), //4
    ccp(314, 1374), //5
    ccp(421, 1474), //6
    ccp(269, 1548), //7
};

#define MAX_STAGE 200

#define CLOUD_PADDING 13

#define MAX_CLOUD MAX_STAGE/CLOUD_PADDING

//const int cloud_level[MAX_CLOUD] = {10,20,30,40};
//const int cloud_star[MAX_CLOUD] = {15,40,65,90};

enum TOOL_TYPE{
    TOOL_TYPE_TIME,
    TOOL_TYPE_STEP,
    TOOL_TYPE_HAMMER,
    TOOL_TYPE_REFRESH,
    TOOL_TYPE_SPECIAL,
    TOOL_TYPE_STAR,
    MAX_TOOL_COUNT
};

const int tool_prices[MAX_TOOL_COUNT] = {600,600,1000,800,1800,1000};
const int tool_open_level[MAX_TOOL_COUNT] = {8,6,7,9,11,10};
//const int tool_open_level[MAX_TOOL_COUNT] = {0,0,0,0,0,0};



#define MAX_SHOP_ITEM_COUNT 10//�̵����
const int shop_item_type[MAX_SHOP_ITEM_COUNT] = {0,0,0,0,8,8,1,9,10,11};//10 �ػ���� 11 �������
const int shop_item_tips[MAX_SHOP_ITEM_COUNT] = {0,1,2,3,0,0,0,0,4,4};
const int shop_item_getCount[MAX_SHOP_ITEM_COUNT] = {1000,3000,7000,24500,1,3,99,3,1,1};
//const int shop_item_type[MAX_SHOP_ITEM_COUNT] = {1,0,0,0,0,9};
//const int shop_item_tips[MAX_SHOP_ITEM_COUNT] = {0,0,1,2,3,4};
//const int shop_item_getCount[MAX_SHOP_ITEM_COUNT] = {99,2000,5000,8000,12000,3};

#define MAX_QUICK_BUY 4 //���ٹ���
const int quick_buy_type[MAX_QUICK_BUY] = {0,1,8,9};
const int quick_buy_getCount[MAX_QUICK_BUY] = {24500,99,3,3};

//��� ���� �������ʼ��
#define INIT_POWER 5
#define MAX_POWER 8
#define INIT_COIN 0
#define INIT_BOOK 3

//��Ϸ���
//#define MAX_WIN_CONDITIONS 11
//#define MAX_LOSE_CONDITIONS 2
#define BLOCK_WH 71
#define BLOCK_NUM_W 9
#define BLOCK_NUM_H 10
#define BLOCK_NUM_WH 90

const int stage_coin_rewards[3] = {40,70,100};

enum GEM_TYPE{//��ʯ����
	GEM_NORMAL = 0,//��ͨ��ʯ
	GEM_V = 1,//������ʯ
	GEM_H = 2,//������ʯ
	GEM_AREA = 3,//��ը��ʯ
	GEM_MAGIC = 4,//ħ��
    GEM_TIME = 5,//+5�뱦ʯ
    GEM_SPECIAL = 6,//���飿
    GEM_BEE = 7,//�۷�
    GEM_EGG = 8,//��
    GEM_COIL = 10,//����
    GEM_GOLD = 11,//�ʹ�
	GEM_VH = 12,//��������
	GEM_3VH = 13,//����3����
	GEM_3AREA = 14,//��Χ��ը
	GEM_MAGIC_NORMAL = 15,//ħ����ը��ͨ��ʯ
	GEM_MAGIC_VH = 16,//ħ��������ʯ
	GEM_MAGIC_AREA = 17,//ħ����ը��ʯ
	GEM_2MAGIC = 18,//2ħ������
    GEM_HOLE_WALL = 19,//ǽ
    GEM_HOLE_NORMAL = 20,//����
    GEM_HOLE_MID_1 = 21,//����1
    GEM_HOLE_MID_2 = 22,//����2
    GEM_HOLE_MID_3 = 23,//����3
    GEM_HOLE_SPECIAL_1 = 24,//ħ��
    GEM_HOLE_SPECIAL_2 = 25,//����
    GEM_HOLE_SPECIAL_3 = 26,//�Ŵ�
    GEM_HOLE_SPECIAL_4 = 27,//����
    GEM_HOLE_SPECIAL_5 = 28,//��ʯ
    GEM_HOLE_SPECIAL_6 = 29,//δ��ѿ������
    GEM_HOLE_SPECIAL_7 = 30, //ͷ��
    GEM_BAO,//����Ԫ��
    GEM_TIME_BOMB = 300,//��ʱը��
};

enum GEM_COLOR{//��ʯ��ɫ
	GEM_COLOR_0 = 1,
	GEM_COLOR_1 = 2,
	GEM_COLOR_2 = 3,
	GEM_COLOR_3 = 4,
	GEM_COLOR_4 = 5,
	GEM_COLOR_5 = 6,
	GEM_COLOR_NOCOLOR = 7,
};

enum BLOCK_BOTTOM_TYPE{//���²�Ԫ��
    BLOCK_BOTTOM_SPACE = 0,//�հ�
    BLOCK_BOTTOM_NORMAL = 1,//��ͨ����
    BLOCK_BOTTOM_ROPE = 2,//���� 0 ������ 1 �� 2 �� 4 �� 8 ��
    BLOCK_BOTTOM_DOOR_IN = 3,//���������
    BLOCK_BOTTOM_DOOR_OUT = 4,//�����ų���
    BLOCK_BOTTOM_DIRTY_RES = 5,//��ȾԴ
    BLOCK_BOTTOM_MAGNET = 6,//����ʯ
    BLOCK_BOTTOM_COIL_GUN = 7,//Ԫ��1������
    BLOCK_BOTTOM_GUN = 8,//��ͨԪ�ط�����
};

enum ROPE_DIR{
    ROPE_DIR_NONE = 0,
    ROPE_DIR_UP = 1,
    ROPE_DIR_RIGHT = 2,
    ROPE_DIR_DOWN = 4,
    ROPE_DIR_LEFT = 8,
};

enum BLOCK_MID_TYPE{//�в�Ԫ��
    BLOCK_MID_NONE = 0,
    BLOCK_MID_ICE = 1,//����
};

enum BLOCK_TOP_TYPE{
    BLOCK_TOP_NONE = 0,
    BLOCK_TOP_WALL = 1,//ǽ��
    BLOCK_TOP_DIRTY = 2,//����
    BLOCK_TOP_PRISON = 3,//����
    BLOCK_TOP_BIG_ICE = 4,//�����
    BLOCK_TOP_VIRUS = 5, //������
    BLOCK_TOP_EGG = 6,//���鵰
    BLOCK_TOP_SEA_WALL = 7//����צ
};

enum SPECIAL_BOMB_TYPE{
    SPECIAL_BOMB_V,//����ը
    SPECIAL_BOMB_H,//����ը
    SPECIAL_BOMB_AREA,//��ͨ����ը
    SPECIAL_BOMB_3AREA,//������ը
    SPECIAL_BOMB_MAGIC_NORMAL,//��ͨħʯ��ը
    SPECIAL_BOMB_MAGIC_VH,//ħʯ��Ч��ʯ����
    SPECIAL_BOMB_MAGIC_AREA,//ħʯ��ը��ʯ����
    SPECIAL_BOMB_2MAGIC//ħʯħʯ����
};

enum NEW_SPECIAL_GEM_TYPE{
    NEW_GEM_V = 1,
    NEW_GEM_H = 2,
    NEW_GEM_AREA = 4,
    NEW_GEM_MAGIC = 8,
};


enum EYE_DIR{
	EYE_DIR_NONE,
	EYE_DIR_UP,
	EYE_DIR_DOWN,
	EYE_DIR_LEFT,
	EYE_DIR_RIGHT,
	EYE_DIR_LEFT_UP,
	EYE_DIR_RIGHT_UP,
	EYE_DIR_LEFT_DOWN,
	EYE_DIR_RIGHT_DOWN
};

enum WIN_CONDITION{
    WIN_CONDITION_COLOR_0 = 0,
    WIN_CONDITION_COLOR_1 = 1,
    WIN_CONDITION_COLOR_2 = 2,
    WIN_CONDITION_COLOR_3 = 3,
    WIN_CONDITION_COLOR_4 = 4,
    WIN_CONDITION_COLOR_5 = 5,
    WIN_CONDITION_SCORE = 6,
    WIN_CONDITION_GOLD = 7,
    WIN_CONDITION_WALL = 8,
    WIN_CONDITION_ICE = 9,
    WIN_CONDITION_PRISON = 10,
    WIN_CONDITION_VIRUS = 11,
    WIN_CONDITION_MAX
};

enum LOSE_CONDITION{
    LOSE_CONDITION_TIME,
    LOSE_CONDITION_STEP,
    LOSE_CONDITION_MAX
};



enum GAME_STATE{
    GAME_STATE_PLAY,
    GAME_STATE_PAUSE,
    GAME_STATE_WIN,
    GAME_STATE_LOSE,
    GAME_STATE_END
};



static int hole_scores[] = {150,150,250,350,450,200,200,200,200,200,200,200};

const int maxHoleLevel = 16;

const int maxHoleTime = 120;//120;

const int maxRerwardTime = 30;

static int BOMB_MAX_COUNT = 12;
static int MAX_REPOSITON_PAIR = 40;

static int SEC_PER_LIGHT = 4;
static int STEP_PER_LIGHT = 1;


const int maxunlimitscorescount=4;
const int unlimitrewardscores[maxunlimitscorescount] = {4000,8000,12000,16000};

static int hole_wall_rates[][5] = {
    {24,0,0,0,0},
    {12,12,0,0,1},
    {0,24,0,0,2},
    {0,12,12,0,3},
    {0,0,24,0,4},
    {0,0,12,12,5},
    {0,0,0,24,6},
    {0,0,0,12,7},
    //    {0,0,7,13,8},
    //    {0,0,0,20,9},
    //    {0,0,0,20,10},
};

#define _SEA_MAX_BLOOD 24000

#define MAX_BAO  43

enum BAO_FROM{
    BAO_FROM_TREE,
    BAO_FROM_STAGE,
    //BAO_FROM_STAGE_OVER,
    BAO_FROM_HOLE,
    //BAO_FROM_HOLE_OVER,
    BAO_FROM_SEA,
    BAO_FROM_TURNTABLE
    //BAO_FROM_SEA_OVER
};

const BAO_FROM baos_type[MAX_BAO] = {
    BAO_FROM_TREE,//0
    BAO_FROM_TREE,//1
    BAO_FROM_TREE,//2
    BAO_FROM_TREE,//3
    BAO_FROM_TREE,//4
    BAO_FROM_TREE,//5
    BAO_FROM_TREE,//6
    BAO_FROM_TREE,//7
    BAO_FROM_TREE,//8
    BAO_FROM_TREE,//9
    BAO_FROM_TREE,//10
    BAO_FROM_TREE,//11
    BAO_FROM_TREE,//12
    BAO_FROM_TREE,//13
    BAO_FROM_TREE,//14
    BAO_FROM_TREE,//15
    BAO_FROM_STAGE,//16
    BAO_FROM_STAGE,//17
    BAO_FROM_STAGE,//18
    BAO_FROM_STAGE,//19
    BAO_FROM_HOLE,//20
    BAO_FROM_STAGE,//21
    BAO_FROM_STAGE,//22
    BAO_FROM_STAGE,//23
    BAO_FROM_STAGE,//24
    BAO_FROM_SEA,//25
    BAO_FROM_HOLE,//26
    BAO_FROM_STAGE,//27
    BAO_FROM_STAGE,//28
    BAO_FROM_STAGE,//29
    BAO_FROM_STAGE,//30
    BAO_FROM_STAGE,//31
    BAO_FROM_SEA,//32
    BAO_FROM_HOLE,//33
    BAO_FROM_HOLE,//34
    BAO_FROM_STAGE,//35
    BAO_FROM_HOLE,//36
    BAO_FROM_SEA,//37
    BAO_FROM_SEA,//38
    BAO_FROM_SEA,//39
    BAO_FROM_HOLE,//40
    BAO_FROM_TURNTABLE,//41
    BAO_FROM_TURNTABLE,//42
};//0 ���ϳ��� 1 �ؿ����� 2 �ؿ����� 3 ��Ѩ�г��� 4 ��Ѩ�������� 5 ���׳��� 6 ���׽�������
const int baos_level[MAX_BAO] = {
    24,//0
    84,//1
    36,//2
    180,//3
    192,//4
    120,//5
    60,//6
    144,//7
    156,//8
    132,//9
    48,//10
    12,//11
    96,//12
    72,//13
    168,//14
    108,//15
    16,//16
    73,//17
    115,//18
    100,//19
    -1,//20
    44,//21
    34,//22
    25,//23
    97,//24
    -1,//25
    -1,//26
    124,//27
    29,//28
    62,//29
    57,//30
    84,//31
    -1,//32
    -1,//33
    -1,//34
    19,//35
    -1,//36
    -1,//37
    -1,//38
    -1,//39
    -1,//40
    -1,//41
    -1,//42
};
const bool baos_opened[MAX_BAO] = {
    true,//0
    true,//1
    true,//2
    true,//3
    true,//4
    true,//5
    true,//6
    true,//7
    true,//8
    true,//9
    true,//10
    true,//11
    true,//12
    true,//13
    true,//14
    true,//15
    true,//16
    true,//17
    true,//18
    true,//19
    true,//20
    true,//21
    true,//22
    true,//23
    true,//24
    true,//25
    true,//26
    true,//27
    true,//28
    true,//29
    true,//30
    true,//31
    true,//32
    true,//33
    true,//34
    true,//35
    true,//36
    true,//37
    true,//38
    true,//39
    true,//40
    true,//41
    true,//42
};

#define MAX_BAO_TREE_COUNT 16

const int baos_tree_ids[MAX_BAO_TREE_COUNT]={
    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
};

const CCPoint baos_tree_pos[] = {
    ccp(373,424),   //0
    ccp(215,473),   //1
    ccp(431, 510),  //2
    ccp(327, 548),  //3
    ccp(180, 600),  //4
    ccp(368, 680),  //5
    ccp(208, 747),  //6
    ccp(400, 780),  //7
    ccp(315, 843),  //8
    ccp(210, 906),  //9
    ccp(480, 945),  //10
    ccp(343, 1000), //11
    ccp(207, 1114), //12
    ccp(365, 1134), //13
    ccp(500, 1196), //16
};

const int d_guides[][9]={
    {1,4,3,3,3,4,1,0,0},//��������
    {1,4,4,2,5,5,2,1,0},
    {1,0,0,0,0,0,0,2,1},
    {2,2,3,4,3,3,3,3,0},//������Ч��ʯ����
    {2,5,4,2,4,5,4,4,0},
    //{2,0,0,0,0,0,15,6,1},
    {3,5,4,3,4,3,5,7,0},//��Χ��Ч��ʯ����
    {3,4,4,2,3,5,4,8,0},
    {3,0,0,0,0,0,0,9,1},
    {4,5,5,1,5,5,6,10,0},//��Χ+������Ч����
    {4,0,0,0,0,0,16,11,1},
    {5,4,3,2,4,4,7,12,0},//ħ������
    {5,4,4,2,4,5,6,13,0},
    {5,0,0,0,0,0,0,14,1},
    {6,3,3,4,3,3,8,15,0},//ħ��+������ʯ����
    {6,0,0,0,0,0,0,16,1},
    {9,0,0,0,0,0,9,17,1},//ʣ��ʱ������
    {10,6,5,3,5,5,10,18,0},//��������
    {10,0,0,0,0,0,0,19,1},
    {14,7,3,3,5,3,13,27},//èͷӥ����
    {21,3,1,2,4,2,2,20,0},//ǽ������
    {28,4,5,3,3,5,11,21,0},//�ʹ�����
    {28,0,0,0,0,0,0,22,1},
    {32,3,4,3,2,5,1,23,0},//��������
    {32,0,0,0,0,0,0,24,1},
    {32,0,0,0,0,0,0,25,1},
    {37,4,4,2,5,5,2,26,0},//��������
    {47,0,0,0,0,7,14,28,0},//��Ⱦ������
    {52,0,0,0,7,7,14,29,0},//��ʱը������
    {70,0,0,0,4,9,14,32,0},//��ȾԴ����
    {42,0,0,0,4,3,14,34,0},//���鷢����
    {57,0,0,0,1,7,14,30,0},//����+5
    {61,0,0,0,3,4,14,31,0},//����?
    {80,0,0,0,4,4,14,33,0},//�����
    {8,0,0,0,0,0,17,41,0},//���ӵ��߿���
    {12,0,0,0,0,0,19,42,0},//�������߿���
    {10,0,0,0,0,0,18,43,0},//ˢ�µ��߿���
    {999}
};

#define MAX_SHARE 3

enum GAMESCENE_TYPE{
    GAMESCENE_NONE,
    GAMESCENE_LOGO,
    GAMESCENE_MENU,
    GAMESCENE_MAIN,
    GAMESCENE_GAME
};

#endif

//
//  HGloba.cpp
//  Bejeweled
//
//  Created by wilford on 14-1-6.
//
//

#include "HGloba.h"

long G::g_last_power_recovery_time = 0;
int G::g_mPower = 0;
int G::g_maxPower =0;
int G::g_mBook = 0;
int G::g_mCoin = 0;
void* G::g_currentScene = NULL;
bool G::g_mIsBackgroundMusicOn = false;
bool G::g_mIsEffectVolumeOn = false;
vector<const char*> G::g_m_played_effects;
CCArray* G::g_stageInfos = new CCArray();
CCArray* G::g_toolinfos = new CCArray();
int G::g_hole_max_score = 0;
int G::g_hole_total_depth = 0 ;
BUY_TYPE G::g_last_buytype = BUY_TYPE_NONE;
int G::g_last_buyid = 0;

int G::g_game_buff[3];
int G::g_game_win_conditions[WIN_CONDITION_MAX];
int G::g_game_lose_conditions[LOSE_CONDITION_MAX];
int G::g_game_blocks[BLOCK_NUM_WH];
int G::g_game_gems[BLOCK_NUM_WH];
GAMEMODE G::g_game_mode = GAMEMODE_STAGE;
int G::g_game_maxColorCount = 0;
int G::g_game_max_gold_count = 0;
int G::g_game_max_gem_time_count =0;
int G::g_game_max_gem_egg_count=0;
int G::g_game_max_gem_timebomb_count=0;
int G::g_game_star2_score = 0;
int G::g_game_star_score = 0;
int G::g_game_stage = 0;
vector<vector<HELP_INFO*> > G::g_help_infos;
CCArray* G::g_achieve_infos = new CCArray();
CCArray* G::g_bao_infos = new CCArray();

bool G::tree_scroll_has_showed = false;
bool G::g_share_reward_got[MAX_SHARE];
bool G::g_hole_isOpened = false;
bool G::g_hole_isNewShowed = false;
bool G::g_sea_isOpened = false;
bool G::g_sea_isNewShowed = false;

bool G::g_cloud_isOpened[MAX_CLOUD];
bool G::g_has_first_saved = false;

int G::shop_item_prices[MAX_SHOP_ITEM_COUNT];
int G::quick_buy_prices[MAX_QUICK_BUY];
bool G::shop_th_has_buyed = false;
bool G::shop_ts_has_buyed = false;

long G::turntable_time = 0;
int G::turntable_count = 0;

GAMESCENE_TYPE G::g_gamescene_type = GAMESCENE_NONE;




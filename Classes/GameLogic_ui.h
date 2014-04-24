//
//  GameLogic_ui.h
//  Test
//
//  Created by wilford on 14-3-6.
//
//

#ifndef __Test__GameLogic_ui__
#define __Test__GameLogic_ui__

#include "GameLogic_block_update.h"
#include "cocos-ext.h"
#include "HJNI.h"

USING_NS_CC_EXT;

typedef void (CCObject::*SEL_TOOLBUY)(int id,int count);
#define h_toolBuy(_SELECTOR) (SEL_TOOLBUY)(&_SELECTOR)
typedef void (CCObject::*SEL_GAMEPAUSE)();
#define h_gamePause(_SELECTOR) (SEL_GAMEPAUSE)(&_SELECTOR)

class GameLogic_ui:public GameLogic_block_update{
public:
    void addToolBuyEvent(CCObject* target,SEL_TOOLBUY selector){
        m_tool_buy_listener = target;
        m_tool_buy_selector = selector;
    }
    
    void addGamePauseEvent(CCObject* target,SEL_GAMEPAUSE selector){
        m_gamePause_listener = target;
        m_gamePause_selector = selector;
    }
    
    void setMLayer(UILayer* layer){
        m_layer = layer;
    }

protected:
    GameLogic_ui()
    :m_ui_layer(NULL)
    ,m_tool_buy_listener(NULL)
    ,m_tool_buy_selector(NULL)
    ,m_tool_mask(NULL)
    ,m_coin_num(NULL)
    {
        
    }
    
   
    
    
    void ShowGamePause(CCObject* sender);
    
    void UseTool(int tool_id,int pos_id);
    
    bool MagicTool(int pos_id);
    
    bool BombTool(int pos_id);
   
    void updateToolBtns();
    
    void ToolBuy(int id,int count);
    
    void OnControllerButtonClicked(CCObject* sender);
    
    void initToolBtns(UIWidget* parent);
    
    void ToolOpenAnim(UIWidget* tool,float delay);
    
    void initUI();
    
    void drawBackground();
    
    void drawNormalBackground();
    
    void drawHoleBackground();
    
    void drawSeaBackground();

    
    virtual void showWinConditionAnim(int id);
    
    void updateConditions(float dt);
    
    void updateHole(float dt);
    
    void updateHoleRise();
    
    void updateSea(float dt);
    
    void HoleRise();
    
    virtual void showScore(int score,int pos = -1);
    virtual void showScore(GEM_TYPE type,GEM_COLOR color,int pos);
    virtual void showHoleScore(GEM_TYPE type,int pos);
    virtual void showSeaHurt(int hurt,int pos);
    
    void show_score_effect(CCPoint from,CCPoint to);
    
    void RotateEye();
    virtual void SeaMouthOut();
    
    void initCombo();
    
    void showHammerAnim(int pos);
    void showMagicAnim(int pos);
    void showXAnim(int pos);
    
    void showToolMask(int id);
    void clearToolMask();
    
    
    virtual void Combo();
    
    virtual void closeGuide(){}
    
protected:
    CCObject* m_tool_buy_listener;
    SEL_TOOLBUY m_tool_buy_selector;
    CCObject* m_gamePause_listener;
    SEL_GAMEPAUSE m_gamePause_selector;
    
    UILoadingBar* m_score_bar;
    UILabelBMFont* m_score_num;
    UILayer* m_layer;
    UILayer* m_ui_layer;
    UILayer* m_ui_top_layer;
    UIWidget* toolwidget[MAX_TOOL_COUNT];
    COCO_UIIMAGEVIEW* flag_2;
    COCO_UIIMAGEVIEW* flag_3;
    UILabelBMFont* m_label_win_conditions[WIN_CONDITION_MAX];
    UIWidget* m_win_condition_icons[WIN_CONDITION_MAX];
    COCO_UILOADINGBAR* m_win_condition_progress[WIN_CONDITION_MAX];
    UIWidget* time_or_step_bg;
    UILabelAtlas* num_time_or_step;
    CCSprite* combo_label_sprite;
    CCLabelAtlas* combo_num;
    CCLabelAtlas* combo_score_num;
    CCLayerColor* m_tool_mask;
    UILabelBMFont* m_coin_num;
    COCO_UISLIDER* m_hole_bar;
    COCO_UIIMAGEVIEW* m_hole_clock_img;
    
    COCO_UISLIDER* m_sea_bar;
    COCO_UIIMAGEVIEW* m_sea_heart_img;
    
    CCSprite* m_sea_eye_left;
    CCSprite* m_sea_eye_right;
    CCSprite* m_sea_mouth;
    
    UILabelAtlas* m_hole_time_num;
    UILabelAtlas* m_hole_score_num;
    UILabelAtlas** m_hole_num;
};

#endif /* defined(__Test__GameLogic_ui__) */

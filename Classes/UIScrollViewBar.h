//
//  UIScrollViewBar.h
//  Bomb
//
//  Created by wilford on 13-12-12.
//
//

#ifndef Bomb_UIScrollViewBar_h
#define Bomb_UIScrollViewBar_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "AutoSceneSize.h"
#include "HDefine.h"

USING_NS_CC;
USING_NS_CC_EXT;

enum UISCROLLBAR_DIR{
UISCROLLBAR_VERTICAL=0,
UISCROLLBAR_HORIZONTAL
};

class UIScrollViewBar : public cocos2d::extension::UIWidget{
public:
    UIScrollViewBar();
    virtual ~UIScrollViewBar();
    
    CREATE_FUNC(UIScrollViewBar);
    
    virtual bool init();
    
    void attach(COCO_UISCROLLVIEW* view,UISCROLLBAR_DIR dir);
    
    void setBackgroundImage(const char* fileName,float width);
    void setForegroundImage(const char* fileName);
    
    void restBarSize();
    
    void setPercent(int percent);
    
    virtual void update(float dt);
    
    void updateBar();
private:
    
    COCO_UIIMAGEVIEW* m_background;
    COCO_UIIMAGEVIEW* m_foreground;
    int m_percent;
    float m_bar_start_x;
    float m_bar_end_x;
    float m_scrollview_inner;
    float m_scrollview_container;
    COCO_UISCROLLVIEW* attachView;
    UISCROLLBAR_DIR m_scroll_dir;
};


#endif

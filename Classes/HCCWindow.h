//
//  HCCWindow.h
//  Bomb
//
//  Created by wilford on 13-12-20.
//
//

#ifndef __Bomb__HCCWindow__
#define __Bomb__HCCWindow__

#include "HIWindow.h"
#include "HSelectors.h"
#include "HPlatform.h"
#include "HUIWidgetHelper.h"
#include "HWindowsManager.h"
#include "AutoSceneSize.h"
#include "HPersistence.h"
#include "HDefine.h"
#include "HParams.h"
#include "HTools.h"

//USING_NS_CC;
//USING_NS_CC_EXT;

//使用注意：
//1 继承 HCCWindow 无特殊需要的话用WINDOW_SHOW(__T__) 或者 WINDOW_SINGTON_SHOW(__T__)(需要自己定义static __T__* instance;) 重写与定义静态show(UILayer* layer)方法
//2 在init编写界面初始化内容
//3 给m_tips赋值，它是加载Json获得的界面根Panel(注：它的子集必须命名给"bg"，它是弹出界面的实际背景)
//4 调用closeWindow关闭界面
//5 在代码中使用__T__::show(layer,data)开启界面

typedef void (CCObject::*SEL_WINDOWCLOSEDEVENT)();
#define h_windowclosedselector(_SELECTOR) (SEL_WINDOWCLOSEDEVENT)(&_SELECTOR)

enum WINDOW_ANIM{
WINDOW_ANIM_TOP,
WINDOW_ANIM_RIGHT
};

class HCCWindow:public HIWindow{
public:
    //重写它来开启窗口
    virtual void show();
    //窗口关闭时会被调用
    virtual void close();
    //设置弹出窗口是否可用
    void setTocuhEnable(bool enabled);
    
    virtual void update(float dt){}
    
    HCCWindow();
    ~HCCWindow();
    
protected:
    
    //关闭窗口的时候请调用它
    void closeWindow();
    //打开界面时播放的动画，重写它来自定义
    virtual void startAnim();
    //关闭界面时播放的动画，重写它来自定义，动画播放完回调onCloseAnimOver
    virtual void endAnim();
    
    //关闭窗口动画结束一定要调用这个方法来正式关闭窗口
    void onCloseAnimOver(CCNode* sender);
    
    //添加界面关闭之后的回调事件（用于处理界面完全关闭后才进行的事务）
    void addWindowClosedEvent(CCObject* target,SEL_WINDOWCLOSEDEVENT selector){
        m_windowclosedListener = target;
        m_windowclosedselector = selector;
    }
    
    virtual void onClose();
    
    void setAnimType(WINDOW_ANIM anim_type){
        m_anim_type = anim_type;
    }
    
    //窗口对象
    bool m_autoCenter;
    UIWidget* m_tips;
    //窗口所在的UILayer
    UILayer* m_layer;
    HUIWidgetHelper* m_widgetHelper;
private:
   
    WINDOW_ANIM m_anim_type;
    CCObject* m_windowclosedListener;
    SEL_WINDOWCLOSEDEVENT m_windowclosedselector;
};


#endif /* defined(__Bomb__HCCWindow__) */

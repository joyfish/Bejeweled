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

//ʹ��ע�⣺
//1 �̳� HCCWindow ��������Ҫ�Ļ���WINDOW_SHOW(__T__) ���� WINDOW_SINGTON_SHOW(__T__)(��Ҫ�Լ�����static __T__* instance;) ��д�붨�徲̬show(UILayer* layer)����
//2 ��init��д�����ʼ������
//3 ��m_tips��ֵ�����Ǽ���Json��õĽ����Panel(ע�������Ӽ�����������"bg"�����ǵ��������ʵ�ʱ���)
//4 ����closeWindow�رս���
//5 �ڴ�����ʹ��__T__::show(layer,data)��������

typedef void (CCObject::*SEL_WINDOWCLOSEDEVENT)();
#define h_windowclosedselector(_SELECTOR) (SEL_WINDOWCLOSEDEVENT)(&_SELECTOR)

enum WINDOW_ANIM{
WINDOW_ANIM_TOP,
WINDOW_ANIM_RIGHT
};

class HCCWindow:public HIWindow{
public:
    //��д������������
    virtual void show();
    //���ڹر�ʱ�ᱻ����
    virtual void close();
    //���õ��������Ƿ����
    void setTocuhEnable(bool enabled);
    
    virtual void update(float dt){}
    
    HCCWindow();
    ~HCCWindow();
    
protected:
    
    //�رմ��ڵ�ʱ���������
    void closeWindow();
    //�򿪽���ʱ���ŵĶ�������д�����Զ���
    virtual void startAnim();
    //�رս���ʱ���ŵĶ�������д�����Զ��壬����������ص�onCloseAnimOver
    virtual void endAnim();
    
    //�رմ��ڶ�������һ��Ҫ���������������ʽ�رմ���
    void onCloseAnimOver(CCNode* sender);
    
    //��ӽ���ر�֮��Ļص��¼������ڴ��������ȫ�رպ�Ž��е�����
    void addWindowClosedEvent(CCObject* target,SEL_WINDOWCLOSEDEVENT selector){
        m_windowclosedListener = target;
        m_windowclosedselector = selector;
    }
    
    virtual void onClose();
    
    void setAnimType(WINDOW_ANIM anim_type){
        m_anim_type = anim_type;
    }
    
    //���ڶ���
    bool m_autoCenter;
    UIWidget* m_tips;
    //�������ڵ�UILayer
    UILayer* m_layer;
    HUIWidgetHelper* m_widgetHelper;
private:
   
    WINDOW_ANIM m_anim_type;
    CCObject* m_windowclosedListener;
    SEL_WINDOWCLOSEDEVENT m_windowclosedselector;
};


#endif /* defined(__Bomb__HCCWindow__) */

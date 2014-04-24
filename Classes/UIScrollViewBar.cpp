//
//  UIScrollViewBar.cpp
//  Bomb
//
//  Created by wilford on 13-12-12.
//
//

#include "UIScrollViewBar.h"


UIScrollViewBar::UIScrollViewBar():
m_background(NULL),
m_foreground(NULL),
m_bar_end_x(0),
m_bar_start_x(0),
m_percent(100),
m_scrollview_container(0),
m_scrollview_inner(0),
m_scroll_dir(UISCROLLBAR_VERTICAL)
{
    
}

UIScrollViewBar::~UIScrollViewBar(){
    if (m_background) {
        m_background->removeFromParentAndCleanup(true);
    }
    if (m_foreground) {
        m_foreground->removeFromParentAndCleanup(true);
    }
}

bool UIScrollViewBar::init(){
    bool flag = UIWidget::init();
    setUpdateEnabled(true);
    return flag;
}

void UIScrollViewBar::attach(cocos2d::extension::UIScrollView *view,UISCROLLBAR_DIR dir){
    if (view == NULL) {
        return;
    }
    attachView = view;
    m_scroll_dir = dir;
    switch (dir) {
        case UISCROLLBAR_VERTICAL:
            m_scrollview_inner = attachView->getSize().height;
            m_scrollview_container = attachView->getInnerContainerSize().height;
            break;
        case UISCROLLBAR_HORIZONTAL:
            m_scrollview_inner = attachView->getSize().width;
            m_scrollview_container =attachView->getInnerContainerSize().width;
            break;
        default:
            break;
    }
    restBarSize();
}

void UIScrollViewBar::setBackgroundImage(const char *fileName,float width){
    if (m_background==NULL) {
        m_background = UIImageView::create();
        this->addChild(m_background);
        m_background->setZOrder(0);
    }
    m_background->setTexture(fileName);
    CCSize image_size = m_background->getSize();
    m_background->setScale9Enabled(true);
    m_background->setCapInsets(CCRectMake(11, 11, 43, 2));
    m_background->setScale9Size(CCSizeMake(width, image_size.height));
    m_background->setAnchorPoint(_nLeft);
    m_background->setPosition(CCPointZero);
    restBarSize();
}

void UIScrollViewBar::setForegroundImage(const char *fileName){
    if (m_foreground == NULL) {
        m_foreground = UIImageView::create();
        this->addChild(m_foreground);
        m_foreground->setZOrder(1);
    }
    m_foreground->setTexture(fileName);
    CCSize image_size = m_foreground->getSize();
    m_foreground->setScale9Enabled(true);
    m_foreground->setCapInsets(CCRectMake(11, 11, 43, 2));
    m_foreground->setScale9Size(image_size);
    m_foreground->setAnchorPoint(_nLeft);
    m_foreground->setPosition(CCPointZero);
    restBarSize();
}

void UIScrollViewBar::restBarSize(){
    if (m_scrollview_inner==0||m_scrollview_container==0) {
        setVisible(false);
        return;
    }
    if (m_background==NULL||m_foreground == NULL) {
        return;
    }
    
    CCSize backgroundSize = m_background->getSize();
    
    float sizepercent = m_scrollview_inner/m_scrollview_container;
    
    if (sizepercent>1) {
        sizepercent =1;
    }
    
    if (sizepercent==1) {
        setVisible(false);
    }else
        setVisible(true);
    
    m_foreground->setScale9Size(CCSizeMake(backgroundSize.width*sizepercent, m_foreground->getSize().height));
    
    m_bar_end_x = m_background->getSize().width - m_foreground->getSize().width;
}

void UIScrollViewBar::setPercent(int percent){
    if (m_foreground==NULL||m_bar_end_x ==0) {
        return;
    }
    percent = MAX(0, percent);
    percent = MIN(100, percent);
    
    m_foreground->setPosition(ccp(m_bar_end_x*percent/100, 0));
}

void UIScrollViewBar::update(float dt){
    UIWidget::update(dt);
    updateBar();
}

void UIScrollViewBar::updateBar(){
    if (attachView==NULL) {
        return;
    }
    Layout* inner = attachView->getInnerContainer();
    
    bool bSizeChanged = false;
    
    switch (m_scroll_dir) {
        case UISCROLLBAR_HORIZONTAL:
        {
            if (m_scrollview_container!=inner->getSize().width) {
                m_scrollview_container = inner->getSize().width;
                bSizeChanged = true;
            }
            if (m_scrollview_inner!=attachView->getSize().width) {
                m_scrollview_inner = attachView->getSize().width;
                bSizeChanged = true;
            }
            if (bSizeChanged) {
                restBarSize();
            }
            
            float maxW = inner->getSize().width- attachView->getSize().width;
            maxW = MAX(0, maxW);
            float offsetX = abs(inner->getPosition().x);
            offsetX=MIN(maxW, offsetX);
            setPercent((offsetX)*100/maxW);
        }
            break;
        case UISCROLLBAR_VERTICAL:{
            if (m_scrollview_container!=inner->getSize().height) {
                m_scrollview_container = inner->getSize().height;
                bSizeChanged = true;
            }
            
            if (m_scrollview_inner!=attachView->getSize().height) {
                m_scrollview_inner = attachView->getSize().height;
                bSizeChanged = true;
            }
            
            if (bSizeChanged) {
                restBarSize();
            }
            float maxH = inner->getSize().height-attachView->getSize().height;
            maxH = MAX(0, maxH);
            float offsetY = abs(inner->getPosition().y);
            offsetY=MIN(maxH, offsetY);
            setPercent((offsetY)*100/maxH);
        }
            break;
            
        default:
            break;
    }
}



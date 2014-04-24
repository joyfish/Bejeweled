
#include "AutoSceneSize.h"

AutoSceneSize* AutoSceneSize::instance = NULL;

AutoSceneSize* AutoSceneSize::S(void)
{
    if (!instance)
    {
        instance = new AutoSceneSize();
        instance->init();
    }
    return instance;
}

bool AutoSceneSize::init(void)
{
    return true;
}

void AutoSceneSize::setVirtualScreenWidth(float width)
{
    const CCSize& winSizeInPixels = CCDirector::sharedDirector()->getWinSizeInPixels();

    m_scale = winSizeInPixels.width / width;
    m_screenSize.width = width;
    m_screenSize.height = winSizeInPixels.height / m_scale;
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(m_screenSize.width,
        m_screenSize.height,kResolutionExactFit);

    CCLOG("Virtual width: %0.2f, Virtual height: %0.2f, scale: %0.2f",
        m_screenSize.width, m_screenSize.height, m_scale);

    const CCSize& winSize = CCDirector::sharedDirector()->getWinSize();
    m_center.x = winSize.width / 2;
    m_center.y = winSize.height / 2;
    m_left = 0;
    m_right = m_screenSize.width;
    m_top = m_screenSize.height;
    m_bottom = 0;

    CCLOG("center x: %0.2f, center y: %0.2f", m_center.x, m_center.y);
    CCLOG("top: %0.2f, right: %0.2f, bottom: %0.2f, left: %0.2f", m_top, m_right, m_bottom, m_left);
}

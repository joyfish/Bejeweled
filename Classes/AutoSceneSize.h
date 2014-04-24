#ifndef __SMART_RES_H_
#define __SMART_RES_H_


#include "cocos2d.h"

USING_NS_CC;

#define _pCenter     AutoSceneSize::S()->getCenter()
#define _pTop        AutoSceneSize::S()->getTop()
#define _pRight      AutoSceneSize::S()->getRight()
#define _pBottom     AutoSceneSize::S()->getBottom()
#define _pLeft       AutoSceneSize::S()->getLeft()
#define _pScale      AutoSceneSize::S()->getScale()
#define _pXY(v)      AutoSceneSize::S()->xy(v)
#define _pScreenSize AutoSceneSize::S()->getScreenSize()

#define _nCenter      ccp(.5,.5)
#define _nTop	      ccp(.5,1)
#define _nRight       ccp(1,.5)
#define _nBottom      ccp(.5,0)
#define _nLeft        ccp(0,.5)
#define _nTopLeft     ccp(0,1)
#define _nTopRight    ccp(1,1)
#define _nBottomLeft  ccp(0,0)
#define _nBottomRight ccp(1,0)

class AutoSceneSize
{
public:
    static AutoSceneSize* S(void);

	static void release(){
		CC_SAFE_DELETE(instance);
	}

    void setVirtualScreenWidth(float width);

    const CCSize getScreenSize(void) {
        return m_screenSize;
    }

    float getScale(void) {
        return m_scale;
    }

    const CCPoint getCenter(void) {
        return m_center;
    }

    float getTop(void) {
        return m_top;
    }

    float getRight(void) {
        return m_right;
    }

    float getBottom(void) {
        return m_bottom;
    }

    float getLeft(void) {
        return m_left;
    }

    float xy(float v) {
        return m_scale * v;
    }

private:
    AutoSceneSize(void)
    : m_scale(1.0f)
    , m_top(0)
    , m_right(0)
    , m_bottom(0)
    , m_left(0)
    {
    }
    bool init(void);

    static AutoSceneSize* instance;

    CCSize m_screenSize;
    CCPoint m_center;
    float m_scale;
    float m_top;
    float m_right;
    float m_bottom;
    float m_left;
};

#endif
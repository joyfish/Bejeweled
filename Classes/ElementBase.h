//
//  ElementBase.h
//  Test
//
//  Created by wilford on 14-3-5.
//
//

#ifndef Test_ElementBase_h
#define Test_ElementBase_h

#include "cocos2d.h"

USING_NS_CC;

typedef CCPoint (CCObject::*SEL_GETPOS)(int pos);
#define h_getPos(_SELECTOR) (SEL_GETPOS)(&_SELECTOR)

class ElementBase{
public:
    int id;//元素id
    int pos;//元素位置id
    
    ElementBase()
    :m_getPosListener(NULL)
    ,m_getPosSelector(NULL)
    ,id(0)
    ,pos(-1)
    {}
    
    void AddGetPosEvent(CCObject* target,SEL_GETPOS selector){//添加获得元素坐标
        this->m_getPosListener = target;
        this->m_getPosSelector = selector;
    }
    
    
protected:
    CCPoint GetPos(){//获得元素坐标
        return  GetPos(pos);
    }
    
    CCPoint GetPos(int pos){
        if (m_getPosListener&&m_getPosSelector) {
            return (m_getPosListener->*m_getPosSelector)(pos);
        }
        return CCPointZero;
    }
    
    CCObject* m_getPosListener;
    SEL_GETPOS m_getPosSelector;
};

#endif

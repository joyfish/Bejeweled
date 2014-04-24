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
    int id;//Ԫ��id
    int pos;//Ԫ��λ��id
    
    ElementBase()
    :m_getPosListener(NULL)
    ,m_getPosSelector(NULL)
    ,id(0)
    ,pos(-1)
    {}
    
    void AddGetPosEvent(CCObject* target,SEL_GETPOS selector){//��ӻ��Ԫ������
        this->m_getPosListener = target;
        this->m_getPosSelector = selector;
    }
    
    
protected:
    CCPoint GetPos(){//���Ԫ������
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

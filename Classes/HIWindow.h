//
//  HIWindow.h
//  Bomb
//
//  Created by wilford on 13-12-16.
//
//

#ifndef Bomb_HIWindow_h
#define Bomb_HIWindow_h

#include "cocos2d.h"

USING_NS_CC;

class HIWindow:public CCObject{
public:
    //overide to close your window
    //
    virtual void close();
    
    //
    //overide to update
    //
    virtual void update(float dt);
    
    virtual void releaseRes(){
    }

    
    int getZOrder(){return m_zOrder;}
    void setZOrder(int zorder){
        m_zOrder = zorder;
    }

private:
    int m_zOrder;
};

#endif

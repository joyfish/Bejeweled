//
//  HWindowsManager.cpp
//  Bomb
//
//  Created by wilford on 13-12-15.
//
//

#include "HWindowsManager.h"

#define PopWindowMinZOrder 50;
#define PopWindowPadding 10;

HWindowsManager* HWindowsManager::S(){
    if (m_instance==NULL) {
        m_instance = new HWindowsManager();
    }
    return m_instance;
}

void HWindowsManager::pushWindow(HIWindow *window){
    m_windows->addObject(window);
    CCLOG("-------openWindow  %d",m_windows->count());
}

void HWindowsManager::closeWindow(HIWindow *window){
    if (!window) {
        return;
    }
	CCLOG("closeWindowStart -> %d",m_windows->count());
	CCObject* o;
	CCARRAY_FOREACH(m_windows,o){
		if (window==o)
		{
			m_windows->removeObject(window);
		}
	}
	CCLOG("closeWindowEnd -> %d",m_windows->count());
	m_toclose->addObject(window);
}

void HWindowsManager::closeAllWindows(){
	CCObject* o;
	CCARRAY_FOREACH(m_windows,o){
		m_windows->removeObject(o);
		HIWindow* w = (HIWindow*)o;
		w->close();
        w->releaseRes();
		CC_SAFE_DELETE(w);
	}
    CCLOG("-------closeAllWindows  %d",m_windows->count());
}

void HWindowsManager::clearToClose(){
	CCObject* o;
	CCARRAY_FOREACH(m_toclose,o){
		m_toclose->removeObject(o);
		HIWindow* w = (HIWindow*)o;
		w->close();
        w->releaseRes();
		CC_SAFE_DELETE(w);
	}
}

void HWindowsManager::update(float dt){
	clearToClose();
	updateWindows(dt);
}

void HWindowsManager::updateWindows(float dt){
	CCObject* o;
	CCARRAY_FOREACH(m_windows,o){
		HIWindow* window = (HIWindow*)o;
		if (window)
		{
			window->update(dt);
		}	
	}
}

void HWindowsManager::popWindow(){
   closeWindow((HIWindow*)(m_windows->objectAtIndex(m_windows->count()-1)));
}

int HWindowsManager::getTopZOrder(){
    int zOrder = PopWindowMinZOrder;
    CCObject* o;
    CCARRAY_FOREACH(m_windows,o){
		HIWindow* window = (HIWindow*)o;
		if (window)
		{
			if (zOrder<window->getZOrder()) {
                zOrder = window->getZOrder();
            }
		}
	}
    CCLOG("topZOrder  = %d",zOrder);
    return zOrder+PopWindowPadding;
}

HWindowsManager::HWindowsManager(){
    m_windows= new CCArray();
	m_toclose = new CCArray();
}

HWindowsManager::~HWindowsManager(){
	
	if (m_windows)
	{
		m_windows->removeAllObjects();
	}
	
	if (m_toclose)
	{
		m_toclose->removeAllObjects();
	}
	
	
	CC_SAFE_DELETE(m_windows);
	CC_SAFE_DELETE(m_toclose);
}

HWindowsManager* HWindowsManager::m_instance = NULL;
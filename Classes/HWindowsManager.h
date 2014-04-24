//
//  HWindowsManager.h
//  Bomb
//
//  Created by wilford on 13-12-15.
//
//

#ifndef __Bomb__HWindowsManager__
#define __Bomb__HWindowsManager__

#include "HIWindow.h"

USING_NS_CC;

//
//Manage all the window show by HBaseWindows
//
class HWindowsManager{
public:
    static HWindowsManager* S();
    
    void pushWindow(HIWindow* window);
    
    void popWindow();
    
    void closeWindow(HIWindow* window);
    
    void closeAllWindows();
    
    bool hasWindowsShowed(){return m_windows->count()>0;}
    
	void update(float dt);

	void clearToClose();

    void updateWindows(float dt);

	void release(){

		CC_SAFE_DELETE(m_instance);
	}
    
    int getTopZOrder();
    
protected:
    //
    //constructor
    //
    HWindowsManager();
    
    //
    //destructor
    //
    ~HWindowsManager();
    
private:
    CCArray* m_windows;
	CCArray* m_toclose;
    static HWindowsManager* m_instance;
};

#endif /* defined(__Bomb__HWindowsManager__) */

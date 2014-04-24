//
//  Achievement.h
//  Bejeweled
//
//  Created by wilford on 14-1-16.
//
//

#ifndef __Bejeweled__Achievement__
#define __Bejeweled__Achievement__

#include "HCCWindow.h"
#include "UIScrollViewBar.h"



class Achievement : public HCCWindow{
public:
    WINDOW_SINGTON_SHOW(Achievement);
    virtual void update(float dt);
    
    void initTabs();
    void showTab(int id);
    
protected:
    virtual void startAnim();
    virtual void endAnim(){
        onCloseAnimOver(NULL);
    }
    
   
    
private:
    void onTabClicked(CCObject* sender);
    void onCloseClicked(CCObject* sender);
    static Achievement* instance;
    UIWidget* m_tab_containers[4];
};

#endif /* defined(__Bejeweled__Achievement__) */

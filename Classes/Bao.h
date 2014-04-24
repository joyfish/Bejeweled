//
//  Bao.h
//  Bejeweled
//
//  Created by wilford on 14-1-17.
//
//

#ifndef __Bejeweled__Bao__
#define __Bejeweled__Bao__

#include "HCCWindow.h"
#include "UIScrollViewBar.h"
#include "BaoInfo.h"



class Bao : public HCCWindow{
public:
    WINDOW_SINGTON_SHOW(Bao);
    
    void initTabs();
    void showTab(int id);
    
    
    void initItems(UIWidget* item,BAO_INFO* info);
    void enableIcon(UIWidget* container,bool enabed){
        CCArray* items =  container->getChildren();
        CCObject* obj;
        CCARRAY_FOREACH(items, obj){
            UIWidget* child = (UIWidget*)obj;
            UIWidget* icon = child->getChildByName("icon");
            if (icon) {
                icon->setTouchEnable(enabed);
            }
        }
    }
    
protected:
    virtual void startAnim();
    virtual void endAnim(){
        onCloseAnimOver(NULL);
    }
    
    
    
private:
    void onItemClick(CCObject* sender);
    void onTabClicked(CCObject* sender);
    void onCloseClicked(CCObject* sender);
    static Bao* instance;
    UIWidget* m_tab_containers[5];
};

#endif /* defined(__Bejeweled__Bao__) */

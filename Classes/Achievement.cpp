//
//  Achievement.cpp
//  Bejeweled
//
//  Created by wilford on 14-1-16.
//
//

#include "Achievement.h"

void Achievement::init(void *data){
    m_tips = CCUIHELPER->createWidgetFromJsonFile("Achievement.json");
    initTabs();
    showTab(0);
    HPersistence::S()->SaveToFile();
}

void Achievement::update(float dt){

}

void Achievement::initTabs(){
    for (int i=0; i<5; i++) {
        IntToStringFormat(_containerName, "tab_%d_container", i);
        UIWidget* container = m_tips->getChildByName(_containerName);
        m_tab_containers[i] = container;
        
        if (container) {
            for (int j=0; j<5; j++) {
                if (i==j) {
                    continue;
                }
                IntToStringFormat(_tabName, "tab_%d", j);
                UIWidget* tab = container->getChildByName(_tabName);
                if (tab) {
                    tab->setTouchEnable(true);
                    tab->addReleaseEvent(this, coco_releaseselector(Achievement::onTabClicked));
                    tab->setTag(j);
                }
            }
            UIScrollView* scroll_view = (UIScrollView*)container->getChildByName("ScrollView");
            CCArray* _items = CCArray::create();
            
            int count = G::g_achieve_infos->count();
            
            for (int j=0; j<count; j++) {
                ACHIEVE_INFO* info = (ACHIEVE_INFO*)G::g_achieve_infos->objectAtIndex(j);
                if (!info->isOpened) {
                    continue;
                }
                if (i>0) {
                    if(info->type!=i-1){
                        continue;
                    }
                }
                UIWidget* item = CCUIHELPER->createWidgetFromJsonFile("AchieveItem.json");
                IntToString(_itemName, (int)info->complete_time);
                item->setName(_itemName);
                
                scroll_view->addChild(item);
                _items->addObject(item);
                G::G_initAchievement_Item(info, item);
            }
            
            G::G_sortUIWidgetByName(_items, SORT_DESC);
            
            count = _items->count();
            G::G_orderUIWiddget(_items, ccp(300, (count-1)*175+86), 1, 0, -175);
            scroll_view->setInnerContainerSize(CCSizeMake(640, 175*count));
            scroll_view->setSize(CCSizeMake(640, 175*4));
            scroll_view->setTouchEnable(true);
            scroll_view->setDirection(SCROLLVIEW_DIR_VERTICAL);
            UIScrollViewBar* m_bar = UIScrollViewBar::create();
            CCPoint bar_pos = ccp(300,-440);
            container->addChild(m_bar);
            m_bar->setZOrder(2);
            m_bar->setBackgroundImage("common/scrollviewBar_bg1.png",680);
            m_bar->setForegroundImage("common/scrollviewBar_fore.png");
            m_bar->setPosition(ccp(bar_pos.x-container->getPosition().x, bar_pos.y));
            m_bar->attach(scroll_view, UISCROLLBAR_VERTICAL);
            m_bar->setRotation(-90);

            _items->release();
        }
    }
    
    CCObject* obj;
    CCARRAY_FOREACH(G::g_achieve_infos, obj){
        ACHIEVE_INFO* info = (ACHIEVE_INFO*)obj;
        if (info->is_complete) {
            if (info->isNew) {
                info->isNew = false;
                HPersistence::S()->SaveAchievement(info->id);
            }
        }
    }
}

void Achievement::showTab(int id){
    for (int i=0; i<5; i++) {
        if (m_tab_containers[i]) {
            m_tab_containers[i]->setVisible(false);
            UIScrollView* scroll_view = (UIScrollView*)m_tab_containers[i]->getChildByName("ScrollView");
            if (scroll_view) {
                if (i==id) {
                    scroll_view->setTouchEnable(true);
                }else
                    scroll_view->setTouchEnable(false);
            }
            for (int j=0; j<5; j++) {
                IntToStringFormat(_tabName, "tab_%d", j);
                UIWidget* tab =  m_tab_containers[i]->getChildByName(_tabName);
                if (tab) {
                    if (i==id) {
                        tab->setTouchEnable(true);
                    }else{
                        tab->setTouchEnable(false);
                    }
                }
            }

        }
    }
    m_tab_containers[id]->setVisible(true);
}

void Achievement::startAnim(){
    UIPanel* _panel = (UIPanel*)m_tips;
    _panel->setBackGroundColorOpacity(255);
    UIWidget* btn_close = m_tips->getChildByName("btn_close");
    btn_close->setTouchEnable(true);
    btn_close->setPosition(ccp(_pRight-45, _pTop-45));
    btn_close->addReleaseEvent(this, coco_releaseselector(Achievement::onCloseClicked));
    PopNode(btn_close, 0.1f);
}

void Achievement::onTabClicked(cocos2d::CCObject *sender){
    int tag = ((UIWidget*)sender)->getTag();
    showTab(tag);
}

void Achievement::onCloseClicked(CCObject* sender){
    closeWindow();
}

Achievement* Achievement::instance;
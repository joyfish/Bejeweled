//
//  Bao.cpp
//  Bejeweled
//
//  Created by wilford on 14-1-17.
//
//

#include "Bao.h"

void Bao::init(void *data){
    m_tips = CCUIHELPER->createWidgetFromJsonFile("Bao.json");
    UIWidget* bg = m_tips->getChildByName("bg");
    bg->setAnchorPoint(ccp(0.5f, 0.48f));
    initTabs();
//    for (int i=0; i<5; i++) {
//        if (m_tab_containers[i]) {
//            m_tab_containers[i]->removeAllChildren();
//        }
//    }

    showTab(0);
    HPersistence::S()->SaveToFile();
}


void Bao::initTabs(){
    for (int i=0; i<5; i++) {
        IntToStringFormat(_containerName, "tab_%d_container", i);
        UIWidget* container = m_tips->getChildByName(_containerName);
        m_tab_containers[i] = container;
        
        if (container) {
            for (int j=0; j<5; j++) {
                if (i == j) {
                    continue;
                }
                IntToStringFormat(_tabName, "tab_%d", j);
                UIWidget* tab = container->getChildByName(_tabName);
                if (tab) {
                    tab->setTag(j);
                    tab->setTouchEnable(true);
                    tab->addReleaseEvent(this, coco_releaseselector(Bao::onTabClicked));
                }
            }
           UIScrollView* scroll_view = (UIScrollView*)container->getChildByName("ScrollView");
//            CCArray* _items = CCArray::create();
//            
//
//            for (int j=0; j<MAX_BAO; j++) {
//                BAO_INFO* info = (BAO_INFO*)G::g_bao_infos->objectAtIndex(j);
//                if (!baos_opened[j]) {
//                    continue;
//                }
//                
//                if (i==1) {//关卡类型
//                    if (baos_type[j]!=BAO_FROM_STAGE) {
//                        continue;
//                    }
//                }else if(i==3){//其他类型
//                    if (baos_type[j]!=BAO_FROM_TREE&&baos_type[j]!=BAO_FROM_TURNTABLE) {
//                        continue;
//                    }
//                }else if(i==2){//洞穴
//                    if(baos_type[j]!=BAO_FROM_HOLE){
//                        continue;
//                    }
//                }else if(i==4){//海底
//                    if (baos_type[j]!=BAO_FROM_SEA) {
//                        continue;
//                    }
//                }
//                
//                
//                UIWidget* item = CCUIHELPER->createWidgetFromJsonFile("BaoItem.json");
//
//                initItems(item, info);
//                scroll_view->addChild(item);
//                _items->addObject(item);
// 
//            }
//            
//            int count = _items->count();
//            CCPoint start_pos;
//            if (count/5<4) {
//                start_pos = ccp(65, 4*150-50);
//            }else{
//                start_pos = ccp(65, count/5*150-50);
//            }
//
//            G::G_orderUIWiddget(_items, start_pos, 5, 120, -150);
//            scroll_view->setSize(CCSizeMake(640, 150*4));
//            scroll_view->setInnerContainerSize(CCSizeMake(640, count/5*150));
//            scroll_view->setTouchEnable(true);
//            scroll_view->setDirection(SCROLLVIEW_DIR_VERTICAL);
            UIScrollViewBar* m_bar = UIScrollViewBar::create();
            CCPoint bar_pos = ccp(305,-440);
            container->addChild(m_bar);
            m_bar->setZOrder(2);
            m_bar->setBackgroundImage("common/scrollviewBar_bg1.png",580);
            m_bar->setForegroundImage("common/scrollviewBar_fore.png");
            m_bar->setPosition(ccp(bar_pos.x-container->getPosition().x, bar_pos.y));
            m_bar->attach(scroll_view, UISCROLLBAR_VERTICAL);
            m_bar->setRotation(-90);
//
//            _items->release();
        }
    }
    CCObject* obj;
    CCARRAY_FOREACH(G::g_bao_infos, obj){
        BAO_INFO* info = (BAO_INFO*)obj;
        if (info->isGot) {
            if (info->isNew) {
                info->isNew = false;
                HPersistence::S()->SaveBao(info->id);
            }
        }
    }

}

void Bao::showTab(int id){
    //CCUIHELPER->purgeUIHelper();
    for (int i=0; i<5; i++) {
        if (m_tab_containers[i]) {
            m_tab_containers[i]->setVisible(false);
            UIScrollView* scroll_view = (UIScrollView*)m_tab_containers[i]->getChildByName("ScrollView");
            scroll_view->removeAllChildren();
            if (scroll_view) {
                if (i==id) {
                    scroll_view->setTouchEnable(true);
                    enableIcon(scroll_view, true);
                    CCArray* _items = CCArray::create();
                    
                    
                    for (int j=0; j<MAX_BAO; j++) {
                        BAO_INFO* info = (BAO_INFO*)G::g_bao_infos->objectAtIndex(j);
                        if (!baos_opened[j]) {
                            continue;
                        }
                        
                        if (i==1) {//关卡类型
                            if (baos_type[j]!=BAO_FROM_STAGE) {
                                continue;
                            }
                        }else if(i==3){//其他类型
                            if (baos_type[j]!=BAO_FROM_TREE&&baos_type[j]!=BAO_FROM_TURNTABLE) {
                                continue;
                            }
                        }else if(i==2){//洞穴
                            if(baos_type[j]!=BAO_FROM_HOLE){
                                continue;
                            }
                        }else if(i==4){//海底
                            if (baos_type[j]!=BAO_FROM_SEA) {
                                continue;
                            }
                        }
                        

                        //CCUIHELPER->createWidgetFromJsonFile("BaoItem.json");
                        UIWidget* item = CCUIHELPER->createWidgetFromJsonFile("BaoItem.json");
                        initItems(item, info);
                        scroll_view->addChild(item);
                        _items->addObject(item);

                    }
                    
                    int count = _items->count();
                    CCPoint start_pos;
                    if (count/5<4) {
                        start_pos = ccp(65, 4*150-50);
                    }else{
                        if (count%5 == 0) {
                            start_pos = ccp(65, count/5*150-50);
                        }else{
                            start_pos = ccp(65, (count/5+1)*150-50);
                        }
                       
                    }
                    
                    G::G_orderUIWiddget(_items, start_pos, 5, 120, -150);
                    scroll_view->setSize(CCSizeMake(640, 150*4));
                    if (count%5 == 0) {
                        scroll_view->setInnerContainerSize(CCSizeMake(640, count/5*150));
                    }else{
                        scroll_view->setInnerContainerSize(CCSizeMake(640, (count/5+1)*150));
                    }
                    scroll_view->setTouchEnable(true);
                    scroll_view->setDirection(SCROLLVIEW_DIR_VERTICAL);
                    
                    _items->release();
                }else{
                    scroll_view->setTouchEnable(false);
                    enableIcon(scroll_view, false);
                }
                
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

void Bao::initItems(cocos2d::extension::UIWidget *item, BAO_INFO *info){
    UIWidget* _new = item->getChildByName("new");
    UIImageView* _icon = (UIImageView*)item->getChildByName("icon");
    UILabelBMFont* _name = (UILabelBMFont*)item->getChildByName("name");
    CCDictionary* _strings = CCDictionary::createWithContentsOfFile("data/bao.plist");
    IntToStringFormat(_key, "bao_name_%d", info->id);
    CCString* _s_name = (CCString*)_strings->objectForKey(_key);
    _name->setText(_s_name->getCString());
    _new->setVisible(false);
    
    IntToStringFormat(_iconName, "bao/icon_%d.png", info->id);
    _icon->setTexture(_iconName);
    if(baos_type[info->id]!=BAO_FROM_TREE&&baos_type[info->id]!=BAO_FROM_TURNTABLE){
        _icon->setScale(1.2f);
    }
    
    if (!info->isGot) {
//        IntToStringFormat(_iconName, "bao/icon_%d_a.png", info->id);
//        _icon->setTexture(_iconName);
        _icon->setColor(ccc3(0, 0, 0));
    }else{
        _new->setVisible(info->isNew);
        _icon->setColor(ccc3(255, 255, 255));
//        IntToStringFormat(_iconName, "bao/icon_%d.png", info->id);
//        _icon->setTexture(_iconName);
    }
    
    _strings->release();
    
    _icon->setTouchEnable(true);
    _icon->addReleaseEvent(this, coco_releaseselector(Bao::onItemClick));
    _icon->setTag(info->id);
}

void Bao::startAnim(){
    UIPanel* _panel = (UIPanel*)m_tips;
    _panel->setColor(ccc3(104, 126, 255));
    _panel->setBackGroundColorOpacity(255);
    UIWidget* btn_close = m_tips->getChildByName("btn_close");
    btn_close->setTouchEnable(true);
    btn_close->setPosition(ccp(_pRight-45, _pTop-45));
    btn_close->addReleaseEvent(this, coco_releaseselector(Bao::onCloseClicked));
    PopNode(btn_close, 0.1f);
}

void Bao::onItemClick(cocos2d::CCObject *sender){
    int tag = ((UIWidget*)sender)->getTag();
    BaoInfo::show(m_layer,new BaoInfoParam(tag));
}

void Bao::onTabClicked(cocos2d::CCObject *sender){
    int tag = ((UIWidget*)sender)->getTag();
    showTab(tag);
}

void Bao::onCloseClicked(CCObject* sender){
        closeWindow();
}

Bao* Bao::instance;
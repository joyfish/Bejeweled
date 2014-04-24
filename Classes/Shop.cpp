//
//  Shop.cpp
//  Bejeweled
//
//  Created by wilford on 14-1-10.
//
//

#include "Shop.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "HJNI.h"
#endif

Shop* Shop::instance = NULL;

void Shop::init(void *data){
    m_tips = CCUIHELPER->createWidgetFromJsonFile("Shop.json");
    m_scroll_view = (UIScrollView*)m_tips->getChildByName("good_container");
    UIWidget* bg = m_tips->getChildByName("bg");
    m_coin = (UILabelBMFont*)m_tips->getChildByName("mCoin");
    m_bar = UIScrollViewBar::create();
    bg->addChild(m_bar);
    m_bar->setZOrder(2);
    m_bar->setBackgroundImage("common/scrollviewBar_bg1.png",500);
    m_bar->setForegroundImage("common/scrollviewBar_fore.png");
    m_bar->setPosition(ccp(260 , -330));
    m_bar->attach(m_scroll_view, UISCROLLBAR_VERTICAL);
    m_bar->setRotation(-90);
    m_items = CCArray::create();
    m_items->retain();
    resetItems();
    //m_items->release();
    m_last_maxPower = G::g_maxPower;
    m_last_th_hasbuyed = G::shop_th_has_buyed;
    m_last_ts_hasbuyed = G::shop_ts_has_buyed;
}

void Shop::update(float dt){
    HCCWindow::update(dt);
    if (G::g_maxPower == MAX_POWER) {
        if (m_last_maxPower != MAX_POWER) {
            resetItems();
            m_last_maxPower = MAX_POWER;
        }
    }
    if (G::shop_th_has_buyed) {
        if (!m_last_th_hasbuyed) {
            resetItems();
            m_last_th_hasbuyed = true;
        }
    }
    if (G::shop_ts_has_buyed) {
        if (!m_last_ts_hasbuyed) {
            resetItems();
            m_last_ts_hasbuyed = true;
        }
    }
    IntToString(_coin, G::G_getCoin());
    m_coin->setText(_coin);
}

void Shop::resetItems(){
    G::G_removeAllUIWidgets(m_items);
    
    CCDictionary* _strings = CCDictionary::createWithContentsOfFile("data/shop_des.plist");
    
    int lb_count = 0;
    
    for (int i=0; i<MAX_SHOP_ITEM_COUNT; i++) {
        if (G::g_maxPower==MAX_POWER&&shop_item_type[i]==9) {
            continue;
        }
        if (G::shop_th_has_buyed&&shop_item_type[i] ==10) {
            continue;
        }
        if (G::shop_ts_has_buyed&&shop_item_type[i] ==11) {
            continue;
        }
        
        UIWidget* item ;
        if (shop_item_type[i] == 10) {
            item = CCUIHELPER->createWidgetFromJsonFile("ShopItem_th.json");
            lb_count++;
        }else if(shop_item_type[i] == 11){
            item = CCUIHELPER->createWidgetFromJsonFile("ShopItem_ts.json");
            lb_count++;
        }else{
            item = CCUIHELPER->createWidgetFromJsonFile("ShopItem.json");
        }

        m_scroll_view->addChild(item);
        m_items->addObject(item);
        UIWidget* btn_buy;
        btn_buy = item->getChildByName("btn_buy");
        UILabelAtlas* mCost = (UILabelAtlas*)btn_buy->getChildByName("cost");
        IntToStringFormat(_cost, ":%d", G::shop_item_prices[i]);
        mCost->setStringValue(_cost);
        btn_buy->setVisible(true);
        btn_buy->addReleaseEvent(this, coco_releaseselector(Shop::onItemBuy));
        btn_buy->setTag(i);
        btn_buy->setTouchEnable(true);
        
        UILabelBMFont* l_name = (UILabelBMFont*)item->getChildByName("name");
        UILabelBMFont* l_des = (UILabelBMFont*)item->getChildByName("des");
        UIImageView* icon_img = (UIImageView*)item->getChildByName("icon");
        UIImageView* icon_tips = (UIImageView*)item->getChildByName("tips");
        
        if(shop_item_type[i] != 10&&shop_item_type[i] !=11){
        
            IntToStringFormat(_key_icon, "icon_%d", i);
            IntToStringFormat(_key_name, "name_%d", i);
            IntToStringFormat(_key_des, "des_%d", i);
            CCString* _s_icon = (CCString*)_strings->objectForKey(_key_icon);
            CCString* _s_name = (CCString*)_strings->objectForKey(_key_name);
            CCString* _s_des = (CCString*)_strings->objectForKey(_key_des);
            l_name -> setText(_s_name->getCString());
            l_des ->setText(_s_des->getCString());
            icon_img -> setTexture(_s_icon->getCString());
        }
        
        if (shop_item_tips[i]>0) {
            icon_tips->setVisible(true);
            IntToStringFormat(_tipsName, "shop/leftTop_%d.png", shop_item_tips[i]-1);
            icon_tips->setTexture(_tipsName);
        }
    }
    
    
    _strings->release();

    int count = m_items->count();
    CCObject* obj;
    int id = 0;
    int lb_id = 0;
    CCPoint start_pos = ccp(20,150*(count-lb_count-1)+(lb_count)*350);
    CCARRAY_FOREACH(m_items, obj){
        UIWidget* u = (UIWidget*)obj;
        UIImageView* item_bg = (UIImageView*)u->getChildByName("item_bg");
        if (item_bg->getSize().height>200) {
            CCPoint pos;
            pos.x=20;
            if (lb_id == 0) {
                pos.y = 100;
            }else{
                pos.y = 100 + lb_id*350 ;
            }
            u->setPosition(pos);
            lb_id++;
            continue;
        }
        CCPoint pos;
        pos.x=20;
        pos.y=start_pos.y+id*(-150);
        u->setPosition(pos);
        id++;
    }

    //G::G_orderUIWiddget(m_items, ccp(20, (count-1)*150), 1, 0, -150);
    m_scroll_view->setInnerContainerSize(CCSizeMake(600, 150*(count-lb_count)+(lb_count)*350+5));
    m_scroll_view->setSize(CCSizeMake(600, 150*4+5));
    //Layout* inner = m_scroll_view->getInnerContainer();
    //inner->setPosition(ccp(inner->getPosition().x, -150*(count-1)));
}

void Shop::startAnim(){
    HCCWindow::startAnim();
    UIWidget* btn_close = m_tips->getChildByName("btn_close");
    PopNode(btn_close,0.4f);
    btn_close->addReleaseEvent(this, coco_releaseselector(Shop::onClose));
}

void Shop::onItemBuy(cocos2d::CCObject *sender){
    G::G_playEffect(RES_MUSIC_NORMAL_CLICK);
    UIWidget* u = (UIWidget*)sender;
    int id = u->getTag();
    if (shop_item_type[id]==9&&G::g_maxPower==MAX_POWER) {
        NormalTips::show(m_layer,new NormalTipsParam(0));
        return;
    }else if(shop_item_type[id] == 1 && G::G_getPower()==G::g_maxPower){
        NormalTips::show(m_layer,new NormalTipsParam(1));
        return;
    }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    IntToStringFormat(_pay, "k%d", id);
    IntToStringFormat(_des, "v%d", id);
    HJNI::Pay(_pay,_des);
    switch (id) {
        case 0://金币29
            HJNI::callumeng("event15");
            break;
        case 1://金币10元
            HJNI::callumeng("event14");
            break;
        case 2://金币5元
            HJNI::callumeng("event13");
            break;
        case 3://金币2元
            HJNI::callumeng("event12");
            break;
        case 4://挑战卷5元
            HJNI::callumeng("event22");
            break;
        case 5://挑战卷2元
            HJNI::callumeng("event21");
            break;
        case 6://精力值
            HJNI::callumeng("event8");
            break;
        case 7://拓展卷
            HJNI::callumeng("event10");
            break;
        case 8://特惠礼包
            HJNI::callumeng("event19");
            break;
        case 9://天神礼包
            HJNI::callumeng("event20");
            break;
            
        default:
            break;
    }
#else
    CCArray* rewards = CCArray::create();
    if (shop_item_type[id]==10) {
        rewards->addObject(new RewardInfo(0,11200));
       // rewards->addObject(new RewardInfo(2,1));
       // rewards->addObject(new RewardInfo(3,1));
        rewards->addObject(new RewardInfo(4,1));
       // rewards->addObject(new RewardInfo(5,1));
        rewards->addObject(new RewardInfo(6,1));
        //rewards->addObject(new RewardInfo(7,1));
        G::shop_th_has_buyed = true;
        HPersistence::S()->SaveToFile();
    }else if(shop_item_type[id] == 11){
        rewards->addObject(new RewardInfo(0,24500));
        rewards->addObject(new RewardInfo(2,2));
        rewards->addObject(new RewardInfo(3,2));
        rewards->addObject(new RewardInfo(4,2));
        rewards->addObject(new RewardInfo(5,2));
        rewards->addObject(new RewardInfo(6,2));
        rewards->addObject(new RewardInfo(7,2));
        G::shop_ts_has_buyed = true;
        HPersistence::S()->SaveToFile();
    }else{
        rewards->addObject(new RewardInfo(shop_item_type[id],shop_item_getCount[id]));
    }
    ShopBuyed::show(m_layer,new RewardsParams(rewards));
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    char key[30];
    sprintf(key,"shop%dButton",id+1);
    HJNI::callumengs(key,"tool_use",NULL);
#endif


    
    G::g_last_buytype = BUY_TYPE_NORMAL;
    G::g_last_buyid = id;
}

void Shop::onClose(cocos2d::CCObject *sender){
     G::G_playEffect(RES_MUSIC_NORMAL_CLICK);
    closeWindow();
}
//
//  HJNI_CALLBACK.h
//  Bejeweled
//
//  Created by wilford on 14-1-19.
//
//

#ifndef Bejeweled_HJNI_CALLBACK_h
#define Bejeweled_HJNI_CALLBACK_h

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#endif

#include "cocos2d.h"
#include "ShopBuyed.h"
#include "HJNI.h"

USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
extern "C"
{
	void Java_com_happygod_monster_Bomb_getpay(JNIEnv *env, jobject obj,jint successed)
	{
		if(successed == 1){
            CCLOG("buyed success ! ");
            CCLOG("%d",G::g_last_buytype);
            CCLOG("%d",G::g_last_buyid);
            CCArray* rewards = CCArray::create();
            if (G::g_last_buytype == BUY_TYPE_NORMAL) {
  //              CCArray* rewards = CCArray::create();
                if (shop_item_type[G::g_last_buyid]==10) {
                    rewards->addObject(new RewardInfo(0,11200));
                    rewards->addObject(new RewardInfo(2,1));
                    rewards->addObject(new RewardInfo(3,1));
                    rewards->addObject(new RewardInfo(4,1));
                    rewards->addObject(new RewardInfo(5,1));
                    rewards->addObject(new RewardInfo(6,1));
                    rewards->addObject(new RewardInfo(7,1));
                    G::shop_th_has_buyed = true;
                    HPersistence::S()->SaveToFile();
                }else if(shop_item_type[G::g_last_buyid] == 11){
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
                    rewards->addObject(new RewardInfo(shop_item_type[G::g_last_buyid],shop_item_getCount[G::g_last_buyid]));
                }
//                ShopBuyed::show(m_layer,new RewardsParams(rewards));
//                rewards->addObject(new RewardInfo(shop_item_type[G::g_last_buyid],shop_item_getCount[G::g_last_buyid]));
                CCLOG("shop %d %d",shop_item_type[G::g_last_buyid],shop_item_getCount[G::g_last_buyid]);
                
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
                IntToStringFormat(_item, "shop%d", G::g_last_buyid+1);
                HJNI::umengBuy(_item,1,G::shop_item_prices[G::g_last_buyid]);
#endif
            }else if(G::g_last_buytype == BUY_TYPE_QUICK){
                rewards->addObject(new RewardInfo(quick_buy_type[G::g_last_buyid],quick_buy_getCount[G::g_last_buyid]));
                 CCLOG("quick %d %d",quick_buy_type[G::g_last_buyid],quick_buy_getCount[G::g_last_buyid]);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
                IntToStringFormat(_item, "fast%d", G::g_last_buyid+1);
                HJNI::umengBuy(_item,1,G::quick_buy_prices[G::g_last_buyid]);
#endif
            }
           // CCLOG("rewardscount %d",rewards->count() );

            ShopBuyed::show(((HScene*)G::g_currentScene)->getLayer(),new RewardsParams(rewards));
            HPersistence::S()->SaveToFile();
		}
	}
    
    void Java_com_happygod_monster_Bomb_OnRockShared(JNIEnv *env, jobject obj)
	{
    }
    
    void Java_com_happygod_monster_Bomb_OnSharedOver(JNIEnv *env, jobject obj,jint successed)
	{
//        if (successed == 1) {
//            CCLOG("share success");
//            switch (GlobaData::shared()->share_reward_id) {
//                case 0:
//                    GlobaData::shared()->GetRward(1,10);
//                    break;
//                case 1:
//                    GlobaData::shared()->GetRward(0,2000);
//                    break;
//                case 2:
//                    GlobaData::shared()->GetRward(2,1);
//                    GlobaData::shared()->GetRward(3,1);
//                    GlobaData::shared()->GetRward(4,1);
//                    GlobaData::shared()->GetRward(5,1);
//                    GlobaData::shared()->GetRward(6,1);
//                    GlobaData::shared()->GetRward(7,1);
//                    break;
//                default:
//                    break;
//            }
//            MainScene::shared()->resetPower();
//            MainScene::shared()->resetCoin();
//            GlobaData::shared()->share_reward_got[GlobaData::shared()->share_reward_id] = true;
//            GlobaData::shared()->saveToFile();
//            ShareWindow::shared()->reset();
//            MainScene::shared()->SHOW_NORMAL_TIPS(6);
//        }else{
//            CCLOG("share fail");
//            MainScene::shared()->SHOW_NORMAL_TIPS(7);
//        }
//        
//        CCDirector::sharedDirector()->resume();
//        
//        CCDirector::sharedDirector()->startAnimation();
//        
//        SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    }
    
    void JNICALL Java_com_happygod_monster_Bomb_handleOnWindowFocusChanged( JNIEnv * env, jclass jClass , jboolean hasFocus )
    
    {
        
        if (hasFocus)
            
        {
            
            SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
            
            SimpleAudioEngine::sharedEngine()->resumeAllEffects();
            
        }
        
        else
            
        {
            
            SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
            
            SimpleAudioEngine::sharedEngine()->pauseAllEffects();
            
        }
        
    }
}
#endif


#endif

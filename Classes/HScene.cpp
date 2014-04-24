#include "HScene.h"




void LoadingScene::onEnter(){	
	CCScene::onEnter();
	unscheduleAllSelectors();

	if(list->count() <= 0){
        CCDirector::sharedDirector()->replaceScene(nextScene);
        G::g_currentScene = nextScene;
        nextScene->release();
        return;
	}
	
	MainLayer = UILayer::create();
	this->addChild(MainLayer);
    UIWidget* loading = CCUIHELPER->createWidgetFromJsonFile("Loading.json");
	MainLayer->addWidget(loading);
    
    CCLOG("startLoadingAnim");
    
//    for (int i=0; i<6; i++) {
//        IntToStringFormat(_gemName, "gem_%d", i);
//        UIWidget* gem = loading->getChildByName(_gemName);
//        gem->setScale(1);
//        gem->setPosition(ccp(-175+70*i, 40));
//        if (i%2 == 0) {
//            gem->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(0.3f,ccp(0,30)),CCMoveBy::create(0.25f, ccp(0, -30)),CCDelayTime::create(0.6f), NULL)));
//        }else{
//            gem->runAction(CCRepeatForever::create(CCSequence::create(CCDelayTime::create(0.6f), CCMoveBy::create(0.3f,ccp(0,30)),CCMoveBy::create(0.25f, ccp(0, -30)),NULL)));
//        }
//    }
    UIWidget* top = loading->getChildByName("top");
    UIWidget* load = loading->getChildByName("loading");
    top->setPosition(ccp(_pCenter.x, _pTop));
    load->setPosition(_pCenter);
    
    UIWidget* a = load->getChildByName("a");
    a->runAction(CCRepeatForever::create(CCRotateBy::create(7, -360)));
    

    CCLOG("endLoadingAnim");
    
	for(unsigned int i=0;i<list->count();i++){
	CCString* str = (CCString*)(list->objectAtIndex(i));
	CCTextureCache::sharedTextureCache()->addImageAsync(str->getCString(),this,callfuncO_selector(LoadingScene::OnLoadOver));
	}
    CCLOG("endAddData");
    
    if (!G::g_has_first_saved) {
        HPersistence::S()->AsynchSaveToFile();
        // HPersistence::S()->SaveToFile();
    }
    
    scheduleUpdate();
   
}


void LoadingScene::onExit(){
	CCScene::onExit();
	CCObject* obj;
	CCARRAY_FOREACH(list,obj){
		obj->release();
	}
	list->release();
}

void LoadingScene::Load(HScene* scene){
	CCDirector::sharedDirector()->getTouchDispatcher()->removeAllDelegates();
	//SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	//SimpleAudioEngine::sharedEngine()->stopAllEffects();
	LoadingScene* loading = LoadingScene::create();
	
	CCDirector* director = CCDirector::sharedDirector();
   	
	scene->loadResource();
	loading->setList(scene->getTextureNames());
	loading->setNextScene(scene);

	if(G::g_currentScene==NULL){
		director->runWithScene(loading);
	}else{
		director->replaceScene(loading);
	}
    G::g_currentScene = loading;
}

void LoadingScene::setList(CCArray* list){
    this->list = NULL;
	this->list = list;
	loaded = 0;
	total = list->count();
	CCLOG(" total %d",total);
}

void LoadingScene::OnLoadOver(CCObject* object){
    
	if(loaded<total){
		loaded++;
	}

	CCLOG("Loading:%d/%d",loaded,total);

	}
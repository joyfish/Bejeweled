#ifndef HSCENE
#define HSCENE

#include "cocos-ext.h"
#include "HTools.h"
#include "HDefine.h"
#include "AutoSceneSize.h"
#include "HWindowsManager.h"
#include "SimpleAudioEngine.h"
#include "HSelectors.h"
#include "HPersistence.h"
#include "HGloba.h"

USING_NS_CC_EXT;
using namespace CocosDenshion;

class HScene : public cocos2d::CCScene{
public:
    HScene()
    :m_scenechangeListener(NULL)
    ,m_scenechangeSelector(NULL)
    ,m_data(NULL)
    ,resourceList(NULL)
    {}
    
    virtual void onEnter(){
        CCScene::onEnter();
        scheduleUpdate();
        m_layer = UILayer::create();
        m_layer->setZOrder(50);
        this->addChild(m_layer);
    }

	virtual void onExit(){
		CCScene::onExit();
		ReleaseResource();
	}
    
    virtual void update(float dt){
        CCScene::update(dt);
        if (HWindowsManager::S()) {
            HWindowsManager::S()->update(dt);
        }
        G::g_m_played_effects.clear();
    }

	void releaseTexture(const char* fileName){
		CCTextureCache::sharedTextureCache()->removeTextureForKey(fileName);
	}

	CCArray* getTextureNames(){
		return resourceList;
	}

	void addTextureName(const char* fileName){
		CCString* str = new CCString(fileName);
		resourceList->addObject(str);
	}

	virtual void loadResource(){resourceList = new CCArray();}
	virtual void ReleaseResource(){}

    void addSceneChangeEvent(CCObject* target,SEL_SCENECHANGE selector){
        m_scenechangeListener = target;
        m_scenechangeSelector = selector;
    }
    
    void changeScene(M_SCENE m_scene,void* data = NULL){
        if (m_scenechangeListener&&m_scenechangeSelector) {
            (m_scenechangeListener->*m_scenechangeSelector)(m_scene,data);
        }
    }
    
    void setData(void* data){
        m_data = data;
    }
    
    UILayer* getLayer(){
        return m_layer;
    }
    
protected:
    UILayer* m_layer;
    
private:
    void* m_data;
	CCArray* resourceList;
    CCObject* m_scenechangeListener;
    SEL_SCENECHANGE m_scenechangeSelector;
};

class LoadingScene : public cocos2d::CCScene{
public:
	virtual void onEnter();
	virtual void onExit();
	CREATE_FUNC(LoadingScene);

    virtual void update(float dt){
        HPersistence::S()->update(dt);
        //CCLOG("is_in_save %d", HPersistence::S()->is_in_save);
        if(loaded == total&&!HPersistence::S()->is_in_save){
            loaded = -1;
            CCDirector::sharedDirector()->replaceScene(nextScene);
            G::g_currentScene = nextScene;
            nextScene->release();
        }

    }
    
	static void Load(HScene* scene);

	void setList(CCArray* list);

	void setNextScene(CCScene* nextScene){
		this->nextScene = nextScene;
		this->nextScene->retain();
	}

private:
	void OnLoadOver(CCObject* object);
	CCScene* nextScene;
	UILayer* MainLayer;
	CCArray* list;
	int loaded;
	int total;
};

#endif
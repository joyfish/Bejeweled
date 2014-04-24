#include "AppDelegate.h"
//#include "HTools.h"
#include "HJNI_CALLBACK.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
    AutoSceneSize::S()->release();
    HWindowsManager::S()->release();
    HSceneManager::S()->release();
    HPersistence::S()->release();
    DictionaryHelper::shareHelper()->purgeDictionaryHelper();
    CCSGUIReader::shareReader()->purgeCCSGUIReader();
    CCUIHELPER->purgeUIHelper();
    ActionManager::shareManager()->purgeActionManager();
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    
    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
   // pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    AutoSceneSize::S()->setVirtualScreenWidth(640);
    
    CCFileUtils::sharedFileUtils()->addSearchPath("ccs");
    CCFileUtils::sharedFileUtils()->addSearchPath("game");
    CCFileUtils::sharedFileUtils()->addSearchPath("sounds");
    
    t_startRandom();
    
    G::G_loadConfig();
    HPersistence::S()->LoadGameData();
    
   HSceneManager::S()->changeScene(M_SCENE_LOGO, NULL);
   // HSceneManager::S()->changeScene(M_SCENE_MENU, NULL);
    

    return true;
}


// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();
    //SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();
    //SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

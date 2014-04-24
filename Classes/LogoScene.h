//
//  LogoScene.h
//  Bejeweled
//
//  Created by wilford on 14-1-3.
//
//

#ifndef __Bejeweled__LogoScene__
#define __Bejeweled__LogoScene__

#include "HTools.h"
#include "HScene.h"
#include "HoleModeShow.h"
#include "HoleModeResult.h"


class LogoScene:public HScene{
public:
    CREATE_FUNC(LogoScene);
    
	virtual void onEnter();
    
    virtual void onExit(){
        HScene::onExit();
        stars->removeAllObjects();
        CC_SAFE_DELETE(stars);
    }
    
    virtual void loadResource();
	virtual void ReleaseResource();
    
    void openMenu(float dt){
        changeScene(M_SCENE_MENU);
    }
    
    void PLAY_STAR(float t);
    
private:
    CCArray* stars;
};

#endif /* defined(__Bejeweled__LogoScene__) */

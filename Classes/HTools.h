//
//  HTools.h
//  Bejeweled
//
//  Created by wilford on 14-1-3.
//
//

#ifndef Bejeweled_HTools_h
#define Bejeweled_HTools_h

#include "cocos2d.h"

USING_NS_CC;

static void t_startRandom(){
    srand(time(NULL));
}

static int t_getRandom(int max){
    int result = floor(CCRANDOM_0_1()*max);
    if(result >= max)
        result = 0;
    return result;
}


#endif

//
//  HJNI.h
//  Bejeweled
//
//  Created by wilford on 14-1-6.
//
//

#ifndef Bejeweled_HJNI_h
#define Bejeweled_HJNI_h

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include <jni.h>

#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
class HJNI{
public:
static void Pay(const char* str,const char* des){

    CCDictionary *strings = CCDictionary::createWithContentsOfFile("a.plist");
    const char *key = ((CCString*)strings->objectForKey(str))->m_sString.c_str();
    const char *value = ((CCString*)strings->objectForKey(des))->m_sString.c_str();
    
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t,
                                       "com/happygod/monster/Bomb",
                                       "paymsg",
                                       "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID,
                                    t.env->NewStringUTF(key),t.env->NewStringUTF(value),t.env->NewStringUTF(value));
		
    }
    //strings->release();
}

static void callumeng(const char* eventStr){
    JniMethodInfo t;
    CCLOG("umeng %s",eventStr);
    if (JniHelper::getStaticMethodInfo(t,
                                       "com/happygod/monster/Bomb",
                                       "callumeng",
                                       "(Ljava/lang/String;)V"))
    {
		CCLOG("umeng");
		t.env->CallStaticVoidMethod(t.classID, t.methodID,
                                    t.env->NewStringUTF(eventStr));
    }
}

static void callumengs(const char* params,...){
    va_list ap;
    va_start(ap,params);
    const char* key= params;
    char* stringArray[10];
    int len = 0;
    char* tmp;
    while (true) {
        tmp  = va_arg(ap, char*);
        if (tmp==NULL) {
            break;
        }
        stringArray[len++]=tmp;
    }
    va_end(ap);
    
    JniMethodInfo t;
    
    if (JniHelper::getStaticMethodInfo(t,
                                       "com/happygod/monster/Bomb",
                                       "callumeng",
                                       "(Ljava/lang/String;[Ljava/lang/String;)V"))
    {
        jobjectArray result;
        result = t.env->NewObjectArray(len,t.env->FindClass("java/lang/String"),NULL);
        for (int i=0; i<len; i++) {
            jstring dom = t.env->NewStringUTF(stringArray[i]);
            t.env->SetObjectArrayElement(result, i, dom);
            t.env->DeleteLocalRef(dom);
        }
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID,
                                    t.env->NewStringUTF(key),result);
    }
}

    static void umengstartLevel(const char* level){
        JniMethodInfo t;
        CCLOG("umeng_startLevel %s",level);
        if (JniHelper::getStaticMethodInfo(t,
                                           "com/happygod/monster/Bomb",
                                           "umengstartLevel",
                                           "(Ljava/lang/String;)V"))
        {
            CCLOG("umeng");
            t.env->CallStaticVoidMethod(t.classID, t.methodID,
                                        t.env->NewStringUTF(level));
        }
    }
    
    static void umengfinishLevel(const char* level){
        JniMethodInfo t;
        CCLOG("umeng_finishLevel %s",level);
        if (JniHelper::getStaticMethodInfo(t,
                                           "com/happygod/monster/Bomb",
                                           "umengfinishLevel",
                                           "(Ljava/lang/String;)V"))
        {
            CCLOG("umeng");
            t.env->CallStaticVoidMethod(t.classID, t.methodID,
                                        t.env->NewStringUTF(level));
        }
    }

    
    static void umengfailLevel(const char* level){
        JniMethodInfo t;
        CCLOG("umeng_failLevel %s",level);
        if (JniHelper::getStaticMethodInfo(t,
                                           "com/happygod/monster/Bomb",
                                           "umengfailLevel",
                                           "(Ljava/lang/String;)V"))
        {
            CCLOG("umeng");
            t.env->CallStaticVoidMethod(t.classID, t.methodID,
                                        t.env->NewStringUTF(level));
        }
    }
    
    static void umengBuy(const char* item,jint num,jint price){
        JniMethodInfo t;
        CCLOG("umeng_buy %s",item);
        if (JniHelper::getStaticMethodInfo(t,
                                           "com/happygod/monster/Bomb",
                                           "umengBuy",
                                           "(Ljava/lang/String;II)V"))
        {
            CCLOG("umeng");
            t.env->CallStaticVoidMethod(t.classID, t.methodID,
                                        t.env->NewStringUTF(item),num,price);
        }
    }



static void doShare(jint dialog,jint img,jint shared_target,jint reward_id){
    //GlobaData::shared()->share_reward_id = reward_id;
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t,"com/happygod/monster/Bomb","doShare","(III)V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID,dialog,img,shared_target);
    }
}
};
#endif


#endif

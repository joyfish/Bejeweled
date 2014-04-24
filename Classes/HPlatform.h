//
//  HPlatform.h
//  Bejeweled
//
//  Created by wilford on 14-1-6.
//
//

#ifndef Bejeweled_HPlatform_h
#define Bejeweled_HPlatform_h

//弹出通用窗口声明
#define WINDOW_SHOW(__T__) \
static __T__* show(UILayer* layer,void* data=NULL)\
{ \
__T__* instance = new __T__(); \
instance -> m_layer = layer;\
instance->init(data);\
instance->HCCWindow::show();\
return instance;\
}\
void init(void* data);\

//弹出单列窗口声明
#define WINDOW_SINGTON_SHOW(__T__) \
static __T__* show(UILayer* layer,void* data=NULL) \
{ \
if(instance == NULL){\
instance = new __T__(); \
instance -> m_layer = layer;\
instance->init(data);\
instance->HCCWindow::show();\
}\
return instance;\
}\
\
virtual void close(){\
HCCWindow::close();\
instance = NULL;\
}\
static __T__* S(){return instance;}\
\
void init(void* data);

#endif

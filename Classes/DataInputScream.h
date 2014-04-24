//
//  DataInputScream.h
//  Bejeweled
//
//  Created by wilford on 14-1-11.
//
//

#ifndef __Bejeweled__DataInputScream__
#define __Bejeweled__DataInputScream__

#include "cocos2d.h"

USING_NS_CC;

class DataInputStream
{
public:
    
	DataInputStream(unsigned char *p,bool freeBuf=false){
		posbuf=buf=p;
		pos=0;
		needFreeBuf=freeBuf;
	}
    
	~DataInputStream(){
		if (needFreeBuf) delete buf;
	}
    
	static DataInputStream* loadFileWithPath(const char* path){
		std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(path);
		unsigned char* pBuffer = NULL;
		unsigned long bufferSize = 0;
		pBuffer = CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(),"rb",&bufferSize);
		return new DataInputStream(pBuffer,true);
	}
    
	unsigned char readUChar(){
		unsigned char i=*posbuf;
		posbuf++;
		pos++;
		return i;
	}
	char readChar(){
		char c = (char)readUChar();
		return c;
	}
    
	int readInt(){
		int i=(readChar()<<24);
		i+=(readUChar()<<16);
		i+=(readUChar()<<8);
		i+=readUChar();
		return i;
	}
    
	short readShort(){
		short i=(readChar()<<8);
		i+=readUChar();
		return i;
	}
    
	void skip(int length){
		pos+=length;
		posbuf+=length;
	}
private:
	bool needFreeBuf;
	unsigned char *buf,*posbuf;
	int pos,count;
};


#endif /* defined(__Bejeweled__DataInputScream__) */

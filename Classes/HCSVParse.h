//
//  HCSVParse.h
//  Bejeweled
//
//  Created by wilford on 14-1-24.
//
//

#ifndef __Bejeweled__HCSVParse__
#define __Bejeweled__HCSVParse__

#include <iostream>
#include "cocos2d.h"
#include <vector>
using namespace std;
USING_NS_CC;

class HCSVParse
{
public:
    //    CCSVParse(void);
    ~HCSVParse(void);
    HCSVParse(istream& fin=cin, string sep=","):
    fieldsep(sep),
    cols(0)
    {
        
    }
    
    //用以存储数据
    std::vector<std::vector<std::string> > data;
    bool openFile(const char* fileName);
    const char* getData(unsigned int rows, unsigned int cols);
    int findColsData(int cols, const char* value);
    
    inline int getCols(){return cols;}
    inline int getRows(){return data.size();}
    
private:
    string        fieldsep;
    int            cols;
    
    void StringSplit(const string& str, vector<string>& tokens, const char& delimiters);
    void split(vector<string>& field, string line);
    int advplain(const string& line, string& fld, int);
    int advquoted(const string& line, string& fld, int);
    
    
};

#endif /* defined(__Bejeweled__HCSVParse__) */

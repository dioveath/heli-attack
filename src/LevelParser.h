// LevelParser.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef LEVELPARSER_H
#define LEVELPARSER_H 1


#include <iostream>
#include <vector>
#include "tinyxml.h"

struct Level {
    std::string m_filename;
    int m_id;
};

class LevelParser {

 public:
    static LevelParser* Instance() {
	if(!s_pInstance)
	    s_pInstance = new LevelParser();
	return s_pInstance;
    }
    bool ParseLevel(std::string filename, std::vector<Level>* pLevels, int* currentLevelID);
    bool writeCurrentLevel(std::string fileName, int levelID);

 private:
    static LevelParser* s_pInstance;

};


typedef LevelParser TheLevelParser;




#endif // LEVELPARSER_H
//////////////////////////////////////////////////////////////////////
// $Log:$
//

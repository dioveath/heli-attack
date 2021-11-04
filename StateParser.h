// StateParser.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef STATEPARSER_H
#define STATEPARSER_H 1

#include <string>
#include <vector>
#include "tinyxml.h"


class GameObject;


class StateParser {

 public:
    static StateParser* Instance() {
	if(!s_pInstance)
	    s_pInstance = new StateParser();
	return s_pInstance;
    }

    bool parseState(const char* stateFile, std::string stateID,
		     std::vector<GameObject*>* pObjects,
		     std::vector<std::string>* pTextureIDs);

 private:
    void parseObjects(TiXmlElement* pObjectRoot,
		      std::vector<GameObject*>* pObjects);
    void parseTextures(TiXmlElement* pTextureRoot,
		       std::vector<std::string>* pTextureIDs);

    static StateParser* s_pInstance;
    


};


typedef StateParser TheStateParser;



#endif // STATEPARSER_H
//////////////////////////////////////////////////////////////////////
// $Log:$
//

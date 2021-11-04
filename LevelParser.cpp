/* 

   LevelParser.cpp

   Author: Saroj Rai @ Charicha 
   Created On: Wednesday, 15 August 2018.

*/

#include "LevelParser.h"

// $Log:$ //
//


LevelParser* LevelParser::s_pInstance = 0;


bool LevelParser::ParseLevel(std::string fileName,
			     std::vector<Level>* pLevels,
			     int* currentLevelID){

    TiXmlDocument xmlDoc;

    if(!xmlDoc.LoadFile(fileName)){
	std::cerr << xmlDoc.ErrorDesc() << " Loading error!\n";
	return false;
    }

    TiXmlElement* pRoot = xmlDoc.RootElement();

    for(TiXmlElement* e = pRoot->FirstChildElement();
	e != 0; e = e->NextSiblingElement()){

	if(e->Value() == std::string("level")){
	    Level level;
	    level.m_filename = e->Attribute("filename");
	    e->Attribute("id", &level.m_id);
	    pLevels->push_back(level);
	} else if(e->Value() == std::string("currentlevel")){
	    e->Attribute("id", currentLevelID);
	}
    }

    return true;
}


bool LevelParser::writeCurrentLevel(std::string fileName, int levelID){

    TiXmlDocument xmlDoc;

    if(!xmlDoc.LoadFile(fileName)){
	std::cerr << xmlDoc.ErrorDesc() << " Loading error!\n";
	return false;
    }

    TiXmlElement* pRoot = xmlDoc.RootElement();
    for(TiXmlElement* e = pRoot->FirstChildElement();
	e != 0; e = e->NextSiblingElement()){

	std::cout << "e->Value(): " << e->Value() << std::endl;

	if(e->Value() == std::string("currentlevel")){
	    // e->Attribute("id", currentLevelID);
	    e->SetAttribute("id", levelID);

	    int check;
	    e->Attribute("id", &check);
	    std::cout << "changed to " << check << std::endl;
	    return xmlDoc.SaveFile();
	}
    }

    return true;
}

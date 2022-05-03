/* 

   StateParser.cpp

   Author: Saroj Rai @ Charicha 
   Created On: Wednesday,  1 August 2018.

*/

#include <iostream>
#include "StateParser.h"

#include "Game.h"
#include "TextureManager.h"
#include "GameObjectFactory.h"


// $Log:$ //
//


StateParser* StateParser::s_pInstance = 0;


bool StateParser::parseState(const char* stateFile, std::string stateID,
			     std::vector<GameObject*>* pObjects,
			     std::vector<std::string>* pTextureIDs){
    TiXmlDocument xmlDoc;

    if(!xmlDoc.LoadFile(stateFile)){
	std::cerr << xmlDoc.ErrorDesc() << " Loading error!\n";
	return false;
    }

    TiXmlElement* pRoot = xmlDoc.RootElement();
    TiXmlElement* pStateRoot = 0;

    for(TiXmlElement* e = pRoot->FirstChildElement();
	e != 0; e = e->NextSiblingElement()){
	if(e->Value() == stateID)
	    {
		pStateRoot = e;
	    }
    }

    if(!pStateRoot) std::cout << "There is no element, '" << stateID << "'..!\n";

    TiXmlElement* pTextureRoot = 0;
    TiXmlElement* pObjectRoot = 0;


    for(TiXmlElement* e = pStateRoot->FirstChildElement();
	e != 0; e = e->NextSiblingElement()){
	if(e->Value() == std::string("TEXTURES")){
	    pTextureRoot = e;
	}
	if(e->Value() == std::string("OBJECTS")){
	    pObjectRoot = e;
	}
    }

    if(pTextureRoot)
	parseTextures(pTextureRoot, pTextureIDs);

    if(pObjectRoot)
	parseObjects(pObjectRoot, pObjects);

    
    return true;
}




void StateParser::parseTextures(TiXmlElement* pTextureRoot,
				std::vector<std::string> *pTextureIDs){
    for(TiXmlElement* e = pTextureRoot->FirstChildElement(); e != 0;
	e = e->NextSiblingElement()){
	std::string filenameAttribute = e->Attribute("filename");
	std::string idAttribute = e->Attribute("ID");
	pTextureIDs->push_back(idAttribute);

	TheTextureManager::Instance()->load(filenameAttribute, idAttribute,
					    TheGame::Instance()->getRenderer());
    }
}



void StateParser::parseObjects(TiXmlElement* pObjectRoot,
			       std::vector<GameObject*> *pObjects){

    for(TiXmlElement* e = pObjectRoot->FirstChildElement(); e != 0;
	e = e->NextSiblingElement()){

	int x, y, width, height, numFrames, callbackID, animSpeed = 0;
	std::string textureID;

	 
	e->Attribute("x", &x);
	e->Attribute("y", &y);
	e->Attribute("width", &width);
	e->Attribute("height", &height);
	e->Attribute("numFrames", &numFrames);
	e->Attribute("callbackID", &callbackID);
	e->Attribute("animSpeed", &animSpeed);


	textureID = e->Attribute("textureID");

	GameObject* pGameObject =
	    TheGameObjectFactory::Instance()->create(e->Attribute("type"));

	pGameObject->load(new LoaderParams(x, y, width, height, textureID,
					   numFrames, animSpeed, callbackID));
	pObjects->push_back(pGameObject);
    }
}

/* 

   GameObjectFactory.cpp

   Author: Saroj Rai @ Charicha 
   Created On: Wednesday,  1 August 2018.

*/

#include "GameObjectFactory.h"

// $Log:$ //
//



GameObjectFactory* GameObjectFactory::s_pInstance = 0;



bool GameObjectFactory::registerType(std::string typeID, BaseCreator* pCreator){
    std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);

    if(it != m_creators.end()){	// if we did find matching id
	delete pCreator;
	return false;
    }

    m_creators[typeID] = pCreator;
    return true;
}


GameObject* GameObjectFactory::create(std::string typeID){
    std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);

    if(it == m_creators.end()){ // if we didn't find anything
	std::cout << "couldn't find type: '" << typeID << "' !\n";
	return 0;
    }

    BaseCreator* pCreator = (*it).second;
    return pCreator->createGameObject();
}


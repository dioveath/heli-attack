/* 

   ObjectLayer.cpp

   Author: Saroj Rai @ Charicha 
   Created On: Thursday,  2 August 2018.

*/

#include "ObjectLayer.h"

// $Log:$ //
//


void ObjectLayer::update(){
    for(int i = 0; i < m_gameObjects.size(); i++){
	m_gameObjects[i]->update();
    }
}


void ObjectLayer::render(){
    for(int i = 0; i < m_gameObjects.size(); i++){
	m_gameObjects[i]->render();
    }
}



/* 

   TextureManager.cpp

   Author: Saroj Rai @ Charicha 
   Created On: Friday, 20 July 2018.

*/

#include "TextureManager.h"
#include <iostream>

#include "Camera.h"

// $Log:$ //
//


TextureManager* TextureManager::s_pInstance = 0; // initializing static member


bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
    if(m_textureMap.find(id) != m_textureMap.end()){
	std::cout << "There already exists texture of same id, '" << id << "'!\n";
	return false;
    }
    SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
    if(!pTempSurface) {
	std::cout << "Unable to load '" << fileName << "' file..!\n";
	return false;
    }

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
    SDL_FreeSurface(pTempSurface);
    if(!pTexture) {
	std::cout << "Unable to create texture from surface!\n";
	return false;
    }

    std::cout << "Created Texture with id: " << id << std::endl;

    m_textureMap[id] = pTexture;
    return true;
}


void TextureManager::draw(std::string id, int x, int y, int width, int height,
			  SDL_Renderer* pRenderer, SDL_RendererFlip flip) {
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;

    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}


void TextureManager::drawFrame(std::string id, int x, int y, int width, int height,
			       int currentRow, int currentFrame,
			       SDL_Renderer* pRenderer, SDL_RendererFlip flip,
			       int angle)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = width * currentFrame;
    srcRect.y = height * (currentRow - 1);
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x - TheCamera::Instance()->getPosition().getX();
    destRect.y = y - TheCamera::Instance()->getPosition().getY();

    // std::cout << "id:  " << id << std::endl;


    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, angle, 0, flip);
}


void TextureManager::drawFrameUI(std::string id, int x, int y, int width, int height,
			       int currentRow, int currentFrame,
			       SDL_Renderer* pRenderer, SDL_RendererFlip flip,
			       int angle)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = width * currentFrame;
    srcRect.y = height * (currentRow - 1);
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;

    // std::cout << "id:  " << id << std::endl;


    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, angle, 0, flip);
}


void TextureManager::clearFromTextureMap(std::string id){
    if(m_textureMap.find(id) != m_textureMap.end()){
	SDL_DestroyTexture(m_textureMap[id]);
	m_textureMap.erase(id);
    }
}


void TextureManager::drawTile(std::string id, int margin, int spacing, int x, int y,
			      int width, int height, int currentRow, int currentFrame,
			      SDL_Renderer *pRenderer)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = margin + (spacing + width) * currentFrame;
    srcRect.y = margin + (spacing + width) * currentRow;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x - TheCamera::Instance()->getPosition().getX();
    destRect.y = y - TheCamera::Instance()->getPosition().getY();
 
    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect,
		     0, 0, SDL_FLIP_NONE);
}


void TextureManager::fillRect(int x, int y, int width, int height,
			      SDL_Renderer* pRenderer,
			      int r, int g, int b, int a){
    		SDL_Rect destRect;

		destRect.x = x - TheCamera::Instance()->getPosition().getX();
		destRect.y = y - TheCamera::Instance()->getPosition().getY();
		destRect.w = width;
		destRect.h = height;

		SDL_SetRenderDrawColor(pRenderer, r, g, b, a);

		SDL_RenderFillRect(pRenderer, &destRect);
}


void TextureManager::fillRectUI(int x, int y, int width, int height,
			      SDL_Renderer* pRenderer,
			      int r, int g, int b, int a){
    		SDL_Rect destRect;

		destRect.x = x;
		destRect.y = y;
		destRect.w = width;
		destRect.h = height;

		SDL_SetRenderDrawColor(pRenderer, r, g, b, a);

		SDL_RenderFillRect(pRenderer, &destRect);
}



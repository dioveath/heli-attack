// TextureManager.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H 1


#include <string>
#include <map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Camera.h"


class TextureManager {


 public:
    static TextureManager* Instance() {
	if(!s_pInstance)
	    s_pInstance = new TextureManager();
	return s_pInstance;
    }
    
    bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

    void draw(std::string id, int x, int y, int width, int height,
	      SDL_Renderer* pRenderer, SDL_RendererFlip = SDL_FLIP_NONE);

    void drawFrame(std::string id, int x, int y, int width, int height,
		   int currentRow, int currentFrame,
		   SDL_Renderer* pRenderer, SDL_RendererFlip = SDL_FLIP_NONE,
		   int angle = 0);
    void drawFrameUI(std::string id, int x, int y, int width, int height,
		   int currentRow, int currentFrame,
		   SDL_Renderer* pRenderer, SDL_RendererFlip = SDL_FLIP_NONE,
		   int angle = 0);


    void drawTile(std::string id, int margin, int spacing, int x, int y,
		  int width, int height, int currentRow, int currentFrame,
		  SDL_Renderer* pRenderer);

    void clearFromTextureMap(std::string id);
    void fillRect(int x, int y, int width, int height,
		    SDL_Renderer* pRenderer,
		    int r = 255, int g = 255, int b = 0, int a = 150);

    void fillRectUI(int x, int y, int width, int height,
		  SDL_Renderer* pRenderer,
		  int r = 255, int g = 255, int b = 0, int a = 150);

    /* SDL_Texture* getTexture( */


 private:
    TextureManager() { }
    ~TextureManager() { }

    std::map<std::string, SDL_Texture*> m_textureMap;

    static TextureManager* s_pInstance;

};


typedef TextureManager TheTextureManager;



#endif // TEXTUREMANAGER_H
//////////////////////////////////////////////////////////////////////
// $Log:$
//

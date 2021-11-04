/* 

   AudioManager.cpp

   Author: Saroj Rai @ Charicha 
   Created On: Friday, 17 August 2018.

*/

#include "AudioManager.h"

#include <iostream>


// $Log:$ //
//


AudioManager* AudioManager::s_pInstance = 0;



bool AudioManager::InitAudio(){
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)){
	std::cout << "Unable to initialize audio! " << Mix_GetError() << std::endl;
	return false;
    }
    return true;
}


int AudioManager::LoadSound(std::string filename){
    Mix_Chunk* tempChunk = Mix_LoadWAV(filename.c_str());
    if(!tempChunk){
	std::cout << "Unable to load sound effect, " << Mix_GetError() << std::endl;
	return -1;
    }

    m_Sounds[++m_SoundCounter] = tempChunk;
    return m_SoundCounter;
}


int AudioManager::LoadMusic(std::string filename){
    Mix_Music* tempMusic = Mix_LoadMUS(filename.c_str());
    if(!tempMusic){
	std::cout << "Unable to load music, " << Mix_GetError() << std::endl;
	return -1;
    }

    m_Musics[++m_MusicCounter] = tempMusic;
    return m_MusicCounter;
}


void AudioManager::PlaySound(int id, int loop){
    if(m_Sounds.find(id) == m_Sounds.end()){
	std::cout << "Invalid Sound ID, '" << id << "' to play!\n";
	return;
    }
    Mix_PlayChannel(-1, m_Sounds[id], loop);
}


void AudioManager::PlayMusic(int id, int loop){
    if(m_Musics.find(id) == m_Musics.end()){
	std::cout << "Invalid Music ID, '" << id << "' to play!\n";
	return;
    }
    // if(!Mix_PlayingMusic() /*|| m_CanPlayNext*/){
	Mix_PlayMusic(m_Musics[id], loop);
	// m_CanPlayNext = false;
	// return;
    // }



    // if(Mix_PlayingMusic() && !Mix_FadeOutMusic(3000)){
	// Mix_HookMusicFinished(MusicHookFunction);
	// m_NextPlayID = id;
	// Mix_HaltMusic();
	// Mix_PlayMusic(m_Musics[id], loop);
    // }
}


void AudioManager::ReleaseSound(int id){
    // for(std::map<int, MixChunk*>::iterator it = m_Sounds.begin();
    std::map<int, Mix_Chunk*>::iterator it;
    it = m_Sounds.find(id);
    
    if(it == m_Sounds.end()){
	std::cout << "Invalid Sound ID, '" << id << "' to delete!\n";
	return;
    }

    Mix_FreeChunk(m_Sounds[id]);
    m_Sounds[id] = 0;
    m_Sounds.erase(id);
}


void AudioManager::ReleaseMusic(int id){
    if(m_Musics.find(id) == m_Musics.end()){
	std::cout << "Invalid Music ID, '" << id << "' to delete!\n";
	return;
    }
    Mix_FreeMusic(m_Musics[id]);
    m_Musics[id] = 0;
    m_Musics.erase(id);
}



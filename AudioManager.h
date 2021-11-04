// AudioManager.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H 1

#include <SDL2/SDL_Mixer.h>
#include <map>


class AudioManager {

 public:
    static AudioManager* Instance(){
	if(!s_pInstance)
	    s_pInstance = new AudioManager();
	return s_pInstance;
    }

    bool InitAudio();

    int LoadSound(std::string filename);
    int LoadMusic(std::string filename);

    void PlaySound(int id, int loop = 0);
    void PlayMusic(int id, int loop = -1);

    void ReleaseSound(int id);
    void ReleaseMusic(int id);
    

 private:
    AudioManager()
	: m_SoundCounter(0),
	  m_MusicCounter(0)
	  { }

    static AudioManager* s_pInstance;

    std::map<int, Mix_Chunk*> m_Sounds;
    std::map<int, Mix_Music*> m_Musics;

    int m_SoundCounter;
    int m_MusicCounter;


 public:
    int m_NextPlayID;

};


typedef AudioManager TheAudioManager;




#endif // AUDIOMANAGER_H
//////////////////////////////////////////////////////////////////////
// $Log:$
//

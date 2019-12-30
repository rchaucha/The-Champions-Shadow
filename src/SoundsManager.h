#ifndef DEF_SOUNDSMANAGER
#define DEF_SOUNDSMANAGER

#include <sfml/Audio.hpp>
#include <iostream>
#include <string>
#include <map>
#include <stdio.h>

class SoundsManager
{
public:
   SoundsManager();
   std::string choose_music();
   void play_music();
   void change_music();
   void change_music_volume(int additionnal_volume) { _current_music.setVolume(_current_music.getVolume() + additionnal_volume); }
   void play_sound(std::string sound_name);

private:
   unsigned int _nbr_musics;
   sf::Music _current_music;
   std::map<int, std::string> _musics_list;
   sf::SoundBuffer _buffer;
   sf::Sound _sound;
};

#endif
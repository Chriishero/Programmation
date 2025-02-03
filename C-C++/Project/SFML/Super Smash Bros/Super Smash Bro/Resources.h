#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>

class Resources
{
public:
	static std::map<std::string, sf::Texture> textures;
	static std::map<std::string, sf::SoundBuffer> sounds;
};


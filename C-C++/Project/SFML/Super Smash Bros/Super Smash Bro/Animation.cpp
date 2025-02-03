#include "Animation.h"
#include <algorithm>

Animation::Animation(float lenght, std::vector<AnimFrame> frames) : m_lenght(lenght), m_frames(frames)
{
}

void Animation::update(float deltaTime)
{
	m_time += deltaTime;
}

sf::Texture Animation::getTexture()
{
	while (m_time > m_lenght)
	{
		m_time -= m_lenght;
	}
	for (const auto& frame : m_frames)
	{
		if (m_time >= frame.time)
		{
			return frame.texture;
		}
	}
	return sf::Texture();
}

sf::Texture Animation::front()
{
	return m_frames.front().texture;
}
sf::Texture Animation::back()
{
	return m_frames.back().texture;
}
float Animation::getm_lenght()
{
	return m_lenght;
}
float Animation::getm_time()
{
	return m_time;
}

void Animation::setm_time(float n)
{
	m_time = n;
}

std::vector<AnimFrame> Animation::getm_frames()
{
	return m_frames;
}

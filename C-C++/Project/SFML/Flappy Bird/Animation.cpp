#include "Animation.h"

Animation::Animation(float lenght, std::vector<AnimFrame> frames) : m_lenght(lenght), m_frames(frames)
{}

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



#pragma once
#include <iostream>
#include <SFML/Audio.hpp>
#include "SoundReader.h"

class CustomSound : public sf::Sound
{
public:
	const std::pair<int, int>& getCurrentSample();

	const std::pair<int, int>& getPreviousSample() const;

private:
	std::pair<int, int> m_lastSample{0,0};
};
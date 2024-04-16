#pragma once
#include <iostream>
#include <SFML/Audio.hpp>

class SoundReader
{
public:

	static const std::pair<int, int>& getPlayedSample(const sf::Int16* sampleData,
                                                      const unsigned int& sampleFrequency,
                                                      const unsigned int& numberOfChannels,
                                                      const sf::Time& offset);
};
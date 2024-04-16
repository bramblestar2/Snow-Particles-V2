#include "SoundReader.h"

const std::pair<int, int>& SoundReader::getPlayedSample(const sf::Int16* sampleData,
                                                        const unsigned int& sampleFrequency, 
                                                        const unsigned int& numberOfChannels, 
                                                        const sf::Time& offset)
{
    sf::Time currentPlayingTime{ offset };
    unsigned int currentSamplePosition = currentPlayingTime.asSeconds() * sampleFrequency;
    unsigned int currentSampleDataIndex{ currentSamplePosition * numberOfChannels };
    sf::Int16 leftChannel{ sampleData[currentSampleDataIndex] };
    sf::Int16 rightChannel{ sampleData[currentSampleDataIndex + 1] };

    return { leftChannel, rightChannel };
}

#include "CustomSound.h"


const std::pair<int, int>& CustomSound::getCurrentSample()
{
    unsigned int sampleFrequency{ this->getBuffer()->getSampleRate() };
    unsigned int numberOfChannels{ this->getBuffer()->getChannelCount()};
    const sf::Int16* sampleData{ this->getBuffer()->getSamples()};
    sf::Time currentPlayingTime{ this->getPlayingOffset() };
    unsigned int currentSamplePosition = currentPlayingTime.asSeconds() * sampleFrequency ;
    unsigned int currentSampleDataIndex{ currentSamplePosition * numberOfChannels };
    sf::Int16 leftChannel{ sampleData[currentSampleDataIndex] };
    sf::Int16 rightChannel{ sampleData[currentSampleDataIndex + 1] };

    m_lastSample.first = leftChannel;
    m_lastSample.second = rightChannel;

    return {leftChannel, rightChannel};
}

const std::pair<int, int>& CustomSound::getPreviousSample() const
{
    return m_lastSample;
}

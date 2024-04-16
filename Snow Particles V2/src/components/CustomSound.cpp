#include "CustomSound.h"


const std::pair<int, int>& CustomSound::getCurrentSample()
{
    this->getBuffer()->getChannelCount();
    this->getBuffer()->getSamples();
    this->getBuffer()->getSampleRate();
    std::pair<int, int> samples = SoundReader::getPlayedSample(this->getBuffer()->getSamples(), 
                                                               this->getBuffer()->getSampleRate(), 
                                                               this->getBuffer()->getChannelCount(), 
                                                               this->getPlayingOffset());

    m_lastSample.first = samples.first;
    m_lastSample.second = samples.second;

    return samples;
}

const std::pair<int, int>& CustomSound::getPreviousSample() const
{
    return m_lastSample;
}

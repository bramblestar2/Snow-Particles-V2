#include "SoundBufferManipulator.hpp"


SoundBufferManipulator::SoundBufferManipulator()
{
}


void SoundBufferManipulator::setBuffer(sf::SoundBuffer * const buffer)
{
    m_buffer = buffer;
}


const sf::Int16* SoundBufferManipulator::smoothBuffer(int smoothRate, const bool& forceUpdate)
{
    if (!m_buffer) return nullptr;

    if (!forceUpdate && !m_smoothBuffer.empty()) return m_smoothBuffer.data();
    if (forceUpdate) m_smoothBuffer.clear();

    if (smoothRate <= 0) smoothRate = 2;

    m_smoothBuffer.clear();
    m_smoothBuffer.resize(m_buffer->getSampleCount());
    
    const int threadCount = std::thread::hardware_concurrency();
    std::vector<std::future<void>> threads;

    auto smoothingLambda = [&](const int& start, const int& end) -> void 
        {
            // Apply smoothing to the samples within the specified range
            for (int i = start; i < end; ++i) {
                // Apply the smoothing operation (you can replace this with your smoothing algorithm)
                // For example, averaging neighboring samples
                int sum = 0;
                int count = 0;
                for (int j = std::max(0, i - smoothRate); j <= std::min(static_cast<int>(m_smoothBuffer.size()) - 1, i + smoothRate); ++j) {
                    sum += static_cast<int>(m_buffer->getSamples()[j]);
                    ++count;
                }
                m_smoothBuffer[i] = static_cast<sf::Int16>(sum / count);
            }
        };


    int chunkSize = m_buffer->getSampleCount() / threadCount;
    int remainder = m_buffer->getSampleCount() % threadCount;
    int start = 0;

    for (int i = 0; i < threadCount; ++i)
    {
        int end = start + chunkSize + (i < remainder ? 1 : 0);

        threads.push_back(std::async(std::launch::async, smoothingLambda, start, end));
        start = end;
    }

    for (auto& thread : threads)
        thread.get(); // Wait for threads to finish

    return m_smoothBuffer.data();
}

#pragma once
#include <iostream>
#include <SFML/Audio.hpp>
#include <vector>
#include <mutex>
#include <future>

class SoundBufferManipulator
{
public:
	SoundBufferManipulator();

	void setBuffer(sf::SoundBuffer* const buffer);
	const sf::Int16* smoothBuffer(int smoothRate = 5, const bool& forceUpdate = false);

private:
	sf::SoundBuffer* m_buffer = nullptr;
	std::vector<sf::Int16> m_smoothBuffer;
};
#include "AnimatedTexture.h"

AnimatedTexture::AnimatedTexture(const std::string& path, const std::string& mask, const bool& fillMask)
{
	setPath(path);
	setMaskedString(mask);
	setFillMask(fillMask);
	setFramerate(30);
}


void AnimatedTexture::setPath(const std::string& path)
{
	m_path = path;
}


void AnimatedTexture::setMaskedString(const std::string& mask)
{
	m_maskedString = mask;
}


void AnimatedTexture::setFillMask(const bool& fillMask)
{
	m_fillMask = fillMask;
}


void AnimatedTexture::setStartFrame(const int& frame)
{
	m_startFrame = frame;
}


void AnimatedTexture::setFramerate(const double& framerate)
{
	m_framerate = framerate;
}


const int& AnimatedTexture::getStartFrame() const
{
	return m_startFrame;
}


const int& AnimatedTexture::getCurrentFrame() const
{
	return m_frame;
}


const int& AnimatedTexture::getFrameCount() const
{
	return m_frames.size();
}

sf::Texture * const AnimatedTexture::getTexture() const
{
	return m_frames.at(static_cast<int>(m_frame)).get();
}


void AnimatedTexture::load()
{
	bool exit = false;
	int count = m_startFrame;

	do {
		std::string path = m_path + "/" + frameStr(count, m_fillMask);
		if (!std::filesystem::exists(path)) {
			exit = true;
			continue;
		}

		m_frames.push_back(std::unique_ptr<sf::Texture>(new sf::Texture()));
		m_frames.at(m_frames.size()-1)->loadFromFile(path);

		count++;
	} while (!exit);
}


void AnimatedTexture::update()
{
	updateDT();

	m_frame = std::fmod(m_frame + (m_dt * m_framerate), m_frames.size());
}


std::string AnimatedTexture::frameStr(const int& frame, const bool& fill) const
{
	std::string str = m_maskedString;

	auto count = std::ranges::count(str, '#');

	std::string filledFrame = std::to_string(frame);

	if (fill)
	{
		for (int i = 0; i <= count - filledFrame.size(); i++) 
			filledFrame.insert(filledFrame.begin(), '0');
	}
	
	std::regex reg("[#]+");

	filledFrame = std::regex_replace(str, reg, filledFrame);

	return filledFrame;
}


void AnimatedTexture::updateDT()
{
	m_dt = m_dtClock.restart().asSeconds();
}

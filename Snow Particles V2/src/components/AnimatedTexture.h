#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <regex>

class AnimatedTexture
{
public:
	AnimatedTexture(const std::string& path = "", const std::string& mask = "frame (#)", const bool& fillMask = true);

	void setPath(const std::string& path);
	void setMaskedString(const std::string& mask);
	void setFillMask(const bool& fillMask);
	void setStartFrame(const int& frame);
	void setFramerate(const double& framerate);

	const int& getStartFrame() const;
	const int& getCurrentFrame() const;
	const int& getFrameCount() const;
	sf::Texture * const getTexture() const;

	void load();

	void update();

private:

	std::string frameStr(const int& frame, const bool& fill = true) const;
	void updateDT();

	bool m_fillMask;
	int m_startFrame;
	double m_dt;
	double m_frame;
	double m_framerate;
	std::vector<std::unique_ptr<sf::Texture>> m_frames;
	std::string m_path;
	std::string m_maskedString;
	sf::Clock m_dtClock;
};
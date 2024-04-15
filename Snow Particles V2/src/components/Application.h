#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <dwmapi.h>
#include "DancinWindow.h"
#include "AnimatedTexture.h"
#include "Snow.h"
#include "CustomSound.h"

class Application
{
public:
	Application();

	void updateEvents();
	void updateDT();
	void update();
	void render();

	void run();

private:
	void shutdown();

	DancinWindow m_window;

	double m_framerate;
	double m_dt;
	sf::Clock m_dtClock;
	sf::Clock m_uptime;
	sf::Event m_event;

	AnimatedTexture m_protogenGif;
	sf::RectangleShape m_protogen;

	Snow m_snow;

	CustomSound m_music;
	sf::SoundBuffer m_musicBuffer;
};
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "DancinWindow.h"
#include "AnimatedTexture.h"

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
	DancinWindow m_window;

	double m_framerate;
	double m_dt;
	sf::Clock m_dtClock;
	sf::Event m_event;

	AnimatedTexture m_protogenGif;
	sf::Sprite m_protogen;

	sf::Sound m_music;
	sf::SoundBuffer m_musicBuffer;
};
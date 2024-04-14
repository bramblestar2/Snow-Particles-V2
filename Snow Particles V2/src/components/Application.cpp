#include "Application.h"

Application::Application()
	: m_protogenGif("assets/protogen", "frame (##).png", false)
{
	m_window.create(sf::VideoMode(500, 500), "Hello World");
	m_window.setSpeed(0.5);

	m_framerate = 20;

	m_protogenGif.setStartFrame(1);
	m_protogenGif.setFramerate(m_framerate);
	m_protogenGif.load();

	m_musicBuffer.loadFromFile("assets/song.ogg");

	m_music.setBuffer(m_musicBuffer);
	m_music.setLoop(true);
	m_music.play();
}


void Application::updateEvents()
{
	while (m_window.pollEvent(m_event))
	{
		if (m_event.type == sf::Event::Closed)
			m_window.close();
	}
}


void Application::updateDT()
{
	m_dt = m_dtClock.restart().asSeconds();
}


void Application::update()
{
	m_window.next();

	m_protogenGif.update();
}


void Application::render()
{
	m_window.clear();

	m_protogen.setTexture(*m_protogenGif.getTexture());
	m_window.draw(m_protogen);

	m_window.display();
}


void Application::run()
{
	while (m_window.isOpen())
	{
		updateDT();
		updateEvents();
		update();
		render();
	}
}

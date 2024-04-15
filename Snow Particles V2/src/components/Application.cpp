#include "Application.h"

Application::Application()
	: m_protogenGif("assets/protogen", "frame (##).png", false),
	m_window(sf::VideoMode(500, 500), "Hello World", sf::Style::None)
{
	HWND hWnd = m_window.getSystemHandle();
	SetWindowLongPtr(hWnd, GWL_EXSTYLE, GetWindowLongPtr(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(m_window.getSystemHandle(), 0, 0, LWA_COLORKEY);

	m_framerate = 20;

	m_window.setShake(true);
	m_window.setSpeed(0.5);
	m_window.setWindowMoving(true);

	m_protogenGif.setStartFrame(1);
	m_protogenGif.setFramerate(m_framerate);
	m_protogenGif.load();

	m_musicBuffer.loadFromFile("assets/song.ogg");

	m_music.setBuffer(m_musicBuffer);
	m_music.setLoop(true);
	m_music.play();
	sf::Vector2f protoSize(250,250);
	m_protogen.setSize(protoSize);
	m_protogen.setOrigin(protoSize.x / 2, protoSize.y / 2);
	m_protogen.setPosition(m_window.getSize().x / 2, m_window.getSize().y / 2);

	m_snow.setSpawnWidth(m_window.getSize().x);
	m_snow.setSpeed(50);
	m_snow.setFrequency(0.3);
	m_snow.setMaxDepth(m_window.getSize().y + 50);
}


void Application::updateEvents()
{
	while (m_window.pollEvent(m_event))
	{
		if (m_event.type == sf::Event::Closed)
			shutdown();
		else if (m_event.type == sf::Event::KeyPressed)
		{
			switch (m_event.key.code)
			{
			case sf::Keyboard::Escape:
				shutdown();
				break;
			}
		}
	}
}


void Application::updateDT()
{
	m_dt = m_dtClock.restart().asSeconds();
}


void Application::update()
{
	double uptime = m_uptime.getElapsedTime().asSeconds() * 2;

	double prevSample = ((m_music.getPreviousSample().first + m_music.getPreviousSample().second) / 2) / 1000;
	double sample = ((m_music.getCurrentSample().first + m_music.getCurrentSample().second) / 2) / 1000;

	m_window.setDistance(std::lerp(prevSample, sample, 0.5f));
	m_window.setOffset(cos(uptime), sin(uptime));
	m_window.next();

	m_protogenGif.setFramerate(abs(sample/20.0f)*50);
	m_protogenGif.update(m_dt);

	m_snow.setSpeed(abs(sample / 20.0f)*500);
	m_snow.update(m_dt);
}


void Application::render()
{
	m_window.clear(sf::Color(0,0,0,0));

	m_protogen.setTexture(m_protogenGif.getTexture());
	m_window.draw(m_protogen);

	m_snow.batch();
	m_window.draw(m_snow);

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


void Application::shutdown()
{
	m_window.close();
}

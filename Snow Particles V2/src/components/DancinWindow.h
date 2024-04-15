#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class DancinWindow : public sf::RenderWindow
{
public:
	DancinWindow();
	DancinWindow(sf::VideoMode mode, const sf::String& title, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings());
	DancinWindow(sf::WindowHandle handle, const sf::ContextSettings& settings = sf::ContextSettings());

	void setSpeed(const double& speed);
	void setOffset(const double& x, const double& y);
	void setDistance(const double& distance);
	void setShake(const bool& shake);
	void setWindowMoving(const bool& moving);

	const double& getSpeed() const;

	void next();
private:
	bool m_windowMoving;
	bool m_shake;
	double m_distance;
	double m_speed;
	sf::Vector2f m_offset;
	sf::Clock m_clock;
};
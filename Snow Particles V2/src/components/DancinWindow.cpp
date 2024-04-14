#include "DancinWindow.h"

DancinWindow::DancinWindow() 
	: sf::RenderWindow()
{
}


DancinWindow::DancinWindow(sf::VideoMode mode, const sf::String& title, sf::Uint32 style, const sf::ContextSettings& settings)
	: sf::RenderWindow(mode, title, style, settings)
{
}


DancinWindow::DancinWindow(sf::WindowHandle handle, const sf::ContextSettings& settings)
	: sf::RenderWindow(handle, settings)
{
}


void DancinWindow::setSpeed(const double& speed)
{
	m_speed = speed;
}


void DancinWindow::setOffset(const double& x, const double& y)
{
	m_offset.x = x;
	m_offset.y = y;
}


const double& DancinWindow::getSpeed() const
{
	return m_speed;
}


void DancinWindow::next()
{
	double seconds = m_clock.getElapsedTime().asSeconds() * m_speed;

	sf::VideoMode monitor = sf::VideoMode::getDesktopMode();
	double centerX = monitor.width / 2;
	double centerY = monitor.height / 2;

	double windowX = this->getSize().x;
	double windowY = this->getSize().y;

	double windowCenterX = windowX / 2;
	double windowCenterY = windowY / 2;

	double scale = (2 / (3 - cos(2 * seconds))) * 400;

	double newX = centerX + (cos(seconds) * scale) - windowCenterX;
	double newY = centerY + ((sin(2*seconds) * scale)/2) - windowCenterY;

	double lerpX = std::lerp(this->getPosition().x, newX + m_offset.x, 0.5f);
	double lerpY = std::lerp(this->getPosition().y, newY + m_offset.y, 0.5f);

	this->setPosition(sf::Vector2i(lerpX, lerpY));
}

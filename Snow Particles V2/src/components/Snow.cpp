#include "Snow.h"


Snow::Snow(const int& amountPerSpwn, const double& frequency)
	: m_amountPerSpawn(amountPerSpwn), m_frequency(frequency),
	  m_batch(sf::PrimitiveType::Quads)
{
	m_speed = 1;
	m_frequency = 1;
	m_maxDepth = 100;
	m_snowColor = sf::Color(255,255,255,150);
}


void Snow::setSpeed(const double& speed)
{
	m_speed = speed;
}


void Snow::setSpawnPosition(const sf::Vector2f& position)
{
	m_spawnPosition = position;
}


void Snow::setSpawnWidth(const double& width)
{
	m_spawnWidth = width;
}


void Snow::setFrequency(const double& frequency)
{
	m_frequency = frequency;
}


void Snow::setMaxDepth(const double& depth)
{
	m_maxDepth = depth;
}


void Snow::setColor(const sf::Color& color)
{
	m_snowColor = color;
}


void Snow::batch()
{
	m_batch.clear();
	m_batch.resize(m_particles.size() * 4);

	for (int i = 0; i < m_particles.size(); i++)
	{
		if (abs(m_particles.at(i).getPosition().y) > m_maxDepth)
		{
			m_particles.erase(m_particles.begin() + i);
			i--;
			continue;
		}

		const int index = i * 4;

		const sf::Transform& t = m_particles.at(i).getTransform();
		sf::FloatRect rect = m_particles.at(i).getLocalBounds();

		sf::Vector2f topLeft = t * sf::Vector2f(rect.left, rect.top);
		sf::Vector2f topRight = t * sf::Vector2f(rect.left + rect.width, rect.top);
		sf::Vector2f bottomRight = t * sf::Vector2f(rect.left + rect.width, rect.top + rect.height);
		sf::Vector2f bottomLeft = t * sf::Vector2f(rect.left, rect.top + rect.height);

		m_batch[index].position = topLeft;
		m_batch[index].color = m_particles.at(i).getFillColor();

		m_batch[index + 1].position = topRight;
		m_batch[index + 1].color = m_particles.at(i).getFillColor();

		m_batch[index + 2].position = bottomRight;
		m_batch[index + 2].color = m_particles.at(i).getFillColor();

		m_batch[index + 3].position = bottomLeft;
		m_batch[index + 3].color = m_particles.at(i).getFillColor();
	}
}


void Snow::update(const double& dt)
{
	if (m_clock.getElapsedTime().asSeconds() > m_frequency)
	{
		m_clock.restart();

		std::uniform_real_distribution<double> dist(0, m_spawnWidth);

		for (int i = 0; i < m_amountPerSpawn; i++)
		{
			sf::RectangleShape particle;
			particle.setSize(sf::Vector2f(5,5));
			particle.setFillColor(m_snowColor);
			particle.setPosition(m_spawnPosition.x + dist(m_gen), m_spawnPosition.y);

			m_particles.push_back(particle);
		}
	}

	for (int i = 0; i < m_particles.size(); i++)
	{
		m_particles.at(i).move(0, dt*m_speed);
	}
}


void Snow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_batch);
}

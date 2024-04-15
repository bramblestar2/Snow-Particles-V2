#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <random>

class Snow : public sf::Drawable
{
public:
	Snow(const int& amountPerSpwn = 5, const double& frequency = 0.5);

	void setSpeed(const double& speed);
	void setSpawnPosition(const sf::Vector2f& position);
	void setSpawnWidth(const double& width);
	void setFrequency(const double& frequency);
	void setMaxDepth(const double& depth);
	void setColor(const sf::Color& color);
	
	void batch();

	void update(const double& dt);

private:
	int m_amountPerSpawn;
	double m_frequency;
	double m_speed;
	sf::Color m_snowColor;
	sf::Clock m_clock;

	double m_maxDepth;
	double m_spawnWidth;
	sf::Vector2f m_spawnPosition;

	std::vector<sf::RectangleShape> m_particles;

	sf::VertexArray m_batch;

	std::default_random_engine m_gen;

	// Inherited via Drawable
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
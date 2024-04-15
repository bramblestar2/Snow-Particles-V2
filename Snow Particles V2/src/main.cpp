#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "components/AnimatedTexture.h"
#include "components/Application.h"

int main()
{
	Application app("assets/song1.ogg");

	app.run();

	return 0;
}
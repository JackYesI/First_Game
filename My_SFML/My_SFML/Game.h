#pragma once
#include <iostream>
#include <vector>
#include<ctime>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/*
* Class that acts as a game engine.
* Wrapper class
*/

class Game
{
private:
	// variables 
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	// Game obj
	std::vector<sf::RectangleShape> enemis;
	sf::RectangleShape enemy;

	// Mouse position
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Resources
	sf::Font fonts;

	// Text
	sf::Text uiText;

	// Game logic
	bool endGame;
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemy;
	bool mouseHeld;

	// Private functions
	void initializeVariable();
	void initWindow();
	void initFonts();
	void initEnemies();
	void initText();
public:
	// Constructor/ Destructor
	Game();
	virtual ~Game();
	// Accessors
	const bool running() const;
	const bool getEndGame() const;
	// Functions
	void spawnEnemy();
	void pollIvents();
	void updateMousePosition();
	void updateEnemies();
	void updateText();
	void update();

	void render();
	void renderText(sf::RenderTarget& target);
	void renderEnemies(sf::RenderTarget& target);
};


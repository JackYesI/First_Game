#include "Game.h"

void Game::initializeVariable()
{
	this->window = nullptr;

	// Game logic
	this->points = 0;
	this->health = 10;
	this->enemySpawnTimerMax = 30.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemy = 40;
	this->mouseHeld = false;
	this->endGame = false;
}

void Game::initWindow()
{
	this->videoMode.width = 800;
	this->videoMode.height = 600;
	this->window = new  sf::RenderWindow(this->videoMode, "Yes I", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);
}
void Game::initFonts()
{
	if (!this->fonts.loadFromFile("D:\\c++\\Game\\SFML_\\Rubik_Doodle_Triangles\\RubikDoodleTriangles-Regular.ttf"))
	{
		std::cout << "ERROR FONTS" << "\n";
	}
}
void Game::initEnemies()
{
	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	/*this->enemy.setFillColor(sf::Color::Red);*/
	/*this->enemy.setOutlineColor(sf::Color::Green);
	this->enemy.setOutlineThickness(1.f);*/
}
void Game::initText()
{
	this->uiText.setFont(this->fonts);
	this->uiText.setCharacterSize(25);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("NONE");
}
// Constructor / Destructor
Game::Game()
{
	this->initializeVariable();
	this->initWindow();
	this->initEnemies();
	this->initFonts();
	this->initText();
}

Game::~Game()
{
	delete this->window;
}
const bool Game::running() const
{
	return this->window->isOpen();
}
const bool Game::getEndGame() const
{
	return this->endGame;
}
// Accessors

void Game::spawnEnemy()
{
	/*
	* @return void
	*
	* Spawns enemies and sets their colors and positions.
	* -Sets a random position
	* -Sets a random color.
	* -Adds enemy to the
	*/
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
	);
	int random = (rand() % (4 - 1 + 1)) + 1;
	switch (random)
	{
	case 1:
		this->enemy.setFillColor(sf::Color(243, 98, 153));
		break;
	case 2:
		this->enemy.setFillColor(sf::Color(70, 160, 212));
		break;
	case 3:
		this->enemy.setFillColor(sf::Color(108, 57, 150));
		break;
	case 4:
		this->enemy.setFillColor(sf::Color(39, 255, 254));
		break;
	default:
		break;
	}

	// Spawn the enemy
	this->enemis.push_back(this->enemy);
}

// Functions
void Game::pollIvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		default:
			break;
		}
	}
}

void Game::updateMousePosition()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateEnemies()
{
	/*
	* @ return void
	*
	* Updates the enemy spawn timer and spawnsenemies
	* when the total amount of enemies is smaller than the max
	* Removes the enemies at the edge of the screen
	*/
	//Updating the timer for enemy spawning
	if (this->enemis.size() < this->maxEnemy)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
			//Spawn the enemy and reset the timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	// Move and updating enemies
	for (int i = 0; i < this->enemis.size(); i++)
	{
		bool detected = false;

		this->enemis[i].move(0.f, 2.f);

		if (this->enemis[i].getPosition().y > this->window->getSize().y)
		{
			this->enemis.erase(this->enemis.begin() + i);
			this->health -= 1;
			if (health <= 0) this->endGame = true;
			std::cout << "Health: " << this->health << "\n";
		}
	}

	// Check if click upon
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleted = false;
			for (size_t i = 0; i < this->enemis.size() && deleted == false; i++)
			{
				if (this->enemis[i].getGlobalBounds().contains(this->mousePosView))
				{
					// Delete the enemy
					deleted = true;
					this->enemis.erase(this->enemis.begin() + i);

					// Gain points 
					this->points += 1.f;
					std::cout << "Points: " << this->points << "\n";
				}

			}
		}



	}
	else
	{
		this->mouseHeld = false;
	}



}

void Game::updateText()
{
	std::stringstream ss;

	ss << "Points: " << this->points << "\n"
		<< "Health: " << this->health;

	this->uiText.setString(ss.str());
}

void Game::update()
{
	this->pollIvents();

	if (!this->getEndGame()) {
		this->updateMousePosition();
		this->updateText();
		this->updateEnemies();
	}
	// mouse position 
	// relative to the skrin
	/*std::cout << "Mouse position :: " << sf::Mouse::getPosition().x << " " << sf::Mouse::getPosition().y << "\n";*/
	// relative to the window
	/*std::cout << "Mouse position :: " << sf::Mouse::getPosition(*this->window).x << " " << sf::Mouse::getPosition(*this->window).y << "\n";*/
}

void Game::render()
{
	/*
	* @ return void
	* - clear old frame
	* - render obj
	* display frame in window
	* Renders the game object
	*/
	this->window->clear();

	// Draw game obj

	/*this->window->draw(this->enemy);*/
	this->renderEnemies(*this->window);

	this->renderText(*this->window);

	this->window->display();
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
}

void Game::renderEnemies(sf::RenderTarget& target)
{
	// Rendering all the enemies
	for (auto& e : this->enemis)
	{
		target.draw(e);
	}
}

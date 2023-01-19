#include "jump.h"


int main() 
{
	

	character user;
	sf::Clock enemyClock;
	std::vector<enemy> enemies;
	bool gameStart = true;
	bool spawnEnemy = false;

	sf::SoundBuffer jump_buff;

	// if the jump sound file is not loaded, then print out the error message.
	if (!jump_buff.loadFromFile("jump.wav")) 
	{
		std::cerr << "Could not load sound" << '\n';
	}
	sf::Sound jump_sound;
	jump_sound.setBuffer(jump_buff);

	sf::SoundBuffer hit_buff;

	// if the hit_buff couldn't load the hit sound, then print out the error message.
	if (!hit_buff.loadFromFile("hit.wav")) 
	{
		std::cerr << "Could not load sound" << '\n';
	}

	sf::Sound hit_sound;
	hit_sound.setBuffer(hit_buff);

	// Represents width of the window
	constexpr float window_width = 450.f;
	// Represents height of the window
	constexpr float window_height = 100.f;
	
	// setting the white ground on the window object.
	sf::RectangleShape ground(sf::Vector2f(window_width, window_height / 6));
	ground.setFillColor(sf::Color::White);
	ground.setPosition(0, 5 * window_height / 6);
	
	
	// Creates the window using the given size and title
	sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Jumping Game");
	// Ensures a full reading of all events
	
	// while the window is opened, then keep the loop is running.
	while (window.isOpen()) 
	{
		sf::Event e;

		// asks for event from queue
		while (window.pollEvent(e)) 
		{
			// if the user try to close the window, then close the window.
			if (e.type == sf::Event::Closed) 
			{
				window.close();
			}

			// if the user pressed the key then run this statement.
			if (e.type == sf::Event::KeyPressed) 
			{
				// since any key is pressed, it will start the game.
				user.game_started();

				// if the user pressed the up key, then call the jump function to set the clock and enable the jump_action() and make the jump sound.
				if (e.key.code == sf::Keyboard::Up) 
				{
					user.jump();
					jump_sound.play();
				}
			}
		}

		// set the background as black.
		window.clear(sf::Color::Black);

		// Enemy Spawn Code, if the user is in game, then run this statement
		if (user.inGame()) 
		{
			bool clearEnemies = false;
			
			// if the game is in the very beginning, run this code.
			if (gameStart) 
			{
				// auto spawn an enemy + start timer
				enemyClock.restart();
				enemy newEnemy;
				enemies.push_back(newEnemy);
				gameStart = false;
			}
			else // otherwise, if the user is in the middle of the game, then run this code.
			{
				// spawn if enemy timer is good + restart
				// if the enemy clock has passed 1.5 seconds, then spawn the enemy in 50 50 chance.
				if (enemyClock.getElapsedTime().asSeconds() > 1.5) 
				{
					int rand = std::rand() % 100;
					spawnEnemy = (rand) < 50;
					
					// if the enemy has to be spawn, then insert the new enemy object into the vector.
					if (spawnEnemy) 
					{
						enemy newEnemy;
						enemies.push_back(newEnemy);
					}
					enemyClock.restart();
				}
			}

			// Check for any gone enemies and remove.
			// run this loop untile the iterator reaches the end of the vector.
			for (auto it = enemies.begin(); it != enemies.end();)
			{
				// if the enemy object is out of the frame, then erase the enemy object and raise the game score.
				if ((*it).isDead()) 
				{
					it = enemies.erase(it);
					user.add_point();
				}
				else // otherwise, move onto the different iterator in the vector. 
				{
					++it;
				}
			}

			// Draw all the enemies
			// run this loop until the iterator reaches the end of the vector, and keep move the enemy objects to the left. 
			for (auto it = enemies.begin(); it != enemies.end();)
			{
				(*it).move();
				(*it).display(window);
				++it;
			}

			// Detect if there is user + enemy contact
			// run this loop until the iterator reaches the end of the vector.
			for (auto it = enemies.begin(); it != enemies.end();)
			{
				/*
				if the enemy object is detect the collision, then play the hit sound and increment the death count. 
				after the hit then erase the enemy object.
				 */
				if ((*it).detect(user)) 
				{
					hit_sound.play();
					// reset the game but add a counter to the user -> to tell when game is over
					user.died();
					it = enemies.erase(it);
				}

				// if there is at least more than one element in the enemies, then move onto the next iterator.
				if (enemies.size() > 0) 
				{
					++it;
				}
			}

			// if the user's death count goes over than 3 times, then end the game, and clear all the enemy in the queue.
			if (user.is_dead()) 
			{
				user.end_game();
				clearEnemies = true;
			}

			// clear all elements in the enemies vector.
			if (clearEnemies) 
			{
				enemies.clear();
			}

		}

		window.draw(ground);
		user.display(window);

		window.display();
	}

	

	return 0;
}

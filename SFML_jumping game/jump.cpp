#include "jump.h"
	
	// the default constructor definition for the character class
	character::character() 
	{
		/*
		this basically sets the size of the rectangle and square, and place the rectangle above the white ground and
		set the square above the rectangle object. after the process is done then fill the color with reds and set the clock.
		*/
		square = sf::RectangleShape(sf::Vector2f(length, length));
		rectangle = sf::RectangleShape(sf::Vector2f(3 * length, length));
		rectangle.setPosition(0, 4 * length);
		starting_position = rectangle.getPosition();
		square.setPosition(starting_position.x + length, starting_position.y - length);
		square.setFillColor(sf::Color::Red);
		rectangle.setFillColor(sf::Color::Red);
		clock = sf::Clock();
	}

	// the display definition of the character class
	void character::display(sf::RenderWindow& window) 
	{
		// draw the chracter object
		window.draw(square);
		window.draw(rectangle);

		// if the game is not played nor the game is not ended then print out the initial message.
		if (!is_playing && !after) {
			sf::Text msg;
			sf::Font font;

			// if the compiler couldn't load the font then throw the error and print out the error message.
			if (!font.loadFromFile("sansation.ttf")) {
				throw std::runtime_error("Could not load font");
			}
			msg.setFont(font);
			msg.setCharacterSize(20);
			msg.setFillColor(sf::Color::White);
			msg.setString("Press any key to begin.\nPress Up to jump.\nGet hit 3 times and lose.");
			window.draw(msg);
		}

		// if the user is in game then print out the score board 
		if (is_playing) {
			sf::Text msg;
			sf::Font font;
			if (!font.loadFromFile("sansation.ttf")) {
				throw std::runtime_error("Could not load font");
			}
			msg.setFont(font);
			msg.setCharacterSize(20);
			msg.setFillColor(sf::Color::White);
			msg.setString("Score: " + std::to_string(score));
			window.draw(msg);
		}

		// if the game is ended, then print out the Game over message.
		if (!is_playing && after) {
			sf::Text msg;
			sf::Font font;

			// if the compiler couldn't load the font, then throw out the error and print out the error message.
			if (!font.loadFromFile("sansation.ttf")) {
				throw std::runtime_error("Could not load font");
			}
			msg.setFont(font);
			msg.setCharacterSize(20);
			msg.setFillColor(sf::Color::White);
			msg.setString("Score: " + std::to_string(score) + "  Game Over.");
			window.draw(msg);
		}
		jump_action();
	}

	// the definition of the game_started function.
	void character::game_started() {
		is_playing = true;
		after = true;
	}

	// the definition of the jump_action()
	void character::jump_action() 
	{
		const float my_x = rectangle.getPosition().x;
		float h;

		// if the character object is jumping, and the timer is less than 1.1 second then run the code inside.
		if (moving && clock.getElapsedTime().asSeconds() < T_star) 
		{
			const float t = clock.getElapsedTime().asSeconds();
			// if the timer goes over 1 second, then set the height as zero.
			if (t > T) 
			{
				h = 0;
			}
			else // otherwise, if the timer is less than 1 seconds then set the height of the object according to the fomula described in the hw instruction. 
			{
				h = 8 * t * (T - t) * length / (T * T);
			}
			update_position(my_x, currHeight - h);
		}
		else // if the clock goes over 1.1 seconds then don't make it jump anymore. 
		{
			moving = false;
		}
	}

	// definition of the update_position()
	void character::update_position(const float& x, const float& y) 
	{
		rectangle.setPosition(x, y);
		square.setPosition(x + length, y - length);
	}

	// definition of jump()
	void character::jump() 
	{
		// if the timer goes over than 1.1 seconds, restart the clock and re-enables the moving boolean to let the user use to jump again.
		if (clock.getElapsedTime().asSeconds() > T_star) 
		{
			clock.restart();
			moving = true;
			currHeight = rectangle.getPosition().y;
		}
	}

	// definition of the inGame()
	const bool& character::inGame() 
	{
		return is_playing;
	}

	// definition of the give_x()
	const float& character::give_x() {
		return rectangle.getPosition().x;
	}

	// definition of function getting y-coordinate of the rectangle 
	const float& character::give_y() 
	{
		return rectangle.getPosition().y;
	}

	// definition of function getting the length of the square.
	const float& character::give_side() 
	{
		return length;
	}

	// definition of the function increament the death score and reset the character object's position.
	void character::died()
	{
		update_position(starting_position.x, starting_position.y);
		++deaths;
	}

	// definition of the function checking the death counts and return the boolean that decides the game should continue.
	const bool& character::is_dead() {
		return deaths >= 3;
	}

	// definition of the funtion adding score everytime the character does not hit the enemy object.
	void character::add_point() {
		++score;
	}

	// definition of the function ending the game.
	void character::end_game() 
	{
		is_playing = false;
	}




	// default construct definition for the enemy class
	enemy::enemy()
	{
		/*
			this constructor create and defines the size of the enemy_square object and once it is defined,
			the constructor will place the object on the right bottom corner of the window, and start the clock
			for moving the enemy object.
		*/
		enemy_square = sf::RectangleShape(sf::Vector2f(length, length));
		clock = sf::Clock();
		enemy_square.setFillColor(sf::Color::Yellow);
		starting_position = sf::Vector2f(450.f, 4 * length);
		enemy_square.setPosition(starting_position);
	}

	// display definition for the enemy class
	void enemy::display(sf::RenderWindow& window) 
	{
		// draws the enemy object on the window
		window.draw(enemy_square);
		move_action();
	}

	// definition of the move_action for the enemy object
	void enemy::move_action() 
	{
		float my_y = enemy_square.getPosition().y;

		// if the enemy clock timer indicate less than 0.01 seconds then move the enemy object to the left by 2 pixels
		if (enemy_moving && clock.getElapsedTime().asSeconds() < 0.01) 
		{
			enemy_square.setPosition(current_x - 2, my_y);
		}
		else // otherwise if the timer has passed over 0.01 seconds then, deactive the enemy motion.
		{
			enemy_moving = false;
		}
	}

	// definition of the move function for enemy object
	void enemy::move() 
	{
		// if the timer goes over 0.01 seconds, then reset the clock and activate the enemy_moving to re-enable the move_action() function.
		if (clock.getElapsedTime().asSeconds() > 0.01) 
		{
			clock.restart();
			enemy_moving = true;
			current_x = enemy_square.getPosition().x;
		}
	}

	// definition of the function that checks the enemy should be removed.
	const bool& enemy::isDead() 
	{
		// if the enemy object is out of the window frame, then return true.
		if (enemy_square.getPosition().x <= -length) 
		{
			return true;
		}
		else // otherwise if the enemy object is still in the window frame, then return false. 
		{
			return false;
		}

	}

	// definition of the detecting the collision between the enemy and character object
	const bool& enemy::detect(character& user) 
	{
		int x_l = user.give_x();
		int y_l = user.give_y();
		int l = user.give_side();

		int u_l = enemy_square.getPosition().x;
		int v_l = enemy_square.getPosition().y;

		bool cond1 = x_l < u_l + length;
		bool cond2 = x_l + (l * 3) > u_l;
		bool cond3 = y_l < v_l + length;
		bool cond4 = y_l + (l) > v_l;

		// if the four conditions are all happening, then return true to process the collision.
		if (cond1 && cond2 && cond3 && cond4) 
		{
			return true;
		}
		else // otherwise, nothing happened, therefore return false.
		{
			return false;
		}
	}

#ifndef JUMP_H
#define JUMP_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>


/**
	@class character : the class character defines the chracter object using the constructor functions. character class hosts the shape of the object,
	locations of the character object to be placed when the user starts the game, and scores, jump actions etc.

*/
class character
{
public:

	/**
	this is the constructor creates the shapes of rectangle, and shapes of the square. after the shapes are defined, then the constructor will set the
	positions of the rectangle and the square based on the where the rectangle is located. the square will be set in the middle of the rectangle, and after
	the setting the postion is done, then it will color two shapes at the end.

	*/
	character();

	/**
	this function is designed to set up the images of the chracter objects, and based on the status of the game play, it will decided to show
	which message should be printed out. if the user is in the middle of the game, it will shows the current score and call the jump_action() function 
	to decided that the chracter jumps.

	@param window: the window objects is needed to print out the messages based on the status of the game play.
	*/
	void display(sf::RenderWindow& window);


	/**
	this function is the function that puts the flags to let the program knows that the game is started. 
	once the function is called then it will enables the is_playing and after variables.
	*/
	void game_started();

	/**
	this function is designed to set the course of actions when the character is jumped. when the function detects the chracter is moving upward,
	then time interval between 0 ~ 1 seconds, the character object's motion will behave like a trajectory, and after the 1 second passed,
	then the height of the chracter will land on the ground.

	*/
	void jump_action();


	/**
	this function will enables to change the position of the character object as what parameter user passed. once the paramter is passed,
	then the function will change the position of the square and the rectangle separately.

	@param x: is the position of the x that where the users wants to update.
	@param y: is the position of the y that where the users wants to update. 
	*/
	void update_position(const float& x, const float& y);

	/**
	this function will check the time, and make sure reset the time when the clock hits 1.1 seconds, 
	and reset the initial height again before the jump_action() is called.

	*/
	void jump();

	/**
	this function will obtain the position of character object in x-axis of window_object.

	@return the location of the x-coordinate of the chracter object.
	*/
	const float& give_x();

	/**
	this function will return the is_playing, which is the status of game play is whether the game is in progress or is ended.

	@return is the status of the game play.
	*/
	const bool& inGame();

	/**
	this function will obtain the position of the character object in y-axis of window_object.

	@return the location of the y-coordinate of the chracter object.
	*/
	const float& give_y();

	/**
	this function will returns the length of the square side.

	@return length is the one side of the square object
	*/
	const float& give_side();

	/**
	this function will be initiated when the character object hits the enemy object. when this function is called, then it will reset the chracter's
	starting position, and increase the death score.

	*/
	void died();

	/**
	this function will be initiated to count the death score of the character object, if the death score is more than 3 points, then return true,
	or otherwise if the death score is less than 3 points then return false so it can keep the program runs.

	@return boolean value, when the chracter dies more than 3 times, return true, otherwise return false.
	*/
	const bool& is_dead();

	/**
	this is the helper function when the character objects jump over the enemy object successfully, this function will be initiated
	to raise the score of the game play.

	*/
	void add_point();

	/**
	this is the helper function and it is initiated when the is_dead() function returns the true, which means that the chracter objects hits 
	the enemy object more than 3 times. when this function is called, then it will disable the is_playing variable to stop the game play.

	*/
	void end_game();




private:

	static constexpr float T = 1.f;
	static constexpr float T_star = 1.1;
	static constexpr float length = 100.f / 6;
	sf::Vector2f starting_position;
	sf::RectangleShape square;
	sf::RectangleShape rectangle;
	sf::Clock clock;
	bool moving = false;
	float currHeight = 0;
	bool is_playing = false;
	int deaths = 0;
	int score = 0;
	bool after = false;


};

/**
	@class enemy: this class enemy create and defines the enemy object. once the enemy object is created, also the enemy class will move the enemy object
	,and displays the enemy object on the window, and let the program know that if the collision is happended. and it is also hosts the flag that when the 
	enemy object should be removed.

*/
class enemy
{
public:

	/**
	this is the default constructor of the enemy class, that create and define the shape, size of the enemy object.
	once the function create the enemy object and set the size, then it will set the starting postion at the right bottom corner of the window object.

	*/
	enemy();

	/**
	this is the function actually displays the image of the enemy object. the function will set the enemy object on the window,
	and will call the move_action() function to let the enemy object move after it is created.

	@param window: is the winodw object that the user wants to display the enemy object on the window.
	*/
	void display(sf::RenderWindow& window);

	/**
	this is the function that moves the enemy object to the left by 2 pixels every 0.01 seconds, 
	once after the enemy object is created and it is positioned on the right bottom corner of the window object. 

	*/
	void move_action();

	/**
	this function will be initiated when the enemy clock passed 0.01 seconds and when the enemy object is not deleted,
	then this function will restart the clock so the clock can enables the move_action() function again to let the enemy object keep moving.

	*/
	void move();

	/**
	this function is the helping function checking that the enemy object is out of window frame. 
	if the enemy object is out of frame, then return true, otherwise return false.

	@return boolean value, true when the object is out of frame by 100.f/6 or false otherwise.
	*/
	const bool& isDead();

	/**
	this is the help function that detects whether there is a colision happens between the chracter object and enemy object.
	once the function initialize the values, it will goes through the 4 conditions to make sure there is no collisions.

	condition 1: is the x-coordinates of the enemy's object in the range of the character object's x-coordinate?

	condition 2: is the x-coordinates of the enemy's object is placed on the inbound of the length of the rectangle?

	condition 3: is the y-coordinates of the user's character is now placed lower than the enemy's object?

	condition 4: is the upper side of the user's character is placed higher than the y-coordinates of the enemy object?

	if those 4 conditions were satisfied at once, then collision happend, otherwise, the collision is not happened.

	@param user: is the user's character object to retrive the length and the height of the character object.
	@return true if those four conditions are true, false otherwise. 
	*/
	const bool& detect(character& user);

private:

	static constexpr float length = 100.f / 6;
	sf::RectangleShape enemy_square;
	sf::Clock clock;
	sf::Vector2f starting_position;
	bool enemy_moving = false;
	float current_x = 0;
};


#endif

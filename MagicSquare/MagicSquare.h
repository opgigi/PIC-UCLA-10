#ifndef _MAGIC_SQUARE_
#define _MAGIC_SQUARE_

#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_set>
#include <string>

/**
@class MagicSqaure: the class MagicSquare is designed to find all the possible solution of the nxn square matirx.
class has all the member variable in private. square is the 2d vector, and all the member function will manage the square
to initialize and detect that the possibilty of the solution and finds all the available solution per user_input.

used_up is the unordered_set variable stores the int values to let the compiler knows and prevent using the same variable
while it insert the value in the slot in nxn square matrix.

variable solution is the total numbers of solution available as given input.

*/
class MagicSquare 
{
private:
	// 2d vector 
	std::vector<std::vector<int>> square;
	// the set variable stores that the value already used in the nxn square matrix
	std::unordered_set<int> used_up;
	// total numbers of solution 
	size_t solution = 0;

public:
	/**
	Default Constructor that accepts size this constructor will initialize the total number of solution as 0, after 
	this creates the 1d vector filled with zeros, then fill the 1d vector in each row of the 2d vector.
	eventually, this will initialize every single slot of 2d vector as zero. 
	@param size_t size: the size of the square
	*/
	MagicSquare(const size_t& size);


	/**
	Checks if a given position in the square is empty 
	@param size_t row: the row of the  nxn square matrix 
 	@param size_t column: the column of the nxn square matrix
	@return: this funtion will return boolean value, if the given position is filled with 0, then return true as the slot is empty, otherwise return false.
	*/
	bool empty(const size_t& row, const size_t& column);


	/**
	Checks if a given number is already used in the nxn magic square. loops will run and check every slots in the magic square and 
	checks that any slot in the magic square has the same value as given number as passed by parameter.
	@param const int& num: the given number wants to be checked if it is anywhere in the nxn magic square
	@return: this function will return boolean value, if the given number is taken then return true, otherwise false.
	*/
	bool taken(const int& num);



	/**
	Checks if the square could potentially be a valid solution by checking row sum and also the any column sum doesn't exceed magicsquare number
	@param const size_t row: the targeted row that to check the sum of specific row.
	@return: this function will return the boolean value, if conditions for targeted row sum or the sum of column is satisfied then return true.
	or otherwise return false.
	*/
	bool checkRow(const size_t& row) const;


	/**
	This function checks if a complete magic square satisfies the proper conditions to be a solution
	first, the check vaild function will calculate the formula what the magic square number should be.
	and the function will check sums of each row of 2d vector that each row sum is equivalent to the magic square number.
	if any sums of diagonal, row, or column is not eqaul to magic square number, then return false.
	@return: true if square is valid, false if not
	*/
	bool checkValid() const;

	
	/**
	Accesses the 2d vector, square
	@return: reference to the square
	*/
	std::vector<std::vector<int>>& get_square();


	/**
	this function is for solving the magic square and finds all the possible solution in nxn magic square matrix in a recursive way.
	(please see the MagicSquare.cpp file to check the detailed description for the algorithm)
	@param size_t num: this is the index tracking the number of slots we already considered in the recursion
	 */
	void solveSquare(size_t num);

	/**
	 this is the function gets the total number of possible magic square solution after the solvesquare 
	 funtion is done finding all the solutions.
	 @return size_t solution: total number of solution of nxn case.
	 */
	const size_t& get_solution() const;
};


/**
This is an overloaded operator>> reads from a stream into a vector <vector<int>> that will appropriately process the user's input
@param vector<vector<int>>& matrix: is a vector<vector<int>> storing the the magic square matrix
@param istream& in: is an input stream of the magic square matrix, entered row by row with enteries separated by spaces, rows separated by [enter] and * signifying that the value does not matter
@return: an input stream of the inputted matrix
*/
std::istream& operator>>(std::istream& in, std::vector<std::vector<int>>& matrix);


/**
Operator >> to read from a stream into a MagicSquare class
@param istream& in: the input stream
@param MagicSquare& ms: the MagicSquare class
@return the input stream
*/
std::istream& operator>>(std::istream& in, MagicSquare& magic_square);


/**
this is the overloaded operator<< writes a std::vector< std::vector<int>> with an output stream in the format demonstrated
@param ostream& out: an output stream of the magic square in demonstrated matrix format
@param vector<vector<int>>& matrix: is a vector<vector<int>> storing the the magic square matrix
@return: the output stream, printing out the matrix
*/
std::ostream& operator<<(std::ostream& out, std::vector<std::vector<int>>& matirx);


/**
Operator << to write a MagicSquare class into output stream
@param out the output stream
@param magic_square: is the MagicSquare class
@return: the output stream
*/
std::ostream& operator<<(std::ostream& out, MagicSquare& magic_square);


#endif

#include "MagicSquare.h"
using std::cout;

int main() {

	cout << "Enter a square size: ";
	size_t size = 0;
	std::cin >> size;

	// check that if the size is negative or equal to zero then keep repeat the loops until the user put the right input
	while (size <= 0) 
	{
		cout << "Invalid input. Enter a different size: ";
		std::cin >> size;
	}

	std::cin.ignore();
	//using constructor initializes and creat 2d vector
	MagicSquare mSquare(size);

	// getting a input from user
	cout << "Enter a square format:" << '\n';
	std::cin >> mSquare;

	//solve square 
	mSquare.solveSquare(0);

	// printing out how many total possible solution is exist
	cout << "Solving complete!" << '\n';
	cout << "There were " << mSquare.get_solution() << " solutions!" << '\n';


	return 0;
}

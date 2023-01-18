#include "MagicSquare.h"

// this is the default construct of the MagicSqaure class
MagicSquare::MagicSquare(const size_t& size) : solution(0) 
{
	// runs the loop with the repetition size of the row in the nxn square matrix.
	for (size_t i = 0; i < size; ++i) 
	{ 
		std::vector<int> temp = {};
		
		// runs the loop with the repetition size of the column in the nxn square matrix.
		for (size_t j = 0; j < size; ++j) 
		{ 
			temp.push_back(0); // while the loop is running then the vector temp will be filled with zeros in the size of column in the nxn matrix.
		}
		square.push_back(temp); // then fills every row with 1d vectors in each row of the nxn square matrix
	}
}


bool MagicSquare::empty(const size_t& row, const size_t& column) 
{
	
	// if the currntly slot is empty, which means that, fills with 0, then return true
	if (square[row][column] == 0) 
	{
		return true;
	}
	else // otherwise, then return false, because the slot is occupied with some number currently.
	{
		return false;
	}
}


bool MagicSquare::taken(const int& num) 
{
	// run this loop with repetitions the size of the row in nxn square matrix
	for (size_t i = 0; i < square.size(); ++i) 
	{
		// run this loop with the repetition of the size of column in nxn square matrix 
		for (size_t j = 0; j < square.size(); ++j) 
		{
			// if the number is located in the somewhere in the nxn square matrix then return true
			if (square[i][j] == num) 
			{
				return true;
			}
		}
	}
	// if the num is not currently assigned in any slots in the nxn square matrix then return false.
	return false;
}


bool MagicSquare::checkRow(const size_t& num) const 
{
	
	// this is the formula of the magic square number in every case of nxn square matrix
	const int SumofFlag = square.size() * ((static_cast<double>((square.size() * square.size()) + 1)) / 2);
	
	int sum = 0;
	
	// if the "row" is bigger than square.size(), the number is converted to the actual row
	size_t row_converted = (num / square.size()) - 1;

	// run the loop with the repetition of the size of column in nxn square matrix
	for (size_t i = 0; i < square.size(); ++i) 
	{	
		//since we only want to check the targeted row of sum, thus we will only store the sum of the targeted row
		sum += square[row_converted][i];
	}

	// if the sum of targeted row is not equal to the magicsquare number then return false.
	if (sum != SumofFlag) 
	{
		return false;
	}

	// runs the loop with the repetitions of the size of column of the nxn square matrix
	for (size_t i = 0; i < square.size(); ++i) 
	{
		sum = 0;

		// runs the loop with the repetition of the size of row in the nxn square matrix
		for (size_t j = 0; j < square.size(); ++j) 
		{
			sum += square[j][i]; // add each element of the each column in the nxn square matrix
		}

		// if the any sum of every column in the nxn square matrix is greater then the magicsquare number,
		// then it automatically fails the condition of the solution of magicsquare, thus return false.
		if (sum > SumofFlag) 
		{
			return false;
		}
	}

	// if the sum of targeted row is eqaul to the magicsquare number
	// and the every sum of each column in the nxn square matrix is less than the magicsquare number then it is qualified for being a possible solution.
	return true;
}


bool MagicSquare::checkValid() const 
{

	// magic square number formula described in the hw instruction
	const int SumofFlag = square.size() * ((static_cast<double>((square.size() * square.size()) + 1)) / 2);

	int sum = 0;

	// run the loop with repetition of total number of the row in the nxn square
	for (size_t i = 0; i < square.size(); ++i) 
	{
		sum = 0;
		// run the loop with the repetition of total number of the column in the nxn square
		for (size_t j = 0; j < square.size(); ++j) 
		{
			sum += square[i][j]; // add each element in the row and store it in to sum. 
		}

		// if the sum of each line is not equal to the magicsquare number then it automatically fails the condition of solution.
		if (sum != SumofFlag) 
		{
			return false;
		}
	}


	sum = 0;

	//run the loop with the repetition of total number of the column in the nxn square 
	for (size_t i = 0; i < square.size(); ++i) 
	{
		sum = 0;
		// run the loop with the repetition of the total number of the row in the nxn square 
		for (size_t j = 0; j < square.size(); ++j) 
		{
			sum += square[j][i]; // store each element in the column into the sum. 
		}
		
		// check that each sums of every column is equal to the magicsquare number
		// if the sum is not the same as magicsquare number then return false.
		if (sum != SumofFlag) 
		{
			return false;
		}
	}


	sum = 0;
	
	// run the loop with repetitions of the size of diagonal in the nxn square
	for (size_t i = 0; i < square.size(); ++i) 
	{
		sum += square[i][i]; // add each and every element in the diagonal from left top to the bottom right of the nxn square.
	}

	// if the sum of diagonal from left top to the right bottom is not equal to the magicsquare number then return false. 
	if (sum != SumofFlag) 
	{
		return false;
	}

	
	sum = 0;
	
	// run the loop with the repetition of the size of diagonal line in the nxn square
	for (size_t i = 0; i < square.size(); ++i) 
	{
		// adds each element on the diagonal from top right to the bottom left corner.
		sum += square[i][square.size() - 1 - i];
	}

	// if the sum of diagonal is not equal to the magic square number, then return false.
	if (sum != SumofFlag) 
	{
		return false;
	}
	else // else if every sum of diagonal, row and column are equal to the magicsquare number, then return true 
	{
		return true;
	}
}

// returns the square  gettor function
std::vector<std::vector<int>>& MagicSquare::get_square() 
{
	return square;
}


void MagicSquare::solveSquare(size_t num) 
{
	
	//total number of slots in nxn matrix is equal to the size of the multiplications of the two sides of square
	size_t total_slot = square.size() * square.size();

	// first, if the index num is at the very first position, then proceed to do the code inside of the this if-statment.
	if (num == 0) 
	{ 
		
		// doing the loop until this checks the whole available index.
		for (size_t n = 0; n <= total_slot; ++n) 
		{ 
			
			// if the number n is already used in the magic square then store the number inside the set used_up to denote that this number is already taken.
			if (taken(n)) 
			{
				used_up.insert(n);
			}
		}

		//if the loops are done checking the whole index that whether the number is taken or not, then proceed to the next index
		solveSquare(num + 1);
	}
	// else if the index num is going over the total size of the matrix, then proceed and run the code inside.
	else if (num == total_slot + 1) 
	{
		
		//if the index num is going over than the given total numbers of slots in the vector, that means that they already finished to fill up all the slots in the matrix.
		// if the filled matrix is the solution of the magicsquare then print out the solution and increment the total number of solution.
		if (checkValid()) 
		{  
			std::cout << square << '\n';
			++solution;
		}
	}
	// else if the index num is in the somewhere in the middle between the end and the beggining then proceed and run the code inside of the if-statment.
	// while still going through the slots
	else if (num < total_slot + 1) 
	{ 
		
		//if the index num is not the second position but the num is in the same column as second position of the vector,
		//it means that one of the rows are filled and it need to be ched that if that can be the possible solution.
		if ((num != 1) && (num % square.size() == 1)) 
		{
			
			// if the checkrow says that the if the matrix can be the possible solution then skip this 
			// but if whether the sums of row and the sums of column is more than the formula of the magic square number,
			// then use the recursive method and forward that to the solvesuqare(total_slot + 1) and checks the solution.
			if (!checkRow(num)) 
			{
				solveSquare(total_slot + 1);
				return;
			}
		}

		//then adapt the index num in the 2d vector index, so I convert the index into row and column position.
		const size_t ROW = (num - 1) / square.size(); // the row of the num in the current spot
		const size_t COLUMN = (num - 1) % square.size(); // the column of the num(th) slot

		// if the current index is empty, which means that the current slot is equal to zero then run the code inside.
		if (empty(ROW, COLUMN)) 
		{
			
			// run this loops with n times n repetition 
			for (size_t n = 0; n <= total_slot; ++n) 
			{
				//if the compiler finds the number n, which is not taken,  
				// then we will insert the number n into the current slot of 2d vector.
				if (!taken(n)) 
				{
					square[ROW][COLUMN] = n;

					// after the number n is stored into the 2d vector then store the information in the set to denote the number is taken now.
					used_up.insert(n); 

					// then move onto the next index. until it finds the solution.
					solveSquare(num + 1);

					square[ROW][COLUMN] = 0;
					used_up.erase(n);
				}
			}
		}
		else // if the position is not empty
		{ 
			solveSquare(num + 1); // skips over the current slot and goes to check the next
		}
	}
}


//get function for solution counter
const size_t& MagicSquare::get_solution() const 
{
	return solution;
}

// operator >> for 2d vector
std::istream& operator>>(std::istream& in, std::vector<std::vector<int>>& matirx) 
{
	
	
	/* key mechanism is that the compiler keep reads some meaningful input to store number in the nxn square
	until it reaches the end of the buffer. once it catches the meaningful input (such as '*' or int numbers)
	then int count will track how many int was stored by user input in the first place.
	*/
	
	// runs the loop with the repetition size of the side of the nxn square matrix
	for (size_t i = 0; i < matirx.size(); ++i) 
	{
		std::string format = "";
		std::getline(in, format); // user formats each line

		int count = 0; // counts how many ints in a vector of v (this resets to 0 after each input)
		std::string num = "";

		// loops will run until it reaches to the end of the string input, format.
		for (size_t j = 0; j < format.length(); ++j) 
		{
			// if the string catches the character * or ' ' then proceed to run the code inside.
			if ((format[j] == '*') || (format[j] == ' ')) 
			{
				
				// if the string catches the astrisks '*' that means that it catches the 0, thus compiler will raise the number of the int input stored 
				if (format[j] == '*') 
				{
					++count;
					num = ""; // resets num
				}
				else // if a character is a space ' ' then  
				{ 
					
					// if num is not empty then it means num has some int input other than 0
					if (num != "") 
					{
						//then get the int input from int_buffer
						std::stringstream int_buffer(num);
						
						int x = 0;
						
						//and once the int_buffer gets the input then store into the nxn square matrix in the designated position
						int_buffer >> x;
						matirx[i][count] = x;
						++count;
						num = "";
					}
				}
			}
			//case when the character is a number
			else 
			{
				num += format[j];
			}

			// if the compiler reaches to the end of the istream in, and also reads something other than astrisks '*', which is 0,
			// that means the last input what the compiler gets is the int number.
			if ((j == format.length() - 1) && (format[j] != '*')) 
			{
				std::stringstream s(num);
				int x = 0;
				s >> x;
				// store the last int input in the nxn matrix.
				matirx[i][count] = x;
			}
		}
	}
	return in; // returns an inputsStream
}


std::istream& operator>>(std::istream& in, MagicSquare& magic_square) 
{
	return in >> magic_square.get_square();
}

// Operator << for vector
std::ostream& operator<<(std::ostream& out, std::vector<std::vector<int>>& matirx) 
{
	
	// run the loops with the repetitions the size of the row in the nxn square matrix
	for (size_t i = 0; i < matirx.size(); ++i) 
	{
		// run the loops with the repetitions the size of how many 1d vector stored in each row in nxn square matrix.
		for (size_t j = 0; j < matirx[i].size(); ++j) 
		{
			//prints out each value in every slot of nxn square matrix
			out << matirx[i][j] << ' ';
		}
		out << '\n';
	}
	return out; // returns an output stream
}


std::ostream& operator<<(std::ostream& out, MagicSquare& magic_square) 
{
	return out << magic_square.get_square(); // returns output stream
}

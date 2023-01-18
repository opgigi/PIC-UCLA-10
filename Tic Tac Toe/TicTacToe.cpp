#include <iostream>
#include <string>
#include <cmath>
#include <cassert>

using namespace std;

char Placement[3][3] = {' '};
int winning_cases_player1();
int winning_cases_player2();
void clear_the_board();

/*******************************************************************
	 CLASS OBJECTS FOR THE PLAYER 1 FOR TIC TAC TOE
********************************************************************/

class Player1 {
private:
	string name; // name of player 1
	unsigned int winning_scores; // this is the scores for how many rounds the player 1 won.

public:
	//Constructor

	unsigned int row_coordination; // coordination of row where the player 2 wants to place the mark
	unsigned int col_coordination; // coordination of column where the player 2 wants to place the mark

	unsigned int proceed_turns;

	Player1() : winning_scores(0) {};

	void get_playername() // this memberfunction will get the name of the player 1
	{
		
		cin >> name;
	}

	void winning_score() // this will raise the scores of the player 1 has
	{
		winning_scores++;
	}

	unsigned int point_display() // this allows the access of the winning scores of player 1
	{
		return winning_scores;
	}

	string name_display() // this allows the access of the name of the player 1
	{
		return name;
	}

	void get_coordinate() // this allows to access the coordination variables and edit the value
	{
		
		cin >> row_coordination >> col_coordination;
		row_coordination--;
		col_coordination--;
		
	}


};

/*******************************************************************
	 CLASS OBJECT FOR PLAYER 2
********************************************************************/

class Player2 {
private:
	string name; // name of player 2
	unsigned int winning_scores; // this is the scores for how many rounds the player 2 won.

public:
	//Constructor

	unsigned int row_coordination; // coordination of row where the player 2 wants to place the mark
	unsigned int col_coordination; // coordination of column where the player 2 wants to place the mark

	unsigned int proceed_turns;

	Player2() : winning_scores(0) {};

	void get_playername() // this allows us to input the name of the player 2
	{			
		cin >> name;
	}

	void winning_score() // this will raise the scores of the player 2
	{
		winning_scores++;
	}

	unsigned int point_display() // this allows the access of the scores what player 2 has
	{
		return winning_scores;
	}

	void get_coordinate() // this allows the access of the coordinations and edit the value
	{
		cin >> row_coordination >> col_coordination;
		row_coordination--;
		col_coordination--;
		
	}

	string name_display() // this allows the access of the name of the player 2
	{
		return name;
	}


};

void Tic_Tac_toe_board();



int main()
{
	unsigned int round_limit;
	int i = 2;
	Player1 number1;
	Player2 number2;
	number1.proceed_turns = 0; // We need this because it's important to tell who are supposed to take the turn while they playing the game.
	number2.proceed_turns = 0; // Also turns they played is important for telling that the game is draw round.
	bool vaild_move = true;
	
	

	cout << "This is a Tic Tac Toe game!" << endl;
	cout << "How many rounds would you like to play? ";
	cin >> round_limit;

	cout << "Please enter the name of player 1: " << endl;
	number1.get_playername();

	cout << "Please enter the name of player 2: " << endl;
	number2.get_playername();
	
	while(round_limit)
	{
		number1.proceed_turns = 0;
		number2.proceed_turns = 0;
	do
	{
		
		Tic_Tac_toe_board();

		if (number1.proceed_turns <= number2.proceed_turns)
		{
			cout << "It is " << number1.name_display() << "'s turn." << endl;
			number1.proceed_turns++;

			while (vaild_move) // if the find nothing is in the space of the char array Placement, then this will put the mark on the memory space for player 1. 
			{
				cout << "where would you like to play? Enter your row position and column position: ";
				number1.get_coordinate();
				if (Placement[number1.row_coordination][number1.col_coordination] != 'X' && Placement[number1.row_coordination][number1.col_coordination] != 'O')
				{
					Placement[number1.row_coordination][number1.col_coordination] = 'O';
					vaild_move = false;
					i = winning_cases_player1();
				}
				else
				{
					cout << "Invaild move, Please Try again" << endl;
				}
			}

			vaild_move = true;

			if (i == 1) 
			{
				Tic_Tac_toe_board();
				number1.proceed_turns = 1;
				number2.proceed_turns = 0;
				number1.winning_score();
				cout << number1.name_display() << "won the round!" << endl;
				cout << "Presently, " << number2.name_display() << " has " << number2.point_display() << " points and " << number1.name_display() << " has " << number1.point_display() << " points." << endl;
			}
		}
		else if (number1.proceed_turns > number2.proceed_turns)
		{
			cout << "It is " << number2.name_display() << "'s turn." << endl;
			number2.proceed_turns++;
			

			while (vaild_move) // if the find nothing is in the space of the char array Placement, then this will put the mark on the memory space for player 2.
			{
				cout << "where would you like to play? Enter your row position and column position: ";
				number2.get_coordinate();

				if (Placement[number2.row_coordination][number2.col_coordination] != 'O' && Placement[number2.row_coordination][number2.col_coordination] != 'X')
				{
					Placement[number2.row_coordination][number2.col_coordination] = 'X';
					vaild_move = false;
					i = winning_cases_player2();
				}
				else
				{
					cout << "Invaild move, Please try again" << endl;
					
				}
			}

			vaild_move = true;

			if (i == 1) // this is when the player 2 wins the game and recieve the winning score
			{
				Tic_Tac_toe_board();
				number1.proceed_turns = 0;
				number2.proceed_turns = 1;

				number2.winning_score();
				cout << number2.name_display() << " won the round!" << endl;
				cout << "Presently, " << number2.name_display() << "has" << number2.point_display() << " points and " << number1.name_display() << " has " << number1.point_display() << " points." << endl;
			}
		}

		if (number1.proceed_turns + number2.proceed_turns == 9) // This when the programs sees that players fills all the space in the board and draw.
		{
			number1.proceed_turns = 0;
			number2.proceed_turns = 0;

			Tic_Tac_toe_board();
			cout << "It's a draw round" << endl;
			cout << "Presently, " << number2.name_display() << " has " << number2.point_display() << " points and " << number1.name_display() << " has " << number1.point_display() << " points." << endl;
			i = 0;
		}

		

	} while (i==2);


		round_limit--;
		i = 2;
		clear_the_board();
	}

	if (number1.point_display() > number2.point_display()) // WHEN THE PLAYER 1 WINS THE WHOLE GAME
	{
		cout << endl;
		cout << "Player " << number1.name_display() << " won the game!" << endl;
	}
	else if (number1.point_display() < number2.point_display()) // WHEN THE PLAYER 2 WINS THE WHOLE GAME
	{
		cout << endl;
		cout << "Player " << number2.name_display() << " won the game!" << endl;
	}
	else // WHEN THE PLAYER 1 AND 2 HAS DRAWS THE WHOLE GAME
	{
		cout << endl;
		cout << "It is a draw!" << endl;
	}

	return 0;
}

/*****************************************************************************
	NUMBERS MEANING IN THE CONDITION OF WHILE LOOP
	1 FOR SOME PLAYER WINS THE GAME AND TAKES THE POINT
	2 FOR GAME IS STILL IN PROGRASS UNTIL IT FILLS ALL THE SPACE IN THE BOARD
	O IS FOR GAME IS DRAW
*****************************************************************************/



/*******************************************************************
	 FUNCTION TO CALCULATE THE WINNING SCINARIO OF PLAYER 1
********************************************************************/

int winning_cases_player1()
{
	if (Placement[0][0] == 'O' && Placement[0][1] == 'O' && Placement[0][2] == 'O')
	{
		return 1;
	}
	else if (Placement[1][0] == 'O' && Placement[1][1] == 'O' && Placement[1][2] == 'O')
	{
		return 1;
	}
	else if (Placement[2][0] == 'O' && Placement[2][1] == 'O' && Placement[2][2] == 'O')
	{
		return 1;
	}
	else if (Placement[0][0] == 'O' && Placement[1][0] == 'O' && Placement[2][0] == 'O')
	{
		return 1;
	}
	else if (Placement[0][1] == 'O' && Placement[1][1] == 'O' && Placement[2][1] == 'O')
	{
		return 1;
	}
	else if (Placement[0][2] == 'O' && Placement[1][2] == 'O' && Placement[2][2] == 'O')
	{
		return 1;
	}
	else if (Placement[0][0] == 'O' && Placement[1][1] == 'O' && Placement[2][2] == 'O')
	{
		return 1;
	}
	else if (Placement[0][2] == 'O' && Placement[1][1] == 'O' && Placement[2][0] == 'O')
	{
		return 1;
	}
	else
	{
		return 2;
	}
}

/*******************************************************************
	 FUNCTION TO KNOW THE WINNING MACHANISM OF PLAYER2
********************************************************************/

int winning_cases_player2()
{
	if (Placement[0][0] == 'X' && Placement[0][1] == 'X' && Placement[0][2] == 'X')
	{
		return 1;
	}
	else if (Placement[1][0] == 'X' && Placement[1][1] == 'X' && Placement[1][2] == 'X')
	{
		return 1;
	}
	else if (Placement[2][0] == 'X' && Placement[2][1] == 'X' && Placement[2][2] == 'X')
	{
		return 1;
	}
	else if (Placement[0][0] == 'X' && Placement[1][0] == 'X' && Placement[2][0] == 'X')
	{
		return 1;
	}
	else if (Placement[0][1] == 'X' && Placement[1][1] == 'X' && Placement[2][1] == 'X')
	{
		return 1;
	}
	else if (Placement[0][2] == 'X' && Placement[1][2] == 'X' && Placement[2][2] == 'X')
	{
		return 1;
	}
	else if (Placement[0][0] == 'X' && Placement[1][1] == 'X' && Placement[2][2] == 'X')
	{
		return 1;
	}
	else if (Placement[0][2] == 'X' && Placement[1][1] == 'X' && Placement[2][0] == 'X')
	{
		return 1;
	}
	else
	{
		return 2;
	}
}

/*******************************************************************
	VOID FUNCTION TO DRAW BOARD OF TIC TAC TOE AS THE PLAYER MARKS
********************************************************************/

void Tic_Tac_toe_board()
{
	cout << " 1  2  3" << endl;
	cout << "1 " << Placement[0][0] << "|" << Placement[0][1] << " |" << Placement[0][2] << endl;

	cout << "--------" << endl;
	cout << "2 " << Placement[1][0] << " |" << Placement[1][1] << " |" << Placement[1][2] << endl;

	cout << "--------" << endl;
	cout << "3 " << Placement[2][0] << " |" << Placement[2][1] << " |" << Placement[2][2] << endl;
}

/*******************************************************************
	 FUNCTION TO CLEAR THE BOARD OF TIC TAC TOE WITH PLAYERS MARK
********************************************************************/

void clear_the_board()
{
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			Placement[i][j] = ' ';
		}
	}
}

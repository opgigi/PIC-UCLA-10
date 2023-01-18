#include "SpellCheck.h"

	
	/*This is the default constructor of the class Checking_the_spell. when we declare an object in a format nothing specifies 
	its uniquness then the object will use this default constructor and unordered_set dictionary will clear every content inside the set*/
	
	Checking_the_spell::Checking_the_spell()
	{
		dictionary.clear();
	};

	  
	
	void Checking_the_spell::read_dictionary()
	{
		std::ifstream inFile;
		std::string target_word = { 0 };

		inFile.open("dictionary.txt");

		if (!inFile.is_open()) // if the file is not opened the dictionary.txt then return the fail message.
		{
			std::cout << "There was a problem opening the file.";
		}

		while (inFile >> target_word) // if the stream file reads the word from the dictionary.txt file then insert the word into the dictionary set.
		{
			dictionary.insert(target_word);
		}

		inFile.close();

	}


	// the reason why I didn't pass the parameter by reference, it's because I only want to see that the word is in vaild form and it is in the dictionary set.
	// Once this function find that the word is in vaild format and it's matching the word, then it will return true and will give an original word as an output. 
	bool Checking_the_spell::is_vaild(std::string test_word_)
	{
		// To specify that if the word has the first letter as capital letter, then this funtion will return true
		char Capital_Detector = ' ';

		
		// once the first letter is in uppercase then this will convert the first letter into lowercase
		Capital_Detector = test_word_[0];
		if (('A' <= Capital_Detector) && (Capital_Detector <= 'Z')) //if the first letter of the word is uppercase, then run the code inside the bracket.
		{
			//convert lowercase and then erase the first letter and replace the new converted letter into its first letter.
			Capital_Detector += ('a' - 'A');
			test_word_.erase(0, 1);
			test_word_.insert(0, 1, Capital_Detector);
			
			//if the word is in the dictionary set then, it will has the iterator less than ending number of the dictionary set
			std::unordered_set<std::string>::const_iterator number = dictionary.find(test_word_);
			
			if (number == dictionary.end()) // if the iteration of the word location is not found until it reaches to the end of the dictionary set then return false.
			{
				return false;
			}
			else // return ture if the iteration of the word is found before the dictionary set reaches to the end.
			{
				return true;
			}

		}
		else // when the first letter of the word is not in the uppercase, then run this code inside the bracket.
		{
			std::unordered_set<std::string>::const_iterator number = dictionary.find(test_word_);
			
			if (number == dictionary.end()) // if the iteration of the word location is not found until it reaches to the end of the dictionary set then return false.
			{
				return false;
			}
			else // return ture if the iteration of the word is found before the dictionary set reaches to the end.
			{
				return true;
			}
		}

	}

	
	void Checking_the_spell::process_file()
	{
		char punctuation_preserver = ' ';
		char white_space_detector = ' ';
		std::string word = { 0 };
		std::string file_name = { 0 };
		std::ifstream text_file_read;

		std::cout << "Enter file to spell check: ";
		std::getline(std::cin, file_name);
		text_file_read.open(file_name);

		if (!text_file_read.is_open()) // if the file stream is not opened, then returns this message.
		{
			std::cout << "There was a problem opening the file.";
		}

		while (text_file_read.peek() == '\t') // we have to catch that whether the parahgraph starts with the tab 
		{
			text_file_read.get();
			std::cout << "\t";
		}

		while (text_file_read >> word) //if the stream file reads the word from the example.txt file, then run the code inside.
		{


			if (final_punctuation(word, punctuation_preserver)) // if the word has the punctuation at the end then proceed and run the code inside
			{
				
				if (is_vaild(word)) // if the word is in vaild format and finds the match with one of the word in the dictionary set then proceed and run the code inside
				{
					word.insert(word.length(), 1, punctuation_preserver); // after the word is in vaild format, then it will insert the punctuation at the end of the word.
					std::cout << word; 
				}
				else // if the word is not in vaild format then print out the word with asterisks.
				{
					std::cout << "*" << word << "*" << punctuation_preserver;
				}
			}
			else // if the word doesn't have the punctuation at the end of the word then proceed and run the code inside.
			{
				if (is_vaild(word)) // if the word is in vaild format and finds the match with one of the word in the dictionary set then print out the word to console
				{
					std::cout << word;
				}
				else // if the word is not in vaild format or the function can't find the match with one of the word in the dictionary set then print out word with asterisks.
				{
					std::cout << "*" << word << "*";
				}
				
			}

			while (text_file_read.peek() == '\n' || text_file_read.peek() == '\t' || text_file_read.peek() == ' ') // if the stream file reads any white space character then run this.
			{
				white_space_detector = text_file_read.get();

				if (is_white_space(white_space_detector)) // if the char white_space_detector make returns true from the function is_whte_space() then run inside of if statement.
				{
					if (white_space_detector == '\n') // if white_space_detector is '\n' then proceed to next line
					{
						std::cout << "\n";
					}
					else if (white_space_detector == '\t') // if white_space_detector is '\t' then space out much as tab
					{
						std::cout << "\t";
					}
					else if (white_space_detector == ' ') // if white_space_detector is ' ' then space out as much as like ' '.
					{
						std::cout << " ";
					}
					
				}

			}
				
			
		}

		if (text_file_read.eof()) // if the stream file reads all the words inside the "example.txt" then close the stream file and print out messages. 
		{
			text_file_read.close();
			std::cout << "\n \n /******************************************************************* \n";
			std::cout << "	notification: File " << file_name << " close successfully. \n";
			std::cout << "*******************************************************************/";
		}

	}



//non-member function


bool is_white_space(char _check_whitespace)
{
	if (_check_whitespace == ' ') // if the _check_whitespace is ' ', then return true.
	{
		return true;
	}
	else if (_check_whitespace == '\t') // if the _check_whitespace is '\t', then return true.
	{
		return true;
	}
	else if (_check_whitespace == '\n') // if the _check_whitespace is '\n', then return true.
	{
		return true;
	}
	else // everything else, return false.
	{
		return false;
	}
}

// this function is about catching the punctuation at the end of the string parameter and depunctuate and then return the boolean value.
bool final_punctuation(std::string &word_with_punctuation, char &punctuation_preserve)
{
		/*As you can see, in the if statement, it is comparing its location of the punctuation with the.size() - 1,
		it's because the string .size() function also take account '\0' into its size, thus we subtract .size() by 1, to make the position equaivalent   
		between the location of .find() and .size()-1.
		*/
		if (word_with_punctuation.find('!') == word_with_punctuation.size()-1) // if word_with_punctuation has '!' at the end of the string then depunctuate and return true. 
		{
			depunctuate(word_with_punctuation, punctuation_preserve);
			return true;

		}
		else if (word_with_punctuation.find('?') == word_with_punctuation.length()-1) // if word_with_punctuation has '?' at the end of the string then depunctuate and return true.
		{
			depunctuate(word_with_punctuation, punctuation_preserve);
			return true;
		}
		else if (word_with_punctuation.find(',') == word_with_punctuation.length()-1) // if word_with_punctuation has ',' at the end of the string then depunctuate and return true.
		{
			depunctuate(word_with_punctuation, punctuation_preserve);
			return true;
		}
		else if (word_with_punctuation.find('.') == word_with_punctuation.length()-1) // if word_with_punctuation has '.' at the end of the string then depunctuate and return true.
		{
			depunctuate(word_with_punctuation, punctuation_preserve);
			return true;
		}
		else if (word_with_punctuation.find(';') == word_with_punctuation.length()-1) // if word_with_punctuation has ';' at the end of the string then depunctuate and return true.
		{
			depunctuate(word_with_punctuation, punctuation_preserve);
			return true;
		}
		else if (word_with_punctuation.find(':') == word_with_punctuation.length()-1) // if word_with_punctuation has ':' at the end of the string then depunctuate and return true.
		{
			depunctuate(word_with_punctuation, punctuation_preserve);
			return true;
		}
		else if (word_with_punctuation.find('-') == word_with_punctuation.length()-1) // if word_with_punctuation has '-' at the end of the string then depunctuate and return true.
		{
			depunctuate(word_with_punctuation, punctuation_preserve);
			return true;
		}
		else // everything else, return false.
		{
			return false;
		}
	
}

// this function will store the punctuation inside the @param punctuation_preserve, and then erase the punctuation out of the word_with_punctuation. 
void depunctuate(std::string& word_with_punctuation, char& punctuation_preserve)
{
	punctuation_preserve = word_with_punctuation[word_with_punctuation.size() - 1];
	word_with_punctuation.erase(word_with_punctuation.size() - 1, 1);

}


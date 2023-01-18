#ifndef MY_HEADER_FILE_
#define MY_HEADER_FILE_



#include <iostream>
#include <string>
#include <unordered_set>
#include <fstream>
#include <istream>
#include <cassert>

/**
@class Checking_the_spell: This class has the unordered_set dictionary as the member variable of the class. the purpose of this class is that to store all the
						   words from the dictionary.txt into the set dictionary, as the member function read_dictionary() runs. the class is also contains the function
						   to check the word is in the vaild format or not during the member function process_file() runs.
*/


class Checking_the_spell
{
private:
	// a memeber variable to store the dictionary words
	std::unordered_set<std::string> dictionary;
	

public:
	//Constructor
	
	/**
	This is the default constructor of the class Checking_the_spell. when we declare an object in a format nothing specifies
	its uniquness then the object will use this default constructor and unordered_set dictionary will clear every content inside the set
	*/
	Checking_the_spell();

	/** This funtion is designed to open the dictionary.txt file and read everything inside of the content inside the dictionary.txt
	and copy every word using the unordered_set insert function and paste into the unordered_set variable, dictionary.	
	once the while loop finishes to include all the words from the txt file, then the member funtion will closes a file stream.
	
	*/
	void read_dictionary();

	/**
	This member function, is_vaild, checks the word as a paramater of the function is whether in the set dictionary or not in the dictionary.
	This function will detect if the word is beginning with the uppercase or lowercase. if the word has the first letter as uppercase,
	then the function will convert its first letter turned into the lowercase and it will find the word matches in the dictionary set.
	otherwise, if the first letter of the word is in lowercase, then it will find a word matches in the dictionary set.
	once they find the word is matching with some word in the dictionary set, the funtion will return true value or return false.

	@param test_word_: is the string type variable originally from the stream function once the example.txt stream file is open.

	@return: it will return the true if the test_word_ is in the vaild format and if it is in the dictionary set.

	*/
	bool is_vaild(std::string test_word_);

	/**
	This member function, process_file(), reads through a text file that needs to be spellchecked and prints the checked file to the console window.
	first, this function will ask the name of the file needs to be spell checked, then once the user input the name of the .txt file.
	once the file is opened, then the stream file, text_file_read will read the word from the example.txt file and checks whether the word has the
	punctuation at the end and the word is in vaild form.

	logical step is, in case of the stream file reads the word has the punctuation at the end, then the function, final_punctuation() will depunctuate the word and then
	make the function return true. and the function depuntuate() will erase the punctuation at the end and then it will store the punctuation into the char punctuation_presetver variable
	so the char variable can retrieve the punctuation again and put the end of the word after the function is_vaild() finishes finding the match with the dictionary set.

	in the case of the stream file reads the word without punctuation at the end, then the word will go through the function is_vaild() and will find the match with the dictionary set.
	if the word is in the dictionary set then, it will print out the original word, or if the word is not in dictionary set then, it will be printed out asterisks *.

	at the end part of the function, is_white_space() will also detect the newline, '\n' , and new tab '\t', and " ", and store those white space character into the char variable
	and the stream will print out those white spaces to make the pharagraph in more organized structure.

	once the stream file reads all the content inside of the example.txt file, then the stream file will be closed.

	*/
	void process_file();

}; 

//non-member function

/**
This function will accepts the char variable and it will tell us the character is white space characters or not.
when stream file detects one of the white space variable, then we will save the stream into the character and the character will be used as the parameter of this function.
when the character is any of white space character it will returns the true and this function will help to print out the one of the white space variable on the console display.

@param _check_whitespace: this char type variable will goes through the function and will find out that the variable is matching with any of white space characters.

@return: the function will return true if they find the stream file catches the any white space character or otherwise it will return false.
*/
bool is_white_space(char _check_whitespace);


/**
This function will accept the string and char variable, and it will figure out whether the string parameter has the punctuation at the end of the word from the stream file.
the function will try to find the location of the punctuation in the string varible is whether at the end of the string or not.
once it finds out that there is a punctuation at the end of the string, then depunctuate function will be running to get rid of the punctuation at the end of the string
and stores the punctuation into the char &punctuation_preserve.

@param word_with_punctuation: this string will be originally from the stream file while the stream file reads the example.txt file word by word.
							  and since the parameter is passed by its reference, once the depunctuate funtion finishes its run, the string variable will get rid of the punctuation.

@param depunctuation_preserve: this character variable will store the punctuation when the @param word_with_punctuation has the punctuation at the end of its string.

@return this function will return true when the string parameter has the punctuation at the end, otherwise, it will return false.
*/
bool final_punctuation(std::string& word_with_punctuation, char& punctuation_preserve);



/**
This function will store the punctuation at the end of the @param word_with_punctuation into @param punctuation_preserve
and once the punctuation is stored in the @param punctuation_preserve, then the function will erase the punctuation at the end of the string parameter.

@param word_with_punctuation: this string will be originally from the stream file while the stream file reads the example.txt file word by word.
							  and since the parameter is passed by its reference, once the depunctuate funtion finishes its run, the string variable will get rid of the punctuation.

@param depunctuation_preserve: this character variable will store the punctuation when the @param word_with_punctuation has the punctuation at the end of its string.
*/
void depunctuate(std::string& word_with_punctuation, char& punctuation_preserve);


#endif /*MY_HEADER_FILE_*/

#ifndef VECTOR_STRING_
#define VECTOR_STRING_

#include <iostream>
#include <string>
#include <memory>
#include <new>




namespace pic10b{

	

class VectorString
{
private:
	size_t vec_size;
	size_t vec_capacity;
	std::string* pointer_To_Array = { 0 };

	
	

public:

	

	VectorString& operator= (const VectorString& source_from_class);

	/**
	This is the default constructor of the class, this 
	allocates a dynamic array if std::string of one element(thus, vec_capacity has to be 1 but has the vec_size of 0.)
	*/
	VectorString();

	const VectorString();

	/** 
	This constructor allocates a dynamic array twice the input size : vec_size should be set to the inputand vec_capacity is twice the input with all of the
	string variable set to the empty string
	*/
	VectorString(int size_of_vector_);

	/**
	This is the constructor accepting a size and input string value, that does the same as above with the input size and capacity, and initializes
	all the string variables to the input string
	*/

	VectorString(int size_of_insertion, std::string string_insertion);

	/**
	This is a copy constructor which it makes easier that the constructor can transfer their private variable information
	and once this information passed it to the other contructor, then they will have the same information
	
	*/
	VectorString(const VectorString &copy_string);

	/**
	This is a move constructor. which allow us to construct a new object by harvesting the resources of an rvalue
	*/
	VectorString(VectorString &&copy_string);

	/**
	This is the member function returning the size of the vector once we use this function then the size function will
	return the vec_size value. this is important because this will help us to specify the location of  each string messages, 
	and also this will tell us that whether we need to expand the capacity of the string dynamic memory.
	*/
	int size();

	/**
	This is the member function returning the capacity of the vector. once we call this function then the function will
	return the vec_capcity value.
	*/
	int capacity();

	/**
	member function accepting a std::string that adds an element to the end of the vector
	if the capacity allows and otherwise creates a new dynamic array of twice the former
	capacity, moving all the elements over and adding the new element.
	*/
	void push_back(std::string message);

	/**
	member function that removes the last element of the vector by updating its vec_size value
	the value will remain there in memory but by changing the size, you can logically overwrite
	it if there is another insertion.
	*/
	void pop_back();

	/**
	member function accepting an index value that removes the element at the given index from
	the vector, shifting elements backwards as appropriate. once the user input the index_of_array then function 
	the for loop will replace the every value in the array backward. 

	@param index_of_array_: is the int type variable that indicates the location of the memory where the user willing to delete it.
	*/
	void deleteAt(int index_of_array_);

	/**
	member function accepting an index and std::string value that inserts an element at the input
	position, moving elements including the element previously there forward and
	when this would push the vector size above the capacity then all the elements should be moved over to
	a new dynamic array of twice the former capacity before this process.

	@param index_of_array: is the int type variable that indicates the location of the memory where the user willing to insert the string.
	@param insert_message: is the string type varuable that the user wish to input in the specific location.
	*/
	void insertAt(int index_of_array_, std::string insert_message);

	/**
	this is the member function accepting an index value that returns the element of the string array which located at given location
	and the location will be specified by index_of_array_ variable. as the index_of_array passes, then the at function will return the
	string variable at specific location where index_of_array refers to.
	
	@param index_of_array_: is the int type varuable that indicates the location of the memory where the user willing to specify in the string array
	*/
	std::string at(int index_of_array_);


	/**
	This is the function that raise the size of the dynamic array and returns the value of the current size after raise.
	*/
	int raise_vec_size_();

	
	/**
	This is the function that returns the new capacity as it raise the the capacity by twice.
	*/
	int raise_vec_capacity();


	/**
	This is the function that lowers the size of the string vector and returns the size of it.
	*/
	int lower_vec_size();

};

}

#endif /*VECTOR_STRING_*/

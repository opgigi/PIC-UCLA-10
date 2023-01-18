#include "VectorString.h"
#include <iostream>
#include <string>

//this default constructor will assign a new dynamic memory to the point_To_Array and it will initialize the array and also the size and its capacity.
pic10b::VectorString::VectorString():pointer_To_Array{nullptr}
{
	pointer_To_Array = new std::string[1];
	pointer_To_Array[0] = '\0';
	vec_capacity = 1;
	vec_size = 0;

}

//this constructor will assign a new dynamic memory has the twice space of what the user passes as the parameter.
//also this will initialize the capacity by twice of the parameter.
pic10b::VectorString::VectorString(int size_of_vector_)
{
	pointer_To_Array = new std::string[size_of_vector_ * 2];
	//pointer_To_Array[0] = '\0';
	vec_size = size_of_vector_;
	vec_capacity = size_of_vector_ * 2;
}

//when the user specifies the size of the memory and the string messages wish to put, then it will give out the spece for the array and initializes.
pic10b::VectorString::VectorString(int size_of_insertion, std::string string_insertion)
{
	pointer_To_Array = new std::string[size_of_insertion * 2];
	vec_size = size_of_insertion;
	vec_capacity = size_of_insertion * 2;

	//this for loop will initializes all the string variable in the array.
	for (size_t i = 0; i < size_of_insertion; i++)
	{
		pointer_To_Array[i] = string_insertion;
	}


}


pic10b::VectorString& pic10b::VectorString::operator= (const VectorString& source_from_class)
{
	
	vec_size = source_from_class.vec_size;
	vec_capacity = source_from_class.vec_capacity;
	pointer_To_Array = source_from_class.pointer_To_Array;
	return (*this);
}

pic10b::VectorString::VectorString(const VectorString& copy_string)
{
	vec_capacity = copy_string.vec_capacity;
	vec_size = copy_string.vec_size;
	pointer_To_Array = copy_string.pointer_To_Array;
};

pic10b::VectorString::VectorString(VectorString&& copy_string)
{
	std::swap(vec_capacity, copy_string.vec_capacity);
	std::swap(vec_size, copy_string.vec_size);
	std::swap(pointer_To_Array, copy_string.pointer_To_Array);
}

int pic10b::VectorString::size()
{
	return vec_size;
}

int pic10b::VectorString::capacity()
{
	return vec_capacity;
}

int pic10b::VectorString::raise_vec_size_()
{
	++vec_size;
	return vec_size;
}

int pic10b::VectorString::raise_vec_capacity()
{
	vec_capacity *= 2;
	return vec_capacity;
}

int pic10b::VectorString::lower_vec_size()
{
	--vec_size;
	return vec_size;
}

//this function will separate into two cases whether the actual size is less or greater then the memory capacity of the dynamic memory 
void pic10b::VectorString::push_back(std::string message)
{
	std::string* arr_copy = { 0 };
	size_t total_length;
	size_t length_of_message = 0;
	
			 
		if (vec_size == vec_capacity)
		{

			// this for loop will runs until it finishes to copy all the content inside from the pointer_To_Array
			for (size_t z = 0; z < vec_size; z++)
			{
				arr_copy[z] = pointer_To_Array[z];
			}

			// this for loop will runs until it finishes to pushes out all the string messages to the end 
			for (size_t k = 0; k < length_of_message; k++)
			{
				arr_copy[length_of_message + k] = message[k];
			}

			delete[] pointer_To_Array;
			pointer_To_Array = arr_copy;
			++vec_size;
		}
		else
		{
			pointer_To_Array[vec_size] = message;
			++vec_size;
		}
}

void pic10b::VectorString::pop_back()
{
	lower_vec_size();
}

void pic10b::VectorString::deleteAt(int index_of_array_)
{
	if (index_of_array_ > vec_size)
	{
		return;
	}
	else {

		// this for loops runs until it finishes to push backward the whole messages except the one at the location where the user specify
		for (size_t i = index_of_array_; i < vec_size; i++)
		{
			pointer_To_Array[i - 1] = pointer_To_Array[i];
		}
	}
	lower_vec_size();
}

void pic10b::VectorString::insertAt(int index_of_array_, std::string insert_message)
{
	std::string *array_copy;
	if (vec_capacity > vec_size)
	{
		//this for loops runs until it finishes to pushed out all its contents 
		for (size_t j = index_of_array_-1; j < vec_size; j++)
		{
			pointer_To_Array[j + 1] = pointer_To_Array[j];
		}
		pointer_To_Array[index_of_array_] = insert_message;
		raise_vec_size_();
	}
	else
	{
		array_copy = new std::string[vec_capacity*2];
		
		// this for loops runs until it finishes to copy all the contents from the pointer_To_Array
		for (size_t j = 0; j < index_of_array_; j++)
		{
			array_copy[j] = pointer_To_Array[j];
		}

		// this for loops runs until it finishes to push all the contents if its location is greater then index_of_array.
		for (size_t j = index_of_array_; j < vec_size; j++)
		{
			array_copy[j] = pointer_To_Array[j-1];
		}
		
		array_copy[index_of_array_-1] = insert_message;

		

		vec_capacity *= 2;
		delete[] pointer_To_Array;
		pointer_To_Array = array_copy;


	}

	
}

std::string pic10b::VectorString::at(int index_of_array_)
{
	return pointer_To_Array[index_of_array_];
}

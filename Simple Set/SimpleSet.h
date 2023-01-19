#ifndef SIMPLE_SET_
#define SIMPLE_SET_

#include<vector>

namespace pic10c {


    /**
     @class simple_set: this is the class that stores the element into the vector, and has the feature of the function to insert, delete, find any data type variable out of the vector data, and get the size of the current simplet object as well.

     @tparam T datatype being stored.
     */
    template<typename T>
    class simple_set
    {
    private:
        std::vector<T> data;

    public:

        /**
         this is the default constructor to begin with the empty vector.
         */
        simple_set() : data(std::vector<T>()) {}

        /**
        insert function to insert T - value into the vector, if the value is already in the vector, then the values will not be added.

        @param Insert_values a const reference to T data type value for insertion into the vector data.
        */
        void insert(const T& Insert_values)
        {
            // if the std::find function can return the iterator where stores the Insert_values in the vector data, and that is within the range of the vector data, then do nothing.
            if (std::find(data.begin(), data.end(), Insert_values) != data.end())
            {
                return;
            } // otherwise if the find function cannot return the iterator where stores the Insert_values in the vector data, then the vector does not contain Insert_values in the vector, therefore insert the element into the vector.
            else
            {
                data.push_back(Insert_values);
            }

        }

        /**
        this is the function that remove the value that user wants to delete out of the vector data.

        @param delete_values is the const reference to data type T that the user wants to delete out of the vector.
        */
        void erase(const T& delete_values)
        {
            // we will set the iterator that stores the location of the element, where the delete_values located in the data vector.
            const std::vector<size_t>::iterator& delete_location = std::find(data.begin(), data.end(), delete_values);

            // if the iterator delete_location exist and it does not exceed the end iterator, then erase the value using iterator delete_location.
            if (delete_location != data.end())
            {
                data->erase(delete_location);
            }

        }

        /**
         find function will file the target_value that the user wants to find from the vector data and will give out the result that whether that value does exist or not in the vector.

         @param target_value is the const reference to T  that the user wants to find out the location where it stored.
         @return this function will return true if the function finds the element in the vector data, otherwise return false.
         */
        const bool find(const T& target_value)
        {
            // loops over the vector data, as much as the size of the data vector.
            for (const T& element_check : data)
            {
                // if there is at least one element exist equivalent to the target_value, then return true.
                if (element_check == target_value)
                {
                    return true;
                }
            }

            // otherwise, if the target_value is not in the vector data, then return false.
            return false;
        }

        /**
         this is the find functions figures out that at least one of the element in the vector data is equivalent to the target_value, which is the value that user wants to find. but it passes the just r-value to find that element does exist.

         @param target_value is the const r-value reference to data type T that the user wants to figure out that element does exist in the vector data.

         @return return true if the any of element in the vector data equivalents to the target_value, or otherwise return false if the loop cannot find any element is same as target_value.
        */
        const bool find(const T&& target_value)
        {
            // runs loop and also initailize the element_check as each every element in the vector data, and do the repetition of the size of the vector.
            for (const T& element_check : data)
            {
                // if the that element is equivalent to the target_value, then return true.
                if (element_check == target_value)
                {
                    return true;
                }
            }

            // otherwise if the loop cannot find the target_value in the vector then return false.
            return false;
        }


        /**
         this function will get the current size of the vector data.

         @return size of the data vector.
         */
        const size_t size()
        {
            return data.size();
        }

    };


    /**
    @class simple_set: this class is for the partial specialization of simple_set class for pointers to T, T*.
           this class will create the object has the vector of pointers as the member variables and has the functions to insert, delete, find the any data type variables out of the simple_set object.

     @tparam T datatype being stored.
     */
    template<typename T>
    class simple_set <T*>
    {

    private:
        std::vector<T*> data;

    public:

        /**
        this is the default constructor of the partial specialization of simple_set class for pointer to T.
        this constructor will initialize the empty vector of pointer to T.

         */
        simple_set() : data(std::vector<T*>()) {}

        /**
        this function is conditionally inserts new data into the vector data, if the insert_value does not exist in the data vector, then insert the values into the vector data.

        @param Insert_values is the const pointer to T values for insertion into the vector data.
        */
        void insert(T* const Insert_values)
        {
            // runs the loops with repetition of the size of data, and initialize the element_check with each every element from the vector data.
            for (const T* element_check : data)
            {
                // if the deference of Insert_value is equivalent to the dereferenced element_check, then do nothing and using return, get it out of the function.
                if (*Insert_values == *element_check)
                {
                    return;
                }
            }

            // if they cannot find the value in the vector, then insert the value as a new element.
            data.push_back(Insert_values);
        }


        /**
        Loops over storage vector to erase a value specified in args, if value exists in storage vector
        @param delete_data a const ref to a T value for deletion from class data storage vector
        */
        void erase(const T& delete_target) 
        {
            // after complete to define the iterator and runs the loops as much as the size of the data vector 
            for (auto delete_iterator = data.begin(); delete_iterator != data.end(); ++delete_iterator)
            {
                // if the dereferenced iterator value is equivalent to the delete_target, then delete the element where iterator refers to
                if (*(*delete_iterator) == delete_target)
                { 
                    data.erase(delete_iterator);
                    break; 
                }
            }
        }

        /**
         this is the find function that finds the target value user wants to find and let the user know that the target value does exist in the data vector.

         @param target_value is the const reference to T value that user wants to know the target value exist.
         @return return true boolean if the deference pointer element_check is equivalent to target_value. otherwise, return false because the function can't find the target_value in the vector.
         */
        const bool find(const T& target_value)
        {
            // define the const to T pointer element check and runs the loop as much the size of the data vector
            for (const T* element_check : data)
            {
                // if the dereference element is equivalent to the target_value then target_value does exist in the vector, thus, return true.
                if (*element_check == target_value)
                {
                    return true;
                }
            }

            // otherwise return false, since the function can't find the target_value in the vector.
            return false;

        }

        /**
         this function will let the user know the current size of the vector data.

         @return current size of the vector, data.
        */
        const size_t size()
        {
            return data.size();
        }



    };

    //an explicit specialization of simple_set for the bool type.
    /**
    @class simple_set<bool>: this class is the explicit specialization of simple_set class for the bool type.
                        if its template argument list matches of bool type variable, the compiler will generate the new definition from this partial specialization simple_set class. if the template argument is passed as the bool, then you can use the customized insert, erase, find, size function.

     */
    template<>
    class simple_set<bool>
    {
    private:
        bool has_true;
        bool has_false;


    public:

        /**
         this is the default constructor to begin empty.
         */
        simple_set() : has_true(), has_false() {}

        /**
         the function insert will insert the boolean value into the has_true or has_false.

         @param values const boolean type variable that user wants to insert.
         */
        void insert(const bool& values)
        {
            // if the user wants to insert the true boolean, then update the has_true value as true.
            if (values)
            {
                has_true = true;

            } // else, if the value that the user wants to insert false, then update the has_false value as true.
            else if (!values)
            {
                has_false = true;
            }
            else // otherwise, if the user wants to put something other than true, false, then do nothing.
            {
                return;
            }
        }


        /**
         the function erase will see that what boolean value that the user wants to delete then will decide what bool variable to deactive.

         @param erase_target is const bool
         */
        void erase(const bool& erase_target)
        {
            // if the erase_target is true and the simple_set object has the true boolean, then delete the target out of the simple_set object, deactive the has_true member varaible.
            if (erase_target == true && has_true == true)
            {
                has_true = false;
            } // if the erase target is false and member object has the false boolean then deactive the has_false variable
            else if (erase_target == false && has_false == true)
            {
                has_false = false;
            }
            else // otherwise, do nothing since has_true and has_false is false, we have nothing to delete out of the object.
            {
                return;
            }

        }

        /**
         the find function will find the boolean value that the user wants to find, and let the user know whether it does exist in the object or not.

         @param find_target is const reference to bool value that the user wants to find.
         */
        const bool find(const bool& find_target)
        {
            // if the find_target boolean is equivalent to true and has_true is enabled then return true that true boolean value is exist.
            if (find_target == true && has_true == true)
            {
                return true;
            } // else, if the find_target boolean is equivalent to false and has_false is enabled then return true, that the false boolean does exist.
            else if (find_target == false && has_false == true)
            {
                return true;
            }

            // otherwise, return false.
            return false;

        }


        /**
         this function will return the current size of the object, depends on the has_false, and has_true boolean variables.
         the total possibility of outcome from this function is only 0, 1, 2.

         @return will return size of 2 when the object has has_true, has_false as true. or return 1 either any of between two has_true or has_false boolean value is true, and return size of 0 if both has_true, has_false are false.

         */
        const size_t size()
        {
            // if the object has the has_true and has_false as true boolean then return the size as 2.
            if (has_true == true && has_false == true)
            {
                return 2;
            } // else if the object has the has_true boolean as true but has_false as false then return the size as 1.
            else if (has_true == true && has_false == false)
            {
                return 1;
            } // eles if the object has the has_false boolean as true but has_true as false then return the size as 1.
            else if (has_true == false && has_false == true)
            {
                return 1;
            }
            else // otherwise, if the has_true and has_false are all false then return the size as zero.
            {
                return 0;
            }

        }

    };

}








#endif

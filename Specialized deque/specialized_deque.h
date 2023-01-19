#ifndef specialize_deque_h
#define specialize_deque_h

#include <memory>
#include <climits>
#include <stdexcept>
#include <type_traits>



namespace pic10c {

    /**
     @class deque: The deque class creates an iterable functional double ended queue for arbitrary types. It allows for back and front pushing, and pop front and back of the vectors. and it is designed for every data type except the bool type specialization.
     */
    template<typename T>
    class deque;

    /**
     @class deque<bool>: The deque<bool> class creates an iterable functional double ended queue for bools. It allows for back and front pushing, and pop front and back of the vectors. it is specially designed for the bool so the deque obejct can occupy only one bit.

     */
    template<>
    class deque<bool>;

    /**
     sum function in pic10c namespace
     */
    template<typename T> // numerical only
    const T sum(const deque<T>& target);


    /**
     @class deque: The deque class creates an iterable functional double ended queue for arbitrary types. It allows for back and front pushing, and pop front and back of the vectors. and it is designed for every data type except the bool type specialization.

     @tparam T is the data type being stored.
     */
    template<typename T>
    class deque
    {
    public:
        /**
        @class iterator : The iterator class creates a functional iterator for vals in the specialize_deque. The iterator class privately contains the pointer to deque varaible,and a int type current index and a declaration for specialize_deque as a friend class so that specialize_deque can access current_index and all the iterator function such that the overloaded prefix, postfix of decrement and increment, equivalent, dequivalent operators, and dereference, call operator.
        */
        class iterator;

        /**
        @class const_iterator: The iterator class creates a functional iterator for vals in the specialize_deque. The const_iterator class privately contains the pointer to deque varaible,and a int type current index and a declaration for specialize_deque as a friend class so that specialize_deque can access current_index and all the iterator function such that the overloaded prefix, postfix of decrement and increment, equivalent, dequivalent operators, and dereference, call operator.
        */
        class const_iterator;

        /**
         this is the default constructor, default constructor is designed to initilaize all the member variable before it goes through all the member function. the left and right end will be flagged as -1 which it refers that those index are located at "pass the end".  and it will assign a dynamic memory on the vector data, and initailize the curren_element size as 0 and capacity as 1.

         */
        deque();


        /**
         copy constructor of the deque object

         @param deque_object is the deque_object that the user wants to copy the information from
         */
        deque(const deque& deque_object);

        /**
         move constructor of the deque object

         @param deque_object is the deque object that the user wants to transfer the rvalues from.
         */
        deque(deque&& deque_object);

        /**
         this is the destructor of the deque class. when the program is over and at the time when it is terminated, destructor will make the vector data pointed to nullptr, and automatically it will free the memory. and also it will initialize the current element size and capacity be zero, and left right end index will be flagged as -1.
         */
        ~deque();


        /**
         this is the copy operator of the deque object. it will use the swap functions, and will swap all the member variable in the deque object between the two of deque obejct.

         @param right_hand_side  is the deque object that the user wants to copy the information from.
         */
        deque& operator=(deque right_hand_side)&;

        /**
         this is the subscript operator. once the target_index is passed, it will go through the if statement that whether the target_index goes over the max capacity of the vector, if not then return the data element as the return.

         @param target_index is the index that the user wants to see what's stored in the vector, data.
         @return the element of the data what's stored in the vector, where the target_index refers to from the left end index. to prevent the return goes over the inaccessible index, using mod operator to always get the element within the range.
         */
        T& operator[](const size_t& target_index);


        /**
        this is the helper function that when the current_element_size of the vector is equivalent as the max capacity of the vector, then double the capacity and copy all the values from the current elements stored in the current vector.

         */
        void expand_max_size_double();


        /**
        overloaded push_back function. this function will check that whether the current_element_size and the max capacity of the vector is the same, if it is the same, then it will call the expand_max_size_double function and then push_back the element.
        or, if the vector is not fully occupied, then it will go through cases if there is empty spaces.

         @param inserted_value is the element that the user wants to push back.
         */
        void push_back(const T& inserted_value);

        /**
         push_front function. this function will check that whether the current_element_size and the max capacity of the vector is equivalent. if it is equivalent, then it will call the expand_max_size_double function and then push_front the element.
         or, otherwise, it the vector is not fully occupied, then check if there is a empty space on the left end, then push front.

         @param input is the element that the user wants to push front at the front of the vector.
         */
        void push_front(const T& inserted_value);

        /**
        this is the pop_back function, which eliminate the very last element from the back of the vector. and decrese the size of the current_element_size.
         */
        void pop_back();


        /**
         this is the pop_front function, which eliminate the very first element at the front of the vector, and then it will decrese the size of the current_element_size.
         */
        void pop_front();

        /**
         swap the deque with another one
         @param other is the other deque
         */
        void swap(deque& other);

        /**
         this is the size() function which returns the size of the element that the current vector contains.

         @return a const size_t values what the current_element_size has.
         */
        const size_t size() const { return currnet_element_size; }

        /**
        this is the capacity function that returns the size of the max possible size that the deque object can hold.

        @return a const size_t values what the max_size_of_deque has.
        */
        const size_t capacity() const { return max_size_of_deque; }

        /**
        returns iterator corresponding to first index in the vector

         @return iterator corresponding to first index in the vector.
        */
        const iterator begin();

        /**
         returns the iterator of the last index of the vector.

         @return the const iterator to the last index in the vector
         */
        const iterator end();

        /**
         finds the first idex of the vector and return as a const_iterator object.

         @return the const const_iterator to the fist index in the vector.
         */
        const const_iterator begin() const;

        /**
        finds the last index of the vector and return as the const_iterator object.

        @return the const const_iterator to the last index of the vector.
         */
        const const_iterator end() const;


        /**
         this function is designed to be the helper function that adds all the elements of the deque object.

         @return a const T value sum of all the elements of the deque object.
         */
        const T get_sum() const;

    private:
        std::unique_ptr<T[]> data; // data is a unique pointer to an array of type T
        size_t max_size_of_deque; // max size

        size_t currnet_element_size; // number of element currently has

        // used int data type instead of size_t since pointing_index = -1 indicates the "pass the end" signal!
        int left_end_index;

        // used int data type instead of size_t since pointing_index = -1 indicates the "pass the end" signal!
        int right_end_index;
    };

    /**
     @class deque<bool>: The deque<bool> class creates an iterable functional double ended queue for bools. It allows for back and front pushing, and pop front and back of the vectors. it is specially designed for the bool so the deque obejct can occupy only one bit.

     */
    template<>
    class deque<bool>
    {
    public:
        /**
        @class proxy: the proxy class creates a bit proxy for booleans inserted into our deque. It contains = and bool conversion operators, and as a member variable, it contains the pointer to deque object, data, bit index and constructor.
        */
        class proxy;

        /**
        @class const_proxy: the proxy class creates a bit proxy for booleans inserted into our deque. It contains a bool conversion operator, and as a member variable, it contains the pointer to deque obejct, data, bit index and constructor.
        */
        class const_proxy;

        /**
         @class iterator is the class that manages increment the iterator or decrement the iterator controls the index value and controls the current deque object changing index and use operator to deference or call the value.
         */
        class iterator;

        /**
         @class const_iterator is the class that manages increment the iterator or decrement the iterator controls the index value and controls the current deque object changing index and use operator to dereference or call the value.
         */
        class const_iterator;


        /**
         default constructor, the default constructor will initailize all the member variables, first it will initialize that the max capacity of the vector as 8 bit and start with the left , right index as -1 with current size is zero
         */
        deque();

        /**
         copy constructor, the copy constructor will initialize all the member variable using the initializer list.

         @param right_hand_side is that const reference deque object that the user wants to initialize with.
         */
        deque(const deque& right_hand_side)
        {

            current_element_size = right_hand_side.current_element_size;
            max_size_of_deque = right_hand_side.max_size_of_deque;
            left_end_index = right_hand_side.left_end_index;
            right_end_index = right_hand_side.right_end_index;

            for (size_t i = 0; i < max_size_of_deque; ++i)
            {
                data[i] = right_hand_side.data[i];
            }

        }

        /**
         move constructor, the move contructor will swap all the member variables  between the two deque object.

         @param right_hand_side is the r-value reference deque object that the user wants to swap the value with.
         */
        deque(deque&& right_hand_side)
        {
            using std::swap;

            swap(current_element_size, right_hand_side.current_element_size);
            swap(max_size_of_deque, right_hand_side.max_size_of_deque);
            swap(left_end_index, right_hand_side.left_end_index);
            swap(right_end_index, right_hand_side.right_end_index);
            swap(data, right_hand_side.data);

            delete[] right_hand_side.data;
            right_hand_side.data = nullptr;

        }

        /**
         desctructor,  this will be called at the end of the program terminates, it will free the memory from the data vector and will reset the right, left end, and current, max capacity of the size of the vector.
         */
        ~deque();

        /**
         copy assignment operator, this copy assignment operator
         @param other is the other deque
         */
        deque& operator=(deque right_hand_side)&
        {
            current_element_size = right_hand_side.current_element_size;
            max_size_of_deque = right_hand_side.max_size_of_deque;
            left_end_index = right_hand_side.left_end_index;
            right_end_index = right_hand_side.right_end_index;

            for (size_t i = 0; i < max_size_of_deque; ++i)
            {
                data[i] = right_hand_side.data[i];
            }
            return *this;
        }

        /**
         subscript operator
         @param target_index is the index that the user wants to see the value on that index.
         */
        proxy operator[](const size_t& target_index);


        /**
         subscript operator
         @param target_index is the index that the user wants to see the value on that index.
         */
        const_proxy operator[](const size_t& target_index) const;

        /**
         this function is desinged to expand the capacity of the vector by double and after the expand it will copy all the information from the previous vector.
         */
        void expand_max_size_double();

        /**
         this function is designed to push the element in the rare side of the vector
         @param inserted_value is the element that the user want to add on the back end of the vector.
         */
        void push_back(const bool& inserted_value);


        /**
         this function is designed to push the element on the front side of the vector
         @param inserted_value is the element that the user wants to add on the front end of the vector
         */
        void push_front(const bool& inserted_value);


        /**
         this function is designed to remove the element on the back end side of the vector.
         */
        void pop_back();


        /**
         this function is designed to remove the element from the vector on the front end side of the vector
         */
        void pop_front();


        /**
         swap the deque with another one
         @param swap_target is the other deque that the user wishes to swap with
         */
        void swap(deque<bool>& swap_target)
        {
            //enables ADL swap
            using std::swap;
            swap(current_element_size, swap_target.current_element_size);
            swap(max_size_of_deque, swap_target.max_size_of_deque);
            swap(data, swap_target.data);
            swap(left_end_index, swap_target.left_end_index);
            swap(right_end_index, swap_target.right_end_index);
        }


        /**
         find the size of deque
         @return a size_t value indicating the size
         */
        const size_t size() const { return current_element_size; }


        /**
         find the cap of deque
         @return a size_t value indicating the cap
         */
        const size_t capacity() const { return max_size_of_deque; }


        /**
         find the begin iterator of the deque
         @return the const iterator to the first element
         */
        const iterator begin();


        /**
         find the end iterator of the deque
         @return the const iterator to the past the end element
         */
        const iterator end();


        /**
         find the begin const_iterator of the deque
         @return the const const_iterator to the start
         */
        const const_iterator begin() const;


        /**
         find the end const_iterator of the deque
         @return the const const_iterator to the past the end element
         */
        const const_iterator end() const;




    private:
        unsigned char* data = new unsigned char[CHAR_BIT];
        size_t max_size_of_deque; // max possible size of vector
        size_t current_element_size; // number of element currently has

        // used int data type instead of size_t, since pointing_index = -1 indicates the "pass the end" signal!
        int left_end_index;

        // used int data type instead of size_t, since pointing_index = -1 indicates the "pass the end" signal!
        int right_end_index;
    };

    template<typename T>
    class deque<T>::iterator
    {
        friend deque;
    public:
        /**
         the definition of the class iterator default constructor. this constructor will initialize the container as the empty object and also intialize the index pointing to the "pass the end".
         */
        iterator() : container(nullptr)
        {
            current_index = -1;

        }

        /**
         constructor which initialize the deque object and index information
        @param deque_object is the deque object that the user wants to set the container
        @param target_index is the index of memory address that the user wants to deal with.
        */
        iterator(deque* deque_object, const int& target_index) : container(deque_object)
        {
            current_index = target_index;

        }

        /**
         overloaded equivalency operator
         this operator will compare the iterator between current object and iterator right_hand_side and will give out both are equivalent or not.

         @param right_hand_side is the iterator object on the right hand side, that the user want to compare with
         @return a const boolean, true if the current object's pointing_index is equal to the right_hand_side or otherwise return false.
         */
        const bool operator==(iterator right_hand_side) const;

        /**
         overloaded unequivalency operator
         this operator will compare the iterators between current object and iterator right_hand_side and will give out the result whether both are equivalent or not.

         @param right_hand_side is the iterator object on the right hand side, that the user want to compare with
         @return a const boolean, true if the current object's pointing_index is not equal to the iterator right_hand_side or otherwise return false if both are equivalent.
         */
        const bool operator!=(iterator right_hand_side) const;


        /**
         prefix increment operator
         @return iterator reference, which was incremented by 1.
         */
        iterator& operator++();

        /**
         post increment operator
         @return iterator object that was copied before complete the increment process.
         */
        iterator operator++(int);


        /**
         prefix decrement operator
         @return iterator reference, which was decremented by 1.
         */
        iterator& operator--();


        /**
         post increment operator
         @return iterator object that was copied before complete the decrement process.
        */
        iterator operator--(int);


        /**
         this is the definition of the deference operator. the dereference operator will access the element in the vector, data through iterator by accessing the deque object, container. the iterator object stores the correspond deque object and index information for the vector.

         @return a const T referece value that what the data vector stores in the pointing index.
         */
        const T& operator*() const { return container->data[current_index]; }
        /**
         this is the definition of the arrow operator. the arrow operator will acess the element in the vector data, through the iterator object, pointer to deque, conatainer will access the data vector where it is stored in the pointing_index.

         @return a const pointer to T valye that what the data vector stores in the pointing index.
         */
        const T* operator->() const { return &(container->data[current_index]); }

    private:

        // pointer to deque object that linked with the current deque object from the deque<T> class.
        deque* container;

        // int variable, when the pointing_index is -1, this will indicates the "pass the end" signal!
        int current_index;
    };

    template<typename T>
    class deque<T>::const_iterator
    {
        friend deque;
    public:
        /**
         default construcor, when the default constructor is called, then the deque object, container will be initialized as an empty object and the pointing index will be set the -1 to refers "pass the end signal"
         */
        const_iterator() : container(nullptr)
        {
            current_index = -1;

        }


        /**
         constructor which initialize the deque object and index information
        @param deque_object is the deque object that the user wants to set the container
        @param target_index is the index of memory address that the user wants to deal with.
        */
        const_iterator(const deque* deque_object, const int& target_index) : container(deque_object)
        {
            current_index = target_index;

        }




        /**
         prefix increment operator
         @return a reference const_iterator object , which the current pointing index incremented by 1.
         */
        const_iterator& operator++();


        /**
         post increment operator
         @return a copy of const_iterator object , and the original const_iterator object  will increment the current pointing index by 1 .
         */
        const_iterator operator++(int);


        /**
         prefix decrement operator
         @return a reference const_iterator obeject, which the current pointing index decrement by 1.
         */
        const_iterator& operator--();


        /**
         posfix decrement operator
         @return a copy of the const_iterator object, and the original const_iterator object will be decrement the current pointing index by 1.
         */
        const_iterator operator--(int);

        /**
         overloaded equivalency operator
         this operator will compare the const_iterator between current object and iterator right_hand_side and will give out both are equivalent or not.

         @param right_hand_side is the const_iterator object on the right hand side, that the user want to compare with
         @return a const boolean, true if the current object's pointing_index is equal to the right_hand_side or otherwise return false.
         */
        const bool operator==(const_iterator right_hand_side) const;


        /**
         overloaded unequivalency operator
         this operator will compare the two const_iterators between current object and const_iterator right_hand_side and will give out the result whether both are equivalent or not.

         @param right_hand_side is the const_iterator object on the right hand side, that the user want to compare with

         @return a const boolean, true if the current object's pointing_index is not equal to the iterator right_hand_side or otherwise return false if both are equivalent.
         */
        const bool operator!=(const_iterator right_hand_side) const;

        /**
         this is the definition of the deference operator. the dereference operator will access the element in the vector, data through const_iterator by accessing the deque object, container. the iterator object stores the correspond deque object and index information for the vector.

         @return a const T referece value that what the data vector stores in the pointing index.
         */
        const T& operator*() const { return container->data[current_index]; }


        /**
         this is the definition of the arrow operator. the arrow operator will acess the element in the vector data, through the const_iterator object, pointer to deque, conatainer will access the data vector where it is stored in the pointing_index.

         @return a const pointer to T valye that what the data vector stores in the pointing index.
         */
        const T* operator->() const { return &(container->data[current_index]); }

    private:

        // a const pointer to deque object corresponds to the current deque object that we are dealing with.
        const deque* container;

        // int variable, when the pointing_index is -1, this will indicates the "pass the end" signal!
        int current_index;
    };

    class deque<bool>::iterator
    {
        friend deque<bool>;
    public:


        /**
        this is the definition of the deque<bool> iterator default constructor, which will initialize the deque object as an empty object, and initialize the data, bit index as zero.
         */
        iterator() : container(nullptr), byte_index(0), bit_index(0) { }


        /**
         constructor, which initialize the deque object and data, bit index as what the user wants to specify what to store in that.

         @param deque_object is the deque object that the user wants to initialize the container with
         @param transfer_data_index is data_index that the user wants to initialize
         @param transfer_bit_index is the bit index that the user wants to initialize.
         */
        iterator(deque* deque_object, const size_t& transfer_data_index, const size_t& transfer_bit_index) : container(deque_object), byte_index(transfer_data_index), bit_index(transfer_bit_index) { }

        /**
         overloaded equivalency operator
         this operator will compare the const_iterator between current object and iterator right_hand_side and will give out both are equivalent or not.

         @param right_hand_side is the terator object on the right hand side, that the user want to compare with

         @return a const boolean, true if the current object's and the right_hand_side are the same deque object and the data, bit index information are equivalent. otherwise, if any one of the values are not equivalent, then return false.
         */
        const bool operator==(iterator right_hand_side) const;


        /**
         overloaded unequivalency operator
         this operator will compare the two iterators between current object and iterator right_hand_side and will give out the result whether both are equivalent or not.

         @param right_hand_side is the const_iterator object on the right hand side, that the user want to compare with

         @return a const boolean, true if any one of the member variable is not equivalent, or it only return false when the deque object is empty or it is completely equivalent between the two iterator object.
         */
        const bool operator!=(iterator right_hand_side) const;


        /**
         prefix increment operator
         @return an iterator reference object, with update, data, and bit index as a result.
         */
        iterator& operator++();


        /**
         post increment operator
         @return a copy of iterator object, and the original iterator object will update data, bit index as a result.
         */
        iterator operator++(int);


        /**
         prefix decrement operator
         @return an iterator reference object, with updated data, and bit index as a result.
         */
        iterator& operator--();


        /**
         posfix decrement operator
         @return a copy of iterator object, and original iterator object will update the data, and bit index as a result.
         */
        iterator operator--(int);


        /**
         dereference opearator, the dereference operator will return the binary value, which stored in the current iterator.

         @return a const reference to bool, if it is true, then convert that as 1 and display it on the right location of the vector, otherwise display 0 on the right location of the vector.
         */
        const bool& operator*() const;


    private:
        deque* container;
        int byte_index;
        int bit_index;
    };

    class deque<bool>::proxy
    {
        friend deque<bool>;
    public:
        /**
         assignment operator for proxy object
         @param boolean_code is the boolean that we want to create the proxy for.
         @return it will return a const reference to the proxy object.
         */
        const proxy& operator=(bool boolean_code) const;


        /**
         boolean conversion operator
         */
        operator bool() const;

    private:
        /**
         constructor for proxy object, this will initialize the deque object with the target_container what user specify and it will initailize the data, bit index with the target_Data_index, and target_bit_index.

         @param target_container is the pointer to deque object that the user wants to initialize with
         @param target_data_index is the size_t value that the user wants to initialize with
         @param target_bit_index is the size_t value that the user wants to initalize with
         */
        proxy(deque* target_container, size_t target_data_index, size_t target_bit_index);
        deque* container;
        size_t byte_index;
        size_t bit_index;
    };

    class deque<bool>::const_proxy
    {
        friend deque<bool>;
    public:
        /**
         assignment operator for proxy object
         @param boolean_code is the boolean that we want to create the proxy for.
         @return it will return the const reference of const_proxy object .
         */
        const const_proxy& operator=(bool boolean_code) const;


        /**
         boolean conversion operator
        */
        operator bool() const;

    private:

        /**
         constructor for const_proxy object, this will initalize the deque object and data, bit index with, the user wants to initialize with.

         @param target_container is the const pointer to deque object
         @param target_data_index is the const size_t value.
         @param target_bit_index is the const size_t value.
         */
        const_proxy(const deque* target_container, const size_t target_data_index, const size_t target_bit_index);
        const deque* container;
        size_t byte_index;
        size_t bit_index;
    };

    // definition of the dereference operator.
    // it will return the either 1 or zero depends on the boolean value that is stored in the data_index.
    inline const bool& deque<bool>::iterator::operator*() const
    {
        return ((container->data)[byte_index] >> bit_index) & 1;
    }

    // definition of the proxy object constructor.
    inline deque<bool>::proxy::proxy(deque* target_container, size_t target_byte_index, size_t target_bit_index) : container(target_container), byte_index(target_byte_index), bit_index(target_bit_index) { }

    // definition of the const_proxy object constructor.
    inline deque<bool>::const_proxy::const_proxy(const deque* target_container, const size_t target_byte_index, const size_t target_bit_index) : container(target_container), byte_index(target_byte_index), bit_index(target_bit_index) { }

    // definition of the proxy object subscript operator
    // it will return the proxy constructor.
    inline deque<bool>::proxy deque<bool>::operator[] (const size_t& indice)
    {
        size_t byteIndex = (((indice + left_end_index * CHAR_BIT) + CHAR_BIT) / CHAR_BIT) - 1; // index lets say 10, plus we need to start from leftmost byte that is apart of of deque so we add left index times 8 bc each byte (char) in data contains 8 bools. Then add 8 and divide by 8 to get ceiling interger division. subtract 1 to account for starting at index 0.
        size_t bitIndex = indice + (left_end_index)-(CHAR_BIT * byteIndex); //within byte X, which bit 0-7 going right to left. Need to add any extra unused bits left of the leftmost bit then subtract off the bits of the bytes left of our byte of interest.
        return proxy(this, data[byteIndex], bitIndex);
    }


    // definition of the subscript operator from the const_proxy class
    inline deque<bool>::const_proxy deque<bool>::operator[] (const size_t& indice) const
    {
        return const_proxy(this, data[indice], indice);
    }

    // definition fo the bool conversion operator.
    // this operator will return either 1 or zero depends on the boolean value that is stored in the data_index.
    inline deque<bool>::proxy::operator bool() const
    {
        return ((container->data)[byte_index] >> bit_index) & 1;

    }

    // definition of the bool conversion operator for const_proxy class
    // this operator will return either 1 or zero depends on the boolean value taht is stored in the data_index.
    inline deque<bool>::const_proxy::operator bool() const
    {
        return ((container->data)[byte_index] >> bit_index) & 1;

    }

    // definition of the copy assignment operator
    inline const deque<bool>::proxy& deque<bool>::proxy::operator=(bool boolean_code) const
    {
        return *this;
    }

    // definition of the default constructor of deque<T>
    template<typename T>
    deque<T>::deque() : data(new T[1]), max_size_of_deque(1), currnet_element_size(0), left_end_index(-1), right_end_index(-1) {}

    // definition of the default constructor of deque<bool>
    deque<bool>::deque() : max_size_of_deque(CHAR_BIT), current_element_size(0), left_end_index(-1), right_end_index(-1) {}

    // definition of the constructor of deque<T> that initializes all the memeber variable in the deque object, when the user pass the parameter.
    template<typename T>
    deque<T>::deque(const deque& right_hand_side) : data(right_hand_side.data), max_size_of_deque(right_hand_side.max_size_of_deque), currnet_element_size(right_hand_side.currnet_element_size), left_end_index(right_hand_side.left_end_index), right_end_index(right_hand_side.right_end_index) { }


    // definition of the move constructor, it will swap all the information from the target deque object that the user wants to swap with.
    template<typename T>
    deque<T>::deque(deque&& deque_for_move)
    {
        // enable ADL swap function
        using std::swap;
        swap(data, deque_for_move.data);
        swap(max_size_of_deque, deque_for_move.max_size_of_deque);
        swap(currnet_element_size, deque_for_move.currnet_element_size);
        swap(left_end_index, deque_for_move.left_end_index);
        swap(right_end_index, deque_for_move.right_end_index);
    }

    // definition of the destructor of the class deque<T>. it will free the memory from the vector and will reset all the size and left, right end index.
    template<typename T>
    deque<T>::~deque()
    {
        max_size_of_deque = 0;
        currnet_element_size = 0;
        data = nullptr;
        left_end_index = -1;
        right_end_index = -1;
    }

    // definition of the destructor of the partial specialization class deque<bool>. it will free the memory from the vector and will reset all the size and left, right end index.
    deque<bool>::~deque()
    {
        max_size_of_deque = 0;
        current_element_size = 0;
        data = nullptr;
        left_end_index = -1;
        right_end_index = -1;
    }

    // definition of the assignment operator. it will swaps all the member variable between the current deque object with the right_hand_side deque object.
    template<typename T>
    deque<T>& deque<T>::operator=(deque<T> right_hand_side)&
    {
        // enable ADL swap
        using std::swap;
        swap(data, right_hand_side.data);
        swap(max_size_of_deque, right_hand_side.max_size_of_deque);
        swap(currnet_element_size, right_hand_side.currnet_element_size);
        swap(left_end_index, right_hand_side.left_end_index);
        swap(right_end_index, right_hand_side.right_end_index);
    }

    // definition of the subscription operator of deque<T>.
    template<typename T>
    T& deque<T>::operator[](const size_t& target_index)
    {
        // if the target index is greater than the max possible capacity that the vector can hold, throw the error message.
        if (target_index >= max_size_of_deque)
        {
            throw std::range_error("Index is out of the range");
        }
        else // otherwise, if the target index is within the range, then return the element of the vector stored at the target_index, reference from the left_end_index, and prevent the access of the we will use the mod, so it can only access the value within the range.
        {
            return data[(left_end_index + target_index) % max_size_of_deque];
        }
    }

    // definition of the expand_max_size_double.
    template<typename T>
    void deque<T>::expand_max_size_double()
    {
        // define the varaible to preserve the copy of the current vector.
        auto vector_of_pointer = std::move(data);

        // if the max size of the vector is not zero then we should double the maximum possible size of the vector and transfer all the previous information into the newly expanded vector.
        if (max_size_of_deque != 0)
        {
            data.reset(new T[max_size_of_deque * 2]);

            // if the right end of the current vector has larger index compared to the left end of the vector, then we will copy the every element in normal order from the copyied vector.
            if (left_end_index <= right_end_index)
            {
                for (size_t i = left_end_index; i <= right_end_index; ++i)
                {
                    data[i] = vector_of_pointer[i];

                }
            }
            else // if it is wrapping around, then we will break it into two pieces and combine those are together again.
            {
                size_t reconfigure_index = 0;

                // first chunk will be the sub vector from the left end of the current to the max possible size of the vector, since the right_end_index < left_end_index.
                for (size_t first_part = left_end_index; first_part <= max_size_of_deque - 1; ++first_part)
                {
                    data[reconfigure_index] = vector_of_pointer[first_part];

                    ++reconfigure_index;

                }

                // run this loop to copy the second chunk of the vector from the initial position of the vector to the right_end_index.
                for (size_t second_part = 0; second_part <= right_end_index; ++second_part)
                {
                    data[reconfigure_index] = vector_of_pointer[second_part];

                    // we will update the reconfigure index to track the size of the current element contained in the vector.
                    ++reconfigure_index;

                }
            }

            // once you re done with process of the double up the space of the vector and separate two chuncks and combine all together. 
            //then now you need to update the max possible size and the left, right end of the vector holds actual elements in the vector.

            max_size_of_deque *= 2;
            left_end_index = 0;
            right_end_index = currnet_element_size - 1;

        }
        else // otherwise, if the max capacity of the vector is zero then reallocate the new memory on the vector and reset the right and left end index.
        {
            data.reset(new T[1]);
            left_end_index = -1;
            right_end_index = -1;
            max_size_of_deque = 1;
        }
    }

    // definition of the expand_max_size_double
    void deque<bool>::expand_max_size_double()
    {
        auto copy = std::move(data);
        unsigned char* new_data = (unsigned char*)malloc(sizeof(CHAR_BIT) * 2);
        std::memcpy(new_data, data, sizeof(data));
        if (left_end_index <= right_end_index) // move elements to new places if left <= right
        {
            for (size_t i = left_end_index; i <= right_end_index; ++i)
            {
                size_t data_index = i / CHAR_BIT;
                size_t bit_index = i % CHAR_BIT;
                unsigned char old_val = (copy[data_index] >> bit_index) & 1;
                old_val ^= 1;
                //data[data_index] |= old_val << bit_index;
                data[data_index] = (data[data_index] & ~(1 << bit_index)) | (old_val << bit_index);
            }
        }
        else // if wrapping around, move in two pieces
        {
            size_t tracking_data_index = 0;
            size_t tracking_bit_index = 0;
            for (size_t j = left_end_index; j <= max_size_of_deque - 1; ++j) // first piece, from left to right most
            {
                size_t data_index = j / CHAR_BIT;
                size_t bit_index = j % CHAR_BIT;
                unsigned char old_val = (copy[data_index] >> bit_index) & 1;
                old_val ^= 1;
                //data[tracking_data_index] |= old_val << tracking_bit_index;
                data[data_index] = (data[data_index] & ~(1 << bit_index)) | (old_val << bit_index);
                if (tracking_bit_index < 7)
                {
                    ++tracking_bit_index;
                }
                else
                {
                    tracking_bit_index = 0;
                    ++tracking_data_index;
                }
            }
            for (size_t k = 0; k <= right_end_index; ++k) // second piece, from front most to right
            {
                size_t data_index = k / CHAR_BIT;
                size_t bit_index = k % CHAR_BIT;
                unsigned char old_val = (copy[data_index] >> bit_index) & 1;
                old_val ^= 1;
                data[data_index] = (data[data_index] & ~(1 << bit_index)) | (old_val << bit_index);
                if (tracking_bit_index < 7) { ++tracking_bit_index; }
                else { tracking_bit_index = 0; ++tracking_data_index; }
            }
        }
        max_size_of_deque *= 2;
        left_end_index = 0;
        right_end_index = current_element_size - 1;
    }

    // definition of the push_back from deque<T> class
    template<typename T>
    void deque<T>::push_back(const T& inserted_value)
    {
        using std::swap;
        // if there is a free space available in the vector then we don't have to add more memory into the vector.
        if (currnet_element_size != max_size_of_deque)
        {
            // if there is still a space left on the right end of the vector, we will use it.
            if (right_end_index + 1 <= max_size_of_deque)
            {
                data[right_end_index + 1] = inserted_value;
                ++right_end_index;

                // if the left end of the vector is not defined, then since the space is not empty, then we should define the left end of the vector.
                if (left_end_index == -1)
                {
                    left_end_index = 0;

                }
            }
            else // otherwise, if the vector is not full and if the index of the right end is over the maximum possible size of the vector, meaning that only one space available in the vector.
            {
                data[0] = inserted_value;
                right_end_index = 0;
            }
            ++currnet_element_size;
        }
        else // if there is no free space available in the vector, then we need to reallocate the memory and index into the vector.
        {
            expand_max_size_double();
            push_back(inserted_value);
        }
    }


    void deque<bool>::push_back(const bool& inserted_value)
    {
        if (current_element_size == max_size_of_deque) // if current array is full, find way to reallocate more positions
        {
            expand_max_size_double();
            push_back(inserted_value);
        }
        else // if not full, then no need to allocate new indices for the array
        {
            if (right_end_index + 1 <= max_size_of_deque) // no matter wrapping around or not, if there is a space on the right of back, use it
            {
                size_t target_data_index = (right_end_index) / CHAR_BIT;
                size_t target_bit_index = (right_end_index + 1) % CHAR_BIT;
                data[target_data_index] = (data[target_data_index] & ~(1 << target_bit_index)) | (inserted_value << target_bit_index);
                ++right_end_index;
                if (left_end_index == -1) 
                { 
                    left_end_index = 0; 
                } 
            }
            else // if array is not full and nothing is on right of back, must have something empty on the left of array
            {
               
                data[0] = (data[0] & ~(1 << 0)) | (inserted_value << 0);
                right_end_index = 0;
            }
            ++current_element_size;
        }
    }

    // definition of the push_front from deque<T> class
    template<typename T>
    void deque<T>::push_front(const T& inserted_value)
    {
        // if the vector is not full then we will insert the value into the vector without expanding the max possible capacity of the vector.
        if (currnet_element_size != max_size_of_deque)
        {

            // if the left end tracker is not at the front, then we have to utilize the space, and then update the left end.
            if (left_end_index > 0)
            {
                data[left_end_index - 1] = inserted_value;
                --left_end_index;
            }
            else // otherwise, if there is no free space at the front, then wrap around, which meaning that, we need to move update the left end to the back of the vector.
            {
                data[max_size_of_deque - 1] = inserted_value;
                left_end_index = max_size_of_deque - 1;
                if (right_end_index == -1) { right_end_index = 0; } // set to not empty
            }
            ++currnet_element_size;
        }
        else // otherwise, if the vector's max possible capacity is full, then we have to reallocate memory to expand the max possible capacity so we can push front more values into the vector.
        {

            // after the process is done then update the current size of the actual element contained in the vector.
            expand_max_size_double();

            // after the capacity was updated, then use the recursion to push front the target value that user wants to insert.
            push_front(inserted_value);
        }
    }
    void deque<bool>::push_front(const bool& inserted_value)
    {
        if (current_element_size == max_size_of_deque) // array full, more pos added and call recurssively
        {
            expand_max_size_double();
            push_front(inserted_value);
        }
        else
        {
            if (left_end_index > 0)  // if left not at front, use the space in front
            {
                size_t target_data_index = (left_end_index - 1) / CHAR_BIT;
                size_t target_bit_index = (left_end_index - 1) % CHAR_BIT;
                data[target_data_index] = (data[target_data_index] & ~(1 << target_bit_index)) | (inserted_value << target_bit_index);
                --left_end_index;
            }
            else// otherwise, wrap around
            {
                size_t target_data_index = (max_size_of_deque - 1) / CHAR_BIT;
                size_t target_bit_index = (max_size_of_deque - 1) % CHAR_BIT;
                data[target_data_index] = (data[target_data_index] & ~(1 << target_bit_index)) | (inserted_value << target_bit_index);
                left_end_index = max_size_of_deque - 1;
                if (right_end_index == -1) { right_end_index = 0; } // set to not empty
            }
            ++current_element_size;
        }
    }


    template<typename T>
    void deque<T>::pop_back()
    {
        // decrement the current size of the element.
        --currnet_element_size;
        // if the current vector is not empty, then run this statement.
        if (currnet_element_size != 0)
        {
            // if the right_end is at the zero index of the vector, that means we need to set the new rights
            if (right_end_index != 0)
            {
                --right_end_index;

            }
            else // otherwise, if the right_end is not at the zero index, then we will just update the right end index, pushing the right index by -1;
            {
                right_end_index = max_size_of_deque - 1;

            }
        }
        else // otherwise, if the current size of the actual element does exist in the vector is zero then we should set the flags "pass the end" on the left and right end.
        {

            left_end_index = -1;
            right_end_index = -1;
        }
    }

    // definition of the pop_back from the deque<bool>
    void deque<bool>::pop_back()
    {
        // decrement the current size of the element.
        --current_element_size;

        // if the current vector is not empty, then run this statement.
        if (current_element_size != 0)
        {
            // if the right_end is at the zero index of the vector, that means we need to set the new rights as the max capcity off by -1.
            if (right_end_index == 0)
            {
                right_end_index = max_size_of_deque - 1;
            }
            else // otherwise, if the right_end is not at the zero index, then we will just update the right end index, pushing the right index by -1;
            {
                --right_end_index;
            }


        }
        else // otherwise, if the current size of the actual element does exist in the vector is zero then we should set the flags "pass the end" on the left and right end.
        {
            left_end_index = -1;
            right_end_index = -1;
        }
    }

    // definition of the pop_front from deque<T>
    template<typename T>
    void deque<T>::pop_front()
    {
        --currnet_element_size;

        // if the current_size is not zero then, we will need to update the left end index based on conditions.
        if (currnet_element_size != 0)
        {
            //if the current vector is not empty, and the left end index is very at the end of the maximum capacity that the vector can hold, then set the new left at the zero index of the vector.
            if (left_end_index == max_size_of_deque - 1)
            {
                left_end_index = 0;


            }
            else // otherwise, if the left end index is not at the maximum capacity that the vector can hold, then we will update the left end index to get rid of the very front value on the current exist element on the vector.
            {
                ++left_end_index;

            }

        }
        else // otherwise, if the current size of the element exist in the vector is zero then we will set the flag on the right and left end index as "pass the end" because the current vector is empty.
        {

            left_end_index = -1;
            right_end_index = -1;
        }
    }


    // definition of the pop_front from the deque<bool> class.
    void deque<bool>::pop_front()
    {
        --current_element_size;

        // if the current_size is not zero then, we will need to update the left end index based on conditions.
        if (current_element_size != 0)
        {
            //if the current vector is not empty, and the left end index is very at the end of the maximum capacity that the vector can hold, then set the new left at the zero index of the vector.
            if (left_end_index == max_size_of_deque - 1)
            {
                left_end_index = 0;
            }
            else // otherwise, if the left end index is not at the maximum capacity that the vector can hold, then we will update the left end index to get rid of the very front value on the current exist element on the vector.
            {
                ++left_end_index;
            }

        }
        else // otherwise, if the current size of the element exist in the vector is zero then we will set the flag on the right and left end index as "pass the end" because the current vector is empty.
        {
            left_end_index = -1;
            right_end_index = -1;
        }
    }

    // definition of the iterator begin() function from the deque<T> class
    template<typename T>
    const typename deque<T>::iterator deque<T>::begin()
    {
        return iterator(this, left_end_index);
    }

    // definition of the const_iterator begin() function from deque<T> class
    template<typename T>
    const typename deque<T>::const_iterator deque<T>::begin() const
    {
        return const_iterator(this, left_end_index);
    }

    // definition of the iterator begin function from deque<bool> class.
    const typename deque<bool>::iterator deque<bool>::begin()
    {
        return iterator(this, left_end_index / CHAR_BIT, left_end_index % CHAR_BIT);
    }

    // definition of the iterator end() function from the deque<T> class
    template<typename T>
    const typename deque<T>::iterator deque<T>::end()
    {
        return iterator(this, -1);
    }

    // definition of the const_iterator end() function from the deque<T> class
    template<typename T>
    const typename deque<T>::const_iterator deque<T>::end() const
    {
        return const_iterator(this, -1);
    }

    // definition of the iterator end() function from the deque<bool> class
    const typename deque<bool>::iterator deque<bool>::end()
    {
        return iterator(this, -1, -1);

    }

    // definition of the operator++ from iterator class from deque<T>
    template<typename T>
    typename deque<T>::iterator& deque<T>::iterator::operator++()
    {
        // if the next index from the current_index is larger or smaller than its right end index then run this.
        if (current_index != container->right_end_index)
        {
            // if current_index does not go over the max possible iterator, then you re good to raise the index by 1.
            if (current_index + 1 <= container->max_size_of_deque - 1)
            {
                ++current_index;

            }
            else // otherwise, if the next index from the current index is larger than the max possible iterator allowed, then return back to the very first iterator of the vector.
            {
                current_index = 0;

            }



        }
        else // otherwise, if the current_index is at the right end index of the deque object then set the flag "pass the end"
        {
            current_index = -1;
        }
        return *this;
    }

    // definition of the operator++ from the const_iterator class
    template<typename T>
    typename deque<T>::const_iterator& deque<T>::const_iterator::operator++()
    {
        // if current_index does not go over the max possible iterator, then you re good to raise the index by 1.
        if (current_index != container->right_end_index)
        {

            // if the next index from the current_index is equal or smaller than its max possible index then run this.
            if (current_index + 1 <= container->max_size_of_deque - 1)
            {
                ++current_index;
            }
            else // otherwise, if the next index from the current index is larger than the max possible iterator allowed, then return back to the very first iterator of the vector.
            {
                current_index = 0;
            }
        }
        else // otherwise, if the current_index is at the right end index of the deque object then set the flag "pass the end"
        {
            current_index = -1;
        }
        return *this;
    }

    // definition of the operator++ from deque<bool> class
    typename deque<bool>::iterator& deque<bool>::iterator::operator++()
    {
        // if any one of the data, or bit index is "passing the end", then do nothing and return
        if (byte_index == -1 || bit_index == -1)
        {
            return *this;
        }
        else // otherwise, if both data, and bit index does exist and not passing the end, then run this.
        {
            int current_index = byte_index * CHAR_BIT + bit_index;

            // if current_index does not go over the max possible iterator, then you re good to raise the index by 1.
            if (current_index != container->right_end_index)
            {

                // if the next index from the current_index is equal or smaller than its right end index then raise the current index and break the index info into data, and bit index.
                if (current_index + 1 <= container->max_size_of_deque - 1)
                {
                    ++current_index;

                    byte_index = current_index / CHAR_BIT;

                    bit_index = current_index % CHAR_BIT;

                }
                else // otherwise, if the next index from the current index is larger then the max possible index in the vector then return to the very first iterator in the vector.
                {
                    byte_index = 0;
                    bit_index = 0;
                }
            }
            else // otherwise, if the current index is at the right end index of the current_element_vector, then set both data, bit index as passing the end.
            {
                byte_index = -1;
                bit_index = -1;

            }
        }
        return *this;
    }


    // definition of the postfix operator++ from iterator class for deque<T> class
    template<typename T>
    typename deque<T>::iterator deque<T>::iterator::operator++(int)
    {
        // use prefix to define
        iterator temp = *this;
        ++(*this);
        return temp;
    }

    // definition of the postfix operator++ from the const_iterator class for deque<T> class
    template<typename T>
    typename deque<T>::const_iterator deque<T>::const_iterator::operator++(int)
    {
        // use prefix to define
        const_iterator temp = *this;
        ++(*this);
        return temp;
    }


    // definition of the postfix operator++ from the iterator class for deque<bool> specialization.
    typename deque<bool>::iterator deque<bool>::iterator::operator++(int)
    {
        // use prefix to define
        iterator temp = *this;
        ++(*this);
        return temp;
    }

    // definition of the prefix operator-- from the iterator class for deque<T>
    template<typename T>
    typename deque<T>::iterator& deque<T>::iterator::operator--()
    {
        // if the current_index is not at the left end of the deque object, then run this
        if (current_index != container->left_end_index)
        {
            // if the current_index does not pointing to the zero index, then that means we have more room on the left side, thus we only decrement the current index.
            if (current_index != 0)
            {
                --current_index;
            }
            else // otherwise, if the current index is at the zero index of the vector, you need to iterate back to back end of the vector.
            {
                current_index = container->max_size_of_deque - 1;
            }

        }
        else // otherwise, if the current index is at the left end index of the current_element vector, then flag the "pass the end".
        {
            current_index = -1;
        }
        return *this;
    }

    // definition of the prefix operator-- from const_iterator class for the deque<T> object
    template<typename T>
    typename deque<T>::const_iterator& deque<T>::const_iterator::operator--()
    {

        // if the current_index is not at the left end of the deque object, then run this
        if (current_index != container->left_end_index)
        {
            // if the current_index does not pointing to the zero index, then that means we have more room on the left side, thus we only decrement the current index.
            if (current_index != 0)
            {
                --current_index;
            }
            else // otherwise, if the current index is at the zero index of the vector, you need to iterate back to back end of the vector.
            {
                current_index = container->max_size_of_deque - 1;
            }

        }
        else // otherwise, if the current index is at the left end index of the current_element vector, then flag the "pass the end".
        {
            current_index = -1;
        }
        return *this;
    }

    // definition of the prefix operator-- from the iterator class for deque<bool> specialization.
    typename deque<bool>::iterator& deque<bool>::iterator::operator--()
    {
        // if any of the data, bit index referring the flag they are at the end, then do nothing and return the object.
        if (byte_index == -1 || bit_index == -1)
        {
            return *this;
        }
        else // otherwise, if the two data, and bit index does exist and not passing the end, then run this.
        {
            int current_index = byte_index * CHAR_BIT + bit_index;

            // if the pointing index is not at the left end index then run this.
            if (current_index != container->left_end_index)
            {
                // if the current index is at the very front end of the vector then there is no more free space on the left side, meaning that you have to return to the back end side of the vector
                if (current_index == 0)
                {
                    current_index = container->max_size_of_deque - 1;
                }
                else // otherwise, if the pointing_index does not referred zero in the vector, meaning that there are more spaces on the left besides the left end index, thus you can decrement the iterator.
                {
                    --current_index;
                }

                // now update the byte and bit index
                byte_index = current_index / CHAR_BIT;
                bit_index = current_index % CHAR_BIT;

            }
            else // otherwise, if the current index is at the left end of the current element vector, then flag "pass the end" on the both byte, and bit index.
            {

                byte_index = -1;
                bit_index = -1;
            }
        }
        return *this;
    }

    // definition of the postfix operator-- from iterator class for the deque<T>
    template<typename T>
    typename deque<T>::iterator deque<T>::iterator::operator--(int)
    {
        // use prefix to define
        iterator temp = *this;
        --(*this);
        return temp;
    }

    // definition of the postfix operator-- from const_iterator class for the deque<T>
    template<typename T>
    typename deque<T>::const_iterator deque<T>::const_iterator::operator--(int)
    {
        // use prefix to define
        const_iterator temp = *this;
        --(*this);
        return temp;
    }

    // definition of the postfix operator-- from iterator class for the deque<bool> specialization.
    typename deque<bool>::iterator deque<bool>::iterator::operator--(int)
    {
        // use prefix to define
        iterator temp = *this;
        --(*this);
        return temp;
    }

    // definition of the equivalent operator== from the iterator class for the deque<T>
    template<typename T>
    const bool deque<T>::iterator::operator==(iterator right_hand_side) const
    {
        // if the container what the current iterator is completely equivalent to the iterator right hand side, then return true
        if (!(container->data[current_index] < container->data[right_hand_side.current_index]) && !(container->data[right_hand_side.current_index] < container->data[current_index]) && current_index == right_hand_side.current_index)
        {
            return true;

        } // else if any of container from iterator object is empty then that means there is no object to compare, thus return false.
        else if (right_hand_side.container == nullptr || container == nullptr)
        {
            return false;

        }
        else // anything else will turn out to be false.
        {
            return false;

        }
    }

    // definition of the operator== from the const_iterator for deque<T> objects.
    template<typename T>
    const bool deque<T>::const_iterator::operator==(const_iterator right_hand_side) const
    {
        // if the container what the current iterator is completely equivalent to the iterator right hand side, then return true
        if (!(container->data[current_index] < container->data[right_hand_side.current_index]) && !(container->data[right_hand_side.current_index] < container->data[current_index]) && current_index == right_hand_side.current_index)
        {
            return true;

        } // else if any of container from iterator object is empty then that means there is no object to compare, thus return false.
        else if (right_hand_side.container == nullptr || container == nullptr)
        {
            return false;

        }
        else // anything else will turn out to be false.
        {
            return false;

        }
    }

    // definition of the operator== from the iterator class for deque<bool> specialization.
    const bool deque<bool>::iterator::operator==(iterator right_hand_side) const
    {
        // if the deque objects are identical and also has the same index then return true.
        if (container == right_hand_side.container && byte_index == right_hand_side.byte_index && bit_index == right_hand_side.bit_index)
        {
            return true;
        } // else if any one of two deque object does not exist, then return as false
        else if (container == nullptr || right_hand_side.container == nullptr)
        {
            return false;
        }
        else // otherwise, if the deque object is not empty nor its not identical, then return false.
        {
            return false;
        }
    }

    // definition of the operator != from the iterator class for deque<T> object
    template<typename T>
    const bool deque<T>::iterator::operator!=(iterator right_hand_side) const
    {
        // if the container what the current iterator is completely equivalent to the iterator right hand side, then return true
        if (!(container->data[current_index] < container->data[right_hand_side.current_index]) && !(container->data[right_hand_side.current_index] < container->data[current_index]) && current_index == right_hand_side.current_index)
        {
            return false;

        } // else if any of container from iterator object is empty then that means there is no object to compare, thus return false.
        else if (right_hand_side.container == nullptr || container == nullptr)
        {
            return false;

        }
        else // anything else will turn out to be true.
        {
            return true;

        }
    }


    template<typename T>
    const bool deque<T>::const_iterator::operator!=(const_iterator right_hand_side) const
    {
        // if the container what the current iterator is completely equivalent to the iterator right hand side, then return false
        if (!(container->data[current_index] < container->data[right_hand_side.current_index]) && !(container->data[right_hand_side.current_index] < container->data[current_index]) && current_index == right_hand_side.current_index)
        {
            return false;

        } // else if any of container from iterator object is empty then that means there is no object to compare, thus return false.
        else if (right_hand_side.container == nullptr || container == nullptr)
        {
            return false;

        }
        else // anything else will turn out to be true.
        {
            return true;

        }
    }


    const bool deque<bool>::iterator::operator!=(iterator right_hand_side) const
    {
        // if the deque objects are identical and also has the same index then return false.
        if (container == right_hand_side.container && byte_index == right_hand_side.byte_index && bit_index == right_hand_side.bit_index)
        {
            return false;
        } // else if any one of two deque object does not exist, then return as false
        else if (container == nullptr || right_hand_side.container == nullptr)
        {
            return false;
        }
        else // otherwise, if the deque object is not empty nor its not identical, then return true.
        {
            return true;
        }
    }


    template<typename T>
    const T deque<T>::get_sum() const
    {
        T result_of_sum = 0;

        // if the capacity of the vector is zero, then the vector is empty, therefore return 0 as the result of the sum.
        if (max_size_of_deque == 0)
        {
            return 0;

        }
        else //otherwise, if the capacity of the vector is not zero then there are possible element exist in the vector, then figure out the sum.
        {
            // if the right end is larger then the left end index, then the element are arranged in right order, then just calculate the sum from left end index to the right end index.
            if (right_end_index >= left_end_index)
            {
                // runs the sum from the left end to the right end, and add onto the result of sum by every iteration
                for (int i = left_end_index; i <= right_end_index; ++i)
                {
                    result_of_sum += data[i];

                }

            }
            else //otherwise, if the it is wrapped around then
            {
                // runs the loop from zero index to right end and from the left index to the max capacity of the vector.
                for (int i = 0; (i < max_size_of_deque) && (0 < i <= right_end_index || left_end_index <= i < max_size_of_deque - 1); ++i)
                {
                    result_of_sum += data[i];
                }
            }
        }
        return result_of_sum;
    }

    // call member helper function to do the work
    template<typename T>
    const T sum(const deque<T>& target)
    {
        return target.get_sum();
    }

}

#endif /* specialize_deque_h */

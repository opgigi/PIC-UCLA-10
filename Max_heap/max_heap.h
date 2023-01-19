#ifndef max_heap_h
#define max_heap_h

#include <vector>
#include <utility>
#include <stdexcept>


namespace pic10c
{


    // enables ADL, once you use the ADL, then the copiler will finds the best swap functions for variables.
    using std::swap;

    /**
     @class max_heap: this max_heap class is the data structure that has always the max value by using compare_type variable, pred, among the structure at the top.
                in order to sort out the structure to have the largest value at the top of the tree structure, this class has several member functions and member variables.
                this class majorly separated into two parts, which is the collection of the function to sort out algorithm to promote and demote the targeted value depends
                on the situation, the other part is that the function applying the promote and demote algorithm to run the main routine.

     @tparam T : data type being stored.
     @tparam S : This is for the type to defining order method for promote and demoting algorithm. and the default is std::less<T> if not specified.
     */
    template<typename T, typename S = std::less<T>>
    class max_heap
    {
    private:

        // the vector values with the data type of T, which can stores any datatype.
        std::vector <T> values;
        // pred is the member variable of compare_type.
        S pred;


    public:

        /**
        default constructor by templated class, once the default and any other constructor is defined within the class scope, then we can refer to the variables and the class itself.
        if user gives only single argument are given, then the constructor will automatically set the pred as the compare_type.
         */
        max_heap<T, S>();

        /**
         constructor by templated class, once the constructor is defined within the class scope, then we can also refer to the variables and the class itself.
         this constructor is designed to use the value the value _pred, to initialize the value for pred.

         @param _pred : the ordering method, which is defaulted to std::less<T>
         */
        max_heap<T, S>(S _pred) : pred(_pred) {};

        /***
         once you define the function to calculate the index, I am going to define the fuction to sort out the max_heap structure.
         first, before we sort the tree stucture, we have to insert the new element in the very bottom of the tree structure and then start the sort process from there.
         there are two major cases in order to sort the tree structure from the bottom.
         one is that the case that pred gives out the true boolean, then swap the position between current index and its child.
         and repeats the process until the targeted element reaches to the highest position of the structure could possibly get to.

         in the case you have to get rid of the top element using pop() function, then we have to get rid of the top value in the structure, which is located at the 0th index of the 1d vector.
         to remove the top element of the structure, I will reference the slide that the algorithm should start to swap the top element with
         */

         // I wanna use the sort algorithm using recursion. the idea is that the program finishes inserting the new element in very bottom of the structure,
         // you will compare the parents index and current index to see that there is a possibility for the promotion.

         /**
          this function is designed to move up the new insert value in the tree structure to its highest possible position using recursion. once the current_index is passed then it will see that whether its parents node is smaller than
          the current index value, if the if-statment turns out true, then it will promote the current index value to its parents node index and it will repeat until it reaches to the highest possible position of the tree structure.

          @param current_index  :this vairable is the const reference int and this represents the current memory address for the std::vector<T> values.
          */
        void promotion_from_bottom(int const& current_index)
        {

            /*
             according to the slide, in the 1d vector, the relation between parents index and it's child node will be:
             parents_index = (child_index - 1) / 2
            */

            int its_parents = ((current_index - 1) / 2);

            // if the compare_type value turns out true, then promote the child node of the current_index using swap and recursion.
            if (pred(values[its_parents], values[current_index]))
            {

                swap(values[its_parents], values[current_index]);

                // the point of the algorithm is that we have to let the new element promote in the tree structure as much as possible.
                // therefore, we are going to use recursion until it reaches the highest position as much as possible.
                promotion_from_bottom(its_parents);
            }


        }

        /**
         this function is designed to demote the targeted value in the tree structure to its lowest possible position using recursion. once the current_index is passed then it will see that depends on the pred's compare_type, the function decided to demote the current_index value in the structure.  if any of  if-statment turns out true, then it will demote the current index value to its children node index and it will repeat until it reaches to the lowest possible position of the tree structure.

         @param current_index: this vairable is the const reference int and this represents the current memory address for the std::vector<T> values.
         */
        void demote_from_the_top(int const& current_index)
        {

            /**
             According to the lecture material from data structure, once you re handling the max_heap data structure in the 1d vector, you can easily find the relationship between parents index and child node.
             and these are the following formula for accessing parents and child nodes:

             parents_index = (child_index - 1) / 2
             left_child_index = (parents_index * 2) + 1
             right_child_index = (parents_index * 2) + 2

             based on this information, we will define a function that calculates the parents_index and child_index in the current position.
             */

            int left_child_node = (current_index * 2) + 1;

            int right_child_node = (current_index * 2) + 2;

            // this variable is needed for more possibility to demote the value.
            int possible_demotion_node = 0;


            // first thing is to see that if either any of right child of current index falls within the range of size of structure.
            if (left_child_node < values.size())
            {
                // if the compare_type variable pred detects that the statement is true then, update the possible_demotion_node to see that there are more possibility
                // to demote the value in the structure.
                if (pred(values[current_index], values[left_child_node]))
                {

                    possible_demotion_node = left_child_node;
                }
            }
            // to check that the right child is fallin within the range of the size of the structure, then proceed to run the code

            if (right_child_node < values.size())
            {
                // if the current index will be compared with the value in its right child, if the predication turns out true then, update the possible_demotion_node
                if (pred(values[current_index], values[right_child_node]))
                {

                    possible_demotion_node = right_child_node;
                }
            }






            // if either any of left or right child node is identical with possible_demotion_node, then run the recursion to see the possible demotion.
            if (possible_demotion_node == left_child_node || possible_demotion_node == right_child_node)
            {
                swap(values[current_index], values[possible_demotion_node]);

                demote_from_the_top(possible_demotion_node);

            }

        }

        /**
         this function is designed to insert the new element in the vector and after we inserted the new element in the structure, then this function will also sort it out using the function promote_from_bottom.
         the function promotion_from_bottom will find the highest position of the newly inserted element, how much it can go up in the structure.

         @param inserted_value : this is the value in any datatype to insert into the tree structure, and it is passed by referenence to prevent to copy the value from the original variable.

         */
        void insert(const T& inserted_value)
        {
            values.push_back(inserted_value);

            promotion_from_bottom(values.size() - 1);
        }

        /**
         this function is designed to check what's the total numbers of the elements in the structure.
         @return it returns the total number of the element in the std::vector<T> values to let the user know that how much is the size of the structure.
         */
        const int size()
        {
            return values.size();
        }

        /**
         this function is designed to show what's the value on the top of the heap structure.
         the main purpose of the maximum_heap structure is that to keep the most large or least value in the at the top of the heap sturcture
         for easy access to the maximum value or max_min of the heap structure and also to find the top value in efficient way.

         @return if there is at least more than one element in the heap, then it will return the value[0], which is the top value in the max_heap structure.
         */
        T top()
        {
            // if there is at least more than one element in the heap structure, then return the max value from the heap.
            if (values.size() > 0)
            {
                return values[0];
            }
            else // otherwise, send out the message that heap is empty.
            {
                throw std::logic_error("heap is now empty!");
            }
        }


        /**
         this function is designed to remove the top value from the heap and adapting into the new structure once after old top value is removed.
         according to the slides, to remove the top item from the structure, the first step is to swap the top item with the item at the final position of the structure and use pop_back() to remove the swapped item.
         and after that we will apply the demote_from_top function to adjust new top element into the right position in the structrue.
         */
        void pop()
        {

            // if there is at least more than one element in the heap structure,
            if (values.size() > 0)
            {
                //first step is to swap the top item with the last item in the structure.
                swap(values[0], values[size() - 1]);

                //then remove the last element from the structure after swap.
                values.pop_back();

                // then use the demotion algorithm to adjust the heap structure.
                demote_from_the_top(0);
            }
            else //otherwise, send out the message that there is no element in the heap.
            {
                throw std::logic_error("heap is now empty!");
            }
        }



    };

    /**
     The inline function enables the compiler replace the constructor with the function definition which if any different templated default constructor is defined.
     since we defined the constructor with only one template which are <typename T, std::less<T>>, this inline templated constructor is necessary in the case that you re defining templated constructor in a different format.
     such as, max_heap<int, std::greater<int>>, or max_heap<std::string, decltype(by_length)> so on.
     */
    template<typename T, typename S>
    inline max_heap<T, S>::max_heap()
    {
        /* empty */
    }




}


#endif /* max_heap_h */

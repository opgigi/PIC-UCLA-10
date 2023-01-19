#ifndef BST_H
#define BST_H

#include <utility>
#include <functional>
#include <stdexcept>

namespace pic10c {

    //enables ADL, once you using keyword to use ADL, the compiler will finds the best swap functions for variables.
    using std::swap;

    /**
    @class bst: the class bst is the associative data structure that stores the data in specific order into the tree structure.
           if the data is randomly stored into the tree, this bst class does insert/find/erasing element in O(logn) complexity.
           and this class contains nested class node, and class iterator.

     The bst class has the member variable root, pred variable in compare_type as the defult of std::less<T>, and size of the tree structure.
     and the class bst contains the member function, find,  overloaded swap function for the bst variables, Insert fucntions to put the value into the node in specific patterns of
     ordering. begin() and end() functions will find the first index of the structure in the specific ordering method, and the end index of the structure as well.
     erase() function will delete the specified index in the structure where the user wants to erase the whole nodes. the emplace function will insert the list of elements into the nodes of the bst class.


     @tparam T :Datatype being stored
     @tparam S :this type is defining the order methods for comparing any data type of two variable. and the default type is std::less if the user does not specified.
     */
    template <typename T, typename S = std::less<T>>
    class bst {

    private:

        // nested node class, this enables to use the member variable/function to construct the member functions in the bst class.
        class node;

        // node of the binary search tree structure.
        node* root;

        // S type varaible enables to compare between any type of two variables.
        S pred;

        // number of elements in the binary search tree structure.
        size_t structure_size = 0;

        /**
         this function is designed to delete the all the elements and nodes out of the binary search tree structure. deletetree function is necessary to delete the whole structure of the tree when the destructuor is called.
         this function will use the recursive method to delete the tree nodes, when the function initially passes the root node of the sturcture, then it will move down far left as possible of the structure, delete the node.
         after the far left node is deleted then it will get out of its recursive function and will started to delete the right child node and go on recursively to delete all the nodes in the structure.

         @param node_to_delete : this is the variable of the node data type that wanted to be deleted out of the structure.
        */
        void deleteTree(node* node_to_delete);


        /**
         this function is designed to assist with copying using recursive function on nodes to copy. this function is necessary to construct the copy constructor of bst class.
         this function will initially access to the farest left of the tree structure, and copy the value and insert into the other tree structure.
         and also the current node has the right child, then go to the right child and find possibility to find the child, if not then copy the value from the node and insert that value into the node in the other structure.
         and repeat this process until you copy all the stucture and the values inside of each node in the structure.

         @param node_to_insert : this is the targeted node
         */
        void traverseInsert(node* node_to_insert);

    public:

        /**
        constructor which initializes: pred, root, and tree_size

        @param pred_input the comparison function to compare the data
        */
        bst(const S& pred_input = S()) :
            pred(pred_input), root(nullptr), structure_size(0) {}

        /**
        @class iterator: the iterator class is designed to numbering the iterator of each nodes in specific way of ordering using the functional iterator.

        the iterator class construct the functional iterator how the node pointer should behave when they are locating the index of the structure.
        in the class iterator has the node pointer for the current_location to represent its location of the structure. and this function is friended with class bst to allow the bst class can access to the current_position.
        this class contains a constructor, destructor, and overloaded operator of prefix and postfix of ++ and -- and overloaded comparison operator == and !=  to compare the iterator variables.
        and last, dereferencing operator and operator arrow to get an access of the value in the nodes.

        */
        class iterator;

        /**
        this is the destructor declaration and definition, destructor is necessary because it must happen prior to the deallocation.
        thus, the destuctor is designed to delete every node in the tree strucutre and free the memory in the tree structure.
        once this function is called then it will call the deleteTree function which deletes all the element and the nodes out of the tree structure and free the memory so it make sure that
        there are no memory leaks before they end the program.
        */
        ~bst() { deleteTree(root); }

        /**
        copy constructor
        @param right_hand_side is the const bst reference type variable that the user wants copied from.
        */
        bst(const bst& right_hand_side);

        /**
        move constructor
        @param copy_target this is the bst type variable to be moved. it will transfer all the rvalue information from the variable that
        */
        bst(bst&& copy_target) noexcept;

        /**
        copy/move assignment operator
        once this function is called, then the member swap function will be called to replace all the information of root and pred and size of the tree sturcture.

        @param copied_from is that bst variable that the user wants to copy the infromation from.
        */
        bst& operator=(bst that)&;




        /**
         this function is designed to check if the tree has the value what the user wants to find, which is, target_value.
         this function will go through every single nodes to find the target_value in the structure, once it finds the value, then it will return the iterator of the structure.
         if not, then it will return the nullptr

         @param target_value the specific double
         @return true if found, false if not
        */
        iterator find(const T& target_value) const;

        /**
        swaps member functions for two trees, this swap function is designed to swap the current bst value with the different swap_target bst variable.
        when this function called, current bst and swap target bst will swap their information and replace the pred, structure size, and root infromation.

        @param swap_target this is the bst type variable to swap with the current bst variable.
        */
        void swap(bst& swap_target);

        /**
        this function is designed to set the iterator to a begin position

        @return the iterator that is set to the begin postion of the structure
        */
        iterator begin() const;

        /**
        this function is designed to set the iterator to an end position

        @return the constructor of iterator which initializes the node current_position as the nullptr which is the past-end-position.
        */
        iterator end() const;

        /**
        this function is designed to insert the given lvalue in any data type to the tree sturcutre. when this function is called then the function will check that whether the tree structure is empty or not
        if the whole stucture is empty then using the constructor of the node, creates the root node of the structure, if there is at least more than one element is exist in the tree structure, then create the new node
        then the insertnode function finds the right place to insert into the structure and update the size of the structure.

        @param inserted_value the element that the user wants to insert into the structure.
        */
        void insert(const T& inserted_value);

        /**
        this function is designed to insert the given rvalue into the tree structure. uses the same procedure as lvalue insert fucntion, when this function is called then the function will check that whether the structure is empty.
        if it is empty structrue then create the new node and move the rvalue into the node, if there at least more than one element in the strcutrue then, create the new node and call the insertNode function
        so it can find the right place to insert into the structure, once the insertion process is over, then it will update the size of the structure.

        @param inserted_value the rvalue element that the user watns to insert into the structure.
        */
        void insert(T&& inserted_value);

        /**
        this function is designed to removes the node based on the given iterator value.
        According to the slide, there are three scenarios when you remove the nodes out of the structure.
        which are when the current node has no children, or has one child (left or right) and lastly, when the current node has both left and right children.
        erase function will apply the different erase method depends on those three cases.

        @param remove_target the iterator variable that the user wants to erase the node and the value inside.
        */
        void erase(iterator remove_target);

        /**
        this function is designed, based on the variadic list of the parameters, this function will call the insert function and will insert every list argument into the tree structure.
        using std::forward function, and this enables to forward the r-value reference data type into the function. then when each variable from the argument list then, it will call the insert function and
        insert the value into the tree structure.

        @param list_of_arguments variadic list of arguments used to construct T
        */
        template <typename... Types>
        void emplace(Types&&... list_of_arguments);

        /**
        this function is designed to access the size of the tree structure.

        @return structure_size which is the size of the whole tree structure
        */
        size_t size() const;


    };

    // the definition of the class iterator doxygen format is on the declaration part in the public part of the bst
    template <typename T, typename S>
    class bst<T, S>::iterator { //nested iterator class

        // this allows using bst member functions and variable to change the value of iterator
        friend bst;

    private:

        /**
        constructor which initializes node current_position and the bst pointer container.
        if the user does not specify the what node and bst pointer varaible to use for initalization, then both will be set as nullptr as default.


        @param n is the node varaible will be used to initailize the node current_position
        @param c is the bst pointer will be used to initalize the bst pointer container
        */
        iterator(node* n = nullptr, const bst* c = nullptr) :
            current_position(n), container(c) {}

        // this variable refers the current node in the structure.
        node* current_position;


        const bst* container;



    public:

        /**
        this function is designed to move onto the next iterator in the tree structure.
        According to the slides, to move forward from one node to the next, in current node location, we will first check that there is a right child node exist, then move it to the right child
        and from that we will take the most far left child node. if the function moves down the far left child, then that will be the next iterator from the formal iterator.

        or if the node current_position does not have the right child, then move the current node up to the its parent node and keep continues until the parent node has the right child.
        once the function finds the parents has the right child then, return the iterator of the structure.

        @return *this, which is the current instance iterator
        */
        iterator& operator++()
        {
            //if the current_position's right child is exist, then run the code inside the braket.
            if (current_position->right)
            {
                // move to the right child node
                current_position = current_position->right;

                // then find the furtest left child node and keep going down to left child until find the node that doesn't have the left child.
                while (current_position->left)
                {
                    // move to the left child.
                    current_position = current_position->left;
                }
            }
            else // if there are no right child exist from the current node, then run the code inside this bracket.
            {
                // create the new node to store the parent node information of the current node.
                node* its_parents = current_position->parent;

                // if the parent node is exist and the current node is placed on the right child of its parents,
                // then we have to move up to the parent of parent node to see that there is right child.
                while (its_parents && (current_position == its_parents->right))
                {
                    // then move up the current nodes up to its parents.
                    current_position = its_parents;
                    // then update its parents since the current node move up to its parents.
                    its_parents = its_parents->parent;
                }

                /*
                 if the loop does not run, which means that the current position of coming from the left child of its parent
                 then there might be a possibility to find the right child of its parents, thus move it up to its parents and
                 return the instance of iterator.

                 otherwise, if the loop runs, it means that the current node is located at its parents right child then the function
                 should locate the current node until it reaches the parent node that has the right child.

                 the reason behind this is that, in this algorithm anything on the left child node has the more priority having an iterator
                 compared to its right child having its iterator, so in order to avoid to missing putting iterator on some of nodes in the structure
                 you have to put iterator on its left child and parent, and then go down to the right child node and update it as the parents and repeat
                 the process.
                 */
                if (current_position->parent)
                {
                    current_position = current_position->parent;
                    return *this;
                }
                else // if the current position does not have the parent then we are dealing with the root node therefore, return the iterator past end.
                {
                    current_position = nullptr;
                    return *this;
                }
            }

            // once the program reach this line it means that you found the far left child of the structure.
            // thus return the iterator of the instance.
            return *this;
        }

        /**
         this function is designed to move backward to the previous iterator.
         this function will behave exactly opposite to find the previous iterator. since we know that left child of the current node will always have the priority of its parents,
         therefore, once you get to the left child,  then the right child always has the less iterator priority than the left child, knowing that, we move down to the left child and then
         we take the far most right child, once it reaches to the far left then return the iterator.


         or if there are no left child exist, then keep going up to the parents until you find the parents has the left child of it, then return the iterator of that parent.

         @return *this, which is the current instance iterator
         */
        iterator& operator--()
        {
            // if the current node's left child is exist, then move to its left child.
            if (current_position->left)
            {
                current_position = current_position->left;

                // then if the left child exist, knowing that the right child always has less priority to get iterated.
                // thus keep moving down to its far most right child in the structure.
                while (current_position->right)
                {
                    current_position = current_position->right;
                }

            }
            else // when there is no left child of the current node, then we have to find the previous iterator from one of parent node in the sturcuture.
            {
                // create the new node to store the parent node information of the current node.
                node* its_parents = current_position->parent;

                // if the current node is located at its parent's left child, then move up to the parents and keep update the current node's parent node
                // if the current node is the parent's left child, then there are no possibility you can find the previous iterator with moving down to the
                // left child, that's why we will keep move up the parent node until we find the parent node that might possibly can have the left child node.
                // (meaning that, current node is not the left child of its parent.)
                while (current_position == its_parents->left)
                {
                    current_position = its_parents;
                    its_parents = its_parents->parent;
                }

                /*
                 if the loop runs that means that the current node is not the left child of its parent node anymore,
                 then with running the condition, if there is parent exist, then finally current node moves up to the parent might possibly have
                 left child.

                 othewise if the parents does not exist, which meaning that it reached the roots of the structure, thus current position will be nullptr
                 and return the iterator.
                 */
                if (current_position->parent)
                {
                    //move to parent and end
                    current_position = current_position->parent;
                    return *this;
                }
                else //else, return one space past end
                {
                    current_position = nullptr;
                    return *this;
                }
            }
            return *this;

        }


        /**
         this function is overloaded postfix operator ++
         after they create the node for copy to copy all the information that current node has and then going through the exact same process as what prefix function ++ does.
         once they update the current node, then they return the previous information of current node before it was updated.

         @param unused inform compiler that function is for postfix
         @return return the copied_node.
         */
        iterator operator++(int)
        {
            node* copied_node(*this);
            ++current_position;

            return copied_node;
        }


        /**
         this function is overloaded postfix operator --
         after they create the node for copy to copy all the information that current node has and then going through the exact same process as what prefix function -- does.
         once they update the current node, then they return the previous information of current node before it was updated.

         @param unused inform compiler that function is for postfix
         @return return the copied_node.
         */
        iterator operator--(int)
        {
            node* copied_node(*this);
            --current_position;

            return copied_node;
        }



        /**
        overloaded == comparison operator, which compares the two iterator variable which are, left_hand_side and right_hand_side.

         @param left_hand_side : is the iterator variable on the left side of the operator.
         @param right_hand_side : is the iterator varaible on the right side of the operator for comparison.
         @return it will return ture if both left and right hand side iterator are equal and false if not.
         */
        friend bool operator==(const iterator& left_hand_side, const iterator& right_hand_side) {

            return left_hand_side.current_position == right_hand_side.current_position;
        }

        /**
        overloaded != comparison operator, which compares the two iterator variables which are, left_hand_side and right_hand_side.

         @param left_hand_side : is the iterator variable on the left side of the operator.
         @param right_hand_side : is the iterator variable on the right side ofthe operator for comparison.
         @return it will return true if right and left hand side are not equal if it is equal then return false.
         */
        friend bool operator!=(const iterator& left_hand_side, const iterator& right_hand_side) {

            return left_hand_side.current_position != right_hand_side.current_position;
        }

        /**
        overload dereferencing operator (without modifying tree element).
        once this function is called then the function will acess value stored in the current node and return the value.


         @return it will return value in the current node in any data type.
         */
        const T& operator*() const {
            return current_position->value; // value contained by current node
        }

        /**
        overload arrow operator as a member function.
        this purpose of this function is same which is that access values stored in the current node and return the value.
        but the difference is that this function will return the current position dereferenced.

         @return the current position dereferences
         */
        const T* operator->() const {
            return &current_position->value; // value contained by current node
        }


    };

    // the definition of the deleteTree function.
    template <typename T, typename S>
    void bst<T, S>::deleteTree(node* node_to_delete) {

        if (node_to_delete != nullptr)
        {
            /*
            if there is left child is exist, then the function will keep fall into its recursion and reached to the most far left child
            first and run into the next recursion to check that if the most far left has the right child.
            if there is no right child, then delete the node and get out of the recursion.
            */
            deleteTree(node_to_delete->left);

            /*
            once the first recursion finds the farest left possible, then from that point you move on to the farest right then delete the node.
            once after the recursion, delete the node and get out of the recursion and then find the possible left child node and if there is the one
            then delete the node and then get out of the recursion.

            repeat this process until you delete all the subtrees derived from the some of node of the right child.
            */
            deleteTree(node_to_delete->right);
            delete node_to_delete;
        }

        // once the deletion process is over then update the side of the tree structure and end the function.
        structure_size = 0;

    }

    // the definition of the traverseInsert
    template <typename T, typename S>
    void bst<T, S>::traverseInsert(node* current) {

        insert(current->value); //insert all values from the branch

        /*
         if there is the left child exist then recursively calls the same function but the left child will be passed as the parameter
         and it will go down the far left down of the sturcutre from the current node. once node reached the farest left then the function
         will insert the the value where it is currently located.
         */
        if (current->left)
        {
            traverseInsert(current->left);
        }



        /*
         once the function reaches to the farest left child, then it will check that the left child has its right child.
         if there is right child exist then the function will go deep into the structure, what is the farest right child.
         once it reaches to the right child then it will run the finding left child in recursion but if there is nothing then insert and
         get out of the loop. we keep repeat this process until the program copys all the nodes from the sturcture.
         */
        if (current->right)
        {
            traverseInsert(current->right); //recurse as far right as possible
        }

    }

    // definition of the copy constructor
    template <typename T, typename S>
    bst<T, S>::bst(const bst& right_hand_side) : root(nullptr), pred(right_hand_side.pred) {

        pred = right_hand_side.pred;
        // it will call the copy helper function traverseInsert to copy all the nodes from the current structure to the other structure.
        traverseInsert(right_hand_side.root);
    }

    // definition of the move constructor
    template <typename T, typename S>
    bst<T, S>::bst(bst&& other_structure) noexcept : bst() {

        // using the swap member function to swap currnet structure with the other stucture that all the pred,root, and structure size value.
        (*this).swap(other_structure);
    }

    // definition of the move/copy assignment operator.
    template <typename T, typename compare_type>
    bst<T, compare_type>& bst<T, compare_type>::operator=(bst that)& {

        (*this).swap(that); // swap implicit tree with given tree
        return *this; // return implicit tree
    }



    // definition of the member swap function to swap between two tree sturucture.
    template <typename T, typename S>
    void bst<T, S>::swap(bst& other_structure) {

        // swap the root information of the current sturcutre with the root information belongs to the other_structure.
        std::swap(root, other_structure.root);

        // swap predicate of implicit structure with the other structure.
        std::swap(pred, other_structure.pred);

        // swap the structure size of the current structure and the other structure size.
        std::swap(structure_size, other_structure.structure_size);
    }

    // definition of the free swap function between two tree sturucture.
    template <typename T, typename S>
    void swap(bst<T, S>& first, bst<T, S>& second) {

        first.swap(second); // use member function to swap first tree with second
    }

    // the definition of the begin function.
    template <typename T, typename S>
    typename bst<T, S>::iterator bst<T, S>::begin() const {

        // check that if the root is empty that means the whole structure is empty.
        if (!root) {

            // since the structure is empty then return the nullptr.
            return iterator(nullptr, this);
        }

        // since we check that the structure is not empty, then set the node to find the begin position.
        node* n = root;


        /*
         since we knows that every left child has the priority to have the number of the iterator,
         my strategy will find the far most left child if the function catches that far left child from the root node,
         then it must be the first iterator.
         */

         // if the node has the right child then proceed to the left child.
        while (n->left)
        {
            // move it down to its left child
            n = n->left;
        }

        // once the program reaches to the farest left child from the root node then, return the iterator what the node n has.
        return iterator(n, this);
    }

    // the definition of the end() function.
    template <typename T, typename S>
    typename bst<T, S>::iterator bst<T, S>::end() const
    {
        //return the iterator to nullptr.
        return iterator(nullptr, this);
    }

    // the definition of the lvalue insert function.
    template <typename T, typename S>
    void bst<T, S>::insert(const T& inserted_value) {

        // if the root currently points out the null, which means the sturcutre is currently empty.
        if (root == nullptr)
        { //if root is empty

            root = new node(inserted_value); //make a node with given value the root
            ++structure_size; //node added
        }
        else
        { //if the root is exist which means that the structure at least has more than one node in the structure.

            // then set up the node, and initailized the value using node constructor.
            node* n = new node(inserted_value);

            /*
            then you will insert newly created node into the strucuture using insertNode() function.
            after the insertion node function is successful, then it will give out true boolean
            and run in the if-statement.
            */

            if (root->insertNode(n, pred))
            {
                //if node insertion is successful, then increase the size of structure in the tree.
                ++structure_size;
            }
        }
    }

    // definition of the rvalue insert function
    template <typename T, typename S>
    void bst<T, S>::insert(T&& inserted_value)
    {

        // if the root does not exist, which means that the tree structure is empty.
        if (!root)
        {
            // then we will set up the root node in the structure. using node constructor.
            // which initializes the value and create left, right, and parent node pointer.
            root = new node(std::move(inserted_value));

            // once the process is done, then increase the size of the structure.
            ++structure_size;
        }
        else // otherwise, if you do have the root in the stucture, then you just need to insert the node in the tree.
        {

            // set up the new node that we want to insert in the structure.
            node* new_node;

            // then using the node constructor, which initializes the value inside the node and
            // setting up the right left and parents node pointers so it can link to the structure.
            new_node = new node(std::move(inserted_value));

            // if the root can call the insertNode function and after the insertion is successful,
            if (root->insertNode(new_node, pred))
            {
                // then increase the size of the structure.
                ++structure_size;
            }
        }
    }

    // nested node class definition
    template <typename T, typename S>
    class bst<T, S>::node {

        // this enables that makes the node class can access bst member functions to search through the nodes.
        friend bst;

        // this enables that makes the node class can access the iterator operator functions
        friend iterator;

    private:

        /*
        the constructor of node, will initialize the value inside the node using rvalue,
        and they will set up the left. right, and parents node pointer to connect the node in the structure.
        */
        node(T value) : value(std::move(value)), left(nullptr),
            right(nullptr), parent(nullptr) {}

        // node pointer refers that left child of the node what the program currently dealing with.
        node* left;

        // node pointer refers that the right child of the node what the program currently dealing with.
        node* right;

        // node pointer refers that the parent of the node what the program currently dealing with.
        node* parent;

        // the value in any data type stored in the node.
        T value;

        /**
        insertNode function is designed to be the helper function of the insert() function to insert node into the structure.
        insertNode will see that the newly inserted value is smaller or greater than the current node value.
        if the new value is smaller than the current value, then it will place it on the left side.

        otherwise if the new value is greater than the current value, then it will place the value then place it on the right side.

        @param new_node is the node is aiming to be inserted into the tree structure.
        @param pred the compare_type variable that returns boolean returns which one is smaller or greater.
        @return whether the node was successfully inserted
        */
        bool insertNode(node* new_node, S pred);
    };

    // the definition of the insertNode function.
    template<typename T, typename S>
    bool bst<T, S>::node::insertNode(node* new_node, S pred) {

        // if the new inserted value is greater than the current value, then place it on the right side.
        if (pred(value, new_node->value)) {

            // check that if there is a right child
            if (right) {

                // if the right child exist then find more possibility that you can place the new value on the further right side.
                // to do this, using recursion.
                right->insertNode(new_node, pred);
            }
            else { // otherwise if there is no more right child exist, then run this code.
                // set right to be the new node.
                right = new_node;

                // and set the connection between currnet node and the new node as a right child.
                new_node->parent = this;

                // if the insertion was successful, then return true.
                return true;
            }
        }  // if the new value is smaller than the current node value, then it should be placed on the left.
        else if (pred(new_node->value, value))
        {

            // if the left child exist then run the code inside
            if (left)
            {
                // since we figure out the left child exist then using the recursion and check that
                // to see more possibility to place that on the right or left side.
                left->insertNode(new_node, pred);
            }
            else { // otherwise if the left child does not exist, then run the code inside.

                //new_node will be set on the left child of the current node.
                left = new_node;

                // then establish the connection between new_node and the current node.
                new_node->parent = this;

                // if the insertion is successful then return the true boolean.
                return true;
            }
        }

        // if the current node value are not smaller nor bigger than the new node value, it means that two values are identical.
        else {


            /*
             since the program catches that the two values are identical then there is no point to insert the value inside the structure.
             therefore we will free the memory of the new node and then return false, which means that insertion is failed then
             we will eventually doing nothing else then maintain the same tree structure.
             */
            delete new_node;
            return false; // indicate insertion was not successful
        }
        
    }

    // definition of the find function
    template <typename T, typename S>
    typename bst<T, S>::iterator bst<T, S>::find(const T& target_value) const {

        if (!root) { // root is null (tree is empty)

            return iterator(nullptr, this); // past-the-end iterator
        }

        node* n = root; // start at the root

        while (true) { // loop until an iterator is returned

            // current node value contains correct value
            if (!pred(target_value, n->value) && !pred(n->value, target_value)) {

                return iterator(n, this); // iterator to node
            }

            // value less than current node value and left child exists
            else if (pred(target_value, n->value) && (n->left)) {

                n = n->left; // move left
            }

            // value greater than current node value and right child exists
            else if (pred(n->value, target_value) && (n->right)) {

                n = n->right; // move right
            }

            // value is not in tree
            else {

                return iterator(nullptr, this); // past-the-end iterator
            }
        }
        
    }

    // the definition of the erase function
    template <typename T, typename S>
    void bst<T, S>::erase(iterator iterator_to_erase) {

        // if the root is empty, then do nothing.
        if (!root)
        {
            return;
        } // if the target node does not have the both left and right child then run this code.
        else if (!iterator_to_erase.current_position->left && !iterator_to_erase.current_position->right)
        {

            // if the target node's parent does not exist that means that we are dealing with the root.
            if (iterator_to_erase.current_position->parent)
            {
                //current node is the root - set root to null before deleting
                root = nullptr;
            }
            else // if parent is exist, that means that the current node is not the root node
            {
                // if the deferenced value of erase target is smaller than the its parent value, that means it is the target value is placed on the left.
                if (pred(*iterator_to_erase, iterator_to_erase.current_position->parent->value))
                {
                    // then let the pointer from parents to erase target to be nullptr
                    iterator_to_erase.current_position->parent->left = nullptr;
                }
                else // if erase target value is bigger than the its parent value, then the target should placed on right.
                {
                    // then set the parent point to null on the right
                    iterator_to_erase.current_position->parent->right = nullptr;
                }
            }

            // after the pointers set to be null, then delete the target node and decrease the structure size.
            delete iterator_to_erase.current_position;

            --structure_size;

        }
        // or if the target node has only left child then run this code.
        else if (iterator_to_erase.current_position->left && !iterator_to_erase.current_position->right)
        {
            // then update the its left childs parents node as the parent node of the erase target.
            iterator_to_erase.current_position->left->parent = iterator_to_erase.current_position->parent;

            // if the current node is not exist, that means we are dealing with the current node as a root.
            if (!iterator_to_erase.current_position->parent)
            {
                // then update the its left child parents node as the parent node of the erase target.
                root = iterator_to_erase.current_position->left;
            }
            else { //if the current node has the parents then the current node is not the root.

                // if the erase target value is smaller than the its parents value, then target value is placed on the left
                if (pred(*iterator_to_erase, iterator_to_erase.current_position->parent->value))
                {
                    // then update the parent point to the current node's left child
                    iterator_to_erase.current_position->parent->left = iterator_to_erase.current_position->left;
                }
                else //otherwise, if the target value is placed on the right then run this code.
                {
                    // update the parent point ot the ccurrent node's right child
                    iterator_to_erase.current_position->parent->right = iterator_to_erase.current_position->left;
                }
            }

            // after erase all the link between the erase target to its parent and children then delete the node and free the memory.
            delete iterator_to_erase.current_position;

            // if the delete was successful, then decrease the size of the structure.
            --structure_size;
        }
        // if the current node has only child on the right then run this code
        else if (iterator_to_erase.current_position->right && !iterator_to_erase.current_position->left)
        {
            // update the right child point to the parent of the current node.
            iterator_to_erase.current_position->right->parent = iterator_to_erase.current_position->parent;

            // if the current node's parent does not exist, meaning that we are dealing with the current node.
            if (!iterator_to_erase.current_position->parent)
            {
                // then set the root as current node's right child.
                root = iterator_to_erase.current_position->right;
            }
            else // otherwise if the parent does exist then run this code inside
            {
                //if the target value is smaller than its parent value, meaning that the current node is placed on the left
                if (pred(*iterator_to_erase, iterator_to_erase.current_position->parent->value))
                {
                    // then set the node to the parent's left child
                    iterator_to_erase.current_position->parent->left = iterator_to_erase.current_position->right;
                }
                else //if the node to be deleted is a right child
                {
                    // then set the node to the parent's right child
                    iterator_to_erase.current_position->parent->right = iterator_to_erase.current_position->right;
                }
            }

            // after setting up the pointer between the nodes in the structure, now get rid of the current node.
            delete iterator_to_erase.current_position;

            // after you delete the node successfully then decrease the structure size
            --structure_size;
        }

        else //if the current node has two children
        {
            // first thing we do is that we need to swap the current element with the far left child from current element's right child.
            //keep track of the current location
            iterator temp = iterator_to_erase;

            //then move the temp iterator to the right and then reach the most far left for swap the value.
            temp.current_position = temp.current_position->right;

            //and as far left as possible
            while (temp.current_position->left)
            {
                temp.current_position = temp.current_position->left;
            }

            // Overwrite the given node’s value with the right-far-left value
            iterator_to_erase = temp;

            erase(temp); //recursively erase the temp node (which has 0 or 1 children)
        }
    }

    /* accepts variadic listand constructs a T and
    attempt to place within the tree */
    template <typename T, typename S>
    template <typename... Types>
    void bst<T, S>::emplace(Types&&... args) {

        // construct and insert an object of type T
        insert(T(std::forward<Types>(args)...));
    }

    // definition of the size function, enables to access the size of the structure.
    template <typename T, typename S>
    size_t bst<T, S>::size() const {
        return structure_size;
    }
}

#endif

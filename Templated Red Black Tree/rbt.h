#ifndef rbt_h
#define rbt_h

#include<iostream>
#include<stdexcept>
#include<utility>



namespace pic10c
{
    //enables ADL, once you using keyword to use ADL, the compiler will finds the best swap functions for variables.
    using std::swap;


    /**
    @class rbt: the class brt is the associative data structure that stores the data in specific order into the tree structure.
           if the data is randomly stored into the tree, this bst class does insert/find/erasing element in O(logn) complexity.
           and this class contains nested class node, and class iterator and const iterator.

     rbt class is designed to balance the structure using the red-black coloring technique. using this method, rbt class can prevent the structure to be formed one heavy side in the structrue to the others. in order to blance the structure, the rbt class will use the many different teqnique from the normal binary search tree classes.

     @tparam T :Datatype being stored
     @tparam S :this type is defining the order methods for comparing any data type of two variable. and the default type is std::less if the user does not specified.
     */
    template <typename T, typename S = std::less<T>>
    class rbt
    {
    public:
        
        /**
        @class iterator: the iterator class is designed to numbering the iterator of each nodes in specific way of ordering using the functional iterator.

        the iterator class construct the functional iterator how the node pointer should behave when they are locating the index of the structure.
        in the class iterator has the node pointer for the current_location to represent its location of the structure. and this function is friended with class bst to allow the bst class can access to the current_position.
        this class contains a constructor, destructor, and overloaded operator of prefix and postfix of ++ and -- and overloaded comparison operator == and !=  to compare the iterator variables.
        and last, dereferencing operator and operator arrow to get an access of the value in the nodes.

        */
        class iterator;
        class const_iterator;
        
        

        /**
        @class node
        @brief The node class is a nested class in rbt for holding T values and providing infrastructure for the tree
        
        the class node takes the role to assign the family relationship on the current node, such which node is the left or right child, and what's the current parent, sibling, uncle, granparent using family_relation_tracker() function. left rotate and right rotate is designed for the color correction prior to insertnode() function called. while the insertion is happening into the structure, the insert node will find its correct position for itself and after that, using a color correction, it will gives the right color in the structure, so the tree structure can find its balance during the insertion process.
         
        also there are other functions can help other functions in the different classes. for destruction process or getting the size of the structure etc.
        */
        class node
        {
        private:
            T value;
            node* left;
            node* right;
            node* parent;
            node* sibling;
            node* grandparent;
            node* uncle;
            S pred;

            bool double_black_status = false;

            bool black;
            rbt* container;

            //friend class templated_iterator;
            friend class rbt;

        public:
            
            /**
            constructor which initializes: vlaue, and set the all family related node to nullptr, and compare_type inforamtion, and the node* variable for root access.

            @param data this is the value that to initialize the value variable in the object.
            @param _pred this is the compare_type variable to compare while the find function is called in, to find the target value in order to remove that out of the structure.
            @param _container  is the node* type variable to let the node variables or iterator varaibles has the connection to its root directly.
            */
            node(T data, S _pred, rbt* _container) : value(data), left(nullptr), right(nullptr), parent(nullptr),
                sibling(nullptr), grandparent(nullptr), uncle(nullptr), pred(_pred), container(_container), black(false) {};
            
            /**
            this is the destructor declaration and definition, destructor is necessary because it must happen prior to the deallocation.
            thus, the destuctor is designed to delete every node in the tree strucutre and free the memory in the tree structure.
            once this function is called then it will call the deleteTree function which deletes all the element and the nodes out of the tree structure and free the memory so it make sure that there are no memory leaks before they end the program.
            */
            ~node() {}


            /**
            this is the helper function to get the size of the structure for the size function in the rbt class. this function will start from the root and goes down to its left and right child recursively everytime the function is over, will increase the size by one.
            
            @param _root is a const pointer to the root node for counting
            @return is the total numbers of node exist in the tree structure.
            */
            size_t size(const node* _root) const
            {
                // if the root is empty, then we will return as zero of size in the structure.
                if (_root == nullptr)
                {
                    return 0;
                } // otherwise if the structure is not empty, then we will go through the every single node in the structure recursively to get the right size.
                return (1 + size(_root->left) + size(_root->right));
            }
            
            /**
            this function is designed to track the family relation of the current node and set them in the right relationship for the insertion and deletion process.
            
            @param current_node is the node that the user wants to set the uncle, granparent, sibling relationship from the current node in the tree structure.
            */
            void family_relation_tracker(node* current_node)
            {
                // if the current_node does not exist then do nothing.
                if (current_node == nullptr)
                {
                    return;
                }
                
                // if the current node's left child does exist, then run this code.
                if (current_node->left)
                {
                    // if the left child does exist then set the right child as the sibling of the left child.
                    current_node->left->sibling = current_node->right;
                    // if the current node has the right child then run this code.
                    if (current_node->right)
                    {
                        // if the left child's sibling is set as the right child of the current node successfully, then run this code.
                        if (current_node->left->sibling)
                        {
                            current_node->left->sibling->sibling = nullptr;
                        }
                        // then set the left child of the current node as the right child sibling of the current node.
                        current_node->right->sibling = current_node->left;
                    }
                    
                    // after done setting up the sibling relations between two child, we will set the connection between the left child to its parent. and set the grandparent, uncle node of the current node. then recursively setting the family relations when it is going down to its left child.
                    current_node->left->parent = current_node;
                    current_node->left->grandparent = current_node->parent;
                    current_node->left->uncle = current_node->sibling;
                    family_relation_tracker(current_node->left);
                }
                
                // if the current node's right child does exist then run this code.
                if (current_node->right)
                {
                    // after we know there is a right child, then set the left child as the sibling of the right child.
                    current_node->right->sibling = current_node->left;
                    
                    // if also the current node has the left child then run this code.
                    if (current_node->left)
                    {
                        // if the right child's sibling does exist, then run this code.
                        if (current_node->right->sibling)
                        {
                            current_node->right->sibling->sibling = nullptr;
                        }
                        // then set the right child as the left child's sibling.
                        current_node->left->sibling = current_node->right;
                    }
                    
                    // after setting the children's relationship, then set the grandparent and the uncle node from the current node, and then go through recursion to set all the node's relation in the structure.
                    current_node->right->parent = current_node;
                    current_node->right->grandparent = current_node->parent;
                    current_node->right->uncle = current_node->sibling;
                    family_relation_tracker(current_node->right);
                }
            }


            /**
            this is the helper function for the insert() in the rbt class, this function will first
            @param node_to_insert is the node that the user wants to insert into the sturcutre.
            @param current_node is the node in the structure to see the possiblity of the insertion in the structure.
            @param node_to_promote this is the node that previosly one of the bottom node in the structure, but needs to be promote since there are new node is coming in
            @param leftInsert is a simple mechanism to ensure child is placed on correct side of parent
            */
            void insertNode(node* node_to_insert, node* current_node, node* node_to_promote = nullptr, bool leftInsert = true)
            {
                
                // if the current node does not exist then that's where we need to insert the node into the structure.
                if (current_node == nullptr)
                {
                    // then update the current node as the node that the user wants to insert into the structure.
                    current_node = node_to_insert;
                    // set the current node's parent as the node to promote.
                    current_node->parent = node_to_promote;
                    
                    // if child should be left of parent, insert left
                    if (leftInsert)
                    {
                        node_to_promote->left = current_node;
                        
                    }
                    else // insert right instead
                     {
                         node_to_promote->right = current_node;
                        
                    }
                    current_node->family_relation_tracker(current_node->parent);
                    if (!(current_node->parent->black)) {
                        correct_color_for_insertion(current_node);
                        current_node->family_relation_tracker(current_node->parent);
                    }


                } //if node exists, then we have to find the different location where is empty to insert the new node into the structure.
                else
                {
                
                    // check if the value inside the node is the less then what the current node holds as a value, if the insert target is smaller than the current node, then we have to go down to its left child to see the possiblity to insert into the structure.
                    if (pred(node_to_insert->value, current_node->value))
                    {
                        try
                        {
                            // then we will recursively go down its left child to see that the target node is the right place to insert into the structure
                            insertNode(node_to_insert, current_node->left, current_node);
                        }
                        catch (...) {} //should be present at the last of all the catches so if any try is not present in above catches it will go to catch(...)
                    }
                    else // check if the value inside the node is greater then what the current node holds as a value, if the insert target is bigger than the current node, then we have to go down its right child to see there are possiblity to insert into that location.
                    {
                        try
                        {
                            // then we will recursively go down its right child to see that the target node is the right place to insert into the structure
                            insertNode(node_to_insert, current_node->right, current_node, false);
                        }
                        catch (...) {} //should be present at the last of all the catches so if any try is not present in above catches it will go to catch(...)
                    }
                }
            }

            /*
            Left rotation function to help rebalance trees
            
             rotate_to_left function will demote the current node to the child of the current node's child and then left child of the current node will promote and become a new parent, then all the right child of the child of the current node will be shifted to the left child of the demoted current node.
            */
            void rotate_to_left()
            {
                //checks if parent is root
                if (this->grandparent)
                {
                    //checks if parent is right child
                    if (this->grandparent->right == this->parent)
                    {
                        
                        node* copy_grandparent = this->grandparent;
                        
                        node* copy_parent = this->parent;

                        // set the grandparents's right child as the current node.
                        copy_grandparent->right = this;
                        
                        // and set the current node's parent as the current grandparent node.
                        this->parent = copy_grandparent;
                        
                        // then set the parent's right child as the current node's left child, which means all the substructure belongs to the formal child of the current node will shifted to the formal current node as a child.
                        copy_parent->right = this->left;
                        
                        // check that the demoted parent succesfully has the right child and re-connect the link.
                        if (copy_parent->right)
                        {
                            copy_parent->right->parent = parent;
                            
                        }
                        
                        // and then make the formal current node become a child of the formal child node of its current node.
                        this->left = copy_parent;
                        copy_parent->parent = this;

                        //and this process will change the color.
                        bool red_or_black1 = copy_parent->black;
                        bool red_or_black2 = this->black;
                        this->black = red_or_black1;
                        copy_parent->black = red_or_black2;

                        //resets the family relationship based on the changed node structure.
                        family_relation_tracker(copy_parent->parent);
                        family_relation_tracker(copy_grandparent);

                    }
                    //otherwise if the parent node is the left child of its grandparent node, then run this statement
                    else if (this->grandparent->left == this->parent)
                    {
                        
                        node* copy_grandparent = this->grandparent;
                       
                        node* copy_parent = this->parent;

                        // now start the linking process between the child of the current node and the parent node of the current node to replace the loaction.
                        copy_grandparent->left = this;
                        this->parent = copy_grandparent;
                        copy_parent->right = this->left;
                        
                        // check that the demoted parent succesfully has the right child and re-connect the link.
                        if (copy_parent->right)
                        {
                            // then connect the right
                            copy_parent->right->parent = copy_parent;
                        }
                        
                        // now replace the current node and its child using this procedure.
                        this->left = copy_parent;
                        copy_parent->parent = this;

                        //performs recoloring
                        bool red_or_black1 = copy_parent->black;
                        bool red_or_black2 = this->black;
                        this->black = red_or_black1;
                        copy_parent->black = red_or_black2;

                        //resets relationships for future rebalancing
                        family_relation_tracker(copy_parent->parent);
                        family_relation_tracker(copy_grandparent);
                    }

                    //grandparent exists, but parent is not child of grandparent -- something went wrong
                    else { std::cout << "something went wrong during left rotation."; }
                }

                //parent is root
                else {
                    //symbolic copy of parent for syntactical ease
                    node* _parent = this->parent;

                    //performs rotation
                    _parent->right = this->left;
                    if (_parent->right != nullptr) { _parent->right->parent = _parent; }
                    this->left = _parent;
                    _parent->parent = this;

                    //this is now root node
                    this->parent = nullptr;
                    this->container->root = this;
                    this->sibling = nullptr;
                    this->uncle = nullptr;

                    //performs recoloring
                    bool b1 = _parent->black;
                    bool b2 = this->black;
                    this->black = b1;
                    _parent->black = b2;

                    //resets relationships for future rebalancing
                    family_relation_tracker(this);
                }

            }

            /*
            Right rotation function to help rebalance trees
            
             promotes node on which rotation is called to its parent's rank and demotes its parent to its child, rotation happens such that child on left of parent moves to parent's location and parent moves right and down, children of new parent become children of old parent
            */
            void rotateRight() {
                //checks if parent is root
                if (this->grandparent != nullptr) {
                    //parent is right child
                    if (this->grandparent->right == this->parent) {
                        //symbolic copy of grandparent for syntactical ease
                        node* copy_grandparent = this->grandparent;
                        //symbolic copy of parent for syntactical ease
                        node* copy_parent = this->parent;

                        //performs rotation
                        copy_grandparent->right = this;
                        this->parent = copy_grandparent;
                        copy_parent->left = this->right;
                        if (copy_parent->left != nullptr)
                        {
                            copy_parent->left->parent = parent;
                            
                        }
                        this->right = copy_parent;
                        copy_parent->parent = this;

                        //performs recoloring
                        bool b1 = copy_parent->black;
                        bool b2 = this->black;
                        this->black = b1;
                        copy_parent->black = b2;

                        //resets relationships for future rebalancing
                        family_relation_tracker(copy_parent->parent);
                        family_relation_tracker(copy_grandparent);
                    }
                    //parent is left child
                    else if (this->grandparent->left == this->parent) {
                        //symbolic copy of grandparent for syntactical ease
                        node* _grandparent = this->grandparent;
                        //symbolic copy of parent for syntactical ease
                        node* _parent = this->parent;

                        //performs rotation
                        _grandparent->left = this;
                        this->parent = _grandparent;
                        _parent->left = this->right;
                        if (_parent->left != nullptr) { _parent->left->parent = _parent; }
                        this->right = _parent;
                        _parent->parent = this;

                        //performs recoloring
                        bool black_or_red1 = _parent->black;
                        bool black_or_red2 = this->black;
                        this->black = black_or_red1;
                        _parent->black = black_or_red2;

                        //resets relationships for future rebalancing
                        family_relation_tracker(_parent->parent);
                        family_relation_tracker(_grandparent);
                    }
                    else { std::cout << "something went wrong during right rotation."; }
                }

                //parent is root
                else {
                    //symbolic copy of grandparent for syntactical ease
                    node* _parent = this->parent;

                    //performs rotation
                    _parent->left = this->right;
                    if (_parent->left != nullptr) { _parent->left->parent = _parent; }
                    this->right = _parent;
                    _parent->parent = this;

                    //this is now root node
                    this->parent = nullptr;
                    this->container->root = this;
                    this->sibling = nullptr;
                    this->uncle = nullptr;

                    //performs recoloring
                    bool b1 = _parent->black;
                    bool b2 = this->black;
                    this->black = b1;
                    _parent->black = b2;

                    //resets relationships for future rebalancing
                    family_relation_tracker(this);
                }
            }

            /**
            this function is designed to color the node during the insertion process. function recolors if the tree only needs to be recolored, otherwise calls rebalancing (rotation) functions to sort the tree.
            @param current_node is a semi-arbitrary entry-point for color correction
            */
            void correct_color_for_insertion(node* current_node)
            {

                //if rootNode
                if (current_node->parent == nullptr)
                {
                    current_node->black = true; // root must be black
                    current_node->container->root = current_node; // node is now container's root
                    return;
                }
                if (current_node->parent->black)
                {
                    return;
                    
                } // arbitrary call, nothing needs to be done
                else
                {
                    //if current_node has uncle, ask control flow for rotations/recursions
                    if (current_node->uncle != nullptr) {
                        //if node has black uncle, we need rotations on a case-by-case basis
                        if (current_node->uncle->black) {
                            // right right case, color correction happens in rotation
                            if (current_node->parent->right == current_node && current_node->grandparent->right == current_node->parent) {
                                current_node->parent->rotate_to_left();
                            }
                            // right left case, color correction happens in rotation
                            else if (current_node->parent->left == current_node && current_node->grandparent->right == current_node->parent) {
                                current_node->rotateRight();
                                current_node->rotate_to_left();
                            }
                            // left left case, color correction happens in rotation
                            else if (current_node->parent->left == current_node && current_node->grandparent->left == current_node->parent) {
                                current_node->parent->rotateRight();
                            }
                            //left right case, color correction happens in rotation
                            else if (current_node->parent->right == current_node && current_node->grandparent->left == current_node->parent) {
                                current_node->rotate_to_left();
                                current_node->rotateRight();
                            }

                        }
                        //if node has red uncle, we can simply recolor and recurse
                        else {
                            current_node->parent->black = true;
                            current_node->uncle->black = true;
                            current_node->grandparent->black = false;
                            correct_color_for_insertion(current_node->grandparent);
                        }
                    }
                    //if node does not have an uncle, we simply need to rotate.
                    else {
                        if (current_node->grandparent->right == current_node->parent) {
                            //color correction happens in rotation
                            current_node->parent->rotate_to_left();
                        }
                        else {
                            //color correction happens in rotation
                            current_node->parent->rotateRight();
                        }
                    }
                }
            }

            /**
            Find function used by iterator rbt::find()
            @param T is the value we are looking for in the tree
            @return is a node corresponding to the value, if found
            */

            node* find(T target_value) {
                //if input smaller than current node value
                if (pred(target_value, value)) {
                    if (!left) { //cannot continue
                        return nullptr; // value not found, return nullptr
                    }
                    //call find recursively to further cycle through rbt and search for value
                    else {
                        return left->find(target_value);
                    }
                }
                //if input larger than current node value
                else if (pred(value, target_value)) {
                    if (!right)
                    { //cannot continue
                        return nullptr; // value not found, return nullptr
                    }
                    //call find recursively to further cycle through rbt and search for value
                    else
                    {
                        return right->find(target_value);
                    }
                }
                //data and value match
                else {
                    return this; //return this for comparison
                }
            }

            /**
            this function is designed to destroy every single node in the structure, and helper function for the ~brt()
            @param node_to_delete nodes that needes to be destroyed.
            */

            void recursively_destroy(node* node_to_delete) {

                if (!node_to_delete) { return; } // doesn't exist, go back

                recursively_destroy(node_to_delete->left);
                recursively_destroy(node_to_delete->right);
                node_to_delete = nullptr; // set node to nullptr
                free(node_to_delete); // free memory from node

            }




};
















        class iterator
        {
            friend rbt;

        public:
            iterator(node* _current_node, const rbt* _container) : current_node(_current_node), container(_container) {};
            ~iterator() {};


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
                if (current_node->right)
                {
                    // move to the right child node
                    current_node = current_node->right;

                    // then find the furtest left child node and keep going down to left child until find the node that doesn't have the left child.
                    while (current_node->left)
                    {
                        // move to the left child.
                        current_node = current_node->left;
                    }
                }
                else // if there are no right child exist from the current node, then run the code inside this bracket.
                {
                    // create the new node to store the parent node information of the current node.
                    node* its_parents = current_node->parent;

                    // if the parent node is exist and the current node is placed on the right child of its parents,
                    // then we have to move up to the parent of parent node to see that there is right child.
                    while (its_parents && (current_node == its_parents->right))
                    {
                        // then move up the current nodes up to its parents.
                        current_node = its_parents;
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
                    if (current_node->parent)
                    {
                        current_node = current_node->parent;
                        return *this;
                    }
                    else // if the current position does not have the parent then we are dealing with the root node therefore, return the iterator past end.
                    {
                        current_node = nullptr;
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
                if (current_node->left)
                {
                    current_node = current_node->left;

                    // then if the left child exist, knowing that the right child always has less priority to get iterated.
                    // thus keep moving down to its far most right child in the structure.
                    while (current_node->right)
                    {
                        current_node = current_node->right;
                    }

                }
                else // when there is no left child of the current node, then we have to find the previous iterator from one of parent node in the sturcuture.
                {
                    // create the new node to store the parent node information of the current node.
                    node* its_parents = current_node->parent;

                    // if the current node is located at its parent's left child, then move up to the parents and keep update the current node's parent node
                    // if the current node is the parent's left child, then there are no possibility you can find the previous iterator with moving down to the
                    // left child, that's why we will keep move up the parent node until we find the parent node that might possibly can have the left child node.
                    // (meaning that, current node is not the left child of its parent.)
                    while (current_node == its_parents->left)
                    {
                        current_node = its_parents;
                        its_parents = its_parents->parent;
                    }

                    /*
                        if the loop runs that means that the current node is not the left child of its parent node anymore,
                        then with running the condition, if there is parent exist, then finally current node moves up to the parent might possibly have
                        left child.

                        othewise if the parents does not exist, which meaning that it reached the roots of the structure, thus current position will be nullptr
                        and return the iterator.
                    */
                    if (current_node->parent)
                    {
                        //move to parent and end
                        current_node = current_node->parent;
                        return *this;
                    }
                    else //else, return one space past end
                    {
                        current_node = nullptr;
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
                ++current_node;

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
                --current_node;

                return copied_node;
            }

            /**
            overloaded == comparison operator, which compares the two iterator variable which are, left_hand_side and right_hand_side.

            @param left_hand_side : is the iterator variable on the left side of the operator.
            @param right_hand_side : is the iterator varaible on the right side of the operator for comparison.
            @return it will return ture if both left and right hand side iterator are equal and false if not.
            */
            friend bool operator==(const iterator& left_hand_side, const iterator& right_hand_side)
            {

                return (left_hand_side.current_node == right_hand_side.current_node) && (left_hand_side.container == right_hand_side.container);
            }

            /**
            overloaded != comparison operator, which compares the two iterator variables which are, left_hand_side and right_hand_side.

            @param left_hand_side : is the iterator variable on the left side of the operator.
            @param right_hand_side : is the iterator variable on the right side ofthe operator for comparison.
            @return it will return true if right and left hand side are not equal if it is equal then return false.
            */
            friend bool operator!=(const iterator& left_hand_side, const iterator& right_hand_side)
            {

                return !(left_hand_side == right_hand_side);
            }

            /**
            overload dereferencing operator (without modifying tree element).
            once this function is called then the function will acess value stored in the current node and return the value.


            @return it will return value in the current node in any data type.
            */
            const T& operator*() const
            {
                return current_node->value; // value contained by current node
            }

            /**
            overload arrow operator as a member function.
            this purpose of this function is same which is that access values stored in the current node and return the value.
            but the difference is that this function will return the current position dereferenced.

            @return the current position dereferences
            */
            const T* operator->() const
            {
                return &current_node->value; // value contained by current node
            }








        private:
            node* current_node;
            const rbt* container;

        };


        class const_iterator
        {
            friend class rbt;

        public:
            const_iterator(node* _current_node, const rbt* _container) : current_node(_current_node), container(_container) {};

            /**
            this function is designed to move onto the next iterator in the tree structure.
            According to the slides, to move forward from one node to the next, in current node location, we will first check that there is a right child node exist, then move it to the right child
            and from that we will take the most far left child node. if the function moves down the far left child, then that will be the next iterator from the formal iterator.

            or if the node current_position does not have the right child, then move the current node up to the its parent node and keep continues until the parent node has the right child.
            once the function finds the parents has the right child then, return the iterator of the structure.

            @return *this, which is the current instance iterator
            */
            const_iterator& operator++()
            {
                //if the current_position's right child is exist, then run the code inside the braket.
                if (current_node->right)
                {
                    // move to the right child node
                    current_node = current_node->right;

                    // then find the furtest left child node and keep going down to left child until find the node that doesn't have the left child.
                    while (current_node->left)
                    {
                        // move to the left child.
                        current_node = current_node->left;
                    }
                }
                else // if there are no right child exist from the current node, then run the code inside this bracket.
                {
                    // create the new node to store the parent node information of the current node.
                    node* its_parents = current_node->parent;

                    // if the parent node is exist and the current node is placed on the right child of its parents,
                    // then we have to move up to the parent of parent node to see that there is right child.
                    while (its_parents && (current_node == its_parents->right))
                    {
                        // then move up the current nodes up to its parents.
                        current_node = its_parents;
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
                    if (current_node->parent)
                    {
                        current_node = current_node->parent;
                        return *this;
                    }
                    else // if the current position does not have the parent then we are dealing with the root node therefore, return the iterator past end.
                    {
                        current_node = nullptr;
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
            const_iterator& operator--()
            {
                // if the current node's left child is exist, then move to its left child.
                if (current_node->left)
                {
                    current_node = current_node->left;

                    // then if the left child exist, knowing that the right child always has less priority to get iterated.
                    // thus keep moving down to its far most right child in the structure.
                    while (current_node->right)
                    {
                        current_node = current_node->right;
                    }

                }
                else // when there is no left child of the current node, then we have to find the previous iterator from one of parent node in the sturcuture.
                {
                    // create the new node to store the parent node information of the current node.
                    node* its_parents = current_node->parent;

                    // if the current node is located at its parent's left child, then move up to the parents and keep update the current node's parent node
                    // if the current node is the parent's left child, then there are no possibility you can find the previous iterator with moving down to the
                    // left child, that's why we will keep move up the parent node until we find the parent node that might possibly can have the left child node.
                    // (meaning that, current node is not the left child of its parent.)
                    while (current_node == its_parents->left)
                    {
                        current_node = its_parents;
                        its_parents = its_parents->parent;
                    }

                    /*
                        if the loop runs that means that the current node is not the left child of its parent node anymore,
                        then with running the condition, if there is parent exist, then finally current node moves up to the parent might possibly have
                        left child.

                        othewise if the parents does not exist, which meaning that it reached the roots of the structure, thus current position will be nullptr
                        and return the iterator.
                    */
                    if (current_node->parent)
                    {
                        //move to parent and end
                        current_node = current_node->parent;
                        return *this;
                    }
                    else //else, return one space past end
                    {
                        current_node = nullptr;
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
            const_iterator operator++(int)
            {
                node* copied_node(*this);
                ++current_node;

                return copied_node;
            }


            /**
            this function is overloaded postfix operator --
            after they create the node for copy to copy all the information that current node has and then going through the exact same process as what prefix function -- does.
            once they update the current node, then they return the previous information of current node before it was updated.

            @param unused inform compiler that function is for postfix
            @return return the copied_node.
            */
            const_iterator operator--(int)
            {
                node* copied_node(*this);
                --current_node;

                return copied_node;
            }
            

            /**
            overloaded == comparison operator, which compares the two iterator variable which are, left_hand_side and right_hand_side.

            @param left_hand_side : is the iterator variable on the left side of the operator.
            @param right_hand_side : is the iterator varaible on the right side of the operator for comparison.
            @return it will return ture if both left and right hand side iterator are equal and false if not.
            */
            friend bool operator==(const const_iterator& left_hand_side, const const_iterator& right_hand_side)
            {

                return (left_hand_side.current_node == right_hand_side.current_node) && (left_hand_side.container == right_hand_side.container);
            }

            /**
            overloaded != comparison operator, which compares the two iterator variables which are, left_hand_side and right_hand_side.

            @param left_hand_side : is the iterator variable on the left side of the operator.
            @param right_hand_side : is the iterator variable on the right side ofthe operator for comparison.
            @return it will return true if right and left hand side are not equal if it is equal then return false.
            */
            friend bool operator!=(const const_iterator& left_hand_side, const const_iterator& right_hand_side)
            {

                return !(left_hand_side == right_hand_side);
            }

            /**
            overload dereferencing operator (without modifying tree element).
            once this function is called then the function will acess value stored in the current node and return the value.


            @return it will return value in the current node in any data type.
            */
            const T& operator*() const
            {
                return current_node->value; // value contained by current node
            }

            /**
            overload arrow operator as a member function.
            this purpose of this function is same which is that access values stored in the current node and return the value.
            but the difference is that this function will return the current position dereferenced.

            @return the current position dereferences
            */
            const T* operator->() const
            {
                return &current_node->value; // value contained by current node
            }


        private:
            node* current_node;
            const rbt* container;


        };

        //constructors, which default pred to less
        rbt<T, S>() : pred(S{}), root(nullptr) {};
        rbt<T, S>(S _pred) : pred(_pred), root(nullptr) {};


        //swap constructor
        rbt<T, S>(rbt&& rhs) noexcept : rbt() {
            std::swap(root, rhs.root);
        };

        //copy constructor
        rbt<T, S>(const rbt& rhs) noexcept : rbt() {
            root = rhs.root;
        };

        //copy operator
        rbt& operator=(const rbt& rhs) {
            root = rhs.root;
            return *this;
        }

        //move operator
        rbt& operator=(rbt&& rhs) {
            root = std::move(rhs.root);
            return *this;
        }

        //swap func
        void swap(rbt&& rhs) {
            std::swap(this, rhs);
        }

        //destructor which calls recursive destruction on root
        ~rbt() {
            if (root != nullptr) {
                try { root->recursively_destroy(root); }
                catch (...) {} // std::cerr << "bad_alloc caught: " << ba.what() << '\n'; is what I want, but no iostream allowed
            }

        }

        //insertion call for 1 arg which forwards to 2 arg insert with root as refNode
        void insert(const T& data) {
            insert(data, root);
        }

        /**
        insertion call for 2 args which initializes a pointer to a new node with type T data and calls
        insertNode on specified refNode for proper insertion
        @tparam data is an arbitrary type of data for insertion in the tree
        @param refNode is the node on which we want to call insertNode later for insertion
        */
        void insert(const T& data, node* refNode) {
            //initialization of new node
            node* new_node = new node(data, pred, this);
            //if root is nullptr, place new_node at root
            if (refNode == nullptr) {
                new_node->black = true;
                if (new_node->parent == nullptr) {
                    new_node->container->root = new_node;
                }
            }
            //else call the recursive insertNode function on new_node to find appropriate location
            else {
                node* new_node2 = refNode->find(data); //call find to ensure no duplicates
                if (new_node2 == nullptr) { //compare find return
                    refNode->insertNode(new_node, refNode);
                }
                else { return; }
            }
        }

        /**
        forwarding function for recursive_print function,
        also prints line for ease of eyes
        */
        void print() {
            recursive_print(root, 0);
            std::cout << "----------------------";
        }

        /**
        recursive function to print tree in a left-right fashion
        @param start is a root from which we will print from left to right
        @param num_spaces is the number of spaces to print before current tree node
        */
        void recursive_print(const node* start, size_t num_spaces) {
            //already printed root
            if (start == nullptr) {
                return;
            }

            //6 is arbitrary number of spaces to print for aesthetic
            num_spaces += 6;

            //recursively print value to right
            recursive_print(start->right, num_spaces);

            std::cout << '\n';
            //print spaces
            for (int i = 6; i < num_spaces; ++i) {
                std::cout << " ";
            }
            //is root, print -
            if (start->parent == nullptr) {
                std::cout << "-";
            }
            //is right child, print /
            else if (start == start->parent->right) {
                std::cout << '/';
            }

            /* is left child, print \ */
            else {
                std::cout << '\\';
            }
            std::cout << start->value;

            //print colors
            if (!(start->black)) {
                std::cout << "(r)\n";
            }
            else {
                std::cout << "(b)\n";
            }
            //recursively print to left
            recursive_print(start->left, num_spaces);
        }

        /**
        creates a new object based on variadic list of params and calls insert for tree insertion
        @tparam arg1 is our variadic list of parameters that are appropriately forwarded to create
        an object, and then inserted into the tree
        */
        template<typename... args>
        void emplace(args&&... arg1) {
            //forwards args from variadic list into T constructor
            T forAddition(std::forward<args>(arg1)...);
            //calls insert to use standard method of insertion on newly constructed T
            this->insert(forAddition);
        }

        /**
        this function is designed to set the iterator to a begin position

        @return the const_iterator that is set to the begin postion of the structure
        */
        iterator begin()
        {
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
        
        /**
        this function is designed to set the iterator to a begin position

        @return the const_iterator that is set to the begin postion of the structure
        */
        const_iterator begin() const
        {
            // check that if the root is empty that means the whole structure is empty.
                   if (!root) {

                       // since the structure is empty then return the nullptr.
                       return const_iterator(nullptr, this);
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
                   return const_iterator(n, this);
        }


        /**
        this function is designed to set the iterator to an end position

        @return the constructor of const_iterator which initializes the node current_position as the nullptr which is the past-end-position.
        */
        const_iterator end() const {
            //return the iterator to nullptr.
            return const_iterator(nullptr, this);
        }

        /**
        this function is designed to set the iterator to an end position

        @return the constructor of iterator which initializes the node current_position as the nullptr which is the past-end-position.
        */
        iterator end() {
            //return the iterator to nullptr.
            return iterator(nullptr, this);
        }

        
        /**
         this function is designed to find the location of the node in the structure what the user wants to find, to do that, we need to start from the root node of the structure, and recursively going down comparing the current node value and the target value until it finds the match.
         
         @param target_value the value that the user wants to find the location in the structure.
         @param current_node a current node that is going to compare the value inside the node with the target value that the user specify.
         @return an iterator object that contains the information of the node and the rbt object.
         */
        iterator traverse_find(const T& target_value, node* current_node)
        {
            //if the root is empty then the structure is empty therefore we will return a constructor initializes that the current node as the empty and the rbt object.
            if (!current_node)
            {
                return iterator(nullptr, this);
            } // otherwise if the target valus is less then the current node value, then we will run the recursion and going down the left child of current node until we finds the match.
            else if (pred(target_value, current_node->value))
            {
                return traverse_find(target_value, current_node->left);
            } // otherwise if the target value is greater than the current node value, then we will run the recursion and going down the right child of the current node until we finds the match.
            else if (pred(current_node->value, target_value))
            {
                return traverse_find(target_value, current_node->right);
            }
            else // if the target value is not less than or greater than the current node value, that means we found the match, therefore, we return the iterator contains the information of the node.
            {
                return iterator(current_node, this);
            }
        }
        
        
        
        /**
         this function is designed to find the location of the node in the structure what the user wants to find, to do that, we need to start from the root node of the structure, and recursively going down comparing the current node value and the target value until it finds the match.
         
         @param target_value the value that the user wants to find the location in the structure.
         @param current_node a current node that is going to compare the value inside the node with the target value that the user specify.
         @return a const iterator object that contains the information of the node and the rbt object.
         */
        const_iterator const_traverse_find(const T& target_value, node* current_node) const
        {
            //if the root is empty then the structure is empty therefore we will return a constructor initializes that the current node as the empty and the rbt object.
            if (!current_node)
            {
                return const_iterator(nullptr, this);
            } // otherwise if the target valus is less then the current node value, then we will run the recursion and going down the left child of current node until we finds the match.
            else if (pred(target_value, current_node->value))
            {
                return const_traverse_find(target_value, current_node->left);
            } // otherwise if the target value is greater than the current node value, then we will run the recursion and going down the right child of the current node until we finds the match.
            else if (pred(current_node->value, target_value))
            {
                return const_traverse_find(target_value, current_node->right);
            }
            else // if the target value is not less than or greater than the current node value, that means we found the match, therefore, we return the iterator contains the information of the node.
            {
                return const_iterator(current_node, this);
            }
        }
        
        
        /**
        this function is designed to find the value that user wants to find from the rbt object.
         
         @param target_value the value that the user wishes to find, and this will go through the traverse_find function to go through the whole structure using recursion.
         @return an iterator object contains the information of the node and the rbt object.
         */
        iterator find(const T& target_value) {
            return traverse_find(target_value, root);
        }
        
        
        /**
        this function is designed to find the value that user wants to find from the rbt object.
         
         @param target_value the value that the user wishes to find, and this will go through the traverse_find function to go through the whole structure using recursion.
         @return an iterator object contains the information of the node and the rbt object.
         */
        const_iterator find(const T& target_value) const {
            return const_traverse_find(target_value, root);
        }

        /**
         swap member function, it will swap all the information of what the rbt object contains,
         
         @param other_red_black_tree is the rbt object that wants to be swapped from the current rbt object.
         */
        void swap(rbt& other_red_black_tree)
        {
            std::swap(root, other_red_black_tree.root);
            std::swap(structure_size, other_red_black_tree.structure_size);
            std::swap(pred, other_red_black_tree.pred);
        }


        /**
         this is the correction color function while the deletion process is going on
         
         @param node_to_delete is the node that the user wants to delete, but the correction first before the program initiates the erase process.
         */
        void correct_color_while_deletion(node* node_to_delete)
        {
            node* copy_sibling = node_to_delete->sibling;
            node* copy_parent = node_to_delete->parent;

            // case 1.1: if the target node has one red child then remove the current node and recolor the child as black node.
            if (node_to_delete->left && node_to_delete->left->black == false && node_to_delete->double_black_status == false)
            {
                node_to_delete->left->black = true;
                return;
            } // case 1.2: if the target node has one red child as the right child node, then re-color the child as black and reset the family tree relationship.
            else if (node_to_delete->right && node_to_delete->right->black == false && node_to_delete->double_black_status == false)
            {
                node_to_delete->right->black = true;
                return;
            } // case 2: if the target node is the red and has no children, in this case, just remove the node
            else if (node_to_delete->left == nullptr && node_to_delete->right == nullptr && node_to_delete->black == false && node_to_delete->double_black_status == false)
            {
                return;
            } // case 3: if the target node is the black and has no children, in this case, we have to go through the double black removal procedure.
            else if (node_to_delete->black == true && node_to_delete->right == nullptr && node_to_delete->left == nullptr)
            {
                node_to_delete->double_black_status = true;
            }



            // we now need to go into the sub-cases for the double black cases.
            if (node_to_delete->double_black_status == true)
            {
                // case 3.1: if the double black target node is the root then we just return to the normal case.
                if (node_to_delete->parent == nullptr)
                {
                    node_to_delete->double_black_status = false;
                    return;
                } // case 3.2: if the double black target node has the red sibling as the right child then run this case
                else if (node_to_delete->sibling->black == false && node_to_delete->parent->left == node_to_delete)
                {
                    copy_parent->rotate_to_left();
                    copy_parent->black = false;
                    copy_sibling->black = true;
                    // recurse the function again to see there is more process can be done.
                    correct_color_while_deletion(node_to_delete);
                } // case 3.3: if the double black target node has the black sibling as the right child and also the sibling has the left red child, and right black child, then run this case.
                else if (node_to_delete->sibling->left && copy_sibling->black == true && (node_to_delete->parent->left == node_to_delete) && ((node_to_delete->sibling->left->black == false) && (node_to_delete->sibling->right->black == true)))
                {
                    node* store_node_for_color_change = copy_sibling->left;
                    copy_sibling->rotateRight();
                    std::swap(node_to_delete->sibling->black, store_node_for_color_change->black);
                    correct_color_while_deletion(node_to_delete);
                } // case 3.4: if the double black target node has the black sibling and has the red right child from the black sibling then run this case.
                else if (node_to_delete->sibling && copy_sibling->right&& copy_sibling->black == true && (node_to_delete->parent->left == node_to_delete) && (copy_sibling->right->black == false))
                {

                    // and this break into the two subcases
                    // case 3.4.1: if the target node has the red parent.
                    if (node_to_delete->parent->black == false)
                    {
                        node* siblings_right_child = node_to_delete->sibling->right;
                        copy_sibling->rotate_to_left();
                        copy_sibling->black = false;
                        node_to_delete->parent->black = true;
                        node_to_delete->double_black_status = false;
                        siblings_right_child->black = true;

                    } // case 3.4.2: if the target node has the black parent.
                    else
                    {
                        node* copy_node_for_color = node_to_delete->sibling->right;
                        copy_sibling->rotate_to_left();
                        node_to_delete->double_black_status = false;
                        copy_node_for_color->black = true;
                    }
                } //case 3.5: if the target node is double-black and has a black sibling node.  and the Both children of sibling node are black.
                else if (node_to_delete->sibling->black == true && node_to_delete->right && copy_sibling->right->black == true && copy_sibling->left->black == true)
                {
                    // if the parent node of the target node is red then run this statement.
                    if (copy_parent->black == false)
                    {
                        // recolor the parent node as black
                        copy_parent->black = true;
                        // now turn off the double black status;
                        node_to_delete->double_black_status = false;
                        // now re-color the sibling node as red
                        node_to_delete->sibling->black = false;
                    }
                    else // otherwise if the parent node of the target node is black then run this statement.
                    {
                        copy_sibling->black = false;
                        node_to_delete->parent->double_black_status = true;
                        node_to_delete->double_black_status = false;
                        correct_color_while_deletion(node_to_delete->parent);
                    }
                }






            }


        }

        void erase(iterator target_node)
        {

            // if the target node has no children then run this code inside.
            if (target_node.current_node->left == nullptr && target_node.current_node->right == nullptr)
            {
                // first, correct the color of the target node before we redirect the link and delete the node.
                correct_color_while_deletion(target_node.current_node);
                
                // after we delete the node, we will set the tmep parent
                node* temp_parent = target_node.current_node->parent;
                
                // if the parent does exist, and also the current node is the left child of its parent then run this code inside.
                if (temp_parent && (target_node.current_node->parent->left == target_node.current_node))
                {
                    //we will disconnect the link between target node and its parent for the deletion process.
                    temp_parent->left = nullptr;
                } // if the target parent exist and the target node is the right child of its parent, then this code.
                else if (temp_parent && !(target_node.current_node->parent->right == target_node.current_node))
                {
                    // then disconnect the link between the target node and its parent for the deletion process.
                    temp_parent->right = nullptr;
                }
                
                // then completely end the connection between the target node and its parents for the delete process.
                target_node.current_node->parent = nullptr;
                delete target_node.current_node;
                
                // decrease the size of the structure.
                --structure_size;
                
                //if the tree structure is empty then set the root node empty.
                if (structure_size == 0)
                {
                    root = nullptr;
                }
                return;
            } //if we know that the target node's left child does not exist, then we have to check the right child.
            else if (!target_node.current_node->left)
            {
                // first, we will check the color of the curret node and its family's color to set the color in the right way.
                correct_color_while_deletion(target_node.current_node);
                node* temp_curr_node = target_node.current_node;
                
                //if we are at the root, then we need to get remove the target node and promote its child to replace its position.
                if (target_node.current_node == root)
                {
                    
                    
                    // we will set the temp curr node to store the node inside temporary.
                    temp_curr_node = target_node.current_node->right;
                    
                    // then update the current node as its right child of the target node to replace.
                    target_node.current_node = temp_curr_node;
                    
                    // after you replace the target node as its right child, then you re done, now delete the right child of the target node.
                    delete target_node.current_node->right;
                    
                    // update the root
                    root = target_node.current_node;
                    --structure_size;
                    return;
                }
                else // otherwise if the target node is not located at the root of the structure, then you run this statement.
                {
                    // we will set the temp curr node to store the node inside temporary.
                    temp_curr_node = target_node.current_node->right;
                    
                    // then update the current node as its right child of the target node to replace.
                    target_node.current_node = temp_curr_node;
                    
                    // disconnect the link betwwen the right child of the delete target then delete the node.
                    target_node.current_node->right = nullptr;
                    delete target_node.current_node->right;
                    
                    // update the size of the structure.
                    --structure_size;
                    return;
                }
            } // if we know that the target node's right child does not exist, then we have to check the left child.
            else if (!target_node.current_node->right)
            {
                node* temp_curr_node;
                // correct the color before we are going through the deletion process
                correct_color_while_deletion(target_node.current_node);
                
                //if the target node is located at the root of the structure, then run this statement.
                if (target_node.current_node == root)
                {
                    // we will set the temp curr node to store the node inside temporary.
                    temp_curr_node = target_node.current_node->right;
                    
                    // then update the current node as its left child of the target node to replace.
                    target_node.current_node = temp_curr_node;
                    
                    delete target_node.current_node->left;
                    
                    // update the root, since we have the new root value.
                    root = target_node.current_node;
                    --structure_size;
                    return;
                }
                else //otherwise if the target node is not located at the root of the structure, then run this scope.
                {
                    // we will set the temp curr node to store the node inside temporary.
                    temp_curr_node = target_node.current_node->right;
                    
                    // then update the current node as its left child of the target node to replace.
                    target_node.current_node = temp_curr_node;
                    
                    // disconnect between the left child of target node out of the structure.
                    target_node.current_node->left = nullptr;
                    delete target_node.current_node->left;
                    --structure_size;
                    return;
                }
            }
            else //if the target node has the both children, then run this statement.
            {
                
                iterator temp_curr = target_node;
                
                // move it to the right and move down left as much as possible like the operator++ behaves.
                temp_curr.current_node = temp_curr.current_node->right;
                while (temp_curr.current_node->left != nullptr)
                {
                    temp_curr.current_node = temp_curr.current_node->left;
                }
                
                // once you reached very far left of the structure, then update the value from the temp current node.
                target_node.current_node->value = temp_curr.current_node->value;
                
                
                
                // then recursively using the same function to find the right case for deletion.
                erase(temp_curr);
                
                
            }
        }


        

        //calls root size function
        size_t size() {
            structure_size = root->size(root);
            return structure_size;
        }






    private:

        node* root;
        S pred;
        size_t structure_size;

        friend class node;








    };

    /**
    this is the free swap function to swap two rbt objects.
     
     @param red_black_tree1 is the rbt object to swap
     @param red_black_tree2 is the rbt object to swap
     */
    template<typename T, typename compare_type = std::less<T>>
    void swap(rbt<T, compare_type>& red_black_tree1, rbt<T, compare_type>& red_black_tree2)
    {   // using the rbt class swap member function
        red_black_tree1.swap(red_black_tree2);
        return;
    }

}





#endif /* rbt_h */



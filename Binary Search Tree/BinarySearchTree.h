#ifndef __BINARYSEARCHTREE__
#define __BINARYSEARCHTREE__

#include <iostream>
#include <vector>
#include <stdexcept>
#include <iostream>

//namespace keeps Tree, node, and iterator classes unique in this namespace
namespace pic10b {
    /**
     Tree Class functions of a binary search tree.
     */
    class Tree {
    private:
        /**
         Nested node class
         */
        class node;

        node* root; //the root of the Tree
        std::size_t sz; //keeps the number of elements in the tree

        /**
         Recursively deletes the tree nodes, deletes nodes moving upwards from bottom
         @param n the node to be deleted
         */
        void deleteTree(node* n);

        /**
         Helps with copying of tree data
         @param n the node
         */
        void traverseInsert(node* n);
    public:


        class iterator; //must be public for operator!=

        /**
         Default constructor for our binary tree
         */
        Tree();

        /**
         Destructor for the tree
         */
        ~Tree();

        /**
         Copy constructor
         @param tree this is the other tree to be copied
         */
        Tree(const Tree& rhs);

        /**
         Move constructor
         @param tree is the other tree to be moved
         */
        Tree(Tree&& rhs);

        /**
        Swaps two trees
        visible at the pic10b namespace level
        @param tree the other tree to be swapped
        */
        void swap(Tree& tree);

        /**
         the assignment operators
         @param rhs the tree to be moved
         */
        Tree& operator=(Tree rhs);

        /**
         inserts a double value to the tree
         @param val the double value to be inserted
         */
        void insert(double val);

        /**
          Erases a value
          @param itr the iterator with the position to be deleted
          */
        void erase(iterator itr);

        /**
         Sets the iterator to a begin position
         @return the iterator that is set to begin position
         */
        iterator begin() const;

        /**
         Sets the iterator to an end position
         @return the iterator that is set to end position
         */
        iterator end() const;

        /**
         returns the number of elements in the Tree
         @return size
         */
        std::size_t size() const;

        /**
           Checks to see if the tree has a double
           def returns the iterator to the node with a given value
           if found and otherwise returning the past-the-end iterator.
           @param _val the specific double
           @return true if found, false if not
       */
        iterator find(double val);
    };

    class Tree::node {
        friend Tree;
        friend iterator;
    private:

        /**
         Constructor
         @param _val the double value from which the node will be created
         */
        node(double _val);
        node* left, * right, * parent; //pointers to the nodes surrounding the current node
        double val; // data value stored

        /**
         Recursive function passes a new node between existing nodes until it has reached its proper location.

         @param n the node to be inserted
         @return true if the node is inserted (is unique), false if the node is not inserted (is a duplicate of an existing node)
         */
        bool insertNode(node* n);
    };

    class Tree::iterator {
        friend Tree; //to allow iterator modifications by Tree operations
    private:
        /**
         Constructor
         @param n the curr node
         @param tree the tree that the iterator will go through
         */
        iterator(node* n, const Tree* container);
        node* curr; //the node at the current location
        const Tree* container; //the Tree iterator manages
    public:

        /**
        Prefix ++ operator
        @return the updated iterator
        */
        iterator& operator++();

        /**
        Postfix ++ operator
        @param unused informs compiler that function is for postfix
        @return the copy of the iterator
        */
        iterator operator++(int);

        /**
        Prefix-- operator
        @return the updated iterator
        */
        iterator& operator--();

        /**
        Postfix -- operator
        @param unused informs compiler that function is postfix
        @return the copy of the iterator
        */
        iterator operator--(int unused);



        /**
        Dereferencing operator
        @return the double at the current node
        */
        double& operator*() const;

        /**
        Arrow operator
        @return the current position dereferenced
        */
        double* operator->() const;

        /**
        Compares two iterators

        @param left iterator
        @param right]iterator for comparison
        @return true if both are equal and false if not
        */
        bool operator==(const iterator& rhs) const; // comparisons
    };

    /**
   Compares two iterators to see if they are different

   @param left iterator
   @param right iterator for comparison
   @return true if iterators are different and false if they are the same
   */
    bool operator!=(const Tree::iterator& lhs, const Tree::iterator& rhs);

    /**
     Swaps two trees
     @param left a tree to be swapped
     @param right the other tree to be swapped
     */
    void swap(Tree& left, Tree& right);
}

#endif

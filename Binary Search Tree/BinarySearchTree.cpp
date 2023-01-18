#include "BinarySearchTree.h"


namespace pic10b {
    // Default constructor for tree
    Tree::Tree() : root(nullptr), sz(0) {}

    Tree::~Tree() {
        deleteTree(root); //calls a recursive functions on all the nodes to delete
    }

    Tree::Tree(const Tree& rhs) : root(nullptr), sz(rhs.sz) {
        traverseInsert(rhs.root); //calls a recursive function on all the  nodes to copy
    }

    Tree::Tree(Tree&& rhs) : root(rhs.root), sz(rhs.sz) {
        rhs.root = nullptr; //set rhs to an empty tree
        rhs.sz = 0; //with size 0
    }

    // Swap member function
    void Tree::swap(Tree& tree) {
        std::swap(root, tree.root); // swaps root
        std::swap(sz, tree.sz); // swaps size
    }


    Tree& Tree::operator=(Tree rhs) {
        pic10b::swap(*this, rhs); //copy swap idiom lets this work for both copy and move assignment
        return *this; //return this Tree with the new values
    }

    void Tree::insert(double val) {
        if (root == nullptr) { //if root is empty
            root = new node(val); //make a node with given value the root
            ++sz; //node added
        }
        else { //if there is already a root
            node* n = new node(val); //create a new node
            if (root->insertNode(n)) { //recursively pass to nodes until in place
                ++sz; //if node successfully added, increase size
            }
        }
    }

    void Tree::erase(Tree::iterator itr) {
        if (root == nullptr) //if there's no tree to begin with
            return; //do nothing

        else if (itr.curr->left == nullptr && itr.curr->right == nullptr) { //if current node has no children
            if (itr.curr->parent == nullptr) { //if parent is nullptr
                root = nullptr; //current node is the root - set root to null before deleting
            }
            else { //if the current node is not the root
                if (*itr < itr.curr->parent->val) { //if the node to be deleted is a left child
                    itr.curr->parent->left = nullptr; //have the parent point to null on the left
                }
                else { //if the node to be deleted is a right child
                    itr.curr->parent->right = nullptr; //have the parent point to null on the right
                }
            }
            delete itr.curr; //get rid of the current node
            --sz; //delete successful, decrease size
        }

        else if (itr.curr->left != nullptr && itr.curr->right == nullptr) { //if the current node has only one child on the left
            itr.curr->left->parent = itr.curr->parent; //set the child's parent to this node's parent
            if (itr.curr->parent == nullptr) { //if the current node is the root
                root = itr.curr->left; //the child is now the root
            }
            else { //if the current node is not the root
                if (*itr < itr.curr->parent->val) { //if the node to be deleted is a left child
                    itr.curr->parent->left = itr.curr->left; //set the node to the parent's left child
                }
                else { //if the node to be deleted is a right child
                    itr.curr->parent->right = itr.curr->left; //set the node to the parent's right child
                }
            }
            delete itr.curr; //get rid of the current node
            --sz; //delete successful, decrease size
        }

        else if (itr.curr->right != nullptr && itr.curr->left == nullptr) { //if the current node has only one child on the right
            itr.curr->right->parent = itr.curr->parent; //set the child's parent to this node's parent
            if (itr.curr->parent == nullptr) { //if the current node is the root
                root = itr.curr->right; //the child is now the root
            }
            else { //if the current node is not the root
                if (*itr < itr.curr->parent->val) { //if the node to be deleted is a left child
                    itr.curr->parent->left = itr.curr->right; //set the node to the parent's left child
                }
                else { //if the node to be deleted is a right child
                    itr.curr->parent->right = itr.curr->right; //set the node to the parent's right child
                }
            }
            delete itr.curr; //get rid of the current node
            --sz; //delete successful, decrease size
        }

        else { //if the current node has two children
            iterator temp = itr; //keep track of the current location

            //go to the next node
            temp.curr = temp.curr->right; //move right...
            while (temp.curr->left != nullptr) //and as far left as possible
                temp.curr = temp.curr->left;

            *itr = *temp; //overwrite the given node’s value with the right-far-left value

            erase(temp); //recursively erase the temp node (which has 0 or 1 children)
        }
    }

    Tree::iterator Tree::begin() const { // return type requires scope
        if (!root) { // if root is null then tree empty
            return iterator(nullptr, this); // return iterator that is null
        }
        node* n = root; // start at the root
        while (n->left != nullptr) { // while we can still go left (to lower value)
            n = n->left; // go left
        }
        return iterator(n, this); // return iterator for node of smallest value
    }

    Tree::iterator Tree::end() const {
        return iterator(nullptr, this); //nullptr represents past the end
    }

    std::size_t Tree::size() const {
        return sz; //return the member variable
    }
    // Find function
    Tree::iterator Tree::find(double val) {
        auto itr = begin(); //start at the beginning of the tree
        while (itr != end()) { //go through each node of the tree
            if (*itr == val) //if the value isfound in the tree
                return itr; //return that location
            ++itr; //if not found at this node, go to the next
        }
        return itr;
    }

    void Tree::deleteTree(node* n) {
        if (n != nullptr) {
            deleteTree(n->left); //go far left as possible on every branch
            deleteTree(n->right); //and as far right as possible
            delete n;
        }
        sz = 0; //tree now has 0 nodes
    }

    void Tree::traverseInsert(Tree::node* n) {
        if (n->left != nullptr) //if there is a left branch
            traverseInsert(n->left); //recurse as far left on the branch as possible
        insert(n->val); //insert all values from the branch
        if (n->right != nullptr) //if there are right branches
            traverseInsert(n->right); //recurse as far right as possible
    }

    Tree::node::node(double _val) : left(nullptr), right(nullptr), parent(nullptr), val(_val) {} //starts as unconnected with a given value

    bool Tree::node::insertNode(node* n) {
        if (n->val < val) {
            if (left != nullptr) //if this node has a left child
                left->insertNode(n); //pass n to the left
            else { //if left child is null
                n->parent = this;
                left = n; //make n the left child
            }
            return true; //node inserted
        }
        else if (n->val > val) { //if n's val is greater than this node's val, n should go to the right
            if (right != nullptr) //if this node has a right child
                right->insertNode(n); //pass n to the right
            else { //if right child is null
                n->parent = this;
                right = n; //make n the right child
            }
            return true; //node inserted
        }

        return false; //no node inserted if no values
    }

    Tree::iterator::iterator(node* n, const Tree* t) : curr(n), container(t) {} //constructed with a given node and tree

    Tree::iterator& Tree::iterator::operator++() {
        if (this->curr == nullptr) //rem nothing comes after nullptr
            throw std::logic_error("Invalid address,points to null");
        else {
            if (curr->right != nullptr) { //if the current node has a right child
                curr = curr->right; //move right
                while (curr->left != nullptr) { //then as far left as possible
                    curr = curr->left;
                }
            }
            else {
                double val = *(*this);
                while (true) { //go up onto parents
                    curr = curr->parent;
                    if (curr == nullptr || *(*this) > val) //if we're at the root's parent (nullptr) or at the node with the next highest val
                        break;
                }
            }
        }
        return *this;
    }

    Tree::iterator Tree::iterator::operator++(int) {
        Tree::iterator itr(this->curr, this->container); //make a copy of this iterator
        ++* this; //increment this iterator
        return itr; //return the copy
    }

    // -- prefix
    Tree::iterator& Tree::iterator::operator--() 
    {
        if (curr == nullptr) // if curr is empty then proceed to inside and run the code
        {
            curr = this->container->root;

            while (curr->right != nullptr) { // then as far right as possible move it to right
                curr = curr->right; 
            }
        }
        else if (curr == container->begin().curr)  
        {
            curr = nullptr;
        }
        else if (curr->left != nullptr) // if the current node has a left child then move it to right
        {
            curr = curr->left;
            while (curr->right != nullptr) // then as far right as possible, move the it to right.
            {
                curr = curr->right;
            }
        }
        else if (curr->left == nullptr) // if the left child is empty then proceed inside and run the code.
        {
            if (curr->parent != nullptr) // if the parent is not empty then proceed inside and run the code.
            {
                if (curr == curr->parent->right) // if the curr point to the same position as the parents on the right
                {
                    curr = curr->parent; // go up onto the parent
                }
                else if (curr == curr->parent->left) // else if the current
                {
                    while (curr->parent != nullptr) // until the parent is empty, move it 
                    {
                        curr = curr->parent; // go up onto the parent
                    }
                    if (curr->parent != nullptr) // if the parent is not empty
                    {
                        curr = curr->parent; // go up onto the parent
                    }
                    else // otherwise, set the curr to empty
                    {
                        curr = nullptr;
                    }
                }
            } // otherwise if the parent is empty then set the curr to empty
            else 
            {
                curr = nullptr;
            }
        }
        return *this;
    }

    // -- postfix
    Tree::iterator Tree::iterator::operator--(int unused) {
        iterator copy(*this);
        --(*this);
        return copy;
    }

    double& Tree::iterator::operator*() const {
        return curr->val; //give the current node's value
    }

    double* Tree::iterator::operator->() const {
        return &(curr->val); //give the location in memory of the current node's value
    }

    bool Tree::iterator::operator==(const Tree::iterator& rhs) const {
        if (curr == rhs.curr && container == rhs.container) //if the nodes and Trees are the same
            return true; //they are equal
        return false; //otherwise not equal
    }

    bool operator!=(const Tree::iterator& lhs, const Tree::iterator& rhs) {
        return !(lhs == rhs); //negate the == operator
    }

    // swap function
    void pic10b::swap(Tree& left, Tree& right) {
        left.swap(right);
    }
}

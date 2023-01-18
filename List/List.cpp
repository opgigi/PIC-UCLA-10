#include "List.h"

namespace pic10b {

    
    //empty list with null first and last
    LinkedList::LinkedList() noexcept : first(nullptr), last(nullptr) {}


    
    //range based for loop to push the data(value) into empty LinkedList
    LinkedList::LinkedList(const std::initializer_list<int>& list) : first(nullptr), last(nullptr) {
        for (auto i : list) {
            push_back(i);
        }
    }
    

    LinkedList::~LinkedList() {
        node* n = first;  
        while (n != nullptr) { // while not past-the-end, then temp node will store the next positions and delete the node on the heap.
            node* temp = n->next;
            delete n;
            n = temp; // then move the node n to the right.
        }
    }


    
    //directly swaps the pointers (first and last) and the sizes
    void swap(LinkedList& one, LinkedList& another) {
        std::swap(one.first, another.first);
        std::swap(one.last, another.last);
        std::swap(one.size_, another.size_);
    }



    LinkedList::LinkedList(const LinkedList& other) : first(nullptr), last(nullptr) 
    {
        for (int i : other) {// the variable 'i' will be incremented until it takes each every value from other and push into LinkedList
            push_back(i);
        }
    }
    
   //take pointers to first/last and then set other's pointers to null - so its in a valid destructible statet
    LinkedList::LinkedList(LinkedList&& other) noexcept : LinkedList() {
        swap(*this, other);
    }

    /*
    copy construct temp with other
     swap this with temp
    */
    LinkedList& LinkedList::operator=(const LinkedList& other)& {
        if (this != &other) {
            LinkedList temp(other);
            swap(*this, temp);
        }
        return *this;
    }


    //this is move operator= and it's gonna swap two LinkedList object without constructing a new copy 
    LinkedList& LinkedList::operator=(LinkedList&& other) & noexcept {
        swap(*this, other);
        return *this;
    }

    
    void LinkedList::push_back(int value) {
        node* n = new node(value); // create a new node
        if (!last) { // if last node is null - LinkedList is empty,both first and last point to newly added node n
            first = last = n;
        }
        else {// otherwise, make last point to n and make n have last as previous
            last->next = n;
            n->prev = last;
            last = n;
        }
        ++size_; // update last and increment size
    }

    
    void LinkedList::push_front(int value) {
        node* n = new node(value); // create a new node
        if (!first) { // if first node is null then LinkedList is empty both first and last point to newly added node n
            first = last = n;
        }
        else { // otherwise first node is not null that means LinkedList is not empty, then make first have n as previous make n point to first
            first->prev = n;
            n->next = first;
            first = n;
        }
        ++size_;
    }

   
    void LinkedList::pop_back() {
        if (!last) { // if last is null, that means LinkedList is empty/ then it will throw the error message.
            throw std::logic_error("error empty list");
        }
        else if (first == last) { // if there is just one element in the list then free the heap memory
            delete first; // free heap memory
            first = last = nullptr; //and make first and last to be null because they are empty again
            --size_;                       //decrements size
        }
        else { // if there are several element exist in the list then run these process
            node* newlast = last->prev; 
            newlast->next = nullptr;
            delete last;
            last = newlast;
            --size_;
        }
    }


    void LinkedList::pop_front() {
        if (!first) { // if last is null that means LinkedList is empty then throw the error message.
            throw std::logic_error("error empty list");
        }
        else if (first == last) { // if there is only one element in the LinkedList

            delete first; //free heap memory
            first = last = nullptr; //and make first and last to be null because it will delete the only one element in the list and be empty again
            --size_;                       //decrement size
        }
        else { // else set new first node prev pointer to null then free memory and point to prev and decrement size,
            node* newfirst = first->next;
            newfirst->prev = nullptr;
            delete first;
            first = newfirst;
            --size_;
        }
    }

    // this iterator points the pas end
    iterator LinkedList::begin() {
        return iterator(first, this);
    }
    // this is for obtaining begin iterator 
    iterator LinkedList::end() {
        return iterator(nullptr, this);
    }
    // this is for obtaining the const begin iterator
    const_iterator LinkedList::begin() const {
        return const_iterator(first, this);
    }
    // this is for obtaining the const iterator pointing past end
    const_iterator LinkedList::end() const {
        return const_iterator(nullptr, this);
    }

    //this the function for inserting value before the current position
    void LinkedList::insert(iterator it, int value) {
        if (it.curr == nullptr) {// if the current position points to null then insert the int value before the past-the-end
            push_back(value);
        }
        else if (it.curr == first) { //if the current position is same as the first then add the value at the beginning
            push_front(value);
        }
        else {// if the current position is located somewhere in the middle then proceed to these steps
            node* n = new node(value); // set the new node
            n->next = it.curr; 
            n->prev = it.curr->prev;
            it.curr->prev->next = n; // make current previous next node into n
            it.curr->prev = n;// make current position previous node in to n;
            ++size_; //and add up the size at the end.
        }
    }

    //removing first or removing last from the list or middle function
    void LinkedList::erase(iterator it) {
        if (it.curr == first) { //if the current position is same as the first, then remove the first element using pop_front()
            pop_front();
        }
        else if (it.curr == last) {
            pop_back(); //if the current position is same as the last, then remove the last element using pop_back()
        }
        else { // if the postion is somewhere in the middle then, reroute it and remove it
            //reroute next of previous                         
            it.curr->prev->next = it.curr->next;
            it.curr->next->prev = it.curr->prev;
            //free heap memory of items being removed  
            delete it.curr;
            --size_;                                  //decrement size
        }
    }

    std::size_t LinkedList::size() const {
        return size_;
    }

    void LinkedList::sort() {
        //iterate from past-the-end to the second element
        for (iterator it = end(); it != begin(); --it) {
            //left iterator at first element
            iterator left = begin();
            iterator right = begin();
            //right iterator at second element
            ++right;
            //as long as right iterator is not same as it      
            while (right != it) {
                //compare values of adjacent iterators                   
                if (*left > *right) {
                    //swap the values of nodes if unsorted             
                    std::swap(*left, *right);
                }
                //move left iterator forward
                ++left;
                ++right;
            }
        }
    }

    std::ostream& operator<<(std::ostream& out, const LinkedList& list) {
        //for data in list
        for (int i : list) {
            //print out data     
            out << i << ' ';
        }
        out << '\n';
        return out;
    }

    //node stores value but points to null on either side
    node::node(int i) :val(i), prev(nullptr), next(nullptr) {}
    iterator::iterator(node* n, const LinkedList* ll) : curr(n), container(ll) {} //
      //prefix ++ unary operator
    iterator& iterator::operator++() {
        //cannot go past-the-end                
        if (curr == nullptr) {
            throw std::logic_error("Invalid address");
        }
        //anywhere else, reference next node
        else {
            curr = curr->next;
        }
        return *this;
    }

    //postfix ++ binary operator
    iterator iterator::operator++(int unused) {
        iterator temp(*this);
        ++(*this);
        return temp;
    }

    //prefix -- unary operator
    iterator& iterator::operator--() {
        //cannot go before first            
        if (curr == container->first) {
            throw std::logic_error("Err Invalid address");
        }
        //if past-the-end, go to last
        else if (curr == nullptr) {
            curr = container->last;
        }
        else {
            //if somewhere in the middle, reference the previous node                                       
            curr = curr->prev;
        }
        return *this;
    }

    //postfix -- binary operator
    iterator iterator::operator--(int unused) {
        iterator temp(*this);
        --(*this);
        return temp;
    }

    //dereference operator: return reference to the int stored
    int& iterator::operator*() const {
        return curr->val;
    }

    bool operator==(const iterator& lhs, const iterator& rhs) {
        return ((lhs.curr == rhs.curr) && (lhs.container == rhs.container));
    }

    bool operator!=(const iterator& lhs, const iterator& rhs) {
        return !(lhs == rhs);
    }

    //iterator to const_iterator
    iterator::operator const_iterator() const {
        return const_iterator(curr, container);
    }

    const_iterator::const_iterator(node* n, const LinkedList* ll) : curr(n), container(ll) {}

    //prefix ++ unary operator
    const_iterator& const_iterator::operator++() {
        //cannot go past the end    
        if (curr == nullptr) {
            throw std::logic_error("Invalid address");
        }
        //anywhere else, reference next node
        else {
            curr = curr->next;
        }
        return *this;
    }

    //postfix ++ binary operator
    const_iterator const_iterator::operator++(int unused) {
        //copy cuurent const_iterator
        const_iterator temp(*this);
        //call the other ++                        
        ++(*this);
        //return this copy                                 
        return temp;
    }

    //prefix -- unary operator
    const_iterator& const_iterator::operator--() {
        //cannot go before first  
        if (curr == container->first) {
            throw std::logic_error("Invalid address");
        }
        //if past-the-end, go to last
        else if (curr == nullptr) {
            curr = container->last;
        }
        //if somewhere in the middle,then reference previous node
        else {
            curr = curr->prev;
        }
        return *this;
    }

    //postfix  binary operator
    const_iterator const_iterator::operator--(int unused) {
        const_iterator temp(*this);
        --(*this);
        return temp;
    }

    //dereference the operator: returns a copy of the int kept
    int const_iterator::operator*() const {
        return curr->val;
    }

    bool operator==(const const_iterator& lhs, const const_iterator& rhs) {
        return((lhs.curr == rhs.curr) && (lhs.container == rhs.container));
    }

    bool operator!=(const const_iterator& lhs, const const_iterator& rhs) {
        return !(lhs == rhs);
    }

    //ranges from first iterator upto las but not including the second iterator
    bool seqSearch(const const_iterator& it1, const const_iterator& it2, int value) {
        for (const_iterator i = it1; i != it2; ++i) {
            //check to see f value Exists in the LinkdList       
            if (*i == value) {
                return true;
            }
        }
        return false;
    }
}

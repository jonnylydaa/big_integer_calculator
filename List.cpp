/********************************************************************************* 
* Jonathan Lyda, jlyda@ucsc.edu 
* 2022 Spring CSE101 PA#6
* List.cpp
* List ADT program
*********************************************************************************/
#include "List.h"
#include<iostream>

List::Node::Node(ListElement x) {
    data = x;
    next = nullptr;
    prev = nullptr;
}

List::List() {
    frontDummy = new Node(0);
    backDummy = new Node(-1);
    frontDummy->next = backDummy;
    frontDummy->prev = nullptr;
    backDummy->prev = frontDummy;
    backDummy->next = nullptr;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

List::List(const List& L) {
    //copy constructor
    frontDummy = new Node(0);
    backDummy = new Node(-1);
    frontDummy->next = backDummy;
    frontDummy->prev = nullptr;
    backDummy->next = nullptr;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
    Node* N = L.frontDummy->next;
    while (N!=L.backDummy) {
        this->insertAfter(N->data);
        this->moveNext();
        N = N->next;
    }
    pos_cursor = L.pos_cursor;
    N = this->frontDummy;
    for (int i = 0; i < pos_cursor; i++) {
        N = N->next;
    }
    beforeCursor = N;
    afterCursor = N->next;
}

List::~List() {
    // destructor
    clear();
    delete frontDummy;
    delete backDummy;
    // Node *tmp = this->frontDummy;
    // while (tmp != backDummy) {
    //     Node *tmp2 = tmp;
    //     tmp = tmp->next;
    //     delete tmp2;
    // }
    // delete tmp;
}

// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const {
    return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const {
    if (length() > 0) {
        return frontDummy->next->data;
    }
    throw std::length_error("List::front(): empty list");
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const {
    if (length() > 0) {
        return backDummy->prev->data;
    }
    throw std::length_error("List::back(): empty list");
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const {
    return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const {
    if (position() < length()) {
        return afterCursor->data;
    }
    throw std::range_error("List::peekNext(): cursor at back");
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const {
    if (position() > 0) {
        return beforeCursor->data;
    }
    throw std::range_error("List::peekPrev(): cursor at front");
}


// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear() {
    if (frontDummy->next != backDummy) {
        Node *tmp = frontDummy->next;
        Node *tmp2 = nullptr;
        while (tmp != backDummy) {
            tmp2 = tmp;
            tmp = tmp->next;
            delete tmp2;
        }
        frontDummy->next = backDummy;
        backDummy->prev = frontDummy;
        pos_cursor = 0;
        num_elements = 0;
    }
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront() {
    pos_cursor = 0;
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack() {
    pos_cursor = length();
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext() {
    // ListElement value;

    if (position() < length()) {
        pos_cursor += 1;
        beforeCursor = beforeCursor->next;
        afterCursor = afterCursor->next;
        return beforeCursor->data;
    }
    throw std::range_error("List::moveNext(): cursor at back");
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev() {
    
    if (position() > 0) {
        pos_cursor -= 1;
        beforeCursor = beforeCursor->prev;
        afterCursor = afterCursor->prev;
        return afterCursor->data;
    }
    throw std::range_error("List::movePrev(): cursor at front");
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x) {
    Node *N = new Node(x);
    N->next = afterCursor;
    N->prev = beforeCursor;
    beforeCursor->next = N;
    afterCursor->prev = N;
    afterCursor = N;
    num_elements += 1;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x) {
    Node *N = new Node(x);
    N->next = afterCursor;
    N->prev = beforeCursor;

    beforeCursor->next = N;
    afterCursor->prev = N;

    beforeCursor = N;
    num_elements += 1;
    pos_cursor += 1;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x) {
    if (position() < length()) {
        afterCursor->data = x;
    }
    else {
        throw std::range_error("List::setAfter(): cursor at back");
    }
    
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x) {
    if (position() > 0) {
        beforeCursor->data = x;
    }
    else {
        throw std::range_error("List::setBefore(): cursor at front");
    }
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter() {
    
    if (position() < length()) {
        Node *tmp = afterCursor;

        afterCursor = afterCursor->next;
        afterCursor->prev = beforeCursor;
        beforeCursor->next = afterCursor;
        
        delete tmp;
        num_elements -= 1;
    }
    else {
        throw std::range_error("List::eraseAfter(): cursor at back");
    }
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore() {
    if (position() > 0) {
        Node *tmp = beforeCursor;

        beforeCursor = beforeCursor->prev;
        beforeCursor->next = afterCursor;
        afterCursor->prev = beforeCursor;
        
        delete tmp;
        num_elements -= 1;
        pos_cursor -= 1;
    }
    else {
        throw std::range_error("List::eraseBefore(): cursor at front");
    }
}


// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x) {

    Node *tmp = afterCursor;
    while (tmp != backDummy) {
        if (tmp->data == x) {
            beforeCursor = tmp;
            afterCursor = tmp->next;
            pos_cursor++;
            return pos_cursor;
        }
        else {
            tmp = tmp->next;
            pos_cursor++;
        }
    }
    // if (tmp == nullptr) {
    pos_cursor = length();
    afterCursor = backDummy;
    beforeCursor = backDummy->prev;
    // }
    return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x) {

    Node *tmp = beforeCursor;
    while (tmp != frontDummy) {
        if (tmp->data == x) {
            beforeCursor = tmp->prev;
            afterCursor = tmp;
            pos_cursor--;
            return pos_cursor;
        }
        else {
            tmp = tmp->prev;
            pos_cursor--;
        }
    }
    // if (tmp == nullptr) {
    pos_cursor = 0;
    afterCursor = frontDummy->next;
    beforeCursor = frontDummy;
    return -1;
    // }
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup() {
    Node *tmp = frontDummy->next;
    while (tmp != backDummy) {
        Node *tmp2 = tmp->next;
        bool passedCursor = false;
        if (tmp == afterCursor) {
            passedCursor = true;
        }
        while (tmp2 != backDummy) {
            if (tmp2 == afterCursor) {
                passedCursor = true;
            }
            if (tmp->data == tmp2->data) {
                tmp2->prev->next = tmp2->next;
                tmp2->next->prev = tmp2->prev;
                if (beforeCursor == tmp2) {
                    beforeCursor = tmp2->prev;
                }
                if (afterCursor == tmp2) {
                    afterCursor = tmp2->next;
                }
                Node *tmp3 = tmp2;
                tmp2 = tmp2->next;
                delete tmp3;
                if (!passedCursor) {
                    if (pos_cursor != 0) {
                        pos_cursor--;
                    }
                }
                num_elements--;
            }
            else {
                tmp2 = tmp2->next;
            }
        }
        tmp = tmp->next;
    }

}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const {
    List nL;
    Node *N = this->frontDummy->next;
    Node *M = L.frontDummy->next;
    while (N != backDummy) {
        nL.insertAfter(N->data);
        nL.moveNext();
        N = N->next;
    }
    while (M != L.backDummy) {
        nL.insertAfter(M->data);
        nL.moveNext();
        M = M->next;
    }
    nL.moveFront();
    return nL;
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const {
    Node *N = nullptr;
    std::string s = "(";
    N = this->frontDummy->next;
    if (N == this->backDummy) {
        s += ")";
    }
    while (N != this->backDummy) {
        if (N->next == this->backDummy) {
            s += std::to_string(N->data) + ")";
        }
        else {
            s += std::to_string(N->data) + ", ";
        }
        N = N->next;
    }
    return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const {
    bool eq = false;
    Node* N = nullptr;
    Node* M = nullptr;
    eq = (this->num_elements == R.num_elements);
    N = this->frontDummy->next;
    M = R.frontDummy->next;
    while((eq) && (N!=backDummy)) {
        eq = (N->data==M->data);
        N = N->next;
        M = M->next;
    }

    return eq;
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ) {
    return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ) {
    return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=(const List& L) {
    if(this != &L){ // not self assignment
        // make a copy of L
        List temp = L;
        // then swap the copy's fields with fields of this
        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(afterCursor, temp.afterCursor);
        std::swap(pos_cursor, temp.pos_cursor);
        std::swap(num_elements, temp.num_elements);
    }
    // return this with the new data installed
    return *this;
    // the copy, if there is one, is deleted upon return
}

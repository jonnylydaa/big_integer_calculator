/********************************************************************************* 
* Jonathan Lyda, jlyda@ucsc.edu 
* 2022 Spring CSE101 PA#6
* BigInteger.cpp
* BigInteger ADT program
*********************************************************************************/

#include "BigInteger.h"
#include<iostream>
#include <string.h>
#include <cmath>

using namespace std;

const int power = 9;
const ListElement base = pow(10, power);

BigInteger::BigInteger() {
    signum = 0;
    List digits;

}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s) {
    //go to back of string, read until number of digits match power, place those (as a long) into the List
    // 264,009  -(009, 264)-for everything else    (264, 0, 90) Xfor printing    ACTUAL: (264, 009)
    if (!s.empty()) {
        bool isZero = true;
        bool leadingZero = true;
        bool signednum = false;
        // List bI;
        signum = 1;
        ListElement entry;
        int spill;
        spill = s.length() % power;
        // cout << "length: " << s.length() << endl;
        
        if(!isdigit(s[0])) {
            if (s.length() > 1) {
                for (unsigned long i = 1; i < s.length(); i++) {
                    if (!isdigit(s[i])) {
                        throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
                    }
                }
            }
            else {
                throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
            }


            signednum = true;
            spill = (s.length() - 1) % power;
            if (s[0] == '-') {
                signum = -1;
            }

            for (unsigned long i = 1; i < s.length(); i++) {
                int cur = s[i] - '0'; //changes ascii to number ('0' is 48)
                // cout << "current1: " << cur << endl;
                 if (cur != 0) {
                    // cout << "not zero1: " << cur << endl;
                
                    isZero = false;
                    break;
                }
            }
            if (isZero) {

                signum = 0;
                
            }
        }
        else {
            for (unsigned long i = 0; i < s.length(); i++) {
                if (!isdigit(s[i])) {
                    throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
                }
            }
            for (unsigned long i = 0; i < s.length(); i++) {
                int cur = s[i] - '0'; //changes ascii to number ('0' is 48)
                // cout << "current2: " << cur << endl;
                if (cur != 0) {
                    // cout << "not zero2: " << cur << endl;
                
                    isZero = false;
                    break;
                }
            }
            if (isZero) {

                signum = 0;
            }

        }
        if (signum != 0) {
            //fill in the spill entry
            if (signednum) {
                
                if (spill != 0) {
                    string sub = s.substr(1, spill);
                    // cout << "Sub1: " << sub << endl;
                    entry = (ListElement) stoll(sub, nullptr, 10);
                    if (entry != 0) {
                        leadingZero = false;
                    }
                    // cout << "entry1: " << entry << endl;
                    if (!leadingZero) {
                        digits.insertBefore(entry);
                    }
                
                }

                for (unsigned long i = spill + 1; i < s.length(); i += power) {
                    string sub = s.substr(i, power);
                    // cout << "Sub2: " << sub << endl;
                    entry = (ListElement) stoll(sub, nullptr, 10);
                    if (entry != 0) {
                        leadingZero = false;
                    }
                    // cout << "entry2: " << entry << endl;
                    // if ((entry)%base != 0)
                    // digits->insertBefore(entry);
                    if (!leadingZero) {
                        digits.insertBefore(entry);
                    }
                }
            }
            else {
                if (spill != 0) {
                    string sub = s.substr(0, spill);
                    // cout << "Sub3: " << sub << endl;
                    entry = (ListElement) stoll(sub, nullptr, 10);
                    if (entry != 0) {
                        leadingZero = false;
                    }
                    // cout << "entry3: " << entry << endl;
                    if (!leadingZero) {
                        digits.insertBefore(entry);
                    }
                
                }

                for (unsigned long i = spill; i < s.length(); i += power) {
                    string sub = s.substr(i, power);
                    // cout << "Sub4: " << sub << endl;
                    entry = (ListElement) stoll(sub, nullptr, 10);
                    if (entry != 0) {
                        leadingZero = false;
                    }
                    // cout << "entry4: " << entry << endl;
                    // if ((entry)%base != 0)
                    // digits->insertBefore(entry);
                    if (!leadingZero) {
                        digits.insertBefore(entry);
                    }
                }
            }
        }
        
    }
    else {
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N) {
    signum = N.signum;
    digits = N.digits;
}

// Optional Destuctor
// ~BigInteger()
// ~BigInteger();


// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const {
    return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const {
    BigInteger num1 = *this;
    BigInteger num2 = N;
    num1 = num1.sub(num2);
    return num1.signum;
}


// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero() {
    digits.clear();
    signum = 0;
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate() {
    signum  = (signum * -1);
}


//HELPER FUNCTIONS------------------------
// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List& L) {
    L.moveFront();
    while (L.position() < L.length()) {
        L.setBefore(L.moveNext() * -1);
    }
}

// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors). // Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn) {
    // bool negatedList = false;
    if (sgn == -1) {
        negateList(B);
        // negatedList = true;
    }
    A.moveBack();
    B.moveBack();
    S.moveBack();
    while ((A.position() != 0) && (B.position() != 0)) {
        ListElement elementSum;
        // cout << "A num: " << A.peekPrev() << " B num: " << B.peekPrev() << endl;
        elementSum = A.movePrev() + B.movePrev();
        // cout << "ele sum: " << elementSum << endl;
        S.insertAfter(elementSum);
    }
    //Fills in rest of sum with the larger number.
    if (A.position() == 0) {
        while (B.position() != 0) {
            S.insertAfter(B.movePrev());
        }
    }
    else { //num2 is shorter
        while (A.position() != 0) {
            S.insertAfter(A.movePrev());
        }
    }
    // if (negatedList) {
    //     negateList(S);
    // }
}

// normalizeList()
// Performs carries from right to left (least to most significant // digits), then returns the sign of the resulting integer. Used // by add(), sub() and mult().
int normalizeList(List& L) {
    L.moveBack();
    int carry = 0;
    while (L.position() != 0) {
        ListElement ele = L.peekPrev();
        // cout << "element: " << ele << endl;
        ele += carry;
        carry = ele/base;
        ele = ele % base;
        
        if (L.position() == 1) { // last element
            // cout << "last element L: " << L << endl;
            L.setBefore(ele);
            // cout << "last element L2: " << L << endl;
            break;
        }
        // cout << "element1: " << ele << " Base: " << base << endl;
        // if (ele >= base) {
        //     carry = ele/base;

        //     ele = ele % base;
        // }
        if (ele < 0) {
            carry -= 1;
            ele += base;
        }
        // else {
        //     carry = 0;
        // }
        // cout << "element after carry: " << ele << endl;
        // cout << "carry: " << carry << endl;
        L.setBefore(ele);
        L.movePrev();
    }
    if (carry != 0) {
        L.movePrev();
        L.insertBefore(carry);
    }
    L.moveFront();
    while (L.peekNext() == 0) {
        // cout << "iterating for zeros" << endl;
        L.moveNext();
        L.eraseBefore();
        // cout << "L after erase after: " << L << endl;
    }
    // cout << "L after normalize: " << L << endl;
    return carry;
}

// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p) {
    L.moveBack();
    for (int i = 0; i < p; i++) {
        L.insertAfter(0);
    }
}

// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult(). 
void scalarMultList(List& L, ListElement m) {
    //may have to copy L when this is called so that i dont mess up L
    // bool isZero = true;
    L.moveBack();
    while (L.position() != 0) {
        ListElement ele = L.peekPrev();
        L.setBefore(m * ele);
        L.movePrev();
    }
    // L.moveBack();
    // while (L.position() != 0) {
    //     if (L.peekPrev() != 0) {
    //         isZero = false;
    //         break;
    //     }
    //     L.movePrev();
    // }
    // if (isZero) {
    //     L.
    // }
}


// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const {
    BigInteger num1 = *this;
    BigInteger num2 = N;
    BigInteger sum;
    bool num1bigger = false;
    // bool iszero = false;
    // sum.signum = 1;

    //FIND THE SUM's SIGN
    if (num1.signum == num2.signum){
        // cout << "same sign in add" << endl;
        sum.signum = num1.signum;
    }
    else if ((num1.signum == 0) || (num2.signum == 0)) {
        if (num1.signum == 0) {
            sum.signum = num2.signum;
            if (num2.signum == -1) {
                num1bigger = true;
            }
            
        }
        else {
            sum.signum = num1.signum;
            if (num1.signum == 1) {
                num1bigger = true;
            }
        }
    }
    else {
        if (((num1.signum == 1) && (num2.signum == -1)) || ((num2.signum == 1) && (num1.signum == -1))) {
            if (num1.digits.length() > num2.digits.length()) { //num1 is bigger
                sum.signum = num1.signum;
                num1bigger = true;
            }
            else if (num1.digits.length() < num2.digits.length()) {  //num2 is bigger
                sum.signum = num2.signum;
            }
            else { //if the number of entries is equal
                if (num1.digits.front() > num2.digits.front()) { //num1 is bigger
                    sum.signum = num1.signum;
                    num1bigger = true;
                }
                else if (num2.digits.front() > num1.digits.front()) { //num2 is bigger
                    sum.signum = num2.signum;
                }
                else { // num2 and num1 are the same number but different signs
                    // cout << "front is the same" << endl;
                    bool same = true;
                    num1.digits.moveFront();
                    num2.digits.moveFront();
                    while ((num1.digits.position() < num1.digits.length()) && (num2.digits.position() < num2.digits.length())) {
                        ListElement num1ele = num1.digits.peekNext();
                        ListElement num2ele = num2.digits.peekNext();
                        if (num1ele > num2ele) {
                            sum.signum = num1.signum;
                            same = false;
                            num1bigger = true;
                            break;
                        }
                        else if (num2ele > num1ele) {
                            sum.signum = num2.signum;
                            same = false;
                            break;
                        }
                        else {
                            num1.digits.moveNext();
                            num2.digits.moveNext();
                        }

                    }
                    if (same) {
                        // cout << "same number?" << endl;
                        sum.signum = 0;
                        // iszero = true;
                    }
                    
                }
            }
        }

    }

    // //greater than equal to base = carry
    // num1.digits.moveBack();
    // num2.digits.moveBack();
    // sum.digits.moveBack();
    // while ((num1.digits.position() != 0) && (num2.digits.position() != 0)) {
    //     ListElement elementSum;
    //     elementSum = num1.digits.movePrev() + num2.digits.movePrev();
    //     // cout << "ele sum: " << elementSum << endl;
    //     sum.digits.insertAfter(elementSum);
    // }
    // //Fills in rest of sum with the larger number.
    // if (num1.digits.position() == 0) {
    //     while (num2.digits.position() != 0) {
            
    //         sum.digits.insertAfter(num2.digits.movePrev());
    //     }
    // }
    // else { //num2 is shorter
    //     while (num1.digits.position() != 0) {
    //         sum.digits.insertAfter(num1.digits.movePrev());
    //     }
    // }
    BigInteger new1 = num1;
    BigInteger new2 = num2;
    // if (new1.signum == -1) {
    //     negateList(new1.digits);
    // }
    // if (new2.signum == -1) {
    //     negateList(new2.digits);
    // }
    // cout << "new 2: " << new2 << endl;
    // cout << "num2: " << num2 << "sum sign: " << sum.signum << endl;
    if (sum.signum != 0) {
        if ((new1.signum == -1) && (new2.signum == -1)) {
            negateList(new1.digits);
            sumList(sum.digits, new1.digits, new2.digits, new2.signum);
            negateList(sum.digits);
            // sum.negate();
        }
        else if ((new1.signum == 1) && (new2.signum == -1)) {
            sumList(sum.digits, new1.digits, new2.digits, new2.signum);
            if (!num1bigger) {
                negateList(sum.digits);
            }
        }
        else if ((new1.signum == -1) && (new2.signum == 1)) {
            // cout << "IN HERE" << endl;
            sumList(sum.digits, new2.digits, new1.digits, new1.signum);
            if (num1bigger) {
                negateList(sum.digits);
            }
        }
        else if (new1.signum == 0) {
            sum = new2;
        }
        else if (new2.signum == 0) {
            sum = new1;
        }
        else {
            sumList(sum.digits, new1.digits, new2.digits, new2.signum);
        }
        // cout << "sum before normalize: " << sum.digits << endl;
        //now normalize the sum list
        normalizeList(sum.digits);
        // cout << "sum after normalize: " << sum.digits << endl;
    }
    // cout << "Sum at end of ADD: " << sum << endl;
    return sum;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const {
    BigInteger num1 = *this;
    BigInteger num2 = N;
    num2.negate();
    return num1.add(num2);
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const {
    BigInteger num1 = *this;
    BigInteger num2 = N;
    // cout << "num 1: " << num1 << " num 2: " << num2 << endl;
    BigInteger tmp2 = num2;
    BigInteger prevNum;

    if ((num1.signum == 0) || (num2.signum == 0)) {
        prevNum.signum = 0;
        return prevNum;
    }
    int shift = 0;
    tmp2.digits.moveBack();
    while (tmp2.digits.position() != 0) {
        BigInteger tmp1 = num1;
        // cout << "in while MULT" << endl;
        ListElement ele = tmp2.digits.peekPrev();
        // cout << "list element from num2: " << ele << endl;
        // tmp1.digits.moveBack();
        // while (tmp1.digits.position() != 0) {

        // if (prevNum.signum != 0) {
        //     cout << "first pevnum" << endl;
        //     scalarMultList(prevNum.digits, ele); //tmp1.digits is updated now   //should be prevNum
        // }
        // else {
        if (ele == 0) {
            tmp1.makeZero();
        }
        else {
            scalarMultList(tmp1.digits, ele); //tmp1.digits is updated now   //should be prevNum
        }
        // }

        // scalarMultList(tmp1.digits, ele); //tmp1.digits is updated now   //should be prevNum
        // cout << "after scalar mult: " << tmp1 << endl;
        shiftList(tmp1.digits, shift);
        // cout << "after shift: " << tmp1 << endl;
        // if (prevNum.signum != 0) { //if prevnum is not used yet
        // cout << "prev num before add: " << prevNum << " temp 1 before add: " << tmp1 << endl;
        // BigInteger sum = tmp1.add(prevNum);
        tmp1 = tmp1.add(prevNum);
        // cout << "after add tmp1: " << tmp1 << " after add prev num: " << prevNum << endl;
        // }
        // }
        // normalizeList(tmp1.digits);
        // prevNum = tmp2;
        prevNum = tmp1;
        // cout << "prev num: " << prevNum << endl;
        shift++;
        tmp2.digits.movePrev();
    }
    // cout << "previous num: " << prevNum << endl;
    if (num1.signum == num2.signum) {
        prevNum.signum = 1;
    }
    else {
        prevNum.signum = -1;
    }
    return prevNum;
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string() {
    string s = "";
    // cout << "hello" << endl;
    if (signum == 0) {
        s += "0";
        // cout << "hello" << endl;
        return s;
    }
    // else if (signum == 1) {
    //     s += "+";
    // }
    else if (signum == -1){
        s += "-";
    }
    // s += std::to_string(digits.front());
    bool firstele = true;
    digits.moveFront();
    while (digits.position() < digits.length()) {
        // digits.moveNext();
        if (firstele) {
            s += std::to_string(digits.moveNext());
            firstele = false;
        }
        else {
            ListElement nextele;
            nextele = digits.peekNext();
            if (nextele == 0) {
                for (int j = 0; j < power - 1; j++) {
                    s += "0";
                }
            }
            else {
                int count = 0;
                while(nextele != 0) {
                    nextele = nextele / 10;
                    count++;
                }
                if (count != power) {
                    int leadzeros = power - count;
                    for (int j = 0; j < leadzeros; j++) {
                        s += "0";
                    }
                }
            }
            s += std::to_string(digits.moveNext());
        }
    }
    return s;
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
    return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) == 0) {
        return true;
    }
    return false;
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) == -1) {
        return true;
    }
    return false;
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ) {
    int cmp = A.compare(B);
    if ((cmp == -1) || (cmp == 0)) {
        return true;
    }
    return false;
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) == 1) {
        return true;
    }
    return false;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ) {
    int cmp = A.compare(B);
    if ((cmp == 1) || (cmp == 0)) {
        return true;
    }
    return false;
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
    BigInteger sum;
    sum = A;
    return sum.add(B);
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
    A = A.add(B);
    return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ) {
    BigInteger difference;
    difference = A;
    return difference.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ) {
    A = A.sub(B);
    return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ) {
    BigInteger prod;
    prod = A;
    return prod.mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ) {
    A = A.mult(B);
    return A;
}

/********************************************************************************* 
* * Jonathan Lyda, jlyda@ucsc.edu 
* * 2022 Spring CSE101 PA#6
* * Arithmetic.cpp
* * Takes in file, parses, constructs A and B BigInteger, and runs some operations on those BigIntegers
* *********************************************************************************/

//-----------------------------------------------------------------------------
//  BigIntegerClient.cpp 
//  A test client for the BigInteger ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main(){

    string s1 = "9128734667000004389234563456345619187236478";
    //string s2 = "-330293847502398475";
    string s3 = "9876545439000000000000000200000000000006543654365346534";
    //string s4 = "9876545439000000000000000100000000000006543654365346534";
    //string s5 = "98765454390000000000000000000000000000065436543";
    // string s6 = "9876545439000000000000000000000000000006543";
    // string s7 = "0";
    //BigInteger N;
    // BigInteger(s1).to_string();
    // to_string();

    // string s10 = "1559";
    // string s11 = "-1798";//produces -239 with extra negate (correct)

    // string s10 = "559";
    // string s11 = "-1798";//produces -1239 with extra negate (correct)
    
    // string s10 = "-13559";
    // string s10 = "25";
    string s10 = "-798";
    string s11 = "7893878";
    // string s12 = "";
    // string s13 = "34";
    // string s14 = "-400003";
    //produces +-10239 with extra negate (wrong), should be 9761, produces +9761 without negate (correct)

    // cout << "s6 = " << BigInteger(s6) << endl;
    // exit(1);

    BigInteger Q = BigInteger(s10);
    BigInteger W = BigInteger(s11);

    // BigInteger C = BigInteger(s13);
    // BigInteger D = BigInteger(s14);
    BigInteger A = BigInteger(s1);
    BigInteger B = BigInteger(s3);
    
    cout << endl;
    // cout << "A scalarmult 2: " << C.mult(D) << endl;
    cout << "A = " << A << endl;
    cout << "B = " << B << endl;
    cout << "Q = " << Q << endl;
    cout << "W = " << W << endl;
    cout << "Q + W = " << Q.add(W) << endl;
    cout << "Q - W = " << Q.sub(W) << endl;
    cout << "Q + W = " << Q.add(W) << endl;
    cout << "Q * W = " << Q.mult(W) << endl;
    // BigInteger newQ = Q.negate();
    // cout << "Q after negate = " << newQ << endl;
    // cout << "Q after makezero = " << Q.makeZero() << endl;
    
    
    // cout << "overloaded: C - C = " << (C-C) << endl;
    cout << endl;
    // exit(1);

    BigInteger C = A+B;
    BigInteger D = B+A;
    BigInteger E = A-A;
    BigInteger F = B-A;
    BigInteger G = A*B;
    BigInteger H = B*A;
    BigInteger I = C*E;

    cout << "(A==B) = " << ((A==B)?"True":"False") << endl;
    cout << "(A<B)  = " << ((A<B)? "True":"False") << endl;
    cout << "(A<=B) = " << ((A<=B)?"True":"False") << endl;
    cout << "(A>B)  = " << ((A>B)? "True":"False") << endl;
    cout << "(A>=B) = " << ((A>=B)?"True":"False") << endl << endl;

    cout << "C = " << C << endl;
    cout << "D = " << D << endl;
    cout << "(C==D) = " << ((C==D)?"True":"False") << endl;
    cout << "E = " << E << endl;
    cout << "F = " << F << endl;
    cout << "G = " << G << endl;
    cout << "H = " << H << endl;
    cout << "(G==H) = " << ((G==H)?"True":"False") << endl;
    cout << "I = " << I << endl << endl;

    cout << endl;
    // cout << "before overload A = " << A << endl;
    // cout << "before overload B = " << B << endl;
    // cout << "before overload C = " << C << endl;
    A += B;
    B -= C;
    C *= D;
    cout << "after over A = " << A << endl;
    cout << "after over B = " << B << endl;
    cout << "after over C = " << C << endl;
    cout << endl;

    cout << A*B*C*D*F*G*H << endl << endl;

    cout << endl;

    // test exceptions
    try{
        BigInteger J = BigInteger("");
    }catch( std::invalid_argument& e ){
        cout << e.what() << endl;
        cout << " 1  continuing without interruption" << endl;
    }
    try{
        BigInteger J = BigInteger("+");
    }catch( std::invalid_argument& e ){
        cout << e.what() << endl;
        cout << " 2  continuing without interruption" << endl;
    }
    try{
        BigInteger J = BigInteger("12329837492387492837492$4982379487293847");
    }catch( std::invalid_argument& e ){
        cout << e.what() << endl;
        cout << " 3  continuing without interruption" << endl;
    }
    try{
        BigInteger J = BigInteger("5298374902837409+82734098729287349827398");
    }catch( std::invalid_argument& e ){
        cout << e.what() << endl;
        cout << " 4  continuing without interruption" << endl;
    }

    cout << endl;

    return EXIT_SUCCESS;
}

// ///////GRADING SCRIPT///////

// #include <csetjmp>
// #include <csignal>
// #include <cstdbool>
// #include <cstdint>
// #include <cstdlib>
// #include <cstring>
// #include <iostream>
// #include <string>

// #include "BigInteger.h"
// #include "List.h"

// #define FIRST_TEST Sign_test
// #define MAXSCORE 36
// #define CHARITY 10

// #define RED "\033[0;31m"
// #define CYAN "\033[0;36m"
// #define GREEN "\033[0;32m"
// #define NC "\033[0m"

// using namespace std;

// static uint8_t testsPassed;
// static volatile sig_atomic_t testStatus;
// static uint8_t disable_exit_handler;
// jmp_buf test_crash;

// enum Test_e {
//   Sign_test = 0,
//   Negate_test,
//   Makezero_test,
//   Add_test,
//   AddAssign_test,
//   Subtract_test,
//   SubAssign_test,
//   Multiply_test,
//   MultAssign_test,
//   Compare_test,
//   CompareEquals_test,
//   Equals_test,
//   NUM_TESTS,
// };

// string testName(int test) {
//   if (test == Sign_test)
//     return "Sign_test";
//   if (test == Negate_test)
//     return "Negate_test";
//   if (test == Makezero_test)
//     return "Makezero_test";
//   if (test == Add_test)
//     return "Add_test";
//   if (test == AddAssign_test)
//     return "AddAssign_test";
//   if (test == Subtract_test)
//     return "Subtract_test";
//   if (test == SubAssign_test)
//     return "SubAssign_test";
//   if (test == Multiply_test)
//     return "Multiply_test";
//   if (test == MultAssign_test)
//     return "MultAssign_test";
//   if (test == Compare_test)
//     return "Compare_test";
//   if (test == CompareEquals_test)
//     return "CompareEquals_test";
//   if (test == Equals_test)
//     return "Equals_test";
//   if (test == NUM_TESTS)
//     return "NUM_TESTS";

//   return "";
// }

// uint8_t runTest(BigInteger *pA, BigInteger *pB, BigInteger *pC, BigInteger *pD,
//                 int test) {
//   // List A = A;
//   // List B = B;
//   BigInteger A = *pA;
//   BigInteger B = *pB;
//   BigInteger C = *pC;
//   BigInteger D = *pD;

//   switch (test) {
//   case Sign_test: {
//     if (A.sign() != 0)
//       return 1;
//     B = BigInteger("13378008135");
//     C = BigInteger("+13378008135");
//     D = BigInteger("-13378008135");
//     if (B.sign() != 1)
//       return 2;
//     if (C.sign() != 1)
//       return 3;
//     if (D.sign() != -1)
//       return 4;
//     return 0;
//   }
//   case Negate_test: {
//     A = BigInteger("+13378008135");
//     A.negate();
//     if (A.sign() != -1)
//       return 1;

//     A.negate();
//     if (A.sign() != 1)
//       return 2;

//     B = BigInteger();
//     B.negate();
//     if (B.sign() != 0)
//       return 3;

//     return 0;
//   }
//   case Makezero_test: {
//     A = BigInteger("+13378008135");
//     A.makeZero();
//     if (A.sign() != 0)
//       return 1;

//     B = BigInteger();
//     if (!(A == B))
//       return 2;
//     return 0;
//   }
//   case Add_test: {
//     /*
//      * Adding numbers fall into one of 4 cases, denote pos = positive number,
//      * neg = negative number
//      *
//      * pos + pos = pos
//      *
//      * pos + neg = 0
//      *           < 0
//      *           > 0
//      *
//      * neg + pos = 0
//      *           < 0
//      *           > 0
//      *
//      * neg + neg = neg
//      */
//     A = BigInteger("+111122223333");
//     B = BigInteger("+222211110000");

//     // pos + pos = pos
//     D = BigInteger("+333333333333");
//     C = A + B;

//     if (!(C == D))
//       return 1;

//     // add a positive and a negative integer
//     //-> pos + neg = 0
//     B = BigInteger("-111122223333");
//     C = A + B;
//     if (C.sign() != 0)
//       return 2;

//     //-> pos + neg > 0
//     B = BigInteger("-110122223333");
//     D = BigInteger("1000000000");
//     C = A + B;
//     if (C.sign() != 1)
//       return 31;
//     if (!(C == D))
//       return 32;

//     //-> pos + neg < 0
//     B = BigInteger("-112122223333");
//     D = BigInteger("-1000000000");
//     C = A + B;
//     if (C.sign() != -1)
//       return 41;
//     if (!(C == D))
//       return 42;

//     //-> neg + neg = neg
//     A = BigInteger("-221211110000");
//     D = BigInteger("-333333333333");
//     C = A + B;
//     if (!(C == D))
//       return 5;

//     return 0;
//   }
//   case AddAssign_test: {
//     A = BigInteger("+111122223333");
//     B = BigInteger("+222211110000");

//     // pos + pos = pos
//     D = BigInteger("+333333333333");
//     A += B;

//     if (!(A == D))
//       return 1;

//     // add a positive and a negative integer
//     //-> pos + neg = 0

//     A = BigInteger("+111122223333");
//     B = BigInteger("-111122223333");
//     A += B;
//     if (A.sign() != 0)
//       return 2;

//     //-> pos + neg > 0

//     A = BigInteger("+111122223333");
//     B = BigInteger("-110122223333");
//     D = BigInteger("1000000000");
//     A += B;
//     if (A.sign() != 1)
//       return 31;
//     if (!(A == D))
//       return 32;

//     //-> pos + neg < 0
//     A = BigInteger("+111122223333");
//     B = BigInteger("-112122223333");
//     D = BigInteger("-1000000000");
//     A += B;
//     if (A.sign() != -1)
//       return 41;
//     if (!(A == D))
//       return 42;

//     //-> neg + neg = neg
//     A = BigInteger("-221211110000");
//     B = BigInteger("-112122223333");
//     D = BigInteger("-333333333333");
//     A += B;
//     if (!(A == D))
//       return 5;

//     return 0;
//   }
//   case Subtract_test: {
//     /*
//      * subtracting numbers fall into one of 4 cases, denote pos = positive
//      * number, neg = negative number
//      *
//      * pos - pos = 0
//      *           < 0
//      *           > 0
//      *
//      * pos - neg = pos
//      *
//      * neg - pos = neg
//      *
//      * neg - neg = 0
//      *           < 0
//      *           > 0
//      */

//     // pos - pos = 0
//     A = BigInteger("+111122223333");
//     B = BigInteger("+111122223333");

//     C = A - B;
//     if (C.sign() != 0)
//       return 1;

//     // pos - pos < 0
//     B = BigInteger("121122223333");
//     D = BigInteger("-10000000000");
//     C = A - B;
//     if (C.sign() != -1)
//       return 21;
//     if (!(C == D))
//       return 22;

//     // pos - pos > 0
//     B = BigInteger("101122223333");
//     D = BigInteger("10000000000");
//     C = A - B;
//     if (C.sign() != 1)
//       return 31;
//     if (!(C == D))
//       return 32;

//     // pos - neg = pos
//     B.negate();
//     D = BigInteger("212244446666");
//     C = A - B;
//     if (C.sign() != 1)
//       return 41;
//     if (!(C == D))
//       return 42;

//     // neg - pos = neg
//     D.negate();
//     C = B - A;
//     if (C.sign() != -1)
//       return 51;
//     if (!(C == D))
//       return 52;

//     return 0;
//   }
//   case SubAssign_test: {
//     A = BigInteger("-111122223333");
//     B = BigInteger("-111122223333");

//     // neg - neg = 0
//     A -= B;
//     if (A.sign() != 0)
//       return 1;

//     // neg - neg > 0
//     A = BigInteger("-111122223333");
//     B = BigInteger("-112122223333");
//     D = BigInteger("1000000000");
//     A -= B;
//     if (A.sign() != 1)
//       return 21;
//     if (!(A == D))
//       return 22;

//     // neg - neg < 0
//     A = BigInteger("-111122223333");
//     B = BigInteger("-110122223333");
//     D = BigInteger("-1000000000");
//     A -= B;
//     if (A.sign() != -1)
//       return 31;
//     if (!(A == D))
//       return 32;

//     // neg - pos = neg
//     A = BigInteger("-111122223333");
//     B.negate();
//     D = BigInteger("-221244446666");
//     A -= B;
//     if (A.sign() != -1)
//       return 41;
//     if (!(A == D))
//       return 42;

//     return 0;
//   }
//   case Multiply_test: {
//     A = BigInteger("111122223333");
//     B = BigInteger("111122223333");
//     C = BigInteger();
//     D = BigInteger("12348148518469129628889");

//     // pos * pos = pos
//     C = A * B;
//     if (C.sign() != 1)
//       return 1;
//     if (!(C == D))
//       return 2;

//     // pos * neg = neg
//     B.negate();
//     D.negate();
//     C = A * B;
//     if (C.sign() != -1)
//       return 3;
//     if (!(C == D))
//       return 4;

//     B.makeZero();
//     C = A * B;
//     if (C.sign() != 0)
//       return 5;

//     return 0;
//   }
//   case MultAssign_test: {
//     A = BigInteger("-111122223333");
//     B = BigInteger("111122223333");
//     D = BigInteger("-12348148518469129628889");

//     // neg * pos = neg
//     A *= B;
//     if (A.sign() != -1)
//       return 1;
//     if (!(A == D))
//       return 2;

//     // neg * neg = pos
//     A = BigInteger("-111122223333");
//     B.negate();
//     D.negate();
//     A *= B;
//     if (A.sign() != 1)
//       return 3;
//     if (!(A == D))
//       return 4;

//     A = BigInteger("-111122223333");
//     B.makeZero();
//     A *= B;
//     if (A.sign() != 0)
//       return 5;

//     return 0;
//   }
//   case Compare_test: {
//     A = BigInteger("111122223333");
//     B = BigInteger("111122223333");
//     C = BigInteger("112122223333");
//     D = BigInteger("110122223333");

//     // A = B
//     if (!(A == B))
//       return 1;

//     // A < C
//     if (!(A < C))
//       return 2;

//     // A > D
//     if (!(A > D))
//       return 3;

//     return 0;
//   }
//   case CompareEquals_test: {
//     A = BigInteger("111122223333");
//     B = BigInteger("111122223333");
//     C = BigInteger("112122223333");
//     D = BigInteger("110122223333");

//     // A = B
//     if (!(A <= B))
//       return 1;

//     // A < C
//     if (A >= C)
//       return 2;

//     // A > D
//     if (A <= D)
//       return 3;

//     return 0;
//   }
//   case Equals_test: {
//     A = BigInteger("111122223333");
//     B = BigInteger("111122223333");
//     C = BigInteger("-111122223333");
//     D = BigInteger("999111122223333");

//     // A = B
//     if (!(A == B))
//       return 1;

//     // A > C
//     if ((A == C))
//       return 2;

//     // A < D
//     if ((A == D))
//       return 3;

//     return 0;
//   }
//   }
//   return 255;
// }

// void segfault_handler(int signal) { // everyone knows what this is
//   testStatus = 255;
//   longjmp(test_crash, 1);
// }

// void exit_attempt_handler(void) { // only I decide when you are done
//   if (disable_exit_handler)
//     return; // allow this to be disabled
//   testStatus = 255;
//   longjmp(test_crash, 2);
// }

// void abrupt_termination_handler(int signal) { // program killed externally
//   testStatus = 255;
//   longjmp(test_crash, 3);
// }

// int main(int argc, char **argv) {
//   if (argc > 2 || (argc == 2 && strcmp(argv[1], "-v") != 0)) {
//     printf("Usage: %s [-v]", (argc > 0 ? argv[0] : "./ListTest"));
//     exit(1);
//   }

//   printf("\n"); // more spacing
//   if (argc == 2)
//     printf("\n"); // consistency in verbose mode

//   testsPassed = 0;
//   disable_exit_handler = 0;
//   atexit(exit_attempt_handler);
//   signal(SIGSEGV, segfault_handler);
//   // signal(SIGTERM, abrupt_termination_handler); // dangerous
//   // signal(SIGINT, abrupt_termination_handler);
//   // signal(SIGFPE, abrupt_termination_handler);
//   // signal(SIGABRT, abrupt_termination_handler);
//   for (uint8_t i = FIRST_TEST; i < NUM_TESTS; i++) {
//     BigInteger A, B, C, D;
//     uint8_t fail_type;
//     try {

//       testStatus = runTest(&A, &B, &C, &D, i);
//       fail_type = setjmp(test_crash);
//     } catch (...) {
//       testStatus = 255;
//       fail_type = 3;
//     }
//     if (argc == 2) { // it's verbose mode
//       cout << "Test " + testName(i) + ": "
//            << (testStatus == 0 ? GREEN "PASSED" NC : RED "FAILED" NC);
//       if (testStatus == 255) {
//         cout << ": due to a " RED
//              << (fail_type == 1
//                      ? "segfault"
//                      : (fail_type == 2
//                             ? "program exit"
//                             : (fail_type == 3 ? "exception being thrown"
//                                               : "program interruption")))
//              << NC << endl;
//         cout << "\nWARNING: Program will now stop running tests\n" << endl;
//         break;
//       } else if (testStatus != 0) {
//         cout << ": test " CYAN << testStatus << NC << endl;
//       } else {
//         cout << endl;
//       }
//     }
//     if (testStatus == 0) {
//       testsPassed++;
//     }
//   }

//   disable_exit_handler = 1;

//   uint8_t totalScore = (MAXSCORE - NUM_TESTS * 3) + testsPassed * 3;
//   if (testsPassed == 0)
//     totalScore = 0;

//   if (argc == 2 && testStatus != 255)
//     cout << "\nYou passed " << unsigned(testsPassed) << " out of " << NUM_TESTS
//          << " tests" << endl;
//   else if (testStatus == 255) {
//     totalScore = CHARITY; // charity points
//     if (argc == 2)
//       cout << RED "Receiving charity points because your program crashes" NC
//            << endl;
//   }
//   cout << "You will receive " << unsigned(totalScore) << " out of " << MAXSCORE
//        << " possible points on the BigInteger Functionality Test\n"
//        << endl;
//   return 0;
// }
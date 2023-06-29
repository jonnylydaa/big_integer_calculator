/********************************************************************************* 
* * Jonathan Lyda, jlyda@ucsc.edu 
* * 2022 Spring CSE101 PA#6
* * Arithmetic.cpp
* * Takes in file, parses, constructs A and B BigInteger, and runs some operations on those BigIntegers
* *********************************************************************************/

#include<iostream>
#include<fstream>
#include<string>
#include "BigInteger.h"

using namespace std;

#define MAX_LEN 300

int main(int argc, char * argv[]){

    int token_count, line_count;
    size_t begin, end, line_length;
    ifstream in;
    ofstream out;
    string line;
    string tokenBuffer;
    string token;

    // check command line for correct number of arguments
    if( argc != 3 ){
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return(EXIT_FAILURE);
    }

    // open files for reading and writing 
    in.open(argv[1]);
    if( !in.is_open() ){
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }

    out.open(argv[2]);
    if( !out.is_open() ){
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }

    // read each line of input file, then count and print tokens 
    line_count = 0;
    BigInteger A;
    BigInteger B;
    while( getline(in, line) )  {
        line_count++;
        line_length = line.length();
        
        // get tokens in this line
        token_count = 0;
        tokenBuffer = "";

        // get first token
        begin = min(line.find_first_not_of(" ", 0), line_length);
        end = min(line.find_first_of(" ", begin), line_length);
        token = line.substr(begin, end-begin);
        
        while( token!="" ){  // we have a token
            // update token buffer
            tokenBuffer += token;
            token_count++;

            // get next token
            begin = min(line.find_first_not_of(" ", end+1), line_length);
            end = min(line.find_first_of(" ", begin), line_length);
            token = line.substr(begin, end-begin);
        }

        // print tokens in this line
        // out << "line " << line_count << " contains " << token_count;
        // out << " token" << (token_count==1?"":"s") << endl;
        if (line_count == 1) {
            A = tokenBuffer;
        }
        if (line_count == 3) {
            B = tokenBuffer;
        }
        // out << tokenBuffer << endl;
    }
    // fprintf(out, "Hello\n");
    out << A << endl;
    out << endl;
    out << B << endl;
    out << endl;
    out << A.add(B) << endl;
    out << endl;
    out << A.sub(B) << endl;
    out << endl;
    out << A.sub(A) << endl;
    out << endl;
    BigInteger three("3");
    BigInteger two("2");
    BigInteger C = A.mult(three);
    BigInteger D = B.mult(two);
    out << C.sub(D) << endl;
    out << endl;
    out << A.mult(B) << endl;
    out << endl;
    out << A.mult(A) << endl;
    out << endl;
    out << B.mult(B) << endl;
    out << endl;
    BigInteger nine("9");
    BigInteger sixteen("16");
    BigInteger E = A.mult(A.mult(A.mult(A)));
    BigInteger F = B.mult(B.mult(B.mult(B.mult(B))));
    E = E.mult(nine);
    F = F.mult(sixteen);
    out << E.add(F) << endl;
    out << endl;

    // close files 
    in.close();
    out.close();

    return(EXIT_SUCCESS);
}




// #define MAX_LEN 300

// extern char *strdup(const char *);

// int main(int argc, char * argv[]){
    
//    FILE *in, *out;

//    // check command line for correct number of arguments
//    if( argc != 3 ){
//       printf("Usage: %s <input file> <output file>\n", argv[0]);
//       exit(1);
//    }

//    // open files for reading and writing 
//    in = fopen(argv[1], "r");
//    if( in==NULL ){
//       printf("Unable to open file %s for reading\n", argv[1]);
//       exit(1);
//    }

//    out = fopen(argv[2], "w");
//    if( out==NULL ){
//       printf("Unable to open file %s for writing\n", argv[2]);
//       exit(1);
//    }


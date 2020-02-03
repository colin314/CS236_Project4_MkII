#include<iostream>
#include "Scanner.h"
#include "DataLogger.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    ofstream fout;
    fout.open("output.txt");
    
    Scanner scnr(argv[1]);

    vector<Token> tokens = scnr.Tokenize();
     
    DataLogger dataLogger;

    dataLogger.parse(&tokens);

    cout << dataLogger.toString();
    fout << dataLogger.toString();

    return 1;
}
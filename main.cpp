#include<iostream>
#include "Scanner.h"
#include "DataLogger.h"

using namespace std;

int main(int argc, char* argv[]) {
    ofstream fout;
    fout.open("output.txt");
    
    Scanner scnr(argv[1]);

    vector<Token> tokens = scnr.Tokenize();

    for (size_t i = 0; i < tokens.size(); i++) {
        cout << tokens[i] << endl;
        fout << tokens[i] << endl;
    }
    cout << "Total Tokens = " << tokens.size() << endl;
    fout << "Total Tokens = " << tokens.size();

    fout << endl << endl << endl;

    DataLogger dataLogger;

    dataLogger.parse(&tokens);

    return 1;
}
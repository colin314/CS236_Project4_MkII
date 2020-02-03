#include<iostream>
#include "Scanner.h"
#include "DataLogger.h"
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    Scanner scnr(argv[1]);
    vector<Token> tokens = scnr.Tokenize();
    DataLogger dataLogger;
    dataLogger.parse(&tokens);
    cout << dataLogger.toString();
    return 0;
}
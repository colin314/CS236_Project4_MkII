#include<iostream>
#include "Scanner.h"
#include "DataLogger.h"
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    Scanner* scnr = new Scanner(argv[1]);
    vector<Token> tokens = scnr->Tokenize();
    DataLogger* dataLogger = new DataLogger();
    dataLogger->parse(&tokens);
    cout << dataLogger->toString();
    delete scnr;
    delete dataLogger;
    return 0;
}
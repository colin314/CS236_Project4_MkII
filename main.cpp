#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "Scanner.h"
#include "DataLogger.h"
#include "Database.h"

using namespace std;

int main(int argc, char *argv[])
{
    Scanner *scnr = new Scanner(argv[1]);
    vector<Token> tokens = scnr->Tokenize();
    DataLogger *dataLogger = new DataLogger();
    dataLogger->parse(&tokens);

    Database* db = new Database(*dataLogger);

    cout << db->runQueries() << endl;

    delete scnr;
    delete dataLogger;
    return 0;
}
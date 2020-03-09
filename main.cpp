#include <iostream>
#include <fstream>
#include <string>
#include "Database.h"
#include "Scanner.h"
#include "DataLogger.h"
#include <map>

using namespace std;

int main(int argc, char *argv[])
{
    Scanner *scnr = new Scanner(argv[1]);
    vector<Token> tokens = scnr->Tokenize();
    DataLogger *dataLogger = new DataLogger();
    dataLogger->parse(&tokens);

    Database *db = new Database(*dataLogger);

    cout << db->runQueries();

    delete db;
    delete scnr;
    delete dataLogger;
    return 0;
}
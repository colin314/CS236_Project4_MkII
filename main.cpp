#include<iostream>
#include <fstream>
#include <string>
#include "Relation.h"
#include "Scanner.h"
#include "DataLogger.h"

using namespace std;

int main(int argc, char* argv[]) {
    Scanner* scnr = new Scanner(argv[1]);
    vector<Token> tokens = scnr->Tokenize();
    DataLogger* dataLogger = new DataLogger();
    dataLogger->parse(&tokens);
    cout << dataLogger->toString();

    Relation* rel = new Relation(*(dataLogger->getSchemes()->at(0)));
    const vector<Fact*>* facts = dataLogger->getFacts();
    for (vector<Fact*>::const_iterator cit = facts->cbegin(); cit != facts->cend(); ++cit) {
        const vector<string>* factStrs = (*cit)->getFacts();
        rel->addTuple(*factStrs);
    }

    cout << rel->toString() << endl << endl;
    vector<string> newAttrib;
    newAttrib.push_back("A");
    newAttrib.push_back("N");
    Relation* rel2 = rel->project(newAttrib);
    cout << rel2->toString() << endl << endl;


    delete rel;
    delete scnr;
    delete dataLogger;
    return 0;
}
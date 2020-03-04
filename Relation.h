#pragma once
#include <set>
#include <vector>
#include "Tuple.h"
#include <string>
#include "DbScheme.h"
#include "Scheme.h"
#include <iostream>
#include <sstream>

using std::stringstream;
using std::cout;
using std::endl;
using std::set;
using std::string;
using std::vector;

class Relation {
public:
    Relation(const Scheme& scheme) {
        this->scheme = new DbScheme(scheme);
    }
    Relation(DbScheme* dbScheme) {
        scheme = dbScheme;
    }
    ~Relation() {
        for (set<Tuple*>::iterator it = tuples.begin(); it != tuples.end(); it++) {
            delete *it;
        }
        delete scheme;
    }

    Relation* select();
    Relation* project(const vector<string>& attributes);
    Relation* rename(string oldAttribute, string newAttribute);

    void addTuple(const vector<string>& data);
    string toString() const;

private:
    size_t getIndex(string attribute) {

    }
    Relation() {
        scheme = nullptr;
    }
    Relation(string relationName) {
        name = relationName;
    }
    set<Tuple*> tuples;
    string name;
    DbScheme* scheme;
};


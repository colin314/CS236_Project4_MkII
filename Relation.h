#pragma once
#include <set>
#include <vector>
#include "Tuple.h"
#include <string>
#include "DbScheme.h"
#include "Scheme.h"
#include <iostream>
#include <sstream>
#include <map>

using std::pair;
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
        this->name = scheme.getSchemeId();
    }
    Relation(DbScheme* dbScheme) {
        scheme = dbScheme;
    }
    Relation(DbScheme* dbScheme, const vector<Tuple*>& tuples, string name) {
        scheme = dbScheme;
        for (vector<Tuple*>::const_iterator cit = tuples.cbegin(); cit != tuples.cend(); ++cit) {
            this->tuples.push_back(new Tuple(*(*cit)));
        }
        this->name = name;
    }
    ~Relation() {
        for (vector<Tuple*>::iterator it = tuples.begin(); it != tuples.end(); it++) {
            delete *it;
        }
        delete scheme;
    }

    Relation* select2(const string& attribute1, const string& attribute2);
    Relation* select1(const string& attribute, const string& value);
    Relation* project(const vector<string>& attributes);
    Relation* rename(string oldAttribute, string newAttribute);

    const size_t getAttributeIndex(const string& attribute) {
        return scheme->getAttribIndex(attribute);
    }

    const string getAttribute(size_t index) {
        return scheme->getAttribute(index);
    }

    void addTuple(const vector<string>& data);
    const vector<Tuple*>* getTuples() const { return &tuples; }
    string toString() const;

private:
    Relation() {
        scheme = nullptr;
    }
    Relation(string relationName) {
        name = relationName;
    }
    vector<Tuple*> tuples;
    string name;
    DbScheme* scheme;
};


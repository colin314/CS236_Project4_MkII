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
    Relation(DbScheme* dbScheme, const set<Tuple>& tuples, string name) {
        scheme = dbScheme;
        for (set<Tuple>::const_iterator cit = tuples.cbegin(); cit != tuples.cend(); ++cit) {
            this->tuples.insert(Tuple(*cit));
        }
        this->name = name;
    }
    Relation(const Relation& relation) {
        this->scheme = new DbScheme(*relation.scheme);
        this->name = relation.name;
        this->tuples = relation.tuples;
    }
    ~Relation() {
        delete scheme;
    }

    Relation* select1(const string& attribute, const string& value);
    Relation* select2(const string& attribute1, const string& attribute2);
    Relation* project(const vector<string>& attributes);
    Relation* rename(string oldAttribute, string newAttribute);
    void addTuple(const vector<string>& data);
    string toString() const;

    set<Tuple> getTuples() { return tuples; }
    const size_t getAttributeIndex(const string& attribute) {
        return scheme->getAttribIndex(attribute);
    }
    const string getAttribute(size_t index) {
        return scheme->getAttribute(index);
    }


private:
    Relation() {
        scheme = nullptr;
    }
    Relation(string relationName) {
        name = relationName;
    }
    set<Tuple> tuples;
    string name;
    DbScheme* scheme;
};


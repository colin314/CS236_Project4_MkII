#pragma once
#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include "Relation.h"
#include "DataLogger.h"

using std::stringstream;
using std::map;
using std::string;
using std::vector;
using std::set;
using std::pair;
using std::cout; using std::endl;

class Database {
public:
    Database(const DataLogger& dataLogger) {
        const vector<Scheme*>* schemes = dataLogger.getSchemes();
        for (vector<Scheme*>::const_iterator cit = schemes->cbegin(); cit != schemes->cend(); ++cit) {
            relations.insert(pair<string,Relation*>((*cit)->getSchemeId(), new Relation(*(*cit))));
        }
        const vector<Fact*>* facts = dataLogger.getFacts();
        for (vector<Fact*>::const_iterator cit = facts->begin(); cit != facts->cend(); ++cit) {
            Relation* rel = relations.at((*cit)->getID());
            rel->addTuple(*(*cit)->getFacts());
        }
        const vector<Predicate*>* queries = dataLogger.getQueries();
        for (vector<Predicate*>::const_iterator cit = queries->cbegin(); cit != queries->cend(); ++cit) {
            this->queries.push_back(new Predicate(*(*cit)));
        }
    }
    ~Database() {
        for (map<string, Relation*>::iterator it = relations.begin(); it != relations.end(); ++it) {
            delete it->second;
        }
    }

    string runQueries();

    string toString() const;

private:
    Relation* select1(const string& relationName, const string& attribute, const string& value);
    Relation* project(const string& relationName, const vector<string>& attributes);
    Relation* rename(const string& relationName, const string& oldName, const string& newName);
    Relation* select2(const string& relationName, const string& attribute1, const string& attribute2);
    map<string, Relation*> relations;
    vector<Predicate*> queries;
    string queryResults;
};


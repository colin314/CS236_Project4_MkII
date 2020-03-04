#pragma once
#include <set>
#include <string>
#include "Scheme.h"
#include <vector>
#include "Token.h"
#include <sstream>

using std::stringstream;
using std::vector;
using std::string;
using std::set;

class DbScheme {
public:
    DbScheme(const Scheme& scheme) {
        for (vector<Token*>::const_iterator cit = scheme.begin(); cit != scheme.end(); ++cit) {
            if (attributeSet.find((*cit)->getTokenStr()) != attributeSet.end()) {
                throw "Invalid scheme, attributes must be unique.";
            }

            attributeSet.insert((*cit)->getTokenStr());
            _attributes.push_back((*cit)->getTokenStr());
        }
    }
    DbScheme(const DbScheme& scheme) {
        for (vector<string>::const_iterator cit = scheme._attributes.cbegin(); cit != scheme._attributes.cend(); ++cit) {
            attributeSet.insert(*cit);
            _attributes.push_back(*cit);
        }
    }
    

    ~DbScheme() {}

    size_t getSchemeSize() {
        return _attributes.size();
    }

    bool attribInScheme(string attribute) {
        return attributeSet.find(attribute) != attributeSet.end();
    }

    size_t getAttribIndex(string attribute) {
        vector<string>::iterator it = std::find(_attributes.begin(), _attributes.end(), attribute);
        if (it == _attributes.end()) {
            throw "The given attribute is not in the current scheme";
        }
        return std::distance(_attributes.begin(), it);
    }

    vector<size_t>* getAttributeIndices(const vector<string>& newAttributes);
    DbScheme* generateNewScheme(const vector<string>& newScheme);
    string toString() const;
private:
    
    DbScheme() {}
    set<string> attributeSet;
    vector<string> _attributes;
};


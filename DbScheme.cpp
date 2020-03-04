#include "DbScheme.h"

vector<size_t>* DbScheme::getAttributeIndices(const vector<string>& newAttributes) {
    vector<size_t>* rv = new vector<size_t>();
    for (vector<string>::const_iterator cit = newAttributes.cbegin(); cit != newAttributes.cend(); ++cit) {
        try {
            rv->push_back(getAttribIndex(*cit));
        }
        catch (string error) {
            delete rv;
            throw error;
        }
        catch (...) {
            delete rv;
        }
    }
    return rv;
}

DbScheme* DbScheme::generateNewScheme(const vector<string>& newScheme) {
    DbScheme* rv = new DbScheme();
    for (vector<string>::const_iterator cit = newScheme.cbegin(); cit != newScheme.cend(); ++cit) {
        if (!attribInScheme(*cit)) {
            delete rv;
            throw "Unable to generate new dbScheme. Provided attribute is not in the scheme";
        }
        rv->attributeSet.insert(*cit);
        rv->_attributes.push_back(*cit);
    }
    return rv;
}

string DbScheme::toString() const {
    stringstream sstr;
    for (size_t i = 0; i < _attributes.size(); i++) {
        sstr << _attributes.at(i);
        if (i < _attributes.size() - 1) {
            sstr << ",";
        }
    }
    return sstr.str();
}
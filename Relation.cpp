#include "Relation.h"

Relation* Relation::select() {
    return new Relation();
}

Relation* Relation::project(const vector<string>& attributes) {
    for (vector<string>::const_iterator cit = attributes.cbegin(); cit != attributes.cend(); ++cit) {
        if (!scheme->attribInScheme(*cit)) {
            throw "Unable to perform projection operation, the selected attribute is not in the scheme";
        }
    }

    this->scheme->generateNewScheme(attributes);
    Relation* rv = new Relation(this->scheme->generateNewScheme(attributes));
    
    try {
        vector<size_t>* attributeIndices = scheme->getAttributeIndices(attributes);
        try {
            for (set<Tuple*>::const_iterator cit = tuples.cbegin(); cit != tuples.cend(); ++cit) {
                vector<string> items = (*cit)->getItems(*attributeIndices);
                rv->addTuple(items);
            }
        }
        catch (string& err) {
            delete attributeIndices;
            throw err;
        }
        catch (...) {
            delete attributeIndices;
            throw std::exception("Error encountered in Relation::project");
        }
        

    }
    catch (string& error) {
        delete rv;
        throw error;
    }
    catch (...) {
        delete rv;
        throw std::exception("Error encountered in Relation::project");
    }
    return rv;
}

Relation* Relation::rename(string oldAttribute, string newAttribute) {
    return new Relation();
}

void Relation::addTuple(const vector<string>& data) {
    if (data.size() != scheme->getSchemeSize()) {
        throw "Cannot add tuple to relation. Number of elements in tuple not equal to scheme size.";
    }

    tuples.insert(new Tuple(data));
}

string Relation::toString() const {
    stringstream sstr;
    sstr << "Relation Name: " << name << endl;
    sstr << "Relation Scheme: " << scheme->toString() << endl;
    sstr << "Tuples in Relation:" << endl;
    for (set<Tuple*>::const_iterator cit = tuples.cbegin(); cit != tuples.cend(); ++cit) {
        sstr << "\t" << (*cit)->toString() << endl;
    }
    return sstr.str();
}
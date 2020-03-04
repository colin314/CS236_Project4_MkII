#include "Database.h"

string Database::toString() const {
    stringstream sstr;
    for (map<string, Relation*>::const_iterator cit = relations.cbegin(); cit != relations.cend(); ++cit) {
        sstr << cit->second->toString() << endl;
    }
    return sstr.str();
}

Relation* Database::select1(const string& relationName, const string& attribute, const string& value) {
    return relations.at(relationName)->select1(attribute, value);
}

Relation* Database::select2(const string& relationName, const string& attribute1, const string& attribute2) {
    return relations.at(relationName)->select2(attribute1, attribute2);
}

Relation* Database::project(const string& relationName, const vector<string>& attributes) {
    return relations.at(relationName)->project(attributes);
}

Relation* Database::rename(const string& relationName, const string& oldName, const string& newName) {
    return relations.at(relationName)->rename(oldName, newName);
}

string Database::query1(const string& relationName, const pair<string, string> parameter, const pair<string, string> value) {
    Relation* rel = relations.at(relationName)->select1(value.first, value.second);

    try {
        stringstream sstr;

        const vector<Tuple*>* tuples = rel->getTuples();

        if (tuples->size() == 0) {
            return "No\n";
        }
        else {
            sstr << "Yes(" << tuples->size() << ")" << endl;
            int index = rel->getAttributeIndex(parameter.first);
            for (vector<Tuple*>::const_iterator cit = tuples->cbegin(); cit != tuples->cend(); ++cit) {
                sstr << "  " << parameter.second << "=" << (*cit)->getAt(index) << endl;
            }
        }
        delete rel;
        return sstr.str();
    }
    catch (const std::exception& ex) {
        delete rel;
        throw ex;
    }
}

string Database::query2(const string& relationName, const pair<string, string> param1, const pair<string, string> param2) {
    stringstream sstr;
    if (param1.second == param2.second) {
        Relation* rel = relations.at(relationName)->select2(param1.first, param2.first);
        try {
            const vector<Tuple*>* tuples = rel->getTuples();
            if (tuples->size() == 0) {
                return "No\n";
            }
            else {
                sstr << "Yes(" << tuples->size() << ")" << endl;
                size_t index = rel->getAttributeIndex(param1.first);
                for (size_t i = 0; i < tuples->size(); i++) {
                    sstr << "  " << param1.second << "=" << tuples->at(i)->getAt(index) << endl;
                }
            }
            delete rel;
            return sstr.str();
        }
        catch (const std::exception& ex) {
            delete rel;
            throw ex;
        }
    }
    else {
        Relation* rel = relations.at(relationName);
        const vector<Tuple*>* tuples = rel->getTuples();
        if (tuples->size() == 0) {
            return "No\n";
        }
        else {
            sstr << "Yes(" << tuples->size() << ")" << endl;
            size_t index1 = rel->getAttributeIndex(param1.first);
            size_t index2 = rel->getAttributeIndex(param2.first);
            for (size_t i = 0; i < tuples->size(); i++) {
                sstr << "  " << param1.second << "=" << tuples->at(i)->getAt(index1) << ", " << param2.second << "=" << tuples->at(i)->getAt(index2) << endl;
            }
            return sstr.str();
        }
    }
}

string Database::query3(const string& relationName, const pair<string, string> val1, const pair<string, string> val2) {
    Relation* rel0 = relations.at(relationName)->select1(val1.first, val1.second);
    try {
        Relation* rel = rel0->select1(val2.first, val2.second);
        try {
            stringstream sstr;

            const vector<Tuple*>* tuples = rel->getTuples();

            if (tuples->size() == 0) {
                return "No\n";
            }
            else {
                sstr << "Yes(1)" << endl;
            }
            delete rel0;
            delete rel;
            return sstr.str();
        }
        catch (const std::exception& ex) {
            delete rel;
            throw ex;
        }
    }
    catch (const std::exception& ex) {
        delete rel0;
        throw ex;
    }
}

string Database::runQueries() {
    stringstream sstr;
    for (vector<Predicate*>::const_iterator cit = queries.cbegin(); cit != queries.cend(); ++cit) {
        if ((*cit)->getParameters()->size() != 2) {
            cout << "UNABLE TO HANDLE MORE THAN 2 PARAMETERS IN QUERY" << endl;
        }
        Parameter* param1 = (*cit)->getParameters()->at(0);
        Parameter* param2 = (*cit)->getParameters()->at(1);
        string relationName = (*cit)->getId();
        Relation* rel = relations.at(relationName);
        if (param1->getType() == TokenType::STRING && param2->getType() == TokenType::STRING) {
            StringParam* strParam1 = reinterpret_cast<StringParam*>(param1);
            StringParam* strParam2 = reinterpret_cast<StringParam*>(param2);
            string attribute1 = rel->getAttribute(0);
            string attribute2 = rel->getAttribute(1);
            pair<string, string> val1 = pair<string, string>(attribute1, strParam1->getStr());
            pair<string, string> val2 = pair<string, string>(attribute2, strParam2->getStr());
            sstr << (*cit)->getId() << "(" << strParam1->getStr() << "," << strParam2->getStr() << ")? ";
            sstr << query3(relationName, val1, val2);
        }
        else if (param1->getType() == TokenType::ID && param2->getType() == TokenType::STRING) {
            IdParam* idParam = reinterpret_cast<IdParam*>(param1);
            StringParam* strParam = reinterpret_cast<StringParam*>(param2);
            string attribute1 = rel->getAttribute(0);
            string attribute2 = rel->getAttribute(1);
            pair<string, string> parameter = pair<string, string>(attribute1, idParam->getIdStr());
            pair<string, string> value = pair<string, string>(attribute2, strParam->getStr());
            sstr << (*cit)->getId() << "(" << idParam->getIdStr() << "," << strParam->getStr() << ")? ";
            sstr << query1(relationName, parameter, value);
        }
        else if (param1->getType() == TokenType::STRING && param2->getType() == TokenType::ID) {
            IdParam* idParam = reinterpret_cast<IdParam*>(param2);
            StringParam* strParam = reinterpret_cast<StringParam*>(param1);
            string attribute1 = rel->getAttribute(0);
            string attribute2 = rel->getAttribute(1);
            pair<string, string> parameter = pair<string, string>(attribute2, idParam->getIdStr());
            pair<string, string> value = pair<string, string>(attribute1, strParam->getStr());
            sstr << (*cit)->getId() << "(" << strParam->getStr() << "," << idParam->getIdStr() << ")? ";
            sstr << query1(relationName, parameter, value);
        }
        else if (param1->getType() == TokenType::ID && param2->getType() == TokenType::ID) {
            IdParam* IdParam1 = reinterpret_cast<IdParam*>(param1);
            IdParam* IdParam2 = reinterpret_cast<IdParam*>(param2);
            string attribute1 = rel->getAttribute(0);
            string attribute2 = rel->getAttribute(1);
            pair<string, string> param1 = pair<string, string>(attribute1, IdParam1->getIdStr());
            pair<string, string> param2 = pair<string, string>(attribute2, IdParam2->getIdStr());
            sstr << (*cit)->getId() << "(" << IdParam1->getIdStr() << "," << IdParam2->getIdStr() << ")? ";
            sstr << query2(relationName, param1, param2);
        }
    }
    return sstr.str();
}
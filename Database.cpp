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

string Database::runQueries() {
    stringstream sstr;

    for (vector<Predicate*>::const_iterator query = queries.cbegin(); query != queries.cend(); ++query) {
        sstr << (*query)->getId() << "(";


        string queryId = (*query)->getId();
        Relation* rel = new Relation(*relations.at(queryId));
        vector<Parameter*>* parameters = (*query)->getParameters();
        Relation* rel2 = rel;
        set<string> usedIDs;
        vector<string> usedIDsVec;

        try {
            for (size_t i = 0; i < parameters->size(); ++i) {
                string attrib = rel->getAttribute(i);
                Parameter* parameter = parameters->at(i);

                if (parameter->getType() == TokenType::ID) {
                    IdParam* idParam = dynamic_cast<IdParam*>(parameter);
                    sstr << idParam->getIdStr();

                    if (usedIDs.find(idParam->getIdStr()) == usedIDs.end()) {
                        rel2 = rel;
                        rel = rel2->rename(attrib, idParam->getIdStr());
                        delete rel2; rel2 = nullptr;
                        usedIDs.insert(idParam->getIdStr());
                        usedIDsVec.push_back(idParam->getIdStr());
                    }
                    else {
                        stringstream sstr2;
                        string id = idParam->getIdStr();
                        sstr2 << id << i;
                        id = sstr2.str();

                        rel2 = rel;
                        rel = rel2->rename(attrib, id);
                        delete rel2; rel2 = nullptr;

                        vector<string> projStrs;
                        projStrs.push_back(idParam->getIdStr());
                        Relation* rel3 = rel->project(projStrs);
                        Relation* rel4 = nullptr;
                        Relation* rel5 = nullptr;
                        try {
                            const vector<Tuple*>* tuples = rel3->getTuples();
                            vector<Tuple*>::const_iterator cit = tuples->cbegin();
                            if (cit != tuples->cend()) {
                                rel2 = rel->select1(idParam->getIdStr(), (*cit)->getData()->at(0));
                                rel4 = rel2->select1(id, (*cit)->getData()->at(0));
                                delete rel2; rel2 = nullptr;
                            }
                            ++cit;
                            while (cit != tuples->cend()) {
                                rel2 = rel->select1(idParam->getIdStr(), (*cit)->getData()->at(0));
                                rel5 = rel2->select1(id, (*cit)->getData()->at(0));
                                for (vector<Tuple*>::const_iterator data = rel5->getTuples()->cbegin(); data != rel5->getTuples()->cend(); ++data) {
                                    rel4->addTuple(*(*data)->getData());
                                }
                                delete rel2; rel2 = nullptr;
                                delete rel5; rel5 = nullptr;
                                ++cit;
                            };
                            rel = rel4;
                        }
                        catch (const std::exception& ex) {
                            if (rel3 != nullptr) { delete rel3; }
                            if (rel4 != nullptr) { delete rel4; }
                            if (rel5 != nullptr) { delete rel5; }
                            throw ex;
                        }
                        if (rel3 != nullptr) { delete rel3; }
                        if (rel5 != nullptr) { delete rel5; }
                    }

                }
                else if (parameter->getType() == TokenType::STRING) {
                    StringParam* strParam = dynamic_cast<StringParam*>(parameter);
                    sstr << strParam->getStr();
                    rel2 = rel;
                    rel = rel2->select1(attrib, strParam->getStr());
                    delete rel2; rel2 = nullptr;
                }
                if (parameters->size() > 1 && i < parameters->size() - 1) {
                    sstr << ",";
                }
            }
        }
        catch (const std::exception& ex) {
            if (rel !=  nullptr) { delete rel; }
            if (rel2 != nullptr) { delete rel2; }
            throw ex;
        }
        sstr << ")? ";
        if (rel->getTuples()->size() == 0) {
            sstr << "No" << endl;
        }
        else {
            sstr << "Yes (" << rel->getTuples()->size() << ")" << endl;

            if (usedIDs.size() > 0) {
                const vector<Tuple*>* tuples = rel->getTuples();
                for (vector<Tuple*>::const_iterator cit = tuples->cbegin(); cit != tuples->cend(); ++cit) {
                    sstr << "  ";
                    for (size_t i = 0; i < usedIDsVec.size(); ++i) {
                        size_t attribIndex = rel->getAttributeIndex(usedIDsVec.at(i));
                        sstr << usedIDsVec.at(i) << "=" << (*cit)->getAt(attribIndex);
                        if (i < usedIDsVec.size() - 1) {
                            sstr << ", ";
                        }
                    }
                    sstr << endl;
                }
            }
        }

            if (rel != nullptr) { delete rel; }
            if (rel2 != nullptr) { delete rel2; }
        }
    

    return sstr.str();
}

#include "Relation.h"

Relation *Relation::select1(const string &attribute, const string &value)
{
    if (!scheme->attribInScheme(attribute))
    {
        throw "Error in select. The desired attribute is not present in the scheme";
    }

    size_t attIndex = scheme->getAttribIndex(attribute);

    Relation *rv = new Relation(new DbScheme(*scheme));
    try
    {
        rv->name = this->name;
        for (vector<Tuple *>::const_iterator cit = tuples.cbegin(); cit != tuples.cend(); cit++)
        {
            if ((*cit)->getAt(attIndex) == value)
            {
                rv->addTuple(*((*cit)->getData()));
            }
        }
    }
    catch (const std::exception &ex)
    {
        delete rv;
        throw ex;
    }
    catch (...)
    {
        delete rv;
        throw "Error in Relation::select1";
    }

    return rv;
}

Relation *Relation::select2(const string &attribute1, const string &attribute2)
{
    if (!scheme->attribInScheme(attribute1) || !scheme->attribInScheme(attribute2))
    {
        throw "Error in select, desired attribute is not present in the scheme";
    }

    size_t index1 = scheme->getAttribIndex(attribute1);
    size_t index2 = scheme->getAttribIndex(attribute2);

    Relation *rv = new Relation(new DbScheme(*scheme));
    try
    {
        rv->name = this->name;
        for (vector<Tuple *>::const_iterator cit = tuples.cbegin(); cit != tuples.cend(); cit++)
        {
            if ((*cit)->getAt(index1) == (*cit)->getAt(index2))
            {
                rv->addTuple(*((*cit)->getData()));
            }
        }
    }
    catch (const std::exception &ex)
    {
        delete rv;
        throw ex;
    }
    catch (...)
    {
        delete rv;
        throw "Error in Relation::select1";
    }
    return rv;
}

Relation *Relation::project(const vector<string> &attributes)
{
    for (vector<string>::const_iterator cit = attributes.cbegin(); cit != attributes.cend(); ++cit)
    {
        if (!scheme->attribInScheme(*cit))
        {
            throw "Unable to perform projection operation, the selected attribute is not in the scheme";
        }
    }

    this->scheme->generateNewScheme(attributes);
    Relation *rv = new Relation(this->scheme->generateNewScheme(attributes));
    try
    {
        rv->name = this->name;
        vector<size_t> *attributeIndices = scheme->getAttributeIndices(attributes);
        try
        {
            for (vector<Tuple *>::const_iterator cit = tuples.cbegin(); cit != tuples.cend(); ++cit)
            {
                vector<string> items = (*cit)->getItems(*attributeIndices);
                rv->addTuple(items);
            }
        }
        catch (string &err)
        {
            delete attributeIndices;
            throw err;
        }
        catch (...)
        {
            delete attributeIndices;
            throw "Error encountered in Relation::project";
        }
    }
    catch (string &error)
    {
        delete rv;
        throw error;
    }
    catch (...)
    {
        delete rv;
        throw "Error encountered in Relation::project";
    }
    return rv;
}

Relation *Relation::rename(string oldAttribute, string newAttribute)
{
    if (!scheme->attribInScheme(oldAttribute))
    {
        throw "Cannot rename attribute. The given attribute is not in the scheme";
    }

    if (scheme->attribInScheme(newAttribute) && oldAttribute != newAttribute)
    {
        throw std::exception();
    }

    size_t oldIndex = scheme->getAttribIndex(oldAttribute);
    DbScheme *newScheme = scheme->generateNewScheme(oldIndex, newAttribute);
    Relation *rv = new Relation(newScheme, this->tuples, this->name);

    return rv;
}

void Relation::addTuple(const vector<string> &data)
{
    if (data.size() != scheme->getSchemeSize())
    {
        throw "Cannot add tuple to relation. Number of elements in tuple not equal to scheme size.";
    }

    bool unequal = true;
    for (vector<Tuple *>::const_iterator cit = tuples.cbegin(); cit != tuples.cend(); cit++)
    {
        unequal = false;
        for (size_t i = 0; i < data.size(); i++)
        {
            if ((*cit)->getAt(i) != data.at(i))
            {
                unequal = true;
                break;
            }
        }
        if (!unequal)
        {
            return;
        }
    }
    tuples.push_back(new Tuple(data));
}

string Relation::toString() const
{
    stringstream sstr;
    sstr << "Relation Name: " << name << endl;
    sstr << "Relation Scheme: " << scheme->toString() << endl;
    sstr << "Tuples in Relation:" << endl;
    for (vector<Tuple *>::const_iterator cit = tuples.cbegin(); cit != tuples.cend(); ++cit)
    {
        sstr << "\t" << (*cit)->toString() << endl;
    }
    return sstr.str();
}
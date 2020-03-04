#pragma once
#include "Relation.h"
#include <set>

using std::set;

class Database {
public:
    Database() {}
    ~Database() {}

private:
    set<Relation*> relations;
};


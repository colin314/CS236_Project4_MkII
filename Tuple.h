#pragma once
#include <map>
#include <string>
#include <vector>
#include <sstream>

using std::stringstream;
using std::vector;
using std::string;
using std::map;

class Tuple {
public:
    Tuple() { }
    Tuple(const vector<string>& data) {
        for (vector<string>::const_iterator cit = data.cbegin(); cit != data.cend(); ++cit) {
            values.push_back(*cit);
        }
    }
    Tuple(const Tuple& old) {
        for (size_t i = 0; i < old.values.size(); i++) {
            this->values.push_back(old.values.at(i));
        }
    }
    ~Tuple() { }

    string getAt(size_t index) {
        return values.at(index);
    }

    vector<string> getItems(const vector<size_t>& indicies) {
        vector<string> rv;

        for (vector<size_t>::const_iterator cit = indicies.cbegin(); cit != indicies.cend(); ++cit) {
            rv.push_back(values.at(*cit));
        }

        return rv;
    }

    const vector<string>* getData() const {
        return &values;
    }

    string toString() const;

private:
    vector<string> values;
};


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

    string getAt(size_t index) const {
        return values.at(index);
    }

    vector<string> getItems(const vector<size_t>& indicies) const {
        vector<string> rv;

        for (vector<size_t>::const_iterator cit = indicies.cbegin(); cit != indicies.cend(); ++cit) {
            rv.push_back(values.at(*cit));
        }

        return rv;
    }

    const vector<string> getData() const {
        return values;
    }

    string toString() const;

    bool operator< (const Tuple& t) {
        if (this->values.size() < t.values.size()) {
            for (size_t i = 0; i < this->values.size(); i++) {
                if (this->values.at(i) < t.values.at(i)) {
                    return true;
                }
            }
        }
        else {
            for (size_t i = 0; i < t.values.size(); i++) {
                if (t.values.at(i) < this->values.at(i)) {
                    return false;
                }
            }
        }
        return this->values.size() < t.values.size();
    }

    friend bool operator< (const Tuple& t1, const Tuple& t2);

    //friend bool operator< (const Tuple& t1, const Tuple& t2) {
    //    if (t1.values.size() < t2.values.size()) {
    //        for (size_t i = 0; i < data1.size(); i++) {
    //            if (data1.at(i) < data2.at(i)) {
    //                return data1.at(i) < data2.at(i);
    //            }
    //        }
    //        return data1.size() < data2.size();
    //    }
    //    else {
    //        for (size_t i = 0; i < data2.size(); i++) {
    //            if (data1.at(i) < data2.at(i)) {
    //                return data1.at(i) < data2.at(i);
    //            }
    //        }
    //        return data2.size() < data1.size();
    //    }


    //}

private:
    vector<string> values;
};


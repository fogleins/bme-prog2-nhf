//
// Created by Simon on 2020-04-17.
//

#include "family.h"

Family& Family::operator=(const Family& rhs) {
    setID(rhs.getID());
    setTitle(rhs.getTitle());
    setRunningTime(rhs.getRunningTime());
    setReleaseYear(rhs.getReleaseYear());
    setCategory(rhs.getCategory());
    ageRating = rhs.ageRating;
    // setCollection(rhs.getCollection());
    return *this;
}

bool Family::operator==(const Family &rhs) {
    if (this == &rhs)
        return true;
    else
        return this->getTitle() == rhs.getTitle() && this->getRunningTime() == rhs.getRunningTime() &&
            this->getReleaseYear() == rhs.getReleaseYear() && this->getCategory() == rhs.getCategory() &&
            ageRating == rhs.ageRating /*&& this->getCollection() == rhs.getCollection()*/;
}

void Family::print(const string &sep) {
    Movie::print(sep);
    cout << sep << "Korhatar-besorolas: " << ageRating;
}

void Family::print(ofstream &ofs) {
    Movie::print(ofs);
    ofs << ";" << ageRating;
}

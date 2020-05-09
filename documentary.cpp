//
// Created by Simon on 2020-04-17.
//

#include "documentary.h"

Documentary& Documentary::operator=(const Documentary& rhs) {
    setID(rhs.getID());
    setTitle(rhs.getTitle());
    setRunningTime(rhs.getRunningTime());
    setReleaseYear(rhs.getReleaseYear());
    description = rhs.description;
    setCategory(rhs.getCategory());
    //setCollection(rhs.getCollection());
    return *this;
}

bool Documentary::operator==(const Documentary& rhs) {
    if (this == &rhs)
        return true;
    else
        return this->getTitle() == rhs.getTitle() && this->getRunningTime() == rhs.getRunningTime() &&
            this->getRunningTime() == rhs.getReleaseYear() && this->getCategory() == rhs.getCategory() &&
            this->description == rhs.description /*&& this->getCollection() == rhs.getCollection()*/;
}

void Documentary::print(const string& sep) {
    Movie::print(sep);
    cout << sep << "Leiras: " << description;
}

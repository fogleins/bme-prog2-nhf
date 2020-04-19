//
// Created by Simon on 2020-04-17.
//

#ifndef FILMTAR_COLLECTION_H
#define FILMTAR_COLLECTION_H

#include "movie.h"
#include "data.h"

class Collection {
    Data movies; /**< A tárolt filmek pointereit tároló tömb */
public:
    bool add();
    void print();
    void find(const char* keyword);
    // TODO
    /** Egy vagy az összes elem törlése */
    bool clear();


};


#endif //FILMTAR_COLLECTION_H

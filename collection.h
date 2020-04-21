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
    void add(Movie& mv);
    void print();
    void search(const char* keyword);
    // TODO
    /** Egy elem törlése */
    void clear(int id);
    /** Az összes elem törlése */
    void clear();
};


#endif //FILMTAR_COLLECTION_H

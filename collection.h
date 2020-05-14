//
// Created by Simon on 2020-04-17.
//

#ifndef FILMTAR_COLLECTION_H
#define FILMTAR_COLLECTION_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "data.hpp"
#include "movie.h"
#include "family.h"
#include "documentary.h"

using namespace std;

class Collection {
    Data<Movie> movies; /**< A tárolt filmek pointereit tároló tömb */
public:
    Collection() : movies(Data<Movie>()) { }
    // ~Collection() { movies.~Data(); }
    // TODO: Data& ok?
    Data<Movie>& getMovies();
    void add(Movie& mv);
    void add(Movie* mv);
    void remove(unsigned int index);
    void print(ostream& os = cout);
    void print(unsigned int index);
    void search(const string& keyword, ostream& os = cout);
    /** Az összes elem törlése */
    void clearCollection();
    void readFile(const char* path);
    void writeFile(const char* path);
    Collection& operator=(const Collection& rhs);
    bool operator==(const Collection& rhs);
};


#endif //FILMTAR_COLLECTION_H

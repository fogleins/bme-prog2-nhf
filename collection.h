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


/** @class Collection collection.h
 *  @brief A gyűjtemény osztály, összeköti a tároló- és a film osztályokat
 */
class Collection {
    Data<Movie> movies; /**< A tárolt filmek pointereit tároló tömb */
public:
    /** Paraméter nélküli konstruktor */
    Collection() : movies(Data<Movie>()) { }

    /** Getter függvény a tárolt Data tömb visszaadására
     *
     * @return A tárolt Data<Movie>&
     */
    Data<Movie>& getMovies() {
        return movies;
    }
    void add(Movie& mv);
    void add(Movie* mv);
    void remove(unsigned int index);
    void print(std::ostream& os = std::cout) const;
    void print(unsigned int index, std::ostream& os = std::cout) const;
    void search(const std::string& keyword, std::ostream& os = std::cout) const;
    void clear();
    void readFile(const char* path);
    void writeFile(const char* path) const;
};


#endif //FILMTAR_COLLECTION_H

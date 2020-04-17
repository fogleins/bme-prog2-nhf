//
// Created by Simon on 2020-04-17.
//

#ifndef FILMTAR_DOCUMENTARY_H
#define FILMTAR_DOCUMENTARY_H

#include "movie.h"

class Documentary : public Movie {
    string description;
public:
    /** A dokumentumfilm osztály konstruktora
     *
     * @param t A film címe
     * @param rt A film hossza percben
     * @param ry A film kiadásának éve
     * @param d A film rövid leírása
     */
    Documentary(const string& title, unsigned int runningTime, unsigned int releaseYear, string description)
        : Movie(title, runningTime, releaseYear, category = Documentary), description(description) { }
};


#endif //FILMTAR_DOCUMENTARY_H

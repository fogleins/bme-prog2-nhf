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
     * @param title A film címe
     * @param runningTime A film hossza percben
     * @param releaseYear A film kiadásának éve
     * @param description A film rövid leírása
     */
    Documentary(const string& title, unsigned int runningTime, unsigned int releaseYear, const string& description)
        : Movie(c.movies.getElementCount() + 1, title, runningTime, releaseYear, DocumentaryE),
        description(description) { }
    /** Getter függvény a leírás visszaadására
     *
     * @return A dokumentumfilm leírása
     */
    string getDescription() {
        return description;
    }
    Documentary& operator=(const Documentary& rhs);
    bool operator==(const Documentary& rhs);
};


#endif //FILMTAR_DOCUMENTARY_H

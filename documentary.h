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
     * @param _title A film címe
     * @param _runningTime A film hossza percben
     * @param _releaseYear A film kiadásának éve
     * @param _description A film rövid leírása
     */
    Documentary(const string& _title, unsigned int _runningTime, unsigned int _releaseYear, const string& _description)
        : Movie(_title, _runningTime, _releaseYear, DocumentaryE),
        description(_description) { }

    /** Getter függvény a leírás visszaadására
     *
     * @return A dokumentumfilm leírása
     */
    string getDescription() {
        return description;
    }

    void print(const string& sep = " ");
    Documentary& operator=(const Documentary& rhs);
    bool operator==(const Documentary& rhs);
    bool operator==(const Movie& rhs) {
        return false;
    }
};


#endif //FILMTAR_DOCUMENTARY_H

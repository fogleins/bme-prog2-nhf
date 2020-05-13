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
    explicit Documentary(const string& _title = "No title", unsigned int _runningTime = -1,
            unsigned int _releaseYear = -1, const string& _description = "No description")
        : Movie(_title, _runningTime, _releaseYear, DocumentaryE), description(_description) { }

    ~Documentary() { }

    string getCategoryStr() const {
        return "Documentary";
    }

    /** Getter függvény a leírás visszaadására
     *
     * @return A dokumentumfilm leírása
     */
    string getDescription() {
        return description;
    }

    void print(ostream& os = cout, bool file = false) const;
    Documentary& operator=(const Documentary& rhs);
    bool operator==(const Documentary& rhs);

    /** Egyenlőségvizsgálat-operator overloadja Documentary és Movie típusra
     *
     * @param rhs A jobboldali, Movie típusú objektum
     * @return False, mivel két különböző típusú film nem lehet azonos
     */
    bool operator==(const Movie& rhs) {
        return false;
    }
};


#endif //FILMTAR_DOCUMENTARY_H

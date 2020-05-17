//
// Created by Simon on 2020-04-17.
//

#ifndef FILMTAR_DOCUMENTARY_H
#define FILMTAR_DOCUMENTARY_H

#include "movie.h"


/** @class Documentary documentary.h
 *  @brief A dokumentumfilm típust megvalósító osztály
 */
class Documentary : public Movie {
    std::string description;
public:
    /** A dokumentumfilm osztály konstruktora
     *
     * @param _title A film címe
     * @param _runningTime A film hossza percben
     * @param _releaseYear A film kiadásának éve
     * @param _description A film leírása
     */
    Documentary(const std::string& _title, unsigned int _runningTime, unsigned int _releaseYear,
            const std::string& _description) : Movie(_title, _runningTime, _releaseYear, DocumentaryE),
            description(_description) { }

    /** Paraméter nélküli konstruktor */
    Documentary(): Movie(), description("") { setCategory(DocumentaryE); }

    /** Másoló konstruktor
     *
     * @param from A másolandó film
     */
    Documentary(const Documentary& from)  : Movie(from) {
        description = from.description;
    }

    /** Destruktor */
    ~Documentary() { }

    /** @return A kategória megnevezése */
    std::string getCategoryStr() const {
        return "Documentary";
    }

    /** @return A dokumentumfilm leírása */
    std::string getDescription() const {
        return description;
    }

    void print(std::ostream& os = std::cout, bool file = false) const;
    Documentary& operator=(const Documentary& rhs);
    bool operator==(const Documentary& rhs) const;

    /** Egyenlőségvizsgálat-operator overloadja Documentary és Movie típusra
     *
     * @param rhs A jobboldali, Movie típusú objektum
     * @return Hamis, mert két különböző típusú film tulajdonságai nem egyezhetnek
     */
    bool operator==(const Movie& rhs) const {
        return false;
    }
};


#endif //FILMTAR_DOCUMENTARY_H

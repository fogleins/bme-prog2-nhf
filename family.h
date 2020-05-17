//
// Created by Simon on 2020-04-17.
//

#ifndef FILMTAR_FAMILY_H
#define FILMTAR_FAMILY_H

#include "movie.h"


/** Korhatár-besorolások */
enum Rating {
    unrated = -1, /**< Besorolás nélküli */
    allAges = 0, /**< Minden korosztály nézheti */
    ages6AndUp = 6, /**< 6 éven felülieknek */
    ages12AndUp = 12, /**< 12 éven felülieknek */
    ages16AndUp = 16, /**< 16 éven felülieknek */
    ages18AndUp = 18 /**< 18 éven felülieknek */
};

/** @class Family family.h
 *  @brief Családi film típust megvalósító osztály
 */
class Family : public Movie {
    Rating ageRating; /**< A film korhatár-besorolása */
public:
    /** A család osztály konstruktora
     *
     * @param _title A film címe
     * @param _runningTime A film hossza percben
     * @param _releaseYear A film megjelenési éve
     * @param _rating A film korhatár-besorolása
     */
    Family(const std::string& _title, unsigned int _runningTime, unsigned int _releaseYear, Rating _rating = unrated)
        : Movie(_title, _runningTime, _releaseYear, FamilyE), ageRating(_rating) { }

    /** Paraméter nélküli konstruktor */
    Family(): Movie(), ageRating(unrated) { setCategory(FamilyE); }

    /** Másoló konstruktor
     *
     * @param from A másolandó film
     */
    Family(const Family& from): Movie(from) {
        ageRating = from.ageRating;
    }

    /** Destruktor */
    ~Family() { }

    /** @return A kategória megnevezése */
    std::string getCategoryStr() const {
        return "Family";
    }

    /** @return A családi film korhatár-besorolása */
    Rating getAgeRating() const {
        return ageRating;
    }

    void print(std::ostream& os = std::cout, bool file = false) const;
    Family& operator=(const Family& rhs);
    bool operator==(const Family& rhs) const;

    /** Egyenlőségvizsgálat-operator overloadja Family és Movie típusra
     *
     * @param rhs A jobboldali, Movie típusú objektum
     * @return Hamis, mert két különböző típusú film tulajdonságai nem egyezhetnek
     */
    bool operator==(const Movie& rhs) const {
        return false;
    }
};


#endif //FILMTAR_FAMILY_H

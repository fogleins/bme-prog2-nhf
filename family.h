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

/** Családi film objektumot tároló osztály */
class Family : public Movie {
    Rating ageRating; /**< A film korhatára */
public:
    /** A család osztály konstruktora
     *
     * @param title A film címe
     * @param runningTime A film hossza percben
     * @param releaseYear A film megjelenési éve
     * @param rating A film korhatár-besorolása
     */
    Family(const string& title, unsigned int runningTime, unsigned int releaseYear, Rating rating)
        : Movie(c.movies.getElementCount() + 1, title, runningTime, releaseYear, FamilyE), ageRating(rating) { }
    /** Getter függvény a korhatár-besorolás visszaadására
     *
     * @return A film korhatár-besorolása
     */
    Rating getAgeRating() {
        return ageRating;
    }
    Family& operator=(const Family& rhs);
    bool operator==(const Family& rhs);
};


#endif //FILMTAR_FAMILY_H

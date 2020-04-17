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
     * @param t A film címe
     * @param rt A film hossza percben
     * @param ry A film megjelenési éve
     * @param r A film korhatár-besorolása
     */
    Family(const string& title, unsigned int runningTime, unsigned int releaseYear, Rating rating)
        : Movie(title, runningTime, releaseYear, category = Family), ageRating(rating) { }
};


#endif //FILMTAR_FAMILY_H

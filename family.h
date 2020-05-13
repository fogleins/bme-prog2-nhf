//
// Created by Simon on 2020-04-17.
//

#ifndef FILMTAR_FAMILY_H
#define FILMTAR_FAMILY_H

#include "movie.h"

using namespace std;

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
     * @param _title A film címe
     * @param _runningTime A film hossza percben
     * @param _releaseYear A film megjelenési éve
     * @param _rating A film korhatár-besorolása
     */
    explicit Family(const string& _title = "No title", unsigned int _runningTime = -1,
            unsigned int _releaseYear = -1, Rating _rating = unrated)
        : Movie(_title, _runningTime, _releaseYear, FamilyE), ageRating(_rating) { }

    ~Family() { }

    string getCategoryStr() const {
        return "Family";
    }

    /** Getter függvény a korhatár-besorolás visszaadására
     *
     * @return A film korhatár-besorolása
     */
    Rating getAgeRating() {
        return ageRating;
    }

    void print(const string& sep = "\t") const;
    void print(ofstream& ofs) const;
    Family& operator=(const Family& rhs);
    bool operator==(const Family& rhs);
    bool operator==(const Movie& rhs) {
        return false;
    }
};


#endif //FILMTAR_FAMILY_H

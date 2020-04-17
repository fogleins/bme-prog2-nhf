//
// Created by Simon on 2020-04-17.
//

#ifndef FILMTAR_MOVIE_H
#define FILMTAR_MOVIE_H

#include <string>

using namespace std;

/** A film lehetséges típusai */
enum Category {
    Family, /**< Családi film */
    Documentary, /**< Dokumentumfilm */
    Other /**< Egyéb film */
};

class Movie {
protected:
    string title; /**< A film címe */
    unsigned int runningTime; /**< A film hossza percben */
    unsigned int releaseYear; /**< A film kiadásának éve */
    Category category; /**< A film típusa */
public:
    /** A film osztály konstruktora
     *
     * @param t A film címe
     * @param rt A film hossza percben
     * @param ry A film megjelenési éve
     * @param category A film típusa
     */
    Movie(const string& t, unsigned int rt, unsigned int ry, Category category)
        : title(t), runningTime(rt), releaseYear(ry), category(category) { }


};


#endif //FILMTAR_MOVIE_H

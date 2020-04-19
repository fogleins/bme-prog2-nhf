//
// Created by Simon on 2020-04-17.
//

#ifndef FILMTAR_MOVIE_H
#define FILMTAR_MOVIE_H

#include <string>

using namespace std;

/** A film lehetséges típusai */
enum Category {
    FamilyE, /**< Családi film */
    DocumentaryE, /**< Dokumentumfilm */
    OtherE /**< Egyéb film */
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
     * @param title A film címe
     * @param runningTime A film hossza percben
     * @param releaseYear A film megjelenési éve
     * @param category A film típusa
     */
    Movie(const string& title, unsigned int runningTime, unsigned int releaseYear, Category category = OtherE)
        : title(title), runningTime(runningTime), releaseYear(releaseYear), category(category) { }
    Movie& operator=(Movie& rhs);
    bool operator==(Movie& rhs);

};


#endif //FILMTAR_MOVIE_H

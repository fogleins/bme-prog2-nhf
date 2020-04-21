//
// Created by Simon on 2020-04-17.
//

#ifndef FILMTAR_MOVIE_H
#define FILMTAR_MOVIE_H

#include <string>

#include "data.h"
#include "collection.h"

using namespace std;

/** A film lehetséges típusai */
enum Category {
    FamilyE, /**< Családi film */
    DocumentaryE, /**< Dokumentumfilm */
    OtherE /**< Egyéb film */
};

class Movie {
protected:
    unsigned int id;
    string title; /**< A film címe */
    unsigned int runningTime; /**< A film hossza percben */
    unsigned int releaseYear; /**< A film kiadásának éve */
    Category category; /**< A film típusa */
    Collection c; /**< Az a Collection, ami tartalmazza a filmet */
public:
    Movie();
    /** A film osztály konstruktora
     *
     * @param id A film azonosítója
     * @param title A film címe
     * @param runningTime A film hossza percben
     * @param releaseYear A film megjelenési éve
     * @param category A film típusa
     */
    Movie(int id, const string& title, unsigned int runningTime, unsigned int releaseYear, Category category = OtherE)
        : id(c.movies.getElementCount() + 1), title(title), runningTime(runningTime),
        releaseYear(releaseYear), category(category) { }

    unsigned int getID() {
        return id;
    }
    string getTitle() {
        return title;
    }
    unsigned int getRunningTime() {
        return runningTime;
    }
    unsigned int getReleaseYear() {
        return releaseYear();
    }
    Category getCategory() {
        return category;
    }
    Movie& operator=(const Movie& rhs);
    bool operator==(const Movie& rhs);
    // std::ostream& operator<<(std::ostream& os, const String& s0);
};


#endif //FILMTAR_MOVIE_H

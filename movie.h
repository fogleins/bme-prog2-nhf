//
// Created by Simon on 2020-04-17.
//

#ifndef FILMTAR_MOVIE_H
#define FILMTAR_MOVIE_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

/** A film lehetséges típusai */
enum Category {
    FamilyE, /**< Családi film */
    DocumentaryE, /**< Dokumentumfilm */
    OtherE /**< Egyéb film */
};

class Movie {
private:
    unsigned int id; /**< A film azonosítója és indexere */
    string title; /**< A film címe */
    unsigned int runningTime; /**< A film hossza percben */
    unsigned int releaseYear; /**< A film kiadásának éve */
    Category category; /**< A film típusa */
public:
    /** A film osztály konstruktora
     *
     * @param _title A film címe
     * @param _runningTime A film hossza percben
     * @param _releaseYear A film megjelenési éve
     * @param _category A film típusa
     */
    explicit Movie(const string& _title = "No title", unsigned int _runningTime = -1, unsigned int _releaseYear = -1,
            Category _category = OtherE)
        : id(-1), title(_title), runningTime(_runningTime), releaseYear(_releaseYear), category(_category) { }

    virtual ~Movie() { }

    // getters
    unsigned int getID() const {
        return id;
    }
    string getTitle() const {
        return title;
    }
    unsigned int getRunningTime() const {
        return runningTime;
    }
    unsigned int getReleaseYear() const {
        return releaseYear;
    }
    Category getCategory() const {
        return category;
    }
    virtual string getCategoryStr() const {
        return "Movie";
    }

    // setters
    void setID(unsigned int _id) {
        id = _id;
    }
    void setTitle(const string& t) {
        title = t;
    }
    void setRunningTime(unsigned int rt) {
        runningTime = rt;
    }
    void setReleaseYear(unsigned int ry) {
        releaseYear = ry;
    }
    void setCategory(Category cat) {
        category = cat;
    }

    virtual void print(ostream& os = cout, bool file = false) const;

    // TODO: copy ctor?
    // TODO: virtual legyen?
    /*virtual*/ Movie& operator=(const Movie& rhs);
    virtual bool operator==(const Movie& rhs);
};

#endif //FILMTAR_MOVIE_H

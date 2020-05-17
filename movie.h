//
// Created by Simon on 2020-04-17.
//

#ifndef FILMTAR_MOVIE_H
#define FILMTAR_MOVIE_H

#include <string>
#include <iostream>
#include <fstream>


/** A film lehetséges típusai */
enum Category {
    FamilyE, /**< Családi film */
    DocumentaryE, /**< Dokumentumfilm */
    OtherE /**< Egyéb film */
};

/** @class Movie movie.h
 *  @brief A film típust megvalósító osztály
 */
class Movie {
private:
    unsigned int id; /**< A film azonosítója és indexere */
    std::string title; /**< A film címe */
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
    Movie(const std::string& _title, unsigned int _runningTime, unsigned int _releaseYear, Category _category = OtherE)
        : id(0), title(_title), runningTime(_runningTime), releaseYear(_releaseYear), category(_category) { }

    /** Paraméter nélküli konstruktor */
    Movie(): id(0), title(""), runningTime(0), releaseYear(0), category(OtherE) { }

    /** Másoló konstruktor
     *
     * @param from A másolandó film
     */
    Movie(const Movie& from) {
        id = 0;
        title = from.title;
        runningTime = from.runningTime;
        releaseYear = from.releaseYear;
        category = from.category;
    }

    /** Destruktor */
    virtual ~Movie() { }

    // getter függvények
    /** @return A film azonosítója */
    unsigned int getID() const {
        return id;
    }
    /** @return A film címe */
    std::string getTitle() const {
        return title;
    }
    /** @return A film hossza */
    unsigned int getRunningTime() const {
        return runningTime;
    }
    /** @return A film kiadási éve */
    unsigned int getReleaseYear() const {
        return releaseYear;
    }
    /** @return A film kategóriája */
    Category getCategory() const {
        return category;
    }
    /** @return A kategória megnevezése */
    virtual std::string getCategoryStr() const {
        return "Movie";
    }

    // setter függvények
    /** Beállítja a film azonosítóját
     *
     * @param _id  A film azonosítója
     */
    void setID(unsigned int _id) {
        id = _id;
    }
    /** Beállítja a film címét
     *
     * @param t A film címe
     */
    void setTitle(const std::string& t) {
        title = t;
    }
    /** Beállítja a film hosszát
     *
     * @param rt A film hossza
     */
    void setRunningTime(unsigned int rt) {
        runningTime = rt;
    }
    /** Beállítja a film kiadási évét
     *
     * @param ry A film kiadásának éve
     */
    void setReleaseYear(unsigned int ry) {
        releaseYear = ry;
    }
    /** Beállítja a film kategóriáját
     *
     * @param cat A film kategóriája
     */
    void setCategory(Category cat) {
        category = cat;
    }

    virtual void print(std::ostream& os = std::cout, bool file = false) const;
    Movie& operator=(const Movie& rhs);
    bool operator==(const Movie& rhs) const;
};

#endif //FILMTAR_MOVIE_H

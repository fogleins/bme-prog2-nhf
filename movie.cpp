//
// Created by Simon on 2020-04-17.
//

#include "movie.h"

Movie& Movie::operator=(const Movie& rhs) {
    if (this != &rhs) {
        id = rhs.id;
        title = rhs.title;
        runningTime = rhs.runningTime;
        releaseYear = rhs.releaseYear;
        category = rhs.category;
        //c = rhs.c;
    }
    return *this;
}

bool Movie::operator==(const Movie& rhs) {
    if (this == &rhs)
        return true;
    else
        return title == rhs.title && runningTime == rhs.runningTime && releaseYear == rhs.releaseYear &&
               category == rhs.category/* && c == rhs.c*/;
}

/** Kiírja a film adatait a konzolra
 *
 * @param sep Az adattagok közötti elválasztó karakter vagy karaktersorozat
 */
void Movie::print(const string& sep) {
    // TODO: separator referencia ok?
    // TODO: endl mindig a hívás helyén kell, így az öröklött osztályok használhatják az alaposztály printjét
    // TODO: category-nak a nevét írja ki, vagy elég az enum-os szám?
    std::cout << id << sep << title << sep << runningTime << sep << releaseYear << sep << category;
}

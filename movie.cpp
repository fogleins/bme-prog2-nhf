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
    }
    return *this;
}

bool Movie::operator==(const Movie& rhs) {
    if (this == &rhs)
        return true;
    else
        return title == rhs.title && runningTime == rhs.runningTime && releaseYear == rhs.releaseYear &&
               category == rhs.category;
}

/** Kiírja a film adatait a konzolra
 *
 * @param sep Az adattagok közötti elválasztó karakter vagy karaktersorozat
 */
void Movie::print(const string& sep) const {
    cout << id << sep << title << sep << runningTime << " perc"<< sep << releaseYear << sep << getCategoryStr();
}

/** Fájlba írja a film adatait
 *
 * @param ofs A fájl, amibe az adatokat írja
 */
void Movie::print(ofstream& ofs) const {
    ofs << category << ";" << title << ";" << runningTime << ";" << releaseYear;
}

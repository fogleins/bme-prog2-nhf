//
// Created by Simon on 2020-04-17.
//

#include "collection.h"

Data<Movie>& Collection::getMovies() {
    return movies;
}

void Collection::add(Movie& mv) {
    mv.setID(movies.getElementCount() + 1);
    // mv.setCollection(this);
    movies.addElement(mv);
}


void Collection::remove(unsigned int index) {
    movies.removeElement(index);
}

/** Kilistázza az összes filmet és azok adatait */
void Collection::print() {
    for (unsigned int i = 0; i < movies.getElementCount(); ++i) {
        // TODO: öröklött osztályok is írják ki a tulajdonságaikat, legyen külön Movie.print(), stb?
        // TODO: meghívja az overloaded függvényt a for-on belül?
//        cout << movies[i]->getID() << " " << movies[i]->getTitle() << " " << movies[i]->getRunningTime() << " " <<
//            movies[i]->getReleaseYear();
//        if (movies[i]->getCategory() == OtherE) {
//            cout << " Other" << endl;
//        }
//        else if (movies[i]->getCategory() == FamilyE) {
//            Family* mv = (Family*) movies[i];
//            cout << " Family " << mv->getAgeRating() << endl;
//        }
//        else if (movies[i]->getCategory() == DocumentaryE) {
//            Documentary* mv = (Documentary*) movies[i];
//            cout << " Documentary " << mv->getDescription() << endl;
//        }
        movies[i]->print();
    }
}

/** Kiírja egy adott indexű film adatait */
void Collection::print(unsigned int index) {
    movies[index]->print();
}

/** Keresés a filmek címei között
 *
 * @param keyword A keresendő kifejezés
 */
 // TODO: bővítés más tulajdonságokra is
void Collection::search(const string& keyword) {
    for (unsigned int i = 0; i < movies.getElementCount(); ++i) {
        // std::string::find()
        size_t found = movies[i]->getTitle().find(keyword);
        if (found != -1)
            print(i);
    }
}

/** Az összes elem törlése */
void Collection::clearCollection() {
    // Hátulról indul, így nem kell minden egyes törlés után áthelyezni az elemeket
    for (unsigned int i = movies.getElementCount(); i >= 0; --i) {
        movies.removeElement(i);
    }
}

/** Korábban létrehozott gyűjtemény betöltése fájlból
 *
 * @param path A fájl elérési útja
 */
void Collection::readFile(const char* path) {
    ifstream inputTxt;
    inputTxt.open(path);
    string line;
//    while (getline(inputTxt,line)) {
// TODO: fájl adatainak tárolása, objektumok létrehozása, split, konverzió, tömb feltöltése -> virtual
//
//        if (line[0] == '0') {
//            // hívja meg a movie osztály beolvasó függvényét
//        }
//        else if (line[0] == '1') {
//            //
//        }
//        else if (line[0] == '2') {
//            //
//        }
//    }
//    inputTxt.close();
}

void Collection::writeFile(const char* path) {
    ofstream outputTxt;
    outputTxt.open(path);
    string line;
//    for (unsigned i = 0; i < movies.getElementCount(); ++i) {
//        if (movies.array[i]->getCategory() == OtherE) { // TODO: itt elég lenne movies[i]->getCategory() ha a datának van operator[] függvénye
//            outputTxt << movies.array[i]->getCategory() << ";" << movies.array[i]->getID() << ";" << movies.array[i]->getTitle() << ";" <<
//                      array[i]->getRunningTime() << ";" << array[i]->getReleaseYear() << endl;
//        }
//        else if (array[i]->getCategory() == FamilyE) {
//            Family* f = (Family*) array[i];
//            outputTxt << array[i]->getCategory() << ";" << array[i]->getID() << ";" << array[i]->getTitle() << ";" <<
//                      array[i]->getRunningTime() << ";" << array[i]->getReleaseYear() << ";" << f->getAgeRating() << endl;
//        }
//        else if (array[i]->getCategory() == DocumentaryE) {
//            Documentary* d = (Documentary*) array[i];
//            outputTxt << array[i]->getCategory() << ";" << array[i]->getID() << ";" << array[i]->getTitle() << ";" <<
//                      array[i]->getRunningTime() << ";" << array[i]->getReleaseYear() << ";" << d->getDescription() << endl;
//        }
//    }
//    outputTxt.close();
}

Collection& Collection::operator=(const Collection& rhs) {
    if (this != &rhs) {
        movies = rhs.movies;
    }
    return *this;
}

bool Collection::operator==(const Collection &rhs) {
    return &this->movies == &rhs.movies;
}


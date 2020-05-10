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
    cout << "ID\tCim\tHossz\tEv\tKategoria\tEgyeb" << endl; // TODO: hosszra formázás
    for (unsigned int i = 0; i < movies.getElementCount(); ++i) {
        movies[i]->print();
        cout << endl;
    }
}

/** Kiírja egy adott indexű film adatait */
void Collection::print(unsigned int index) {
    cout << "ID\tCim\tHossz\tMegjelenes eve\tKategoria\tEgyeb" << endl;
    movies[index]->print();
    cout << endl;
}

/** Keresés a filmek címei között
 *
 * @param keyword A keresendő kifejezés
 */
 // TODO: bővítés más tulajdonságokra is
 // TODO: hibakezelés + nincs találat
void Collection::search(const string& keyword) {
    bool result = false;
    for (unsigned int i = 0; i < movies.getElementCount(); ++i) {
        // std::string::find()
        size_t found = movies[i]->getTitle().find(keyword);
        if (found != -1) {
            if (!result)
                cout << "ID\tCim\tHossz\tMegjelenes eve\tKategoria\tEgyeb" << endl;
            movies[i]->print();
            result = true;
        }
    }
    if (!result)
        cout << "Nem talalhato a keresesi feltetelnek megfelelo cimu film a gyujtemenyben." << endl;
}

/** Az összes elem törlése */
void Collection::clearCollection() { // TODO
    // Hátulról indul, így nem kell minden egyes törlés után áthelyezni az elemeket
    for (unsigned int i = movies.getElementCount() - 1; i >= 0; --i) {
        movies.removeElement(i);
    }
}

/** Korábban létrehozott gyűjtemény betöltése fájlból
 *
 * @param path A fájl elérési útja
 */
void Collection::readFile(const char* path) {
    ifstream inputTxt;
    inputTxt.open(path); // TODO: hibakezelés
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
/** Az adott gyűjtemény mentése
 *
 * @param path A kimeneti fájl elérési útja
 */
void Collection::writeFile(const char* path) {
    ofstream outputTxt(path);
    for (unsigned i = 0; i < movies.getElementCount(); ++i) {
        movies[i]->print(outputTxt);
        outputTxt << endl;
    }
    outputTxt.close();
    // TODO: hibakezelés
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


//
// Created by Simon on 2020-04-17.
//

#include "collection.h"

Data<Movie>& Collection::getMovies() {
    return movies;
}

void Collection::add(Movie& mv) {
    mv.setID(movies.getElementCount());
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
    cout << endl;
}

/** Kiírja egy adott indexű film adatait */
void Collection::print(unsigned int index) {
    try {
        if (index > movies.getElementCount())
            throw std::out_of_range("A megadott indexu elem nem letezik.");
        cout << "ID\tCim\tHossz\tMegjelenes eve\tKategoria\tEgyeb" << endl;
        movies[index]->print();
        cout << endl;
    }
    catch (std::out_of_range& indexError) {
        cout << indexError.what() << endl;
    }
}

/** Keresés a filmek címei között
 *
 * @param keyword A keresendő kifejezés
 */
 // TODO: bővítés más tulajdonságokra is?
void Collection::search(const string& keyword) {
    bool result = false; // ha volt már találat, akkor true lesz
    for (unsigned int i = 0; i < movies.getElementCount(); ++i) {
        size_t found = movies[i]->getTitle().find(keyword);
        if (found != -1) {
            if (!result)
                cout << "Kereses - \"" << keyword << "\":\nID\tCim\tHossz\tMegjelenes eve\tKategoria\tEgyeb" << endl;
            movies[i]->print();
            cout << endl;
            result = true;
        }
    }
    if (!result)
        cout << "Nem talalhato a keresesi feltetelnek megfelelo cimu film a gyujtemenyben." << endl;
}

/** Az összes elem törlése */
void Collection::clearCollection() { // TODO: dtorral?
    // Hátulról indul, így nem kell minden egyes törlés után áthelyezni az elemeket
    // A 0. indexű elem elérése miatt >= 0 kell, de ha -1 lesz, az unsigned int átfordul, ezért ezt is ellenőrizni kell
    for (unsigned int i = movies.getElementCount() - 1; i >= 0 && i < -1; --i) {
        movies.removeElement(i, true);
    }
    cout << "Gyujtemeny torlese sikeres." << endl;
}

/** Korábban létrehozott gyűjtemény betöltése fájlból
 *
 * @param path A fájl elérési útja
 */
void Collection::readFile(const char* path) {
    try {
        ifstream inputTxt;
        inputTxt.open(path);
        if (!inputTxt) {
            throw std::ios_base::failure("Hiba a fajl megnyitasa soran");
        }
        string line;
        string split[5]; // A darabolt sort ebbe a tömbbe rakjuk

        while (!inputTxt.eof()) { // fájl végéig megy
            getline(inputTxt, line);
            istringstream oneLine(line);
            for (int i = 0; !oneLine.eof(); ++i) { // a beolvasott sor darabolása
                getline(oneLine, split[i], ';');
            }
            // stringek számmá alakítása
            unsigned runningTime = strtoul(split[2].c_str(), NULL, 10);
            unsigned releaseYear = strtoul(split[3].c_str(), NULL, 10);
            if (runningTime == 0 || releaseYear == 0) // ha nem sikerül a konverzió, a változó értéke 0 lesz
                cout << "Megjegyzes: Ervenytelen szamertek a fajlban. A serult adattag erteke 0-ra lett allitva. "
                        "Modositotta a kimeneti fajl tartalmat?" << endl;

            if (line[0] == '0') { // Family
                Rating rating = (Rating) atoi(split[4].c_str());
                Family* fmv = new Family(split[1], runningTime, releaseYear, rating);
                this->add(*fmv);
            } else if (line[0] == '1') { // Documentary
                Documentary* dmv = new Documentary(split[1], runningTime, releaseYear,split[4]);
                this->add(*dmv);
            } else if (line[0] == '2') { // Other
                Movie* omv = new Movie(split[1], runningTime, releaseYear);
                this->add(*omv);
            }
        }
        inputTxt.close();
    }
    catch (std::ios_base::failure& ioerror) {
        cout << ioerror.what() << endl;
    }
}
/** Az adott gyűjtemény mentése
 *
 * @param path A kimeneti fájl elérési útja
 */
void Collection::writeFile(const char* path) {
    try {
        ofstream outputTxt(path);
        if (!outputTxt)
            throw ios_base::failure("A fajlba iras sikertelen");
        for (unsigned i = 0; i < movies.getElementCount(); ++i) {
            movies[i]->print(outputTxt);
            outputTxt << endl;
        }
        outputTxt.close();
    }
    catch (ios_base::failure& ioerror) {
        cout << ioerror.what() << endl;
    }
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


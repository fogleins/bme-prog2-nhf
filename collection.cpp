//
// Created by Simon on 2020-04-17.
//

#include "collection.h"

/** Elem felvétele a gyűjteménybe
 *
 * @param mv A felveendő objektum
 */
void Collection::add(Movie& mv) {
    try {
        bool duplicate = false;
        for (unsigned int i = 0; i < movies.getElementCount(); ++i) {
            if (*movies[i] == mv) {
                cerr << "Ezt a filmet mar hozzaadta a gyujtemenyhez, igy most nem lesz hozzaadva." << endl;
                duplicate = true;
                break;
            }
        }
        if (!duplicate) {
            mv.setID(movies.getElementCount());
            movies.addElement(mv);
        }
    }
    catch (bad_alloc& e) {
        cerr << "A memoriafoglalas nem sikerult: " << e.what() << endl;
    }
}

/** Elem felvétele a gyűjteménybe
 *
 * @param mv A felveendő objektumra mutató pointer
 */
void Collection::add(Movie *mv) {
    add(*mv);
}

/** Elem törlése a gyűjteményből
 *
 * @param index A törlendő elem indexe
 */
void Collection::remove(unsigned int index) {
    try {
        movies.removeElement(index);
    }
    catch (out_of_range& indexError) {
        cerr << indexError.what() << endl;
    }
    catch (runtime_error& runtimeError) {
        cerr << runtimeError.what() << endl;
    }
    catch (bad_alloc& memError) {
        cerr << "A memoriafoglalas nem sikerult: " << memError.what() << endl;
    }
}

/** Kilistázza az összes filmet és azok adatait a konzolra
 *
 * @param os Az az ostream, amire az eredményt írjuk
 */
void Collection::print(ostream& os) {
    os << "ID\tCim\tHossz\tEv\tKategoria\tEgyeb" << endl;
    for (unsigned int i = 0; i < movies.getElementCount(); ++i) {
        movies[i]->print();
        os << endl;
    }
    os << endl;
}

/** Kiírja egy adott indexű film adatait a konzolra
 *
 * @param index A kiírandó elem indexere
 */
void Collection::print(unsigned int index) {
    try {
        if (index > movies.getElementCount())
            throw std::out_of_range("A megadott indexu elem nem letezik.");
        cout << "ID\tCim\tHossz\tMegjelenes eve\tKategoria\tEgyeb" << endl;
        movies[index]->print();
        cout << endl;
    }
    catch (std::out_of_range& indexError) {
        cerr << indexError.what() << endl;
    }
}

/** Keresés a filmek címei között
 *
 * @param keyword A keresendő kifejezés
 */
void Collection::search(const string& keyword, ostream& os) {
    bool result = false; // ha volt már találat, akkor true lesz
    for (unsigned int i = 0; i < movies.getElementCount(); ++i) {
        size_t found = movies[i]->getTitle().find(keyword);
        if (found != (unsigned) -1) {
            if (!result)
                os << "Kereses - \"" << keyword << "\":\nID\tCim\tHossz\tMegjelenes eve\tKategoria\tEgyeb" << endl;
            movies[i]->print(os);
            os << endl;
            result = true;
        }
    }
    if (!result)
        cerr << "Nem talalhato a keresesi feltetelnek megfelelo cimu film a gyujtemenyben." << endl;
}

/** Az összes elem törlése a gyűjteményből */
void Collection::clear() { // TODO: dtorral?
    try {
        // Hátulról indul, így nem kell minden egyes törlés után áthelyezni az elemeket
        // A 0. indexű elem elérése miatt >= 0 kell, de ha -1 lesz, az unsigned int átfordul, ezért ezt is ellenőrizni kell
        for (unsigned int i = movies.getElementCount() - 1; i >= 0 && i < (unsigned) -1; --i) {
            movies.removeElement(i);
        }
        cerr << "Gyujtemeny torlese sikeres." << endl;
    }
    catch (out_of_range& indexError) {
        cerr << indexError.what() << endl;
    }
    catch (bad_alloc& memError) {
        cerr << "A memoriafoglalas nem sikerult: " << memError.what() << endl;
    }
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
            throw ios_base::failure("Hiba a fajl megnyitasa soran");
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
                cerr << "Megjegyzes: Ervenytelen szamertek a fajlban. A serult adattag erteke 0-ra lett allitva. "
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
    catch (ios_base::failure& ioerror) {
        cerr << ioerror.what() << endl;
    }
}

/** Az adott gyűjtemény mentése fájlba
 *
 * @param path A kimeneti fájl elérési útja
 */
void Collection::writeFile(const char* path) {
    try {
        ofstream outputTxt(path);
        if (!outputTxt)
            throw ios_base::failure("A fajlba iras sikertelen");
        for (unsigned i = 0; i < movies.getElementCount(); ++i) {
            movies[i]->print(outputTxt, true);
            outputTxt << endl;
        }
        outputTxt.close();
    }
    catch (ios_base::failure& ioerror) {
        cerr << ioerror.what() << endl;
    }
}


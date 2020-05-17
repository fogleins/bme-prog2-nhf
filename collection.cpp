//
// Created by Simon on 2020-04-17.
//

#include "collection.h"

using std::string;
using std::cout;
using std::cerr;
using std::endl;

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
    catch (std::bad_alloc& e) {
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
    catch (std::out_of_range& indexError) {
        cerr << indexError.what() << endl;
    }
    catch (std::runtime_error& runtimeError) {
        cerr << runtimeError.what() << endl;
    }
    catch (std::bad_alloc& memError) {
        cerr << "A memoriafoglalas nem sikerult: " << memError.what() << endl;
    }
}

/** Kilistázza az összes filmet és azok adatait a konzolra
 *
 * @param os Az az ostream, amire az eredményt írjuk
 */
void Collection::print(std::ostream& os) {
    os << "ID\tCim\tHossz\tEv\tKategoria\tEgyeb" << endl;
    for (unsigned int i = 0; i < movies.getElementCount(); ++i) {
        movies[i]->print(os);
        os << endl;
    }
    os << endl;
}

/** Kiírja egy adott indexű film adatait a konzolra
 *
 * @param index A kiírandó elem indexere
 */
void Collection::print(unsigned int index, std::ostream& os) {
    try {
        if (index > movies.getElementCount())
            throw std::out_of_range("A megadott indexu elem nem letezik.");
        os << "ID\tCim\tHossz\tMegjelenes eve\tKategoria\tEgyeb" << endl;
        movies[index]->print(os);
        os << endl;
    }
    catch (std::out_of_range& indexError) {
        os << indexError.what() << endl;
    }
}

/** Keresés a filmek címei között
 *
 * @param keyword A keresendő kifejezés
 * @param os Az ostream, amire a kimenetet írjuk
 */
void Collection::search(const string& keyword, std::ostream& os) {
    bool result = false; // ha volt már találat, akkor true lesz
    for (unsigned int i = 0; i < movies.getElementCount(); ++i) {
        string title = movies[i]->getTitle();
        size_t found = title.find(keyword);
        if (found >= unsigned(0) && found < title.length()) {
            if (!result)
                os << "Kereses - \"" << keyword << "\":\nID\tCim\tHossz\tMegjelenes eve\tKategoria\tEgyeb" << endl;
            movies[i]->print(os);
            os << endl;
            result = true;
        }
    }
    if (!result)
        os << "Nem talalhato a keresesi feltetelnek megfelelo cimu film a gyujtemenyben." << endl;
}

/** Az összes elem törlése a gyűjteményből */
void Collection::clear() {
    try {
        movies = Data<Movie>(); // új, 0 elemű Data-t kap
        cout << "Gyujtemeny torlese sikeres." << endl;
    }
    catch (std::bad_alloc& memError) {
        cerr << "A memoriafoglalas nem sikerult: " << memError.what() << endl;
    }
}

/** Korábban létrehozott gyűjtemény betöltése fájlból
 *
 * @param path A fájl elérési útja
 */
void Collection::readFile(const char* path) {
    try {
        std::ifstream inputTxt;
        inputTxt.open(path);
        if (!inputTxt) {
            throw std::ios_base::failure("Hiba a fajl megnyitasa soran");
        }
        string line;
        string split[5]; // A darabolt sort ebbe a tömbbe rakjuk

        while (!inputTxt.eof()) { // fájl végéig megy
            getline(inputTxt, line);
            std::istringstream oneLine(line);
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
    catch (std::ios_base::failure& ioerror) {
        cerr << ioerror.what() << endl;
    }
}

/** Az adott gyűjtemény mentése fájlba
 *
 * @param path A kimeneti fájl elérési útja
 */
void Collection::writeFile(const char* path) {
    try {
        std::ofstream outputTxt(path);
        if (!outputTxt)
            throw std::ios_base::failure("A fajlba iras sikertelen");
        for (unsigned i = 0; i < movies.getElementCount(); ++i) {
            movies[i]->print(outputTxt, true);
            outputTxt << endl;
        }
        outputTxt.close();
    }
    catch (std::ios_base::failure& ioerror) {
        cerr << ioerror.what() << endl;
    }
}


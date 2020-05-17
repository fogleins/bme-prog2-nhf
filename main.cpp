#include <iostream>
#include <ctime>

#include "movie.h"
#include "family.h"
#include "documentary.h"
#include "collection.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stringstream;

// JPORTÁN VALÓ FUTTATÁSHOZ DEFINIÁLNI KELL
// a konzolos inputhoz és a felhaszálói oldalról
// való teszteléshez definiálatlannak kell lennie
//#define JPORTA

#ifdef JPORTA
#include "gtest_lite.h"
#include "memtrace.h"
#endif

#ifndef JPORTA
void add(Collection& coll, bool& exit);
string getCurrentTime();
bool containsAccentedChar(const char* str);
#endif

int main() {
#ifdef JPORTA // tesztesetek
    // konstruktorok teszelése
    TEST(movies, ctors) {
        stringstream t1, t2, t3, pnelkul;
        Movie* movie = new Movie("1917", 119, 2019);
        Family* family = new Family("Frozen 2", 103, 2019, ages6AndUp);
        Documentary* documentary = new Documentary("Free solo", 97, 2018, "Professional rock climber "
                                                   "Alex Honnold attempts to conquer the first free solo climb of "
                                                   "famed El Capitan's 900-metre vertical rock face at Yosemite "
                                                   "National Park.");
        // paraméter nélküli ctor
        Documentary paramnelkul;
        paramnelkul.print(pnelkul, true);
        EXPECT_STREQ("1;;0;0;", pnelkul.str().c_str());
        // copy ctor
        Movie copy = *movie;
        EXPECT_EQ(movie->getReleaseYear(), copy.getReleaseYear());
        // ha nincs gyűjteményhez adva, az id 0
        movie->print(t1);
        family->print(t2);
        documentary->print(t3);
        EXPECT_STREQ("0\t1917\t119 perc\t2019\tMovie", t1.str().c_str());
        EXPECT_STREQ("0\tFrozen 2\t103 perc\t2019\tFamily\tKorhatar-besorolas: 6", t2.str().c_str());
        EXPECT_STREQ("0\tFree solo\t97 perc\t2018\tDocumentary\tLeiras: Professional rock climber Alex Honnold "
                     "attempts to conquer the first free solo climb of famed El Capitan's 900-metre vertical rock face "
                     "at Yosemite National Park.", t3.str().c_str());
        delete movie;
        delete family;
        delete documentary;
    } ENDM

    // a gyűjtemény teszteléséhez ezeket használjuk
    Collection tcoll;
    Movie* tmovie = new Movie("1917", 119, 2019);
    Family* tfamily = new Family("Frozen 2", 103, 2019, ages6AndUp);
    Documentary* tdocumentary = new Documentary("Free solo", 97, 2018, "Professional rock climber "
                                                                       "Alex Honnold attempts to conquer the first free solo climb of "
                                                                       "famed El Capitan's 900-metre vertical rock face at Yosemite "
                                                                       "National Park.");
    // üres gyűjtemény kiírása
    TEST(collection, printEmpty) {
        EXPECT_EQ(unsigned(0) , tcoll.getMovies().getElementCount());
        stringstream ss;
        tcoll.print(ss);
        EXPECT_STREQ("ID\tCim\tHossz\tEv\tKategoria\tEgyeb\n\n", ss.str().c_str());
    } ENDM

    // gyűjteményhez adás és kiírás
    TEST(collection, add) {
        stringstream tfamilyss, tmoviess;
        // gyűjteményhez adjuk, hogy kapjon id-t
        tcoll.add(tdocumentary);
        tcoll.add(*tfamily); // referenciával is lehet
        tcoll.add(tmovie);
        tfamily->print(tfamilyss);
        tmovie->print(tmoviess);
        EXPECT_STREQ("1\tFrozen 2\t103 perc\t2019\tFamily\tKorhatar-besorolas: 6", tfamilyss.str().c_str());
        EXPECT_STREQ("2\t1917\t119 perc\t2019\tMovie", tmoviess.str().c_str());
    } ENDM

    TEST(collection, printNotEmpty) {
        stringstream ss;
        tcoll.print(ss);
        EXPECT_STREQ("ID\tCim\tHossz\tEv\tKategoria\tEgyeb\n0\tFree solo\t97 perc\t2018\tDocumentary\tLeiras: "
                     "Professional rock climber Alex Honnold attempts to conquer the first free solo climb of famed "
                     "El Capitan's 900-metre vertical rock face at Yosemite National Park.\n1\tFrozen 2\t103 perc\t2019"
                     "\tFamily\tKorhatar-besorolas: 6\n2\t1917\t119 perc\t2019\tMovie\n\n", ss.str().c_str());
    } ENDM

    TEST(collection, checkDuplicate) {
        // Ha azonos tulajdonságú filmet próbálunk hozzáadni a gyűjteményhez, akkor azt a duplikációk elkerülése
        // érdekében nem adja hozzá, így a hozzáadás előtti-utáni elemszám megegyezik
        EXPECT_EQ(unsigned(3), tcoll.getMovies().getElementCount());
        Documentary* mv3copy = tdocumentary;
        tcoll.add(mv3copy);
        EXPECT_EQ(unsigned(3), tcoll.getMovies().getElementCount());
    } ENDM

    TEST(collection, removeElement) {
        tcoll.remove(0);
        EXPECT_EQ(unsigned(2), tcoll.getMovies().getElementCount());
        // ez a foglalt memóriaterületet is felszabadítja, így itt már nem kell felszabadítani
        // a fent foglalt objektumok által foglalt memóriát
    } ENDM

    // a teljes gyűjtemény törlése
    TEST(collection, clear) {
        EXPECT_EQ(unsigned(2), tcoll.getMovies().getElementCount());
        tcoll.clear();
        EXPECT_EQ(unsigned (0), tcoll.getMovies().getElementCount());
    } ENDM

    // a filmek operator= és operator== függvényeinek tesztelése
    TEST(movies, operators) {
        Movie* movie = new Movie("1917", 119, 2019);
        Family* family = new Family("Frozen 2", 103, 2019, ages6AndUp);
        Documentary* documentary = new Documentary("Free solo", 97, 2018, "Professional rock climber "
                                                   "Alex Honnold attempts to conquer the first free solo climb of "
                                                   "famed El Capitan's 900-metre vertical rock face at Yosemite "
                                                   "National Park.");
        Movie movieCopy;
        movieCopy = *movie;
        Family familyCopy;
        familyCopy = *family;
        Documentary docCopy;
        docCopy= *documentary;

        EXPECT_EQ(false, *movie == *family);
        EXPECT_EQ(false, *documentary == *movie);
        EXPECT_EQ(false, *movie == *documentary);
        EXPECT_EQ(false, documentary == &docCopy); // deep copyt csinál
        EXPECT_EQ(true, *movie == movieCopy);
        EXPECT_EQ(true, *family == familyCopy);
        EXPECT_EQ(true, *documentary == docCopy);
        delete movie;
        delete family;
        delete documentary;
    } ENDM

    // a dobott kivételeket teszteli
    TEST(collection, exceptions) {
        Movie* movie = new Movie("1917", 119, 2019);
        Family* family = new Family("Frozen 2", 103, 2019, ages6AndUp);
        Documentary* documentary = new Documentary("Free solo", 97, 2018, "Professional rock climber "
                                                   "Alex Honnold attempts to conquer the first free solo climb of "
                                                   "famed El Capitan's 900-metre vertical rock face at Yosemite "
                                                   "National Park.");
        // gyűjtemény feltöltése
        Collection coll;
        coll.add(movie);
        coll.add(family);
        coll.add(documentary);
        EXPECT_EQ(unsigned(3) , coll.getMovies().getElementCount());

        // indexelő operátor tesztelése
        EXPECT_EQ(unsigned (119), coll.getMovies()[0]->getRunningTime());
        EXPECT_ANY_THROW(coll.getMovies()[15]); // túlindexelés
        EXPECT_ANY_THROW(coll.getMovies()[-15]); // túlindexelés
        EXPECT_NO_THROW(coll.getMovies()[2]);
        // törlés
        EXPECT_ANY_THROW(coll.getMovies().removeElement(5)); // túlindexelés
        EXPECT_NO_THROW(coll.getMovies().removeElement(2));
        // documentary-t kitöröltük, így nem található a gyűjteményben
        EXPECT_ANY_THROW(coll.getMovies().removeElement(*documentary));
    } ENDM

    // keresés a gyűjteményben
    TEST(collection, search) {
        Collection coll;
        stringstream ss1, ss2, ss3;
        Movie* mv1 = new Movie("1917", 119, 2019);
        Family* mv2 = new Family("Frozen 2", 103, 2019, ages6AndUp);
        Documentary* mv3 = new Documentary("Free solo", 97, 2018, "Alex Honnold attempts to conquer "
                                               "the first free solo climb of El Capitan's 900-metre vertical rock face.");
        coll.add(mv1);
        coll.add(mv2);
        coll.add(mv3);
        coll.search("oze", ss1);
        EXPECT_STREQ("Kereses - \"oze\":\nID\tCim\tHossz\tMegjelenes eve\tKategoria\tEgyeb\n1\tFrozen 2\t"
                     "103 perc\t2019\tFamily\tKorhatar-besorolas: 6\n", ss1.str().c_str());
        // Több találat esetén minden találatot kiír
        coll.search("e", ss2);
        EXPECT_STREQ("Kereses - \"e\":\nID\tCim\tHossz\tMegjelenes eve\tKategoria\tEgyeb\n1\tFrozen 2\t"
                     "103 perc\t2019\tFamily\tKorhatar-besorolas: 6\n2\tFree solo\t97 perc\t2018\tDocumentary\tLeiras: "
                     "Alex Honnold attempts to conquer the first free solo climb of El Capitan's 900-metre vertical "
                     "rock face.\n",ss2.str().c_str());
        coll.search("nem talalhato", ss3);
        EXPECT_STREQ("Nem talalhato a keresesi feltetelnek megfelelo cimu film a gyujtemenyben.\n",
                ss3.str().c_str());
    } ENDM

    // fájlbeolvasás tesztelése
    TEST(collection, readFile) {
        Collection coll;
        // ha nem létező fájlt próbálunk megnyitni, a dobott kivételt lekezeli
        EXPECT_NO_THROW(coll.readFile("ilyenFajlNincs.csv"));
        coll.readFile("./teszt.csv");
        Family* familymv = (Family*) coll.getMovies()[1];
        EXPECT_EQ(12, familymv->getAgeRating());
        stringstream ss;
        Documentary* docmv = (Documentary*) coll.getMovies()[2];
        EXPECT_STREQ("Dokumentumfilm leirasa", docmv->getDescription().c_str());
        docmv->print(ss);
        EXPECT_STREQ("2\tDokumentumfilm\t86 perc\t2013\tDocumentary\tLeiras: Dokumentumfilm leirasa",
                ss.str().c_str());
    } ENDM

    // gyűjtemény kiírása
    TEST(collection, writeFile) {
        Collection coll, coll2;
        Movie* mv = new Movie("Cim", 25, 2020);
        coll.add(mv);
        coll.writeFile("kiiras.csv");
        // visszaolvassuk a teszteléshez
        stringstream ss;
        coll2.readFile("kiiras.csv");
        coll2.print(0, ss);
        EXPECT_STREQ("ID\tCim\tHossz\tMegjelenes eve\tKategoria\tEgyeb\n0\tCim\t25 perc\t2020\tMovie\n",
                ss.str().c_str());
    } ENDM
#endif

#ifndef JPORTA
    bool exit = false;
    Collection coll;
    cout << "Parancsok listazasahoz: sugo" << endl;
    string command;
    while (!exit) {
        command = "";
        cout << "Parancs: ";
        // üres string esetén újból beolvassuk, EOF esetén kilépünk a programból
        while (command.empty()) {
            getline(cin, command);
            if ((exit = cin.eof())) { break; }
        }

        // film felvétele
        if (command.find("uj") == 0) {
            add(coll, exit);
            if (exit)
                break;
        }
        else if (command.find("keres") == 0) {
            if (command.length() <= 6)
                cout << "A parancs utan adja meg a keresett kifejezest is!" << endl;
            else {
                string kw = command.substr(6);
                coll.search(kw);
            }
        }
        // beolvasás fájlból
        else if (command.find('p') == 0) {
            if (command.length() <= 2)
                cout << "A parancs utan adja meg a fajl eleresi utjat is!" << endl;
            else {
                string path = command.substr(2);
                // különleges karaktereket tartalmazó elérési út esetén
                // hibaüzenetet adunk és nem olvassuk be a fájlt
                if (!containsAccentedChar(path.c_str()))
                    coll.readFile(path.c_str());
            }
        }
        else if (command == "ls") {
            coll.print();
        }
        else if (command.find("rm") == 0) {
            if (command.length() >= 4) { // ha nem adott meg id-t
                string quit;
                unsigned int id = strtoul(command.substr(3).c_str(), NULL, 10);
                // érvénytelen karakter esetén az strtoul() 0-t ad
                if (id == 0) {
                    cout << "Lehetseges, hogy nem megfelelo azonositot adott meg. Erositse meg, hogy valoban az elso, "
                            "0 azonositoju filmet szeretne torolni. Minden nem \"igen\" valasz nem-nek szamit. (igen/nem): "
                         << endl;
                    cin >> quit;
                    if (quit.find("igen") != unsigned(-1))
                        coll.remove(id);
                } else coll.remove(id);
            }
            else
                cout << "Adja meg a torlendo film azonositojat!" << endl;
        }
        else if (command == "rst") {
            string confirm;
            cout << "A nem mentett modositasok elvesznek, ha nem menti a gyujtemenyt." << endl;
            while ((confirm.find("igen") != 0 && confirm.find("nem") != 0)) {
                cout << "Biztosan torli a gyujtemenyt? (igen/nem): ";
                cin >> confirm;
                if (confirm.find("igen") == 0)
                    coll.clear();
            }
        }
        else if (command == "ment") {
            coll.writeFile(getCurrentTime().c_str());
        }
        else if (command == "sugo") {
            cout << "Elerheto parancsok:\n\tuj:\tuj film felvetele a gyujtemenybe\n\tkeres:\tkereses filmek cimere "
                    "a gyujtemenyben\n\tp:\tgyujtemeny beolvasasa fajlbol\n\tls:\ta tarolt filmek kilistazasa\n\trm:"
                    "\tmegadott azonositoju film torlese a gyujtemenybol\n\trst:\tminden film torlese a gyujtemenybol"
                    "\n\tment:\tfajlba irja a jelenlegi gyujtemenyt\n\tkilep:\tkilep a programbol" << endl;
        }
        else if (command == "kilep") {
            string confirm;
            cout << "A nem mentett modositasok elvesznek, ha nem menti a gyujtemenyt." << endl;
            while ((confirm.find("igen") != 0 && confirm.find("nem") != 0) && !exit) {
                cout << "Biztosan ki szeretne lepni? (igen/nem): ";
                cin >> confirm;
                if (confirm.find("igen") == 0)
                    exit = true;
            }
        }
        else {
            cout << "Hibas parancs" << endl;
        }
    }
    cout << "\nBezarhatja a programot." << endl;
#endif

    return 0;
}

#ifndef JPORTA
/** Film felvétele a gyűjteménybe a konzolon megadott adatokból
 *
 * @param coll A gyűjtemény, amibe felvesszük a filmet
 * @param exit A kilépést jelző bool, amit igazra állít,
 * ha film hozzáadása során a felhasználó ki szeretne lépni
 */
void add(Collection& coll, bool& exit) {
    cout << "Adja meg a kivant tipust: 1 - Normal film, 2 - Csaladi film, 3 - Dokumentumfilm: ";
    string categorystr;
    int category = 0;

    while (category < 1 || category > 3) {
        cin >> categorystr;
        category = atoi(categorystr.c_str());
        if (category < 1 || category > 3)
            cout << "Ervenytelen tipus." << endl;
    }
    string split[4];
    cout << "A film cime: ";
    // üres string és ékezetes string nem elfogadott, EOF esetén kilépünk
    while (split[0].empty() || containsAccentedChar(split[0].c_str())) {
        getline(cin, split[0]);
        if ((exit = cin.eof())) { return; }
    }

    cout << "Hossza percben: ";
    if ((exit = cout.eof())) { return; }
    cin >> split[1];
    cout << "Kiadasi eve: ";
    if ((exit = cout.eof())) { return; }
    cin >> split[2];
    unsigned int runningTime = strtoul(split[1].c_str(), NULL, 10);
    unsigned int releaseYear = strtoul(split[2].c_str(), NULL, 10);
    if (runningTime == 0 || releaseYear == 0) {
        cout << "Hibas bemenet. A megadott adatokat nem lehetett szamma alakitani. Probalja ujra." << endl;
        category = -1;
    }

    switch (category) {
        case 1: {
            Movie* mv = new Movie(split[0], runningTime, releaseYear);
            coll.add(mv);
            break;
        }
        case 2: {
            int ageRating;
            cout << "Korhatar-besorolasa: ";
            cin >> ageRating;
            Rating rating = Rating(ageRating);
            // érvénytelen besorlás kezelése
            if (rating != unrated && rating != ages6AndUp && rating != ages12AndUp &&
                rating != ages16AndUp && rating != ages18AndUp && rating != allAges) {
                cout << "Ervenytelen besorolas-kategoria. A film korhatara \"nem minositett\" lesz." << endl;
                rating = unrated;
            }
            Family *mv = new Family(split[0], runningTime, releaseYear, rating);
            coll.add(mv);
            break;
        }
        case 3: {
            cout << "Leirasa: ";
            // üres string nem elfogadott, EOF-nál kilépünk
            while (split[3].empty()) {
                getline(cin, split[3]);
                if ((exit = cin.eof())) { return; }
            }
            Documentary* mv = new Documentary(split[0], runningTime, releaseYear, split[3]);
            coll.add(mv);
        }
        // érvénytelen filmtípus megadása esetén
        default:
            break;
    }
}

/** Egyedi fájlnév létrehozása mentéshez
 *
 * @return A jelenlegi időpontot tartalmazó fájlnév
 */
string getCurrentTime() {
    char s[20];
    time_t t = time(NULL);
    struct tm local = *localtime(&t);
    sprintf(s, "%d%02d%02d-%02d%02d%02d.csv", local.tm_year + 1900, local.tm_mon + 1, local.tm_mday,
            local.tm_hour, local.tm_min, local.tm_sec);
    string currTime = "collection-";
    currTime += s;
    return currTime;
}

/** Megvizsgálja, hogy egy bemenet érvényes-e, azaz nem tartalmaz meg nem engedett karaktereket
 *
 * @param str A karakterlánc, amit vizsgálunk
 * @return Igaz, ha a string tartalmaz meg nem engedett karaktert, egyébként hamis
 */
bool containsAccentedChar(const char* str) {
    for (int i = 0; str[i] != '\0' ; ++i) {
        if (str[i] < 32 || str[i] > 122) {
            cout << "A megadott bemenet ervenytelen karakter(eke)t tartalmaz." << endl;
            return true;
        }
    }
    return false;
}

#endif

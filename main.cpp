#include <iostream>
#include <ctime>

#include "gtest_lite.h"
#include "memtrace.h"

#include "movie.h"
#include "family.h"
#include "documentary.h"
#include "collection.h"

// JPORTÁN VALÓ FUTTATÁSHOZ DEFINIÁLNI KELL
// a konzolos inputhoz és a felhaszálói oldalról
// való teszteléshez definiálatlannak kell lennie
#define JPORTA

#ifndef JPORTA
void add(Collection& coll);
string getCurrentTime();
bool containsAccentedChar(const char* str);
#endif

int main() {
#ifdef JPORTA // tesztesetek
    // fájlba és konzolra írás tesztelése mindegyik filmtípuson
    TEST(movies, ctors) {
        stringstream t1, t2, t3;
        Movie* test1mv = new Movie("1917", 119, 2019);
        Family* test2mv = new Family("Frozen 2", 103, 2019, ages6AndUp);
        Documentary* test3mv = new Documentary("Free solo", 97, 2018, "Professional rock climber "
                                                   "Alex Honnold attempts to conquer the first free solo climb of "
                                                   "famed El Capitan's 900-metre vertical rock face at Yosemite "
                                                   "National Park.");
        // copy ctor
        Movie test1copy = *test1mv;
        Movie test2copy = *test2mv; /* TODO */
        EXPECT_EQ(test1mv->getReleaseYear(), test1copy.getReleaseYear());
        // konzolra írás függvényének tesztelése
        test1mv->print(t1);
        // az id inicializálatlan (unsigned -1 = 4294967295)
        EXPECT_STREQ("0\t1917\t119 perc\t2019\tMovie", t1.str().c_str());

        // gyűjteményhez adjuk, hogy kapjon id-t
        Collection coll;
        coll.add(test2mv);
        test2mv->print(t2);
        EXPECT_STREQ("0\tFrozen 2\t103 perc\t2019\tFamily\tKorhatar-besorolas: 6", t2.str().c_str());

        // fájlba írás
        test3mv->print(t3, true);
        EXPECT_STREQ("1;Free solo;97;2018;Professional rock climber Alex Honnold attempts to conquer the "
                     "first free solo climb of famed El Capitan's 900-metre vertical rock face at "
                     "Yosemite National Park.", t3.str().c_str());
        delete test1mv; // test2mv gyűjteményhez lett adva, azt a dtor felszabadítja
        delete test3mv;
    } ENDM

    // TODO: split?
    // gyűjteményhez adás és kiírás
    TEST(collection, addAndPrint) {
        Movie* test1mv = new Movie("1917", 119, 2019);
        Family* test2mv = new Family("Frozen 2", 103, 2019, ages6AndUp);
        Documentary* test3mv = new Documentary("Free solo", 97, 2018, "Professional rock climber "
                                                   "Alex Honnold attempts to conquer the first free solo climb of "
                                                   "famed El Capitan's 900-metre vertical rock face at Yosemite "
                                                   "National Park.");
        Collection coll;
        stringstream ss;
        coll.print(ss); // üres gyűjtemény kiírása
        EXPECT_EQ((unsigned) 0, coll.getMovies().getElementCount());
        EXPECT_STREQ("ID\tCim\tHossz\tEv\tKategoria\tEgyeb\n\n", ss.str().c_str());

        // filmek gyűjteményhez adása pointerrel és referenciával
        coll.add(test1mv);
        coll.add(test2mv);
        coll.add(*test3mv);
        EXPECT_EQ((unsigned) 3, coll.getMovies().getElementCount());

        stringstream t1, t2, t3;
        test1mv->print(t1);
        EXPECT_STREQ("0\t1917\t119 perc\t2019\tMovie", t1.str().c_str());
        test2mv->print(t2);
        EXPECT_STREQ("1\tFrozen 2\t103 perc\t2019\tFamily\tKorhatar-besorolas: 6", t2.str().c_str());
        // fájlba író mód
        test3mv->print(t3, true);
        EXPECT_STREQ("1;Free solo;97;2018;Professional rock climber Alex Honnold attempts to conquer the "
                     "first free solo climb of famed El Capitan's 900-metre vertical rock face at "
                     "Yosemite National Park.", t3.str().c_str());

        // Ha azonos tulajdonságú filmet próbálunk hozzáadni a gyűjteményhez, akkor azt a duplikációk elkerülése
        // érdekében nem adja hozzá, így a hozzáadás előtti-utáni elemszám megegyezik
        EXPECT_EQ((unsigned) 3, coll.getMovies().getElementCount());
        Documentary* mv3copy = test3mv;
        coll.add(mv3copy);
        EXPECT_EQ((unsigned) 3, coll.getMovies().getElementCount());
        // objektumok által foglalt memóriát a gyűjtemény szabadítja fel
    } ENDM

    // TODO: operátortesztelés ok
    // a filmek operator= és operator== függvényeinek tesztelése
    TEST(movies, operators) {
        Movie* test1mv = new Movie("1917", 119, 2019);
        Family* test2mv = new Family("Frozen 2", 103, 2019, ages6AndUp);
        Documentary* test3mv = new Documentary("Free solo", 97, 2018, "Professional rock climber "
                                                   "Alex Honnold attempts to conquer the first free solo climb of "
                                                   "famed El Capitan's 900-metre vertical rock face at Yosemite "
                                                   "National Park.");
        Movie* test1copy = test1mv;
        Family test2copy = *test2mv;
        Documentary test3copy = *test3mv;

        EXPECT_EQ(false, *test1mv == *test2mv);
        EXPECT_EQ(false, *test3mv == *test1mv);
        EXPECT_EQ(false, *test1mv == *test3mv);
        EXPECT_EQ(false, test3mv == &test3copy); // deep copyt csinál
        EXPECT_EQ(true, *test1mv == *test1copy);
        EXPECT_EQ(true, *test2mv == test2copy);
        EXPECT_EQ(true, *test3mv == test3copy);
        delete test1mv;
        delete test2mv;
        delete test3mv;
    } ENDM

    // TODO: nagyjából ok
    // a dobott kivételeket teszteli
    TEST(collection, exceptions) {
        Movie* test1mv = new Movie("1917", 119, 2019);
        Family* test2mv = new Family("Frozen 2", 103, 2019, ages6AndUp);
        Documentary* test3mv = new Documentary("Free solo", 97, 2018, "Professional rock climber "
                                                   "Alex Honnold attempts to conquer the first free solo climb of "
                                                   "famed El Capitan's 900-metre vertical rock face at Yosemite "
                                                   "National Park.");
        // gyűjtemény feltöltése
        Collection coll;
        coll.add(test1mv);
        coll.add(test2mv);
        coll.add(test3mv);

        // indexelő operátor tesztelése
        EXPECT_EQ((unsigned) 3, coll.getMovies().getElementCount());
        EXPECT_EQ((unsigned) 119, coll.getMovies()[0]->getRunningTime());
        EXPECT_ANY_THROW(coll.getMovies()[15]); // túlindexelés
        EXPECT_NO_THROW(coll.getMovies()[2]);
        // törlés
        EXPECT_ANY_THROW(coll.getMovies().removeElement(5)); // túlindexelés
        EXPECT_NO_THROW(coll.getMovies().removeElement(2));
        // a teljes gyűjtemény törlése
        EXPECT_EQ((unsigned) 2, coll.getMovies().getElementCount());
        coll.clear();
        EXPECT_EQ((unsigned) 0, coll.getMovies().getElementCount());
    } ENDM

    // TODO: ok
    // keresés a gyűjteményben
    TEST(collection, search) {
        Collection coll;
        stringstream ss1, ss2;
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
    } ENDM

    // TODO: ok
    TEST(collection, readFile) {
        Collection coll;
        coll.readFile("./teszt.txt");
        Family* familymv = (Family*) coll.getMovies()[1];
        EXPECT_EQ(12, familymv->getAgeRating());
        stringstream ss;
        Documentary* docmv = (Documentary*) coll.getMovies()[2];
        EXPECT_STREQ("Dokumentumfilm leirasa", docmv->getDescription().c_str());
        docmv->print(ss);
        EXPECT_STREQ("2\tDokumentumfilm\t86 perc\t2013\tDocumentary\tLeiras: Dokumentumfilm leirasa",
                ss.str().c_str());
    } ENDM
#endif

#ifndef JPORTA
    bool exit = false;
    Collection coll;
    cout << "Parancsok listazasahoz: sugo" << endl;
    string command;
    while (!exit) {
        cout << "Parancs: ";
        while (command.empty()) // üres string esetén újból beolvassuk
            getline(cin, command);

        // film felvétele
        if (command.find("uj") == 0) {
            add(coll);
        }
        else if (command.find("keres") == 0) {
            string kw = command.substr(6);
            coll.search(kw);
        }
        // beolvasás fájlból
        else if (command.find('p') == 0) {
            string path = command.substr(2);
            // különleges karaktereket tartalmazó elérési út esetén
            // hibaüzenetet adunk és nem olvassuk be a fájlt
            if (!containsAccentedChar(path.c_str()))
                coll.readFile(path.c_str());
        }
        else if (command == "ls") {
            coll.print();
        }
        else if (command.find("rm") == 0) {
            string quit;
            unsigned int id = strtoul(command.substr(3).c_str(), NULL, 10);
            // érvénytelen karakter esetén az strtoul() 0-t ad
            if (id == 0) {
                cout << "Lehetseges, hogy nem megfelelo azonositot adott meg. Erositse meg, hogy valoban az elso, "
                        "0 azonositoju filmet szeretne torolni. Minden nem \"igen\" valasz nem-nek szamit. (igen/nem): "
                        << endl;
                cin >> quit;
                if (quit.find("igen") != (unsigned) -1)
                    coll.remove(id);
            }
            else coll.remove(id);
        }
        else if (command == "rst") {
            string confirm;
            cout << "A nem mentett modositasok elvesznek, ha nem menti a gyujtemenyt." << endl;
            while ((confirm.find("igen") != 0 && confirm.find("nem") != 0)) {
                cout << "Biztosan ki szeretne lepni? (igen/nem): ";
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
                    "a gyujtemenyben\n\tp:\tgyujtemeny beolvasasa fajlbol\n\tls:\ta tarolt filmek kilistazasa\n\trm id:"
                    "\tmegadott azonositoju film torlese a gyujtemenybol\n\trst:\tminden film torlese a gyujtemenybol"
                    "\n\tment: fajlba irja a jelenlegi gyujtemenyt\n\tkilep:\tkilep a programbol" << endl;
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
        command = "";
    }
    cout << "Bezarhatja a programot." << endl;
#endif

    return 0;
}

#ifndef JPORTA
/** Film felvétele a gyűjteménybe a konzolon megadott adatokból
 *
 * @param coll A gyűjtemény, amibe felvesszük a filmet
 */
void add(Collection& coll) {
    cout << "Adja meg a kivant tipust: 1 - Normal film, 2 - Csaladi film, 3 - Dokumentumfilm: ";
    int category;
    cin >> category;

    if (category <= 0 || category > 3)
        cout << "Ervenytelen tipus." << endl;
    else {
        string split[4];
        cout << "A film cime: ";
        // üres string és ékezetes string nem elfogadott
        while (split[0].empty() || containsAccentedChar(split[0].c_str()))
            getline(cin, split[0]);

        // if (containsAccentedChar(split[0].c_str())) { return; }
        cout << "Hossza percben: ";
        cin >> split[1];
        cout << "Kiadasi eve: ";
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
                Rating rating = (Rating) ageRating;
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
                while (split[3].empty()) // üres string nem elfogadott
                    getline(cin, split[3]);
                Documentary* mv = new Documentary(split[0], runningTime, releaseYear, split[3]);
                coll.add(mv);
            }
            // érvénytelen filmtípus megadása esetén
            default:
                break;
        }
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
 * @return True, ha talált meg nem engedett karaktert, egyébként false
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

#include <iostream>

#include "gtest_lite.h"
#include "memtrace.h"

#include "movie.h"
#include "family.h"
#include "documentary.h"
#include "collection.h"

/* tesztesetek */
int main() {
    // fájlba és konzolra írás tesztelése mindegyik filmtípuson
    TEST(movies, print) {
        stringstream t1, t2, t3;
        Movie* test1mv = new Movie("1917", 119, 2019);
        Family* test2mv = new Family("Frozen 2", 103, 2019, ages6AndUp);
        Documentary* test3mv = new Documentary("Free solo", 97, 2018, "Professional rock climber "
                                                   "Alex Honnold attempts to conquer the first free solo climb of "
                                                   "famed El Capitan's 900-metre vertical rock face at Yosemite "
                                                   "National Park.");
        // konzolra írás függvényének tesztelése
        test1mv->print(t1);
        // az id inicializálatlan (unsigned -1 = 4294967295)
        EXPECT_STREQ("4294967295\t1917\t119\t2019\tMovie", t1.str().c_str());

        // gyűjteményhez adjuk, hogy kapjon id-t
        Collection coll;
        coll.add(test2mv);
        test2mv->print(t2);
        EXPECT_STREQ("0\tFrozen 2\t103\t2019\tFamily\t6", t2.str().c_str());

        // fájlba írás
        test3mv->print(t3, true);
        EXPECT_STREQ("1;Free solo;97;2018;Professional rock climber Alex Honnold attempts to conquer the "
                     "first free solo climb of famed El Capitan's 900-metre vertical rock face at "
                     "Yosemite National Park.", t3.str().c_str());
        delete test1mv; // test2mv gyűjteményhez lett adva, azt a dtor felszabadítja
        delete test3mv;
    } ENDM

    // gyűjteményhez adás és kiírás
    TEST(collection, addAndPrint) {
        Movie* test1mv = new Movie("1917", 119, 2019);
        Family* test2mv = new Family("Frozen 2", 103, 2019, ages6AndUp);
        Documentary* test3mv = new Documentary("Free solo", 97, 2018, "Professional rock climber "
                                                   "Alex Honnold attempts to conquer the first free solo climb of "
                                                   "famed El Capitan's 900-metre vertical rock face at Yosemite "
                                                   "National Park.");
        Collection coll;
        // üres gyűjtemény kiírása
        stringstream ss;
        coll.print(ss);
        EXPECT_STREQ("ID\tCim\tHossz\tEv\tKategoria\tEgyeb\n\n", ss.str().c_str());
        coll.add(test1mv);
        coll.add(test2mv);
        coll.add(test3mv);
        EXPECT_EQ(3, coll.getMovies().getElementCount());
        stringstream t1, t2, t3;

        test1mv->print(t1);
        EXPECT_STREQ("0\t1917\t119\t2019\tMovie", t1.str().c_str());
        test2mv->print(t2);
        EXPECT_STREQ("1\tFrozen 2\t103\t2019\tFamily\t6", t2.str().c_str());
        test3mv->print(t3, true);
        EXPECT_STREQ("1;Free solo;97;2018;Professional rock climber Alex Honnold attempts to conquer the "
                     "first free solo climb of famed El Capitan's 900-metre vertical rock face at "
                     "Yosemite National Park.", t3.str().c_str());
        // objektumok által foglalt memóriát a gyűjtemény szabadítja fel
    } ENDM

    // a filmek operator= és operator== függvényeinek tesztelése
    TEST(movies, operators) {
        Movie* test1mv = new Movie("1917", 119, 2019);
        Family* test2mv = new Family("Frozen 2", 103, 2019, ages6AndUp);
        Documentary* test3mv = new Documentary("Free solo", 97, 2018, "Professional rock climber "
                                                   "Alex Honnold attempts to conquer the first free solo climb of "
                                                   "famed El Capitan's 900-metre vertical rock face at Yosemite "
                                                   "National Park.");
        Movie test1copy = *test1mv;
        Family test2copy = *test2mv;
        Documentary test3copy = *test3mv;
//        Documentary wrongType = test2mv;
//        EXPECT_EQ(false, test2mv == wrongType);
        EXPECT_EQ(false, *test1mv == *test2mv);
        EXPECT_EQ(false, *test3mv == *test1mv);
        EXPECT_EQ(true, *test1mv == test1copy);
        EXPECT_EQ(true, *test2mv == test2copy);
        EXPECT_EQ(true, *test3mv == test3copy);
        delete test1mv;
        delete test2mv;
        delete test3mv;
    } ENDM

    // a túlindexelésnél dobott kivételt és a törlés függvényeket teszteli
    TEST(collection, indexer) {
        Movie* test1mv = new Movie("1917", 119, 2019);
        Family* test2mv = new Family("Frozen 2", 103, 2019, ages6AndUp);
        Documentary* test3mv = new Documentary("Free solo", 97, 2018, "Professional rock climber "
                                                   "Alex Honnold attempts to conquer the first free solo climb of "
                                                   "famed El Capitan's 900-metre vertical rock face at Yosemite "
                                                   "National Park.");
        Collection coll;
        coll.add(test1mv);
        coll.add(test2mv);
        coll.add(test3mv);
        EXPECT_EQ(3, coll.getMovies().getElementCount());
        EXPECT_ANY_THROW(coll.getMovies()[15]);
        EXPECT_NO_THROW(coll.getMovies()[2]);
        EXPECT_NO_THROW(coll.remove(2));
        EXPECT_EQ(2, coll.getMovies().getElementCount());
        coll.clearCollection();
        EXPECT_EQ(0, coll.getMovies().getElementCount());
    } ENDM

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
                     "103\t2019\tFamily\t6\n", ss1.str().c_str());
        // Több találat esetén minden találatot kiír
        coll.search("e", ss2);
        EXPECT_STREQ("Kereses - \"e\":\nID\tCim\tHossz\tMegjelenes eve\tKategoria\tEgyeb\n1\tFrozen 2\t"
                     "103\t2019\tFamily\t6\n2\tFree solo\t97\t2018\tDocumentary\tAlex Honnold attempts to conquer the "
                     "first free solo climb of El Capitan's 900-metre vertical rock face.\n", ss2.str().c_str());
    } ENDM

    TEST(collection, readFile) {
        Collection coll;
        coll.readFile("./teszt.txt");
        Family* familymv = (Family*) coll.getMovies()[1];
        EXPECT_EQ(12, familymv->getAgeRating());
        stringstream ss;
        Documentary* docmv = (Documentary*) coll.getMovies()[2];
        docmv->print(ss);
        EXPECT_STREQ("2\tDokumentumfilm\t86\t2013\tDocumentary\tDokumentumfilm leirasa", ss.str().c_str());
    } ENDM

    return 0;
}

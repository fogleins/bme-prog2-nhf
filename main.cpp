#include <iostream>

#include "gtest_lite.h"
#include "memtrace.h"

#include "movie.h"
#include "family.h"
#include "documentary.h"
#include "collection.h"

#define MEMTRACE
/* tesztesetek */
int main() {
    std::cout << "Hello, World!" << std::endl;

    Movie film1 = Movie("Film cime", 120, 2020);
    Family film2 = Family("Csaladi film", 108, 2018, ages12AndUp);
    Documentary film3 = Documentary("Dokumentumfilm", 86, 2013,"Dokumentumfilm leirasa");
    Movie film4 = Movie("Film cime", 92, 2020);
    film4 = film1;
    bool egyezik = film1 == film3;
    Collection coll;
    coll.add(film1);
    coll.add(film2);
    coll.add(film3);
    coll.remove(10);
    coll.print();
    coll.writeFile("./teszt.txt");
    coll.search("ci");
    coll.remove(2); // TODO: ha ez a sor nincs itt, a coll2 rész crashel
    coll.print();
    cout << coll.getMovies().getElementCount() << endl;

//    coll.clearCollection();

    cout << "\ncoll2:\n";
    Collection coll2;
    coll2 = coll;
    coll.clearCollection();
    if (!egyezik)
        coll2.print();

    return 0;
}

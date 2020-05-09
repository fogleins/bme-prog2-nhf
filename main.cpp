#include <iostream>

#include "gtest_lite.h"
#include "memtrace.h"

#include "movie.h"
#include "family.h"
#include "documentary.h"

/* tesztesetek */
int main() {
    std::cout << "Hello, World!" << std::endl;

    Movie film1 = Movie("Film cime", 120, 2020);
    Family film2 = Family("Csaladi film", 108, 2018, ages12AndUp);
    Documentary film3 = Documentary("Dokumentumfilm", 86, 2013,"Dokumentumfilm leirasa");
    Movie film4 = Movie("Film cime", 92, 2020);
    film4 = film1;
    bool egyezik = film1 == film4;

    return 0;
}
